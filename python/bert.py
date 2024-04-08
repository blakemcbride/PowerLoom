#!/usr/bin/env python-pli

############################# BEGIN LICENSE BLOCK ############################
#                                                                            #
# Version: MPL 1.1/GPL 2.0/LGPL 2.1                                          #
#                                                                            #
# The contents of this file are subject to the Mozilla Public License        #
# Version 1.1 (the "License"); you may not use this file except in           #
# compliance with the License. You may obtain a copy of the License at       #
# http://www.mozilla.org/MPL/                                                #
#                                                                            #
# Software distributed under the License is distributed on an "AS IS" basis, #
# WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License   #
# for the specific language governing rights and limitations under the       #
# License.                                                                   #
#                                                                            #
# The Original Code is the PowerLoom KR&R System.                            #
#                                                                            #
# The Initial Developer of the Original Code is                              #
# UNIVERSITY OF SOUTHERN CALIFORNIA, INFORMATION SCIENCES INSTITUTE          #
# 4676 Admiralty Way, Marina Del Rey, California 90292, U.S.A.               #
#                                                                            #
# Portions created by the Initial Developer are Copyright (C) 2020           #
# the Initial Developer. All Rights Reserved.                                #
#                                                                            #
# Contributor(s):                                                            #
#                                                                            #
# Alternatively, the contents of this file may be used under the terms of    #
# either the GNU General Public License Version 2 or later (the "GPL"), or   #
# the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),   #
# in which case the provisions of the GPL or the LGPL are applicable instead #
# of those above. If you wish to allow use of your version of this file only #
# under the terms of either the GPL or the LGPL, and not to allow others to  #
# use your version of this file under the terms of the MPL, indicate your    #
# decision by deleting the provisions above and replace them with the notice #
# and other provisions required by the GPL or the LGPL. If you do not delete #
# the provisions above, a recipient may use your version of this file under  #
# the terms of any one of the MPL, the GPL or the LGPL.                      #
#                                                                            #
############################# END LICENSE BLOCK ##############################

# Various utilities to use/experiment with pretrained BERT embeddings
# using pytorch_pretrained_bert

import os
import os.path
import sys
import logging
from functools import lru_cache

import torch
from pytorch_pretrained_bert import BertTokenizer, BertModel, BertForMaskedLM


currentModelName = 'bert-base-uncased'
currentModel = None
currentTokenizer = None

def getTokenizer(modelName=None):
    global currentTokenizer, currentModelName
    modelName = modelName or currentModelName
    if currentTokenizer is not None and getattr(currentTokenizer, '_modelName', None) == modelName:
        return currentTokenizer
    currentTokenizer = BertTokenizer.from_pretrained(modelName)
    setattr(currentTokenizer, '_modelName', modelName)
    return currentTokenizer

def getModel(modelName=None):
    global currentModel, currentModelName
    modelName = modelName or currentModelName
    if currentModel is not None and getattr(currentModel, '_modelName', None) == modelName:
        return currentModel
    currentModel = BertModel.from_pretrained(modelName)
    currentModel.eval()
    setattr(currentModel, '_modelName', modelName)
    return currentModel

@lru_cache(maxsize=100)
def tokenizeSentence(text):
    tokenizer = getTokenizer()
    sentence = "[CLS] " + text + " [SEP]"
    tokens = tokenizer.tokenize(text)
    tokenIds = tokenizer.convert_tokens_to_ids(tokens)
    # for single sequences the BERT convention is to use 0 as the only sequence ID,
    # see: https://github.com/google-research/bert/blob/master/extract_features.py
    segmentIds = [0] * len(tokens)
    return tokens, tokenIds, segmentIds

def encodeSentenceToLayers(text):
    model = getModel()
    tokens, tokenIds, segmentIds = tokenizeSentence(text)
    tokensTensor = torch.tensor([tokenIds])
    segmentIdsTensor = torch.tensor([segmentIds])
    with torch.no_grad():
        # generate list of #layers with (#batches x #tokens x #features) tensors,
        # e.g., 12 x 1 x 5 x 768 for a 5-token sentence through a 12-layer model:
        layers, _ = model(tokensTensor, segmentIdsTensor)
        # convert the list of layers into an actual tensor dimension:
        layers = torch.stack(layers, dim=0)
        # eliminate the 1-element batch dimension:
        layers = torch.squeeze(layers, dim=1)
        # result is (#layers x #tokens x #features):
        return layers


### Generating simple embedding-style vectors for words and sentences:

# - sentence embeddings: avg the embeddings of the second to last layer via torch.mean(_, dim=0)
# - word embeddings: sum the last four layers for each token; should we renormalize or rely on
#   our activation function for mapping back onto 0-1 outputs

@lru_cache(maxsize=100)
def getSentenceEmbedding(text, layer=-2):
    """Simple sentence embedding that averages the token embeddings of the second-to-last `layer'.
    To get Arora-style embeddings, we could further weight them by their smoothed inverse frequency.
    See for example: https://github.com/peter3125/sentence2vec/blob/master/sentence2vec.py
    The PCA to remove the 0-th dimension is probably not necessary given that we are basing this
    on one of the later more "semantic" layers of the BERT model.
    Also: if we are using this as an input to a learner, we already further fine-tune through training.
    """
    layers = encodeSentenceToLayers(text)
    sentLayer = layers[layer]
    embedding = torch.mean(sentLayer, dim=0)
    return embedding

@lru_cache(maxsize=100)
def getTokenEmbeddings(text, start=-4, end=None):
    layers = encodeSentenceToLayers(text)
    # permute to make tokens the first dimension:
    tokenLayers = layers.permute(1, 0, 2)
    embeddings = []
    for token in tokenLayers:
        # sum the last 4 (or from start:end) layers:
        embeddings.append(torch.sum(token[start:end], dim=0))
    return embeddings

@lru_cache(maxsize=100)
def getWordEmbeddings(text, start=-4, end=None):
    """Variant of `getTokenEmbeddings' that only preserves alpha-numeric tokens and splices
    tokens that were split by the tokenizer.  Since this produces a new tokenization, we
    return the resulting list of words identified by their positions linked to their embeddings.
    """
    # since we are memoizing, we need to copy before reversing:
    tokens = tokenizeSentence(text)[0][:]
    tokenEmbeddings = getTokenEmbeddings(text, start=start, end=end)[:]
    tokens.reverse()
    tokenEmbeddings.reverse()
    words = []
    wordEmbeddings = []
    curword = ''
    curembs = []
    for tok, emb in zip(tokens, tokenEmbeddings):
        if tok.startswith('##'):
            curword = tok[2:] + curword
            curembs.append(emb)
        elif tok[0].isalnum():
            curword = tok + curword
            words.append(curword)
            curembs.append(emb)
            if len(curembs) > 1:
                wordEmbeddings.append(torch.mean(torch.stack(curembs), dim=0))
            else:
                wordEmbeddings.append(curembs[0])
            curword = ''
            curembs = []
        else:
            curword = ''
            curembs = []
    words.reverse()
    wordEmbeddings.reverse()
    return words, wordEmbeddings

def getWordEmbedding(word, text=None, occidx=0, start=-4, end=None):
    """Return the embedding for `word' occuring in `text' (which defaults to `word').  By default the
    embedding of the first occurrance of `word' in `text' will be returned.  For different positions
    the 0-based `occidx' can be set to 1, 2, 3, etc.  Matching of `word' will always be performed
    case-insensitively, regardless of which tokenizer or BERT model is in use.
    """
    if text is None:
        text = word
    words, wordEmbeddings = getWordEmbeddings(text, start=start, end=end)
    word = word.lower()
    for w, e in zip(words, wordEmbeddings):
        if w.lower() == word:
            if occidx <= 0:
                return e
            else:
                occidx -= 1
    return None

def embeddingSimilarity(emb1, emb2):
    """Simple similarity measure for inspection and sanity checking."""
    from scipy.spatial.distance import cosine
    # cosine distance goes from 0-2 for vectors that can have negative components,
    # similarity for 0-degreess is 1.0, 90-degrees is 0.5 and 180-degrees is 0:
    return 1.0 - cosine(emb1, emb2) * 0.5

"""
>>> be1 = bert.getWordEmbedding("bank", "The bank robber went down to the river bank", occidx=0)
>>> be2 = bert.getWordEmbedding("bank", "The bank robber went down to the river bank", occidx=1)
>>> bert.embeddingSimilarity(be1, be2)
0.9053761661052704
>>> bert.embeddingSimilarity(be1, be1)
1.0
>>> be1 = bert.getWordEmbedding("bus", "The computer bus is 8-bit wide")
>>> be2 = bert.getWordEmbedding("bus", "I took my computer on the bus")
>>> bert.embeddingSimilarity(be1, be2)
0.814663827419281
"""

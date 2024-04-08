#!/usr/bin/env python

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
# Portions created by the Initial Developer are Copyright (C) 2022-2022      #
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

### PowerLoom interface to Huggingface transformers API for NLP tasks

from __future__ import print_function, division, absolute_import

import sys
PY2 = sys.version_info[0] == 2
PY3 = sys.version_info[0] >= 3
if PY3:
    unicode = str
    basestring = (bytes, unicode)
    long = int

if PY3:
    from functools import lru_cache
else:
    from functools32 import lru_cache

import re
import copy
    
import torch
import transformers as trf
import misc
import stellapi as spi
import ploompi as pli


### Configuration:

textDocumentsModule = 'TEXT-DOCUMENTS'
textDataModule = 'TEXT-DATA'

pythonEvalModule = sys.modules['__main__']
defaultFramework = 'pt' # currently hardcoded below, since various operators assume torch for now

debugSpecialist = None # or 'trace', 'step'


### Pipeline management:

def normalizeModelName(name, _norm = re.compile(r'[^a-zA-Z0-9]+')):
    """Normalize a model 'name' or list of names for comparison.
    This removes all punctuation, whitespace, etc. and converts to lower case.
    """
    if isinstance(name, str):
        return _norm.sub('', name).lower()
    else:
        return [_norm.sub("", n).lower() for n in name]

@lru_cache(maxsize=20)
def getTransformerPipeline(task, model=None, tokenizer=None):
    """Instantiate a transformer pipeline for 'task' with 'model' and 'tokenizer'.
    Separated out here primarily to allow memoization, so we don't instantiate
    the same pipeline multiple times.
    """
    if isinstance(model, str):
        if tokenizer is None:
            tokenizer = trf.AutoTokenizer.from_pretrained(model)
    return trf.pipeline(task, model=model, tokenizer=tokenizer)


class NlpPipeline(object):
    """Wrapper class around transformers.Pipeline to give us
    more control, uniformity and flexibility.
    """

    pipelineNames = normalizeModelName(['NlpPipeline'])
    defaultModel = None
    maxCache = 10000
    
    @classmethod
    def getPipelineClass(self, ptype):
        """Find the appropriate class based on the pipeline type 'ptype',
        which can be a pipeline name, class name or class.
        """
        if isinstance(ptype, type) and issubclass(ptype, NlpPipeline):
            return ptype
        elif isinstance(ptype, str):
            active = set([NlpPipeline])
            closed = set()
            while len(active) > 0:
                current = active.pop()
                if normalizeModelName(ptype) in current.pipelineNames:
                    return current
                closed.add(current)
                active.update([sub for sub in current.__subclasses__() if sub not in closed])
        raise Exception(f'cannot determine NlpPipeline class from {ptype}')
    
    def __init__(self, ptype=None, model=None, tokenizer=None):
        self.model = model
        self.tokenizer = tokenizer
        self.pipeline = None
        # minor trickery: change the class of this instance to what we really want it to be:
        self.__class__ = self.getPipelineClass(ptype or self.__class__)
        self.normalizeArguments()
        self.pipeline = self.getPipeline()

    def useDefaultModel(self):
        """Return True if the current model spec indicates the use of the default model.
        """
        if isinstance(self.model, str):
            model = normalizeModelName(self.model)
            if model.startswith('def') or model in self.pipelineNames:
                return True
        return self.model is None

    def normalizeArguments(self):
        if self.useDefaultModel():
            self.model = self.defaultModel

    def getPipeline(self):
        """Class API method that should be implemented on subs.
        Return or create an appropriate transformer pipeline for this class.
        """
        if isinstance(self.pipeline, trf.Pipeline):
            return self.pipeline
        raise Exception('not implemented')

    def runText(self, text, *args, toStella=False, **kwdargs):
        """Class API method that should be implemented on subs.
        This generally analyzes 'text' according to the model, tokenizer and pipeline
        of this class, possibly adding additional 'args' and 'kwdargs' for control.
        Generally returns the result as a list of dicts describing the results with
        fields varying by pipeline.  If 'toStella' is True, convert the result into
        a STELLA object or list of tuples usable by specialists and computations.
        For now this generally assumes a single 'text' while the pipeline API can
        process multiple texts at once.
        """
        raise Exception('not implemented')


class PosTagPipeline(NlpPipeline):

    pipelineNames = normalizeModelName(['PosTagPipeline', 'PosTag', 'PosTagger',])
    defaultModel = 'vblagoje/bert-english-uncased-finetuned-pos'

    def getPipeline(self):
        if not isinstance(self.pipeline, trf.Pipeline):
            self.pipeline = getTransformerPipeline('token-classification', model=self.model, tokenizer=self.tokenizer)
        return self.pipeline
    
    @lru_cache(maxsize=NlpPipeline.maxCache)
    def runText(self, text, toStella=False):
        """Run the postag pipeline (or other token analysis pipeline such as NER)  on 'text' and return 
        the result as a list of dicts, one per token.
        If 'toStella', return the result as a STELLA list of '(word, entity, index, start, end, score)' tuples.
        Note that 'index' is 1-based while 'start' and 'end' are 0-based.
        """
        text = misc.coerceToUnicode(text)
        results = self.pipeline(text)
        if toStella:
            tuples = []
            for res in results:
                # this contains various numpy number types which we have to convert to regular types before STELLA conversion:
                tuples.append([res['word'], res['entity'], int(res['index']), int(res['start']), int(res['end']), float(res['score'])])
            results = spi.pythonToStellaTree(tuples)
        return results


class NerPipeline(PosTagPipeline):

    pipelineNames = normalizeModelName(['NerPipeline', 'NER', 'Named-Entity-Recognition',])
    defaultModel = 'dslim/bert-base-NER'


class TextClassificationPipeline(NlpPipeline):

    pipelineNames = normalizeModelName(['TextClassification', 'TextClass', 'Classification',])
    defaultModel = 'roberta-large-mnli'

    def getPipeline(self):
        if not isinstance(self.pipeline, trf.Pipeline):
            self.pipeline = getTransformerPipeline('text-classification', model=self.model, tokenizer=self.tokenizer)
        return self.pipeline
    
    @lru_cache(maxsize=NlpPipeline.maxCache)
    def runText(self, text, toStella=False, allClasses=True):
        """Run the text classification pipeline on a single 'text' and return the result as a list of dicts,
        one per class sorted by descending scores (or only the top-scoring class if 'allClasses' is False).
        If 'toStella', return the result as a STELLA list of '(label, score)' tuples.
        """
        text = misc.coerceToUnicode(text)
        results = self.pipeline(text, return_all_scores=allClasses)
        # if we are asking for all classes, we get an extra level of nesting:
        results = results[0] if allClasses else results
        results.sort(key=lambda x: x['score'], reverse=True)
        if toStella:
            tuples = []
            for res in results:
                # this contains various numpy number types which we have to convert to regular types before STELLA conversion:
                tuples.append([res['label'], float(res['score'])])
            results = spi.pythonToStellaTree(tuples)
        return results


class SentimentAnalysisPipeline(NlpPipeline):

    pipelineNames = normalizeModelName(['SentimentAnalysisPipeline', 'SentimentAnalysis', 'SA',])
    defaultModel = 'distilbert-base-uncased-finetuned-sst-2-english'

    def getPipeline(self):
        if not isinstance(self.pipeline, trf.Pipeline):
            self.pipeline = getTransformerPipeline('sentiment-analysis', model=self.model, tokenizer=self.tokenizer)
        return self.pipeline
    
    @lru_cache(maxsize=NlpPipeline.maxCache)
    def runText(self, text, toStella=False):
        """Run the sentiment analysis pipeline on 'text' and return the result as a singleton list of dicts.
        If 'toStella', return the result as a singleton STELLA list of '(label, score)' tuples.
        """
        text = misc.coerceToUnicode(text)
        results = self.pipeline(text)
        if toStella:
            tuples = []
            for res in results:
                # this contains various numpy number types which we have to convert to regular types before STELLA conversion:
                tuples.append([res['label'], float(res['score'])])
            results = spi.pythonToStellaTree(tuples)
        return results


class ParaphraseAnalysisPipeline(NlpPipeline):

    pipelineNames = normalizeModelName(['ParaphraseAnalysisPipeline', 'ParaphraseAnalysis', 'PA',])
    defaultModel = 'bert-base-cased-finetuned-mrpc'

    def getPipeline(self):
        if not isinstance(self.pipeline, trf.Pipeline):
            self.pipeline = getTransformerPipeline('text-classification', model=self.model, tokenizer=self.tokenizer)
            # we can't call the pipeline directly for this task it seems, so we store its components to use them directly:
            self.model = self.pipeline.model
            self.tokenizer = self.pipeline.tokenizer
        return self.pipeline
    
    @lru_cache(maxsize=NlpPipeline.maxCache)
    def runText(self, text1, text2, toStella=False):
        """Run the paraphrase analysis pipeline on 'text1' and 'text2' and return the computed score.
        The score describes how strongly 'text2' could be viewed as a paraphrase of 'text1' (note
        that this is not symmetric).  If 'toStella', convert the score into a STELLA wrapper.
        """
        text1 = misc.coerceToUnicode(text1)
        text2 = misc.coerceToUnicode(text2)
        inputs = self.tokenizer(text1, text2, return_tensors='pt')
        logits = self.model(**inputs).logits
        score = float(torch.softmax(logits, dim=1).tolist()[0][1])
        if toStella:
            score = pli.createFloatWrapper(score)
        return score


class PredictNextWordPipeline(NlpPipeline):

    pipelineNames = normalizeModelName(['PredictNextWordPipeline', 'PredictNextWord', 'PredictWord', 'PW',])
    defaultModel = "gpt2-medium"

    def getPipeline(self):
        if not isinstance(self.pipeline, trf.Pipeline):
            self.pipeline = getTransformerPipeline('text-generation', model=self.model, tokenizer=self.tokenizer)
            # we can't call the pipeline directly for this task it seems, so we store its components to use them directly:
            self.model = self.pipeline.model
            self.tokenizer = self.pipeline.tokenizer
        return self.pipeline
    
    @lru_cache(maxsize=NlpPipeline.maxCache)
    def runTextRaw(self, text, k=5):
        """Run the prediction pipeline once to predict the top-'k' single words (or tokens)
        to follow 'text' together with their likelihood scores.  Note, that the predicted words or tokens
        might be particles of the last word/token in 'text' or of another token following the prediction.
        """
        text = misc.coerceToUnicode(text)
        inputs = self.tokenizer(text, return_tensors='pt')
        with torch.no_grad():
            logits = self.model(**inputs).logits[:, -1, :]
        scores, indices = torch.topk(logits, k)
        results = [{'word': self.tokenizer.decode(i.item()), 'rank': rank + 1, 'score': float(s.item())}
                   for rank, (i, s) in enumerate(zip(indices[0], scores[0]))]
        return results

    def countWords(self, text):
        """Count proper words in 'text', ignoring punctuation characters.
        """
        # simple method for now, we can use regex later - however, this counts
        # a sole punctuation character as a single word for now:
        return text.strip().count(' ') + 1
    
    @lru_cache(maxsize=NlpPipeline.maxCache)
    def runText(self, text, n=1, k=5, toStella=False):
        """Generate the top-'k' most likely successor words or phrases to 'text'.
        'n' controls the number of content words in the successor phrase (albeit
        word counting is currently somewhat imperfect).  If 'toStella', return 
        the results as a list of (word, rank, score) STELLA tuples.
        """
        # this is a bit slow for multi-word phrases, but the official text
        # generation API seems to be slowish as well:
        results = self.runTextRaw(text, k=k)
        results = copy.deepcopy(results)
        # this may return words that are particles of the last word in 'text',
        # also, for now we might generate and count punctuation-only words:
        for res in results:
            while self.countWords(res['word']) < n:
                nextWord = self.runTextRaw(text + res['word'], k=1)
                res['word'] += nextWord[0]['word']
                res['score'] += nextWord[0]['score']
        if toStella:
            tuples = []
            for res in results:
                tuples.append([res['word'], res['rank'], res['score']])
            results = spi.pythonToStellaTree(tuples)
        return results

    
@lru_cache(maxsize=100)
def getNlpPipeline(task, model):
    """Create or return the cached NLP pipeline indicated by 'task' and 'model'.
    This first evaluates 'model' as a Python expression in 'pythonEvalModule'
    and if that yields a pipeline object returns and caches that.  Otherwise,
    an NLP pipeline is constructed based on 'task' and 'model'.  If 'model' equals
    'def...' or is None, a default model is used for the specified 'task'.
    """
    if model is not None:
        if normalizeModelName(str(model)).startswith('def'):
            model = None
        else:
            model = str(model)
    try:
        pipeline = eval(model, pythonEvalModule.__dict__)
        if isinstance(pipeline, NlpPipeline):
            return pipeline
    except:
        pass
    return NlpPipeline(ptype=str(task), model=model)


### Specialists and computations:

def nlpPipelineSpecialist(task, frame, lastMove, inputArgTypes=()):
    """Specialist helper for various specialist functions below.  Assumes the incoming frame to have
    ?model and ?text bound, and binds output arguments to the result of NlpPipeline.runText(?text...).
    The appropriate NlpPipeline object will be created or accessed from a cache.  
    ?model can be "def" or "default" to load the default model for this pipeline or name an existing
    Huggingface model appropriate for 'task', and for which we have a matching NlpPipeline implementation.
    'inputArgTypes' can be used to define the types of additional input arguments that must be bound
    and passed to 'runText', for example the 'n' and 'k' parameters of PredictNextWordPipeline.runText().
    """
    if debugSpecialist == 'step':
        import pdb
        pdb.set_trace()
    firstArgIndex = 2 + len(inputArgTypes)
    arity = pli.getFrameArity(frame)
    iterator = pli.getFrameIterator(frame)

    if iterator is None:
        # first time around, the model, text and other input args need to be bound:
        if pli.isFrameBindingPattern(frame, 'BB'):
            model = pli.getNthFrameBinding(frame, 0)
            text = pli.getNthFrameBinding(frame, 1)
            if isinstance(model, (pli.StringWrapper, pli.LogicObject)) and isinstance(text, pli.StringWrapper):
                # check and process any additional input args if we have them:
                inputArgs = []
                for i, argType in enumerate(inputArgTypes):
                    arg = pli.getNthFrameBinding(frame, 2 + i)
                    if not isinstance(arg, argType):
                        return pli.TERMINAL_FAILURE
                    inputArgs.append(arg.pythonify())
                pipeline = getNlpPipeline(task, model)
                if pipeline is None:
                    return pli.TERMINAL_FAILURE
                text = str(text)
                solutions = pipeline.runText(str(text), *inputArgs, toStella=True)
                iterator = pli.consToPlIterator(solutions)
                pli.setFrameIterator(frame, iterator)
                
        if iterator is None:
            return pli.TERMINAL_FAILURE
    
    # generate solutions:
    bindingState = pli.getFrameBindingState(frame)
    for row in iterator:
        row = list(row)
        bindingFailure = False
        for ci, i in enumerate(range(firstArgIndex, arity)):
            value = row[ci]
            if not pli.setNthFrameBinding(frame, i, value):
                bindingFailure = True
                break
        if not bindingFailure:
            # we successfully consumed a whole output row:
            return pli.CONTINUING_SUCCESS
        else:
            pli.setFrameBindingState(frame, bindingState)
    return pli.TERMINAL_FAILURE

@pli.specialist(relation='nlp-part-of-speech-tag', module=textDocumentsModule, create=True, arity=8, defer=True)
def nlpPostagSpecialist(frame, lastMove):
    """Specialist for the PowerLoom `nlp-part-of-speech-tag (?model ?text ?word ?entity ?index ?start ?end ?score)'
    relation which provides a PowerLoom API for the PosTagPipeline.runText() computation.
    Both ?model and ?text need to be bound.  ?model can be "def..." to load the default model for this pipeline
    or name an existing Huggingface token classification model (e.g., for NER or POS tagging).
    """
    return nlpPipelineSpecialist('postag', frame, lastMove)

@pli.specialist(relation='nlp-named-entity-recognition', module=textDocumentsModule, create=True, arity=8, defer=True)
def nlpNerSpecialist(frame, lastMove):
    """Specialist for the PowerLoom `nlp-named-entity-recognition (?model ?text ?word ?entity ?index ?start ?end ?score)'
    relation which provides a PowerLoom API for the NerPipeline.runText() computation.
    Both ?model and ?text need to be bound.  ?model can be "def..." to load the default model for this pipeline
    or name an existing Huggingface token classification model (e.g., for NER or POS tagging).
    """
    return nlpPipelineSpecialist('ner', frame, lastMove)

@pli.specialist(relation='nlp-text-classification', module=textDocumentsModule, create=True, arity=4, defer=True)
def nlpTextClassificationSpecialist(frame, lastMove):
    """Specialist for the PowerLoom `nlp-text-classification (?model ?text ?label ?score)' relation
    which provides a PowerLoom API for the TextClassificationPipeline.runText() computation.
    Both ?model and ?text need to be bound.  ?model can be "def..." to load the default model for this pipeline
    or name an existing Huggingface text classification model.
    """
    return nlpPipelineSpecialist('text-classification', frame, lastMove)

@pli.specialist(relation='nlp-sentiment-analysis', module=textDocumentsModule, create=True, arity=4, defer=True)
def sentimentAnalysisSpecialist(frame, lastMove):
    """Specialist for the PowerLoom `nlp-sentiment-analysis (?model ?text ?label ?score)'
    relation which provides a PowerLoom API for the SentimentAnalysisPipeline.runText() computation.
    Both ?model and ?text need to be bound.  ?model can be "def..." to load the default sentiment model
    or name an existing Huggingface sentiment analysis model that supports the pipeline API.
    """
    return nlpPipelineSpecialist('sentiment-analysis', frame, lastMove)

@pli.specialist(relation='nlp-predict-next-word', module=textDocumentsModule, create=True, arity=7, defer=True)
def predictNextWordSpecialist(frame, lastMove):
    """Specialist for the PowerLoom `nlp-predict-next-word (?model ?text ?n ?k ?word ?rank ?score)'
    relation which provides a PowerLoom API for the PredictNextWordPipeline.runText() computation.
    Both ?model and ?text need to be bound.  ?model can be "def..." to load the default generation model
    or name an existing Huggingface text generation model that supports the pipeline API.
    Additionally, ?n (the number of words to predict) and ?k (the top-k predictions to return)
    need to be bound.
    """
    return nlpPipelineSpecialist('predict-next-word', frame, lastMove, inputArgTypes=(pli.IntegerWrapper, pli.IntegerWrapper))

@pli.computation(function='nlp-test-paraphrase', module=textDocumentsModule, create=True, defer=True)
def testParaphraseComputation(model, text1, text2):
    """Computation for PowerLoom function `nlp-test-paraphrase (?model, ?text1, ?text2, ?score)'.
    Test whether ?text2 is a paraphrase of ?text1 according to ?model and return the resulting ?score.
    Note that this is not symmetric.  If ?model is "def..." the default paraphrase model will be used.
    """
    if debugSpecialist == 'step':
        import pdb
        pdb.set_trace()
    task = 'paraphrase-analysis'
    try:
        if (isinstance(model, (pli.StringWrapper, pli.LogicObject)) and
            isinstance(text1, pli.StringWrapper) and
            isinstance(text2, pli.StringWrapper)):
            pipeline = getNlpPipeline(task, model)
            if pipeline is None:
                return pli.TERMINAL_FAILURE
            score = pipeline.runText(str(text1), str(text2), toStella=True)
            return score
    except:
        pass
    return None


### Examples:

"""
TEXT-DATA |= (retrieve all (nlp-part-of-speech-tag def "Apple is headquartered in Cupertino" ?word ?entity ?index ?start ?end ?score))

There are 7 solutions:
#1: ?WORD="apple", ?ENTITY="PROPN", ?INDEX=1, ?START=0, ?END=5, ?SCORE=0.9988580346107483
#2: ?WORD="is", ?ENTITY="AUX", ?INDEX=2, ?START=6, ?END=8, ?SCORE=0.9957574009895325
#3: ?WORD="headquartered", ?ENTITY="VERB", ?INDEX=3, ?START=9, ?END=22, ?SCORE=0.9991775155067444
#4: ?WORD="in", ?ENTITY="ADP", ?INDEX=4, ?START=23, ?END=25, ?SCORE=0.9988315105438232
#5: ?WORD="cup", ?ENTITY="PROPN", ?INDEX=5, ?START=26, ?END=29, ?SCORE=0.9985600113868713
#6: ?WORD="##ert", ?ENTITY="PROPN", ?INDEX=6, ?START=29, ?END=32, ?SCORE=0.997100830078125
#7: ?WORD="##ino", ?ENTITY="PROPN", ?INDEX=7, ?START=32, ?END=35, ?SCORE=0.9983809590339661

TEXT-DATA |= (retrieve all (nlp-named-entity-recognition def "Apple is headquartered in Cupertino" ?word ?entity ?index ?start ?end ?score))

There are 4 solutions:
#1: ?WORD="Apple", ?ENTITY="B-ORG", ?INDEX=1, ?START=0, ?END=5, ?SCORE=0.9984509944915771
#2: ?WORD="Cup", ?ENTITY="B-LOC", ?INDEX=5, ?START=26, ?END=29, ?SCORE=0.9988107681274414
#3: ?WORD="##ert", ?ENTITY="I-LOC", ?INDEX=6, ?START=29, ?END=32, ?SCORE=0.9937691688537598
#4: ?WORD="##ino", ?ENTITY="I-LOC", ?INDEX=7, ?START=32, ?END=35, ?SCORE=0.9977803230285645

;;; use alternative model name to pick up the correct pipeline:
TEXT-DATA |= (retrieve all (nlp-named-entity-recognition NER "Apple is headquartered in Cupertino" ?word ?entity ?index ?start ?end ?score))

There are 4 solutions:
#1: ?WORD="Apple", ?ENTITY="B-ORG", ?INDEX=1, ?START=0, ?END=5, ?SCORE=0.9984509944915771
#2: ?WORD="Cup", ?ENTITY="B-LOC", ?INDEX=5, ?START=26, ?END=29, ?SCORE=0.9988107681274414
#3: ?WORD="##ert", ?ENTITY="I-LOC", ?INDEX=6, ?START=29, ?END=32, ?SCORE=0.9937691688537598
#4: ?WORD="##ino", ?ENTITY="I-LOC", ?INDEX=7, ?START=32, ?END=35, ?SCORE=0.9977803230285645

TEXT-DATA |= (retrieve all (nlp-text-classification def "I love you. </s></s> I like you." ?label ?score))

There are 3 solutions:
#1: ?LABEL="ENTAILMENT", ?SCORE=0.9283760190010071
#2: ?LABEL="NEUTRAL", ?SCORE=0.06432514637708664
#3: ?LABEL="CONTRADICTION", ?SCORE=0.007298848126083612

TEXT-DATA |= (retrieve all (nlp-sentiment-analysis def "I hate anchovies" ?label ?score))

There is 1 solution:
#1: ?LABEL="NEGATIVE", ?SCORE=0.9977256655693054

TEXT-DATA |= (retrieve all (nlp-test-paraphrase def "cats and dogs" "animals" ?s))

There is 1 solution:
#1: ?S=0.8296365737915039

TEXT-DATA |= (retrieve all (nlp-predict-next-word def "President Barack Obama and" 5 10 ?word ?rank ?score))

There are 10 solutions:
 #1: ?WORD=" his administration have been pushing", ?RANK=1, ?SCORE=-530.8006362915039
 #2: ?WORD=" the Democratic Party have been", ?RANK=2, ?SCORE=-438.0883102416992
 #3: ?WORD=" Republican presidential nominee Mitt Romney", ?RANK=3, ?SCORE=-385.5634841918945
 #4: ?WORD=" Russian President Vladimir Putin have", ?RANK=4, ?SCORE=-472.2831878662109
 #5: ?WORD=" President-elect Donald Trump shake hands", ?RANK=5, ?SCORE=-559.4683547019958
 #6: ?WORD=" Vice President Joe Biden will", ?RANK=6, ?SCORE=-392.4181547164917
 #7: ?WORD=" Hillary Clinton have been at", ?RANK=7, ?SCORE=-389.7384033203125
 #8: ?WORD=" other Democrats have been trying", ?RANK=8, ?SCORE=-586.1811370849609
 #9: ?WORD=" Donald Trump have been at", ?RANK=9, ?SCORE=-630.5829086303711
#10: ?WORD=" former President George W. Bush", ?RANK=10, ?SCORE=-341.0564231872559


;;; Specifying language models explicitly (the lm function is just syntactic sugar):

TEXT-DATA |= (deffunction lm (?name ?id))

|f|LM

TEXT-DATA |= (assert (lm postag "vblagoje/bert-english-uncased-finetuned-pos"))

|P|(= (LM POSTAG) "vblagoje/bert-english-uncased-finetuned-pos")

TEXT-DATA |= (assert (lm ner "dslim/bert-base-NER"))

|P|(= (LM NER) "dslim/bert-base-NER")

TEXT-DATA |= (retrieve all (nlp-part-of-speech-tag (lm postag) "Apple is headquartered in Cupertino" ?word ?entity ?index ?start ?end ?score))

There are 7 solutions:
#1: ?WORD="apple", ?ENTITY="PROPN", ?INDEX=1, ?START=0, ?END=5, ?SCORE=0.9988580346107483
#2: ?WORD="is", ?ENTITY="AUX", ?INDEX=2, ?START=6, ?END=8, ?SCORE=0.9957574009895325
#3: ?WORD="headquartered", ?ENTITY="VERB", ?INDEX=3, ?START=9, ?END=22, ?SCORE=0.9991775155067444
#4: ?WORD="in", ?ENTITY="ADP", ?INDEX=4, ?START=23, ?END=25, ?SCORE=0.9988315105438232
#5: ?WORD="cup", ?ENTITY="PROPN", ?INDEX=5, ?START=26, ?END=29, ?SCORE=0.9985600113868713
#6: ?WORD="##ert", ?ENTITY="PROPN", ?INDEX=6, ?START=29, ?END=32, ?SCORE=0.997100830078125
#7: ?WORD="##ino", ?ENTITY="PROPN", ?INDEX=7, ?START=32, ?END=35, ?SCORE=0.9983809590339661

TEXT-DATA |= (retrieve all (nlp-named-entity-recognition (lm ner) "Apple is headquartered in Cupertino" ?word ?entity ?index ?start ?end ?score))

There are 4 solutions:
#1: ?WORD="Apple", ?ENTITY="B-ORG", ?INDEX=1, ?START=0, ?END=5, ?SCORE=0.9984509944915771
#2: ?WORD="Cup", ?ENTITY="B-LOC", ?INDEX=5, ?START=26, ?END=29, ?SCORE=0.9988107681274414
#3: ?WORD="##ert", ?ENTITY="I-LOC", ?INDEX=6, ?START=29, ?END=32, ?SCORE=0.9937691688537598
#4: ?WORD="##ino", ?ENTITY="I-LOC", ?INDEX=7, ?START=32, ?END=35, ?SCORE=0.9977803230285645
"""

# If possible, execute PowerLoom definitions in the current environment, otherwise this has to be called again later:
pli.processDeferredCommands()

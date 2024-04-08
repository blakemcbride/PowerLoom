#!/bin/python

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
# Portions created by the Initial Developer are Copyright (C) 1997-2020      #
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
############################## END LICENSE BLOCK #############################


from __future__ import print_function, division, absolute_import

import sys
PY2 = sys.version_info[0] == 2
PY3 = sys.version_info[0] >= 3
if PY3:
    basestring = str
    unicode = str
    long = int

import os
import os.path
import re
import stellapi as spi
import ploompi as pli
import stellapi.stella.pdef as pstella
import stellapi.logic.pdef as plogic

import math
import numpy as np
import tensorflow as tf
import tensorflow.keras as keras

import argparse
import shlex
if PY3:
    from functools import lru_cache
else:
    from functools32 import lru_cache
import pickle
import pdb


# PowerLoom to TensorFlow callback wrappers which provide the entry points to the methods defined below.
# These do all the argument conversion and GC protection usually done automatically by STELLA API wrappers.
# However, this is different, since here we implement them on the Python side.  Nevertheless, we might
# want to think about supporting this more generally in the STELLA API.

spi.defun('logic/register-tensorflow-callback')

@spi.FFI.callback("void(void*, int, int, int)")
def tfCallbackAllocateNetworkArrays(net, numIn, numHidden, numOut):
    # special-purpose proxy-class conversion that presumes that mappings are already available:
    netClass = spi.lookupStellaTypeProxyClass(spi.boot.primaryClass(net))
    net = netClass(_stobj=net)
    net._getModel().allocateNetworkArrays(numIn, numHidden, numOut)
plogic.registerTensorflowCallback('tensorflow-neural-network.allocate-network-arrays', tfCallbackAllocateNetworkArrays)

@spi.FFI.callback("void(void*)")
def tfCallbackRandomizeNetworkWeights(net):
    netClass = spi.lookupStellaTypeProxyClass(spi.boot.primaryClass(net))
    net = netClass(_stobj=net)
    net._getModel().randomizeNetworkWeights()
plogic.registerTensorflowCallback('tensorflow-neural-network.randomize-network-weights', tfCallbackRandomizeNetworkWeights)

@spi.FFI.callback("void(void*)")
def tfCallbackInitializeNetworkWeights(net):
    netClass = spi.lookupStellaTypeProxyClass(spi.boot.primaryClass(net))
    net = netClass(_stobj=net)
    net._getModel().initializeNetworkWeights()
plogic.registerTensorflowCallback('tensorflow-neural-network.initialize-network-weights', tfCallbackInitializeNetworkWeights)

@spi.FFI.callback("void(void*, void*)")
def tfCallbackBuildPropositionNetwork(net, prop):
    netClass = spi.lookupStellaTypeProxyClass(spi.boot.primaryClass(net))
    net = netClass(_stobj=net)
    prop = plogic.Proposition(_stobj=prop)
    net._getModel().buildPropositionNetwork(prop)
plogic.registerTensorflowCallback('tensorflow-neural-network.build-proposition-network', tfCallbackBuildPropositionNetwork)

@spi.FFI.callback("int(void*)")
def tfCallbackNumberOfInputs(net):
    netClass = spi.lookupStellaTypeProxyClass(spi.boot.primaryClass(net))
    net = netClass(_stobj=net)
    return net._getModel().numberOfInputs()
plogic.registerTensorflowCallback('tensorflow-neural-network.number-of-inputs', tfCallbackNumberOfInputs)

@spi.FFI.callback("double(void*, int)")
def tfCallbackNthInput(net, n):
    netClass = spi.lookupStellaTypeProxyClass(spi.boot.primaryClass(net))
    net = netClass(_stobj=net)
    return net._getModel().nthInput(n)
plogic.registerTensorflowCallback('tensorflow-neural-network.nth-input', tfCallbackNthInput)

@spi.FFI.callback("double(void*, int)")
def tfCallbackNthInputError(net, n):
    netClass = spi.lookupStellaTypeProxyClass(spi.boot.primaryClass(net))
    net = netClass(_stobj=net)
    return net._getModel().nthInputError(n)
plogic.registerTensorflowCallback('tensorflow-neural-network.nth-input-error', tfCallbackNthInputError)

@spi.FFI.callback("void(void*, void*)")
def tfCallbackSetInputValues(net, values):
    netClass = spi.lookupStellaTypeProxyClass(spi.boot.primaryClass(net))
    net = netClass(_stobj=net)
    spi.gcProtectObject(values)
    values = pstella.Cons(_stobj=values)
    net._getModel().setInputValues(values)
plogic.registerTensorflowCallback('tensorflow-neural-network.set-input-values', tfCallbackSetInputValues)

@spi.FFI.callback("void(void*, void*)")
def tfCallbackSetVectorInputValues(net, values):
    netClass = spi.lookupStellaTypeProxyClass(spi.boot.primaryClass(net))
    net = netClass(_stobj=net)
    spi.gcProtectObject(values)
    values = pstella.Cons(_stobj=values)
    net._getModel().setVectorInputValues(values)
plogic.registerTensorflowCallback('tensorflow-neural-network.set-vector-input-values', tfCallbackSetVectorInputValues)

@spi.FFI.callback("double(void*)")
def tfCallbackForwardPropagateInputs(net):
    netClass = spi.lookupStellaTypeProxyClass(spi.boot.primaryClass(net))
    net = netClass(_stobj=net)
    return net._getModel().forwardPropagateInputs()
plogic.registerTensorflowCallback('tensorflow-neural-network.forward-propagate-inputs', tfCallbackForwardPropagateInputs)

@spi.FFI.callback("void(void*, double)")
def tfCallbackBackwardPropagateError(net, error):
    netClass = spi.lookupStellaTypeProxyClass(spi.boot.primaryClass(net))
    net = netClass(_stobj=net)
    net._getModel().backwardPropagateError(error)
plogic.registerTensorflowCallback('tensorflow-neural-network.backward-propagate-error', tfCallbackBackwardPropagateError)

@spi.FFI.callback("void(void*, double)")
def tfCallbackUpdateNetworkWeights(net, error):
    netClass = spi.lookupStellaTypeProxyClass(spi.boot.primaryClass(net))
    net = netClass(_stobj=net)
    net._getModel().updateNetworkWeights(error)
plogic.registerTensorflowCallback('tensorflow-neural-network.update-network-weights', tfCallbackUpdateNetworkWeights)


# TensorflowNeuralNetwork class whose methods implement the callbacks

spi.defglobal('logic/*Learning-Rate*')
spi.defglobal('logic/*Momentum-Term*')
spi.defglobal('logic/*Weight-Range*')
spi.defglobal('logic/*Error-Cutoff*')

debug = False
stellaFloatSize = 8
stellaLongSize = 8

@spi.logic.pdef
class _TensorflowNeuralNetwork(spi.ProxyClass):
    _stellaTypePath = "/LOGIC/@TENSORFLOW-NEURAL-NETWORK"
    _implClass = None

    def __init__(self, _stobj=None):
        self._stellaObject = _stobj
        modelRef = self.model
        if modelRef is None:
            modelImpl = self._implClass(self)
            # point modelRef.model to `self':
            modelRef = spi.getPythonObjectStellaPointer(modelImpl)
            self.model = modelRef
            # now that we've stored the pointer in the network object, release the GC protection:
            spi.getPythonObjectFromStellaPointer(modelRef)

    def _getModel(self):
        return spi.getPythonObjectFromStellaPointer(self.model)

spi.defslot('logic/TENSORFLOW-NEURAL-NETWORK.model')
spi.defslot('logic/TENSORFLOW-NEURAL-NETWORK.proposition')
spi.defmethod('logic/NEURAL-NETWORK.number-of-ignored-value-arguments')
spi.defmethod('logic/VECTOR-NEURAL-NETWORK.number-of-vector-argument-inputs')
spi.defmethod('logic/VECTOR-NEURAL-NETWORK.number-of-vector-argument-specs')


### Lessons learned

# We experimented with a number of different implementations which are encapsulated by classes
# that implement the various methods expected from TensorflowNeuralNetwork's.
# See old/chameleon_pli.py.2 for a lot of the trial and error and associated details.
#
# Native implementation deviations:
# - native Chameleon uses a slightly different base case to compute the initial error deltas
#   that also takes the derivative of the output value into account; we mirrored that in some
#   of our experimental versions which helped but in the end wasn't necessary.  The reason for
#   this might have been the realization that backchaining from one network to another is akin
#   to going a fixed edge of weight 1 from an input unit back to an output unit, in which case
#   the gradient computation would take the derivative of the output.
# - when doing the detailed comparison, we discovered a reinitializtion bug in the native code
#   during forward propagation, that amounts to hidden units becoming cumulative sums taking
#   values of prior hidden units into account.  We also mirrored that at some point but it didn't
#   really make a difference; additionally, TF will then take that into account during gradient
#   computation which again is different from what's done natively.
# - errors can be positive or negative and we still do the right thing, while in the TF implementation
#   the loss function had to be always positive to work
#
# Other notes and observations
# - we need `(set-rule-combination :noisy-or)'
# - for the model to work in concert with the PowerLoom learning code, output activation values
#   need to be in the range [0, 1], thus, activation functions such as atan need to be scaled
# - for the gradients to do the right thing, the loss function had to be always positive; our native
#   implementation doesn't seem to require that
# - the current TensorFlow model is a lot slower than the native implementation due to the fine-grained
#   and closely interleaved call structure (which results in one low-level TF op at a time).
#   Eventually, we have to create a trainer that batches things better so we can take advantage
#   of TFs parallelism
# - on a related note, a variant implementation that did the gradient computation and weight update directly
#   - as opposed to using an optimizer - slowed us down further by a factor of about 2.5.
# - we experimented with different activation functions (sigmoid, tanh, softsign, atan) and it looks like atan
#   works the best.  We also tried mixed and unscaled functions but to no advantage.
# - convergence on our test cases is still not stable, we usually convert in 200-500 epochs, but there
#   are still cases where that doesn't happen due to different initial values
# - just for history's sake, here is the setup that allowed us the first time to converge:
#   - fixed hidden sum init error in native forward propagation
#   - error = (target - output)
#   - loss = abs(error * output * (1 - output))  # to account for Dave's version of delta_k
#   - optimizer = tf.train.MomentumOptimizer(learning_rate=0.2, momentum=0.1)
#   - however, that setup still took 10,500 epochs until it finally started to converge quickly
#     on theory-revision.plm
# - the model below is now nice and concise, but it took us a while to get there
# - TO DO: the current callback structure doesn't handle exceptions properly, so if we break somewhere
#   below, we keep going on the C++ side

def asNumpyDtype(tspec):
    """Convert a TF (and possibly other) type spec into an equivalent Numpy type."""
    return np.dtype(str(tspec.name))
    
class TensorflowNeuralNetworkImplClassic(object):
    """Implementation that uses TF directly to define a model and tries to stay as close to the structure
    of the Chameleon model as possible (including the structure of the bias input unit).  This uses
    a per-network session object for execution.  This version uses scaled atan activation, which
    has a softer convergence behavior that seems to work better for our use case where output values
    will often be close to 0 or 1.  Also computes usable input error gradients, even though their
    absolute values differ from what's computed by the native implementation.  Does not support vector
    argument values.  Called "classic" since it was developed with TF1 graphs and sessions and has only
    been partially converted to the new TF2 eager computation API.
    """

    dtype = tf.float32
    learningRate = 0.75
    momentum = 0.25
    oneOverPi = 1.0 / math.pi
    piOverTwo = math.pi / 2.0

    def __init__(self, chamNet):
        self.chamNet = chamNet    # `chamNet's `model' slot points to `self'
        self.inputValues = None
        self.batchSize = 1
        self.tfModel = None
        self.tfSession = None
        self.tfOps = []

    def getWeightsInit(self):
        return tf.initializers.RandomUniform(minval=-plogic.oWEIGHT_RANGEo, maxval=plogic.oWEIGHT_RANGEo)

    def getComponent(self, name):
        """Return the model component with `name' or None."""
        return self.tfModel.get(name)

    def getVariable(self, name):
        """Get the graph variable with `name'."""
        # this is a bit tedious, we just keep it for reference:
        name = name + ':'
        for var in self.getComponent('graph').get_collection_ref('variables'):
            if var.name.startswith(name):
                return var
        return None

    def queueOps(self, op):
        if isinstance(op, list):
            self.tfOps += op
        else:
            self.tfOps.append(op)

    def runOps(self, op=None):
        """Runs `op'(s) and any currently queued ops nondeterministically.
        Return the result of `op' or from the last one in the queued list.
        """
        result = None
        if op is not None:
            self.queueOps(op)
        if len(self.tfOps) > 0:
            result = self.tfSession.run(self.tfOps)[-1]
        self.tfOps = []
        return result

    def allocateNetworkArrays(self, numIn, numHidden, numOut):
        graph = tf.Graph()
        if self.tfSession is not None:
            self.tfSession.close()
        self.tfSession = tf.compat.v1.Session(graph=graph)
        with graph.as_default():
            # Basic model structure (input and target are set via assign ops):
            input = tf.Variable(name='input', dtype=self.dtype, initial_value=tf.zeros(shape=[1, numIn], dtype=self.dtype), trainable=False)
            ihWeights = tf.Variable(name='ihWeights', dtype=self.dtype, initial_value=self.getWeightsInit()(shape=[numIn, numHidden], dtype=self.dtype))
            # we are not taking care of any bias here, that's handled by the extra input unit just like the native impl for now:
            hidden = (tf.math.atan(tf.matmul(input, ihWeights)) + self.piOverTwo) * self.oneOverPi
            hoWeights = tf.Variable(name='hoWeights', dtype=self.dtype, initial_value=self.getWeightsInit()(shape=[numHidden, numOut], dtype=self.dtype))
            output = (tf.math.atan(tf.matmul(hidden, hoWeights)) + self.piOverTwo) * self.oneOverPi 

            # Error:
            target = tf.Variable(name='target', dtype=self.dtype, initial_value=tf.zeros(shape=[1, numOut], dtype=self.dtype), trainable=False)
            loss = abs(target - output) # absolute value needed by optimizer

            # Gradients:
            # Look here for how to possibly rewrite this better: https://www.tensorflow.org/api_docs/python/tf/keras/optimizers/Optimizer
            optimizer = tf.optimizers.SGD(learning_rate=self.learningRate, momentum=self.momentum, name='optimizer')
            updateWeights = optimizer.apply_gradients(list(zip(optimizer.get_gradients(loss, [hoWeights, ihWeights]), [hoWeights, ihWeights])), name='updateWeights')
            inputError = -tf.gradients(ys=loss, xs=[input], name='inputError')[0]  # as with weight updates, we have to flip the sign

            # Update operations:
            # tricky: the assign has to be defined during graph definition time and is then later fed by
            # assigning values to a placeholder, otherwise, the graph grows indefinitely with every assignment:
            inputValues = tf.keras.backend.placeholder(dtype=self.dtype, name='inputValues')
            setInputValues = tf.compat.v1.assign(input, inputValues, name='setInputValues')
            targetValues = tf.keras.backend.placeholder(dtype=self.dtype, name='targetValues')
            setTargetValues = tf.compat.v1.assign(target, targetValues, name='setTargetValues')

            # once we do this, we cannot add ops such as assigns anymore - which is what we want:
            graph.finalize()
            model = {'graph': graph, 'input': input, 'ihWeights': ihWeights, 'hidden': hidden, 'hoWeights': hoWeights,
                     'output': output, 'target': target, 'loss': loss, 'inputError': inputError,
                     'inputValues': inputValues, 'setInputValues': setInputValues,
                     'targetValues': targetValues, 'setTargetValues': setTargetValues,
                     'optimizer': optimizer, 'updateWeights': updateWeights}
            self.tfModel = model

    def randomizeNetworkWeights(self):
        for var in self.tfModel['graph'].get_collection('variables'):
            self.queueOps(var.initializer)
        # ensure all variables are initialized:
        self.runOps()

    def initializeNetworkWeights(self):
        self.randomizeNetworkWeights()

    def buildPropositionNetwork(self, prop):
        #print 'buildPropositionNetwork', prop
        numIgnored = self.chamNet.numberOfIgnoredValueArguments(prop)
        # prop columns includes the predicate:
        numIn = (pli.getColumnCount(prop) - 1) - numIgnored + 1   # add 1 for bias unit
        numHidden = min(numIn, 20)
        numOut = 1
        # for really big input layers:
        if numIn > 100:
            numHidden = int((numIn / 10) + 10)
        self.allocateNetworkArrays(numIn, numHidden, numOut)
        self.randomizeNetworkWeights()
        self.runOps()
        # linking to prop is done on STELLA side

    def numberOfInputs(self):
        #print 'numberOfInputs'
        return int(self.getComponent('input').get_shape()[1]) - 1 # subtract bias unit

    def nthInput(self, n):
        #print 'nthInput'
        inputVar = self.getComponent('input')
        inputVals = self.runOps(inputVar)
        return inputVals[0, n + 1]                                # skip bias unit

    def nthInputError(self, n):
        errors = self.runOps(self.getComponent('inputError'))
        err = errors[0, n + 1] # skip bias unit
        return err

    def setInputValues(self, values):
        vals = [1.0] # bias
        for val in values:
            vals.append(float(val))
        inputValues = self.getComponent('inputValues')
        setInputsOp = self.getComponent('setInputValues')
        self.runOps()
        self.tfSession.run(setInputsOp, feed_dict={inputValues: [vals]})

    def setVectorInputValues(self, vectorSpecs):
        raise Exception('setVectorInputValues: not implemented')

    def getOutput(self):
        outputVar = self.getComponent('output')
        result = self.runOps(outputVar)
        return result[0][0]

    def setTarget(self, value):
        targetValues = self.getComponent('targetValues')
        setTargetsOp = self.getComponent('setTargetValues')
        self.runOps()
        self.tfSession.run(setTargetsOp, feed_dict={targetValues: np.array([[value]])})

    def forwardPropagateInputs(self):
        return self.getOutput()

    def backwardPropagateError(self, error):
        output = self.getOutput()
        self.setTarget(output + error)
        self.runOps()

    def updateNetworkWeights(self, error):
        output = self.getOutput()
        self.setTarget(output + error)
        self.runOps()
        updateOp = self.getComponent('updateWeights')
        self.runOps(updateOp)

_TensorflowNeuralNetwork._implClass = TensorflowNeuralNetworkImplClassic


### TensorflowNeuralNetworkImplEager Optimization notes:
# - replacing PI division with oneOverPi multiplication takes us from 49 secs to 40 secs
# - making `runForwardPropagateInputs' into a @tf.function took us to 39 secs
# - making `runBackwardPropagateError' into a @tf.function took us to 32 secs
# - making `runUpdateNetworkWeights'   into a @tf.function took us to 20 secs
# - compare to `TensorflowNeuralNetworkImplClassic' which takes 18 secs; interestingly, fixing the
#   pi constants and division here does not help, so the graph must optimize that already

class TensorflowNeuralNetworkImplEager(object):
    """Eager pure TF2 implementation of ImplClassic which uses tf.function to implicitly
    generate computation graphs.  This is now very close to the original execution time
    (20secs vs. 18secs) despite the fact that it recomputes various things in the three
    core methods (forward/backward/update).  Profiling didn't reveal any serious issues
    as far as we can see, the next major speedup comes through batching (see below).
    See .old/chameleon_pli_tf2.py.3 for the original eager implementation with a profile.
    This variant now also supports vector argument inputs.
    """

    dtype = tf.float32
    learningRate = 0.75
    momentum = 0.25
    oneOverPi = 1.0 / math.pi
    piOverTwo = math.pi / 2.0

    def __init__(self, chamNet):
        self.chamNet = chamNet    # `chamNet's `model' slot points to `self'
        # we now store model objects directly in slots which makes this look similar to the PowerLoom object:
        self.input = None
        self.inputBuffer = None
        self.inputModifiedP = True
        self.inputError = None
        self.ihWeights = None
        self.hoWeights = None
        self.output = None
        self.target = None
        self.optimizer = None

    def getWeightsInit(self):
        return tf.initializers.RandomUniform(minval=-plogic.oWEIGHT_RANGEo, maxval=plogic.oWEIGHT_RANGEo)

    def allocateNetworkArrays(self, numIn, numHidden, numOut):
        # Basic model structure represented via TF variables:
        self.input = tf.Variable(name='input', dtype=self.dtype, initial_value=tf.zeros(shape=[1, numIn], dtype=self.dtype), trainable=False)
        self.inputBuffer = np.zeros(numIn, asNumpyDtype(self.dtype))
        self.inputError = tf.zeros(shape=[1, numIn], dtype=self.dtype)
        self.ihWeights = tf.Variable(name='ihWeights', dtype=self.dtype, initial_value=tf.zeros(shape=[numIn, numHidden], dtype=self.dtype))
        self.hoWeights = tf.Variable(name='hoWeights', dtype=self.dtype, initial_value=tf.zeros(shape=[numHidden, numOut], dtype=self.dtype))
        self.output = tf.zeros(shape=[1, numOut], dtype=self.dtype)
        self.target = tf.zeros(shape=[1, numOut], dtype=self.dtype)
        self.optimizer = tf.optimizers.SGD(learning_rate=self.learningRate, momentum=self.momentum, name='optimizer')

    def randomizeNetworkWeights(self):
        self.ihWeights.assign(self.getWeightsInit()(shape=self.ihWeights.shape, dtype=self.dtype))
        self.hoWeights.assign(self.getWeightsInit()(shape=self.hoWeights.shape, dtype=self.dtype))

    def initializeNetworkWeights(self):
        #pdb.set_trace()
        savedState = findLoadedNetwork(self, self.chamNet.getNeuralNetworkProposition())
        if savedState is not None:
            model = savedState['model']
            self.ihWeights.assign(model['ihWeights'].value())
            self.hoWeights.assign(model['hoWeights'].value())
        else:
            self.randomizeNetworkWeights()

    def buildPropositionNetwork(self, prop):
        #print 'buildPropositionNetwork', prop
        numIgnored = self.chamNet.numberOfIgnoredValueArguments(prop)
        numVectorIn = self.chamNet.numberOfVectorArgumentInputs(prop)
        # prop columns includes the predicate:
        numIn = (pli.getColumnCount(prop) - 1) + numVectorIn - numIgnored + 1   # add 1 for bias unit
        numHidden = min(numIn, 20)
        numOut = 1
        # for really big input layers:
        if numIn > 100:
            numHidden = int((numIn / 10) + 10)
        self.allocateNetworkArrays(numIn, numHidden, numOut)
        self.initializeNetworkWeights()
        # linking to prop is done on STELLA side

    def numberOfInputs(self):
        #print 'numberOfInputs'
        return int(self.input.shape[1]) - self.chamNet.numberOfVectorArgumentInputs(None) - 1

    def nthInput(self, n):
        #print 'nthInput'
        return self.input[0, n + 1]                               # skip bias unit

    def nthInputError(self, n):
        return self.inputError[0, n + 1]                          # skip bias unit

    def setInputValues(self, values):
        buffer = self.inputBuffer
        buffer[0] = 1.0 # bias
        i = 1
        for val in values:
            buffer[i] = float(val)
            i += 1
        self.inputModifiedP = True

    def setVectorInputValues(self, vectorSpecs):
        #pdb.set_trace()
        buffer = self.inputBuffer
        i = self.numberOfInputs() + 1
        for spec in vectorSpecs:
            for elt in spec:
                if isinstance(elt, pli.LongIntegerWrapper):
                    vector = spi.getPythonObjectFromStellaPointer(elt)
                    vdim = len(vector)
                    buffer[i:i+vdim] = vector
                    i += vdim
                elif isinstance(elt, pli.StringWrapper):
                    elt = str(elt)
                    if isPyEval(elt):
                        vector = pyEval(elt)
                        vdim = len(vector)
                        buffer[i:i+vdim] = vector
                        i += vdim
        self.inputModifiedP = True

    def assignInputValues(self):
        # Since we now have two input value operations, we use a dirty flag to only do the assign when necessary:
        if self.inputModifiedP:
            buffer = self.inputBuffer
            # temporarily change buffer shape to match input variable:
            buffer.shape = (1, buffer.shape[0])
            # IMPORTANT: for this overloaded assignment to a tf.Variable to work, the value has to be a
            # tensor, thus we use tf.constant here, alternatively, we could also use tf.convert_to_tensor:
            self.input.assign(tf.constant(buffer, dtype=self.dtype))
            buffer.shape = (buffer.shape[1],)
            self.inputModifiedP = False

    def getOutput(self):
        return self.output[0][0]

    # in the run... tf.function's below passing `input' and/or `target' was crucial to avoid
    # retracing or to make the gradients computation work; we also can't have side effects
    # such as "leaking out a graph tensor" via `self.output = ....' for example, thus we return
    # those tensors now where necessary and handle the assignment in the callers.

    @tf.function
    def runForwardPropagateInputs(self):
        # we are not taking care of any bias here, that's handled by the extra input unit just like the native impl for now:
        hidden = (tf.math.atan(tf.matmul(self.input, self.ihWeights)) + self.piOverTwo) * self.oneOverPi
        output = (tf.math.atan(tf.matmul(hidden, self.hoWeights)) + self.piOverTwo) * self.oneOverPi
        return output

    def forwardPropagateInputs(self):
        # this side effect we can't have inside the tf.function, thus the separation:
        self.assignInputValues()
        self.output = self.runForwardPropagateInputs()
        return self.getOutput()

    @tf.function
    def runBackwardPropagateError(self, input, target):
        with tf.GradientTape() as tape:
            tape.watch(input)
            hidden = (tf.math.atan(tf.matmul(input, self.ihWeights)) + self.piOverTwo) * self.oneOverPi
            output = (tf.math.atan(tf.matmul(hidden, self.hoWeights)) + self.piOverTwo) * self.oneOverPi
            loss = abs(target - output)      # absolute value needed by optimizer
        inputError = -tape.gradient(loss, input)
        return inputError

    def backwardPropagateError(self, error):
        # IMPORTANT: target has to be unwatched and independent from output, otherwise we get zero gradients:
        self.assignInputValues()
        self.target = self.output + error
        self.inputError = self.runBackwardPropagateError(self.input, self.target)

    @tf.function
    def runUpdateNetworkWeights(self, input, target):
        with tf.GradientTape() as tape:
            hidden = (tf.math.atan(tf.matmul(input, self.ihWeights)) + self.piOverTwo) * self.oneOverPi
            output = (tf.math.atan(tf.matmul(hidden, self.hoWeights)) + self.piOverTwo) * self.oneOverPi
            loss = abs(target - output)      # absolute value needed by optimizer
        weightVars = [self.hoWeights, self.ihWeights]
        grads = tape.gradient(loss, weightVars)
        gradsAndVars = list(zip(grads, weightVars))
        self.optimizer.apply_gradients(gradsAndVars)
        
    def updateNetworkWeights(self, error):
        # IMPORTANT: target has to be unwatched and independent from output, otherwise we get zero gradients:
        self.assignInputValues()
        self.target = self.output + error
        self.runUpdateNetworkWeights(self.input, self.target)

_TensorflowNeuralNetwork._implClass = TensorflowNeuralNetworkImplEager


### Tensorflow batch implementation

# Experiments:
# it looks like we can simply extend the primary dimension for inputs and outputs from 1 to N,
# and we use None as the first dimension on variables so that we can assign different shapes:

"""
>>> m = cpi.TensorflowNeuralNetworkImplEager(None)
>>> m.allocateNetworkArrays(3, 3, 1)
>>> m.randomizeNetworkWeights()

# this is the only difference it seems, where we specify 'None' as the first dimension of the input variable:
>>> m.input = tf.Variable(name='input', shape=[None, 3], dtype=tf.float32, initial_value=tf.zeros(shape=[1, 3], dtype=tf.float32))

# here we assign an input batch of size 5:
>>> m.input.assign(tf.constant([[1.0, 0.8, 0.8], [1.0, 0.5, 0.9], [1.0, 0.5, 0.8], [1.0, 0.6, 0.9], [1.0, 0.7, 0.4]], dtype=tf.float32))
<tf.Variable 'UnreadVariable' shape=(None, 3) dtype=float32, numpy=
array([[1. , 0.8, 0.8],
       [1. , 0.5, 0.9],
       [1. , 0.5, 0.8],
       [1. , 0.6, 0.9],
       [1. , 0.7, 0.4]], dtype=float32)>

# this generates 5 outputs respectively:
>>> m.runForwardPropagateInputs()
<tf.Tensor: id=206, shape=(5, 1), dtype=float32, numpy=
array([[0.48336402],
       [0.48331514],
       [0.48331222],
       [0.48333243],
       [0.4833349 ]], dtype=float32)>

# this generates 5 sets of input errors:
>>> m.runBackwardPropagateError(m.input, tf.ones(shape=[5, 1], dtype=tf.float32))
<tf.Tensor: id=266, shape=(5, 3), dtype=float32, numpy=
array([[2.5199360e-04, 1.7265367e-04, 2.9437762e-05],
       [2.5211740e-04, 1.7276996e-04, 2.9514102e-05],
       [2.5211662e-04, 1.7280639e-04, 2.9557734e-05],
       [2.5207739e-04, 1.7271921e-04, 2.9474159e-05],
       [2.5201213e-04, 1.7284753e-04, 2.9665393e-05]], dtype=float32)>
>>> 
"""

"""
# copying arrays natively back and forth between cffi and np using Python's buffer API:
# see here for some inspiration:
# - https://stackoverflow.com/questions/16276268/how-to-pass-a-numpy-array-into-a-cffi-function-and-how-to-get-one-back-out#16290289

>>> spi.defmethod('stella/1D-FLOAT-ARRAY.the-array-reader') # maybe move into stellapi

>>> spi.defclass('logic/chameleon-neural-network')
>>> spi.defconstructor('logic/chameleon-neural-network')
>>> spi.defslot('logic/chameleon-neural-network.input')
>>> spi.defmethod('logic/chameleon-neural-network.allocate-network-arrays')

>>> nn = spi.logic.pdef.ChameleonNeuralNetwork()
>>> nn.allocateNetworkArrays(3, 3, 1)

>>> nn.input
<proxy.oneDFloatArray |i|@1D-FLOAT-ARRAY>
>>> nn.input.theArrayReader()
<cdata 'void *' 0x55a14b6ecbc0>

>>> ffi = spi.FFI
>>> fa = spi.FFI.cast('double*', nn.input.theArrayReader())
>>> (fa[0], fa[1], fa[2])
(4.65168950262983e-310, 2.5928570173463893e-307, 0.0)

# copying numpy array content to chameleon array (dtype has to match):
>>> spi.FFI.memmove(fa, spi.FFI.from_buffer(np.ones(3, dtype=np.float64)), 3 * 8)
>>> (fa[0], fa[1], fa[2])
(1.0, 1.0, 1.0)

# creating a numpy array from chameleon array content (dtype has to match):
>>> np.frombuffer(spi.FFI.buffer(fa, 3 * 8), dtype=np.float64)
array([1., 1., 1.])

# we don't need the cast unless we want to use a[] syntax in Python for the array:
>>> nn.allocateNetworkArrays(3, 3, 1)
>>> lfa = nn.input.theArrayReader()

>>> np.frombuffer(spi.FFI.buffer(lfa, 3 * 8), dtype=np.float64)
array([4.65168950e-310, 3.42127868e+180, 1.47206859e-319])

>>> spi.FFI.memmove(lfa, spi.FFI.from_buffer(np.ones(3, dtype=np.float64)), 3 * 8)
>>> lfa = spi.FFI.cast('double*', lfa)
>>> (lfa[0], lfa[1], lfa[2])
(1.0, 1.0, 1.0)

# we might need additional numpy ops to adjust the element datatype and array shape,
# e.g., np.float32(<array>), np.float64(<array>) which will cause some loss when going to 32 bit
"""

@spi.FFI.callback("void*(void*)")
def tfCallbackBatchForwardPropagateInputs(net):
    netClass = spi.lookupStellaTypeProxyClass(spi.boot.primaryClass(net))
    net = netClass(_stobj=net)
    return net._getModel().batchForwardPropagateInputs()._stellaObject
plogic.registerTensorflowCallback('tensorflow-batch-neural-network.batch-forward-propagate-inputs', tfCallbackBatchForwardPropagateInputs)

@spi.FFI.callback("void(void*)")
def tfCallbackBatchBackwardPropagateError(net):
    netClass = spi.lookupStellaTypeProxyClass(spi.boot.primaryClass(net))
    net = netClass(_stobj=net)
    net._getModel().batchBackwardPropagateError()
plogic.registerTensorflowCallback('tensorflow-batch-neural-network.batch-backward-propagate-error', tfCallbackBatchBackwardPropagateError)

@spi.FFI.callback("void(void*)")
def tfCallbackBatchUpdateNetworkWeights(net):
    netClass = spi.lookupStellaTypeProxyClass(spi.boot.primaryClass(net))
    net = netClass(_stobj=net)
    net._getModel().batchUpdateNetworkWeights()
plogic.registerTensorflowCallback('tensorflow-batch-neural-network.batch-update-network-weights', tfCallbackBatchUpdateNetworkWeights)


@spi.logic.pdef
class _TensorflowBatchNeuralNetwork(spi.ProxyClass):
    _stellaTypePath = "/LOGIC/@TENSORFLOW-BATCH-NEURAL-NETWORK"

spi.defslot('logic/TENSORFLOW-BATCH-NEURAL-NETWORK.input-modified?')
spi.defslot('logic/TENSORFLOW-BATCH-NEURAL-NETWORK.input-batch')
spi.defslot('logic/TENSORFLOW-BATCH-NEURAL-NETWORK.input-batch-length')
spi.defslot('logic/TENSORFLOW-BATCH-NEURAL-NETWORK.vector-batch')
spi.defslot('logic/TENSORFLOW-BATCH-NEURAL-NETWORK.vector-batch-length')
spi.defslot('logic/TENSORFLOW-BATCH-NEURAL-NETWORK.target-batch')
spi.defslot('logic/TENSORFLOW-BATCH-NEURAL-NETWORK.output-batch')
spi.defslot('logic/TENSORFLOW-BATCH-NEURAL-NETWORK.input-error-batch')
spi.defmethod('logic/TENSORFLOW-BATCH-NEURAL-NETWORK.print-network-arrays')

# possibly move these into stellapi.py:
spi.defmethod('stella/1D-FLOAT-ARRAY.the-array-reader')
spi.defmethod('stella/2D-FLOAT-ARRAY.the-array-reader')
spi.defmethod('logic/2D-LONG-ARRAY.the-array-reader')


# TensorflowBatchNeuralNetworkImplEager optimization notes:
# - we are now faster as expected by about a factor of 5 compared to non-batch TF using 5 training examples,
#   however, compared to straight eager Chameleon we are still about 25x slower, even with 2750 training examples
#   (5000 epochs take 31secs vs. 794secs elapsed time)
# - with 2500 examples, batch size 1024 and using the concrete function approach where we only convert the
#   the function to a graph once, we get to a factor 3.6x slower (with an effective avg. batch size of 835)
# - going to 2048 buffer size saves us another 10% or so, so we are getting to the end of the rope here
# - going to 128 buffer size is 2.5x slower than with 1024
# - using a batch size of 1 on 2500 examples is about 75x slower than using batch size 1024
# - we might be able to squeeze some more performance out of readInputBatch, but nothing dramatic at this point,
#   according to the cProfile, it is the most expensive individual function, but it only takes about 18% of the
#   time spent on TensorFlow computations, so not a whole lot of headroom there
# - TO DO: fold the concrete function approach into the non-batch network as well, since we still rely on that
#   for incremental forward propagation during cached proof generation

class TensorflowBatchNeuralNetworkImplEager(TensorflowNeuralNetworkImplEager):
    """Eager pure TF 2 implementation of ImplClassic that supports batch computations.
    This now uses `tf.function(<nnfn>).get_concrete_function to generate per-NN forward/
    backward/update functions which avoids their recomputation and/or rechecking.
    Instead of processing one input at a time, we now process batches and copy them
    and corresponding results back and forth to STELLA in bulk.  A batchsize of 1024
    on 2500 training examples is 75x faster than using a batchsize of 1 for the same.
    We are still slower than the native Chameleon implementation by a factor of 3-4,
    but that disadvantage should vanish with larger networks (e.g., due to embeddings)
    as well as by using GPU processing.
    This variant now also supports vector argument inputs.
    """
    
    dtype = tf.float64      # change the default to avoid extra conversion and copying
    learningRate = 0.25     # we need different/lower learning rates here for our test example, not quite sure why
    momentum = 0.25

    def __init__(self, *args, **kwargs):
        super(TensorflowBatchNeuralNetworkImplEager, self).__init__(*args, **kwargs)
        self.runForwardFunction = None
        self.runBackwardFunction = None
        self.runUpdateFunction = None

    def allocateNetworkArrays(self, numIn, numHidden, numOut):
        # this is still needed for non-batch forward propagation during cached proof generation:
        self.input = tf.Variable(name='input',  shape=[None, numIn], dtype=self.dtype,
                                 initial_value=tf.zeros(shape=[1, numIn], dtype=self.dtype), trainable=False)
        self.inputBuffer = np.zeros(numIn, asNumpyDtype(self.dtype))
        self.inputBatch = None
        self.vectorBatch = None
        self.ihWeights = tf.Variable(name='ihWeights', dtype=self.dtype, initial_value=tf.zeros(shape=[numIn, numHidden], dtype=self.dtype))
        self.hoWeights = tf.Variable(name='hoWeights', dtype=self.dtype, initial_value=tf.zeros(shape=[numHidden, numOut], dtype=self.dtype))
        self.target = tf.zeros(shape=[1, numOut], dtype=self.dtype)
        # output variables, we just initialize them here for documentation, they will be overwritten once the NN is run:
        self.output = tf.zeros(shape=[1, numOut], dtype=self.dtype)
        self.inputError = tf.zeros(shape=[1, numIn], dtype=self.dtype)
        self.optimizer = tf.optimizers.SGD(learning_rate=self.learningRate, momentum=self.momentum, name='optimizer')

    def readInputBatch(self):
        """Read STELLA input and target value batch arrays into local copies that will be fed to tensorflow.
        Only read something if there were any modifications on the STELLA side since the last call to this method.
        """
        # this takes about 30% of the overall run time, so improving this part would be significant, the question is how:
        nn = self.chamNet
        if nn.inputModifiedP:
            batchLength = nn.inputBatchLength
            nInputs = self.numberOfInputs() + 1
            # this is the STELLA array:
            inputBatchArray = nn.inputBatch.theArrayReader()
            # now do a fast byte-level buffer copy into a numpy array and then reshape it to make it look right:
            inputBatch = np.frombuffer(spi.FFI.buffer(inputBatchArray, batchLength * nInputs * stellaFloatSize), dtype=asNumpyDtype(self.dtype))
            inputBatch.shape = (batchLength, nInputs)
            
            if nn.vectorBatchLength > 0:
                # retrieve the pointers of the vectors we need to use:
                nVectorSpecs = nn.numberOfVectorArgumentSpecs(None)
                vectorBatchArray = nn.vectorBatch.theArrayReader()
                vectorBatch = np.frombuffer(spi.FFI.buffer(vectorBatchArray, batchLength * nVectorSpecs * stellaLongSize), dtype=np.long)
                # after reshaping, each row in the batch contains 1 or more vector pointers, each identifying an N-dimensional vector:
                vectorBatch.shape = (batchLength, nVectorSpecs)

                # first, assign truth-value inputs to the left side of each input vector batch row:
                self.inputBatch = np.zeros([batchLength, self.input.get_shape()[1]], dtype=asNumpyDtype(self.dtype)) 
                self.inputBatch[:,0:nInputs] = inputBatch
                
                # second, concatenate vectors indexed by each elt in the vector batch to the right side of truth-valued inputs:
                for b in range(batchLength):
                    offset = nInputs
                    for vix in vectorBatch[b]:
                        vec = spi.getPythonObjectFromStellaPointerId(vix)
                        vdim = len(vec)
                        self.inputBatch[b:,offset:offset+vdim] = vec
                        offset += vdim
                """
                # here is an alternative way without iteration - the magic is in the apply_along_axis on an array with single-element rows,
                # however, it is actually slower than what we do above, possibly because it copies the vectors before assigning them:
                vectorBatch.shape = (vectorBatch.size, 1)
                vectors = np.apply_along_axis(lambda x: spi.getPythonObjectFromStellaPointerId(x[0]), 1, vectorBatch)
                vectors.shape = (batchLength, vectors.size / batchLength)
                # now we assign to the right-column slice of the batch - similar to what we did for truth-value inputs above:
                self.inputBatch[:,nInputs:] = vectors
                """
            else:
                self.inputBatch = inputBatch
            
            targetBatchArray = nn.targetBatch.theArrayReader()
            self.target = np.frombuffer(spi.FFI.buffer(targetBatchArray, batchLength * stellaFloatSize), dtype=np.float64)
            self.target.shape = (batchLength, 1)  # reshape without copying
            
            # convert datatype if necessary:
            if self.dtype == tf.float32:
                self.inputBatch = self.inputBatch.astype(np.float32, copy=False)
                self.target = self.target.astype(np.float32, copy=False)
            nn.inputModifiedP = False

    def writeOutputBatch(self):
        """Write tensorflow output to corresponding STELLA output batch array and return the STELLA array.
        """
        nn = self.chamNet
        batchLength = nn.inputBatchLength
        outputBatch = nn.outputBatch
        outputBatchArray = outputBatch.theArrayReader()
        # this copies, investigate Python's `memoryview()' to see if we can avoid copying:
        tfOutput = self.output.numpy()
        if self.dtype == tf.float32:
            # this should convert in-place on the copy created above:
            tfOutput = tfOutput.astype(np.float64, copy=False)
        # copy values back into the STELLA-side ouput batch float array:
        spi.FFI.memmove(outputBatchArray, spi.FFI.from_buffer(tfOutput), batchLength * stellaFloatSize)
        # this returns a proxy FLOAT-ARRAY, unwrapping to native object is done in the callback:
        return outputBatch

    def writeInputErrorBatch(self):
        """Write tensorflow input errors to corresponding STELLA batch array and return the STELLA array.
        """
        nn = self.chamNet
        batchLength = nn.inputBatchLength
        inputErrorBatch = nn.inputErrorBatch
        inputErrorBatchArray = inputErrorBatch.theArrayReader()
        # this copies, investigate `memoryview' to see if we can avoid copying:
        tfInputError = self.inputError.numpy()
        numVectorIn = nn.numberOfVectorArgumentInputs(None)
        if numVectorIn > 0:
            # we need to slice off the vector argument errors before passing back,
            # unfortunately, we have to copy so we can change to a linear shape below:
            nInputs = self.numberOfInputs() + 1
            tfInputError = np.array(tfInputError[:,:nInputs], dtype=tfInputError.dtype)
        # reshape to 1-D array:
        tfInputError.shape = (tfInputError.size,)
        if self.dtype == tf.float32:
            # this should convert in-place on the copy created above:
            tfInputError = tfInputError.astype(np.float64, copy=False)
        # copy values back into the STELLA-side ouput batch float array:
        spi.FFI.memmove(inputErrorBatchArray, spi.FFI.from_buffer(tfInputError), tfInputError.size * stellaFloatSize)
        # this returns a proxy FLOAT-ARRAY:
        return inputErrorBatch

    
    def runForwardPropagateInputsTemplate(self, input):
        # we are not taking care of any bias here, that's handled by the extra input unit just like the native impl for now:
        hidden = (tf.math.atan(tf.matmul(input, self.ihWeights)) + self.piOverTwo) * self.oneOverPi
        output = (tf.math.atan(tf.matmul(hidden, self.hoWeights)) + self.piOverTwo) * self.oneOverPi
        return output

    def getRunForwardFunction(self):
        # Creating a callable graph function this way just once per NN instead of using a @tf.function annotation
        # speeds us up significantly, since it avoids expensive calls to `maybe_define_function' on every invocation.
        # Important: this has to be run after various referenced self.xxx variables have been initialized.
        if self.runForwardFunction is None:
            self.runForwardFunction = tf.function(self.runForwardPropagateInputsTemplate).get_concrete_function(tf.TensorSpec(shape=[None, None], dtype=self.dtype))
        return self.runForwardFunction

    def batchForwardPropagateInputs(self):
        self.readInputBatch()
        self.output = self.getRunForwardFunction()(tf.constant(self.inputBatch, dtype=self.dtype))
        output = self.writeOutputBatch()
        return output

    
    def runBackwardPropagateErrorTemplate(self, input, target):
        with tf.GradientTape() as tape:
            tape.watch(input)
            hidden = (tf.math.atan(tf.matmul(input, self.ihWeights)) + self.piOverTwo) * self.oneOverPi
            output = (tf.math.atan(tf.matmul(hidden, self.hoWeights)) + self.piOverTwo) * self.oneOverPi
            loss = abs(target - output)      # absolute value needed by optimizer
        inputError = -tape.gradient(loss, input)
        return inputError

    def getRunBackwardFunction(self):
        if self.runBackwardFunction is None:
            self.runBackwardFunction = tf.function(self.runBackwardPropagateErrorTemplate).get_concrete_function(
                tf.TensorSpec(shape=[None, None], dtype=self.dtype),
                tf.TensorSpec(shape=[None, None], dtype=self.dtype))
        return self.runBackwardFunction

    def batchBackwardPropagateError(self):
        self.readInputBatch()
        self.inputError = self.getRunBackwardFunction()(tf.constant(self.inputBatch, dtype=self.dtype),
                                                        tf.constant(self.target, dtype=self.dtype))
        self.writeInputErrorBatch()


    def runUpdateNetworkWeightsTemplate(self, input, target):
        with tf.GradientTape() as tape:
            hidden = (tf.math.atan(tf.matmul(input, self.ihWeights)) + self.piOverTwo) * self.oneOverPi
            output = (tf.math.atan(tf.matmul(hidden, self.hoWeights)) + self.piOverTwo) * self.oneOverPi
            loss = abs(target - output)      # absolute value needed by optimizer
        weightVars = [self.hoWeights, self.ihWeights]
        grads = tape.gradient(loss, weightVars)
        gradsAndVars = list(zip(grads, weightVars))
        self.optimizer.apply_gradients(gradsAndVars)

    def getRunUpdateFunction(self):
        if self.runUpdateFunction is None:
            self.runUpdateFunction = tf.function(self.runUpdateNetworkWeightsTemplate).get_concrete_function(
                tf.TensorSpec(shape=[None, None], dtype=self.dtype),
                tf.TensorSpec(shape=[None, None], dtype=self.dtype))
        return self.runUpdateFunction

    def batchUpdateNetworkWeights(self):
        self.readInputBatch()
        self.getRunUpdateFunction()(tf.constant(self.inputBatch, dtype=self.dtype),
                                    tf.constant(self.target, dtype=self.dtype))
        
_TensorflowBatchNeuralNetwork._implClass = TensorflowBatchNeuralNetworkImplEager


### Save/Restore

spi.defglobal('logic/*all-neural-networks*')
spi.defmethod('logic/tensorflow-neural-network.get-neural-network-proposition')
spi.defun('logic/generate-expression')
spi.defglobal('logic/*queryIterator*')

def getPropositionKey(prop):
    with prop.homeModule() as mod:
        currentQuery = pli.plogic.oQUERYITERATORo
        try:
            # we need to set this to NULL to not get variable bindings in the proposition key:
            pli.plogic.oQUERYITERATORo = None
            term = pli.plogic.generateExpression(prop, True)
            return (pli.getName(mod), pli.objectToString(term))
        finally:
            pli.plogic.oQUERYITERATORo = currentQuery

def createSaveNetworkInfo(chamNet):
    prop = chamNet.getNeuralNetworkProposition()
    module = prop.homeModule()
    model = chamNet._getModel()
    with pli.getExistingModule(module) as mod:
        return {'chameleonType': pli.getStellaTypeName(chamNet),
                'proposition': {'form': pli.objectToString(prop),
                                'module': pli.getName(module),
                                'key': getPropositionKey(prop),
                                },
                'model': {'type': type(model),
                          'ihWeights': model.ihWeights,
                          'hoWeights': model.hoWeights,
                          },
                }

def saveAllNetworks(file):
    networkInfos = {}
    for index, bucket in pli.plogic.oALL_NEURAL_NETWORKSo.consify().tree():
        i = 0
        for cnn in bucket:
            if isinstance(cnn, pli.plogic.TensorflowNeuralNetwork):
                netInfo = createSaveNetworkInfo(cnn)
                networkInfos[netInfo['proposition']['key']] = netInfo
                i += 1
            if i >= 2:
                break
    with open(file, 'wb') as out:
        pickle.dump(networkInfos, out)

loadedNetworks = {}

def loadNetworks(file):
    """Load all saved network infos from `file' and append them to the currently loaded
    network buckets (if any) indexed by their proposition index.  This means the most
    recently loaded networks will be at the end of each proposition bucket.
    """
    if not os.path.exists(file):
        file = pli.findFileInLoadPath(file) or file
    with open(file, 'rb') as inp:
        networks = pickle.load(inp)
    for key, netInfo in networks.items():
        loadedNetworks[key] = netInfo

def findLoadedNetwork(model, prop):
    with prop.homeModule() as mod:
        propKey = getPropositionKey(prop)
        netInfo = loadedNetworks.get(propKey)
        # TO DO: possibly we also have to test for true proposition equivalence here:
        if (netInfo is not None
            and netInfo['proposition']['key'] == propKey
            and netInfo['model']['type'] == type(model)
            and netInfo['proposition']['module'] == pli.getName(mod)):
            return netInfo
    return None


### Python computations that produce vectors

# For now we have two variants to produce vector arguments:
# (1) via python evaluation directives that come to the tensorflow side via string arguments, for example:
#         #!python -m __main__ -c getPersonEmbedding('"'Fred'"')
# (2) via long integer wrappers produced by computation functions such as cham/word-embedding below,
#     which are pointers to actual numpy vectors (or views), for example,
#         (cham/word-embedding "Fred" ?e)  which will bind ?e/93982357044312 (or similar)
# Both variants are passed as elements to vector argument specs generated on the STELLA side

pyEvalPrefix = "#!python"

pyEvalParser = argparse.ArgumentParser()
pyEvalParser.add_argument("-m", "--module", default="__main__", help="the module relative to which to evaluate the expression")
pyEvalParser.add_argument("-c", "--command", nargs='+', help="the Python expression to evaluate")

def pyEvalError(*args, **kwargs):
    raise Exception('pyEval: illegal syntax')

pyEvalParser.exit = pyEvalError

def isPyEval(x):
    """Return True if `x' is a Python expression that should be evaluated."""
    return isinstance(x, basestring) and x.startswith(pyEvalPrefix)

def pyEvalGetModule(moduleRef):
    """Access the Python module specified by `moduleRef' which either has to be a global
    name such as "sys" or "__main__" or an alias visible in the "__main__" module.
    """
    module = sys.modules.get(moduleRef)
    if module is None:
        module = sys.modules['__main__']
        module = getattr(module, moduleRef, None)
    if module is None:
        raise Exception('pyEval: cannot find module with name ' + moduleRef)
    return module

def pyEval(evalSpec):
    """Evaluate the command specified by `evalSpec' and return the result.  Quoting has to be
    done as on the shell command line, even though this is not run through the shell.
    """
    if isPyEval(evalSpec):
        evalArgs = shlex.split(evalSpec[len(pyEvalPrefix):])
        evalArgs = pyEvalParser.parse_args(evalArgs)
        module = pyEvalGetModule(evalArgs.module)
        return eval(' '.join(evalArgs.command), module.__dict__)
    else:
        raise Exception('pyEval: illegal eval spec: ' + evalSpec)

# Examples:
# >>> cpi.pyEval("""#!python -c pyEvalPrefix -m cpi""")
# '#!python'
# >>> cpi.pyEval("""#!python -c '"'Hans'"'.upper()""")
# 'HANS'
# >>> cpi.pyEval("""#!python -c '"'Hans and Franz'"'.upper()""")
# 'HANS AND FRANZ'
# >>> 

@pli.computation(function='cham/word-embedding', module='PL-KERNEL-KB', create=True, defer=True)
def wordEmbeddingComputation(word):
    """Test computation that generates word2vec embeddings based on the configured model.
    """
    import word2vec as w2v
    m = w2v.getDefaultModel()
    word = str(word)
    # we use the vector of the least frequent word as a default value:
    index = (m.vocab.get(word) or m.vocab.get(m.index2word[-1])).index
    # TRICKY: the `m.vectors[index]' call below is creating new array view objects on every call (even though the
    # underlying array data is not copied), thus we would get a different python object id and reference everytime;
    # to work around that we use `index' to get the reference but then replace it with its view in its pointer entry:
    entry = spi.getPythonObjectStellaPointer(index, fullEntry=True)
    if entry[0] is index:
        # store the view which will be returned by future calls to spi.getPythonObjectFromStellaPointer(entry[1]):
        entry[0] = m.vectors[index]
    return entry[1]

spi.defun('logic/description-mode?')
maxOneHotVectorLength = 100

@lru_cache(maxsize=1000)
def getOneHotVectorTypeIndex(type, module=None, context=None):
    instList = list(pli.getInferredBinaryPropositionValues('holds', type, module=module))
    if len(instList) > maxOneHotVectorLength:
        return None
    instList.sort(key=str)
    instIndex = {}
    for inst, i in zip(instList, range(len(instList))):
        instIndex[inst] = i
    return instIndex

@pli.computation(function='cham/one-hot-vector', module='PL-KERNEL-KB', create=True, defer=True)
def oneHotVectorComputation(instance, type):
    """Test computation that generates a one-hot vector for `instance' which is assumed to be of `type',
    that is, querying for `type' will generate all relevant instances we need to represent.
    """
    # don't evaluate this while we build the query description, since that is run in a different context
    # which will then bind the variable to a different pointer which in turn will make the query fail:
    if pli.plogic.descriptionModeP():
        return None
    vector = None
    instIndex = getOneHotVectorTypeIndex(type, pli.getCurrentModule(), spi.stella.pdef.oCONTEXTo)
    if instIndex is not None:
        vector = instIndex.get(instance)
        if vector is not None:
            if isinstance(vector, int):
                # first time accessed, we need to create the vector:
                index = vector
                vector = np.zeros(len(instIndex))
                vector[index] = 1.0
                instIndex[instance] = vector
            vector = spi.getPythonObjectStellaPointer(vector)
    return vector

pli.processDeferredCommands()

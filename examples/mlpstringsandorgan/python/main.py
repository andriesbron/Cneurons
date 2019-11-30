#!/usr/bin/env python3
import os
import math
import time

#! External dependencies for neural networks
import numpy
from sklearn.linear_model import Perceptron

#! @todo use this for an next project
from sklearn.neural_network import MLPClassifier

#! External dependencies of cneurons to derive features
from cneurons import featureextractor

#! External dependencies of cneurons to create c files
from cneurons import ccreator

fe = featureextractor.featureextractor() #! A bookkeeper for the features

strings = fe.load_sounds_from_folders (['sounds/trainingstrings'])
cathedral = fe.load_sounds_from_folders (['sounds/trainingcathedral'])
maxlag = 4 #! Max sample shift for autocorrelation

print ("# cneurons: Sounds loaded.")
print ("# cneurons: Example features:")
print ("- Strings", fe.getFeaturesByAutocorrelation (strings[0], maxlag))
print ("- Cathedral", fe.getFeaturesByAutocorrelation (cathedral[0], maxlag))

#fe.exit("Exitting to check autocorrelation.")
#! @todo A better approach might be to be just picky on a single shift value rather than the whole sum of shifts. Echo's in sound might also be an issue.
#! @todo E.g.: only pick the third or the 3rd and the 7th etcetera. Should make a training to correlate the correlation...
print ("# cneurons: Try adjusting maxLag to 2 and 3 and see that there is not much difference, 4 is a minimum, not a great minimum.")
print ("- Strings", fe.autocorrelate (strings[0], maxlag))
print ("- Cathedral", fe.autocorrelate (cathedral[0], maxlag))

for sample in strings:
        fe.addFeature (fe.getFeaturesByAutocorrelation (sample, maxlag), 1)
        
for sample in cathedral:
        fe.addFeature (fe.getFeaturesByAutocorrelation (sample, maxlag), 0)

print ("# cneurons: Training the perceptron...")

#! See also
#! https://www.python-course.eu/neural_networks_with_scikit.php
'''
p = Perceptron(random_state=42,
              max_iter=30,
              tol=fe.getTrainingAccuracy("perceptron"))

p.fit(fe.getFeatures()['features'], fe.getFeatures()['outputs'])
'''
# https://www.python-course.eu/neural_networks_with_scikit.php
#! Proefje met mlp

#X = [[0., 0.], [1., 1.]]
#y = [0, 1]

clf = MLPClassifier(solver='lbfgs', alpha=1e-5,
                    hidden_layer_sizes=(5, 2), random_state=1)

#clf.fit(X, y)
             
clf.fit(fe.getFeatures()['features'], fe.getFeatures()['output'])

MLPClassifier(activation='relu', alpha=1e-05, batch_size='auto',
              beta_1=0.9, beta_2=0.999, early_stopping=False,
              epsilon=1e-08, hidden_layer_sizes=(5, 2),
              learning_rate='constant', learning_rate_init=0.001,
              max_iter=200, momentum=0.9, n_iter_no_change=10,
              nesterovs_momentum=True, power_t=0.5, random_state=1,
              shuffle=True, solver='lbfgs', tol=0.0001,
              validation_fraction=0.1, verbose=False, warm_start=False)

print ([coef.shape for coef in clf.coefs_])
print(clf.coefs_)


print ("# cneurons: Predicting a training set to demostrate the perceptron...")
print("# cneurons: Predicting strings:\nResult: ", str(p.predict([fe.getFeatures()['features'][0]])))
print("# cneurons: Predicting cathedral:\nResult: ", str(p.predict([fe.getFeatures()['features'][len(fe.getFeatures()['features'])-1]])))

print ("# cneurons: Perceptron coefficients:")
print (p.coef_)
print("# cneurons: Perceptron intercept:")
print (p.intercept_)
print ("# cneurons: Analyzing a file with combinations of strings and cathedral sounds...")

fe.exit()

soundarray, sr = fe.load_sound_file("sounds/soundsfortest/stringorgansound.wav")
maxseconds = int(len(soundarray)/sr)
trainFileDuration = 0.1
for second in range(maxseconds-1):
    audiosample = numpy.array(soundarray[second*sr:int ((second+trainFileDuration)*sr)])
    verifysamples = fe.getFeaturesByAutocorrelation (audiosample, maxlag)
    pred = p.predict([verifysamples])
    print (second, pred)

#! Now create C file to test the model.
#! Create c file objects for exporting
ccstrings = ccreator.ccreator("stringssample", "../generatedfiles/")
cccathedral = ccreator.ccreator("cathedralsample", "../generatedfiles/")

ccperpectron = ccreator.ccreator("stringcathedralperceptron", "../generatedfiles/")

ccstrings.addIVar ({"name":"ff_stringssamples",
            "type":"float",
            "data":list(strings[0])
            })

cccathedral.addIVar ({"name":"ff_cathedralsamples",
            "type":"float",
            "data":list(cathedral[0])
            })

ccperpectron.addIDef ("SC_PERCEPTRON_INPUT_SIZE (" + str (len(p.coef_[0])) + "u)")
ccperpectron.addIDef ("SC_PERCEPTRON_INTERCEPT (" + str (p.intercept_[0]) + ")")


counter = 0
for c in p.coef_[0]:
    ccperpectron.addIDef ("SC_PERCEPTRON_WEIGHT_" + str (counter) + " (" + str (round(c,6)) + ")")
    counter += 1

ccstrings.create()
cccathedral.create()
ccperpectron.create()

fe.exit("Done.\n Results were exported to C in generatedfiles. Re-compile and run the C example.")

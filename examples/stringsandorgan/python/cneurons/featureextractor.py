#!/usr/bin/env python3
import os
import math

#! External dependencies for math
import numpy


#! External dependencies for sound
import librosa


class featureextractor:
    def __init__(self):
        self.featuresByClass = {"features":[], "outputs":[]}
        self.debug = False
        self.useRound = True
        self.decimals = 3 #! Accuracy is determined by your embedded system, you can set it to higher as well as lower values.
        
        
        
    def getTrainingAccuracy(self, nnType):
        if str(nnType).lower()=="perceptron":
            return 0.01
        
        else:
            return 0.01
        
    def debug(self,enable=True):
        self.debug=enable
        
    def exit(self, msg=""):
        ''' It is sometimes convenient to exit the application. Using this, you know who did it. '''
        print ("\n", str(msg))
        print ("Exitting in feature extractor...")
        exit (0)
    
    def load_sounds_from_folders(self, folders):
        SR = 22050 # Sample rate at which the sounds are recorded.
        """ Loads all sounds in a folder"""
        sounds = []
        for foldername in folders:
            for filename in os.listdir (foldername):
                if not "DS_" in filename:
                    X, sr = librosa.load (os.path.join (foldername,filename))
                    assert sr == SR
                    sounds.append(X)
        
        return sounds
    
    def load_sound_file(self, file):
        X, sr = librosa.load (file)
        
        return X, sr
    
    def addFeature (self, feature, featureClass):
        self.featuresByClass["features"].append (feature)
        self.featuresByClass["outputs"].append (featureClass)
        
    def getFeatures (self):
        return self.featuresByClass
    
    
    def normalizeByMean (self, samples):
        samples_normalized=samples
        # compute the mean of X and normalize the data
        samples_mean = sum(samples_normalized) / len(samples_normalized)
        counter=0
        for s in samples_normalized:
            samples_normalized[counter] = s - samples_mean
            counter += 1
            
        return samples_normalized
    
    def getFeaturesByAutocorrelation(self, samples, maxLag):
        correl = self.autocorrelate (samples, maxLag)
        del(correl[0]) #! First value is always 1, correlation with itself, delete it because it does not contain information.
        maxval = max(correl)
        minval = min(correl)
        mean = numpy.mean(correl)
        stdev = numpy.std(correl)
        
        return [maxval, minval, mean, stdev]
    
    def autocorrelate (self, samples, autocorrelationSize):
        '''
        Limiting float precision with self.decimals.
        '''
        if self.useRound:
            mean = round (sum (samples)/len (samples), self.decimals)
        else:
            mean = sum (samples)/len (samples)
        
        autocorrelation = [0.] * autocorrelationSize
        for t in range (0, autocorrelationSize):
            n = 0 # Numerator
            d = 0 # Denominator
            for i in range (0, len(samples)):
                if self.useRound:
                    xim = round(samples[i],self.decimals) - mean
                else:
                    xim = samples[i] - mean
             
                if self.useRound:
                    n += xim * (round(samples[(i + t) % len(samples)],self.decimals) - mean)
                else:
                    n += xim * (samples[(i + t) % len(samples)] - mean)

                d += xim * xim
                
                if self.debug:
                    print ("# featureextractor: i: ", str(i)," sample: ", str(samples[i])," xim: ", str(xim)," n: ",str(n)," d:",str(d),"")
                    
            if self.useRound:
                autocorrelation[t] = round (n / d,self.decimals)
                
            else:
                autocorrelation[t] = n / d

        return autocorrelation
    
    def signals_triangle(self, N=20, amplitude=1, frequency=1, steps=200, noise=0.0):
        '''
        Generates time signal based on inverse FFT, adding sinusoidal waves.
        @param N number of harmonics, N=1 means f0.
        @param amplitude Amplitude of signal.
        @param frequency frequency of signal.
        @param steps in how many steps is the signal required to be detailed.
        '''
        t = numpy.arange (steps)
        firsttime = True
        for i in range(0,N):
            _n = 2*i+1
            if firsttime:
                a = amplitude*math.pow(-1, i)*math.pow(_n,-2)*numpy.sin (2*numpy.pi*t*_n/steps)
                y=a
                firsttime = False

            else:
                b = amplitude*math.pow(-1, i)*math.pow(_n,-2)*numpy.sin (2*numpy.pi*t*_n/steps)
                y =[x+y for x,y in zip(a, b)]
                a=y

        if noise > 0.0:
            b = list(numpy.random.normal(0,noise, steps))
            y =[x+y for x,y in zip(a, b)]
        
        return t, y
        
    def ellipse(self):
        #! https://en.wikipedia.org/wiki/Lissajous_curve
        pass
        #! subtract two sinusses to get elliptic time signals.
        
        
    def signals_sinusSoidal(self, amplitude, frequency, steps):
        t = numpy.arange (steps)
        y = amplitude*numpy.sin (2*numpy.pi*t/steps)
    
        return t, y

    def makeSoundSamples(self, infile, outfile, duration, start=0, end=20, prefix="sound_"):
        '''
        @param infile input file to make samples from. INCLUDE EXTENTION!
        @param outfile output file of the sample. DON'T ADD EXTENSION!
        @param duration how small should the sound samples be
        @param start start point in soundfile in seconds
        @param end end point in soundfile in seconds
        @param prefix replace the file prefix name
        '''
        nextpos=start
        counter=0
        while nextpos < end:
            ffmpeg = "ffmpeg -y -ss "+str(nextpos)+" -t "+str(duration)+" -i "+str(infile) + " output/" + str(prefix)+ "_sample_" +str(counter)+ ".wav"
            print(ffmpeg)
            os.system(ffmpeg)
            nextpos+=duration
            nextpos=round(nextpos,1)
            counter+=1
    

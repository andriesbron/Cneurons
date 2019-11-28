

# Cneurons

- Easy starter for starters in Perceptron neural networks in C for embedded systems, the smaller controllers.
- Concept of cNeurons is to train in Python and implement in embedded C.
- Using Cneurons is by copying an example, currently one, from the example directory. Then, run the python script, next, run the C application. The Python example exports the perceptron parameters as a result of the training into corresponding files for the C application.
- Extend the example to your needs.

First a philosophic note, if you don't want that, scroll down to the example(s).

# Important to understand

Two things you should never forget:

- Mathematics remains applicable which is why:
- The scientific method is always the preferable method to solve a technological problem.

```There is no higher intelligence than the intelligence that applies the scientific method, below that intelligence is artificial intelligence. The scientific method produces a mathematically correct solution that cannot fail or behaves within its tolerances. Artificial intelligence produces a mathematical relation between inputs and outputs according the way you tell it they are. You tell the network what it should do.```


No matter how you train artificial intelligence, the laws of math remain applicable. So what? Well, that is not a problem because, you don't have to do the math 

# Examples
## Detection of sound

Example: Strings and organ

Example demonstrates how to use autocorrelation for detecting a sound, in this case, A note strings or a E note cathedral organ recorded from Garageband, just to demonstrate the work process and that it apparently can work.

First correlate the input sequence:
- ACOR_autoCorrelate_float (...)

Next create a featureset by catching the correlation sequence into a max, min, mean and std
- POPU_population_float (...)

Finally, predict the result:
- PRCPT_predict_float (...)

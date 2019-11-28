

# Cneurons

- Easy starter for starters in Perceptron neural networks in C for embedded systems, the smaller controllers.
- Concept of cNeurons is to train in Python and implement in embedded C.
- Using cNeurons is by copying an example, currently one, from the example directory. Then, run the python script, next, run the C application. The Python example exports the perceptron parameters as a result of the training into corresponding files for the C application.
- Extend the example to your needs.



## Detection of a time series

Example: Strings and organ

Example demonstrates how to use autocorrelation for detecting a time sequences, in this case, A note strings or a E note cathedral organ recorded from Garageband, just to demonstrate the work process.

First correlate the input sequence:
- ACOR_autoCorrelate_float (...)

Next create a featureset by catching the correlation sequence into a max, min, mean and std
- POPU_population_float (...)

Finally, predict the result:
- PRCPT_predict_float (...)

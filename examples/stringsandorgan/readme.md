# Strings and organ


Include stringsandorgan.h in the main program and rund EXAMPLE_stringsOrCathedral().
The python directory contains the training session in which the perceptron parameters are generated and exported to include files for stringsandorgan.h. Have fun.

## Attention
It is not said that there is no other sound that will produce the same features as the strings sound. To be more accurate, an FFT could be used to generate the features. In other words, I would not use this to distinguish strings from organs... 

## Concept of application

First correlate the input sequence:
- ACOR_autoCorrelate_float (...)

Next create a featureset by catching the correlation sequence into a max, min, mean and std
- POPU_population_float (...)

Finally, predict the result:
- PRCPT_predict_float (...)

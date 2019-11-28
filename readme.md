

# Cneurons

- Easy starter for starters in **Perceptron neural networks** in **C for embedded systems**, the smaller controllers.
- Concept of cNeurons is to **train in Python** and **implement in embedded C**.
- Using Cneurons is by copying an example, currently one, from the example directory. Then, run the python script, next, run the C application. The **Python example exports the perceptron parameters** as a result of the training into corresponding files for the C application.
- Extend the example to your needs.

First a philosophic note, if you don't want that, scroll down to the example(s).

# Important to understand

The highest form of intelligence is to apply the **scientific method**, below that intelligence is **artificial intelligence**. Arificial intelligence was developed through the scientific method. The **preferable method** to solve a technological problem is therefore always the **scientific method**.

The difference between both is that the **scientific method produces a mathematically exact description of a behavior** within the limits of its tolerances. **Artificial intelligence produces a mathematical relation between inputs and outputs** according the way you tell it it is. A neural network is **not more powerful than the mind that trained it**. There is no doubt, there are very powerful neural networks and concepts of artificial intelligence. Artificial intelligence is imho **unbeatable in pattern recognition**.

The most important thing when starting with neural networks and artificial intelligence is this:

**Two equations that share more than two unknown variables, cannot be solved. Also not by a neural network.**

Or, in case you train it by ignorance:

**Two equations that share more than two unknown variables, can be solved but have multiple solutions. Also in a neural network.**

It is very likely that you train a network by the latter concept.

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

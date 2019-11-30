//
//  mlperceptron.h
//  Cneurons
//
//  Created by andries bron on 11/30/19.
//

#ifndef mlperceptron_h
#define mlperceptron_h

#include <stdio.h>

/**
 * @brief 16 bits unsigned perceptron.
 */
typedef struct PRCPT_mlPerceptron_float {
    uint16_t inputSize;
    float *inputWeights;
    uint8_t hiddenSize;
    float *hiddenWeights;
    uint8_t outputSize;
    float *outputWeights;

    float intercept;
} PRCPT_mlPerceptron_float_t;





#endif /* mlperceptron_h */

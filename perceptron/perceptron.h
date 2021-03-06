//
//  perceptron.h
//
//  Copyright © 2019 Andries Bron www.github.com/andriesbron All rights reserved.
//

#ifndef perceptron_h
#define perceptron_h

#include <stdio.h>


/**
 * @brief Setting to 1 enables logging to console, for normal use, set to zero.
 */
#define PRCPT_DEBUG (1u)


/**
 * @brief Return values for functions to handle results in a proper way.
 */
typedef enum PRCPT_returnValues {
  PRCPT_SUCCESS
  , PRCPT_SATURATED
  , PRCPT_INPUT_OUTBOUND
  , PRCPT_UNKNOWN_ERROR
} PRCPT_returnValue;

typedef enum PRCPT_activationTypes {
    PRCPT_RELU
} PRCPT_activation_t;

/**
 * @brief 8 bits unsigned perceptron.
 */
typedef struct PRCPT_perceptrons_8u {
    PRCPT_activation_t activation;
    uint16_t inputLength;
    uint8_t *weights;
    uint8_t intercept;
} PRCPT_perceptron_8_t;

/**
 * @brief 16 bits unsigned perceptron.
 */
typedef struct PRCPT_perceptrons_16u {
    PRCPT_activation_t activation;
    uint16_t inputLength;
    uint16_t *weights;
    uint16_t intercept;
} PRCPT_perceptron_16_t;

/**
 * @brief float perceptron.
 */
typedef struct PRCPT_perceptrons_float {
    PRCPT_activation_t activation;
    uint16_t inputLength;
    float *weights;
    float intercept;
} PRCPT_perceptron_float_t;


/**
 * @brief Perceptron prediction for 16 bits unsigned values
 * @param apuc_inputs Array of input values.
 * @param apt_perceptron Pointer to the perceptron implementation.
 * @param apuc_prediction Pointer to the prediction result, this is what you get back from the prediction.
 * @return unsigned char 1 if apuc_inputs are estimated to be in class, otherwise 0.
 */
PRCPT_returnValue PRCPT_predict_float (float *apuc_inputs, PRCPT_perceptron_float_t *apt_perceptron, uint8_t *apuc_prediction);

/**
 * @brief Perceptron prediction for 8 bits unsigned values
 * @param apuc_inputs Array of input values.
 * @param apt_perceptron Pointer to the perceptron implementation.
 * @param apuc_prediction Pointer to the prediction result, this is what you get back from the prediction.
 * @return unsigned char 1 if apuc_inputs are estimated to be in class, otherwise 0.
 */
PRCPT_returnValue PRCPT_predict_8u (uint8_t *apuc_inputs, PRCPT_perceptron_8_t *apt_perceptron, uint8_t *apuc_prediction);

/**
 * @brief Perceptron prediction for 16 bits unsigned values
 * @param apuc_inputs Array of input values.
 * @param apt_perceptron Pointer to the perceptron implementation.
 * @param apuc_prediction Pointer to the prediction result, this is what you get back from the prediction.
 * @return unsigned char 1 if apuc_inputs are estimated to be in class, otherwise 0.
 */
PRCPT_returnValue PRCPT_predict_16u (uint16_t *apuc_inputs, PRCPT_perceptron_16_t *apt_perceptron, uint8_t *apuc_prediction);




#endif /* perceptron_h */

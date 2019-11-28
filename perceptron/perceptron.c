//
//  perceptron.c
//
//  Copyright © 2019 Andries Bron www.github.com/andriesbron All rights reserved.
//


#include <stdio.h>
#include <float.h>
#include "perceptron.h"



PRCPT_returnValue PRCPT_getYOnLine (unsigned char auc_dy, unsigned char auc_offset, unsigned char auc_x);
PRCPT_returnValue PRCPT_getYBetweenPoints (unsigned char auc_x, unsigned char *auc_y, unsigned char auc_x1, unsigned char auc_y1, unsigned char auc_x2, unsigned char auc_y2);


/****************************************************************************************************/
/*                                        Implementations                                            */
/****************************************************************************************************/


/**
 * @attention Not Tested
 */
PRCPT_returnValue PRCPT_getYOnLine (unsigned char auc_dy, unsigned char auc_offset, unsigned char auc_x)
{
  unsigned char uc_y=0;
  
  return uc_y;
}

/**
 * @attention Not Tested
 */
PRCPT_returnValue PRCPT_getYBetweenPoints (unsigned char auc_x, unsigned char *auc_y, unsigned char auc_x1, unsigned char auc_y1, unsigned char auc_x2, unsigned char auc_y2)
{
    uint8_t uc_dy=0;
    uint8_t uc_dx=0;

    if (
        (auc_x < auc_x1)
        && (auc_x > auc_x2)
    ) {
        return PRCPT_INPUT_OUTBOUND;
    }
    
    uc_dy = auc_y2 - auc_y1;
    uc_dx = auc_x2 - auc_x1;
    *auc_y = (auc_x * uc_dy) / uc_dx;

    return PRCPT_SUCCESS;
}

/**
 * @brief Interface function, see decription on interface.
 */
PRCPT_returnValue PRCPT_predict_float (float *apuc_inputs, PRCPT_perceptron_float_t *apt_perceptron, uint8_t *apuc_prediction)
{
    PRCPT_returnValue retVal=PRCPT_SUCCESS;
    uint8_t uc_i;
    float f_sum=0;
    float f_floatmax=FLT_MAX;
    float f_in_weighted=0;

    for (uc_i=0; uc_i < apt_perceptron->inputLength; uc_i++) {
        // Calculate the part that becomes added next to check on saturation
        f_in_weighted = apt_perceptron->weights[uc_i] * apuc_inputs[uc_i];
        
        if (f_sum <= (f_floatmax - f_in_weighted)) {
            f_sum += f_in_weighted;
        } else {
            // Network saturates
            f_sum = f_floatmax;
            retVal = PRCPT_SATURATED;
            break; // Exit loop
        }
#if PRCPT_DEBUG
        printf("Perceptron sum: %f f_inweighted: %f inputval: %f weight:%f\n", f_sum, f_in_weighted, apuc_inputs[uc_i], apt_perceptron->weights[uc_i]);
#endif
    }
    // Add the bias or intercept (sklearn)
    f_sum += apt_perceptron->intercept;
    *apuc_prediction = (unsigned char)(f_sum > 0);
#if PRCPT_DEBUG
    printf("Perceptron sum: %f divided by %d results in %d \n\n", f_sum,apt_perceptron->inputLength, *apuc_prediction);
#endif
    
    return retVal;
}

/**
 * @brief Interface function, see decription on interface.
 * @attention Not Tested
 * @bug result is not saturated when the total becomes to high
 */
PRCPT_returnValue PRCPT_predict_8u (uint8_t *apuc_inputs, PRCPT_perceptron_8_t *apt_perceptron, uint8_t *apuc_prediction)
{
    uint8_t uc_i;
    uint16_t ui_sum=0;

    for (uc_i=0; uc_i < apt_perceptron->inputLength; uc_i++) {
        ui_sum += apt_perceptron->weights[uc_i] * apuc_inputs[uc_i];
    }
    // Add the bias or intercept (sklearn)
    ui_sum += apt_perceptron->intercept;
    *apuc_prediction = (unsigned char)(ui_sum > 0);

    return PRCPT_SUCCESS;
}

/**
 * @brief Interface function, see decription on interface.
 * @attention Not Tested
 * @bug result is not saturated when the total becomes to high
 */
PRCPT_returnValue PRCPT_predict_16u (uint16_t *apuc_inputs, PRCPT_perceptron_16_t *apt_perceptron, uint8_t *apuc_prediction)
{
    unsigned char uc_i;
    unsigned int ui_sum=0;

    for (uc_i=0; uc_i < apt_perceptron->inputLength; uc_i++) {
        ui_sum += apt_perceptron->weights[uc_i] * apuc_inputs[uc_i];
    }
    // Add the bias or intercept (sklearn)
    ui_sum += apt_perceptron->intercept;
    *apuc_prediction = (unsigned char)(ui_sum > 0);

    return PRCPT_SUCCESS;
}

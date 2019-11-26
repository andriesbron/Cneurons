//
//  perceptron.c
//
//  Copyright © 2019 Andries Bron www.github.com/andriesbron All rights reserved.
//


#include <stdio.h>
#include "perceptron.h"


/**
 * @brief Macro's for getting the max values of types.
 */
#define ISSIGNED(t) (((t)(-1)) < ((t) 0))
#define UMAXOF(t) (((0x1ULL << ((sizeof(t) * 8ULL) - 1ULL)) - 1ULL) | \
                    (0xFULL << ((sizeof(t) * 8ULL) - 4ULL)))
#define SMAXOF(t) (((0x1ULL << ((sizeof(t) * 8ULL) - 1ULL)) - 1ULL) | \
                    (0x7ULL << ((sizeof(t) * 8ULL) - 4ULL)))
#define MAXOF(t) ((unsigned long long) (issigned(t) ? smaxof(t) : umaxof(t)))


PRCPT_returnValue PRCPT_getYOnLine (unsigned char auc_dy, unsigned char auc_offset, unsigned char auc_x);
PRCPT_returnValue PRCPT_getYBetweenPoints (unsigned char auc_x, unsigned char *auc_y, unsigned char auc_x1, unsigned char auc_y1, unsigned char auc_x2, unsigned char auc_y2);


/****************************************************************************************************/
/*                                        Implementations                                            */
/****************************************************************************************************/


PRCPT_returnValue PRCPT_getYOnLine (unsigned char auc_dy, unsigned char auc_offset, unsigned char auc_x)
{
  unsigned char uc_y=0;
  
  return uc_y;
}

/**
 * @attention not tested
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

PRCPT_returnValue PRCPT_predict_float (float *apuc_inputs, PRCPT_perceptron_float_t *apt_perceptron, uint8_t *apuc_prediction)
{
    PRCPT_returnValue retVal=PRCPT_SUCCESS;
    uint8_t uc_i;
    float ui_sum=0;
    float f_floatmax=UMAXOF(float);
    float f_inweight;

    for (uc_i=0; uc_i < apt_perceptron->inputLength; uc_i++) {
        f_inweight = apt_perceptron->weights[uc_i] * apuc_inputs[uc_i];
        if (ui_sum + f_inweight < f_floatmax) {
            ui_sum += apt_perceptron->weights[uc_i] * apuc_inputs[uc_i];
        } else {
            ui_sum = f_floatmax;
            retVal = PRCPT_SATURATED;
        }
    }
    ui_sum = ui_sum/apt_perceptron->inputLength;
    *apuc_prediction = (unsigned char)(ui_sum > 0);

    return retVal;
}

PRCPT_returnValue PRCPT_predict_8u (uint8_t *apuc_inputs, PRCPT_perceptron_8_t *apt_perceptron, uint8_t *apuc_prediction)
{
    uint8_t uc_i;
    uint16_t ui_sum=0;

    for (uc_i=0; uc_i < apt_perceptron->inputLength; uc_i++) {
        ui_sum += apt_perceptron->weights[uc_i] * apuc_inputs[uc_i];
    }

    ui_sum = ui_sum/apt_perceptron->inputLength;
    *apuc_prediction = (unsigned char)(ui_sum > 0);

    return PRCPT_SUCCESS;
}

PRCPT_returnValue PRCPT_predict_16u (uint16_t *apuc_inputs, PRCPT_perceptron_16_t *apt_perceptron, uint8_t *apuc_prediction)
{
  unsigned char uc_i;
  unsigned int ui_sum=0;
  
  *apuc_prediction = (unsigned char)(ui_sum > 0);
  
  return PRCPT_SUCCESS;
}

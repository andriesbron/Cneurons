//
//  autocorrelate.c
//
//  Copyright © 2019 Andries Bron, www.github.com/andriesbron. All rights reserved.
//

#include <float.h>
#include "autocorrelation.h"
#include "populations.h"




/****************************************************************************************************/
/*                                        Implementations                                            */
/****************************************************************************************************/



/**
 * @attention Not tested.
 */
ACOR_returnValue_t ACOR_autoCorrelate_8u (uint8_t *apuc_Xi, uint16_t auc_XiSize, int8_t *apuc_autocorrelate, uint16_t auc_autocorrelateSize)
{
    uint8_t f_mean = 0;
    int16_t f_n = 0; // Numerator
    int16_t f_d = 0; // Denominator
    int16_t f_xim;
    
    // UNTESTED FUNCTION MIGHT HAVE ISSUES WITH SIZES
    
    f_mean = POPU_mean_8u (apuc_Xi, auc_XiSize);

    
    
    for (uint8_t t = 0; t < auc_autocorrelateSize; t ++)
    {
        for (uint8_t i = 0; i < auc_XiSize; i ++)
        {
            f_xim = apuc_Xi[i] - f_mean;
            f_n += f_xim * (apuc_Xi[(i + t) % auc_XiSize] - f_mean);
            f_d += f_xim * f_xim;
        }
        apuc_autocorrelate[t] = f_n / f_d;
    }
    
    return ACOR_SUCCESS;
}

/**
 * @attention Not tested.
 */
ACOR_returnValue_t ACOR_autoCorrelate_8s (int8_t *apuc_Xi, uint16_t auc_XiSize, int8_t *apuc_autocorrelate, uint16_t auc_autocorrelateSize)
{
    // rewrite or call the 8u?
    return ACOR_FAULT_DO_NOT_USE_RESULT;
}

ACOR_returnValue_t ACOR_autoCorrelate_float (float *apuc_Xi, uint16_t auc_XiSize, float *apuc_autocorrelate, uint16_t auc_autocorrelateSize)
{
    float f_mean = 0;
    float f_n = 0; // Numerator
    float f_d = 0; // Denominator
    float f_xim;
    ACOR_returnValue_t t_retVal = ACOR_SUCCESS;
    float f_floatmax = FLT_MAX;
    
    //f_mean = ACOR_mean_float (apuc_Xi, auc_XiSize);
    f_mean = POPU_mean_float (apuc_Xi, auc_XiSize);

#if ACOR_DEBUG
    printf ("\n*********** Autocorrelate.h ***********\n");
    printf ("auc_XiSize: %d auc_autocorrelateSize: %d\n", auc_XiSize, auc_autocorrelateSize);
    printf ("f_mean: %f\n", f_mean);
#endif
    for (int t = 0; t < auc_autocorrelateSize; t ++)
    {
        f_n = 0;
        f_d = 0;
        
        for (int i = 0; i < auc_XiSize; i ++)
        {
            f_xim = apuc_Xi[i] - f_mean;
            f_n += f_xim * (apuc_Xi[(i + t) % auc_XiSize] - f_mean);
            f_d += f_xim * f_xim;
#if ACOR_DEBUG
            //printf ("i: %d apuc_Xi[i]: %f f_xim: %f f_n: %f f_d: %f \n", i, apuc_Xi[i], f_xim, f_n, f_d);
#endif
        }
        if (f_d == 0u) {
            t_retVal = ACOR_DIVISIONS_BY_ZERO_SET_ZERO;
            apuc_autocorrelate[t] = f_floatmax;
        } else {
            apuc_autocorrelate[t] = f_n / f_d;
        }
#if ACOR_DEBUG
        printf("\nAutocorrelate index %d value %f\n", t, apuc_autocorrelate[t]);
        printf("- f_n: %f f_d: %f\n", f_n, f_d);
#endif
    }
    
    return t_retVal;
}

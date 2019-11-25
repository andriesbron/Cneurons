//
//  autocorrelate.c
//
//  Copyright © 2019 Andries Bron, www.github.com/andriesbron. All rights reserved.
//

#include "autocorrelation.h"
#include "populations.h"

/**
 * @brief Macro's for getting the max values of types.
 */
#define ISSIGNED(t) (((t)(-1)) < ((t) 0))
#define UMAXOF(t) (((0x1ULL << ((sizeof(t) * 8ULL) - 1ULL)) - 1ULL) | \
                    (0xFULL << ((sizeof(t) * 8ULL) - 4ULL)))
#define SMAXOF(t) (((0x1ULL << ((sizeof(t) * 8ULL) - 1ULL)) - 1ULL) | \
                    (0x7ULL << ((sizeof(t) * 8ULL) - 4ULL)))
#define MAXOF(t) ((unsigned long long) (issigned(t) ? smaxof(t) : umaxof(t)))




/****************************************************************************************************/
/*                                        Implementations                                            */
/****************************************************************************************************/


float ACOR_mean_float (float *apuc_X, uint16_t auc_XLength)
{
    float f_mean=0;
    uint16_t uc_i;

#if ACOR_DEBUG
        printf("sizeof(float) %d\n", (uint8_t)sizeof(float));
#endif
    for (uc_i=0; uc_i < auc_XLength; uc_i++)
    {
        f_mean += apuc_X[uc_i];
    }
#if ACOR_DEBUG
    printf("Sum of mean: %f length of array %d", f_mean, auc_XLength);
#endif
    f_mean = f_mean/auc_XLength;

    return f_mean;
}



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
    return ACOR_UNKNOWN_ERROR;
}

ACOR_returnValue_t ACOR_autoCorrelate_float (float *apuc_Xi, uint16_t auc_XiSize, float *apuc_autocorrelate, uint16_t auc_autocorrelateSize)
{
    float f_mean = 0;
    float f_n = 0; // Numerator
    float f_d = 0; // Denominator
    float f_xim;
    ACOR_returnValue_t t_retVal = ACOR_SUCCESS;
    float f_floatmax = UMAXOF(float);
    
    //f_mean = ACOR_mean_float (apuc_Xi, auc_XiSize);
    f_mean = POPU_mean_float (apuc_Xi, auc_XiSize);

#if ACOR_DEBUG
    printf ("\n*********** Autocorrelate.h ***********\n");
    printf ("auc_XiSize: %d auc_autocorrelateSize: %d\n", auc_XiSize, auc_autocorrelateSize);
    printf ("f_mean: %f\n", f_mean);
    printf ("Max float would we have a division by zero: %f", f_floatmax);
#endif
    for (int t = 0; t < auc_autocorrelateSize; t ++)
    {
#if ACOR_DEBUG
        printf ("\nt: %d\n-------------------------------------------------------------------\n", t);
#endif
        for (int i = 0; i < auc_XiSize; i ++)
        {
            f_xim = apuc_Xi[i] - f_mean;
            f_n += f_xim * (apuc_Xi[(i + t) % auc_XiSize] - f_mean);
            f_d += f_xim * f_xim;
#if ACOR_DEBUG
            printf ("i: %d apuc_Xi[i]: %f f_xim: %f f_n: %f f_d: %f \n", i, apuc_Xi[i], f_xim, f_n, f_d);
#endif
        }
        if (f_d == 0u) {
            t_retVal = ACOR_DIVISION_BY_ZERO_SET_MAX;
            apuc_autocorrelate[t] = f_floatmax;
        } else {
            apuc_autocorrelate[t] = f_n / f_d;
        }
#if ACOR_DEBUG
        printf("Autocorrelate index %d value %f\n", t, apuc_autocorrelate[t]);
        printf("- f_n: %f f_d: %f\n", f_n, f_d);
#endif
    }
    
    return t_retVal;
}

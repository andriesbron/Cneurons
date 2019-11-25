//
//  populations.c
//

#include <math.h>
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

#define MAX_OF(type) \
    (((type)(~0LLU) > (type)((1LLU<<((sizeof(type)<<3)-1))-1LLU)) ? (long long unsigned int)(type)(~0LLU) : (long long unsigned int)(type)((1LLU<<((sizeof(type)<<3)-1))-1LLU))
#define MIN_OF(type) \
    (((type)(1LLU<<((sizeof(type)<<3)-1)) < (type)1) ? (long long int)((~0LLU)-((1LLU<<((sizeof(type)<<3)-1))-1LLU)) : 0LL)




/****************************************************************************************************/
/*                                        Implementations                                            */
/****************************************************************************************************/


void POPU_population_float (float * af_X, uint16_t ai_Size, float * af_max, float * af_min, float *af_mean, float * af_stdev)
{
    float f_sum=0;
    float f_max=MIN_OF(float);
    float f_min=UMAXOF(float);
    float f_stdev=0;
    
    uint16_t uc_i;

    for (uc_i=0; uc_i < ai_Size; uc_i++)
    {
        f_sum += af_X[uc_i];
        if (af_X[uc_i] > f_max) {
            f_max = af_X[uc_i];
        } else if (af_X[uc_i] < f_min) {
            f_min = af_X[uc_i];
        }
        
    }
    
    *af_mean = f_sum/ai_Size;
    printf ("\nmymean %f passed mean %f\n",f_sum/ai_Size, *af_mean);
    for (uc_i=0; uc_i < ai_Size; uc_i++)
    {
        f_stdev += pow(af_X[uc_i] - *af_mean, 2);
    }
    
    *af_max = f_max;
    *af_min = f_min;
    *af_stdev = sqrt(f_stdev/ai_Size);
}

float POPU_mean_float (float * af_X, uint16_t ai_Size)
{
    float f_mean=0;
    uint16_t uc_i;

#if ACOR_DEBUG
        printf("sizeof(float) %d\n", (uint8_t)sizeof(float));
#endif
    for (uc_i=0; uc_i < ai_Size; uc_i++)
    {
        f_mean += af_X[uc_i];
    }
#if ACOR_DEBUG
    printf("Sum of mean: %f length of array %d", f_mean, auc_XLength);
#endif
    f_mean = f_mean/ai_Size;

    return f_mean;
}

float POPU_deviation (float * af_X, uint16_t ai_Size)
{
    float sum = 0.0, mean, standardDeviation = 0.0;
    int i;
    for(i=0; i<ai_Size; ++i)
    {
        sum += af_X[i];
    }
    mean = sum/10;
    for(i=0; i<10; ++i)
        standardDeviation += pow(af_X[i] - mean, 2);
    return sqrt(standardDeviation/ai_Size);
}

float POPU_median (float * af_X, uint16_t ai_Size)
{
    return 0;
}


uint8_t POPU_mean_8u (uint8_t *apuc_X, uint16_t auc_XLength)
{
  uint16_t uc_mean=0;
  uint8_t uc_i;
  
  for (uc_i=0; uc_i < auc_XLength; uc_i++)
  {
    uc_mean += apuc_X[uc_i];
  }
  uc_mean = (int8_t)(uc_mean/auc_XLength);
  
  return uc_mean;
}

int8_t POPU_mean_8s (int8_t *apuc_X, uint16_t auc_XLength)
{
  int16_t uc_mean=0;
  uint8_t uc_i;
  
  for (uc_i=0; uc_i < auc_XLength; uc_i++)
  {
    uc_mean += apuc_X[uc_i];
  }
  uc_mean = (int8_t)(uc_mean/auc_XLength);
  
  return uc_mean;
}

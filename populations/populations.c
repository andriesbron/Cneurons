//
//  populations.c
//

#include <math.h>
#include <float.h>
#include "populations.h"



/****************************************************************************************************/
/*                                        Implementations                                            */
/****************************************************************************************************/


void POPU_population_float (float * af_X, uint16_t ai_Size, float * af_max, float * af_min, float *af_mean, float * af_stdev)
{
    float f_sum=0;
    float f_max=-FLT_MAX;
    float f_min=FLT_MAX;
    float f_stdev=0;
    
    uint16_t uc_i;

    for (uc_i=0; uc_i < ai_Size; uc_i++)
    {
        printf("Value: %f\n",af_X[uc_i]);
        f_sum += af_X[uc_i];
        if (af_X[uc_i] > f_max) {
            f_max = af_X[uc_i];
        }
        if (af_X[uc_i] < f_min) {
            f_min = af_X[uc_i];
        }
    }
    *af_mean = f_sum/ai_Size;
#if POPULATION_DEBUG
    printf ("\nMean %f Sum %f Size: %d\n\n", *af_mean ,f_sum, ai_Size);
#endif
    for (uc_i=0; uc_i < ai_Size; uc_i++)
    {
        f_stdev += pow (af_X[uc_i] - *af_mean, 2);
    }
    
    *af_max = f_max;
    *af_min = f_min;
    *af_stdev = sqrt (f_stdev/ai_Size);
}

float POPU_mean_float (float * af_X, uint16_t ai_Size)
{
    float f_mean=0;
    uint16_t uc_i;

#if POPULATION_DEBUG
        printf("sizeof(float) %d\n", (uint8_t)sizeof(float));
#endif
    for (uc_i=0; uc_i < ai_Size; uc_i++)
    {
        f_mean += af_X[uc_i];
    }
#if POPULATION_DEBUG
    printf("Sum of mean: %f length of array %d", f_mean, ai_Size);
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

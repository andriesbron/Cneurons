//
//  populations.h
//

#ifndef populations_h
#define populations_h

#include <stdio.h>

#define POPULATION_DEBUG (0u)

void POPU_population_float (float * af_X, uint16_t ai_Size, float * af_max, float * af_min,float *af_mean, float * af_stdev);


float POPU_mean_float (float * af_X, uint16_t ai_Size);
int8_t POPU_mean_8s (int8_t *apuc_X, uint16_t auc_XLength);
uint8_t POPU_mean_8u (uint8_t *apuc_X, uint16_t auc_XLength);

float POPU_max_float (float * af_X, uint16_t ai_Size);

float POPU_deviation_float (float * af_X, uint16_t ai_Size);

float POPU_median_float (float * af_X, uint16_t ai_Size);


#endif /* populations_h */

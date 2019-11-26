//
//  autocorrelate.h
//
//  Copyright © 2019 Andries Bon www.github.com/andriesbron. All rights reserved.
//

/**
 * @brief According the idea of https://www.alanzucconi.com/2016/06/06/autocorrelation-function/ see also https://www.datacamp.com/community/tutorials/autocorrelation-r
 * @attention Auto correlation result can either be negative or positive.
 */

#ifndef autocorrelate_h
#define autocorrelate_h

#include <stdio.h>

/**
 * @brief Setting to 1 enables logging to console, for normal use, set to zero.
 */
#define ACOR_DEBUG (1u)


/**
 @todo eliminate the first autocor caluclation, because is always 1. or add a function that does not do that.
 */

/**
 * @brief Return values for functions to handle results in a proper way.
 */
typedef enum ACOR_returnValues {
  ACOR_SUCCESS
  , ACOR_INPUT_OUTBOUND_DIVISION_BY_ZERO // When wrong input data was given, however, the algorithm by nature will not divide by zero.
  , ACOR_DIVISIONS_BY_ZERO // The algorithm divided by zero and returned immediately.
  , ACOR_DIVISIONS_BY_ZERO_SET_MAX // The algorithm prevented division by zero and set the result to the max value of its type.
  , ACOR_DIVISIONS_BY_ZERO_SET_MIN // The algorithm prevented division by zero and set the result to the min value of its type.
  , ACOR_DIVISIONS_BY_ZERO_SET_ZERO // The algorithm prevented division by zero and set the result to zero.
  , ACOR_INPUT_OUTBOUND
  , ACOR_FAULT_DO_NOT_USE_RESULT
} ACOR_returnValue_t;


/**
 * @attention For use: take notice that the first value is always 1, don't train on that value.
 * @brief Autocorrelator for float data.
 * @param apuc_Xi Sample array of floats
 * @param auc_XiSize Size of sample array
 * @param apuc_autocorrelate Autocorrelation array (result returned), see also auc_autocorrelateSize
 * @param auc_autocorrelateSize Size of correlation array (apuc_autocorrelate). If you want to test a delay for one sample, the size should be 1. Size 2 means, two samples delay etcetera.
 * @attention might return a value not equal to ACOR_SUCCESS, e.g. divisions by zero might happen, however the result is still usefull
 */
ACOR_returnValue_t ACOR_autoCorrelate_float (float *apuc_Xi, uint16_t auc_XiSize, float *apuc_autocorrelate, uint16_t auc_autocorrelateSize);

/**
 * @brief Autocorrelator for uint8_t data (unsigned).
 * @param apuc_Xi Sample array of floats
 * @param auc_XiSize Size of sample array
 * @param apuc_autocorrelate Autocorrelation array, see also auc_autocorrelateSize
 * @param auc_autocorrelateSize Size of correlation array (apuc_autocorrelate). If you want to test a delay for one sample, the size should be 1. Size 2 means, two samples delay etcetera.
 * @attention Not tested.
 */
ACOR_returnValue_t ACOR_autoCorrelate_8u (uint8_t *apuc_Xi, uint16_t auc_XiSize, int8_t *apuc_autocorrelate, uint16_t auc_autocorrelateSize);

/**
 * @brief Autocorrelator for int8_t data (signed).
 * @param apuc_Xi Sample array of floats
 * @param auc_XiSize Size of sample array
 * @param apuc_autocorrelate Autocorrelation array, see also auc_autocorrelateSize
 * @param auc_autocorrelateSize Size of correlation array (apuc_autocorrelate). If you want to test a delay for one sample, the size should be 1. Size 2 means, two samples delay etcetera.
 * @attention Not yet implemented.
 */
// ACOR_returnValue_t ACOR_autoCorrelate_8s (int8_t *apuc_Xi, uint16_t auc_XiSize, int8_t *apuc_autocorrelate, uint16_t auc_autocorrelateSize);

#endif /* autocorrelate_h */

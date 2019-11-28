//
//  stringsandorgan.c
//

#include "stringsandorgan.h"

// From generated files
#include "generatedfiles/stringcathedralperceptron.h"
#include "generatedfiles/stringssample.h"
#include "generatedfiles/cathedralsample.h"

#include "perceptron.h"
#include "autocorrelation.h"
#include "populations.h"


#define EXAMPLE_FEATURE_MAX (0u)
#define EXAMPLE_FEATURE_MIN (1u)
#define EXAMPLE_FEATURE_MEAN (2u)
#define EXAMPLE_FEATURE_STD (3u)
#define EXAMPLE_FEATURE_COUNT (4u)

#define EXAMPLE_AUTOCORRELATION_DELAY_MAX (4u)


void EXAMPLE_stringsOrCathedral (void)
{
    printf("testing audio samples.\n");
    float acor[EXAMPLE_AUTOCORRELATION_DELAY_MAX]; // Autocorrelation array
    float f_features[SC_PERCEPTRON_INPUT_SIZE]; // Feature array
    PRCPT_perceptron_float_t t_stringDetector; // Perceptron definition
    float fp_stringDetectorWeights[SC_PERCEPTRON_INPUT_SIZE] = {
        SC_PERCEPTRON_WEIGHT_0,
        SC_PERCEPTRON_WEIGHT_1,
        SC_PERCEPTRON_WEIGHT_2,
        SC_PERCEPTRON_WEIGHT_3
    }; // Perceptron weight values
    uint8_t prediction; // Prediction result
    
    // Perceptron definition from python
    t_stringDetector.inputLength = SC_PERCEPTRON_INPUT_SIZE;
    t_stringDetector.weights = fp_stringDetectorWeights;
    t_stringDetector.intercept = SC_PERCEPTRON_INTERCEPT;
    
    // Testing Strings audio
    ACOR_autoCorrelate_float (ff_stringssamples, FF_STRINGSSAMPLES_CONST, acor, EXAMPLE_AUTOCORRELATION_DELAY_MAX);
    for (uint8_t i=0; i <EXAMPLE_AUTOCORRELATION_DELAY_MAX; i++) {
        printf("Acor %d value %f\n", i, acor[i]);
    }
    // @attention Do not use the first element of the correlation array, that result is 1. Attention subtract therefore 1!
    POPU_population_float (&acor[1], EXAMPLE_AUTOCORRELATION_DELAY_MAX-1, &f_features[EXAMPLE_FEATURE_MAX], &f_features[EXAMPLE_FEATURE_MIN], &f_features[EXAMPLE_FEATURE_MEAN], &f_features[EXAMPLE_FEATURE_STD]);
    printf("Features: max %f min %f mean %f std %f\n",f_features[EXAMPLE_FEATURE_MAX], f_features[EXAMPLE_FEATURE_MIN], f_features[EXAMPLE_FEATURE_MEAN], f_features[EXAMPLE_FEATURE_STD]);
    PRCPT_predict_float (f_features, &t_stringDetector, &prediction);
    printf("Prediction: %d\n\n", prediction);
    
    
    
    // Testing Cathedral audio
    ACOR_autoCorrelate_float (ff_cathedralsamples, FF_CATHEDRALSAMPLES_CONST, acor, EXAMPLE_AUTOCORRELATION_DELAY_MAX);
    for (uint8_t i=0; i <EXAMPLE_AUTOCORRELATION_DELAY_MAX; i++) {
        printf("acor %d value %f\n", i, acor[i]);
    }
    // @attention Do not use the first element of the correlation array, that result is 1. Attention subtract therefore 1!
    POPU_population_float (&acor[1], EXAMPLE_AUTOCORRELATION_DELAY_MAX-1, &f_features[EXAMPLE_FEATURE_MAX], &f_features[EXAMPLE_FEATURE_MIN], &f_features[EXAMPLE_FEATURE_MEAN], &f_features[EXAMPLE_FEATURE_STD]);
    printf("Features: max %f min %f mean %f std %f\n",f_features[EXAMPLE_FEATURE_MAX], f_features[EXAMPLE_FEATURE_MIN], f_features[EXAMPLE_FEATURE_MEAN], f_features[EXAMPLE_FEATURE_STD]);
    PRCPT_predict_float (f_features, &t_stringDetector, &prediction);
    printf("Prediction: %d\n\n", prediction);
}


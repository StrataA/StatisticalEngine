#ifndef comparator_h
#define comparator_h

// General control variables
extern int learnMode; // 0 for false, any other value for true. When learnMode is true,

// Hypothetes testing variables
extern float historicMean, historicStdDev; // stand-ins for the population/true parameters
extern float sampleMean, sampleStdDev; // sample statistics
extern int numSamples, historicObservations;
extern float alpha; // default significance level

enum Tailed {
    one = 0,
    two,
};

int zTest(enum Tailed tail);
float zTableLookup(float z);

int tTest(enum Tailed tail);
float tTableLookup(float t, int df, enum Tailed tail);

int extractFloatArrayFromFile();

#endif
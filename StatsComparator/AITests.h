#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "comparator.h"


// Global variables (assuming these exist in your program)
extern float historicMean;
extern float historicStdDev;
extern int historicObservations;
extern float sampleMean;
extern float sampleStdDev;
extern int numSamples;
extern float alpha;
extern int learnMode;

void run_stats_test_suite();
void simulate_real_world();
void simulate_with_csv();

void reset_globals();
void run_improved_test_suite();
void simulate_and_export_csv(const char* filename);
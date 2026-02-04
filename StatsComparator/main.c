#include <stdio.h>
#include <stdlib.h>

#include "comparator.h"
#include "AITests.h"

// Extern variables for comparator
// Sample mean, stdDev and numSamples are proporties of collected/imported data
// Historic mean, stdDev and Observations accumulate past knowledge
int learnMode = 0;
float historicMean = 0, historicStdDev = 1 ; // stand-ins for the population/true parameters
float sampleMean = 0, sampleStdDev = 1; // sample statistics
int numSamples = 1, historicObservations = 1;
float alpha = 0.5;

void testZTest1();
void testTtest();
void run_stats_test_suite();

int main(){
    
printf("Hello from main\n");

// testZTest1();
// testTtest();9

// run_stats_test_suite();
// simulate_real_world();
// simulate_with_csv();

// reset_globals();
// run_improved_test_suite();
// simulate_and_export_csv("stats_stress_test.csv");


return 0;
}


void testZTest1(){
    alpha = 0.05;
    historicMean = 5.5;
    // historicObservations = 10;
    learnMode = 1;
    sampleMean = 1.445;
    zTest(one);
    sampleMean = 5.8435;
    zTest(one);
    sampleMean = 5.443;
    zTest(one);
    sampleMean = 5.243;
    zTest(one);
    sampleMean = 5.1738;
    zTest(one);
    sampleMean = 5.24;
    zTest(one);
    sampleMean = 5.0132;
    zTest(one);
    sampleMean = 3.88;
    zTest(one);
    sampleMean = 3.8;
    zTest(one);
    sampleMean = 3.7;
    zTest(one);
};

void testTtest(){

        // Stress Test 1: Minimal df
    numSamples = 2;
    sampleMean = 10.0;
    historicMean = 5.0; // Large difference
    sampleStdDev = 1.0;
    tTest(two);
};

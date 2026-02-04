#include "AITests.h"

void run_stats_test_suite() {
    printf("==========================================\n");
    printf("\t\tAI MADE STRESS TEST\n");
    printf("==========================================\n\n");

    // --- TEST 1: Z-Table Boundary ---
    printf("[1] Boundary Test (Z > 3.6): ");
    float pHigh = zTableLookup(5.0f);
    if (pHigh == 0.0001f) printf("PASS\n");
    else printf("FAIL (Got %f)\n", pHigh);

    // --- TEST 2: Symmetry ---
    printf("[2] Symmetry Test (-Z == Z): ");
    if (zTableLookup(-1.96f) == zTableLookup(1.96f)) printf("PASS\n");
    else printf("FAIL\n");

    // --- TEST 3: Column Index Precision ---
    // Floating point math: 0.09 * 100 can sometimes be 8.999999
    printf("[3] Precision Test (Z=0.09): ");
    // Manual check: your 0.0 row, index 9 is 0.4641
    if (zTableLookup(0.09f) == 0.4641f) printf("PASS\n");
    else printf("FAIL (Likely indexing col 8 instead of 9)\n");

    // --- TEST 4: T-Test Extreme Small Sample ---
    printf("[4] Small Sample T (df=1):    ");
    // This tests for division by zero in: 1.0 / (4.0 * df)
    float pTiny = tTableLookup(2.0f, 1, two);
    if (isnan(pTiny)) printf("FAIL (NaN detected)\n");
    else printf("PASS (p = %f)\n", pTiny);

    // --- TEST 5: Welford Stability ---
    printf("[5] Welford Zero Variance:   ");
    // Force a case where variance might become negative due to precision
    historicStdDev = 0.01f;
    historicMean = 100.0f;
    historicObservations = 1000;
    sampleMean = 100.0f; // No change
    learnMode = 1;
    zTest(one); // Run it
    if (historicStdDev >= 0) printf("PASS\n");
    else printf("FAIL (Negative StdDev)\n");

    printf("\nTests Complete.\n");
}



void simulate_real_world() {

historicMean = 100.0f;
historicStdDev = 5.0f;
historicObservations = 50;
alpha = 0.05f;
learnMode = 1;


    printf("Starting Simulation: Population shifting from 100.0 to 105.0\n");
    printf("Iteration | Sample Mean | P-Value | Result | Updated Hist Mean\n");
    printf("------------------------------------------------------------\n");

    srand(time(NULL));

    for (int i = 1; i <= 4000; i++) {
        // 1. Generate a sample batch (n=10) centered around 105.0
        // We'll simulate a 105.0 mean with some random noise
        numSamples = 10;
        float currentSum = 0;
        float data[10];
        
        for(int j=0; j<10; j++) {
            data[j] = 105.0f + ((rand() % 200 - 100) / 10.0f); // 105 +/- 10
            currentSum += data[j];
        }
        
        sampleMean = currentSum / numSamples;

        // 2. Calculate sampleStdDev for the T-test
        float sumSq = 0;
        for(int j=0; j<10; j++) sumSq += pow(data[j] - sampleMean, 2);
        sampleStdDev = sqrt(sumSq / (numSamples - 1));

        // 3. Run the tests
        // We will call your tTest here to see how it handles the shift
        tTest(two);

        // 4. Report Progress
        printf(" [%02d]     |   %6.2f    |  ----  |  DONE  |   %6.2f\n", 
                i, sampleMean, historicMean);
    }
}

void simulate_with_csv() {
historicMean = 100.0f;
historicStdDev = 5.0f;
historicObservations = 50;
alpha = 0.05f;
learnMode = 1;

    FILE *f = fopen("stats_stress_test.csv", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // CSV Header
    fprintf(f, "Iteration,Sample_Mean,Historic_Mean,Historic_StdDev,Status\n");

    printf("Simulation starting... Check stats_stress_test.csv for results.\n");
    int numItr = 100;
    for (int i = 1; i <= numItr; i++) {
        // 1. Simulate a process shift (Population moves to 110.0)
        numSamples = 15;
        float currentSum = 0;
        for(int j=0; j<numSamples; j++) {
            currentSum += 110.0f + ((rand() % 100 - 50) / 5.0f); 
        }
        sampleMean = currentSum / numSamples;
        sampleStdDev = 4.5f; // Static for this stress test

        // 2. Run the T-Test
        // We'll capture the status manually for the CSV
        float stdErr = sampleStdDev / sqrt(numSamples);
        float t = fabs((sampleMean - historicMean) / stdErr);
        float p = tTableLookup(t, numSamples - 1, two);
        const char* status = (p < alpha) ? "SIGNIFICANT" : "NORMAL";

        // 3. Run your actual zTest/tTest to update the 'historic' globals
        // tTest(two);
        zTest(two);

        // 4. Log to CSV
        fprintf(f, "%d,%.2f,%.2f,%.2f,%s\n", 
                i, sampleMean, historicMean, historicStdDev, status);
    }

    fclose(f);
    printf("Simulation Complete. %d iterations logged.\n", numItr);
}

// Helper to reset globals between tests
void reset_globals() {
    historicMean = 100.0f;
    historicStdDev = 5.0f;
    historicObservations = 100;
    alpha = 0.05f;
    learnMode = 0;
    numSamples = 10;
}

void run_improved_test_suite() {
    printf("==========================================\n");
    printf("\tMODERNIZED STATS TEST SUITE\n");
    printf("==========================================\n\n");

    // --- TEST 1: The "No-Brainer" (Null Hypothesis should hold) ---
    reset_globals();
    sampleMean = 100.0f; // Exactly the same as historic
    printf("[1] Identity Test (Sample == Historic): ");
    if (zTest(two) == 0) printf("PASS (Fail to Reject)\n");
    else printf("FAIL (Rejected identical mean)\n");

    // --- TEST 2: The "Outlier" (Null Hypothesis should be rejected) ---
    reset_globals();
    sampleMean = 120.0f; // 4 standard deviations away
    printf("[2] Outlier Test (Significant Diff):   ");
    if (zTest(two) == 1) printf("PASS (Rejected Outlier)\n");
    else printf("FAIL (Failed to detect significant diff)\n");

    // --- TEST 3: Return Consistency (tTest) ---
    reset_globals();
    sampleMean = 120.0f;
    sampleStdDev = 5.0f;
    printf("[3] T-Test Return Value Check:         ");
    // Ensure tTest now returns the same logic as zTest
    int tResult = tTest(two); // Ensure you updated tTest signature to return int
    if (tResult == 1) printf("PASS\n");
    else printf("FAIL (T-Test did not return 1)\n");

    // --- TEST 4: Learning Mode (The "Adaptation" Test) ---
    reset_globals();
    learnMode = 1;
    sampleMean = 102.0f; // Slightly off, but likely won't reject at alpha 0.05
    float oldMean = historicMean;
    
    zTest(two);
    
    printf("[4] Learning Mode Mean Update:         ");
    if (historicMean > oldMean) {
        printf("PASS (Mean drifted from %.2f to %.2f)\n", oldMean, historicMean);
    } else {
        printf("FAIL (Mean stayed at %.2f)\n", historicMean);
    }

    // --- TEST 5: Variance Stability ---
    reset_globals();
    learnMode = 1;
    sampleMean = 110.0f; // Large gap
    zTest(two); // If this rejects (returns 1), historicStdDev should NOT change
    
    printf("[5] Rejection Stability:               ");
    if (historicStdDev == 5.0f) {
        printf("PASS (Variance preserved on rejection)\n");
    } else {
        printf("FAIL (Variance changed despite rejection)\n");
    }
}

void simulate_and_export_csv(const char* filename) {
    reset_globals();
    learnMode = 1;
    alpha = 0.05f;

    FILE *f = fopen(filename, "w");
    fprintf(f, "Iteration,SampleMean,HistoricMean,PValue,Rejected\n");

    printf("Simulating 200 iterations. Check %s for results...\n", filename);

    for (int i = 1; i <= 200; i++) {
        // Slowly drift the true population mean upward
        float trueMean = 100.0f + (i * 0.1f); 
        
        // Generate sample
        sampleMean = trueMean + ((rand() % 200 - 100) / 50.0f); 
        numSamples = 15;
        
        // We manually calculate p-value for the log, then call the function
        float stdErr = historicStdDev / sqrt(numSamples);
        float z = fabs((sampleMean - historicMean) / stdErr);
        float p = zTableLookup(z) * 2.0f; // two-tailed

        int rejected = zTest(two);

        fprintf(f, "%d,%.2f,%.2f,%.4f,%d\n", i, sampleMean, historicMean, p, rejected);
    }
    fclose(f);
    printf("Done.\n");
}
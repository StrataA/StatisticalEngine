#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "CLL.h"
#include "Routines.h"
#include "DataManager.h"


void CLLtests();
void threadManagerTest();

int main () {
    std::cout << "\nBEGIN\n\n";
    
    int numSamples = 10;
    CLL sampleList;
    if (!sampleList.createFixedSampleList(numSamples)) {
            std::cout << "Failed to create sample list." << std::endl;
            return 1;
        }
        
        // CLLtests();
        // threadManagerTest(); 
        
        recordData(sampleList, 23.5, 45.0);
        
        std::cout << "\nEND\n\n";
        return 0;
    }
    
    
void threadManagerTest(){
    int numSamples = 10;
    CLL sampleList;
    if (!sampleList.createFixedSampleList(numSamples)) {
        std::cout << "Failed to create sample list." << std::endl;
        return;
    }
    
    // threadManager(sampleList);

};

void CLLtests(){
    // can be used for final
    int numSamples = 10;
    CLL sampleList;
    if (!sampleList.createFixedSampleList(numSamples)) {
        std::cout << "Failed to create sample list." << std::endl;
        return;
    }


    // temp testing
    // std::cout << sampleList.readAllData() << "\n\n";
    // std::cout << sampleList.readAllData() << "\n\n";
    // sampleList.recordDataSample(23.5, 45.0);
    // sampleList.recordDataSample(24.0, 50.0);
    // sampleList.recordDataSample(24.0, 51.0);
    // sampleList.recordDataSample(24.2, 50.1);
    // std::cout << sampleList.readAllData();
    // end temp testing
    
    // mutex testing
    // start a thread calling a non-static member function: pass pointer-to-member and object pointer
    std::thread worker1(&CLL::recordDataSample, &sampleList, 111.1, 0.1);
    std::thread worker2(&CLL::recordDataSample, &sampleList, 222.2, 0.2);
    std::thread worker3(&CLL::recordDataSample, &sampleList, 333.3, 0.3);
    // wait for the worker to finish in this test; detach if you want background execution
    std::cout << "Before joins:\n "<< sampleList.readAllData();
    worker1.join();
    worker3.join();
    worker2.join();
    std::cout << "After joins:\n "<< sampleList.readAllData();
} 

#endif

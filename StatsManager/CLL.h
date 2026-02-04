#ifndef CLL_H
#define CLL_H

#include <string>
#include <sstream>

#include <thread>
#include <mutex>

// note use of floats - ESP32 uses float32 hardware, so a float is an atomic unit already
// No node mutex is used - nodes should only be accessed via CLL methods which lock the list mutex 
struct nodeC {
    float temp;
    float humidity;
    int sampleInstance;
    nodeC* next;
    
    nodeC (float t, float h, int s);
    bool updateData(float t, float h);
    std::string readData();
    float getTemp();
    float getHumidity();
    int getSampleInstance();
};

struct CLL
{
    private:
    nodeC* head;
    nodeC* current;

    // threading utilities
    std::mutex listmtx;

    public:
    CLL();
    ~CLL();
    

    bool createFixedSampleList (int numSamples);
    std::string readAllData();
    bool recordDataSample (float temperature, float humidity);
    bool isHeadNext();

    
};

#endif
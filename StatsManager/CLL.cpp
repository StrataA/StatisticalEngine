#include "CLL.h"

// nodeC implementations
nodeC::nodeC (float t, float h, int s) : temp(t), humidity(h), sampleInstance(s){
        next = nullptr;
}
    
bool nodeC::updateData(float t, float h) {
        temp = t;
        humidity = h;
        return true;
}
    
std::string nodeC::readData() {
    return std::to_string(sampleInstance) + "|" + std::to_string(temp) + "|" + std::to_string(humidity);
}

float nodeC::getTemp() {
    return temp;
}

float nodeC::getHumidity() {
    return humidity;
}

int nodeC::getSampleInstance() {
    return sampleInstance;
}


// CLL implementations
CLL::CLL() : head(nullptr), current(nullptr) {};

CLL::~CLL() {
        if (!head) return;

        // Lock the list mutex during destruction
        std::lock_guard<std::mutex> lock(listmtx);

        nodeC* current = head->next;
        while (current != head) {
            nodeC* temp = current;
            current = current->next;
            delete temp;
        }
        delete head;
}
    
bool CLL::createFixedSampleList (int numSamples){
        if (numSamples <= 0) return false;
        
        std::lock_guard<std::mutex> lock(listmtx);

        head = new nodeC(0.0f, 0.0f, 0);
        current = head;
        for (int i = 1; i < numSamples; ++i) {
            current->next = new nodeC(0.0f, 0.0f, i);
            current = current->next;
        }
        current->next = head; // Make it circular
        current = head; // Reset current to head
        return true;
}
       
std::string CLL::readAllData() {
        if (!head) return "";

        std::lock_guard<std::mutex> lock(listmtx);

        std::string allData;
        nodeC* firstRead = current;
        do {
            allData += current->readData() + "\n";
            current = current->next;
        } while (current != firstRead);
        current = current->next;
        return allData;
}

bool CLL::recordDataSample (float temperature, float humidity) {
        if (!current) return false;

        std::lock_guard<std::mutex> lock(listmtx);

        current->updateData(temperature, humidity);
        current = current->next;
        return true;
}

bool CLL::isHeadNext() {
    std::lock_guard<std::mutex> lock(listmtx);
    return current->next == head;
}
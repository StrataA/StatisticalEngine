#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "CLL.h"
#include <string>
#include <iostream>

struct gc {
    // global control structure
    int gData;
}

bool recordData(CLL& list, float temperature, float humidity);

bool exportData(CLL& list, std::string& outData);


#endif
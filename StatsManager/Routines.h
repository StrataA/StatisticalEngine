// #ifndef RECORDER_ROUTINE_H
// #define RECORDER_ROUTINE_H

// #include <iostream>
// #include <string>
// #include <thread>
// #include <atomic>
// #include <chrono>
// #include <mutex>
// #include <condition_variable>

// #include "CLL.h"


// // mutex and condition variable for thread synchronization
// std::mutex gRoutineMtx;
// std::condition_variable gRoutineCv;    

// // boolean flags to control thread routines
// std::atomic<bool> gRecorderAsleep = false;
// std::atomic<bool> gUploaderAsleep = false;    
// std::atomic<bool> gTerminateThreads = false;    

// // Global sensor readings - should be recorder every time period
// std::atomic<float> gTemperature;
// std::atomic<float> gHumidity;    

// // Sample intervals in seconds - small values for testing
// // Note that the final implementation will use significantly larger intervals (on scale of hours) to save power and storage
// int SampleRecordInterval = 10; //seconds
// int SampleUploadInterval = 30; //seconds


// // thread manager functions

// int threadManager (CLL& sampleList );

// void recorderRoutine(CLL& sampleList, float& temperature, float& humidity);
// void uploaderRoutine(CLL& sampleList);



// class eRecorderException : public std::exception {
//     std::string msg;

//     virtual const char* what() const throw() {
//         return msg.c_str();
//     }

//     public:
//     eRecorderException(std::string message = "Recorder Routine Exception occurred") : msg(message) {}

// };


// class eUploaderException : public std::exception {
//     std::string msg;

//     virtual const char* what() const throw() {
//         return "Uploader Routine Exception occurred";
//     }

//     public:
//     eUploaderException(std::string message = "Uploader Routine Exception occurred") : msg(message) {}
// };

// #endif
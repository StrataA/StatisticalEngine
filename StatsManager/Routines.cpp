// #include "Routines.h"

// int threadManager (CLL& sampleList ) {
//     // In charge of recorder and uploader threads
//     // controllers ctrl;

//     // std::thread recorderThread(recorderRoutine, std::ref(sampleList), std::ref(gTemperature), std::ref(gHumidity));
//     // std::thread uploaderThread(uploaderRoutine, std::ref(sampleList));
    

//     // // wait for both threads to finish
//     // if (!recorderThread.joinable() || !uploaderThread.joinable()) {
//     //     std::cerr << "Error: Threads not joinable." << std::endl;
//     //     return -1;
//     // }

//     // std::this_thread::sleep_for(std::chrono::seconds(10));
//     // gTerminateThreads.store(true);

//     // recorderThread.join();
//     // uploaderThread.join();


//     return 0;
// }

// void recorderRoutine(CLL& sampleList, float& temperature, float& humidity) {

//     while (!gTerminateThreads.load())
//     {
//         try
//         {        // record data sample
//             std::unique_lock<std::mutex> locker(gRoutineMtx);
//             if (!sampleList.recordDataSample(temperature, humidity)) {
//                 throw eRecorderException("Failed to record data sample in recorderRoutine.");
//             }
//             std::cout << std::this_thread::get_id() << ": Recorded sample: T=" << temperature << " H=" << humidity << std::endl;
//             locker.unlock();
//         }
//         catch(const std::exception& e)
//         {
//             std::cerr << e.what() << '\n';
//         }
        
//         // wait for next recording interval
//         std::this_thread::sleep_for(std::chrono::seconds(SampleRecordInterval)); // simulate data recording interval

//         // check for CLL position
//         if (sampleList.isHeadNext()) {
                       
//             std::unique_lock<std::mutex> locker(gRoutineMtx); //prepare locker for waiting
//             gRecorderAsleep.store(true);
//             gUploaderAsleep.store(false);
//             gRoutineCv.notify_one(); // notify uploader routine to wake up
//             gRoutineCv.wait(locker); // wait until uploader routine signals back
//         }
//     }
    
// }

// void uploaderRoutine(CLL& sampleList) {

//     while (!gTerminateThreads.load())
//     {
//         std::unique_lock<std::mutex> locker(gRoutineMtx);
//         gUploaderAsleep.store(true);
//         gRoutineCv.wait(locker); // wait until notified by recorderRoutine




//         // end of uploading routine - reawaken recorder and go to sleep
//         locker.lock(); //prepare locker for waiting
//             gRecorderAsleep.store(false);
//             gUploaderAsleep.store(true);
//             gRoutineCv.notify_one(); // notify uploader routine to wake up
//             gRoutineCv.wait(locker); // wait until uploader routine signals back
//     }

// }
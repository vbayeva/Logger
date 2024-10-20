#include <iostream>
#include <thread>
#include <vector>

#include "Logger.hpp"

void workerFunction(int thread_id) {
    Logger& logger = Logger::getInstance();

    logger.log(LogLevel::INFO, "Thread " + std::to_string(thread_id) + " started.");
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100 * thread_id));

    logger.log(LogLevel::WARNING, "Thread " + std::to_string(thread_id) + " is processing.");

    std::this_thread::sleep_for(std::chrono::milliseconds(100 * (5 - thread_id)));

    logger.log(LogLevel::ERROR, "Thread " + std::to_string(thread_id) + " encountered an error.");

    logger.log(LogLevel::INFO, "Thread " + std::to_string(thread_id) + " finished.");
}


int main()
{
    Logger& logger = Logger::getInstance();
    logger.setLogFile("app.log"); 

    const int numThreads = 5;
    std::vector<std::thread> threads;

    for (int i = 1; i <= numThreads; ++i) {
        threads.emplace_back(workerFunction, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    logger.log(LogLevel::INFO, "All threads have finished.");

    return 0;
}

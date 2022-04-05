/*
    File Name: producer.hpp
    Created: 7 March 22
    Version: 1.0
*/
#ifndef PRODUCER_HPP_
#define PRODUCER_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <fstream>
#include "shared_memory.hpp"

using namespace std;

class Producer
{

public:
    Producer(string, int, int);
    ~Producer();

    void setSensorFileName(string);
    void setTaskNumber(int);
    void setPeriod(int);
    string getSensorFileName();
    int getTaskNumber();
    int getPeriod();

    bool loadSensorData();

    void run();

private:
    string sensor_file_name;
    int task_num;
    int period;
    vector<float> sensorData;
    SharedMemory shared_mem;
};

#endif // PRODUCER_HPP_

/*
    File Name: producer.hpp
    Created: 7 March 22
    Version: 1.0
    Author: Gabriel Karras

    Description:
    Configures sensor data such that it updates its dynamic array(vector)
    with the current time t's sensor value(i.e.: V[t] = sensor_value)
    This will facilitate the interface between the sensor data and the shared memory
*/
#ifndef PRODUCER_HPP_
#define PRODUCER_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "shared_mem.hpp"
#include "timer.hpp"

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
    string sensor_file_name = "";
    int task_num = 0;
    int period = 0;
    vector<float> sensorData;
};

#endif // PRODUCER_HPP_
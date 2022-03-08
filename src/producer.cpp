/*
    File Name: producer.cpp
    Created: 7 March 22
    Version: 1.0
    Author: Gabriel Karras
*/
#include "producer.hpp"

Producer::Producer(string sensor_file_name, int task_num, int period)
{
    setSensorFileName(sensor_file_name);
    setTaskNumber(task_num);
    setPeriod(period);
    loadSensorData();
}

Producer::~Producer()
{
}

void Producer::setSensorFileName(string sensor_file_name)
{
    sensor_file_name = sensor_file_name;
}

void Producer::setTaskNumber(int task_num)
{
    task_num = task_num;
}

void Producer::setPeriod(int period)
{
    period = period;
}

string Producer::getSensorFileName()
{
    return sensor_file_name;
}

int Producer::getTaskNumber()
{
    return task_num;
}

int Producer::getPeriod()
{
    return period;
}

/*
    Loads sensor values from .txt file into an array
*/
bool Producer::loadSensorData()
{
    ifstream fs;
    fs.open(sensor_file_name);

    // Verify if we open .txt file
    if (!fs)
    {
        cerr << "Error during file opening: " << sensor_file_name << endl;
        exit(EXIT_FAILURE);
    }

#ifdef DEBUG
    cout << sensor_file_name << " is opened!" << endl;
#endif

    // Load data to array
    float sensor_data;

    while (!fs.eof())
    {
        sensorData.push_back(sensor_data);
        fs >> sensor_data;
    }

    // We're able to completely read from the .txt file
    if (fs.eof())
    {
#ifdef DEBUG
        cout << sensor_file_name << " is loaded!" << endl;
#endif

        return true;
    }

    return false;
}

void Producer::run()
{
    int time;
    float data;
    int period = getPeriod();
    int array_size = sensorData.size() - 1;

#ifdef DEBUG
    cout << "Producer running" << endl;
    cout << "Size of array: " << array_size << endl;
#endif

    for (int i = 0; i < array_size; i += period)
    {
        /* TODO: must fetch time and period from shared memory*/
        // time = current_time()
        data = sensorData[time];
        // write_to_shared_mem(loc, data)
#ifdef DEBUG
        cout << "Time: "
             << "Data: " << endl;
#endif
        // sleep(period);
    }
}
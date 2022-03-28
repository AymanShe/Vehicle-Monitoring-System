/*
    File Name: producer.cpp
    Created: 7 March 22
    Version: 1.0
    Author: Gabriel Karras

    Description:
    Configures sensor data such that it updates its dynamic array(vector)
    with the current time t's sensor value(i.e.: V[t] = sensor_value)
    This will facilitate the interface between the sensor data and the shared memory
*/
#include "producer.hpp"

/* Constructor */
Producer::Producer(string sensor_file_name, int task_num, int period)
{
    setSensorFileName(sensor_file_name);
    setTaskNumber(task_num);
    setPeriod(period);
    loadSensorData();
}

/* Empty Destructor */
Producer::~Producer()
{
}

/* Set file name for sensor data(*.txt) */
void Producer::setSensorFileName(string sensor_file_name)
{
    this->sensor_file_name = sensor_file_name;
}

/* Set task number */
void Producer::setTaskNumber(int task_num)
{
    this->task_num = task_num;
}

/* Set period for task */
void Producer::setPeriod(int period)
{
    this->period = period;
}

/* Get sensor file name(*.txt) */
string Producer::getSensorFileName()
{
    return sensor_file_name;
}

/* Get task number */
int Producer::getTaskNumber()
{
    return task_num;
}

/* Get task period */
int Producer::getPeriod()
{
    return period;
}

/* Loads sensor values from .txt file into a vector/dynamic array */
bool Producer::loadSensorData()
{
    ifstream fs;
    fs.open(sensor_file_name.c_str());

    // Verify if we open .txt file
    if (!fs)
    {
        cerr << "Error during file opening: " << sensor_file_name << endl;
        exit(EXIT_FAILURE);
    }

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
        return true;
    }

    return false;
}

/*
    Once we run a thread, we will continually write the sensor date to our
    task number's shared memory address. The task will wake up after
    its time period has elapsed.
*/
void Producer::run()
{
    int task_num_addr = getTaskNumber();
    int period = getPeriod();
    int array_size = sensorData.size() - 1;


    // Iterate through the vector by bounds of the task's period
    for (int time = 0; time < array_size; time += period)
    {
        shared_mem.write(task_num_addr, sensorData[time]);
//        shared_mem.write(task_num_addr + UPDATE_STATUS_OFFSET, UPDATED);
        std::this_thread::sleep_for(std::chrono::seconds(period));
    }

    // Let consumer know that task is done
    shared_mem.write(task_num_addr + UPDATE_STATUS_OFFSET, TASK_DONE);
}

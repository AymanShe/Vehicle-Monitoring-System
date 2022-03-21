/*
    File Name: producer.cpp
    Created: 7 March 22
    Version: 1.0
    Author: Gabriel Karras
*/
#include <producer.hpp>


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
    this->sensor_file_name = sensor_file_name;
}

void Producer::setTaskNumber(int task_num)
{
    this->task_num = task_num;
}

void Producer::setPeriod(int period)
{
    this->period = period;
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

/* Loads sensor values from .txt file into an array */
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
        cout << "Size of array: " << array_size << endl;
#endif
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
    int time;
    int data;
    int task_num_addr = getTaskNumber();
    int period = getPeriod();
    int array_size = sensorData.size() - 1;

#ifdef DEBUG
    cout << "Producer Thread " << getTaskNumber() << " running" << endl;
#endif

    for (int i = 0; i < array_size; i += period)
    {
        /* TODO: must fetch time and period from shared memory*/
        // time = current_time()
        data = sensorData[time];
        shared_mem.write(task_num_addr, data);
#ifdef DEBUG
        cout << "Time: " << time << endl;
        cout << "Data: " << SharedMemory::read(task_num_addr) << endl;
#endif
        // sleep(period);
    }
}

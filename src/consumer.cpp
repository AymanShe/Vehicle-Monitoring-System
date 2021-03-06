/*
    File Name: consumer.cpp
    Created: 7 March 22
    Version: 1.0

    Description: Reads from shared memory and displays the sensor data
    according to the elapsed time t
*/
#include "consumer.hpp"

#define TASK0 0  // Fuel Consumption
#define TASK1 1  // Engine Speed
#define TASK2 2  // Engine Coolant Temp
#define TASK3 3  // Current Gear
#define TASK4 4  // Vehicle Speed

SharedMemory shared_mem;

/*
    Command Line Interface which prints out sensor data value
    whenever a task(Producer thread) writes/updates their value
    in shared memory
*/
void CLI()
{
	std::string paramaters[]=
	{
			"Fuel Consumption(L/100Km)",
			"Engine Speed(RPM)",
			"Engine Coolant Temperature(C)",
			"Current Gear(Gear Level)",
			"Vehicle Speed(Mph)"
	};

	int values[5];
	bool updated[5];
	while (true) {

		for(int i =0; i<5;++i){
			int value = shared_mem.read(i);
			if(value != -1){
				values[i] = value;
				updated[i] = true;
			}
		}

		if(updated[0] && updated[1] && updated[2] && updated[3] && updated[4]){
			cout << "***************" << endl;
			for(int i =0; i<5;++i){
				cout << paramaters[i] << values[i] << endl;
				updated[i] = false;
			}
		}
	}
    cout << "End of Sensor Readings! Good Bye!" << endl;
}

/*
    Verifies if any task(Producer threads) updated their sensor data value
    and clears status if it is true
*/
int TaskUpdates()
{
    int status0, status1, status2, status3, status4;

    // If status is UPDATED then set to 1, else 0
    status0 = shared_mem.read(TASK0 + UPDATE_STATUS_OFFSET == UPDATED) ? 1 : 0;
    status1 = shared_mem.read(TASK1 + UPDATE_STATUS_OFFSET == UPDATED) ? 1 : 0;
    status2 = shared_mem.read(TASK2 + UPDATE_STATUS_OFFSET == UPDATED) ? 1 : 0;
    status3 = shared_mem.read(TASK3 + UPDATE_STATUS_OFFSET == UPDATED) ? 1 : 0;
    status4 = shared_mem.read(TASK4 + UPDATE_STATUS_OFFSET == UPDATED) ? 1 : 0;

    // I personally find this messy, but wanted to keep it simple
    if (status0)
    {
        // Reset status to 0-No updates
        shared_mem.write(TASK0 + UPDATE_STATUS_OFFSET, 0);
        return 1;
    }

    if (status1)
    {
        shared_mem.write(TASK1 + UPDATE_STATUS_OFFSET, 0);
        return 1;
    }

    if (status2)
    {
        shared_mem.write(TASK2 + UPDATE_STATUS_OFFSET, 0);
        return 1;
    }

    if (status3)
    {
        shared_mem.write(TASK3 + UPDATE_STATUS_OFFSET, 0);
        return 1;
    }

    if (status4)
    {
        shared_mem.write(TASK4 + UPDATE_STATUS_OFFSET, 0);
        return 1;
    }

    return 0;
}

/*
    Verifies if all tasks(Producer threads) are all done.
    If so, we return 1 and will allow the CLI to break away from the while-loop
*/
int AllTaskDone()
{
    int status0, status1, status2, status3, status4;

    // If status is DONE then set to 1, else 0
    status0 = shared_mem.read(TASK0 + UPDATE_STATUS_OFFSET == TASK_DONE) ? 1 : 0;
    status1 = shared_mem.read(TASK1 + UPDATE_STATUS_OFFSET == TASK_DONE) ? 1 : 0;
    status2 = shared_mem.read(TASK2 + UPDATE_STATUS_OFFSET == TASK_DONE) ? 1 : 0;
    status3 = shared_mem.read(TASK3 + UPDATE_STATUS_OFFSET == TASK_DONE) ? 1 : 0;
    status4 = shared_mem.read(TASK4 + UPDATE_STATUS_OFFSET == TASK_DONE) ? 1 : 0;

    if (status0 && status1 && status2 && status3 && status4)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

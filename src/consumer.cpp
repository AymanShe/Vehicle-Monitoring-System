/*
    File Name: consumer.cpp
    Created: 7 March 22
    Version: 1.0
    Author: Gabriel Karras
*/
#include "consumer.hpp"

// TODO: Might need to actually implement a class so we can have a dynamic period
void terminalGUI()
{
    cout << "\nTime" << endl;
    cout << "Fuel Consumption(L/100Km)" << SharedMemory::read(0) << endl;
    cout << "Engine Speed(RPM)" << SharedMemory::read(0) << endl;
    cout << "Engine Coolant Temperature(C)" << SharedMemory::read(0) << endl;
    cout << "Current Gear(Gear Level)" << SharedMemory::read(0) << endl;
    cout << "Vehicle Speed(Mph)" << SharedMemory::read(0) << endl;
    // sleep(GUI_PERIOD);
}
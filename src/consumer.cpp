/*
    File Name: consumer.cpp
    Created: 7 March 22
    Version: 1.0
    Author: Gabriel Karras
*/
#include <consumer.hpp>

SharedMemory shared_mem;

// TODO: Might need to actually implement a class so we can have a dynamic period
void terminalGUI()
{
    cout << "\nTime" << endl;
    cout << "Fuel Consumption(L/100Km)" << shared_mem.read(0) << endl;
    cout << "Engine Speed(RPM)" << shared_mem.read(1) << endl;
    cout << "Engine Coolant Temperature(C)" << shared_mem.read(2) << endl;
    cout << "Current Gear(Gear Level)" << shared_mem.read(3) << endl;
    cout << "Vehicle Speed(Mph)" << shared_mem.read(4) << endl;
    // sleep(GUI_PERIOD);
}

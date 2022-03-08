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
    // TODO: must fetch sensor data from shared memory
    cout << "\nTime" << endl;
    cout << "Fuel Consumption(L/100Km)" << endl;
    cout << "Engine Speed(RPM)" << endl;
    cout << "Engine Coolant Temperature(C)" << endl;
    cout << "Current Gear(Gear Level)" << endl;
    cout << "Vehicle Speed(Mph)" << endl;
    // sleep(GUI_PERIOD);
}
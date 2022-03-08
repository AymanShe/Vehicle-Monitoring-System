/*
    COEN 320 Vehicle Monitoring Display System

    File Name: main.cpp
    Created: 7 March 22
    Version: 1.0
    Author(s): Ayman, Gabriel, Ruddy, Serge

    Description:

*/
#include <iostream>
#include <thread>
#include "producer.hpp"
#include "consumer.hpp"

#define DEFAULT_PERIOD 5

int main()
{
    Producer fuel_consumption("Fuel_consumption.txt", 0, DEFAULT_PERIOD);
    Producer engine_speed("Engine_speed.txt", 1, DEFAULT_PERIOD);
    Producer engine_coolant_temperature("Engine_coolant_temperature.txt", 2, DEFAULT_PERIOD);
    Producer current_gear("Current_Gear.txt", 3, DEFAULT_PERIOD);
    Producer vehicle_speed("Vehicle_Speed.txt", 4, DEFAULT_PERIOD);

    cout << "Threads started" << endl;
    thread th_fuel_consumption(&Producer::run, &fuel_consumption);
    thread th_engine_speed(&Producer::run, &engine_speed);
    thread th_engine_coolant_temperature(&Producer::run, &engine_coolant_temperature);
    thread th_current_gear(&Producer::run, &current_gear);
    thread th_vehicle_speed(&Producer::run, &vehicle_speed);
    thread th_GUI(&terminalGUI);

    th_fuel_consumption.join();
    th_engine_speed.join();
    th_engine_coolant_temperature.join();
    th_current_gear.join();
    th_vehicle_speed.join();
    th_GUI.join();
    cout << "Threads Ended" << endl;

    return EXIT_SUCCESS;
}
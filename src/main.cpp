/*
    COEN 320 Vehicle Monitoring Display System

    File Name: main.cpp
    Created: 7 March 22
    Version: 1.0
    Author(s): Ayman, Gabriel, Ruddy, Serge

    Description: Instantiates 5 producer threads(one per each sensor data of interest)
    and 1 consumer thread(which will display the sensor data).
*/
#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>
#include "producer.hpp"
#include "consumer.hpp"

#define DEFAULT_PERIOD 5

#define FUEL_CONSUMPTION 0
#define ENGINE_SPEED 1
#define ENGINE_COOLANT_TEMP 2
#define CURRENT_GEAR 3
#define VEHICLE_SPEED 4

void getUserPeriod(std::vector<int> &periods);

int main()
{
    cout << "Vehicle Monitoring System" << endl;

    // Prompt user for periods
    std::vector<int> periods;
    getUserPeriod(periods);

    // Create Producer for each sensor
    Producer fuel_consumption("Fuel_consumption.txt", FUEL_CONSUMPTION, periods[FUEL_CONSUMPTION]);
    Producer engine_speed("Engine_speed.txt", ENGINE_SPEED, periods[ENGINE_SPEED]);
    Producer engine_coolant_temperature("Engine_coolant_temperature.txt", ENGINE_COOLANT_TEMP, periods[ENGINE_COOLANT_TEMP] );
    Producer current_gear("Current_Gear.txt", CURRENT_GEAR, periods[CURRENT_GEAR]);
    Producer vehicle_speed("Vehicle_speed.txt", VEHICLE_SPEED, periods[VEHICLE_SPEED]);

    // Create threads for each producer and consumer
    cout << "Vehicle Monitoring System Threads Started" << endl;
    thread th_fuel_consumption(&Producer::run, &fuel_consumption);
    thread th_engine_speed(&Producer::run, &engine_speed);
    thread th_engine_coolant_temperature(&Producer::run, &engine_coolant_temperature);
    thread th_current_gear(&Producer::run, &current_gear);
    thread th_vehicle_speed(&Producer::run, &vehicle_speed);
    thread th_CLI(&CLI);

    // Join threads and exit
    th_fuel_consumption.join();
    th_engine_speed.join();
    th_engine_coolant_temperature.join();
    th_current_gear.join();
    th_vehicle_speed.join();
    th_CLI.join();
    cout << "Vehicle Monitoring System Threads Ended" << endl;

    return EXIT_SUCCESS;
}

/*
    Prompts user to either set periods to the default 5 seconds
    or to enter custom periods for each task

    We're assuming the periods will be in seconds
*/
void getUserPeriod(std::vector<int> &periods)
{
    int user_answer;
    std::cout << "Would you like to use the default period of 5s? 0-No 1-Yes:";
    std::cin >> user_answer;

    if (user_answer == 1)
    {
        for (int i = 0; i < 5; i++)
        {
            periods.push_back(DEFAULT_PERIOD);
        }
    }
    else
    {
        int user_input;
        std::cout << "\nEnter Fuel Consumption period(in seconds):";
        std::cin >> user_input;
        periods.push_back(user_input);

        std::cout << "\nEnter Engine Speed period(in seconds):";
        std::cin >> user_input;
        periods.push_back(user_input);

        std::cout << "\nEnter Engine Coolant Temperature period(in seconds):";
        std::cin >> user_input;
        periods.push_back(user_input);

        std::cout << "\nEnter Current Gear period(in seconds):";
        std::cin >> user_input;
        periods.push_back(user_input);

        std::cout << "\nEnter Vehicle Speed period(in seconds):";
        std::cin >> user_input;
        periods.push_back(user_input);
    }
}
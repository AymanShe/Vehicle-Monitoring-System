/*
    File Name: consumer.hpp
    Created: 7 March 22
    Version: 1.0
    Author: Gabriel Karras

    Description: Reads from shared memory and displays the sensor data
    according to the elapsed time t
*/
#ifndef CONSUMER_HPP_
#define CONSUMER_HPP_

#include <iostream>
#include <string>
#include "shared_memory.hpp"
#include "timer.hpp"

using namespace std;

void terminalGUI();

#endif // CONSUMER_HPP_

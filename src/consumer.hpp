/*
    File Name: consumer.hpp
    Created: 7 March 22
    Version: 1.0
*/
#ifndef CONSUMER_HPP_
#define CONSUMER_HPP_

#include <iostream>
#include <string>
#include "shared_memory.hpp"
#include <thread>
#include <chrono>

using namespace std;

void CLI();
int TaskUpdates();
int AllTaskDone();

#endif // CONSUMER_HPP_

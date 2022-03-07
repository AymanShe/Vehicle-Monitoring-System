/*

    COEN 320 Vehicle Monitoring Display System

    Created: 7 March 22
    Version: 1.0
    Author(s): Ayman, Gabriel, Ruddy, Serge

    Description:

*/

#include <iostream>
#include <periodic_timer.hpp>
#include <sys/time.h>

void print_time();

int main()
{
    run_periodically(1000000, 5000000, &print_time);
    return 0;
}

void print_time()
{
    struct timeval te;
    gettimeofday(&te, NULL);                                         // get current time
    long long milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000; // calculate milliseconds
    std::cout << "milliseconds: " << milliseconds << std::endl;
}
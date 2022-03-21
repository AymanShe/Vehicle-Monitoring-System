/*
    File Name: shared_memory.hpp
    Created: 9 March 22
    Version: 1.0
    Author: Gabriel Karras

    Description: Shared memory interface for the Vehicle Monitoring system
    which allows read and writting to the shared memory
*/
#ifndef SHARED_MEMORY_HPP_
#define SHARED_MEMORY_HPP_

#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>

using namespace std;

class SharedMemory
{
private:
    static char *sh_mem;
    static int sh_mem_size;
    int sh_mem_segment;
    int init();

public:
    SharedMemory();
    ~SharedMemory();
    int read(int);
    int write(int, int);
};
#endif // SHARED_MEMORY_HPP_
/*
    File Name: shared_memory.hpp
    Created: 9 March 22
    Version: 1.0
*/
#ifndef SHARED_MEMORY_HPP_
#define SHARED_MEMORY_HPP_

#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <mutex>

#define UPDATE_STATUS_OFFSET 5

#define UPDATED 1
#define TASK_DONE -1

using namespace std;

class SharedMemory
{
private:
    static char *sh_mem;
    static int sh_mem_size;
    int sh_mem_segment;
    int init();
    std::mutex m;

public:
    SharedMemory();
    ~SharedMemory();
    int read(int);
    int write(int, int);
};
#endif // SHARED_MEMORY_HPP_

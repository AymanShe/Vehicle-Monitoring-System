/*
    File Name: shared_memory.cpp
    Created: 9 March 22
    Version: 1.0

    Description: Shared memory interface for the Vehicle Monitoring system
    which allows read and writing to the shared memory
*/
#include "shared_memory.hpp"

int SharedMemory::sh_mem_size;
char *SharedMemory::sh_mem;

SharedMemory::SharedMemory()
{
    /* 'ISO C++11 doesn't allow conversion from string literal to char' can be ignored in QNX Momentics */
    sh_mem = "/shm_mem";
    sh_mem_size = 64;

    init();
    cout << "Created shared memory!" << endl;
}

/* Remove the shared memory segment */
SharedMemory::~SharedMemory()
{
    /* remove the shared memory segment */
    if (shm_unlink(sh_mem) == -1)
    {
        perror("in shm_unlink()");
        exit(EXIT_FAILURE);
    }
}

/* Create the shared memory segment */
int SharedMemory::init()
{
    sh_mem_segment = shm_open(sh_mem, O_CREAT | O_RDWR, 0666);
    if (sh_mem_segment == -1)
    {
        perror("In smh_open() during init of shared memory!");
        exit(EXIT_FAILURE);
    }

    ftruncate(sh_mem_segment, sh_mem_size);

    void *sh_mem_ptr;
    sh_mem_ptr = mmap(0, sh_mem_size, PROT_READ | PROT_WRITE, MAP_SHARED, sh_mem_segment, 0);
    if (sh_mem_ptr == MAP_FAILED)
    {
        printf("In mmap() during init of shared memory!");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/* Reads from shared memory at the specified address*/
int SharedMemory::read(int addr)
{
	m.lock();
    sh_mem_segment = shm_open(sh_mem, O_RDONLY, 0666);
    if (sh_mem_segment == -1)
    {
        perror("In shm_open() during read operation!\n");
        exit(EXIT_FAILURE);
    }

    void *sh_mem_ptr;
    sh_mem_ptr = mmap(0, sh_mem_size, PROT_READ, MAP_SHARED, sh_mem_segment, 0);
    if (sh_mem_ptr == MAP_FAILED)
    {
        perror("In mmap() during read operation!\n");
        exit(EXIT_FAILURE);
    }

    int *data_ptr = (int *)sh_mem_ptr + addr;
	int result = *data_ptr;

	close(sh_mem_segment);
	m.unlock();
	if(*data_ptr != -1){
		int result = *data_ptr;
		write(addr, -1);
		return result;
	}
	return result;
}

/* Writes data into shared memory at the specified address*/
int SharedMemory::write(int addr, int data)
{
	m.lock();
    sh_mem_segment = shm_open(sh_mem, O_CREAT | O_RDWR, 0666);
    void *sh_mem_ptr;
    sh_mem_ptr = mmap(0, sh_mem_size, PROT_READ | PROT_WRITE, MAP_SHARED, sh_mem_segment, 0);
    if (sh_mem_ptr == MAP_FAILED)
    {
        printf("In mmap() during write operation!\n");
        return EXIT_FAILURE;
    }

    int *data_ptr = (int *)sh_mem_ptr;
    data_ptr[addr] = data;

    close(sh_mem_segment);
    m.unlock();
    return EXIT_SUCCESS;
}

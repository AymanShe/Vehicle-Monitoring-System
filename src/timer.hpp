#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <stdint.h>
#include <ctime>


void wait_next_activation(void);
int start_periodic_timer(uint64_t offset, int period);
int run_periodically(uint64_t offset, int period, void (*func)());

#endif /*TIMER_HPP_*/

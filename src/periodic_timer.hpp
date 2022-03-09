#ifndef TIMERS_HPP_
#define TIMERS_HPP_

#include <stdint.h>

void wait_next_activation(void);
int start_periodic_timer(uint64_t offset, int period);
int run_periodically(uint64_t offset, int period, void (*func)());

#endif /*TIMERS_HPP_*/

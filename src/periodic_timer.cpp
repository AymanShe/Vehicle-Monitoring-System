#include <periodic_timer.hpp>
#include <sys/time.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ONE_THOUSAND 1000
#define ONE_MILLION 1000000

sigset_t sigst;

void wait_next_activation(void)
{
	int dummy;
	/* suspend calling process until a signal is pending */
	sigwait(&sigst, &dummy);
}

int start_periodic_timer(uint64_t offset, int period)
{
	struct itimerspec timer_spec;
	struct sigevent sigev;
	timer_t timer;
	const int signal = SIGALRM;
	int res;

	/* set timer parameters */
	timer_spec.it_value.tv_sec = offset / ONE_MILLION;
	timer_spec.it_value.tv_nsec = (offset % ONE_MILLION) * ONE_THOUSAND;
	timer_spec.it_interval.tv_sec = period / ONE_MILLION;
	timer_spec.it_interval.tv_nsec = (period % ONE_MILLION) * ONE_THOUSAND;

	sigemptyset(&sigst);				  // initialize a signal set
	sigaddset(&sigst, signal);			  // add SIGALRM to the signal set
	sigprocmask(SIG_BLOCK, &sigst, NULL); // block the signal

	/* set the signal event a timer expiration */
	memset(&sigev, 0, sizeof(struct sigevent));
	sigev.sigev_notify = SIGEV_SIGNAL;
	sigev.sigev_signo = signal;

	/* create timer */
	res = timer_create(CLOCK_MONOTONIC, &sigev, &timer);

	if (res < 0)
	{
		perror("Timer Create");
		exit(-1);
	}

	/* activate the timer */
	return timer_settime(timer, 0, &timer_spec, NULL);
}

int run_periodically(uint64_t offset, int period, void (*func)())
{
	int res;

	// set and activate a timer
	res = start_periodic_timer(offset, period);
	if (res < 0)
	{
		perror("Start periodic timer");
		return -1;
	}

	while (1)
	{
		wait_next_activation(); // wait for timer expiration
		func();					// executes the task
	}
	return 0;
}
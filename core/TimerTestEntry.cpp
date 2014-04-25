#include <stdio.h>
#include <stdlib.h>
#include "utility/Tools.h"
#include "utility/Pressure.h"

int TimerTestEntry(int argc, char* argv[])
{
	int i = 0;
	int nCount = atoi(argv[2]);
	int iDelayUSec[] = {
		500 * 1000, 
		100 * 1000, 
		50 * 1000,
		10 * 1000,
		5 * 1000, //select会10ms返回
		2 * 1000,
		//不再准确
		2 * 1000,
		1 * 1000,
		100, 
		10,
		1
	};
	int& nDelay = iDelayUSec[atoi(argv[1])];
	BEGIN_COST_CALCULATE("select");
	struct timeval delay;
	while (i < nCount)
	{
		delay.tv_sec = 0;
		delay.tv_usec = nDelay;
		select(0, NULL, NULL, NULL, &delay);
		i++;
	}
	END_COST_CALCULATE();

	BEGIN_COST_CALCULATE("usleep");
	i= 0;
	while (i < nCount)
	{
		usleep(nDelay);
		i++;
	}
	END_COST_CALCULATE();

	/*
	BEGIN_COST_CALCULATE("sleep");
	i= 0;
	while (i < 10)
	{
		sleep(1);
		i++;
	}
	END_COST_CALCULATE();
	*/

	BEGIN_COST_CALCULATE("nanosleep");
	i= 0;
	struct timespec req;
	struct timespec rem;
	rem.tv_sec = 0;
	rem.tv_nsec = 0;
	req.tv_sec = 0;
	req.tv_nsec = nDelay * 1000;

	while (i < nCount)
	{
		if (-1 == nanosleep(&req, &rem))
		{
			printf("%d, %d\n", rem.tv_sec, rem.tv_nsec);
			req.tv_sec = rem.tv_sec;
			req.tv_nsec = nDelay * 1000 + rem.tv_nsec;
		}
		else
		{
			req.tv_sec = 0;
			req.tv_nsec = nDelay * 1000;
		}
		i++;
	}
	END_COST_CALCULATE();

}

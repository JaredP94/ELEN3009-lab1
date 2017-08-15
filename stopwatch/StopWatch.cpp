#include "StopWatch.h"

// construct stopwatch object
stopwatch::stopwatch(){}

// returns the amount of time in seconds that has passed since the process (i.e. your program) started executing 
double stopwatch::getProcessTime()
{
	time = clock();
	return static_cast<double>(time)/CLOCKS_PER_SEC;
}

// sets starting point for timer
void stopwatch::start()
{
	total = getProcessTime();
}

// stops timer and displays result
double stopwatch::stop()
{
	return getProcessTime() - total;
}

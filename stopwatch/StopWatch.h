#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

class stopwatch
{
public:
	// stopwatch constructor
	stopwatch();
	// sets starting point for timer
	void start();
	// stops timer and return result
	double stop();
	
private:
	// gets time taken since program began
	double getProcessTime();
	clock_t time;
	double total;
};

#endif
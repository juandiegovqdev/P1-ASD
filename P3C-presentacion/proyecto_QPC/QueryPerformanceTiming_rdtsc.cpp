/////////////////////////////////////////////////////////
//  Dpto ATC. 
//  version 2. Nov. 2012. Fernando Diaz del Rio/Pablo Iñigo Blasco /Manuel J Dominguez Morales
/////////////////////////////////////////////////////////
// this timing library is based on C++ OpenCV timing function getCPUTickCount(), that are
// based on Windows x86 QueryPerformanceCounter library  .

// QueryPerformanceCounter  Granularity for x86 usually is 0.5 us approx.
//but here the CPU frequency must be defined in QueryPerformanceTiming_rdtsc.h

//	Note: getCPUTickCount() and rdtsc x86 instructions (time stamp counter) is finer but it depends strongly 
//  on current CPU frequency (that is variable in most current CPUs ), and measures
//  are not exact at all if CPU frequency does not match stock CPU (e.g if CPU load is low )
/////////////////////////////////////////////////////////


#include <stdio.h>

#include <iostream>

using namespace std;

#include "QueryPerformanceTiming_rdtsc.h"


#define MAX_DOUBLE_VALUE (1e+307)
/////////////////////////////////////////////////////////
//public methods 
/////////////////////////////////////////////////////////
QPTimer::QPTimer()
{
	minimumTime= MAX_DOUBLE_VALUE;
	times=0;
	overhead= 0.0;
	totalTime=0.0;
	Reset();
	QPFrequencyHz =  CPU_FREQ_HZ ;
	//QPFrequencyHz = getTickFrequency();
	DisableOutput=false;
}

void
	QPTimer::Start()
{
	ReadCycles(&startTime);
}

void
	QPTimer::Stop()
{
	double now;
	ReadCycles(&now);

	double r;
	RestCycles(&r,&now,&startTime);
	RestCycles(&r,&r,&overhead);

	AddCycles(&result,&result,&r);

	AddCycles(&totalTime,&totalTime,&r);

	if (minimumTime > result)
			minimumTime = result;

	times++;
}
///////////////////////////////////////////////////
void
	QPTimer::Calibrate()
{
	int test_times=50;
	overhead= MAX_DOUBLE_VALUE;

	for (int i=0; i<test_times; i++)
	{
		double r;
		double now;

		ReadCycles(&startTime);
		ReadCycles(&now);

		RestCycles(&r,&now,&startTime);
		
		if (overhead > r)
			overhead = r;
	}
	ResetAll();
}


void
	QPTimer::Reset()
{
	//startTime=0.0;
	result=0.0;
}

void
	QPTimer::ResetAll()
{
	//startTime=0.0;
	result=0.0;
	minimumTime=MAX_DOUBLE_VALUE;
	totalTime=0.0;

	times=0;
}

void 
	QPTimer:: PrintTime(const char* message)
{
	if(!DisableOutput)
		PrintTimeSeconds(message,&result);
}

void 
	QPTimer:: PrintCycles(const char* message)
{
	if(!DisableOutput)
		PrintCycles(message,&result);
}

void 
	QPTimer::PrintMinimumTime(const char* message)
{
	if(!DisableOutput)
		PrintTimeSeconds(message,&minimumTime);
}

void 
	QPTimer::PrintMinimumCycles(const char* message)
{
	if(!DisableOutput)
		PrintCycles(message,&minimumTime);
}

void 
	QPTimer::PrintMinimumCyclesByIteration(const char* message, int num)
{
	if(!DisableOutput)
		PrintCyclesByIteration(message,&minimumTime,num);
}

void
	QPTimer::PrintMeanTime(const char* message)
{
	if(!DisableOutput)
	{
		double MeanTime ;
		MeanTime = (totalTime/times);

		PrintTimeSeconds(message,&MeanTime);
		cout << "   (in " << times << " measures)" <<endl;
	}
}

void 
	QPTimer::PrintMeanCycles(const char* message)
{
	if(!DisableOutput)
	{
		double MeanCycles ;
		MeanCycles = (totalTime/times);

		PrintCycles(message,&MeanCycles );
		cout << "   (in " << times << " measures)" <<endl;
	}
}
int  QPTimer::NumberOfMeasures(void) 
{
	return times;
}

/////////////////////////////////////////////////////////
//private methods 
/////////////////////////////////////////////////////////

void QPTimer::ReadCycles (double *cycles)
{
	_int64 time;
	unsigned int t_high, t_low;

	__asm { 
		rdtsc
		mov t_low, eax
		mov t_high, edx
	}
	time = (_int64)t_low | ((_int64)t_high << 32);
	 *cycles = (double) time;
	
}
//void 
//	QPTimer::ReadCycles (double *cycles)
//{
//	// No serializing instruction: there is no flush of pipeline processor
//	// OpenCV timing. It uses QueryPerformanceCounter. Granularity for x86 usually is 0.5 us approx.
////	*cycles = (double)getTickCount();
//	*cycles = (double)getCPUTickCount();
//	
//}

void 
	QPTimer::PrintCycles (const char *pc, double *cycles)
{
	cout << pc << *cycles << endl;
}	


void 
	QPTimer::PrintCyclesByIteration (const char *pc, double *cycles, int NumberOfIterations)
{
	cout << pc << *cycles/(double)NumberOfIterations << endl;
}	

		

void 
	QPTimer::PrintTimeSeconds (const char *pc, double *cycles)
{   
	cout << pc << *cycles/QPFrequencyHz << endl;
/*	if(pc!=NULL && strlen(pc)>0)
		printf("%s",pc);		*/
}
void 
	QPTimer::RestCycles (double *c_dif, double *c_final, double *c_init)
{
	*c_dif=*c_final-*c_init;

}

void QPTimer::AddCycles (double *c_add, double *c_final, double *c_init)
{
	*c_add=*c_final+*c_init;
}
/////////////////////////////////////////////////////////
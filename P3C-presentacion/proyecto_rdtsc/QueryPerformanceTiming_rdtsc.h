/////////////////////////////////////////////////////////
//  Dpto ATC. 
//  version 2. Nov. 2012. Fernando Diaz del Rio/Pablo Iñigo Blasco /Manuel J Dominguez Morales
/////////////////////////////////////////////////////////
// this timing library is based on C++ OpenCV timing function getCPUTickCount(),
// this test uses a new version of QueryPerformanceTiming_rdtsc, to measure CPU cycles more precisely
// based on Windows x86 QueryPerformanceCounter library  .

// QueryPerformanceCounter  Granularity for x86 usually is 0.5 us approx.
//but here the CPU frequency must be defined in QueryPerformanceTiming_rdtsc.h

//	Note: getCPUTickCount() and rdtsc x86 instructions (time stamp counter) is finer but it depends strongly 
//  on current CPU frequency (that is variable in most current CPUs ), and measures
//  are not exact at all if CPU frequency does not match stock CPU (e.g if CPU load is low )
/////////////////////////////////////////////////////////

#pragma once
#include <Windows.h>
#include <stdio.h>

#define CPU_FREQ_HZ (2.800e+9)
//#define CPU_FREQ_HZ (3.20e+9)
//write here your CPU frequency 


 class QPTimer
{
	private:
		DWORD64 startTime; //it contains the real timer (that was started when PC was switch on
		DWORD64 result;    // a partial timing between Start() and Stop()
		DWORD64 totalTime;  // the addition of several partial timing (result). It is the total time since timer was created or ResetAll
		DWORD64 minimumTime;
		DWORD64 overhead;
		int times;

		void ReadCycles (DWORD64 *cycles);
		void PrintCycles (const char *pc, double cycles);
		void PrintCyclesByIteration (const char *pc, double cycles, int NumberOfIterations);
		void PrintTimeSeconds (const char *pc, double cycles);
		void RestCycles (DWORD64 *c_dif, DWORD64 c_final, DWORD64 c_init);
		void AddCycles (DWORD64 *c_dif, DWORD64 c_final, DWORD64 c_init);
	public:
		double QPFrequencyHz;
		bool DisableOutput;
		QPTimer();
		int  NumberOfMeasures(void);
		void Start();
		void Stop();
		
		void Calibrate();
		void Reset();
		void ResetAll();
		void PrintTime(const char* message);
		void PrintCycles(const char* message);
		void PrintMeanTime(const char* message);
		void PrintMeanCycles(const char* message);
		void PrintMinimumTime(const char* message);
		void PrintMinimumCycles(const char* message);

		void PrintMinimumCyclesByIteration (const char* message, int NumberOfIterations);
};
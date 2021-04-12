//----------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Dpto ATC. www.atc.us.es 
//  ASD subject 3º GTI
//  version 1. Nov. 2012. Fernando Diaz del Rio
//  version 2a. March. 2017. Fernando Diaz del Rio
//  
//  - Doing several test to reach ILP limits in superscalar processor 
//  - TEST TIMING OF simple routines 
//  - this test uses a new version of QueryPerformanceTiming , to measure CPU cycles more precisely using RDTSC asm instr.
//		Sometimes RDTSC fails and returns values smaller than expected. In this case try the other version of this test (p3c_proy_QPC_alumnos.zip)
//
//  Debug mode of VS is very slow (it only serves to check bugs in the code)
//  Uses Release mode of VS to measure times 
//-----------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>

using namespace std;
//------------------------------------------------------------------
// project def and includes

// this test uses a new version of QueryPerformanceTiming , to measure CPU cycles more precisely using rdtsc asm instr.
#include "QueryPerformanceTiming_rdtsc.h"

#define  N_REPETIC 256
// repeat several times each test to extract the minimum time
// and to have the caches filled

#define  N_ELEM (1024*2)
//big number to have a mean time (but not very big to avoid cache misses) 

__declspec(align(64)) int a_int[N_ELEM ], b_int[N_ELEM ];

__declspec(align(64)) float a[N_ELEM ], b[N_ELEM ];
__declspec(align(64)) float c[N_ELEM ], d[N_ELEM ];
__declspec(align(64)) float e[N_ELEM ], f[N_ELEM ];
__declspec(align(64)) float g[N_ELEM ], h[N_ELEM ];
float z;

__declspec(align(64)) int cond1[N_ELEM ], cond2[N_ELEM ], cond3[N_ELEM ];

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// vectors  init
void vectors_init ()
{
	int i;
	for (i=0;i<N_ELEM;i++)
	{
		// a[i] must have little values to avoid overflow in pp1()
		a[i]=(float)rand()/(float)RAND_MAX;
		b[i]=(float)i/5;
		c[i]=(float)i/6;
		d[i]=(float)i/7;
		e[i]=(float)i/8;
		f[i]=(float)i/9;
		g[i]=(float)i/10;
		h[i]=(float)i/11;

		a_int[i]=i;

		cond1[i]=1;
		cond3[i]=rand()%2;
	}

	for (i=0;i<N_ELEM;i+=8)
	{
		// put here the pattern behaviour  you want; BTB is very clever !!
		cond2[i+0]=1;
		cond2[i+1]=0;
		cond2[i+2]=1;
		cond2[i+3]=1;
		cond2[i+4]=0;
		cond2[i+5]=1;
		cond2[i+6]=1;
		cond2[i+7]=1;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// tests
float problem ()
{
	int  i;
	float z = 0.0; 

	for (i=0;i<N_ELEM;i++)
	{
		// Put your code here

	}

	// IMPORTANT : Always return a value
	return z; // Replace returned value
}

float example ()
{
	int i;

	for (i=0;i<N_ELEM;i++)
	{
		a[i]=b[i]+8;
	}
	
	// IMPORTANT : Always return a value
	return a[N_ELEM-1 ];
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main( int argc, char** argv ) {

	float var1, var2;
	int i;

	QPTimer c1, c2;

	c1.Calibrate(); //calibrates timer overhead and set cronometer to zero	
	// measuring tests
	for (i=0;i<N_REPETIC;i++)
	{
		vectors_init ();
		c1.Start();  // start timer
		var1=example(); // Do the test
		c1.Stop();  // stop timer
		c1.Reset();
	} 
	// end of    testing

	c2.Calibrate(); //calibrates timer overhead and set cronometer to zero	
	// measuring tests
	for (i=0;i<N_REPETIC;i++)
	{
		vectors_init ();
		c2.Start();  // start timer
		var2=problem(); // Do the test
		c2.Stop();  // stop timer
		c2.Reset();
	} 
	// end of    testing

	cout << endl << "ONLY PRINTING OUTPUT VARIABLE TO PREVENT THAT THE COMPILER ELIMINATES FUNCTION CALLS: " 
		<< var1 << ", " << var2 << endl;

	cout << "-Number of elements N_ELEM: " << N_ELEM << endl;
	cout << "-Number of measures example: " << c1.NumberOfMeasures() << endl;
	cout << "-Number of measures problem: " << c2.NumberOfMeasures() << endl;
	cout << endl;

	// uncomment this if more timing results were needed:
	/*c1.PrintMinimumTime   (" Minimum time in seconds for example is:   ");
	c1.PrintMeanTime      (" Mean time in seconds    for example is:   ");

	c2.PrintMinimumCycles (" Minimum time in cycles for problem  is:   ");
	c2.PrintMeanCycles    (" Mean time in cycles for problem is    :   ");
	*/

	c1.PrintMinimumCyclesByIteration  (" Minimum time in cycles for an element of 'example' is: ", N_ELEM);
	cout << endl  ;

	c2.PrintMinimumCyclesByIteration  (" Minimum time in cycles for an element of 'problem' is: ", N_ELEM);
	cout << endl;
	cout << endl;
}

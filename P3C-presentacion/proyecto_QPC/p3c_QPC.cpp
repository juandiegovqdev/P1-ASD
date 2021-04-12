//----------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Dpto ATC. www.atc.us.es 
//  ASD subject 3º GTI
//  version 2b. March 2017. Fernando Diaz del Rio
//  
//  - Doing several test to reach ILP limits in superscalar processor 
//  - TEST TIMING OF simple routines 
//  - this test uses the QPC (QueryPerformanceCounters) to measure elapsed microseconds (us). 
//		It is not valid for tests that  last less than one us
//		Because of this, the number of elements must be big (e.g. #define  N_ELEM (1024*4) )
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

double MideRetraso(char * pMensaje);

#define  CPU_FREQ_HZ (3.1e+9)

#define  N_REPETIC 15
// repeat several times each test to extract the minimum time
// and to have the caches filled

#define  N_ELEM (1024*4)
//big number to have a mean time (but not very big to avoid cache misses) 

int a_int[N_ELEM ], b_int[N_ELEM ];

float a[N_ELEM ], b[N_ELEM ];
float c[N_ELEM ], d[N_ELEM ];
float e[N_ELEM ], f[N_ELEM ];
float g[N_ELEM ], h[N_ELEM ];
float z;

int cond1[N_ELEM ], cond2[N_ELEM ], cond3[N_ELEM ];

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

double calibrating_QPC_timer(void)
{
double local_overhead_time_crono, local_mean_overhead_time_crono = 0.0;
//calibrating the cronometer, that is measuring the time the own crono lates.
for (int i = 0; i < 50; i++)
{
	local_overhead_time_crono = MideRetraso("");  // start timer. Returned variable is not useful in the first call
	local_overhead_time_crono = MideRetraso("");  // end timer
	local_mean_overhead_time_crono += local_overhead_time_crono;
}
return (local_mean_overhead_time_crono / 50 );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main( int argc, char** argv ) {

	float var1, var2;
	int i;
	double pp, elapsed_time_example, elapsed_time_problem;
	double min_elapsed_time_example = 1.0e+300, min_elapsed_time_problem = 1.0e+300;
	double min_elapsed_time_example_per_iter, min_elapsed_time_problem_per_iter;

	double mean_overhead_time_crono ;

	//calibrating the cronometer, that is measuring the time the own crono lates.
	mean_overhead_time_crono = calibrating_QPC_timer();

	// measuring tests
	for (i=0;i<N_REPETIC;i++)
	{
		vectors_init ();
		pp = MideRetraso("");  // start timer. Returned variable is not useful
		var1=example(); // Do the test
		elapsed_time_example = MideRetraso("");  // end timer
		if (elapsed_time_example < min_elapsed_time_example) min_elapsed_time_example = elapsed_time_example ;
	}
	// end of    testing

	// measuring tests
	for (i=0;i<N_REPETIC;i++)
	{
		vectors_init ();
		pp = MideRetraso("");  // start timer. Returned variable is not useful
		var2=problem(); // Do the test
		elapsed_time_problem = MideRetraso("");  // end timer
		if (elapsed_time_problem < min_elapsed_time_problem) min_elapsed_time_problem = elapsed_time_problem;
	}
	// end of    testing

	cout << endl << "ONLY PRINTING OUTPUT VARIABLE TO PREVENT THAT THE COMPILER ELIMINATES FUNCTION CALLS: " 
		<< var1 << ", " << var2 << endl;

	cout << endl << "-Number of elements N_ELEM: " << N_ELEM << endl;
	cout << "-Number of measures example: " << N_REPETIC << endl;
	cout << "-Number of measures problem: " << N_REPETIC << endl << endl;

	min_elapsed_time_example_per_iter = (min_elapsed_time_example - mean_overhead_time_crono) / (double)N_ELEM;
	cout << " Minimum time in Seconds for an element of 'example' is: " << min_elapsed_time_example_per_iter;
	cout << endl  ;
	cout << " Minimum time in Cycles for an element of 'example' is: " << (CPU_FREQ_HZ) * min_elapsed_time_example_per_iter;
	cout << endl;
	
	min_elapsed_time_problem_per_iter = (min_elapsed_time_problem - mean_overhead_time_crono) / (double)N_ELEM;
	cout << " Minimum time in Seconds for an element of 'problem' is: " << min_elapsed_time_problem_per_iter;
	cout << endl  ;
	cout << " Minimum time in Cycles for an element of 'problem' is: "  << (CPU_FREQ_HZ)* min_elapsed_time_problem_per_iter;
	cout << endl;
	cout << endl;
}

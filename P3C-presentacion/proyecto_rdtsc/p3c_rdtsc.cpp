//----------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Dpto ATC. www.atc.us.es
//  ASD subject 3º GTI
//  
//  - Doing several test to reach ILP limits in superscalar processor 
//  - TEST TIMING OF simple routines 
//  - this test uses a new version of QueryPerformanceTiming , to measure CPU cycles more precisely using RDTSC asm instr.
//		Sometimes RDTSC fails and returns values smaller than expected. In this case try the other version of this test (p3c_proy_QPC_alumnos.zip)
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

#define  N_ELEM (1024)
//big number to have a mean time (but not very big to avoid cache misses) 

__declspec(align(64)) int a_int[N_ELEM], b_int[N_ELEM];

__declspec(align(64)) float a[N_ELEM], b[N_ELEM];
__declspec(align(64)) float c[N_ELEM], d[N_ELEM];
__declspec(align(64)) float e[N_ELEM], f[N_ELEM];
__declspec(align(64)) float g[N_ELEM], h[N_ELEM];
float z;

__declspec(align(64)) int cond1[N_ELEM], cond2[N_ELEM], cond3[N_ELEM];

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// vectors  init
void vectors_init() {
	int i;
	for (i = 0; i < N_ELEM; i++) {
		// a[i] must have little values to avoid overflow in pp1()
		a[i] = (float)rand() / (float)RAND_MAX;
		b[i] = (float)i / 5;
		c[i] = (float)i / 6;
		d[i] = (float)i / 7;
		e[i] = (float)i / 8;
		f[i] = (float)i / 9;
		g[i] = (float)i / 10;
		h[i] = (float)i / 11;

		cout << "a[i]: " << a[i];

		a_int[i] = i;

		cond1[i] = 1;
		cond3[i] = rand() % 2;
	}
	for (i = 0; i < N_ELEM; i += 8) {
		// put here the pattern behaviour  you want; BTB is very clever !!
		cond2[i + 0] = 1;
		cond2[i + 1] = 0;
		cond2[i + 2] = 1;
		cond2[i + 3] = 1;
		cond2[i + 4] = 0;
		cond2[i + 5] = 1;
		cond2[i + 6] = 1;
		cond2[i + 7] = 1;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Funciones con el problema a solucionar.
float apartadoA() {
	int  i;
	float z = 0.0;
	for (i = 0; i < N_ELEM; i++) {
		z = z + a[i];
	}
	return z;
}

float apartadoBPrimeraOpcion() {
	int  i;
	float z = 0.0;
	for (i = 0; i < N_ELEM; i++) {
		z = (z + a[i]) + b[i];
	}
	return z;
}

float apartadoBSegundaOpcion() {
	int  i;
	float z = 0.0;
	for (i = 0; i < N_ELEM; i++) {
		z = (z + a[i]) + 3.0;
	}
	return z;
}

float apartadoCPrimeraCond() {
	int  i;
	float z = 0.0;
	for (i = 0; i < N_ELEM; i++) {
		if (cond3) {
			z = z + a[i];
		}
	}
	return z;
}

float apartadoCSegundaCond() {
	int  i;
	float z = 0.0;
	for (i = 0; i < N_ELEM; i++) {
		if (cond1) {
			z = z + a[i];
		}
	}
	return z;
}

float example() {
	int i;
	for (i = 0; i < N_ELEM; i++) {
		a[i] = b[i] + 8;
	}
	return a[N_ELEM - 1];
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv) {
	float var1, var2, var3, var4, var5, var6;
	int i;
	QPTimer c1, c2, c3, c4, c5, c6;

	c1.Calibrate();
	for (i = 0; i < N_REPETIC; i++) {
		vectors_init();
		c1.Start();
		var1 = example();
		c1.Stop();
		c1.Reset();
	}

	c2.Calibrate();
	for (i = 0; i < N_REPETIC; i++) {
		vectors_init();
		c2.Start();
		var2 = apartadoA();
		c2.Stop();
		c2.Reset();
	}

	c3.Calibrate();
	for (i = 0; i < N_REPETIC; i++) {
		vectors_init();
		c3.Start();
		var3 = apartadoBPrimeraOpcion();
		c3.Stop();
		c3.Reset();
	}

	c4.Calibrate();
	for (i = 0; i < N_REPETIC; i++) {
		vectors_init();
		c4.Start();
		var4 = apartadoBSegundaOpcion();
		c4.Stop();
		c4.Reset();
	}

	c5.Calibrate();
	for (i = 0; i < N_REPETIC; i++) {
		vectors_init();
		c5.Start();
		var5 = apartadoCPrimeraCond();
		c5.Stop();
		c5.Reset();
	}

	c6.Calibrate();
	for (i = 0; i < N_REPETIC; i++) {
		vectors_init();
		c6.Start();
		var6 = apartadoCSegundaCond();
		c6.Stop();
		c6.Reset();
	}

	cout << endl << "ONLY PRINTING OUTPUT VARIABLE TO PREVENT THAT THE COMPILER ELIMINATES FUNCTION CALLS: "
		<< "\n" << "var1: " << var1 << "\nvar2: " << var2 << "\nvar3: " << var3 << "\nvar4: " << var4 << "\nvar5: " << var5 << "\nvar6: " << var6 << endl;

	cout << "-Number of elements N_ELEM: " << N_ELEM << endl;
	cout << "-Number of measures example: " << c1.NumberOfMeasures() << endl;
	cout << "-Number of measures apartadoA: " << c2.NumberOfMeasures() << endl;
	cout << "-Number of measures apartadoBPrimeraOpcion: " << c3.NumberOfMeasures() << endl;
	cout << "-Number of measures apartadoBSegundaOpcion: " << c4.NumberOfMeasures() << endl;
	cout << "-Number of measures apartadoCPrimCond: " << c5.NumberOfMeasures() << endl;
	cout << "-Number of measures apartadoCSegCond: " << c6.NumberOfMeasures() << endl;
	cout << endl;

	c1.PrintMinimumCyclesByIteration(" Minimum time in cycles for an element of 'example' is: ", N_ELEM);
	cout << endl;

	c2.PrintMinimumCyclesByIteration(" Minimum time in cycles for an element of 'apartadoA' is: ", N_ELEM);
	cout << endl;

	c3.PrintMinimumCyclesByIteration(" Minimum time in cycles for an element of 'apartadoBPrimeraOpcion' is: ", N_ELEM);
	cout << endl;

	c4.PrintMinimumCyclesByIteration(" Minimum time in cycles for an element of 'apartadoBSegudaOpcion' is: ", N_ELEM);
	cout << endl;

	c5.PrintMinimumCyclesByIteration(" Minimum time in cycles for an element of 'apartadoCPrimCond' is: ", N_ELEM);
	cout << endl;

	c6.PrintMinimumCyclesByIteration(" Minimum time in cycles for an element of 'apartadoCSegCond' is: ", N_ELEM);
	cout << endl;
}
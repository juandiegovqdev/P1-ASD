//MideRetraso (QueryPerformanceCounter).cpp
/*
Prof. Claudio Amaya. Dpto ATC. Univ. Sevilla. Enero 2017.
Prof. Fernando Diaz. Dpto ATC. Univ. Sevilla. marzo 2017.

Función para medir tiempos, que usa QueryPerformanceCounter (precisión de 1 us):
-  MideRetraso es la versión básica.
	(existe otra MideRetrasoTS es la versión Thread Safe). 

	MideRetraso usa internamente variables estáticas, de forma que sirve para medir tiempos en un sistema mono hilo o multihilo 
	cuando no se quiere medir tiempos en los hilos de forma independiente.
*/

#include <stdio.h>
#include <windows.h>
#include <winnt.h>

#define MAX_DBG_STR 2048

double MideRetraso(char * pMensaje);

// Devuelve retraso (segundos) desde la última llamada a MideRetraso. El valor de la primera llamada debe ignorarse. 
// Si pMensaje es distinto de NULL y distinto de "", muestra un mensaje por la ventana de depuración (Salida)
// de VisualStudio con los segundos transcurridos desde la última llamada

double MideRetraso(char * pMensaje)
{
         static LARGE_INTEGER Antes, Frecuencia;
         LARGE_INTEGER Ahora;
         static BOOL Primera = TRUE;
         double Segs;

         QueryPerformanceCounter(&Ahora);

         if (Primera)
         {
                 QueryPerformanceFrequency(&Frecuencia);
                 Segs = 0.0;
                 Primera = FALSE;
         }
         else
         {
                 Segs = (double)(Ahora.QuadPart - Antes.QuadPart) / (double)Frecuencia.QuadPart;
         }

         Antes = Ahora;

		 // Imprime por OutputDebugString. 
         if (pMensaje != NULL && pMensaje[0] != 0)
         {
                 char Cad[MAX_DBG_STR + 1];
                 sprintf(Cad, "%s: %f.(usuario bb_demo)\n", pMensaje, Segs);
                 OutputDebugString( (LPCWSTR) Cad);
         }
         return Segs;
}

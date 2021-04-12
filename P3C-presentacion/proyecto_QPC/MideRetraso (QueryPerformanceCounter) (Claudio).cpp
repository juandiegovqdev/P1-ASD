//MideRetraso (QueryPerformanceCounter).cpp
/*
Prof. Claudio Amaya. Dpto ATC. Univ. Sevilla. Enero 2017.

Hay 2 versiones de la función para medir tiempos:

·         MideRetraso es la versión básica.

·         MideRetrasoTS es la versión Thread Safe. 

MideRetraso usa internamente variables estáticas, de forma que sirve para medir tiempos en un sistema mono hilo o multihilo cuando no se quiere medir tiempos en los hilos de forma independiente.

MideRetrasoTS no tiene variables estáticas (solo Frecuencia, con el mismo valor en todos los hilos). Para medir tiempos dentro de un hilo, este define una variable __int64 privada (local, por ejemplo), la pone a 0, y mientras use MideRetrasoTS con esa variable medirá su propio tiempo de retraso. Cada hilo puede medir tiempos por separado si usa variables distintas.
*/
 

double MideRetraso(LPCTSTR pMensaje);

double MideRetrasoTS(__int64 * pA0PrimeraLlamada, LPCTSTR pMensaje);

// Devuelve retraso (segundos) desde la última llamada a MideRetraso. El valor de la primera llamada debe ignorarse. 

// Si pMensaje es distinto de NULL y distinto de "", muestra un mensaje por la ventana de depuración (Salida)

// de VisualStudio con los segundos transcurridos desde la última llamada

double MideRetraso(LPCTSTR pMensaje)

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

                 snprintf(Cad, sizeof(Cad), "%s: %f.(usuario bb_demo)\n", pMensaje, Segs);

                 OutputDebugString(Cad);

         }

         return Segs;

}

// Igual que la anterior, pero thread safe. Cada hilo puede llevar su propia cuenta de tiempos si 

// pasa una variable distinta en pA0PrimeraLlamada.

// La primera vez, debe llamarse con *pA0PrimeraLlamada = 0.

/// MUY IMPORTANTE: el parámetro debe ser __int64, no int

double MideRetrasoTS(__int64 * pA0PrimeraLlamada, LPCTSTR pMensaje)

{

         static LARGE_INTEGER Frecuencia;

         LARGE_INTEGER Ahora;

         double Segs;

 

         QueryPerformanceCounter(&Ahora);

         if (*pA0PrimeraLlamada ==0)

         {

                 QueryPerformanceFrequency(&Frecuencia);

                 Segs = 0.0;

         }

         else

         {

                  Segs = (double)(Ahora.QuadPart - *pA0PrimeraLlamada) / (double)Frecuencia.QuadPart;

         }

         *pA0PrimeraLlamada = Ahora.QuadPart;

         // Imprime por OutputDebugString. 

         if (pMensaje != NULL && pMensaje[0] != 0)

         {

                 char Cad[MAX_DBG_STR + 1];

                 snprintf(Cad, sizeof(Cad), "%s: %f.(usuario bb_demo)\n", pMensaje, Segs);

                 OutputDebugString(Cad);

         }

         return Segs;

}

 

 

 

 

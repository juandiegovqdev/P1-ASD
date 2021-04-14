# Arquitectura de Sistemas Distribuídos
### Primero proyecto en grupo.
### Realizado por: Enrique García y Juan Diego Villalobos

## Objetivos del proyecto.
- Resolver el problema asignado.
- Descubrir si el problema es totalmente “paralelizable”.
- Si el código  tiene saltos condicionales dentro del bucle o instrucciones que puedan bloquear la CPU.
- Analizar el comportamiento del código proporcionado como ejemplo (example()), y explicar las diferencias obtenidas.

## Qué resultados tenemos que anotar
-  Máquina (sobre todo procesador). Para ello, podemos usar CPU-Z.
- Compilador y Opciones de optimizaciones usadas (sólo si algún grupo usa otro que no sea el del proyecto suministrado).
- Código de C usados en los búcles.
-  Códigos de Ensamblador del x86 que crean interesantes para explicar los resultados de tiempo.
- Duración en ciclos por iteración (del for) de todos los bucles
- Realizar pruebas con tamaños mayores de vectores (cambiar valor de la constante N_ITER)
- Intente calcular el flujo de datos y encontrar el camino crítico y la UF (unidad funcional) de cada prueba. Recuerde los 5 tipos
de bloqueo cuando se alcanza algún límite del ILP (última transparencia “Casos de estudio” de ASD tema 2 Técnicas
dinámicas TFG.pdf)
- Explicar la causa de la duración y las variaciones (si las hay) que se encuentran al cambiar de código y al aumentar N_ITER
(estudiar el efecto de los accesos a caché y a RAM).
- Y por supuesto cualquier otro resultado que considere importante...

## Hardware usado
### Enrique García

- Procesador:
- Velocidad de reloj: 

### Juan Diego Villalobos

- Procesador: Intel Core i5
- Velocidad de reloj: 4GHz

## Mediciones

### Juan Diego, primera ejecución
- example: 3.93066
- apartadoA: 2.9082
- apartadoBPrimeraOpcion: 5.81396
- apartadobSegundaOpcion: 3.271
- apartadoCPrimCond: 2.90674
- apartadoCSegCond: 2.90723

### Juan Diego, segunda ejecución

- example: 3.64746
- apartadoA: 2.83789
- apartadoBPrimeraOpcion: 5.67285 
- apartadobSegundaOpcion: 3.271
- apartadoCPrimCond: 2.90625
- apartadoCSegCond: 2.90771

### Juan Diego, tercera ejecución

- example: 3.65723
- apartadoA: 2.90771
- apartadoBPrimeraOpcion: 5.81445
- apartadobSegundaOpcion: 3.27051
- apartadoCPrimCond: 2.90723
- apartadoCSegCond: 2.90723

### Juan Diego, cuarta ejecución

- example: 4.36133
- apartadoA: 2.9082
- apartadoBPrimeraOpcion: 5.81396
- apartadobSegundaOpcion: 3.27197
- apartadoCPrimCond: 2.90723
- apartadoCSegCond: 2.9082

### Juan Diego, media

- example: 
- apartadoA: 
- apartadoBPrimeraOpcion:
- apartadobSegundaOpcion: 
- apartadoCPrimCond: 
- apartadoCSegCond: 

### Enrique, primera ejecución

- example: 2.6543
- apartadoA: 2.12012
- apartadoBPrimeraOpcion: 4.23975
- apartadobSegundaOpcion: 2.38916
- apartadoCPrimCond: 2.11963
- apartadoCSegCond: 2.11963

### Enrique, segunda ejecución

- example: 2.62842
- apartadoA: 2.12061
- apartadoBPrimeraOpcion: 4.23877
- apartadobSegundaOpcion: 2.38672
- apartadoCPrimCond: 2.11963
- apartadoCSegCond: 2.11914

### Enrique, tercera ejecución

- example: 2.65381
- apartadoA: 2.12061
- apartadoBPrimeraOpcion: 4.23877
- apartadobSegundaOpcion: 2.38525
- apartadoCPrimCond: 2.11963
- apartadoCSegCond: 2.12012

### Enrique, cuarta ejecución

- example: 2.66406
- apartadoA: 2.12061
- apartadoBPrimeraOpcion: 4.23926
- apartadobSegundaOpcion: 2.38574
- apartadoCPrimCond: 2.12012
- apartadoCSegCond: 2.11963

### Enrique, media 

- example: 2.65015
- apartadoA: 2.12049
- apartadoBPrimeraOpcion: 4.23914
- apartadobSegundaOpcion: 2.38672
- apartadoCPrimCond: 2.11975
- apartadoCSegCond: 2.11963

## Problema a resolver

Sumatorio de los elementos de un vector. Probar al menos con:
a. Una sola suma por iteración (sumatorio).
b. Dos sumas por iteración. Por ejemplo, la suma de dos vectores sobre el mismo acumulador, la suma de una constante y de un vector. Atención: se puede escribir de varias formas, por ejemplo: a) z=z+(a[i]+b[i]); b) z=(z+a[i])+b[i]; etc. O
bien: a) z=z+(a[i]+3.0); b) z=(z+a[i])+3.0; etc.
c. Una suma condicional por iteración. Es decir, en cada iteración, al acumulador se le sumará el elemento de un vector o el
de otro en función de que una condición sea cierta o falsa. Probar con dos tipos de condiciones del if():
i.La condición sea difícilmente predecible (p. ej. Random). Cuidado: no introducir la llamada a función rand() (o
similar) en el cuerpo del bucle (tarda mucho).
ii.La condición sea fácilmente predecible por la BTB.
Para la condición del if() hay varios vectores definidos: uno de ellos (cond1) con valores muy fácilmente predecibles, cond3
usa valores aleatorios, dificilmente predecibles, y cond2 usa valores predecibles (forman un patrón), así que puede preguntar
por el valor de los elementos de esos vectores. Ver la fase de inicialización de vectores en el código fuente para más detalles
(y para cambiar el patrón en cond2).
Pruebe a desactivar el uso de instrucciones mejorado (/arch:IA32 en lugar de /arch:SSE). ¿A qué se deben las diferencias en
los tiempos observados, sobre todo cuando se usa una condición dificilmente predecible por la BTB?
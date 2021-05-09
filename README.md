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

- Procesador: Intel Core i5-8250U (8 CPUs)
- Caché: 
- Velocidad de reloj: 1.8 GHz (TurboBoost a 3.3 GHz)

### Juan Diego Villalobos

- Procesador: Intel Core i5-10400 (12 CPUs)
- Caché: 
- Velocidad de reloj: 2.9GHz (TurboBoost a 4GHz)

## Mediciones

### Juan Diego, primera ejecución
- example(): 3.6665
- apartadoA(): 2.90771
- apartadoBPrimeraOpcion(): 5.81396
- apartadobSegundaOpcion(): 3.27197
- apartadoCPrimCond(): 2.90869
- apartadoCSegCond(): 2.90771

### Juan Diego, segunda ejecución

- example: 3.6665
- apartadoA: 2.90723
- apartadoBPrimeraOpcion: 5.8125
- apartadobSegundaOpcion: 3.27295
- apartadoCPrimCond: 2.90869
- apartadoCSegCond: 2.90771

### Juan Diego, tercera ejecución

- example: 3.86963
- apartadoA: 2.90723
- apartadoBPrimeraOpcion: 5.81299
- apartadobSegundaOpcion: 3.27246
- apartadoCPrimCond: 2.9082
- apartadoCSegCond: 2.90723

### Juan Diego, cuarta ejecución

- example: 3.84473
- apartadoA: 2.9082
- apartadoBPrimeraOpcion: 5.8125
- apartadobSegundaOpcion: 3.27295
- apartadoCPrimCond: 2.90723
- apartadoCSegCond: 2.90527

### Juan Diego, media

- example: 3.76184
- apartadoA: 2.90759
- apartadoBPrimeraOpcion: 3.27258
- apartadobSegundaOpcion: 2.90820
- apartadoCPrimCond: 2.90820
- apartadoCSegCond: 2.90698

### Enrique, primera ejecución

- example: 3.77393
- apartadoA: 3.00391
- apartadoBPrimeraOpcion: 6.00586
- apartadobSegundaOpcion: 3.38086
- apartadoCPrimCond: 3.00537
- apartadoCSegCond: 3.00342

### Enrique, segunda ejecución

- example: 3.7749
- apartadoA: 3.00293
- apartadoBPrimeraOpcion: 6.00635
- apartadobSegundaOpcion: 3.37891
- apartadoCPrimCond: 3.00439
- apartadoCSegCond: 3.00391
### Enrique, tercera ejecución

- example: 3.77393
- apartadoA: 3.11182
- apartadoBPrimeraOpcion: 6.00732
- apartadobSegundaOpcion: 3.3833
- apartadoCPrimCond: 3.00391
- apartadoCSegCond: 3.00342

### Enrique, cuarta ejecución

- example: 3.69908
- apartadoA: 2.99854
- apartadoBPrimeraOpcion: 6.00684
- apartadobSegundaOpcion: 3.3833
- apartadoCPrimCond: 3.00488
- apartadoCSegCond: 3.00342

### Enrique, media 

- example: 3.75546
- apartadoA: 3.0293
- apartadoBPrimeraOpcion: 6.006592
- apartadobSegundaOpcion: 3.381593
- apartadoCPrimCond: 3.004637
- apartadoCSegCond: 3.003542

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
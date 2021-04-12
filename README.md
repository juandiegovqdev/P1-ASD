# P1-ASD

## Objetivos del proyecto.
- Resolver el problema asignado.
- Descubrir si el problema es totalmente “paralelizable”.
- Si el código  tiene saltos condicionales dentro del bucle o instrucciones que puedan bloquear la CPU.
- Analizar el comportamiento del código proporcionado como ejemplo (example()), y explicar las diferencias obtenidas.
- 
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

## Realizar presentación en PowerPoint

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

# Investigación de teoría de la computación

**Elaborado por:** 
Erik Kuhlmann B84175
Adrián Sibaja B87561

## Planteamiento del problema 

El trabajo de investigación consiste en utilizar algoritmos heurísticos para resolver un problema de la familia del knapsack (mochila).

Específicamente, se tiene un conjunto de 10000 números positivos, los cuales se quieren dividir en 3 subconjuntos disjuntos tales que todo número de la lista pertenece a un solo subconjunto y la suma de números en cada subconjunto sea lo más parecida posible a la de los otros dos subconjuntos. Si hay números repetidos, es claro que algunos pueden estar en un subconjunto y otros en otro.

Si la suma de los valores en cada subconjunto es s1, s2 y s3, queremos minimizar la suma de cuadrados de sus diferencias: f(s1, s2, s3) = (s1 - s2)^2 + (s1 - s3)^2 + (s2 - s3)^2.

## Descripción general del proyecto

Los algoritmos heurísticos escogidos fueron: el **algoritmo genético** y el algoritmo de recocido simulado (**Simulated annealing**).

## Instrucciones de ejecución

```c++
- make
- ./tarea_investigacion algoritmoGenetico
- ./tarea_investigacion simulatedAnnealing
```



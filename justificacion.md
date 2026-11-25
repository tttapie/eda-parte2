# Justificación de órdenes — Obligatorio 2


## Ejercicio 6
- Justificación: pide O(N). Contamos cuántas veces aparece cada valor en un array de 1001 posiciones, con una sola pasada por las N placas. Después recorremos ese array de mayor a menor y armamos la mitad izquierda con los pares. El centro es el valor más grande que quedó impar. Recorrer las 1001 posiciones es constante y el cartel tiene como mucho N placas, así que queda O(N) en tiempo y en espacio.

## Ejercicio 7
- Justificación: pide O(N log N). Es un merge sort al que le agregamos el conteo de remontadas antes de cada merge. Como las mitades ya vienen ordenadas, contamos con dos punteros, y como j nunca vuelve para atrás, contar y mezclar es O(N) en cada nivel. Hay log N niveles, así que queda O(N log N). En espacio solo agregamos el array aux de tamaño N, o sea O(N).

## Ejercicio 8
- Justificación: pide O(N·W·L0·L1·L2·L3). La tabla tiene una dimensión por cada dato,el producto, el peso libre y cuántos llevamos de cada categoría. Cada casilla se llena en O(1), porque solo comparamos comprar o no comprar el producto mirando la fila siguiente. Entonces el tiempo y el espacio son el tamaño de la tabla.

## Ejercicio 9
- Justificación: pide O(K²). El estado es la ronda, la diferencia de goles y si bailó en el tiro anterior, así que hay K·K·2 estados. Con memo cada uno se calcula una sola vez y en O(1) (bailar o no bailar), así que el tiempo y el espacio quedan O(K²).

## Ejercicio 10
- Justificación: es un backtracking que le prueba un dígito libre a cada letra, sin poner 0 en la primera letra de palabras de más de una letra. Tiene dos podas,
  - Si un sumando es más largo que el resultado, no hay solución y ni arrancamos.
  - Asignamos las letras columna por columna desde las unidades. Cada vez que se completa una columna chequeamos que la suma con el acarreo dé bien, y si no da, cortamos esa rama.

  En el peor caso se prueban todas las asignaciones, O(10! · K · M) por acertijo (K sumandos, M largo del resultado). Con las podas, cada test corre en un par de segundos. Usamos int64_t porque con 10 cifras no entra en un int.
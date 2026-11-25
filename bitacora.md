# Bitácora — Obligatorio 2

**Integrantes:** Marco Bonicelli (340379), Francisco Tapie (351043)

## 2026-11-07 — Francisco 
- Leí la letra del 1er ejercicio, y lo implementé prácticamente entero
el primer problema que tuve fue suponer el array del cartel como un entero e intentar ingresar los pares al principio y al final,
terminé usando la primer mitad del cartel y espejándolo, de forma distinta si tiene un centro o no
la prueba 1000 pasa
## 2026-11-11 — Francisco 
- 2do ejercicio, para la lógica del merge, al principio pensamos en ir comparando todos los elementos  de la izquierda del array ordenado con los de la derecha, y si cumple con la condición de que si su nro es al menos 2 veces mayor del otro, suma 1 a la cantidad de remontadas épicas.
recorríamos cada parte del array y comparábamos sumando cuando cumplía la condición pero esto no es O(N log N), es O(N^2), en este caso nos trancamos y tuvimos que recurrir a usar IA para bajar el orden. Según lo que concluimos con la ayuda de la IA, tenemos que ir ordenando las mitades luego de compararse, para que la próxima vez, si la condición no cumple con el 1er elemento de la segunda mitad, todos los otros tampoco lo van a hacer, recortando casos.
## 2026-11-12 — Marco y Francisco
-leímos el ejercicio 8 e hicimos la versión recursiva previa a la tabulación
## 2026-11-13 — Marco y Francisco
-Seguimos con el ejercicio 8, para definir la estructura para guardar los datos de la satisfacción, es una lista de tablas, que son  5 variables, los elementos
el peso y las 4 categorías, que son las variables que van cambiando el posible resultado
-Uso de (IAG) la inicialización de la matriz y la liberación de la memoria de este.
La prueba 100 pasa
## 2026-11-20 — Marco y Francisco
-Ejercicio 9 entero, primero hicimos la recursión y luego lo pasamos a memoización
-Si el valor no estaba calculado y la ronda era menor a la cantidad de rondas total, se calcula y compara la opción de bailar con la de no bailar y se queda
-con el que consigue más likes 
-Uso de (IAG) corrección de detalles menores, indentación y errores tipográficos.

## 2026-11-21 — Marco y Francisco
-Comenzamos el ejercicio 10, planteamos todo el ejercicio, nos faltan las podas y reducir casos 
-muchos_largos.in.txt y muchos.in.txt pasan pero tardan mucho
## 2026-11-25 — Marco y Francisco
-hicimos podas de caso en el que un sumando es más largo que el resultado en solucionAcertijo
-y las otras podas son de columnas antes de hacer la recursión en backtracking, hicimos la función podaColumnas con ayuda de Claude para entender el tema del acarreo y separar la función en 2 para que sea más entendible
- Corrimos todas las pruebas de los ejercicios 6, 7, 8 y 9, encontramos un error en 6, al espejar la mitad izquierda sin centro, el for iba hasta placas en vez de cant(placas de la mitad izquierda)
- Luego de la corrección todas las pruebas pasan del 6 al 9
- Para el ejercicio 10, hicimos las podas pero el tiempo de ejecución sigue sin cumplir en los tests muchos.in.txt y muchos_largos.in.txt 
-Uso de (IAG) generacion de ideas para bajar el tiempo de ejecución(orden de las letras en el backtracking)
-Luego de implementar el cambio de orden de las letras, todos los tests pasan
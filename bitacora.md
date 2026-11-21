# Bitácora — Obligatorio 2

**Integrantes:** Nombre Apellido (Nº estudiante), Nombre Apellido (Nº estudiante)

> **Instrucciones** (borrar esta sección antes de entregar): agregar una entrada por
> cada día trabajado, indicando la fecha y quién trabajó (un integrante o "En conjunto").
> Registrar el proceso real: ideas exploradas, decisiones y su justificación, partes de
> implementaciones, bugs encontrados y cómo se corrigieron, resultados de pruebas y dudas
> abiertas. Si se usó IA ese día, indicar herramienta, consulta y qué se hizo con la
> respuesta. Una bitácora escrita íntegramente el día de la entrega implica pérdida de puntos.

## 2026-07-11 — Francisco 
- Lei la letra del 1er ejercicio, y lo implemente practicamente entero
el primer problema que tuve fue suponer el array del cartel como un entero e intentar ingresar los pares al principio y al final,
termine usando la primer mitad del cartel y espejandolo, de forma distinta si tiene un centro o no
la prueba 1000 pasa
## 2026-11-11 — Francisco 
- 2do ejercicio, para la logica del merge, al principio pensamos en ir comparando todos los elementos  de la izquierda del array ordenado con los de al derecha , y si cumple con la condicion de que si su nro es al menos 2 veces mayor del otro, suma 1 a la cantidad de remontadas epicas.
recorriamos cada parte del array y comparabamos sumando cuando cumplia la condicion pero esto no es O(N log N), es O(N^2), en este caso nos trancamos y tuvimos que recurrir a usar ia para bajar el orden. Segun lo que concluimos con la ayuda de la ia , tenemos que ir ordenando las mitades luego de compararse, para que la proxima vez, si la condicion no cunple con el 1er elemento de la segunda mitad, todos los otros tampoco lo van a hacer, recortando casos.
## 2026-12-11 — Marco y Francisco
-leimos el 3er ejercicio e hicimos la version recursiva previa a la tabulation
## 2026-13-11 — Marco y Francisco
-Seguimos con el ejercicio 3, para definir la estructura para guardar los datos de la satisfaccion, es una lista de tablas, que son  5 variables, los elementos
el peso y las 4 categorias, que son las variables que van cambiando el posible resultado
La prueba 100 pasa
## 2026-20-11 — Marco y Francisco
-Ejercicio 9 entero, primero hicimos la recursion y luego lo pasamos a memoization
-Si el valor no estaba calculado y la ronda era menor a la cantidad de rondas total, se calcula y compara compara la opcion de bailar con la de no bailar y se queda
-con el que consigue mas likes 
## 2026-21-11 — Marco y Francisco
-Comenzamos el ejercicio 10, planteamos todo el ejercicio, nos faltan las podas y reducir casos 
-muchos_largos.in.txt pasa pero tarda mucho
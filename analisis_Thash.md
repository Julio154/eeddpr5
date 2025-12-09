# Análisis de tablas de dispersión

* *Silvia Cruz Román*
* *Julio Gallegos Rojas*

## Tamaño de tabla (lambda 0.65): 5099
| función | máximo de colisiones | supera 10 colisiones | factor de carga | promedio de colisiones |
|---------|:--------------------:|:--------------------:|:---------------:|:----------------------:|
| hash1   |          13          |          4           |     0.6491      |         0.7514         |
| hash2   |          11          |          1           |     0.6491      |         0.5432         |
| hash3   |          14          |          11          |     0.6491      |         1.0239         |

## Tamaño de tabla (Lambda 0.68): 4871
| función | máximo de colisiones | supera 10 colisiones | factor de carga | promedio de colisiones |
|---------|:--------------------:|:--------------------:|:---------------:|:----------------------:|
| hash1   |          13          |          7           |     0.6795      |         1.2622         |
| hash2   |          14          |          12          |     0.6795      |         0.8444         |
| hash3   |          18          |          6           |     0.6795      |         1.7242         |

## Justificación de la configuración elegida
Hemos optado por la configuración con Lambda 0.65 y función hash2.

La elección se basa en el equilibrio entre el tamaño de la tabla y la minimización de colisiones:


Estabilidad y Peor Caso: La función hash2 con Lambda 0.65 es la única configuración que logra mantener en 1 el contador 
de elementos que "superan 10 colisiones". Esto es clave para garantizar que ninguna operación de inserción individual 
sufra un retardo excesivo, ofreciendo el rendimiento más estable de todas las pruebas.

Eficiencia Media: Presenta el promedio de colisiones más bajo de todas las combinaciones. Esto indica que la 
gran mayoría de los elementos se insertan en su primer o segundo intento, superando notablemente a hash1 y a 
hash3.

Comparación con Lambda 0.68: Al reducir el tamaño de la tabla, la función hash1 empeora significativamente: el promedio 
de colisiones sube a 0.8444 y aparecen 12 elementos con más de 10 colisiones.

Descarte de otras funciones: La función hash3 mostró un rendimiento pobre en ambas configuraciones, y la hash1, aunque 
aceptable, mantiene valores atípicos que la hacen menos robusta que la ganadora.


## Comparación de tiempos dados en milisegundos
Tiempo en realizar las búsquedas en la Tabla Hash: 2,006 ms.
Tiempo en realizar las búsquedas en la Lista: 118.138 ms.
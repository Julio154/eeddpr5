# Análisis de tablas de dispersión

* *Silvia Cruz Román*
* *Julio Gallegos Rojas*

## Tamaño de tabla (lambda 0.65): 5099
| función | máximo de colisiones | supera 10 colisiones | factor de carga | promedio de colisiones |
|---------|:--------------------:|:--------------------:|:---------------:|:----------------------:|
| hash1   |          13          |          3           |     0.3242      |         0.5698         |
| hash2   |          10          |          0           |     0.3242      |         0.4079         |
| hash3   |          14          |          10          |     0.3242      |         0.8181         |

## Tamaño de tabla (Lambda 0.68): 4871
| función | máximo de colisiones | supera 10 colisiones | factor de carga | promedio de colisiones |
|---------|:--------------------:|:--------------------:|:---------------:|:----------------------:|
| hash1   |          12          |          3           |     0.3397      |         0.9423         |
| hash2   |          14          |          4           |     0.3397      |         0.6142         |
| hash3   |          12          |          1           |     0.3397      |         1.2934         |

## Justificación de la configuración elegida
Hemos optado por la configuración con Lambda 0.65 y función hash2.

La elección se basa en el equilibrio entre el tamaño de la tabla y la minimización de colisiones:


Estabilidad y Peor Caso: La función hash2 con Lambda 0.65 es la única configuración que logra mantener en 0 el contador 
de elementos que "superan 10 colisiones". Esto es clave para garantizar que ninguna operación de inserción individual 
sufra un retardo excesivo, ofreciendo el rendimiento más estable de todas las pruebas.

Eficiencia Media: Presenta el promedio de colisiones más bajo (0.4079) de todas las combinaciones. Esto indica que la 
gran mayoría de los elementos se insertan en su primer o segundo intento, superando notablemente a hash1 (0.5698) y a 
hash3 (0.8181).

Comparación con Lambda 0.68: Al reducir el tamaño de la tabla, la función hash1 empeora significativamente: el promedio 
de colisiones sube a 0.6142 y aparecen 4 elementos con más de 10 colisiones. El ahorro de memoria no justifica esta 
pérdida de rendimiento y estabilidad.

Descarte de otras funciones: La función hash3 mostró un rendimiento pobre en ambas configuraciones, y la hash1, aunque 
aceptable, mantiene valores atípicos que la hacen menos robusta que la ganadora.


## Comparación de tiempos dados en milisegundos
Tiempo en realizar las búsquedas en la Tabla Hash: 0,631 ms.
Tiempo en realizar las búsquedas en la Lista: 49,874 ms.
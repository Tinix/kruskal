Algoritmo de Kruskal 
=======

labs4 FaMAF UNC

El algoritmo de Kruskal es un algoritmo de la teoría de grafos para encontrar un árbol recubridor mínimo en un grafo conexo y ponderado. Es decir, busca un subconjunto de aristas que, formando un árbol, incluyen todos los vértices y donde el valor de la suma de todas las aristas del árbol es el mínimo. Si el grafo no es conexo, entonces busca un bosque expandido mínimo (un árbol expandido mínimo para cada componente conexa). Este algoritmo toma su nombre de Joseph Kruskal, quien lo publicó por primera vez en 1956.1​2​. Otros algoritmos que sirven para hallar el árbol de expansión mínima o árbol recubridor mínimo son el algoritmo de Prim, el algoritmo del borrador inverso y el algoritmo de Boruvka.

### Descripción

El algoritmo de Kruskal es un ejemplo de algoritmo voraz que funciona de la siguiente manera:

se crea un bosque B (un conjunto de árboles), donde cada vértice del grafo es un árbol separado
se crea un conjunto C que contenga a todas las aristas del grafo
mientras C es no vacío
eliminar una arista de peso mínimo de C
si esa arista conecta dos árboles diferentes se añade al bosque, combinando los dos árboles en un solo árbol
en caso contrario, se desecha la arista
Al acabar el algoritmo, el bosque tiene un solo componente, el cual forma un árbol de expansión mínimo del grafo.

En un árbol de expansión mínimo se cumple:

la cantidad de aristas del árbol es la cantidad de nodos menos uno (1).

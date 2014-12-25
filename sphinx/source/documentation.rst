.. role:: underline
	  :class: underline

.. role:: el
	:class: element

Autores: Pablo Cabeza García y Paco Criado Gallart

Introducción
============

En este documento presentamos Bloco, un lenguaje de programación y un compilador asociado, para la
asignatura de Procesadores de Lenguajes.

El lenguaje Bloco es fuertemente tipado y muy similar a C,
salvo que añade definiciones de funciones anidadas, como Pascal. También permite funciones
anónimas, y de primer orden, y unas reglas de visibilidad de identificadores especiales, junto con
operadores de nuestra invención y muchas otras innovaciones apuntadas a conseguir un lenguaje de
paradigma funcional/imperativo.

Su objetivo final es reducir los caracteres del código fuente de un programa.

Análisis léxico
===============

Nuestro análisis léxico se basa una implementación del tradicional
lex, flex. La sintaxis de la gramática es muy similar, tan solo
variando algunas estructuras de control. Todo este análisis se
encuentra en *scanner.ll* y *scanner.hpp*. Cabe destacar que para los
identificadores hemos añadido una tabla de *"símbolo de tipo"*, donde
al encontrar un identificador se comprueba si es un tipo o no.

Sintaxis
========

La sintaxis del lenguaje Bloco es similar a la de c. Tenemos funciones que se pueden declarar en
cualquier ámbito, incluyendo funciones anónimas. La particularidad de nuestro lenguaje es
fundamentalmente esta.

Sin embargo, también hay algunas anomalías a nivel sintáctico, entre las que cabe destacar:

1. El if es sustituido por el operador '?', que se comporta de manera parecida a la del operador
   ternario de c/c++. Este recibe en vez de expresiones, funciones sin argumentos, tipicamente
   funciones anónimas.
2. De la misma forma, tenemos el operador '@', que representa al bucle while (en la forma
   "condición@función_anonima"). Este operador utiliza funciones que reciben y devuelven void,
   aunque originalmente estaba diseñado para poder anidarlo en expresiones, o como un operador
   entre funciones.
3. Tambien, siguiendo la filosofía de reducir el código, nuestro lenguaje abusa del operador ',' de
   c, añadiendo además el operador "apóstrofe". Al igual que el operador coma, el apóstrofe ejecuta
   una instruccion y luego la siguiente. Pero la diferencia es que el valor de la expresión es el
   valor de la primera instruccion ejecutada. Así, la diferencia es la misma que la que hay entre
   el ++ postfijo y prefijo de c: ++a se puede implementar como a,(a=a+1) y a++ se puede
   implementar como a'(a=a+1).
4. Además, la sintaxis para expresar un tipo suele ser de la forma "tipo:variable", al contrario
   que en c/c++. Hemos optado por esta aproximación para acercarnos más a un modelo matemático de
   las funciones.
5. El lenguaje Bloco soporta tipos de arrays, y tuplas anónimas y con nombre. Además, soporta
   variables de tipo función, lo que permite orden superior en funciones. Pero eso se explicará más
   adelante.

Operadores
~~~~~~~~~~

En las expresiones de Bloco, contamos con los siguientes operadores. Notese que es muy similar a la
tabla de operadores de c/c++.

.. table::
	:class: optable
	:column-classes: first

	+-----------+------------+-------------+------------------+
	|Precedencia|Operador    |Asociatividad|Descripción       |
	+===========+============+=============+==================+
	|1          |:el:`()`    |postfijo     |llamada a función |
	|           |            |izda-dcha    |                  |
	|           +------------+             +------------------+
	|           |:el:`[]`    |             |acceso a array y a|
	|           |            |             |tuplas anónimas   |
	|           |            |             |                  |
	|           |            |             |                  |
	|           +------------+             +------------------+
	|           | :el:`.`    |             |acceso a tupla con|
	|           |            |             |nombre            |
	|           +------------+             +------------------+
	|           |:el:`\+\+`  |             |\+\+ \-\-         |
	|           |:el:`\-\-`  |             |postfijos         |
	|           +------------+             +------------------+
	|           |:el:`type[]`|             |definición de     |
	|           |            |             |array             |
	|           +------------+             +------------------+
	|           |:el:`..{..}`|             |función anónima   |
	|           |            |             |                  |
	+-----------+------------+-------------+------------------+
	|2          |:el:`\+\+`  |prefijo      |\+\+ \-\- prefijos|
	|           |:el:`\-\-`  |dcha-izda    |                  |
	|           +------------+             +------------------+
	|           |:el:`\+`    |             |operadores de     |
	|           |:el:`\-`    |             |signo             |
	|           +------------+             +------------------+
	|           |:el:`~`     |             |NOT bit a bit     |
	|           +------------+             +------------------+
	|           |:el:`b`     |             |break             |
	|           +------------+             +------------------+
	|           |:el:`c`     |             |continue          |
	|           +------------+             +------------------+
	|           |:el:`r`     |             |return            |
	+-----------+------------+-------------+------------------+
	|3          |:el:`\*`    |infijo       |                  |
	|           |:el:`/`     |izda-dcha    |                  |
	|           |:el:`%`     |             |                  |
	|           |            |             |                  |
	+-----------+------------+             +------------------+
	|4          |:el:`\+`    |             |                  |
	|           |:el:`\-`    |             |                  |
	|           |            |             |                  |
	|           |            |             |                  |
	+-----------+------------+             +------------------+
	|5          |:el:`<<`    |             |desplazamientos de|
	|           |:el:`>>`    |             |bits              |
	+-----------+------------+             +------------------+
	|6          |:el:`<`     |             |operadores de     |
	|           |:el:`<=`    |             |orden             |
	|           |:el:`>`     |             |                  |
	|           |:el:`>=`    |             |                  |
	+-----------+------------+             +------------------+
	|7          |:el:`==`    |             |operadores de     |
	|           |:el:`!=`    |             |igualdad          |
	+-----------+------------+             +------------------+
	|8          |:el:`&`     |             |AND bit a bit     |
	+-----------+------------+             +------------------+
	|9          |:el:`^`     |             |XOR bit a bit     |
	+-----------+------------+             +------------------+
	|10         |:el:`\|`    |             |OR bit a bit      |
	+-----------+------------+             +------------------+
	|11         |:el:`&&`    |             |AND boolena       |
	+-----------+------------+             +------------------+
	|12         |:el:`\|\|`  |             |OR booleana       |
	+-----------+------------+-------------+------------------+
	|13         |:el:`:?`    |infijo       |operador          |
	|           |            |dcha-izda    |ternario          |
	+-----------+------------+-------------+------------------+
	|14         |:el:`=`     |infijo       |asignación        |
	|           |:el:`@`     |dcha-izda    |bucle "while"     |
	+-----------+------------+-------------+------------------+
	|16         |:el:`,`     |infijo       |operadores coma y |
	|           |:el:`'`     |dcha-izda    |apóstrofe         |
	|           |            |             |                  |
	+-----------+------------+-------------+------------------+



Gramática del lenguaje
~~~~~~~~~~~~~~~~~~~~~~

La gramática ha sido compilada con bison, la implementación de gnu de YACC. La gramática en
cuestión que generamos es como sigue:

.. literalinclude:: ../../src/parser.output
	:language: ebnf

Una de nuestras prioridades era minimizar el número de caractéres de código que tendría un programa
Bloco. Por esto, fué bastante dificil eliminar algunas ambiguedades derivadas de la reutilización
de operadores. Por ejemplo, los paréntesis, además de expresar diferentes niveles en una expresión,
representan también el tipo tupla, y la lista de argumentos de una funcion. Además, una tupla vacía
es un tipo diferente si es anónima o no.

Todos estos detalles hicieron que tuviesemos que tener
mucho cuidado con algunas de las reglas de la gramática. En particular, en las reglas 72-73, podían
darse muchos tipos de ambiguedades. Notese como se han resuelto considerando la tupla vacía como un
caso aparte en la regla 82.

Además, bison genera el arbol de sintaxis abstracta del programa, de acuerdo a los nodos descritos
en nodes.hpp.

Identificadores y tipos
=======================

El sistema de tipos que presentamos en bloco es bastante estándar, fuertemente tipado y con tipos
funcionales:
1. Tipos básicos: int, bool (se compila como int realmente), y float (no implementado a nivel de
   tipos, pero si considerado a nivel sintáctico)
2. Arrays, siguiendo la filosofía de Java según la cual se generan dinámicamente y comprueban los
   índices en ejecución.
3. Tuplas, anónimas (se acceden como un array) y con nombre. Se corresponden con los structs de c,
   y se compilan exactamente como estos.
4. Tipos funcionales. Esta es la base del lenguaje Bloco. Son valores funcionales que se pueden
   asignar y modificar, como las variables, o llamar como una función normal. Se definien de dos
   formas, como una función normal o como una función anónima. Un identificador de funcion normal
   no se puede modificar (se comprueba en compilación), pero ambos se compilan exactamente igual.
   Las funciones anónimas tienen un comportamiento especial en fase de identificadores.

Anidamiento de ámbitos
~~~~~~~~~~~~~~~~~~~~~~

En Bloco se considera que todo el código es una función, main, que no tiene cabecera.
Debido a que los bucles y bifurcaciones reciben funciones anónimas,  Bloco sólo genera ámbitos
en una circunstancia: cuando se define una función.

Los ámbitos entonces se pueden definir con una función anónima o con una función normal. En ambos
casos se sigue un procedimiento muy similar al proceso por el cual se identifican en pascal. Los
identificadores hacen referencia a cualquier variable que haya sido definida arriba en el código.
Si hay varias instancias, el identificador hace referencia al ámbito más cercano, el más anidado.

Cuando se resuelven los identificadores, se asocia a cada uno dos números. Uno indica cuantos
ámbitos hay que subir en el árbol de ámbitos para llegar a la definición. El otro, indica la
posición de ese identificador en el struct de variables locales de la función asociada. Estos
detalles se explicarán mejor en la parte de generacíón de código.

A parte de esto, el procedimiento por el que se recorre el árbol para resolver los identificadores
es el habitual: recorrer los hijos de un nodo del arbol primero, resolver sus identificadores, y su
tipo, y utilizar esta información para resolver los identificadores de los nodos superiores.

Para esto usamos una pila de contextos, que representa las variables que hay en el punto actual del
árbol de sintaxis abstracta. Esta pila de contextos no es el objetivo, si no el medio para lograr
resolver las referencias entre identificadores.

Generación de código
====================

Estamos traduciendo código bloco a código C en el compilador, que
después será compilado sin problemas con un compilador estándar de C
como GCC. Todos las comprobaciones de tipos y otros errores se hacen
desde nuestro compilador, tan solo usando el compilador de C para la
fase de generar código máquina (esto significa que cualquier error se
detecta durante la traducción y el código C generado ya es correcto).

Toda la generación de código está en el archivo *generate.cpp*, donde
se implementa el método *generate(CodeGenerate& g)* de cada uno de los
subtipos de nodo.

CodeGenerate
~~~~~~~~~~~~

Esta clase se encuentra en *codegenerate.hpp* en su totalidad y es una
clase auxiliar que contiene el código ya generado, separando las
cabeceras del cuerpo.

Método auxiliares
~~~~~~~~~~~~~~~~~

Hemos usado una serie de funciones auxiliares para ayudar en el
cálculo de offsets y en la generación de código. Los métodos son:

- **namednodelistgeneratefun()**: Este método genera los argumentos
  del prototipo de una

- **framesize()**: calcula el tamaño de un frame, incluyendo el
  puntero al padre.

- **frameoffset()**: Dado un frame, calcula el offset de un símbolo
  dado por el índice en el frame. Esto sería equivalente a la función
  :math:`\rho()`.

- **generategetframe()**: Dada la pila completa de frames y un par
  (i,j) representando la posición del símbolo en la pila, genera una
  expresión para acceder al símbolo.

- **generatefun()**: genera una expresión de *casting a
  puntero-a-función* de un NodeType de función.


Funciones de primer orden
~~~~~~~~~~~~~~~~~~~~~~~~~

La característica principal de bloco son las funciones de primer order. C no tiene esta característica, por lo que hay que implementarla de alguna forma en el lenguaje. Para ello hemos investigado algunas soluciones que se han dado a este problema y la que usa el lenguaje javascript (similar al nuestro por ser imperativo con primer order) puede ser implementada con relativa facilidad.

Cuando una función es declarada, por ejemplo:

.. code-block:: c++

	  int: c = 5;
	  int(int): fun = int (int: a) { r 2*a*c; };
	  r fun;

Las diferencia con una función C normal se resumirían en:

#. La función se genera *"al vuelo"*, entrelazada con el resto de
   código

#. Las funciones se comportan como variables, y por lo tanto se pueden
   asignar a variables de tipo función.
#. La función tiene acceso a las variables en entorno de definición
   durante la ejecución (clausuras).

Los puntos .1 y .2 se pueden resolver separando el código de la
función y sus referencias usando una cabecera de definiciones para el
código y punteros a función para las referencias.

Por otra parte, el punto .3 es más difícil de implementar por que
implica que las variables tengan un tiempo de vida mayor que tan solo
su bloque de definición, ya que pueden ser referenciadas por funciones
internas que se ejecuten en otro ámbito.

Encadenamiento de frames
------------------------

La solución usada para resolver este problema es crear una estructura
de datos que hemos llamado **frame**. Un frame es un bloque de memoria
donde se definen las variables locales de una función, además de un
puntero al frame *"padre"*. Este frame se crea en memoria dinámica
dentro de una función y nunca es borrado para que se pueda acceder
desde fuera de su ámbito. Para que esto no ocurra habría que
implementar algún tipo de recolección de basura, cosa que no estaba a
nuestro alcance. La estructura de un frame entonces es:

.. code::

	0	puntero al frame padre
	N	parámetro de la función
	M	variables locales

Durante la compilación cualquier referencia a símbolos se resuelve usando un par de números  (i,j) donde i es el número de frames que hay que ascender en la cadena de frames para encontrar el símbolo y j es el índice del símbolo en el frame. El offset en el frame se calcula durante la generación de código.

Supongamos que (i,j)=(3,2), frameoffset(2)=10 y el símbolo es de tipo *int*, el código generado para referenciarlo será:

.. code-block:: c

	  ( ( int *) ((***(char****) frame) + 10) )[0]

.. note:: El casting *(((char\*) frame) + M1)* es muy importante ya
          que en *aritmética de punteros* de C, el offset M1 se suma
          al puntero *frame* multiplicado por el tamaño del tipo, esto
          significa que necesitamos un tipo de tamaño 1 (char) para
          que funcione


Usando esto, cada función se traduce a una función C con la forma:

.. code-block:: c

	int __anon_M (void* _frame, int arg1); // M is an unique number

Además cada función tendrá un epílogo que consiste en:

#. Crear el frame en memoria dinámica.
#. Asignar el punter padre a este frame
#. Copiar los parámetro de la función al frame

Así el epílogo se parecerá a:

.. code-block:: c

	  void * frame = malloc(N); // Allocate frame
	  *(void**)frame=_frame; // Save parent frame
	  ((type_arg1*)(((char*) frame) + M1))[0] = arg1; // Copy first parameter
	  ((type_arg2*)(((char*) frame) + M2))[0] = arg2; // Copy second parameter

Done **N** el tamaño calculado del frame y **M1**, **M2**,... los
offsets de sus respectivos argumentos en el frame.

Unión del código y el entorno
-----------------------------

Ahora que el problema de las clausuras está solucionado hay que ver
cómo se hace la unión entre el código que se ejecuta y el entorno (el
frame padre) y como se ejecuta. Para ello necesitamos un par
*(función, frame)*, que se crea en el cuerpo cuando y donde la función
anónima es definida.

Para ello definimos un tipo común para todas las funciones anónimas:

.. code-block:: c

	  typedef struct { void* code; void* frame} anon_t;

Entonces, por ejemplo, la traducción de este bloque de código:

.. code-block:: c++

	  int: c=5;
	  int(int): fun = int (int: a) { r 2*a*c; };

Se parecerá a:

.. code-block:: c

	  int __anon_1 (void* _frame, int a) {
	  	// Function prologue to create frame
		return 2*A*C;
	  }

	  int main() {
	  	// Create base frame
		C = 5;
		FUN = (anon_t) {__anon_1,frame};
	  }


Donde **A**, **C**, **FUN** son expresiones para acceder a los
símbolos del frame.

Llamada a funciones
-------------------

En este punto llamar a la función consistiría en acceder al miembro
*.code*, hacer el casting al tipo *punter-a-función* correcto y
llamarlo usando *.frame* y el resto de parámetros.

El problema es que el resultado tiene que ser una expresión para poder
usar su valor de retorno como parte de otras expresiones, con lo que necesitamos hacer el anterior proceso en un sólo paso. La solución que hemos adoptado es genearar funciones auxiliares que realicen esto.

Por ejemplo, la traducción del código:

.. code-block:: c++

	  ((int: a) { c = 2*a; })(5); // c is already defined


Serían 2 funciones, *__anon_1* and *__aux_1*, la creación de un objeto
de tipo *anon_t* y la llamada a *__aux_1*. El resultado es:

.. code-block:: c

	void __anon_1 (void* _frame, int a) {
		// Prologue of function
		C = 2 * A;
	}

	void __aux_1 (anon_t f, int f1) {
		((void (*) ( void*, int )) f.code)( f.frame, f1); // Forward parameters to actual function
	}

	int main() {
		// main prologue to allocate base frame
		// ...
		__aux_1 ( (anon_t) { __anon_1 ,frame}, 5 ); // Creation of anon_t and call to __aux_1
	}

Conclusiones
============

Este lenguaje tenía un propósito claramente experimental, para probar un paradigma mixto que mezcla
conceptos de muchos lenguajes que ya conocemos de entre los vistos en la carrera. Tambien hemos
tenido oportunidad de  descubrir esquemas de compilación y técnicas que no habiamos visto nunca
antes en lenguajes existentes. Y vistos los problemas que nos han surgido, hemos podido entender
por qué eran (o no) buenas ideas de diseño.

Pese a que el lenguaje no es perfecto, y genera algo de basura, estamos muy satisfechos con el
resultado.

Bibliografía
============

Links
~~~~~

- Apuntes de la asignatura de PLG, curso 2013-2014
- Pdf sobre la  `comprobación de tipos`_ .
- `Ejemplo <http://www.thebinaryidiot.com/archives/2010/03/06/>`_ de un compilador en yacc y c++
- `Otro ejemplo  <http://panthema.net/2007/flex-bison-cpp-example/>`_u

.. _`comprobación de tipos`: http://www.sci.tamucc.edu/~sking/Courses/Compilers/Slides/type_checking.pdf

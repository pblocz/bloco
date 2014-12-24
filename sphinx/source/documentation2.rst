.. role:: underline
	  :class: underline

.. role:: el
	:class: element


..
	.. contents::

..
	1  Lexer and Parser
	  1.1  Structures needed
	  1.2  Processing
	  1.3  Operators
	2  Grammar for the language
	3  Documents
	  3.1  Links

Lexer and Parser
================

Structures needed
~~~~~~~~~~~~~~~~~

- **Type symbol table**: A table of types that should consist of:

  - *id*: the name of the type

  - *size*: its width in memory (for allocating)

  - *definition*: some kind of structure defining the type (fields,...)

- **Symbol tables**: The tables of symbols each must contain:

  - *id*: the name
  - *type*: the type of the variable
  - *value*: some kind of pointer or other structure for the value.

  It must  also be structured in  a stack manner, since  there will be
  scoping to  apply to  the rules. To  accomplish this for  each scope
  there will  be a table, and  when a new  scope is needed a  table is
  added.

  1. An initial table of symbols (globals).
  2. When an scope is added, a table is created and linked to the
     previous scope table.
  3. When looking for an id, check tables in order from the
     current scope up.
  4. When leaving an scope remove to top table.

- **String table**: A table for constant strings (global table). This can be use
  to optimise repeated strings.


Processing
~~~~~~~~~~

In the :underline:`lexer` the process to decide if an identifier is a type name or variable name should be:

	#. Lookup the *type symbol table*, if the id is there, return
	   a type token of the type found (with a reference to the entry in the
	   table.)
	#. Else, return new variable token.

Operators
~~~~~~~~~

.. table::
	:class: optable
	:column-classes: first

	+-----------+------------+-------------+------------------+
	|Precedence |Operator    |Associativtry|Description       |
	+===========+============+=============+==================+
	|1          |:el:`()`    |postfix      |function call     |
	|           |            |left-right   |                  |
	|           +------------+             +------------------+
	|           |:el:`[]`    |             |array and unnamed |
	|           |            |             |tuple access      |
	|           |            |             |                  |
	|           |            |             |                  |
	|           +------------+             +------------------+
	|           | :el:`.`    |             |named tuple access|
	|           |            |             |                  |
	|           +------------+             +------------------+
	|           |:el:`\+\+`  |             |postfix \+\+ \-\- |
	|           |:el:`\-\-`  |             |                  |
	|           +------------+             +------------------+
	|           |:el:`type[]`|             |array creation    |
	|           |            |             |                  |
	+-----------+------------+-------------+------------------+
	|2          |:el:`\+\+`  |prefix       |Prefix \+\+       |
	|           |:el:`\-\-`  |right-left   |                  |
	|           +------------+             +------------------+
	|           |:el:`\+`    |             |Sign op           |
	|           |:el:`\-`    |             |                  |
	|           +------------+             +------------------+
	|           |:el:`$type$`|             |Casting op        |
	|           +------------+             +------------------+
	|           |            |             |Typeof operator   |
	|           |:el:`$`     |             |                  |
	|           |            |             |                  |
	+-----------+------------+-------------+------------------+
	|3          |:el:`\*`    |infix        |                  |
	|           |:el:`/`     |left-right   |                  |
	|           |:el:`%`     |             |                  |
	|           |            |             |                  |
	+-----------+------------+             +------------------+
	|4          |:el:`\+`    |             |                  |
	|           |:el:`\-`    |             |                  |
	|           |            |             |                  |
	|           |            |             |                  |
	+-----------+------------+             +------------------+
	|5          |:el:`<<`    |             |bitwise shift     |
	|           |:el:`>>`    |             |                  |
	+-----------+------------+             +------------------+
	|6          |:el:`<`     |             |relational ops    |
	|           |:el:`<=`    |             |                  |
	|           |:el:`>`     |             |                  |
	|           |:el:`>=`    |             |                  |
	+-----------+------------+             +------------------+
	|7          |:el:`==`    |             |relational ops    |
	|           |:el:`!=`    |             |                  |
	+-----------+------------+             +------------------+
	|8          |:el:`&`     |             |bitwise and       |
	+-----------+------------+             +------------------+
	|9          |:el:`^`     |             |bitwise xor       |
	+-----------+------------+             +------------------+
	|10         |:el:`\|`    |             |bitwise or        |
	+-----------+------------+             +------------------+
	|11         |:el:`&&`    |             |bool and          |
	+-----------+------------+             +------------------+
	|12         |:el:`\|\|`  |             |bool or           |
	+-----------+------------+-------------+------------------+
	|13         |:el:`=`     |infix        |assignment        |
	|           |:el:`\+=`   |right-left   |operators         |
	|           |:el:`\-=`   |             |                  |
	|           |:el:`\*=`   |             |                  |
	|           |:el:`/=`    |             |                  |
	|           |:el:`%=`    |             |                  |
	|           |:el:`<<=`   |             |                  |
	|           |:el:`>>=`   |             |                  |
	|           |:el:`&=`    |             |                  |
	|           |:el:`^=`    |             |                  |
	|           |:el:`\|=`   |             |                  |
	+-----------+------------+-------------+------------------+
	|14         |:el:`?:`    |infix (n-ary)|if operator       |
	+-----------+------------+right-left   +------------------+
	|15         |:el:`@`     |             |loop operator     |
	+-----------+------------+-------------+------------------+
	|16         |:el:`,`     |infix        |comma operator    |
	|           +------------+left-right   +------------------+
	|           |:el:`'`     |             |apostrophy        |
	|           |            |             |operator          |
	+-----------+------------+-------------+------------------+



Grammar for the language
========================


.. literalinclude:: grammar.ebnf
   :language: ebnf

..
	This is without sphinx, comment it if not using it.
	.. raw:: html

		 <pre class="ebnf">

	.. raw:: html
		 :file: grammar.ebnf

	.. raw:: html

		 </pre>

.. note::
	Maybe delete LValue class and have a "flag" in the VariableNode
	to see if the variable is an RValue or LValue. If a VarNode is built
	from a variable then it is an LValue, else it is an RValue


Code generation
===============

We are translating bloco code into C language, that should be compiled
without problems using an standard C compiler like GCC. All type
checks are done in the identifier phase without relying in the
compiler, just using the C compiler to translate correct code into
object code (which means if a compiler error should be raised, it will
be during translation to C).

All generation related code is located in the file *generate.cpp* that
implements the method *generate(CodeGenerate& g)* from each subtype of
Node.

CodeGenerate
~~~~~~~~~~~~

This class is located in *codegenerate.hpp* completely and is just an
auxiliary class that contains the already generated code separating it
in head and body sections.

Auxiliary methods
~~~~~~~~~~~~~~~~~

We have a couple of auxiliary methods to help computing offsets or
generating repetitive code. Those are:

- **namednodelistgeneratefun()**: this method generates the parameters
  of a function prototype.

- **framesize()**: computes the size of a frame, including the parent pointer.

- **frameoffset()**: given a frame, compute the offset of a symbol
  given by its index in the frame. This will be the equivalent to the
  :math:`\rho()` function.

- **generategetframe()**: given the full stack of frames and the pair
  (i,j) representing the position of a symbol, generate an expression
  that accesses this symbol.

- **generatefun()**: generate the *casting to function-pointer*
  expression for the given function NodeType.


First order functions
~~~~~~~~~~~~~~~~~~~~~

The main feature of bloco is first order functions. C doesn't have
native support for it, to implement it we have researched various
solutions given to this problem and found that the solution adopted by
the javascript language (very similar in the sense that it is
imperative plus having first order) could be implemented in C with
relative ease.

When a function is declared, for example:

.. code-block:: c++
	  
	  int: c = 5;
	  int(int): fun = int (int: a) { r 2*a*c; };
	  r fun;

The differences with an standard C functions would be summarized in:

#. The function in generated *"on the fly"*, interleaved with actual
   code.
#. The function is passed to a variable of type function, that can be
   then called.
#. The function has access to variables on the definition scope during
   execution (closures).

For points number 1. and 2., carefully placing the function definition
in a header and referencing it using pointers to function can solve
it. 

On the other hand, point 3. is harder to implement because it implies
that variable should have a longer lifespan than just its defining
block, because they can be referenced from an inner defined function,
and that function should be able to access symbols from the upper
scope in the code.

Frame chaining
--------------

The solution we have used to solve this problem is creating a data
structure that we call **frame**. A frame is just a chunk of memory
where we define local variables of a function, plus a pointer to the
*"parent"* frame (the one in the upper scope). This frame is created
inside a function allocated in dynamic memory, and is never
deleted. This is due to the *lifespan* problem mentioned above, to
solve it some kind of *garbage collector* must be implemented, something
that was out of our scope. Then the structure of a frame is:

.. code::

	0	pointer to parent frame
	N	function parameters
	M	local variables


During compilation any reference to symbols is resolved using a pair
of number (i,j) where i is the number of scopes it has to go up in the
definition chain, and j in the index of that symbol in the frame. The
offset of the symbol is computed using when generating the code.

Imagine that (i,j)=(3,2), frameoffset(2)=10 and the symbol is of type *int*, the generated code to reference the symbol would be:

.. code-block:: c

	  ( ( int *) ((***(char****) frame) + 10) )[0]

.. note:: The casting *(((char\*) frame) + M1)* is very important
   because, in C *pointer arithmetic*, the offset M1 is added to the
   pointer *frame* multiplied by the size of it's type, which means we
   need to use some type of size 1 (char) for this to work properly.



Using this, now each function is translated into a C function that have the form:

.. code-block:: c

	int __anon_M (void* _frame, int arg1); // M is an unique number

And each function will have a prelude that consists on:

#. Allocating the frame using dynamic memory.
#. Assigning the parent frame to this frame.
#. Copying function parameters to the frame.

So the prelude will look like this:

.. code-block:: c
	  
	  void * frame = malloc(N); // Allocate frame
	  *(void**)frame=_frame; // Save parent frame 
	  ((type_arg1*)(((char*) frame) + M1))[0] = arg1; // Copy first parameter
	  ((type_arg2*)(((char*) frame) + M2))[0] = arg2; // Copy second parameter

Where **N** is the computed size of the frame and **M1**,
**M2**,... are the offsets of their respective function arguments in
the frame.	  

Code and scope binding
----------------------

Now that the closure problem is solved we need to address the problem
of binding a function with its parent frame (the frame of its scope)
and calling it. We need a pair *(function, frame)*, that is created
when and where a function is defined.

We first define a common C struct for anonymous functions:

.. code-block:: c

	  typedef struct { void* code; void* frame} anon_t;

Then the translation of this bloco code:

.. code-block:: c++
   
	  int: c=5;
	  int(int): fun = int (int: a) { r 2*a*c; };
	  
Would look like:

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


In the code **A**, **C**, **FUN** are expressions to access their
respective symbols in the frame, that are omitted to light the
example.

Function calling
----------------

At this point calling the function would consist on accessing it's
*.code* member, cast it to the right type and call it passing *.frame*
as it's first argument and then the rest of parameters. The problem is
that it should act as an *expression* because we might need it's
return value as part of another expression. This means that we need to
*"give it a name"* to access each member. The solution adopted is
to generate auxiliary functions that do all this processing. 

For example lets translate this code:

.. code-block:: c++
	  
	  ((int: a) { c = 2*a; })(5); // c is already defined


This will translate into 2 functions, *__anon_1* and *__aux_1*, a
creation of an object of type *anon_t* and a call to *__aux_1*. The result is:

.. code-block:: c
	  
	void __anon_1 (void* _frame, int a) {
		// Epilogue of function
		C = 2 * A;
	}

	void __aux_1 (anon_t f, int f1) {
		((void (*) ( void*, int )) f.code)( f.frame, f1); // Forward parameters to actual function
	}

	int main() {
		// main epilogue to allocate base frame
		// ...
		__aux_1 ( (anon_t) { __anon_1 ,frame}, 5 ); // Creation of anon_t and call to __aux_1
	}

Documents
=========

Links
~~~~~

- Pdf that explains `type checking`_ .
- `Example <http://www.thebinaryidiot.com/archives/2010/03/06/>`_ for building lex and yacc parser in c++.
- `Complete example <http://panthema.net/2007/flex-bison-cpp-example/>`_ of c++ parser for flex and bison.

.. _`type checking`: http://www.sci.tamucc.edu/~sking/Courses/Compilers/Slides/type_checking.pdf

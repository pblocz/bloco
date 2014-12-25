# bloco

authors: Pablo Cabeza García & Paco Criado Gallart

This is a compiler built using [bison] and [flex], yacc and lex implementations.
An example of source code:

    int(int,int) : fun = int (int:act,int:sum) {
	    r ((act!=0) ? fun(act-1,sum+act) : sum);
    };

    int:a = fun(100,0);

## Usage

You pass your code through the standard input and the translated code is output
to the standard output. Calling it through terminal, you can redirect the
standard input:

    bloco-c < sourcefile.bl

## Documentation

The specific documentation and report for this assignment is
[here][documentation] (spanish).

It is built using sphinx, and then exported to html. Source for the
documentation is located under [sphinx]  folder.

## Examples

Under [examples] we have some working source files that translate correctly with
our compiler.

One mayor drawback is that we have no system calls (this include printing),
which means that to get the actual output when executing the code, printing must
be added manually to the compiled version. This can be easily achived using:

    // Meaningful code

    var1; var2; ...

    // EOF

When translated the last expressions of the code are lvalues representing
the variables.

## Sources and compilation

### Compilation

To compile it you need:

- GNU make
- Flex
- Bison (or other YACC compatible implementation)
- clang++ (c++ compiler based in LLVM)

There is a `makefile` in the root directory that builds binaries to `/bin`
folder.

### Sources

scanner.hpp
scanner.ll

parser.yy

blocodriver.hpp
blocodriver.cpp

blocotree.hpp

nodes.hpp
nodes.cpp

codegeneration.hpp

generate.cpp
identifiers.cpp


[bison]: <>
[flex]: <>

[documentation]: <sphinx/build/singlehtml/index.html>

[sphinx]: <>
[examples]: <>

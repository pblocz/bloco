YACC=bison
LEX=flex
CP = cp
MKDIR = mkdir -p
RM = rm -r
GCC = clang++

CFLAGS = -pedantic -Wall -Wextra -Wformat=2 -std=c++11 -g -Wno-overloaded-virtual\
 -Wno-unused-parameter

# Add to static_files all .hpp or .cpp files needed for compilation
static_files = blocodriver.hpp blocodriver.cpp scanner.hpp nodes.hpp \
 nodes.cpp blocotree.hpp identifiers.cpp generate.cpp codegeneration.hpp
build_static = $(addprefix build/, $(static_files))
cpp_build_static = $(filter build/%.cpp,$(build_static))
hpp_build_static = $(filter %.hpp,$(build_static))

compile_cpp = $(filter %.cpp,$(static_files)) parser.cpp scanner.cpp

.phony: start clean

start: build/ build/parser.cpp build/scanner.cpp $(build_static)
	cd build; $(GCC) $(CFLAGS) $(compile_cpp)


build/parser.cpp: parser.yy
	$(YACC) -o build/parser.cpp --defines=build/parser.hpp parser.yy

build/scanner.cpp: scanner.ll
	$(LEX) -o build/scanner.cpp scanner.ll

$(cpp_build_static): build/%.cpp : %.cpp
	cp $< $@

$(hpp_build_static): build/%.hpp : %.hpp
	cp $< $@


build/:
	$(MKDIR) build/

clean:
	$(RM) build/

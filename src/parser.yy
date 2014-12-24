// This will be included in parser.cpp at the top
%{
#include <iostream>
#include <string>
#include <vector>

#include "nodes.hpp"
%}

// This will be included in the parser.hpp before any useful code
%code requires {
#include "nodes.hpp"
namespace bloco{ class BlocoDriver; } // forward declare
}

%debug
//%start start
%defines
%skeleton "lalr1.cc"
%define namespace "parser"
%define parser_class_name "Parser"
%locations
%initial-action {
    @$.begin.filename = @$.end.filename = &driver.streamname;
};

%parse-param { bloco::BlocoDriver& driver }
%error-verbose

// estructura de datos de la informacion asociada a los simbolos.
%union{
    std::string*	stringval;
    int				intval;
    double			floatval;
    Node*			nodeptr;
	NodeList*		vect;
	NamedNodeList*	vectnom;
}

%token END 0 "end of file"
%token EOL "end of line"

%token <intval>    INTEGER_    "integer"
%token <floatval>  FLOAT_      "float"
%token <stringval> STRING_     "string"
%token <intval>    BOOL_       "bool"

%token <stringval> IDENTIFIER_ "identifier"
%token <stringval> TYPE_       "type identifier"

%token INT MASMAS MENOSMENOS MAYORIGUAL MENORIGUAL IGUALIGUAL NOIGUAL BARRABARRA ANDAND MENORMENOR MAYORMAYOR

%type <nodeptr> program stmt expr15 expr14 expr14_1 expr14_2 expr13 expr12 expr11 expr10 expr9 expr8 expr7 expr6 expr5 expr4 expr3 expr1 funcion_anonima declaracion type def_funcion_cte
%type <vectnom> lista_types_nombre
%type <vect>  stmt_list lista_args lista_types

// If we want to destroy them...
//%destructor { delete $$; } STRING_ IDENTIFIER_ TYPE_

// Pass the current locations to nodeptr, vect and vectnom nodes
%destructor { $$->loc = @$; } <nodeptr>
%destructor { for(auto n: *$$) n->loc = @$; } <vect>
%destructor { for(auto n: *$$) n.first->loc = @$; } <vectnom>

%{
#include "blocodriver.hpp"
#include "scanner.hpp"

/* connect bison parser to flex scanner in the driver, the function to get the
 * next token.
 */
#undef yylex
#define yylex driver.lexer->lex
%}

%%

 /**** Here goes the rules of the grammar ****/

//esta es simple, es la regla inicial, la que define el main
program:
	stmt_list {driver.tree.setnode(new NodeProg($1));}
;

//lista de instrucciones
stmt_list:
	stmt_list stmt {
        $1->push_back($2);
        $$=$1;}
|	stmt {
    auto aux=new NodeList();
    aux->push_back($1);
    $$=aux;}
;

//instrucción
stmt:
	expr15 ';' {$$=$1;}
|	declaracion ';' {$$=$1;}
|	def_funcion_cte {$$=$1;}
;

/*
	A partir de aquí, se especifican las expresiones, con su orden de prioridad de operadores.
	Son especialmente interesantes los primeros y los ultimos niveles:
*/
expr15:
	expr14 ',' expr15 {$$=opbinario(',',$1,$3);}
|	expr14 '\'' expr15 {$$=opbinario('\'',$1,$3);}
|	expr14 {$$=$1;}
;

/*
	Esto es polémico. El operador @ es muy especial, no sabíamos si hacer que recibiera
	instrucciones o funciones. En un caso, si recibe instrucciones, para hacer ejecutar un bloque de
	código, hace falta ejecutar la llamada a la función anónima al final: a!=0@{a--;}()
	
	En el otro caso, si recibe funciones, cada @ tiene que tener un par de llaves siempre, lo que no
	permite bucles de una sola instrucción de forma limpia. Optamos por esta segunda opción
*/
expr14:
	expr14_1 '=' expr14 {$$=opbinario('=',$1,$3);}
|	expr14_2 '=' expr14 {$$=opbinario('=',$1,$3);}
|	expr14_1 '@' funcion_anonima {$$=opbinario('@',$1,$3);}
|	expr14_2 '@' funcion_anonima {$$=opbinario('@',$1,$3);}
|	expr14_1 {$$=$1;}
|	expr14_2 {$$=$1;}
;

/*
	Nuestro operador ternario también plantea algunos dilemas, para empezar el del caso anterior.
	Además, este es el típico ejemplo del else ambiguo. Se resuelve por el procedimiento habitual.
*/
expr14_1:
	expr13 '?' expr14_1 {$$=opbinario('?',$1,$3);}
|	expr13 '?' expr14_2 ':' expr14_1 {
		NodeList *v=new NodeList;
		v->push_back($1);
		v->push_back($3);
		v->push_back($5);
		$$=new NodeExprOp('?', v);
	}
|	expr13 '?' expr14_2 {$$=opbinario('?',$1,$3);}
;

expr14_2:
	expr13 '?' expr14_2 ':' expr14_2 {
		NodeList *v=new NodeList;
		v->push_back($1);
		v->push_back($3);
		v->push_back($5);
		$$=new NodeExprOp('?', v);
	}
|	expr13 {$$=$1;}
;

// Operadores con menos interés
expr13:
	expr13 BARRABARRA expr12{$$=opbinario(barrabarra,$1,$3);}
|	expr12 {$$=$1;}
;

expr12:
	expr12 ANDAND expr11 {$$=opbinario(andand,$1,$3);}
|	expr11 {$$=$1;}
;

expr11:
	expr11 '|' expr10 {$$=opbinario('|',$1,$3);}
|	expr10 {$$=$1;}
;

expr10:
	expr10 '^' expr9 {$$=opbinario('^',$1,$3);}
|	expr9 {$$=$1;}
;

expr9:
	expr9 '&' expr8 {$$=opbinario('&',$1,$3);}
|	expr8 {$$=$1;}
;

expr8:
	expr8 IGUALIGUAL expr7 {$$=opbinario(igualigual,$1,$3);}
|	expr8 NOIGUAL expr7 {$$=opbinario(noigual,$1,$3);}
|	expr7 {$$=$1;}
;

expr7:
	expr7 MENORIGUAL expr6 {$$=opbinario(menorigual,$1,$3);}
|	expr7 MAYORIGUAL expr6 {$$=opbinario(mayorigual,$1,$3);}
|	expr7 '<' expr6 {$$=opbinario('<',$1,$3);}
|	expr7 '>' expr6 {$$=opbinario('>',$1,$3);}
|	expr6 {$$=$1;}
;

expr6:
	expr6 MENORMENOR expr5 {$$=opbinario(menormenor,$1,$3);}
|	expr6 MAYORMAYOR expr5 {$$=opbinario(mayormayor,$1,$3);}
|	expr5 {$$=$1;}
;

expr5:
	expr5 '+' expr4 {$$=opbinario('+',$1,$3);}
|	expr5 '-' expr4 {$$=opbinario('-',$1,$3);}
|	expr4 {$$=$1;}
;

expr4:
	expr4 '*' expr3 {$$=opbinario('*',$1,$3);}
|	expr4 '/' expr3 {$$=opbinario('/',$1,$3);}
|	expr4 '%' expr3 {$$=opbinario('%',$1,$3);}
|	expr3 {$$=$1;}
;

/*
	El masmas prefijo se compila como un (c=c+1)
	El masmas postfijo se compila como un unario masmas
*/
expr3:
	MASMAS expr3 {$$=opunario(masmas,$2);}
|	MENOSMENOS expr3 {$$=opunario(menosmenos,$2);}
|	'-' expr3 {$$=opunario('-',$2);}
|	'+' expr3 {$$=opunario('+',$2);}
|	'!' expr3 {$$=opunario('!',$2);}
|	'~' expr3 {$$=opunario('~',$2);}
|	'r' expr3 {$$=opunario('r',$2);}
|	'c' expr3 {$$=opunario('c',$2);}
|	'b' expr3 {$$=opunario('b',$2);}
|	expr1 {$$=$1;}
;

expr1:
	expr1 MASMAS {$$=opbinario(masmas,$1,nullptr);}
|	expr1 MENOSMENOS {$$=opbinario(menosmenos,$1,nullptr);}
|	expr1 '(' lista_args ')' { //llamada a función
		auto aux=opunario('(', $1);
		for(auto i:*$3) ((NodeExprOp *)aux)->args->push_back(i);
		$$=aux;
	}
|	expr1 '[' expr15 ']' {
		$$=opbinario('[', $1, $3);
	}
|	expr1 '.' IDENTIFIER_ { $$=opbinario('.', $1, new NodeExprId(*$3));}
|	IDENTIFIER_ {$$=new NodeExprId(*$1);}
|	funcion_anonima {$$=$1;}
|	type '[' expr15 ']' {
		$$=new NodeExprDefArr($1,$3);
	}
|	INTEGER_ {$$=new NodeExprCte($1);}
|	'(' expr15 ')' {$$=$2;}
;

lista_args:
	/*epsilon*/ {$$=new vector<Node *>();}
|   expr14 { $$=new vector<Node *>(); $$->push_back($1); }
|	lista_args ',' expr14 {$1->push_back($3);$$=$1;}
;

/*WTF*/
/*
	Este es el punto donde la gramática daba problemas por algún motivo.
	Nótese la sintaxis de las funciones anónimas. El tipo void es (), que es en realidad una tupla
	anónima. Así que daba problemas. Por eso, deje que () fuera considerado como caso aparte
	siempre.
*/
funcion_anonima:
	'{' stmt_list '}' { // Sin argumentos, devuelve un tipo ()
		$$=new NodeExprAnon(nullptr, new NamedNodeList(), new NodeProg($2));
	}
|	'(' lista_types_nombre ')' '{' stmt_list '}' { // devuelve ()
	    $$=new NodeExprAnon(nullptr, $2, new NodeProg($5));
	}
|	type '(' lista_types_nombre ')' '{' stmt_list '}' { 
		$$=new NodeExprAnon((NodeType *) $1, $3, new NodeProg($6));
	}
|	type '(' ')' '{' stmt_list '}' { //Obligatorio resaltar el () porque si no, es ambiguo.
		$$=new NodeExprAnon((NodeType *) $1, new NamedNodeList(), new NodeProg($5));
	}
;

//Declaración de una variable, con o sin asignacion inicial.
declaracion:
	type ':' IDENTIFIER_ {
		auto aux=new NodeDecl((NodeType *)$1, *$3, nullptr);
		$$=aux;
	}
|	type ':' IDENTIFIER_ '=' expr14 {
		auto aux=new NodeDecl((NodeType *)$1, *$3,(NodeExpr *)$5);
		$$=aux;
	}
| 	declaracion ',' IDENTIFIER_ {
		((NodeDecl *) $1)->addargs(nullptr,*$3);
		$$=$1;
	}
| 	declaracion ','IDENTIFIER_ '=' expr14 {
		((NodeDecl *) $1)->addargs((NodeExpr *)$5,*$3);
		$$=$1;
	}
;

type:
	type '[' ']' { //Array con tamaño a determinar
		$$=new NodeTypeArr((NodeType *) $1);
	}
|	'(' lista_types ')' { //tupla anónima
		$$=new NodeTypeTuple($2);
	}
|	'(' ')' { //tupla anónima vacía
		$$=new NodeTypeTuple(new vector<Node *>);
	}
|	type '(' lista_types ')' { //tipo función
		$$=new NodeTypeFunc((NodeType *)$1, $3);
	}
|	type '('  ')' { //tipo función
		$$=new NodeTypeFunc((NodeType *)$1, new vector<Node *>);
	}
|	'(' lista_types_nombre ')' { //tupla con nombres
		$$=new NodeTypeNamedTuple($2);
	}
|	INT {$$=new NodeTypeInt;}
;

lista_types:
	type {
		auto aux=new vector<Node *>;
		aux->push_back((NodeType *) $1);
		$$=aux;
	}
|	lista_types ',' type {$1->push_back((Node *)$3); $$=$1;}
;

lista_types_nombre:
	type ':' IDENTIFIER_ {
		NamedNodeList* aux=new NamedNodeList;
		aux->push_back(make_pair((NodeType *)$1, *$3));
		$$=aux;
	}
|	lista_types_nombre ',' type ':' IDENTIFIER_ {
		auto aux=$1;
		aux->push_back(make_pair((NodeType *)$3,*$5));
		$$=aux;
	}
;

/*Relacionado con WTF*/
def_funcion_cte:
	type IDENTIFIER_ '{' stmt_list '}' {
		$$=new NodeDeffun((NodeType*)$1, *$2, new NamedNodeList(), new NodeProg($4));
	}
|	type IDENTIFIER_ '(' lista_types_nombre ')' '{' stmt_list '}' {
		$$=new NodeDeffun((NodeType*)$1, *$2, $4, new NodeProg($7));
	}
|	type IDENTIFIER_ '(' ')' '{' stmt_list '}' {
		$$=new NodeDeffun((NodeType*)$1, *$2, new NamedNodeList, new NodeProg($6));
	}
;


 /**** End of rules ****/

%%

void parser::Parser::error(const Parser::location_type& l, const std::string& m){
    driver.error(l,m);
}

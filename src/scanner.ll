%{

#include <string>
#include <utility>
#include "scanner.hpp" // our scanner interface
#pragma clang diagnostic ignored "-Wdeprecated-register"

typedef lexer::Scanner::Driver::token token;
typedef lexer::Scanner::Driver::token_type token_type;

// override default behaviour of returning 0 on end, return a token
#define yyterminate() return token::END

// no include unistd.h... communication will be with STL streams
#define YY_NO_UNISTD_H

%}

%option c++
%option prefix="Bloco"
%option batch
%option debug
%option stack

%{
#define YY_USER_ACTION yylloc->columns(yyleng);
%}

%x COMMENT
%x STRING

%%

 /* code to place at the beggining of yylex() */
%{
    using namespace std;
    yylloc->step();
%}

 /**** Rules here ****/

 /* rule for comments */
"/*" { BEGIN(COMMENT); yylloc->step(); }
<COMMENT>"*/" { BEGIN(INITIAL); yylloc->step(); }
<COMMENT>\n { yylloc->lines(yyleng); yylloc->step(); }
<COMMENT>. { yylloc->step(); }

 /* line comments */
"//"[^\n]*\n

 /* rule for strings */
"\"" { BEGIN(STRING); yylloc->columns(yyleng); }
<STRING>"\\\"" { strm << '"'; yylloc->columns(yyleng); }
<STRING>"\"" { yylval->stringval=new string(strm.str()); strm.str(""); BEGIN(INITIAL); return token_type::STRING_; }
<STRING>\n { strm << '\n'; yylloc->lines(yyleng); }
<STRING>\t { strm << '\t'; yylloc->columns(yyleng); }
<STRING>. { strm << (char)*yytext; yylloc->columns(yyleng); }

 /* rule for strings */
[0-9]+ { yylval->intval = atoi(yytext); return token::INTEGER_; }

 /* rule for floats */
[0-9]*\.[0-9]+ { yylval->floatval = atof((string("0")+yytext).c_str()); return token::FLOAT_; }

 /* rule for booleans */
 /* TODO: do it for actual booleans */
"true" { yylval->intval = 1; return token::INTEGER_; }
"false" { yylval->intval = 0; return token::INTEGER_; }
 
 /* special rule for keywords */
"r" { return static_cast<token_type>(*yytext); }

 /* rule for identifiers */
[a-zA-Z][a-zA-Z_]* {
    yylval->stringval = new string(yytext);
    if(driver.type(*(yylval->stringval))) return token::INT; // FIXME: fixthis token::TYPE_;
    return token::IDENTIFIER_;
 }


"++"        return token::MASMAS;
"--"        return token::MENOSMENOS;
">="        return token::MAYORIGUAL;
"<="        return token::MENORIGUAL;
"=="        return token::IGUALIGUAL;
"!="        return token::NOIGUAL;
"||"		return token::BARRABARRA;
"&&"		return token::ANDAND;
"<<"		return token::MENORMENOR;
">>"		return token::MAYORMAYOR;




 /* other rules */
[ \t\r]+ { yylloc->step(); }
[\n]+ { yylloc->lines(yyleng); yylloc->step(); }
. { return static_cast<token_type>(*yytext); }

 /**** End of rules ****/

%%

// If lexer::Scanner must have code in .cpp, this code needs to be here.

#ifdef yylex
#undef yylex
#endif // yylex

int BlocoFlexLexer::yylex(){
    std::cerr << "ERROR!!! inside FlexLexer::yylex()" << std::endl;
    return 0;
}

int BlocoFlexLexer::yywrap(){
    return 1;
}

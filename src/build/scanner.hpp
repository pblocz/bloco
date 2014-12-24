#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <sstream>


// YY_DECL is the declaration of the yylex method. Furthermore it must be declared.

#ifndef YY_DECL
#define YY_DECL\
    lexer::Scanner::Driver::token_type lexer::Scanner::lex (\
        lexer::Scanner::Driver::semantic_type* yylval,\
        lexer::Scanner::Driver::location* yylloc)
#endif // YY_DECL


// Include the flex lexer

#ifndef __FLEX_LEXER_H
//#ifndef yyFlexLexerOnce
#define yyFlexLexer BlocoFlexLexer
#include <FlexLexer.h>
#undef yyFlexLexer
#endif // yyFlexLexerOnce


#include "blocodriver.hpp" // bloco driver has all parser information

namespace lexer{

class Scanner : public BlocoFlexLexer {
public:
    typedef bloco::BlocoDriver Driver;

    Scanner(Driver& driver, std::istream* arg_yyin = 0,
            std::ostream* arg_yyout = 0)
        :BlocoFlexLexer(arg_yyin, arg_yyout),driver(driver){}

    virtual ~Scanner(){}

    // Flex implements it
    virtual Driver::token_type lex( Driver::semantic_type* yylval,
                                    Driver::location* yylloc);

    void set_debug(bool b){ yy_flex_debug = b; }

private:
    Driver& driver;
    std::stringstream strm;
}; // class Scanner

} // namespace lexer
#endif //SCANNER_HPP

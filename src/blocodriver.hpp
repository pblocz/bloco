#ifndef BLOCODRIVER_HPP
#define BLOCODRIVER_HPP

#include "parser.hpp"
//#include "context.hpp"
#include "blocotree.hpp"

#include <string>
#include <vector>



namespace lexer { class Scanner; }

namespace bloco {

class BlocoDriver {
public:
        typedef parser::Parser::token token;
        typedef parser::Parser::token_type token_type;
        typedef parser::Parser::location_type location;
        typedef parser::Parser::semantic_type semantic_type;

        BlocoDriver(BlocoTree& tree);

        bool parse_stream(std::istream& in,
                        const std::string& name = "input stream");

        void error(const location& l, const std::string& m);
        void error(const std::string& m);

        /* TODO: actual type getter from context */
        bool type(const std::string& id);

        bool trace_scanning;
        bool trace_parsing;

        std::string streamname; // for errors
        lexer::Scanner* lexer;
        BlocoTree& tree;
}; // BlocoDriver

} // bloco

#endif // BLOCODRIVER_HPP

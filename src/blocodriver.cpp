#include <fstream>
#include <sstream>

#include "blocodriver.hpp"
#include "scanner.hpp"
//#include "context.hpp"

namespace bloco {

BlocoDriver::BlocoDriver(bloco::BlocoTree & context)
    : trace_scanning(false), trace_parsing(true),tree(context){}

bool BlocoDriver::parse_stream(std::istream& in, const std::string& sname){
    streamname = sname;
    lexer::Scanner scanner(*this,&in);
    scanner.set_debug(trace_scanning);

    this->lexer = &scanner;

    parser::Parser parser(*this);
    parser.set_debug_level(trace_parsing);
    return parser.parse() == 0;
}

void BlocoDriver::error(const BlocoDriver::location& l, const std::string& m){
    std::cerr << l << ": " << m << std::endl;
}

void BlocoDriver::error(const std::string& m){
    std::cerr << m << std::endl;
}

bool BlocoDriver::type(const std::string& id){
    if(id=="int") return true;
    return false;
}

} // namespace bloco


#include <iostream>

// EXAMPLE
// namespace bloco{
// class BlocoTree{};
// }

int main(){
    bloco::BlocoTree b;
    bloco::BlocoDriver(b).parse_stream(std::cin,"stdin");

    auto n = new NamedNodeList;
    Context c;
    ((NodeProg*)b.node)->identifiers(c);

    b.node->print(0);
    std::cout << std::flush;

    CodeGenerate g;
    g.addhead("#include <stdio.h>\n");
    g.addhead("#include <stdlib.h>\n");
    g.addhead("typedef struct {void* code; void* frame; } anon_t;\n\n");

    b.node->generate(g);


    std::cout <<  g.headerstr.str();

    std::cout << "int main() { void* _frame=0;\n"  << g.sstr.str() << "}\n" ;

    return 0;
}

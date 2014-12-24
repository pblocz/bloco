#ifndef BLOCOTREE_HPP
#define BLOCOTREE_HPP

#include "nodes.hpp"

#include <map>
#include <string>

namespace bloco {

class BlocoTree {
public:
    void setnode(Node* node){ this->node= node;}
    void decorate_identifiers(){
        // TODO
    }

    Node* node;
}; // class BlocoTree

} // namespace bloco

#endif //BLOCOTREE_HPP

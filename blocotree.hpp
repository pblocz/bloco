#ifndef BLOCOTREE_HPP
#define BLOCOTREE_HPP

#include <map>
#include <string>

#include "nodes.hpp"


namespace bloco{

template <class T>
class Context{
public:
    Context():prev(0){}
    Context(const T& p) :prev(&p){}
    virtual ~Context(){ delete prev; }

    void insert(const std::string& id,const T& v){table[id]=v;}
    const T* get(const std::string& id){
        auto* c = this;
        do{auto& t=c->table; if(t.find(id)!=t.npos) return t[id];}
        while(c=c->prev);
        return 0;
    }

    // return a new context nested to this
    Context<T> push(){
        return Context(*this);
    }

    // After pop node is freed... dont use it.
    Context<T> pop(){
        auto& pr= *prev;
        prev=NULL;
        delete *this;
        return pr;
    }

    std::map<string,T*> table;
    Context<T>* prev;
};

class BlocoTree{
public:
    void setnode(Node& node){ this->node= &node;}
    void setnode(Node* node){ this->node= node;}
    void decorate_identifiers(){
        // TODO
    }

    Node* node;
    Context<NodeType> curtypecontext;
}; // class BlocoTree

} // namespace bloco

#endif //BLOCOTREE_HPP

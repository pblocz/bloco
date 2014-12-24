#ifndef _NODES_HPP_
#define _NODES_HPP_

# include "location.hh"
#include "codegeneration.hpp"

#include <vector>
#include <algorithm>
#include <iostream>

using std::pair; using std::vector;

class Node; class NodeType; class NodeProg;// Forward declare

// Define instantiation of context for nodes

enum operators{opint=256, masmas, menosmenos, mayorigual,menorigual, igualigual,
	       noigual,barrabarra, andand, menormenor, mayormayor};
enum tnode{decl, expr, type, prog, deffun};
enum ttype{tupl, namedTupl, arr, func, int_};
enum texpr{op, cte, anon, ident, arrdef};
typedef std::string _t;

typedef vector<Node *> NodeList;
typedef vector<pair<Node*, _t> > NamedNodeList;
typedef vector<NodeProg*> Context;

class Node{
public:
    parser::location loc;

    const tnode type;
    virtual void print(int p)=0;
    virtual void identifiers(Context &c);
    virtual void generate(CodeGenerate&){}

    Node(tnode t=(tnode) -1) :type(t){}
    virtual ~Node(){};
};

class NodeType: public Node {
public:
    ttype typetype;

    virtual void print(int p)=0;
    virtual void identifiers(Context &c);
    virtual bool operator==(const NodeType& n) const;
    virtual bool operator!=(const NodeType& n) const { return !(*this==n); }
    virtual size_t size() { return 10000; }

    NodeType(ttype t=(ttype)-1);
    virtual ~NodeType(){};
};

class NodeProg: public Node {
public:
    NodeList inst;
	NamedNodeList frame;
	int numArgs;

    NodeProg(NodeList * _inst) :Node(prog),inst(*_inst){};
    void print(int p);
    virtual void identifiers(Context &c,NamedNodeList _frame=NamedNodeList());
    virtual void generate(CodeGenerate& g);
    virtual ~NodeProg();
};

class NodeExpr: public Node {
public:
    texpr typeexpr;
    bool lvalue=false;
    NodeType * isa=nullptr;

    virtual void print(int p)=0;
    //virtual void identifiers(Context &c);
    NodeExpr(texpr t=(texpr)-1) :Node(expr),typeexpr(t) {}
    virtual ~NodeExpr() {};
};

class NodeExprCte: public NodeExpr {
public:
    int value;

    NodeExprCte(int v);
    void print(int p);
    virtual void generate(CodeGenerate& g);
    virtual void identifiers(Context &c);
    virtual ~NodeExprCte(){}
};

class NodeExprOp: public NodeExpr {
public:
    int oper;
    NodeList *args;

    NodeExprOp(int _oper, NodeList *_args);
    NodeExprOp(int _oper, NodeList _args) :NodeExprOp(_oper,new NodeList(_args)) {}
    void print(int p);
    virtual void identifiers(Context &c);
    virtual void generate(CodeGenerate& g);
    virtual ~NodeExprOp();
};

class NodeExprAnon: public NodeExpr {
public:
    NodeType* ret;
    NamedNodeList *args;
    NodeProg* prog;
    _t id;

    NodeExprAnon(NodeType * _ret, NamedNodeList *_args, NodeProg *_prog);
    void print(int p);
    virtual void generate(CodeGenerate&);
    virtual void identifiers(Context &c);
    virtual ~NodeExprAnon();
};

class NodeExprDefArr: public NodeExpr {
public:
    NodeType * arg;
    NodeExpr * size;

    NodeExprDefArr(Node *_arg, Node * _size);
    void print(int p);
    virtual void generate(CodeGenerate&);
    virtual void identifiers(Context &c);
    virtual ~NodeExprDefArr() { delete arg; delete size; }
};

class NodeExprId: public NodeExpr {
public:
    _t id;
	pair<int,int> decl {-1,-1};
    Context c;

    NodeExprId(_t _id);
    void print(int p);
    virtual void generate(CodeGenerate&);
    virtual void identifiers(Context &c);
    virtual ~NodeExprId();
};

class NodeTypeTuple: public NodeType {
public:
    NodeList *args;

    NodeTypeTuple(NodeList *_args);
    size_t size() { size_t s=0; for(auto arg:*args) s+=((NodeType*) arg)->size(); return s; }
    size_t offset(size_t i) { size_t o=0; for(auto arg:*args){ o+=((NodeType*) arg)->size(); if(!--i) break; } return o; }

    void print(int p);
    ~NodeTypeTuple();
};

class NodeTypeNamedTuple: public NodeType {
public:
    NamedNodeList *args;

    NodeTypeNamedTuple(NamedNodeList *_args);
    size_t size() { size_t s=0; for(auto arg:*args) s+=((NodeType*) arg.first)->size(); return s; }
    size_t offset(_t i) { 
        size_t o=0; 
        for(auto arg:*args){ o+=((NodeType*) arg.first)->size(); if(arg.second==i) break; } return o; 
    }
    void print(int p);
    virtual ~NodeTypeNamedTuple();
};

class NodeTypeArr: public NodeType {
public:
    NodeType * arg;

    NodeTypeArr(NodeType *_arg);
    virtual void generate(CodeGenerate&);
    size_t size() { return sizeof(void*); }
    void print(int p);
    virtual ~NodeTypeArr();
};

class NodeTypeFunc: public NodeType {
public:
    NodeType *ret; NodeList *args;
	bool modificable=true;

    NodeTypeFunc(NodeType *_ret, NodeList *_args);
    size_t size() { return modificable ? 2*sizeof(void*) : 0; }
	void generate(CodeGenerate&);
    void print(int p);
    virtual ~NodeTypeFunc();
};

class NodeTypeInt: public NodeType {
public:
    NodeTypeInt():NodeType(int_){}
    virtual void generate(CodeGenerate&);
    size_t size() { return sizeof(int); }
    void print(int p);
    ~NodeTypeInt();
};

class NodeDecl: public Node {
public:
    NodeType *arg;
    std::vector<NodeExprId> ids;
    NamedNodeList *args;
    Context c;

    NodeDecl(NodeType *_arg, _t id, NodeExpr *exp);
    void print(int p);
    virtual void generate(CodeGenerate&);
    virtual void identifiers(Context &c);
    void addargs(NodeExpr*,const _t&);
    virtual ~NodeDecl();
};

class NodeDeffun: public Node {
public:
    NodeType *ret;
    _t id;
    NamedNodeList *args;
    NodeProg * prog;

    NodeDeffun(NodeType *_ret, _t id, NamedNodeList* _args, NodeProg* _prog)
	:Node(deffun),ret(_ret),id(id),args(_args),prog(_prog){};
    void print(int p);
    virtual void identifiers(Context &c);
    virtual void generate(CodeGenerate&);
    virtual ~NodeDeffun(){};
};

Node * opbinario(int op, Node * arg1, Node * arg2);
Node * opunario(int op, Node * arg);

#endif // _NODES_HPP_

//#include "bloco.hpp"
#include "nodes.hpp"
// #include "context.hpp"

#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

inline void tabs(int prof){for(int i=0; i<prof; i++) cout<<'\t';}

NodeType::NodeType(ttype t) :Node(tnode::type),typetype(t){}

bool NodeType::operator==(const NodeType& n) const{
    if(typetype==n.typetype
			&&type==n.type){
        if(typetype==arr) 
          return *((NodeTypeArr*) this)->arg == *((NodeTypeArr*) &n)->arg;
        else if(typetype==tupl) {
            auto &v = *((NodeTypeTuple*) &n)->args; int i = 0;
            for (auto arg: *((NodeTypeTuple*) this)->args){
                if(*((NodeType*)arg) != *((NodeType*)v[i])) return false; i++;
            }
            return true;
        }
        else if(typetype==namedTupl) {
            auto &v = *((NodeTypeNamedTuple*) &n)->args; int i = 0;
            for (auto arg: *((NodeTypeNamedTuple*) this)->args){
                if(*((NodeType*)arg.first) != *((NodeType*)v[i].first)) return false;
                else if (arg.second != v[i].second) return false; 
                i++;
            }
            return true;
        }
        else if(typetype==func) {
            const NodeTypeFunc* f1 = (NodeTypeFunc*) &n, *f2= (NodeTypeFunc*) this;
            if(f1->ret== f2->ret || *(f1->ret) == *(f2->ret)) {
                auto &v = *f2->args; int i = 0;
                for (auto arg: *f1->args){
                	if (i>=v.size()) return false;
                    if(*((NodeType*)arg) != *((NodeType*)v[i])) return false; i++;
                }
                return true;
            }
        }
        else if(typetype==int_) return true;
    }
    return false;
}

void NodeProg::print(int p) {
	tabs(p); cout<<"Programa:"<<endl;
	tabs(p+1); cout << "NumArgs in frame: " << numArgs << endl;
	tabs(p+1); cout << "Frame: ";
	for (auto p: frame) cout << p.second << ","; cout << endl;
	for(Node *i:inst) i->print(p+1);
}
NodeProg::~NodeProg(){for(Node *v:inst) delete v;}

NodeExprCte::NodeExprCte(int v) :NodeExpr(cte),value(v) {}

void NodeExprCte::print(int p) {
	tabs(p); cout<<"cte: "<<value<< " type: ";
	if(isa!=nullptr) isa->print(0);
	else cout << endl;

}

NodeExprOp::NodeExprOp(int _oper, NodeList *_args) :NodeExpr(op){
	oper=_oper;  args=_args;
	if(_oper=='[' && ((NodeExpr *)(*args)[0])->lvalue) this->lvalue=true;
	if(_oper=='.' && ((NodeExpr *)(*args)[0])->lvalue) this->lvalue=true;
}
void NodeExprOp::print(int p) {
	tabs(p); cout<<"Op: "<<oper<<endl;

	if(isa!=nullptr){ tabs(p+1); cout << "Type:" << endl; isa->print(p+1); }
	tabs(p+1); cout << "Value:" << endl;
	for(Node *arg:*args) if(arg!=NULL) arg->print(p+1);
}
NodeExprOp::~NodeExprOp(){for(Node * arg:*args) delete arg;delete args;}

NodeExprAnon::NodeExprAnon(NodeType * _ret, NamedNodeList *_args, NodeProg *_prog)
 	:NodeExpr(anon) {
	lvalue=false;
	this->ret=_ret;
	this->args=_args;
	this->prog=_prog;
}
void NodeExprAnon::print(int p) {
	tabs(p); cout<<"Def:"<<endl;
	tabs(p+1); cout<<"recibe:"<<endl;
	for(pair<Node *, _t> arg:*args) {
		tabs(p+1); cout<<"tipo:"<<endl;
		arg.first->print(p+1);
		tabs(p+1); cout<<"id: "<<arg.second<<endl;
	}
	tabs(p+1); cout<<"devuelve"<<endl;
	if (ret!=NULL) ret->print(p+1);
	tabs(p+1); cout<<"código"<<endl;
	prog->print(p+1);
}
NodeExprAnon::~NodeExprAnon(){
	delete ret;
	delete prog;
	for(pair<Node *, _t> arg:*args) delete arg.first;
}

NodeExprDefArr::NodeExprDefArr(Node *_arg, Node * _size)
	:NodeExpr(arrdef) {
		arg=(NodeType*)_arg; size=(NodeExpr *) _size;
}

void NodeExprDefArr::print(int p) {
	tabs(p); cout<<"array def"  << ":" << endl;
	arg->print(p+1);
	cout<<"size:"<<endl;
	size->print(p+1);
}

NodeExprId::NodeExprId(_t _id) :NodeExpr(ident) {id=_id;this->lvalue=true;}
void NodeExprId::print(int p) {
	tabs(p); cout<<"id: "<<id<< " decl(" << decl.first << "," << decl.second << ") of type:" << endl;
	if(isa!=nullptr) isa->print(p+1);
	// cout << endl;
}
NodeExprId::~NodeExprId(){}

NodeTypeTuple::NodeTypeTuple(NodeList *_args) :NodeType(tupl),args(_args) {}
void NodeTypeTuple::print(int p) {
	tabs(p); cout<<"tupla:"<<endl;
	for(auto arg:*args)arg->print(p+1);
}
NodeTypeTuple::~NodeTypeTuple(){
	for(auto arg:*args) delete arg; delete args;
}

NodeTypeNamedTuple::NodeTypeNamedTuple(NamedNodeList *_args) :NodeType(namedTupl),args(_args) {}

void NodeTypeNamedTuple::print(int p) {
	tabs(p); cout<<"tuplaNom:"<<endl;
	for(auto arg:*args)
		arg.first->print(p+1),tabs(p+1),cout<<arg.second<<endl;
}
 NodeTypeNamedTuple::~NodeTypeNamedTuple(){
	for(auto arg:*args) delete arg.first;
	delete args;
}

NodeTypeArr::NodeTypeArr(NodeType *_arg) :NodeType(arr) {arg=_arg;}
void NodeTypeArr::print(int p) {
	tabs(p); cout<<"array:"<<endl; arg->print(p+1);
}
NodeTypeArr::~NodeTypeArr() {delete arg;}

NodeTypeFunc::NodeTypeFunc(NodeType *_ret, NodeList *_args) :NodeType(func) {
	ret=_ret; args=_args;
}
void NodeTypeFunc::print(int p) {
	tabs(p); cout<<"funcion"<<endl;
	tabs(p+1);cout<<"recibe"<<endl;
	for(auto aux:*args) aux->print(p+1),tabs(p+1);
	tabs(p+1); cout<<"devuelve"<<endl; if(ret!=nullptr) ret->print(p+1);
}
NodeTypeFunc::~NodeTypeFunc() {delete ret; delete args;}

void NodeTypeInt::print(int p) {tabs(p);cout<<"Ent"<<endl;}
NodeTypeInt::~NodeTypeInt(){}

NodeDecl::NodeDecl(NodeType *_arg, _t _id, NodeExpr *exp)
	:Node(decl) {
	arg=_arg;
	args=new NamedNodeList();
	ids.push_back(NodeExprId(_id));
	args->push_back(make_pair((Node*) exp, _id));
}
void NodeDecl::print(int p) {
	tabs(p); cout<<"Declaración de tipo"<<endl;
	arg->print(p+1);
	tabs(p+1); cout<<"Y variables:"<<endl;
	int i=0;
	for(auto aux:*args) {
		tabs(p); cout<<"variable con id: "<<aux.second;
		if(ids.size()) cout << "(" << ids[i].decl.first << ',' << ids[i].decl.second << ')';
		cout <<endl;

		if(aux.first!=nullptr) aux.first->print(p+1);
	i++; }
}

void NodeDecl::addargs(NodeExpr* e,const _t& id){
	args->push_back(make_pair(e,id));
	ids.push_back(NodeExprId(id));
}

NodeDecl::~NodeDecl() {
	for(auto aux:*args) delete aux.first;
	delete arg;
	delete args;
}

void NodeDeffun::print(int p){
	tabs(p);
	std::cout << "function defition" << std::endl;

	tabs(p+1);cout << "name: " << id << endl;

	tabs(p+1);cout << "return type:" << endl;
	if(ret) ret->print(p+1);

	tabs(p+1);cout << "arguments:" << endl;
	for(pair<Node *, _t> arg:*args) {
		tabs(p+1); cout<<"tipo:"<<endl;
		arg.first->print(p+1);
		tabs(p+1); cout<<"id: "<<arg.second<<endl;
	}

	tabs(p+1);cout << "code:" << endl;
	prog->print(p+1);
}

Node * opbinario(int op, Node * arg1, Node * arg2) {
	NodeList *aux=new NodeList; aux->push_back(arg1); aux->push_back(arg2);
	return new NodeExprOp(op, aux);
}

Node *opunario(int op, Node *arg) {
	NodeList *aux=new NodeList; aux->push_back(arg);
	return new NodeExprOp(op, aux);
}

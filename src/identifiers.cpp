//#include "context.hpp"
#include "nodes.hpp"

using namespace std;

void error(string msg, Node *n) {
	cout<<"ERROR: "<<msg<<endl;
	cout<<"At node: "<<endl;
	n->print(0);
	abort();
}

int randomint = 0;

NodeList* unzip(NamedNodeList* n) {
	auto aux=new NodeList(); for(auto i:*n) aux->push_back(i.first);
	return aux;
}

void Node::identifiers(Context &c) {}
void NodeType::identifiers(Context &c) {}

void NodeProg::identifiers(Context &c,NamedNodeList _frame) {
	frame=_frame;
	numArgs=_frame.size();
	c.push_back(this);
	for(auto i:inst) i->identifiers(c);
	c.pop_back();
}

void NodeExprCte::identifiers(Context &c) {
	this->isa=new NodeTypeInt;
}
void NodeExprOp::identifiers(Context &c) {
	//primero, se buscan los tipos de los argumentos, salvo el '.','++','--'. 
	//Estos tienen segundos argumentos que no deben ser procesados
	//
	//En el primer caso, es porque el argumento es un identificador sin valor fuera del struct.
	//Los otros dos, porque el ++/-- prefijo es unario y el postfijo binario, para distinguirlos.
	if(oper!='.' && oper!=masmas && oper!=menosmenos)
		for(auto arg: *args) arg->identifiers(c);
	else (*args)[0]->identifiers(c); 

	//Ya se han hecho los identificadores, ahora pensamos en los tipos. Primero van los raros:
	if(oper=='\'') {
		isa=((NodeExpr *)(*args)[0])->isa;
	}
	else if(oper==',') {
		isa=((NodeExpr *)(*args)[1])->isa;
	}
	else if(oper=='=') {
		if(!((NodeExpr *)(*args)[0])->lvalue) error("Incompatible left side of asignation",this);
		if(((NodeExpr *)(*args)[0])->isa==nullptr) error("Asignation to void",this);
		if(((NodeExpr *)(*args)[1])->isa==nullptr) error("Asignation to void",this);

		NodeExpr* epr = ((NodeExpr *)(*args)[1]);
		NodeType* n1=(((NodeExpr *)(*args)[0])->isa);
		NodeType* n2=(((NodeExpr *)(*args)[1])->isa);
		if(n2==(NodeType*)0x1) n2 = (((NodeExpr *)(*args)[1])->isa) = nullptr;
		if(n1==(NodeType*)0x1) n1 = (((NodeExpr *)(*args)[0])->isa) = nullptr;
		/*cout<<"beg"<<endl;
		if(n1!=nullptr && n2!=nullptr) {
			n1->print(0), n2->print(0);
			if(*n1==*n2) cout<<"ok1"<<endl;
			if(*n1!=*n2) cout<<"nok1"<<endl;
		}
		if(n1==nullptr || n2==nullptr) {
			cout<<"k"<<endl; 
		}*/
		if(n1==nullptr || n2==nullptr|| *n1!=*n2) error("Incompatible types in asignation",this);
		//cout<<"end"<<endl;

		isa=((NodeExpr *)(*args)[1])->isa;
	}
	else if(oper=='@') {
		if(*(new NodeTypeInt)!=*(((NodeExpr*)(*args)[0])->isa))
			error("'@' without boolean expression",this);
	}
	else if(oper=='?') {
		this->isa=((NodeExpr*)(*args)[1])->isa;
		if(((NodeExpr*)(*args)[0])->isa==nullptr) error("void argument",this);
		if(this->args->size()==3 && *(this->isa)!=*((NodeExpr*)(*args)[2])->isa)
			error("Incompatible types in ?",this);
	}
	else if(oper=='[') {
		if(((NodeExpr*)(*args)[0])->isa==nullptr) error("void argument",this);
		if(((NodeExpr *)(*args)[1])->isa->typetype!=int_)
			error("Incompatible array index",this);
		isa=((NodeTypeArr *)((NodeExpr *)(*args)[0])->isa)->arg;
	}
	else if(oper=='(') {
		if(((NodeExpr*)(*args)[0])->isa==nullptr) error("void argument",this);
		if(((NodeExpr *)(*args)[0])->isa->typetype!=func) error("call to a non-function",this);
		else {
			this->isa=((NodeTypeFunc *)((NodeExpr *)(*args)[0])->isa)->ret;
		}
	}
	//Ahora va ++, --, que aunque son diferentes segun si son prefijos o postfijos, se tratan igual.
	else if(oper==masmas || oper==menosmenos) {
		if(((NodeExpr*)(*args)[0])->isa==nullptr) error("void argument",this);
		if( ((NodeExpr*)(*args)[0])->isa->typetype!=int_) error("Bad type in operator",this);
			isa=new NodeTypeInt;	
	}

	//los otros unarios:
	else if(args->size()==1) {
		if(oper=='b'||oper=='c') error("Not implemented operation",this);
		else if(((NodeExpr*)(*args)[0])->isa==nullptr) error("void argument",this);
		else if(oper=='r')
			if(((NodeExpr*)(*args)[0])->isa==nullptr) error("void argument", this);
		else {
			if(((NodeExpr*)(*args)[0])->isa->typetype!=int_) error("Bad type in operator",this);
			isa=new NodeTypeInt;
		}	
	}
	//Los que quedan, son todos tipo int->int->int
	else if( oper==barrabarra||oper==andand||oper=='|'||oper=='^'||oper=='&'||oper==igualigual||
		oper==noigual||oper==menorigual||oper==mayorigual||oper=='<'||oper=='>'||
		oper==menormenor||oper==mayormayor||oper=='+'||oper=='-'||oper=='*'||oper=='/'||oper=='%') {

		if( ((NodeExpr*)(*args)[0])->isa==nullptr||((NodeExpr*)(*args)[1])->isa==nullptr|| 
			*(new NodeTypeInt)!=*(((NodeExpr*)(*args)[0])->isa) ||
			*(new NodeTypeInt)!=*(((NodeExpr*)(*args)[1])->isa)) 
				error("Bad type in binary operator",this);
		isa=new NodeTypeInt ;
	}
	else error("You shouldnt be here",this);
}

void NodeExprAnon::identifiers(Context &c) {
	lvalue=false;

	// generamos el nombre aleatorio
	stringstream strm; strm << "__anon" << randomint++;
	id = strm.str();

	isa=new NodeTypeFunc(ret, unzip(args));
	prog->identifiers(c,*args);
}

void NodeExprDefArr::identifiers(Context &c) {
	lvalue=false;
	isa=new NodeTypeArr(arg);
}
void NodeExprId::identifiers(Context &c) {
	this->c = c;
	for(unsigned long i=0; i<c.size(); i++) {
		auto aux=c[c.size()-i-1]->frame;
		for(unsigned long j=0; j<aux.size(); j++)
			if(aux[j].second==id) {
				decl=pair<int,int>(i,j);
				isa=(NodeType *) aux[j].first;
				lvalue=true;
				return;
			}
	}
}

void NodeDecl::identifiers(Context &c) {
	this->c = c;
	for(auto x:*args) {
		auto& aux=c.back()->frame;
		for(unsigned long j=0; j<aux.size(); j++)
			if(aux[j].second==x.second) {
				error("defined variable", this);
				abort();
			}
		if(x.first!=nullptr) {
			x.first->identifiers(c);
			if(! (*(((NodeExpr *)x.first)->isa)==*arg)) error("Types not match", this),abort();
		}
		aux.push_back(make_pair(arg,x.second));
	}
	for(auto& id:ids) id.identifiers(c);
}
void NodeDeffun::identifiers(Context &c) {
	auto t=new NodeTypeFunc(ret,unzip(args));
	t->modificable=false;
	c.back()->frame.push_back(make_pair(t,id));
	prog->identifiers(c,*args);
}

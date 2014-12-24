#include "nodes.hpp"

using namespace std;

int auxint = 0;

void namednodelistgenerateassign(CodeGenerate& g,NamedNodeList* args){
	bool first=true;
	for(auto arg: *args) {
		if(first) first=false;
		else g.addcode(",");

		g.addcode(arg.second);
		if(arg.first!=nullptr) {
			g.addcode("=");
			arg.first->generate(g);
		}
	}
}


void namednodelistgeneratefun(CodeGenerate& g,NamedNodeList* args){
	for(auto arg: *args) {
		g.addcode(",");

		arg.first->generate(g);
		g.addcode(arg.second);

	}
}

size_t framesize(NodeProg* _prog) { NodeProg& prog=*_prog;
	size_t size = sizeof(void*);
	for(auto& f: prog.frame) {
		if(f.first->type != type){ cerr << "error in framesize" << endl; abort(); }
		size+=((NodeType*) f.first)->size();
	}
	return size;
}

size_t frameoffset(NamedNodeList& frame, size_t s) {
	size_t size = sizeof(void*);
	for(size_t si=0; si<s; si++){ auto& f = frame[si];
		if(f.first->type != type){ cerr << "error in framesize" << endl; abort(); }
		size+=((NodeType*) f.first)->size();
	}
	return size;
}

string generategetframe(size_t frames,size_t s,const Context& c) {
	stringstream strm; strm << "((";
	for(size_t i=0; i<frames; i++) strm<<'*';
	strm<< "(char*";
	for(size_t i=0; i<frames; i++) strm<<'*';
	strm<<") frame";
	strm << ") + " << frameoffset(c[c.size()-1-frames]->frame,s) << ")";
	return strm.str();
}

string generatefun(CodeGenerate& g, NodeType* t) {
	NodeTypeFunc *f = (NodeTypeFunc*)t;

	CodeGenerate g1; if(f->ret!=nullptr) f->ret->generate(g1); else g1.addcode("void");

	g.addcode(g1.sstr.str()); g.addcode("(*) ( void*");
	bool first=false;//true;
	for(auto arg: *f->args) { if(first) first=false; else g.addcode(",");
		arg->generate(g);
	}
	g.addcode(")");
	return g1.sstr.str();
// int (*code)(void*)
}


void NodeProg::generate(CodeGenerate& g) {
	// if(numArgs) {
		stringstream strm;
		strm << "void *frame = malloc(" << framesize(this) << ");\n";
		strm << "*(void**)frame=_frame;\n";
		for(int i=0; i<numArgs; i++) {
			CodeGenerate g1; frame[i].first->generate(g1);

			strm << "((" << g1.sstr.str() << "*)" << generategetframe(0,i,Context {this})
				 << ")[0] = " <<  frame[i].second << ";\n";
		}
		g.addcode(strm.str());
	// }

	for(auto i:inst){
		i->generate(g);

	 	if(i->type!=deffun) g.addcode(";\n");
	}
}

void NodeExprCte::generate(CodeGenerate& g) {
	stringstream strm;
	strm << value;
	g.addcode(strm.str());
}


// TODO: finalizar if
void NodeExprOp::generate(CodeGenerate& g) {
	stringstream strm;
	string op;
	if(oper==masmas){
		op="++";
	}
	else if  (oper==menosmenos) op="--";
	else if (oper==noigual) op="!=";
	else if (oper==mayorigual) op=">=";
	else if (oper==menorigual) op="<=";
	else if (oper==igualigual) op="==";
	else if (oper==barrabarra) op="||";
	else if (oper==andand) op="&&";
	else if (oper==menormenor) op="<<";
	else if (oper==mayormayor) op=">>";
	else if (oper=='r') op="return";
	else op=(char)oper;


	// generamos el código
	if(op=="?") {
		// TODO: que pasa si no se puede poner un if el el sition;
		// TODO: que pasa con el if que tiene solo 1 rama?
		// Si args es algo con prog, entonces en if
		// Si no entonces en operador ?

		// g.addcode("if (");
		g.addcode("(");
		args[0][0]->generate(g); // generate condition
		// g.addcode(") {");

		// if(args->size()==2) args[0][1]->generate(g);
		// else{
			g.addcode("?");
			NodeExpr *arg1= static_cast<NodeExpr*>(args[0][1]),
			         *arg2= static_cast<NodeExpr*>(args[0][2]);
			arg1->generate(g); // if(arg1->typeexpr==anon) g.addcode("(frame);");
			g.addcode(":");
			// g.addcode("} else {");
			arg2->generate(g); //if(arg2->typeexpr==anon) g.addcode("(frame);");
			// g.addcode("}");
		//}
		g.addcode(")");
	}
	else if(op=="@") {
		g.addcode("while("); static_cast<NodeExpr*>(args[0][0])->generate(g);
		g.addcode(") {");

		NodeExprAnon* a = static_cast<NodeExprAnon*>(args[0][1]);

		CodeGenerate g1;
		string  retstr=generatefun(g1,a->isa);

		strm << " __aux"<< auxint++;
		string name = strm.str();
		strm.str("");

		strm << retstr << name << "(anon_t f) {\n";
		strm << "((" << g1.sstr.str() << ") f.code)( f.frame );";
		strm << "}\n";

		g.addhead(strm.str());

		g.addcode(name); g.addcode("(");
		a->generate(g);
		g.addcode(")");

	    g.addcode("; }");
	}
	else if(op=="(") {
		CodeGenerate g1;
		// g1.addcode("struct {");
		string  retstr=generatefun(g1,((NodeExpr*)args[0][0]) -> isa);
		// g1.addcode("; void* context; }");

		strm << " __aux"<< auxint++;
		string name = strm.str();
		strm.str("");

		strm << retstr << name << "(anon_t f";
		for (int i=1; i<args->size(); i++) {
			CodeGenerate g1; ((NodeExpr*)args[0][i])->isa->generate(g1); strm << ", " << g1.sstr.str() << " f" << i;
		}
		strm << ") {\n";

		if(retstr!="void") strm << "return ";
		strm << "((" << g1.sstr.str() << ") f.code)( f.frame";
		for (int i=1; i<args->size(); i++) strm << ", f" << i;
		strm << ");";

		strm << "}\n";

		g.addhead(strm.str());

		g.addcode(name); g.addcode("(");
		args[0][0]->generate(g);
		for (int i = 1; i< args->size(); i++) { g.addcode(","); args[0][i]->generate(g); }
		g.addcode(")");

    // ((struct { int (*code)(void*); void* context; }*) f)->code(((struct { int (*code)(void*); void* context; }*) f)->context);


	}
	else if(op=="[") {
		args[0][0]->generate(g); 		
		g.addcode("[");
		args[0][1]->generate(g);
		g.addcode("]");
	}
	else if (args[0].size()==1) {
		g.addcode(op);
		args[0][0]->generate(g);
	}
	else { // operadores binarios
		args[0][0]->generate(g);
		g.addcode(op);
		args[0][1]->generate(g);
	}
}

void NodeExprAnon::generate(CodeGenerate& g) {
	// TODO
	CodeGenerate g1;
	if(ret!=nullptr) ret->generate(g1); else g1.addcode("void");
	g1.addcode(id);
	g1.addcode("( void* _frame");
	namednodelistgeneratefun(g1,args);
	g1.addcode(")");

	g1.addcode("{\n");
	prog->generate(g1);
	g1.addcode("}\n");

	g.addhead(g1.headerstr.str());
	g.addhead(g1.sstr.str());

	// g.addcode("(struct {");
	// if(ret!=nullptr) ret->generate(g); else g.addcode("void");
	// g.addcode("(*code)(void*");
	// for(auto arg: *args) { g.addcode(","); arg.first->generate(g); }
	// g.addcode("); void* context;})");
	g.addcode("(anon_t)");
	g.addcode("{"); g.addcode(id); g.addcode(",frame}");

	// CodeGenerate g1;
	// if(ret!=nullptr) ret->generate(g1); else g1.addcode("void");
	// g1.addcode(id+"_code");
	// g1.addcode("( void* _frame");
	// namednodelistgeneratefun(g1,args);
	// g1.addcode(")");
	//
	// g1.addcode("{\n");
	// prog->generate(g1);
	// g1.addcode("}\n");
	//
	//
	// g1.addcode("struct {");
	// if(ret!=nullptr) ret->generate(g1); else g1.addcode("void");
	// g1.addcode("(*code)(void*");
	// for(auto arg: *args) { g1.addcode(","); arg.first->generate(g1); }
	// g1.addcode("); void* context;}"); g1.addcode(id); g1.addcode("=");
	// g1.addcode("{"); g1.addcode(id+"_code"); g1.addcode("};\n"); //g1.addcode(",frame};\n");
	//
	// g.addhead(g1.sstr.str());
	//
	// g.addcode("((");g.addcode(id); g.addcode(".context = frame)");
	// g.addcode(","); g.addcode(id); g.addcode(")");
}

void NodeExprId::generate(CodeGenerate& g) {
	//g.addcode(id);
	CodeGenerate g1; isa->generate(g1);

	g.addcode("( ("); g.addcode(g1.sstr.str()); g.addcode("*)");
	g.addcode(generategetframe(decl.first,decl.second,c));
	g.addcode(")[0]");
}

void NodeDecl::generate(CodeGenerate& g) {
	// stringstream strm;
	// arg->generate(g);

	// namednodelistgenerateassign(g,args);

	for(int i=0; i<args->size(); i++) { if(args[0][i].first==nullptr) continue;
		ids[i].generate(g);
		g.addcode("=");
		(*args)[i].first->generate(g);
		g.addcode(";\n");
	}
}

void NodeTypeInt::generate(CodeGenerate& g){
	g.addcode("int");
}

void NodeTypeFunc::generate(CodeGenerate& g){
	g.addcode("anon_t");
}

void NodeDeffun::generate(CodeGenerate& g){
	CodeGenerate g1;
	ret->generate(g1);
	g1.addcode(id);
	g1.addcode("(void* _frame");
	namednodelistgeneratefun(g1,args);
	g1.addcode(")");

	g1.addcode("{\n");
	prog->generate(g1);
	g1.addcode("}\n");

	g.addhead(g1.headerstr.str());
	g.addhead(g1.sstr.str());
}

void NodeTypeArr::generate(CodeGenerate& g){
	arg->generate(g); g.addcode("*");
}

void NodeExprDefArr::generate(CodeGenerate& g){
	stringstream strm; strm<< "malloc(" << arg->size() << "* (";
	g.addcode(strm.str());
	size->generate(g);
	g.addcode(") )");
}
#ifndef CODEGENERATION_H__
#define CODEGENERATION_H__

#include <sstream>
#include <string>

using std::string;

class CodeGenerate {
public:
	bool firsthead = true;
	bool firstbody = true;

	void addcode(const string& str) {
		if(firstbody) firstbody=false;
		else sstr << ' ';
		sstr << str; }
	void addhead(const string& str) {
		if(firsthead) firsthead=false;
		else headerstr << ' ';
		headerstr << ' ' << str << ' '; }

    std::stringstream headerstr;
	std::stringstream sstr;

	/* data */
};


#endif // CODEGENERATION_H__

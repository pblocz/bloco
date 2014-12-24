#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <map>
#include <string>
#include <vector>

namespace bloco {

template <class T>
class Context {
public:
    Context(){}
    virtual ~Context(){}

    void insert(const std::string id,T v){st.back()[id]=v;}
    const T* get(const std::string &id){
		T* a=nullptr;
        for(auto t:st) if(t.find(id)!=t.end()) a=t[id];
        return a;
    }

    // return a new context nested to this
    void push(){
		std::map<std::string, T*> m;
		st.push_back(m);
    }

    // After pop node is freed... dont use it.
   	void pop(){
		st.pop_back();
    }

	std::vector<std::map<std::string, T> > st;
};

} // namespace bloco

#endif //CONTEXT_HPP

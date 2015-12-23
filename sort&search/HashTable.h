#ifndef SORT_SEARCH_HASHTABLE_H_
#define SORT_SEARCH_HASHTABLE_H_

#include <tr1/unordered_set>
#include "../headers/Funcionario.h"

struct funcHash {
	int operator()(const Funcionario &f1) const {
		return f1.getID();
	}

	bool operator()(const Funcionario &f1, const Funcionario &f2) const {
		return f1 == f2;
	}
};


typedef tr1::unordered_set<Funcionario, funcHash, funcHash> tabHFunc;

#endif /* SORT_SEARCH_HASHTABLE_H_ */

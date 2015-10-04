#ifndef SRC_CONDOMINIO_H_
#define SRC_CONDOMINIO_H_

#include "Header.h"
#include "Condomino.h"

class Condominio{
private:
	int numFuncionarios = 0;
	float fundos = 0;
	vector <Condomino *> moradores;
public:
	Condominio(){
		this->fundos = 5000;
	}
	void fimDoMes();
	bool contratarFuncionarios(); //TODO
};

#endif

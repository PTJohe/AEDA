#ifndef SRC_CONDOMINIO_H_
#define SRC_CONDOMINIO_H_

#include "../headers/Condomino.h"
#include "../headers/Header.h"

class Condominio{
private:
	int numFuncionarios;
	float fundos;
	vector <Condomino *> moradores;
public:
	Condominio(){
		this->fundos = 5000;
		this->numFuncionarios = 0;
		this->fundos = 0;
	}
	void fimDoMes();
	bool contratarFuncionarios(); //TODO
};

#endif

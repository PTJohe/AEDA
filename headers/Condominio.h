#ifndef HEADERS_CONDOMINIO_H_
#define HEADERS_CONDOMINIO_H_

#include "../headers/Condomino.h"
#include "../headers/Header.h"

class Condomino;

class Condominio{
private:
	int numFuncionarios;
	float fundos;
	vector <Condomino *> moradores;
	vector <Habitacao *> propriedades;
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

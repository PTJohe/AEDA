#ifndef SRC_CONDOMINO_H_
#define SRC_CONDOMINO_H_

#include "../headers/Habitacao.h"
#include "../headers/Header.h"

class Condomino {
private:
	string nome;
	int NIF;
	vector<Habitacao *> propriedades;
public:
	Condomino(string nome, int NIF){
		this->nome = nome;
		this->NIF = NIF;
	}
	vector<Habitacao *> getPropriedades();
	void requisitarLimpeza(); //TODO
	void requisitarCanalizacao(); //TODO
	void requisitarPintura(); //TODO
	void display() const;
};

#endif

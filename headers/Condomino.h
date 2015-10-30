#ifndef HEADERS_CONDOMINO_H_
#define HEADERS_CONDOMINO_H_

#include "../headers/Header.h"
#include "../headers/Habitacao.h"

class Condomino {
private:
	string nome;
	string NIF;
	vector<Habitacao *> propriedades;
public:
	Condomino(){
		this->nome = "NAO DEFINIDO";
		this->NIF = "NAO DEFINIDO";
	}
	Condomino(string nome, string NIF){
		this->nome = nome;
		this->NIF = NIF;
	}
	vector<Habitacao *> getPropriedades();
	string getNome() const;
	string getNIF() const;
	void setNome(string nome);
	void setNIF(string NIF);
	void setPropriedades(vector<Habitacao*> propriedades);
	bool addPropriedade(Habitacao* h1);

	void requisitarLimpeza(); //TODO
	void requisitarCanalizacao(); //TODO
	void requisitarPintura(); //TODO
	void info() const;
};

#endif

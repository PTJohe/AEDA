#ifndef HEADERS_CONDOMINO_H_
#define HEADERS_CONDOMINO_H_

#include "../headers/Header.h"
#include "../headers/Habitacao.h"

class Condomino {
private:
	string nome;
	string NIF;
	int fundosMensais;
	int divida;
	vector<Habitacao *> propriedades;
public:
	Condomino(){
		this->nome = "NAO DEFINIDO";
		this->NIF = "NAO DEFINIDO";
		this->fundosMensais = 0;
		this->divida = 0;
	}
	Condomino(string nome, string NIF){
		this->nome = nome;
		this->NIF = NIF;
		this->fundosMensais = 0;
		this->divida = 0;
	}
	Condomino(string nome, string NIF, int fundosMensais, int divida){
			this->nome = nome;
			this->NIF = NIF;
			this->fundosMensais = fundosMensais;
			this->divida = divida;
		}
	vector<Habitacao *> getPropriedades();
	string getNome() const;
	string getNIF() const;
	void setNome(string nome);
	void setNIF(string NIF);
	void setPropriedades(vector<Habitacao*> propriedades);
	bool addPropriedade(Habitacao* h1);
	bool operator== (const Condomino c1) const;

	void requisitarLimpeza(); //TODO requisitarLimpeza()
	void requisitarCanalizacao(); //TODO requisitarCanalizacao()
	void requisitarPintura(); //TODO requisitarPintura()
	void info() const;
};

#endif

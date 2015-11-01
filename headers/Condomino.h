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
	vector<Habitacao *> habitacoes;
public:
	Condomino();
	Condomino(string nome, string NIF);
	Condomino(string nome, string NIF, int fundosMensais, int divida);

	string getNome() const;
	string getNIF() const;
	int getFundosMensais() const;
	int getDivida() const;
	vector<Habitacao *> getHabitacoes();

	void setNome(string nome);
	void setNIF(string NIF);
	void setHabitacoes(vector<Habitacao*> propriedades);
	bool addPropriedade(Habitacao* h1);
	bool operator==(const Condomino c1) const;

	void requisitarLimpeza(); //TODO requisitarLimpeza()
	void requisitarCanalizacao(); //TODO requisitarCanalizacao()
	void requisitarPintura(); //TODO requisitarPintura()

	void info() const;
	void infoHabitacoes() const;
	void infoRenda() const;
};

#endif

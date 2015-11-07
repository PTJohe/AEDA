#ifndef HEADERS_FUNCIONARIO_H_
#define HEADERS_FUNCIONARIO_H_

#include "../headers/Header.h"

class Funcionario {
private:
	string nome;
	int id;
	bool ocupado;
	string especialidade;
	int servicosEfectuados;

public:
	Funcionario(string especialidade);
	Funcionario(string especialidade, int id, int servicosEfectuados);

	int getID() const;
	bool isOcupado() const;
	string getEspecialidade() const;
	int getServicosEfectuados() const;

	void setOcupado(bool status);
	void setEspecialidade(string especialidade);
	void addServicoEfectuado();

	bool operator== (const Funcionario f1) const;
	bool operator< (const Funcionario f1) const;

	void info() const;
};


#endif

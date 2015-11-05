#ifndef HEADERS_FUNCIONARIO_H_
#define HEADERS_FUNCIONARIO_H_

#include "../headers/Header.h"

class Funcionario {
private:
	string nome;
	int id;
	bool ocupado;
	string especialidade;

public:
	Funcionario(string especialidade);
	Funcionario(string especialidade, int id);

	int getID() const;
	bool getOcupado() const;
	string getEspecialidade() const;

	void setOcupado(bool status);
	void setEspecialidade(string especialidade);

	bool operator== (const Funcionario f1) const;
	bool operator< (const Funcionario f1) const;
};


#endif

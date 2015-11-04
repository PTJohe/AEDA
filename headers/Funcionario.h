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
	Funcionario();
	Funcionario(string nome,string especialidade);

	string getNome() const;
	int getID() const;
	bool getOcupado() const;
	string getEspecialidade() const;

	void setNome(string nome);
	void setOcupado(bool status);
	void setEspecialidade(string especialidade);
};


#endif

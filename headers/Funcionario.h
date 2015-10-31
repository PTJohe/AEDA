/*
 * Funcionario.h
 *
 *  Created on: 31 Oct 2015
 *      Author: simao
 */

#ifndef HEADERS_FUNCIONARIO_H_
#define HEADERS_FUNCIONARIO_H_

#include "../headers/Header.h"

#define pathEspecialidades "../savedata/especialidades.txt"

class Funcionario {
private:
	string nome;
	static int id;
	bool status; // false -> ocupado
	vector<string> especialidades;

public:
	Funcionario(string nome,string especialidade);
	string getNome(){return nome;}
	bool getStatus(){return status;}
	vector<string> getEspecialidades(){return especialidades;}
	void giveEspecialidade(string especialidade);

};


#endif /* HEADERS_FUNCIONARIO_H_ */

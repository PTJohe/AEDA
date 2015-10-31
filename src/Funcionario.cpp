/*
 * Funcionario.cpp
 *
 *  Created on: 31 Oct 2015
 *      Author: simao
 */
#include "../headers/Funcionario.h"

int Funcionario::id = 1;

void verificaEspecialidades(string toCompare){
	vector<string> tempVec;
	string tempStr;
	fstream especs;

	especs.open(pathEspecialidades);

	while(!especs.eof()){
		getline(especs,tempStr);
		tempVec.push_back(tempStr);
	}

	if(!sequentialSearch(tempVec,toCompare)){
		especs << toCompare << endl;
	}

}


Funcionario::Funcionario(string nome,string especialidade){
	this->nome = nome;
	this->especialidades.push_back(especialidade);
	this->status = true;
	id++;
	verificaEspecialidades(especialidade);
}



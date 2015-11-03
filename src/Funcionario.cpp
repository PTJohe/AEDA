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

void atualizaCondominio(Condominio &condo){
	vector<Funcionario> velho;
	Funcionario tmp = this;
	velho = condo.getFuncionarios();
	velho.push_back(tmp);
}

Funcionario::Funcionario(string nome,string especialidade,Condominio &condo){
	this->nome = nome;
	this->especialidades.push_back(especialidade);
	this->status = true;
	this->Funcionario;
	id++;
	verificaEspecialidades(especialidade);
	atualizaCondominio(condo);
}


void Funcionario::giveEspecialidade(string especialidade){
	this->especialidades.push_back(especialidade);
}

void Funcionario::giveStatus(bool status){

	this->status = status;
}


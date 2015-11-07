/*
 * Funcionario.cpp
 *
 *  Created on: 31 Oct 2015
 *      Author: simao
 */
#include "../headers/Funcionario.h"

static int nextId = 1;

Funcionario::Funcionario(string especialidade) {
	this->especialidade = especialidade;
	this->id = nextId;
	this->ocupado = false;
	nextId++;
	this->servicosEfectuados = 0;
}
Funcionario::Funcionario(string especialidade, int id, int servicosEfectuados) {
	this->especialidade = especialidade;
	this->id = id;
	this->ocupado = false;
	nextId = id + 1;
	this->servicosEfectuados = servicosEfectuados;
}

int Funcionario::getID() const {
	return id;
}
bool Funcionario::isOcupado() const {
	return ocupado;
}
string Funcionario::getEspecialidade() const {
	return especialidade;
}
int Funcionario::getServicosEfectuados() const{
	return servicosEfectuados;
}

void Funcionario::setOcupado(bool ocupado) {
	this->ocupado = ocupado;
}
void Funcionario::setEspecialidade(string especialidade) {
	this->especialidade = especialidade;
}
void Funcionario::addServicoEfectuado(){
	this->servicosEfectuados++;
}

bool Funcionario::operator==(const Funcionario f1) const {
	return (this->id == f1.id);
}
bool Funcionario::operator<(const Funcionario f1) const {
	return (this->id < f1.id);
}

void Funcionario::info() const {
	cout << "ID = " << this->id << endl;
	cout << "Especialidade: " << this->especialidade << endl;
	cout << "Estado: ";
	if (this->ocupado)
		cout << "Ocupado" << endl;
	else
		cout << "Livre" << endl;
	cout << "Servicos efectuados = " << this->servicosEfectuados << endl;
	cout << "Salario = 500$\n" << endl;

}

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
}
Funcionario::Funcionario(string especialidade, int id) {
	this->especialidade = especialidade;
	this->id = id;
	this->ocupado = false;
	nextId = id + 1;
}

int Funcionario::getID() const {
	return id;
}
bool Funcionario::getOcupado() const {
	return ocupado;
}
string Funcionario::getEspecialidade() const {
	return especialidade;
}

void Funcionario::setOcupado(bool ocupado) {
	this->ocupado = ocupado;
}
void Funcionario::setEspecialidade(string especialidade) {
	this->especialidade = especialidade;
}

bool Funcionario::operator==(const Funcionario f1) const {
	return (this->id == f1.id);
}
bool Funcionario::operator<(const Funcionario f1) const{
	return (this->id < f1.id);
}

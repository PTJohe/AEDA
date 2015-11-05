/*
 * Funcionario.cpp
 *
 *  Created on: 31 Oct 2015
 *      Author: simao
 */
#include "../headers/Funcionario.h"

static int nextId = 1;

Funcionario::Funcionario(string nome, string especialidade) {
	this->nome = nome;
	this->id = nextId;
	this->especialidade = especialidade;
	this->ocupado = false;
	nextId++;
}

string Funcionario::getNome() const {
	return nome;
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

void Funcionario::setNome(string nome) {
	this->nome = nome;
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

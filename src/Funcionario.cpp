/*
 * Funcionario.cpp
 *
 *  Created on: 31 Oct 2015
 *      Author: simao
 */
#include "../headers/Funcionario.h"

static int nextId = 1;

/**
 * Constructor.
 * @param especialidade Specialty, can be either cleaning, plumbing or painting.
 */
Funcionario::Funcionario(string especialidade) {
	this->especialidade = especialidade;
	this->id = nextId;
	this->ocupado = false;
	nextId++;
	this->servicosEfectuados = 0;
}
/**
 * Complete constructor. Only used when importing employee data.
 * @param especialidade Specialty, can be either cleaning, plumbing or painting.
 * @param id Employee's id.
 * @param servicosEfectuados Number of services done by the employee.
 */
Funcionario::Funcionario(string especialidade, int id, int servicosEfectuados) {
	this->especialidade = especialidade;
	this->id = id;
	if (id + 1 > nextId)
		nextId = id + 1;
	this->ocupado = false;
	this->servicosEfectuados = servicosEfectuados;
}

/**
 * @return Employee's ID.
 */
int Funcionario::getID() const {
	return id;
}
/**
 * @retval TRUE Employee is currently doing a service.
 * @retval FALSE Employee is free to do a service.
 */
bool Funcionario::isOcupado() const {
	return ocupado;
}
/**
 * @return Specialty, can be either cleaning, plumbing or painting.
 */
string Funcionario::getEspecialidade() const {
	return especialidade;
}
/**
 * @return Number of services done.
 */
int Funcionario::getServicosEfectuados() const {
	return servicosEfectuados;
}

/**
 * Sets employee busy status.
 * @param ocupado If true, employee is now doing a service, else, if false, employee finished doing a service.
 */
void Funcionario::setOcupado(bool ocupado) {
	this->ocupado = ocupado;
}
/**
 * Sets employee specialty.
 * @param especialidade Specialty, can be either cleaning, plumbing or painting.
 */
void Funcionario::setEspecialidade(string especialidade) {
	this->especialidade = especialidade;
}
/**
 * Adds one to the number of services done by the employee.
 */
void Funcionario::addServicoEfectuado() {
	this->servicosEfectuados++;
}

/**
 * Compares two employees by their ID too see if they're equal.
 * @param f1 Employee to be compared to.
 * @retval TRUE Employee has the same ID than f1.
 * @retval FALSE Employee has a different ID than f1.
 */
bool Funcionario::operator==(const Funcionario f1) const {
	return (this->id == f1.id);
}
/**
 * Compares two employees by their ID, for sorting purposes.
 * @param f1 Employee to be compared to.
 * @retval TRUE Employee has a lower ID than f1.
 * @retval FALSE Employee has an higher ID than f1.
 */
bool Funcionario::operator<(const Funcionario f1) const {
	return (this->id < f1.id);
}

/**
 * Displays employee info.
 */
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

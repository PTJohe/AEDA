#include "../headers/Utilizador.h"

//Construtores
Utilizador::Utilizador(string nomeUtilizador) {
	this->nomeUtilizador = nomeUtilizador;
	this->password = "";
	this->admin = false;
	this->nifCondomino = "NAO DEFINIDO";
}
Utilizador::Utilizador(string nomeUtilizador, string password) {
	this->nomeUtilizador = nomeUtilizador;
	this->password = password;
	this->admin = false;
	this->nifCondomino = "NAO DEFINIDO";
}
Utilizador::Utilizador(string nomeUtilizador, string password, bool admin) {
	this->nomeUtilizador = nomeUtilizador;
	this->password = password;
	this->admin = admin;
	this->nifCondomino = "NAO DEFINIDO";
}
Utilizador::Utilizador(string nomeUtilizador, string password, bool admin,
		string nifCondomino) {
	this->nomeUtilizador = nomeUtilizador;
	this->password = password;
	this->admin = admin;
	this->nifCondomino = nifCondomino;
}

//Gets e Sets
string Utilizador::getNomeUtilizador() const {
	return nomeUtilizador;
}
string Utilizador::getPassword() const {
	return password;
}
string Utilizador::getNIFCondomino()  {
	return nifCondomino;
}
bool Utilizador::isAdmin() const {
	return admin;
}

void Utilizador::setNomeUtilizador(string novoNome) {
	this->nomeUtilizador = novoNome;
}
void Utilizador::setPassword(string novaPassword) {
	this->password = novaPassword;
}
void Utilizador::setNIFCondomino(string nif) {
	this->nifCondomino = nif;
}
void Utilizador::setAdmin(bool admin) {
	this->admin = admin;
}

//Funcoes
bool Utilizador::hasDados() const {
	if (this->nifCondomino == "NAO DEFINIDO")
		return false;
	else
		return true;
}

bool Utilizador::validPassword(string password) {
	if (this->password == password)
		return true;
	else
		return false;
}

bool Utilizador::operator <(const Utilizador u1) const {
	return (this->nomeUtilizador < u1.nomeUtilizador);
}

bool Utilizador::operator ==(const Utilizador u1) const {
	if (this->nomeUtilizador == u1.nomeUtilizador)
		return true;
	return false;
}

void Utilizador::info() const{
	cout << "Nome de utilizador - " << nomeUtilizador << endl;
	cout << "Password - " << password << endl;
	cout << "Admin - ";
	if(this->admin)
		cout << "SIM" << endl;
	else
		cout << "NAO" << endl;
	cout << endl;
}

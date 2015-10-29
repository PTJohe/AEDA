#include "../headers/Utilizador.h"

//Construtores
Utilizador::Utilizador(string nomeUtilizador, string password) {
	this->nomeUtilizador = nomeUtilizador;
	this->password = password;
	this->admin = false;
	this->dados = NULL;
}
Utilizador::Utilizador(string nomeUtilizador, string password, bool admin) {
	this->nomeUtilizador = nomeUtilizador;
	this->password = password;
	this->admin = admin;
	this->dados = NULL;
}
Utilizador::Utilizador(string nomeUtilizador, string password, bool admin,
		Condomino* dados) {
	this->nomeUtilizador = nomeUtilizador;
	this->password = password;
	this->admin = admin;
	this->dados = dados;
}

//Gets e Sets
string Utilizador::getNomeUtilizador() const {
	return nomeUtilizador;
}

Condomino* Utilizador::getDados() const {
	return dados;
}
void Utilizador::setAdmin() {
	this->admin = true;
}
bool Utilizador::setDados(Condomino* dados) {
	this->dados = dados;
}

//Funcoes
bool Utilizador::isAdmin() const {
	return this->admin;
}
bool Utilizador::validPassword(string password) {
	if (this->password == password)
		return true;
	else
		return false;
}

bool Utilizador::operator < (const Utilizador u1) const{
	if(this->admin > u1.admin)
		return true;
	else return (this->nomeUtilizador < u1.nomeUtilizador);
}

bool Utilizador::operator == (const Utilizador u1) const{
	if(this->nomeUtilizador == u1.nomeUtilizador)
		if(this->password == u1.password)
			return true;
	return false;
}


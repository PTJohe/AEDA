#include "../headers/Utilizador.h"

//Construtores
Utilizador::Utilizador(string nomeUtilizador) {
	this->nomeUtilizador = nomeUtilizador;
	this->password = "";
	this->admin = false;
	this->dados = new Condomino();
}
Utilizador::Utilizador(string nomeUtilizador, string password) {
	this->nomeUtilizador = nomeUtilizador;
	this->password = password;
	this->admin = false;
	this->dados = new Condomino();
}
Utilizador::Utilizador(string nomeUtilizador, string password, bool admin) {
	this->nomeUtilizador = nomeUtilizador;
	this->password = password;
	this->admin = admin;
	this->dados = new Condomino();
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
string Utilizador::getPassword() const {
	return password;
}
Condomino* Utilizador::getDados()  {
	return dados;
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
void Utilizador::setDados(Condomino* dados) {
	this->dados = dados;
}
void Utilizador::setAdmin() {
	this->admin = true;
}

//Funcoes
bool Utilizador::hasDados() const {
	if (this->dados->getNome() == "NAO DEFINIDO" || this->dados->getNIF() == "NAO DEFINIDO")
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


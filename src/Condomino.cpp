#include "../headers/Condomino.h"

Condomino::Condomino(string nomeUtilizador, string password) {
	this->nomeUtilizador = nomeUtilizador;
	this->password = password;
	this->admin = false;
	this->nomeCivil = "NAO DEFINIDO";
	this->NIF = "NAO DEFINIDO";
	this->fundosMensais = 0;
	this->divida = 0;
}
Condomino::Condomino(string nomeUtilizador, string password, string nomeCivil,
		string NIF) {
	this->nomeUtilizador = nomeUtilizador;
	this->password = password;
	this->admin = false;
	this->nomeCivil = nomeCivil;
	this->NIF = NIF;
	this->fundosMensais = 0;
	this->divida = 0;
}
Condomino::Condomino(string nomeUtilizador, string password, bool admin,
		string nomeCivil, string NIF, long int fundosMensais, long int divida) {
	this->nomeUtilizador = nomeUtilizador;
	this->password = password;
	this->admin = admin;
	this->nomeCivil = nomeCivil;
	this->NIF = NIF;
	this->fundosMensais = fundosMensais;
	this->divida = divida;
}

string Condomino::getNomeUtilizador() const {
	return nomeUtilizador;
}
string Condomino::getPassword() const {
	return password;
}
bool Condomino::isAdmin() const {
	return admin;
}
string Condomino::getNomeCivil() const {
	return nomeCivil;
}
string Condomino::getNIF() const {
	return NIF;
}
int Condomino::getFundosMensais() const {
	return fundosMensais;
}
int Condomino::getDivida() const {
	return divida;
}
vector<Habitacao *> Condomino::getHabitacoes() {
	return habitacoes;
}

void Condomino::setNomeUtilizador(string novoNomeUtilizador) {
	this->nomeUtilizador = novoNomeUtilizador;
}
void Condomino::setPassword(string novaPassword) {
	this->password = novaPassword;
}
void Condomino::setAdmin(bool admin) {
	this->admin = admin;
}
void Condomino::setNomeCivil(string novoNomeCivil) {
	this->nomeCivil = novoNomeCivil;
}
void Condomino::setNIF(string novoNIF) {
	this->NIF = novoNIF;
	for (size_t i = 0; i < this->habitacoes.size(); i++) {
		this->habitacoes[i]->setProprietario(novoNIF);
	}
}
void Condomino::setFundosMensais(long int novosFundos) {
	this->fundosMensais = novosFundos;
}
void Condomino::setDivida(long int novaDivida) {
	this->divida = novaDivida;
}
void Condomino::setHabitacoes(vector<Habitacao*> habitacoes) {
	this->habitacoes = habitacoes;
}

void Condomino::sortHabitacoes() {
	sort(habitacoes.begin(), habitacoes.end(), compHabitacao);
}
void Condomino::addHabitacao(Habitacao* h1, int currentMes) {
	h1->setProprietario(this->NIF);
	for (size_t i = 0; i < currentMes; i++)
		h1->setPago(i);
	this->habitacoes.push_back(h1);
	sortHabitacoes();
}
bool Condomino::eraseHabitacao(int pos) {
	if (pos != -1) {
		delete habitacoes[pos];
		habitacoes.erase(habitacoes.begin() + pos);
		return true;
	} else
		return false;
}

bool Condomino::validPassword(string password) {
	if (this->password == password)
		return true;
	else
		return false;
}
bool Condomino::hasDados() const {
	if (this->nomeCivil == "NAO DEFINIDO" || this->NIF == "NAO DEFINIDO")
		return false;
	else
		return true;
}
bool Condomino::operator==(const Condomino c1) const {
	if (this->nomeUtilizador == c1.nomeUtilizador) {
		return true;
	} else
		return (this->NIF == c1.NIF);
}
bool Condomino::operator<(const Condomino c1) const {
	if (this->nomeUtilizador < c1.nomeUtilizador)
		return true;
	else
		return false;
	/*if (this->nomeCivil < c1.nomeCivil)
	 return true;
	 else if (this->nomeCivil > c1.nomeCivil)
	 return false;
	 else
	 return (this->NIF < c1.NIF);*/
}

void Condomino::infoConta() const {
	cout << "Nome de utilizador - " << nomeUtilizador << endl;
	cout << "Password - " << password << endl;
	cout << "Admin - ";
	if (this->admin)
		cout << "SIM" << endl;
	else
		cout << "NAO" << endl;
	cout << endl;
}
void Condomino::infoCondomino() const {
	cout << this->nomeCivil << endl;
	cout << "NIF: " << this->NIF << endl;
	cout << "Numero de habitacoes: " << this->habitacoes.size() << endl;
	cout << "Fundos Mensais = " << this->fundosMensais << "$" << endl;
	cout << "Divida = " << this->divida << "$" << "\n" << endl;
}
void Condomino::infoHabitacoes() const {
	cout << "Numero de habitacoes = " << this->habitacoes.size() << "\n"
			<< endl;

	for (size_t i = 0; i < this->habitacoes.size(); i++) {
		cout << i + 1 << " - ";
		habitacoes[i]->info();
	}
}
void Condomino::infoRenda() const {
	cout << "ESTADO DA RENDA:" << endl;
	cout << "Numero de habitacoes = " << this->habitacoes.size() << "\n"
			<< endl;

	cout << "\t\tRenda\t J F M A M J J A S O N D" << endl;
	if (habitacoes.empty())
		cout << "Nao possui habitacoes." << endl;
	else {
		for (size_t i = 0; i < this->habitacoes.size(); i++) {
			cout << i + 1 << " - " << habitacoes[i]->getTipo() << "\t"
					<< habitacoes[i]->calcRenda() << "$" << "\t|";
			for (size_t j = 0; j < 12; j++) {
				if (this->habitacoes[i]->getPago(j) == 1)
					cout << "X|";
				else
					cout << " |";
			}
			cout << endl;
		}
	}
}

/*
 * Non-class functions
 */

bool compHabitacao(Habitacao* h1, Habitacao* h2) {
	if (h1->getNIFProprietario() < h2->getNIFProprietario())
		return true;
	else if (h1->getNIFProprietario() > h2->getNIFProprietario())
		return false;
	else if (h1->calcRenda() < h2->calcRenda())
		return true;
	else if (h1->calcRenda() > h2->calcRenda())
		return false;
	else
		return (h1->getMorada() < h2->getMorada());
}

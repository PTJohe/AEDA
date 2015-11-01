#include "../headers/Condomino.h"

Condomino::Condomino() {
	this->nome = "NAO DEFINIDO";
	this->NIF = "NAO DEFINIDO";
	this->fundosMensais = 0;
	this->divida = 0;
}
Condomino::Condomino(string nome, string NIF) {
	this->nome = nome;
	this->NIF = NIF;
	this->fundosMensais = 0;
	this->divida = 0;
}
Condomino::Condomino(string nome, string NIF, int fundosMensais, int divida) {
	this->nome = nome;
	this->NIF = NIF;
	this->fundosMensais = fundosMensais;
	this->divida = divida;
}

string Condomino::getNome() const {
	return nome;
}
string Condomino::getNIF() const {
	return NIF;
}

int Condomino::getFundosMensais() const{
	return fundosMensais;
}

int Condomino::getDivida() const{
	return divida;
}

vector<Habitacao *> Condomino::getHabitacoes() {
	return habitacoes;
}


void Condomino::setNome(string nome) {
	this->nome = nome;
}
void Condomino::setNIF(string NIF) {
	this->NIF = NIF;
	for(size_t i = 0; i < this->habitacoes.size(); i++){
		this->habitacoes[i]->setProprietario(NIF);
	}
}
void Condomino::setHabitacoes(vector<Habitacao*> habitacoes) {
	this->habitacoes = habitacoes;
}
bool Condomino::addPropriedade(Habitacao* h1) {
	int pos = sequentialSearch(this->habitacoes, h1);
	if (pos == -1) {
		h1->setProprietario(this->NIF);
		this->habitacoes.push_back(h1);
		insertionSort(this->habitacoes);
		return true;
	} else
		return false;
}

bool Condomino::operator==(const Condomino c1) const {
	cout << "\nThis NIF = " << this->NIF << endl;
	cout << "That NIF = " << c1.NIF << endl;
	if (this->NIF == c1.NIF)
		return true;
	else
		return false;
}

void Condomino::info() const {
	cout << "Nome: " << this->nome << endl;
	cout << "NIF: " << this->NIF << endl;
	cout << "Numero de habitacoes: " << this->habitacoes.size() << endl;
	cout << "Fundos Mensais = " << this->fundosMensais << "$" << endl;
	cout << "Divida = " << this->divida << "$" << "\n" << endl;
}

void Condomino::infoHabitacoes() const {
	cout << "HABITACOES:" << endl;
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

	cout << "\t\t J F M A M J J A S O N D" << endl;
	for (size_t i = 0; i < this->habitacoes.size(); i++) {
		cout << i + 1 << " - " << habitacoes[i]->getTipo() << "\t|";
		for (size_t j = 0; j < 12; j++) {
			if (this->habitacoes[i]->getPago(j) == 1)
				cout << "X|";
			else
				cout << " |";
		}
		cout << endl;
	}
}

#include "../headers/Condominio.h"

Condominio::Condominio() {
	this->fundos = 5000;
	this->numFuncionarios = 0;
	this->currentMes = 0;
}

int Condominio::getMes() const {
	return currentMes;
}

vector<Condomino*> Condominio::getMoradores() {
	return moradores;
}
vector<Habitacao*> Condominio::getPropriedades() {
	return propriedades;
}
void Condominio::setMoradores(vector<Condomino*> moradores) {
	this->moradores = moradores;
}
void Condominio::setPropriedades(vector<Habitacao*> propriedades) {
	this->propriedades = propriedades;
}

void Condominio::fimDoMes() {
	for (size_t i = 0; i < moradores.size(); i++)
		for (size_t j = 0; j < moradores[i]->getPropriedades().size(); j++)
			fundos += moradores[i]->getPropriedades()[j]->calcRenda();
	fundos -= numFuncionarios * 500;

	if (this->currentMes < 12)
		this->currentMes++;
	else if (this->currentMes == 12)
		this->currentMes = 1;
}

void Condominio::infoMoradores() const {
	cout << "Numero de moradores = " << this->moradores.size() << "\n" << endl;
	for (size_t i = 0; i < this->moradores.size(); i++) {
		cout << i + 1 << " - ";
		this->moradores[i]->info();
	}
}
void Condominio::infoPropriedades() const {
	cout << "Numero de habitacoes = " << this->propriedades.size() << "\n" << endl;
	for (size_t i = 0; i < this->propriedades.size(); i++) {
		cout << i + 1 << " - ";
		this->propriedades[i]->info();
	}
}

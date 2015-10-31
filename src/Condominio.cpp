#include "../headers/Condominio.h"

Condominio::Condominio() {
	this->fundos = 5000;
	this->numFuncionarios = 0;
	this->fundos = 0;
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
	else if(this->currentMes == 12)
		this->currentMes = 1;
}

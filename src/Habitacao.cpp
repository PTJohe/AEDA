#include "Habitacao.h"

Habitacao::Habitacao(string morada, string codigoPostal) {
	this->morada = morada;
	this->codigoPostal = codigoPostal;
}

bool Habitacao::operator ==(const Habitacao* h1) const {
	if (this->morada == h1->morada)
		return true;
	else
		return false;
}

bool Habitacao::operator <(const Habitacao* h1) const {
	if (this->calcRenda() < h1->calcRenda())
		return true;
	else if (this->calcRenda() > h1->calcRenda())
		return false;
	else
		return (this->morada < h1->morada);
}

Vivenda::Vivenda(string morada, string codigoPostal, float areaInterior,
		float areaExterior, bool piscina) :
Habitacao(morada, codigoPostal) {
	this->areaInterior = areaInterior;
	this->areaExterior = areaExterior;
	this->piscina = piscina;
}

float Vivenda::calcRenda() const {
	return (150 + 0.5 * areaExterior + 50 * piscina);
}

void Vivenda::info() const {
	cout << "Info Vivenda:" << "\n";
	cout << "Morada - " << morada + ", " + codigoPostal << "\n"; //Estava a dar "invalid overload" se usasse o endl, cenas do eclipse
	cout << "Area Habitacional = " << areaInterior << "\n";
	cout << "Area Exterior = " << areaExterior << "\n" << endl;
}

Apartamento::Apartamento(string morada, string codigoPostal, int tipologia,
			float areaInterior, int piso) :
			Habitacao(morada, codigoPostal) {
		this->tipologia = tipologia;
		this->areaInterior = areaInterior;
		this->piso = piso;
	}
float Apartamento::calcRenda() const {
	return (100 + 20 * tipologia + 10 * piso);
}

void Apartamento::info() const {
	cout << "Info Apartamento:" << "\n";
	cout << "Morada - " << morada + ", " + codigoPostal << "\n"; //Aqui igual
	cout << "Tipologia: T" << tipologia << "\n";
	cout << "Piso " << piso << "\n" << endl;
}

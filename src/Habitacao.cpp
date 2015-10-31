#include "../headers/Habitacao.h"

/*
 * Habitacao
 */
Habitacao::Habitacao(string morada, string codigoPostal,
		Condomino* proprietario) {
	this->morada = morada;
	this->codigoPostal = codigoPostal;
	this->proprietario = proprietario;
	fill(this->pago, pago + sizeof(pago), 0);
}

Habitacao::Habitacao(string morada, string codigoPostal,
		Condomino* proprietario, bool pago[12]) {
	this->morada = morada;
	this->codigoPostal = codigoPostal;
	this->proprietario = proprietario;
	for (size_t i = 0; i < 12; i++) {
		this->pago[i] = pago[i];
	}
}

string Habitacao::getMorada() const {
	return morada;
}
string Habitacao::getCodigoPostal() const {
	return codigoPostal;
}
Condomino* Habitacao::getProprietario() const {
	return proprietario;
}
bool Habitacao::getPago(int mes) const {
	return pago[mes];
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

/*
 * Vivenda
 */
Vivenda::Vivenda(string morada, string codigoPostal, Condomino* proprietario,
		float areaInterior, float areaExterior, bool piscina) :
		Habitacao(morada, codigoPostal, proprietario) {
	this->areaInterior = areaInterior;
	this->areaExterior = areaExterior;
	this->piscina = piscina;
}

Vivenda::Vivenda(string morada, string codigoPostal, Condomino* proprietario,
		bool pago[12], float areaInterior, float areaExterior, bool piscina) :
		Habitacao(morada, codigoPostal, proprietario, pago) {
	this->areaInterior = areaInterior;
	this->areaExterior = areaExterior;
	this->piscina = piscina;
}

float Vivenda::getAreaInterior() const {
	return areaInterior;
}
float Vivenda::getAreaExterior() const {
	return areaExterior;
}
string Vivenda::getTipo() const{
	string tipo = "Vivenda";
	return tipo;
}
bool Vivenda::getPiscina() const{
	return piscina;
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

/*
 * Apartamento
 */
Apartamento::Apartamento(string morada, string codigoPostal,
		Condomino* proprietario, int tipologia, float areaInterior, int piso) :
		Habitacao(morada, codigoPostal, proprietario) {
	this->tipologia = tipologia;
	this->areaInterior = areaInterior;
	this->piso = piso;
}

Apartamento::Apartamento(string morada, string codigoPostal,
		Condomino* proprietario, bool pago[12], int tipologia,
		float areaInterior, int piso) :
		Habitacao(morada, codigoPostal, proprietario, pago) {
	this->tipologia = tipologia;
	this->areaInterior = areaInterior;
	this->piso = piso;
}

int Apartamento::getTipologia() const {
	return tipologia;
}
float Apartamento::getAreaInterior() const {
	return areaInterior;
}
int Apartamento::getPiso() const {
	return piso;
}
string Apartamento::getTipo() const{
	string tipo = "Apartamento";
	return tipo;
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

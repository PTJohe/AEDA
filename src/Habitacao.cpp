#include "../headers/Habitacao.h"

/*
 * Habitacao
 */

Habitacao::Habitacao(string morada, string codigoPostal) {
	this->morada = morada;
	this->codigoPostal = codigoPostal;
	this->NIFProprietario = "";
	fill(this->pago, pago + sizeof(pago), 0);
}
Habitacao::Habitacao(string morada, string codigoPostal,
		string NIFProprietario) {
	this->morada = morada;
	this->codigoPostal = codigoPostal;
	this->NIFProprietario = NIFProprietario;
	fill(this->pago, pago + sizeof(pago), 0);
}

Habitacao::Habitacao(string morada, string codigoPostal, string NIFProprietario,
		bool pago[12]) {
	this->morada = morada;
	this->codigoPostal = codigoPostal;
	this->NIFProprietario = NIFProprietario;
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
string Habitacao::getNIFProprietario() const {
	return NIFProprietario;
}
bool Habitacao::hasProprietario() const {
	if (NIFProprietario == "")
		return false;
	else
		return true;
}
bool Habitacao::getPago(int mes) const {
	return pago[mes];
}

void Habitacao::setMorada(string morada) {
	this->morada = morada;
}
void Habitacao::setCodigoPostal(string codigoPostal) {
	this->codigoPostal = codigoPostal;
}
void Habitacao::setProprietario(string nif) {
	this->NIFProprietario = nif;
}
void Habitacao::setPago(int mes) {
	this->pago[mes] = true;
}
void Habitacao::resetPago(){
	for(size_t i = 0; i < 12; i++)
		this->pago[i] = false;
}

/*
 * Vivenda
 */

Vivenda::Vivenda(string morada, string codigoPostal, float areaInterior,
		float areaExterior, bool piscina) :
		Habitacao(morada, codigoPostal) {
	this->areaInterior = areaInterior;
	this->areaExterior = areaExterior;
	this->piscina = piscina;
}
Vivenda::Vivenda(string morada, string codigoPostal, string proprietario,
		float areaInterior, float areaExterior, bool piscina) :
		Habitacao(morada, codigoPostal, proprietario) {
	this->areaInterior = areaInterior;
	this->areaExterior = areaExterior;
	this->piscina = piscina;
}

Vivenda::Vivenda(string morada, string codigoPostal, string proprietario,
		bool pago[12], float areaInterior, float areaExterior, bool piscina) :
		Habitacao(morada, codigoPostal, proprietario, pago) {
	this->areaInterior = areaInterior;
	this->areaExterior = areaExterior;
	this->piscina = piscina;
}
void Vivenda::setAreaInterior(float area){
	this->areaInterior = area;
}
void Vivenda::setAreaExterior(float area){
	this->areaExterior = area;
}
void Vivenda::setPiscina(bool piscina){
	this->piscina = piscina;
}

float Vivenda::getAreaInterior() const {
	return areaInterior;
}
float Vivenda::getAreaExterior() const {
	return areaExterior;
}
string Vivenda::getTipo() const {
	string tipo = "Vivenda";
	return tipo;
}
bool Vivenda::getPiscina() const {
	return piscina;
}
float Vivenda::calcRenda() const {
	return (200 + 0.5 * areaExterior + 100 * piscina);
}

void Vivenda::info() const {
	cout << "Vivenda" << endl;
	cout << "NIF Proprietario = " << NIFProprietario << endl;
	cout << "Morada - " << morada + ", " + codigoPostal << endl;
	cout << "Area Habitacional = " << areaInterior << endl;
	cout << "Area Exterior = " << areaExterior << endl;
	cout << "Piscina - ";
	if (this->piscina)
		cout << "Sim" << endl;
	else
		cout << "Nao" << endl;
	cout << "Renda = " << this->calcRenda() << "$\n" << endl;
}

/*
 * Apartamento
 */

Apartamento::Apartamento(string morada, string codigoPostal, int tipologia,
		float areaInterior, int piso) :
		Habitacao(morada, codigoPostal) {
	this->tipologia = tipologia;
	this->areaInterior = areaInterior;
	this->piso = piso;
}

Apartamento::Apartamento(string morada, string codigoPostal,
		string proprietario, int tipologia, float areaInterior, int piso) :
		Habitacao(morada, codigoPostal, proprietario) {
	this->tipologia = tipologia;
	this->areaInterior = areaInterior;
	this->piso = piso;
}

Apartamento::Apartamento(string morada, string codigoPostal,
		string proprietario, bool pago[12], int tipologia, float areaInterior,
		int piso) :
		Habitacao(morada, codigoPostal, proprietario, pago) {
	this->tipologia = tipologia;
	this->areaInterior = areaInterior;
	this->piso = piso;
}

void Apartamento::setAreaInterior(float area){
	this->areaInterior = area;
}
void Apartamento::setTipologia(int tipologia){
	this->tipologia = tipologia;
}
void Apartamento::setPiso(int piso){
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
string Apartamento::getTipo() const {
	string tipo = "Apartamento";
	return tipo;
}
float Apartamento::calcRenda() const {
	return (150 + 25 * tipologia + 10 * piso);
}

void Apartamento::info() const {
	cout << "Apartamento" << endl;
	cout << "NIF Proprietario = " << NIFProprietario << endl;
	cout << "Morada - " << morada + ", " + codigoPostal << endl;
	cout << "Tipologia: T" << tipologia << endl;
	cout << "Piso " << piso << endl;
	cout << "Renda = " << this->calcRenda() << "$\n" << endl;
}


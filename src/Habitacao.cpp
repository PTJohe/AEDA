#include "Habitacao.h"

float Vivenda::calcRenda() const{
	return (150 + 0.5*areaExterior + 50*piscina);
}

float Apartamento::calcRenda() const{
	return (100 + 20*tipologia + 10*piso);
}

void Vivenda::info() const{
	cout << "Info Vivenda:" << "\n";
	cout << "Morada - " << morada + ", " + codigoPostal << "\n"; //Estava a dar "invalid overload" se usasse o endl, cenas do eclipse
	cout << "Area Habitacional = " << areaInterior << "\n";
	cout << "Area Exterior = " << areaExterior << "\n" << endl;
}

void Apartamento::info() const{
	cout << "Info Apartamento:" << "\n";
	cout << "Morada - " << morada + ", " + codigoPostal << "\n"; //Aqui igual
	cout << "Tipologia: T" << tipologia << "\n";
	cout << "Piso " << piso << "\n" << endl;
}

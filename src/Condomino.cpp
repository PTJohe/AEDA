#include "Condomino.h"

vector<Habitacao *> Condomino::getPropriedades(){
	return propriedades;
}

void Condomino::display() const{
	cout << "DADOS:\n" << endl;
	cout << "Nome: " << this->nome << endl;
	cout << "NIF: " << this->NIF << endl;
	cout << "Numero de propriedades: " << this->propriedades.size() << "\n" << endl;
}

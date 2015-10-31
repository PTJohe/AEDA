#include "../headers/Condomino.h"

vector<Habitacao *> Condomino::getPropriedades() {
	return propriedades;
}

string Condomino::getNome() const {
	return nome;
}
string Condomino::getNIF() const {
	return NIF;
}
void Condomino::setNome(string nome) {
	this->nome = nome;
}
void Condomino::setNIF(string NIF) {
	this->NIF = NIF;
}
void Condomino::setPropriedades(vector<Habitacao*> propriedades) {
	this->propriedades = propriedades;
}
bool Condomino::addPropriedade(Habitacao* h1) {
	int pos = sequentialSearch(this->propriedades, h1);
	if (pos == -1) {
		this->propriedades.push_back(h1);
		insertionSort(this->propriedades);
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
	cout << "DADOS:\n" << endl;
	cout << "Nome: " << this->nome << endl;
	cout << "NIF: " << this->NIF << endl;
	cout << "Numero de propriedades: " << this->propriedades.size() << "\n"
			<< endl;
}

#include "../headers/Condominio.h"

Condominio::Condominio() {
	this->fundos = 5000;
	this->currentMes = 0;
}

int Condominio::getMes() const {
	return currentMes;
}

vector<Condomino> Condominio::getMoradores() {
	return moradores;
}
vector<Habitacao*> Condominio::getHabitacoes() {
	return habitacoes;
}
void Condominio::setMoradores(vector<Condomino> moradores) {
	this->moradores = moradores;
}
void Condominio::setHabitacoes(vector<Habitacao*> habitacoes) {
	this->habitacoes = habitacoes;
}

int Condominio::addMorador(Condomino condomino) {
	int pos = sequentialSearch(this->moradores, condomino);

	if (pos == -1) {
		this->moradores.push_back(condomino);
		insertionSort(moradores);
		pos = sequentialSearch(this->moradores, condomino);
		return pos;
	} else
		return false;
}
bool Condominio::eraseMorador(string nifMorador) {
	Condomino c1 = Condomino("nome", nifMorador);
	int pos = sequentialSearch(this->moradores, c1);

	if (pos != -1) {
		this->moradores.erase(moradores.begin() + pos);
		insertionSort(moradores);
		return true;
	} else
		return false;
}
int Condominio::addHabitacao(Habitacao* habitacao) {
	int pos = sequentialSearch(this->habitacoes, habitacao);
	if (pos == -1) {
		this->habitacoes.push_back(habitacao);
		insertionSort(habitacoes);
		pos = sequentialSearch(this->habitacoes, habitacao);
		return pos;
	} else
		return -1;
}

bool Condominio::updateHabitacoesCondominos() {
	for (size_t i = 0; i < this->moradores.size(); i++) {
		vector<Habitacao*> habitacoes;
		for(size_t j = 0; j < this->habitacoes.size(); j++){
			if(this->moradores[i].getNIF() == this->habitacoes[j]->getNIFProprietario())
				habitacoes.push_back(this->habitacoes[j]);
		}
		this->moradores[i].setHabitacoes(habitacoes);
	}
	return true;
}

void Condominio::fimDoMes() {
	for (size_t i = 0; i < moradores.size(); i++)
		for (size_t j = 0; j < moradores[i].getHabitacoes().size(); j++)
			fundos += moradores[i].getHabitacoes()[j]->calcRenda();
	fundos -= this->funcionarios.size() * 500;

	if (this->currentMes < 12)
		this->currentMes++;
	else if (this->currentMes == 12)
		this->currentMes = 1;
}

void Condominio::infoMoradores() const {
	cout << "Numero de moradores = " << this->moradores.size() << "\n" << endl;
	for (size_t i = 0; i < this->moradores.size(); i++) {
		cout << i + 1 << " - ";
		this->moradores[i].info();
	}
}
void Condominio::infoHabitacoes() const {
	cout << "Numero de habitacoes = " << habitacoes.size() << "\n" << endl;
	for (size_t i = 0; i < habitacoes.size(); i++) {
		cout << i + 1 << " - ";
		habitacoes[i]->info();
	}
}

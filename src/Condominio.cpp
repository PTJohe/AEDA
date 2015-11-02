#include "../headers/Condominio.h"

Condominio::Condominio() {
	this->fundos = 5000;
	this->currentMes = 0;
}

long int Condominio::getFundos() const{
	return fundos;
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
void Condominio::setFundos(long int fundos) {
	this->fundos = fundos;
}
void Condominio::setCurrentMes(int currentMes) {
	this->currentMes = currentMes;
}
void Condominio::setMoradores(vector<Condomino> moradores) {
	this->moradores = moradores;
}
void Condominio::setHabitacoes(vector<Habitacao*> habitacoes) {
	this->habitacoes = habitacoes;
}

void Condominio::sortMoradores() {
	insertionSort(moradores);
}
int Condominio::addMorador(Condomino condomino) {
	int pos = sequentialSearch(this->moradores, condomino);
	if (pos == -1) {
		this->moradores.push_back(condomino);
		insertionSort(moradores);
		pos = sequentialSearch(this->moradores, condomino);
		return pos;
	} else
		return -1;
}
int Condominio::eraseMorador(Condomino condomino) {
	int pos = sequentialSearch(this->moradores, condomino);

	if (pos != -1) {
		this->moradores.erase(moradores.begin() + pos);
		insertionSort(moradores);
		return pos;
	} else
		return -1;
}

bool Condominio::saldarDivida(Condomino condomino) {
	int pos = sequentialSearch(this->moradores, condomino);
	if (pos == -1) {
		return false;
	} else {
		this->moradores[pos].setDivida(0);
		for (size_t i = 0; i < this->moradores[pos].getHabitacoes().size();
				i++) {
			for (size_t j = 0; j < this->currentMes; j++) {
				this->moradores[pos].getHabitacoes()[i]->setPago(j);
			}
		}
		return true;
	}
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
		for (size_t j = 0; j < this->habitacoes.size(); j++) {
			if (this->moradores[i].getNIF()
					== this->habitacoes[j]->getNIFProprietario())
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
		this->moradores[i].infoCondomino();
	}
}
void Condominio::infoHabitacoes() const {
	cout << "Numero de habitacoes = " << habitacoes.size() << "\n" << endl;
	for (size_t i = 0; i < habitacoes.size(); i++) {
		cout << i + 1 << " - ";
		habitacoes[i]->info();
	}
}

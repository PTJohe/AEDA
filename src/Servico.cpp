#include "../headers/Servico.h"

static int nextId = 1;

Servico::Servico(string especialidade) {
	this->especialidade = especialidade;
	this->id = nextId;
	nextId++;

	if (especialidade == "Limpeza")
		this->duracao = 5*60;
	else if (especialidade == "Canalizacao")
		this->duracao = 2*60;
	else if (especialidade == "Pintura")
		this->duracao = 10*60;
}
Servico::Servico(string especialidade, int idFuncionario) {
	this->especialidade = especialidade;
	this->id = nextId;
	nextId++;

	if (especialidade == "Limpeza")
		this->duracao = 2*60;
	else if (especialidade == "Canalizacao")
		this->duracao = 5*60;
	else if (especialidade == "Pintura")
		this->duracao = 10*60;

	this->idFuncionario = idFuncionario;
	this->dataInicio = time(NULL);
	this->dataFim = dataInicio + duracao;
}

string Servico::getEspecialidade() const {
	return especialidade;
}
int Servico::getID() const {
	return id;
}
float Servico::getDuracao() const {
	return duracao;
}
int Servico::getIDFuncionario() const {
	return idFuncionario;
}

void Servico::setEspecialidade(string especialidade) {
	this->especialidade = especialidade;
}
void Servico::setDuracao(float duracao) {
	this->duracao = duracao;
}
void Servico::setIDFuncionario(int idFuncionario) {
	this->idFuncionario = idFuncionario;
}

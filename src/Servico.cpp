#include "../headers/Servico.h"

static int nextId = 1;

Servico::Servico(string especialidade, string NIFcondomino) {
	this->especialidade = especialidade;
	this->id = nextId;
	nextId++;

	if (especialidade == "Limpeza")
		this->duracao = 5 * 60;
	else if (especialidade == "Canalizacao")
		this->duracao = 2 * 60;
	else if (especialidade == "Pintura")
		this->duracao = 10 * 60;

	this->NIFcondomino = NIFcondomino;
	this->dataInicio = 0;
	this->dataFim = 0;
	this->idFuncionario = -1;
}
Servico::Servico(string especialidade, string NIFcondomino, string mes,
		int idFuncionario) {
	this->especialidade = especialidade;
	this->id = nextId;
	nextId++;

	if (especialidade == "Limpeza")
		this->duracao = 2 * 60;
	else if (especialidade == "Canalizacao")
		this->duracao = 5 * 60;
	else if (especialidade == "Pintura")
		this->duracao = 10 * 60;

	this->NIFcondomino = NIFcondomino;

	this->idFuncionario = idFuncionario;
	this->mes = mes;
	this->dataInicio = time(NULL);
	this->dataFim = dataInicio + duracao;
}
Servico::Servico(int id, string especialidade, string NIFcondomino, string mes, time_t dataInicio,
		int idFuncionario) {
	this->especialidade = especialidade;
	this->id = id;
	nextId = id + 1;

	if (especialidade == "Limpeza")
		this->duracao = 2 * 60;
	else if (especialidade == "Canalizacao")
		this->duracao = 5 * 60;
	else if (especialidade == "Pintura")
		this->duracao = 10 * 60;

	this->NIFcondomino = NIFcondomino;

	this->idFuncionario = idFuncionario;
	this->mes = mes;
	this->dataInicio = dataInicio;
	this->dataFim = dataInicio + duracao;
}

string Servico::getEspecialidade() const {
	return especialidade;
}
int Servico::getID() const {
	return id;
}
string Servico::getMes() const{
	return mes;
}
time_t Servico::getDataInicio() const {
	return dataInicio;
}
float Servico::getDuracao() const {
	return duracao;
}
int Servico::getIDFuncionario() const {
	return idFuncionario;
}
string Servico::getNIFcondomino() const {
	return NIFcondomino;
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

void Servico::iniciarServico(string mes, int idFuncionario) {
	this->idFuncionario = idFuncionario;
	this->mes = mes;
	this->dataInicio = time(NULL);
	this->dataFim = dataInicio + duracao;
}

bool Servico::operator<(const Servico s1) const {
	return this->id < s1.id;
}

void Servico::info() const {
	cout << "ID = " << this->id << endl;
	cout << "Tipo: " << this->especialidade << endl;

	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&this->dataInicio);
	strftime(buf, sizeof(buf), "%H:%M:%S", &tstruct);
	string convert(buf);

	cout << "Data Inicio: " << this->mes << " " << convert << endl;
	cout << "Duracao: " << this->duracao / 60 << " min" << endl;
	cout << "ID Funcionario: " << this->idFuncionario << endl;
}

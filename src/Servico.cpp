#include "../headers/Servico.h"

static int nextId = 1;

Servico::Servico(string especialidade, string NIFcondomino,
		string mesRequisitado, time_t dataRequisitado) {
	this->id = nextId;
	nextId++;
	this->especialidade = especialidade;
	this->NIFcondomino = NIFcondomino;
	this->mesRequisitado = mesRequisitado;
	this->dataRequisitado = dataRequisitado;

	if (especialidade == "Limpeza")
		this->duracao = 2 * 60;
	else if (especialidade == "Canalizacao")
		this->duracao = 5 * 60;
	else if (especialidade == "Pintura")
		this->duracao = 10 * 60;

	this->idFuncionario = 0;
	this->mesInicio = mesRequisitado;
	this->dataInicio = 0;
	this->dataFim = 0;

}
Servico::Servico(string especialidade, string NIFcondomino,
		string mesRequisitado, time_t dataRequisitado, string mesActual,
		int idFuncionario) {
	this->id = nextId;
	nextId++;
	this->especialidade = especialidade;
	this->NIFcondomino = NIFcondomino;
	this->mesRequisitado = mesRequisitado;
	this->dataRequisitado = dataRequisitado;
	this->mesInicio = mesActual;
	this->dataInicio = time(NULL);
	this->idFuncionario = idFuncionario;

	if (especialidade == "Limpeza")
		this->duracao = 2 * 60;
	else if (especialidade == "Canalizacao")
		this->duracao = 5 * 60;
	else if (especialidade == "Pintura")
		this->duracao = 10 * 60;

	this->dataFim = dataInicio + duracao;
}
Servico::Servico(int id, string especialidade, string NIFcondomino,
		string mesRequisitado, time_t dataRequisitado, string mesInicio,
		time_t dataInicio, int idFuncionario) {
	this->id = id;
	nextId = id + 1;
	this->especialidade = especialidade;
	this->NIFcondomino = NIFcondomino;
	this->mesRequisitado = mesRequisitado;
	this->dataRequisitado = dataRequisitado;
	this->mesInicio = mesInicio;
	this->dataInicio = dataInicio;
	this->idFuncionario = idFuncionario;

	if (especialidade == "Limpeza")
		this->duracao = 2 * 60;
	else if (especialidade == "Canalizacao")
		this->duracao = 5 * 60;
	else if (especialidade == "Pintura")
		this->duracao = 10 * 60;

	if (idFuncionario == 0)
		this->dataFim = 0;
	else
		this->dataFim = dataInicio + duracao;
}

string Servico::getEspecialidade() const {
	return especialidade;
}
int Servico::getID() const {
	return id;
}

string Servico::getMesRequisitado() const {
	return mesRequisitado;
}
time_t Servico::getDataRequisitado() const {
	return dataRequisitado;
}
string Servico::getMesInicio() const {
	return mesInicio;
}
time_t Servico::getDataInicio() const {
	return dataInicio;
}
float Servico::getDuracao() const {
	return duracao;
}
time_t Servico::getDataFim() const {
	return dataFim;
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
	this->mesInicio = mes;
	this->dataInicio = time(NULL);
	this->dataFim = dataInicio + duracao;
}
void Servico::iniciarServico(string mes, int idFuncionario, time_t dataInicio) {
	this->idFuncionario = idFuncionario;
	this->mesInicio = mes;
	this->dataInicio = dataInicio;
	this->dataFim = dataInicio + duracao;
}
bool Servico::operator<(const Servico s1) const {
	return this->id < s1.id;
}

void Servico::info() const {
	cout << "ID = " << this->id << endl;
	cout << "Tipo: " << this->especialidade << endl;

	struct tm tstruct1;
	char buf1[80];
	tstruct1 = *localtime(&this->dataRequisitado);
	strftime(buf1, sizeof(buf1), "%H:%M:%S", &tstruct1);
	string convert1(buf1);

	cout << "Data Requisitado: " << this->mesRequisitado << " " << convert1
			<< endl;

	struct tm tstruct2;
	char buf2[80];
	tstruct2 = *localtime(&this->dataInicio);
	strftime(buf2, sizeof(buf2), "%H:%M:%S", &tstruct2);
	string convert2(buf2);

	cout << "Data Inicio: ";
	if (this->dataInicio == 0)
		cout << "Ainda esta na lista de espera" << endl;
	else {
		cout << this->mesInicio << " " << convert2 << endl;

		struct tm tstruct3;
		char buf3[80];
		tstruct3 = *localtime(&this->dataFim);
		strftime(buf3, sizeof(buf3), "%H:%M:%S", &tstruct3);
		string convert3(buf3);

		cout << "Data Fim: " << this->mesInicio << " " << convert3 << endl;
	}
	cout << "Duracao: " << this->duracao / 60 << " min" << endl;
	cout << "ID do Funcionario: ";
	if (this->idFuncionario == 0)
		cout << "Ainda nao foi atribuido" << endl;
	else
		cout << this->idFuncionario << endl;
}

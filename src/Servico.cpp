#include "../headers/Servico.h"

static int nextId = 1;
/**
 * Constructor used to create a service waiting to be done.
 * @param especialidade Type of service, can be either cleaning, plumbing or painting.
 * @param NIFcondomino NIF of the tenant that requested the service.
 * @param mesRequisitado Month when it was requested.
 * @param dataRequisitado Time when it was requested.
 */
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
/**
 * Constructor used to create a service that is immediately being done.
 * @param especialidade Type of service, can be either cleaning, plumbing or painting.
 * @param NIFcondomino NIF of the tenant that requested the service.
 * @param mesRequisitado Month when the service was requested.
 * @param dataRequisitado Time when the service was requested.
 * @param mesActual Current month.
 * @param idFuncionario Employee that is going to do the service.
 */
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
/**
 * Complete constructor. Only used to import service data.
 * @param id Service ID.
 * @param especialidade Type of service, can be either cleaning, plumbing or painting.
 * @param NIFcondomino NIF of the tenant that requested the service.
 * @param mesRequisitado Month when the service was requested.
 * @param dataRequisitado Time when the service was requested.
 * @param mesInicio Month when the service started.
 * @param dataInicio Time when the service started.
 * @param idFuncionario Employee that is going to do the service.
 */
Servico::Servico(int id, string especialidade, string NIFcondomino,
		string mesRequisitado, time_t dataRequisitado, string mesInicio,
		time_t dataInicio, int idFuncionario) {
	this->id = id;
	if (id + 1 > nextId)
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

/**
 * @return Type of service, can be either cleaning, plumbing or painting.
 */
string Servico::getEspecialidade() const {
	return especialidade;
}
/**
 * @return Service ID.
 */
int Servico::getID() const {
	return id;
}
/**
 * @return Month when the service was requested.
 */
string Servico::getMesRequisitado() const {
	return mesRequisitado;
}
/**
 * @return Time when the service was requested.
 */
time_t Servico::getDataRequisitado() const {
	return dataRequisitado;
}
/**
 * @return Month when the service started.
 */
string Servico::getMesInicio() const {
	return mesInicio;
}
/**
 * @return Time when the service started.
 */
time_t Servico::getDataInicio() const {
	return dataInicio;
}
/**
 * @return Service duration.
 */
float Servico::getDuracao() const {
	return duracao;
}
/**
 * @return Time when the service is going to end.
 */
time_t Servico::getDataFim() const {
	return dataFim;
}
/**
 * @return ID of the employee that did or is doing the service.
 */
int Servico::getIDFuncionario() const {
	return idFuncionario;
}
/**
 * @return NIF of the tenant that requested the service.
 */
string Servico::getNIFcondomino() const {
	return NIFcondomino;
}

/**
 * Sets the type of service.
 * @param especialidade Type of service, can be either cleaning, plumbing or painting.
 */
void Servico::setEspecialidade(string especialidade) {
	this->especialidade = especialidade;
}
/**
 * Sets the service duration.
 * @param duracao Time the service is going to take.
 */
void Servico::setDuracao(float duracao) {
	this->duracao = duracao;
}
/**
 * Sets an employee to do the service.
 * @param idFuncionario Employee ID.
 */
void Servico::setIDFuncionario(int idFuncionario) {
	this->idFuncionario = idFuncionario;
}

/**
 * Starts the service.
 * @param mes Month when the service started.
 * @param idFuncionario Employee ID.
 */
void Servico::iniciarServico(string mes, int idFuncionario) {
	this->idFuncionario = idFuncionario;
	this->mesInicio = mes;
	this->dataInicio = time(NULL);
	this->dataFim = dataInicio + duracao;
}
/**
 * Starts the service.
 * @param mes Month when the service started.
 * @param idFuncionario Employee ID.
 * @param dataInicio Time when the service started.
 */
void Servico::iniciarServico(string mes, int idFuncionario, time_t dataInicio) {
	this->idFuncionario = idFuncionario;
	this->mesInicio = mes;
	this->dataInicio = dataInicio;
	this->dataFim = dataInicio + duracao;
}

/**
 * Compares two services by their id, for sorting purposes.
 * @param s1 Service to be compared to.
 * @retval TRUE Service has a lower id than s1.
 * @retval FALSE Service has an higher id than s1.
 */
bool Servico::operator<(const Servico s1) const {
	return this->id < s1.id;
}

/**
 * Displays service info.
 */
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

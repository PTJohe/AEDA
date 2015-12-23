#include "../headers/Condominio.h"

static int nextId = 1;

/**
 * Default constructor.
 */
Condominio::Condominio() {
	this->id = nextId;
	nextId++;
	this->fundos = 5000;
	this->currentMes = 0;
}

/**
 * Constructor of a new condominium.
 * @param designacao Name of the condominium
 * @param localizacao Address and coordinates of the condominium
 */
Condominio::Condominio(string designacao, Posicao localizacao) {
	this->id = nextId;
	nextId++;
	this->fundos = 5000;
	this->currentMes = 0;

	this->designacao = designacao;
	this->localizacao = localizacao;
}

/**
 * Complete constructor. This is only used to import condominium data.
 * @param id Condominium ID
 * @param fundos Funds available for the condominium
 * @param currentMes Current month to use in rent
 * @param designacao Name of the condominium
 * @param localizacao Address and coordinates of the condominium
 */
Condominio::Condominio(int id, long int fundos, int currentMes,
		string designacao, Posicao localizacao) {
	this->id = id;
	if (id >= nextId)
		nextId = id + 1;
	this->fundos = fundos;
	this->currentMes = currentMes;

	this->designacao = designacao;
	this->localizacao = localizacao;
}

/**
 * @return Condominium ID.
 */
int Condominio::getID() const {
	return id;
}
/**
 * Decrements condominium's nextID.
 */
void Condominio::decID() {
	nextId--;
}
/**
 * @return Condominium funds.
 */
long int Condominio::getFundos() const {
	return fundos;
}
/**
 * @return Current month.
 */
int Condominio::getMes() const {
	return currentMes;
}
/**
 * @return Name.
 */
string Condominio::getDesignacao() const {
	return designacao;
}
/**
 * @return Location and coordinates.
 */
Posicao Condominio::getLocalizacao() const {
	return localizacao;
}
/**
 * Given a position in the tenants vector, returns a pointer to that tenant.
 * @param pos Position in the tenants vector.
 * @return Pointer to the specified tenant.
 */
Condomino* Condominio::getCondomino(int pos) {
	Condomino* p = &moradores[pos];
	return p;
}
/**
 * @return Vector of condominium's tenants.
 */
vector<Condomino> Condominio::getMoradores() {
	return moradores;
}
/**
 * @return Vector of condominium's houses.
 */
vector<Habitacao*> Condominio::getHabitacoes() {
	return habitacoes;
}
/**
 * @return Vector of condominium's employees.
 */
vector<Funcionario> Condominio::getFuncionarios() {
	tabHFunc::iterator it = funcionarios.begin();
	vector<Funcionario> vec;
	for (it; it != funcionarios.end(); it++) {
		vec.push_back(*it);
	}
	return vec;
}
/**
 * Returns a pointer to an employee using its id.
 * @param id Employee id.
 * @return A pointer to the employee.
 */
Funcionario Condominio::getFuncionario(int id) {
	Funcionario f1 = Funcionario("", -1, 0);
	tabHFunc::iterator it = funcionarios.begin();
	for (it; it != funcionarios.end(); it++) {
		if ((*it).getID() == id) {
			f1 = (*it);
			break;
		}
	}
	return f1;
}

/**
 * @param vectorServicos 0 = servicosTerminados, 1 = servicosEmCurso, 2 = servicosEmEspera
 * @return Vector of condominium's services.
 */
vector<Servico> Condominio::getServicos(int vectorServicos) {
	if (vectorServicos == 0)
		return servicosTerminados;
	else if (vectorServicos == 1)
		return servicosEmCurso;
	else
		return servicosEmEspera;
}
/**
 * @return Tranports priority queue.
 */
priority_queue<Transporte> Condominio::getTransportes() {
	return this->transportes;
}


bool setDestinoTransporte(Transporte t1, string novoDestino){

}

/**
 * @return Number of properties in the condominium.
 */
int Condominio::getNumHabitacoes() const {
	return habitacoes.size();
}

/**
 * @return Number of properties with the type "house" in the condominium.
 */
int Condominio::getNumVivendas() const {
	int soma = 0;
	for (size_t i = 0; i < habitacoes.size(); i++) {
		if (habitacoes[i]->getTipo() == "Vivenda")
			soma++;
	}
	return soma;
}
/**
 * @return Number of tenants in the condominium.
 */
int Condominio::getNumMoradores() const {
	return moradores.size();
}

/**
 * Sets the condominium funds.
 * @param fundos New amount of funds.
 */
void Condominio::setFundos(long int fundos) {
	this->fundos = fundos;
}
/**
 * Sets the current month.
 * @param currentMes Position of the month. 0 = January, ... , 11 = December.
 */
void Condominio::setCurrentMes(int currentMes) {
	this->currentMes = currentMes;
}
/**
 * Sets the condominium's tenants.
 * @param moradores New vector of tenants.
 */
void Condominio::setMoradores(vector<Condomino> moradores) {
	this->moradores = moradores;
}
/**
 * Sets the condominium's houses.
 * @param habitacoes New vector of houses.
 */
void Condominio::setHabitacoes(vector<Habitacao*> habitacoes) {
	this->habitacoes = habitacoes;
}
/**
 * Sets the condominium's employees.
 * @param funcionarios New vector of employees.
 */
void Condominio::setFuncionarios(vector<Funcionario> funcionarios) {
	this->funcionarios.clear();

	for (size_t i = 0; i < funcionarios.size(); i++) {
		this->funcionarios.insert(funcionarios[i]);
	}
}
/**
 * Sets the condominium's services.
 * @param vectorServicos 0 = servicosTerminados, 1 = servicosEmCurso, 2 = ServicosEmEspera
 * @param servicos New vector of services
 */
void Condominio::setServicos(int vectorServicos, vector<Servico> servicos) {
	if (vectorServicos == 0)
		this->servicosTerminados = servicos;
	else if (vectorServicos == 1)
		this->servicosEmCurso = servicos;
	else if (vectorServicos == 2)
		this->servicosEmEspera = servicos;
}
/**
 * Sets the condominium's tranports.
 * @param transportes New transports.
 */
void Condominio::setTransportes(priority_queue<Transporte> transportes){
	this->transportes = transportes;
}
/**
 * Sets the condominium's name.
 * @param designacao New name.
 */
void Condominio::setDesignacao(string designacao) {
	this->designacao = designacao;
}
/**
 * Sets the condominium's address.
 * @param localizacao New address.
 */
void Condominio::setLocalizacao(Posicao localizacao) {
	this->localizacao = localizacao;
}

/**
 * Compares two condominiums by the number of properties and/or houses.
 * @param c1 Condominium to be compared.
 * @retval TRUE Condominium has more properties than c1.
 * @retval FALSE Condominum has less properties than c1.
 */
bool Condominio::operator <(const Condominio &c1) const {
	if (this->getNumHabitacoes() < c1.getNumHabitacoes())
		return true;
	else if (this->getNumHabitacoes() > c1.getNumHabitacoes())
		return false;
	else if (this->getNumVivendas() < c1.getNumVivendas())
		return true;
	else if (this->getNumVivendas() > c1.getNumVivendas())
		return false;
	else
		return this->getID() < c1.getID();
}
/**
 * Compares two condominiums by their ID.
 * @param c1 Tenant to be compared.
 * @retval TRUE Equal ID
 * @retval FALSE Condominiums are different.
 */
bool Condominio::operator ==(const Condominio &c1) const {
	return this->getID() == c1.getID();
}
/**
 * Print condominium overload.
 */
ostream& operator<<(ostream& os, Condominio &c1) {
	os << c1.getID() << endl;
	os << c1.getFundos() << endl;
	os << c1.getMes() << endl;
	os << c1.getDesignacao() << endl;
	os << c1.getLocalizacao().cidade << endl;
	os << c1.getLocalizacao().x << endl;
	os << c1.getLocalizacao().y << endl;
	os << endl;
	return os;
}
/*
 * Sorts the tenants according to a specified option.
 * @param sortOption 0 = Username, 1 = Name, 2 = NIF.
 */
void Condominio::sortMoradores(int sortOption) {
	if (sortOption == 0)
		insertionSort(moradores);
	else if (sortOption == 1)
		sort(moradores.begin(), moradores.end(), compCondominoNomeCivil);
	else if (sortOption == 2)
		sort(moradores.begin(), moradores.end(), compCondominoNIF);
}
/**
 * Adds a tenant to the condominium. If it's the first tenant, it's automatically given admin rights.
 * @param condomino Tenant to be added.
 * @return Position of the new tenant in the vector of tenants. Position = -1 if tenant to be added is already in the vector.
 * @throws CondominoDuplicado There is already a tenant with the same username of NIF in the condominium.
 */
int Condominio::addMorador(Condomino condomino) {
	if (this->moradores.empty()) {
		condomino.setAdmin(true);
		this->moradores.push_back(condomino);
		return 0;
	}
	int pos = sequentialSearch(this->moradores, condomino);
	if (pos == -1) {
		this->moradores.push_back(condomino);
		insertionSort(moradores);
		pos = sequentialSearch(this->moradores, condomino);
		return pos;
	} else
		throw CondominoDuplicado();
}
/**
 * Removes a tenant from the condominium.
 * @param condomino Tenant to be removed.
 * @return Position where the tenant used to be in the vector. Position = -1 if tenant to be removed isn't in the vector.
 */
int Condominio::eraseMorador(Condomino condomino) {
	int pos = sequentialSearch(this->moradores, condomino);

	if (pos != -1) {
		this->moradores.erase(moradores.begin() + pos);
		insertionSort(moradores);
		for (size_t i = 0; i < this->habitacoes.size(); i++) {
			if (habitacoes[i]->getNIFProprietario() == condomino.getNIF())
				habitacoes[i]->setProprietario("");
		}
		sortHabitacoes(2);
		return pos;
	} else
		return -1;
}

/**
 * Sorts houses according to a specified option.
 * @param sortOption 0 = ID, 1 = Type, 2 = Rent, 3 = Owner's NIF.
 */
void Condominio::sortHabitacoes(int sortOption) {
	if (sortOption == 0)
		sort(habitacoes.begin(), habitacoes.end(), compHabitacaoID);
	else if (sortOption == 1)
		sort(habitacoes.begin(), habitacoes.end(), compHabitacaoTipo);
	else if (sortOption == 2)
		sort(habitacoes.begin(), habitacoes.end(), compHabitacaoRenda);
	else if (sortOption == 3)
		sort(habitacoes.begin(), habitacoes.end(), compHabitacaoNIF);
	updateHabitacoesCondominos();
}
/**
 * Checks if a given house is in a given vector of houses.
 * @param habitacoes Vector of houses.
 * @param habitacao House to be searched.
 * @return Position of the house in the given vector. Position = -1 if the house isn't in the vector.
 */
int Condominio::findHabitacao(vector<Habitacao*> habitacoes,
		Habitacao* habitacao) {
	int pos = -1;
	for (size_t i = 0; i < habitacoes.size(); i++) {
		if (habitacao->getMorada() == habitacoes[i]->getMorada()) {
			pos = i;
			return pos;
		}
	}
	return pos;
}
/**
 * Adds house to the condominium.
 * @param habitacao House to be added.
 * @retval TRUE House was added.
 * @retval FALSE House with the same address was already in the vector of houses.
 */
bool Condominio::addHabitacao(Habitacao* habitacao) {
	int pos = -1;
	for (size_t i = 0; i < this->habitacoes.size(); i++) {
		if (habitacoes[i]->getMorada() == habitacao->getMorada())
			pos = i;
	}
	if (pos == -1) {
		this->habitacoes.push_back(habitacao);
		if (habitacao->getNIFProprietario() != "")
			for (size_t i = 0; i <= currentMes; i++)
				habitacao->setPago(i);
		sortHabitacoes(3);
		return true;
	} else
		return false;
}
/**
 * Removes a house from a given user.
 * @param condomino User whose house is being removed.
 * @param pos Position of the house in the owner's vector of owned houses.
 * @retval TRUE House successfully deleted.
 * @retval FALSE Tenant doesn't own the house to be removed.
 */
bool Condominio::eraseHabitacaoPossuida(Condomino condomino, int pos) {
	int pos1 = sequentialSearch(this->moradores, condomino);
	if (pos1 == -1) {
		return false;
	} else {
		bool success = moradores[pos1].eraseHabitacao(pos);
		sortHabitacoes(3);
		return success;
	}
}
/**
 * Removes a house from the condominium if empty, makes it empty if owned by a tenant.
 * @param pos Position of the house in the condominium's vector of houses.
 * @retval TRUE House successfully deleted.
 * @retval FALSE House doesn't exist.
 */
bool Condominio::eraseHabitacao(int pos) {
	Condomino c1 = Condomino("nome", "password", "nomeCivil",
			this->habitacoes[pos]->getNIFProprietario());
	int pos1 = sequentialSearch(this->moradores, c1);

	if (pos1 == -1) {
		delete habitacoes[pos];
		habitacoes.erase(habitacoes.begin() + pos);
		return true;
	} else {
		int pos2 = this->findHabitacao(moradores[pos1].getHabitacoes(),
				habitacoes[pos]);
		return this->moradores[pos1].eraseHabitacao(pos2);
	}
}

/**
 * Sets a new username for the given tenant.
 * @param condomino Tenant whose username is being changed.
 * @param nomeUtilizador New username.
 * @retval TRUE Username successfully changed.
 * @retval FALSE Tenant doesn't exist.
 */
bool Condominio::setNomeUtilizador(Condomino condomino, string nomeUtilizador) {
	int pos = sequentialSearch(this->moradores, condomino);
	if (pos == -1) {
		return false;
	}
	this->moradores[pos].setNomeUtilizador(nomeUtilizador);
	return true;
}
/**
 * Sets a new password for the given tenant.
 * @param condomino Tenant whose password is being changed.
 * @param password New password.
 * @retval TRUE Password successfully changed.
 * @retval FALSE Tenant doesn't exist.
 */
bool Condominio::setPassword(Condomino condomino, string password) {
	int pos = sequentialSearch(this->moradores, condomino);
	if (pos == -1) {
		return false;
	}
	this->moradores[pos].setPassword(password);
	return true;
}
/**
 * Sets or revokes administrator rights for the given tenant.
 * @param condomino Tenant whose admin rights is being changed.
 * @param admin If true, sets the tenant as admin. If false, revokes admin rights of the tenant.
 * @retval TRUE Admin right successfully changed.
 * @retval FALSE Tenant doesn't exist.
 */
bool Condominio::setAdmin(Condomino condomino, bool admin) {
	int pos = sequentialSearch(this->moradores, condomino);
	if (pos == -1) {
		return false;
	}
	this->moradores[pos].setAdmin(admin);
	return true;
}

/**
 * Sets a new name for the given tenant.
 * @param condomino Tenant whose name is being changed.
 * @param nomeCivil New name.
 * @retval TRUE Name successfully changed.
 * @retval FALSE Tenant doesn't exist.
 */
bool Condominio::setNomeCivil(Condomino condomino, string nomeCivil) {
	int pos = sequentialSearch(this->moradores, condomino);
	if (pos == -1) {
		return false;
	}
	this->moradores[pos].setNomeCivil(nomeCivil);
	return true;
}
/**
 * Sets a new NIF for the given tenant.
 * @param condomino Tenant whose NIF is being changed.
 * @param NIF New NIF.
 * @retval TRUE NIF successfully changed.
 * @retval FALSE Tenant doesn't exist.
 */
bool Condominio::setNIF(Condomino condomino, string NIF) {
	int pos = sequentialSearch(this->moradores, condomino);
	if (pos == -1) {
		return false;
	}
	this->moradores[pos].setNIF(NIF);
	return true;
}
/**
 * Sets new monthly funds for the given tenant.
 * @param condomino Tenant whose monthly funds is being changed.
 * @param fundos New monthly funds.
 * @retval TRUE Monthly funds successfully changed.
 * @retval FALSE Tenant doesn't exist.
 */
bool Condominio::setFundosMensais(Condomino condomino, long int fundos) {
	int pos = sequentialSearch(this->moradores, condomino);
	if (pos == -1) {
		return false;
	}
	this->moradores[pos].setFundosMensais(fundos);
	return true;
}
/**
 * Clears debt of a given tenant and updates paid rent of his houses.
 * @param condomino Tenant whose debt is being cleared.
 * @retval TRUE Debt successfully cleared.
 * @retval FALSE Tenant doesn't exist.
 */
bool Condominio::saldarDivida(Condomino condomino) {
	int pos = sequentialSearch(this->moradores, condomino);
	if (pos == -1) {
		return false;
	} else {
		this->moradores[pos].setDivida(0);
		for (size_t i = 0; i < this->moradores[pos].getHabitacoes().size();
				i++) {
			for (int j = 0; j <= this->currentMes; j++) {
				this->moradores[pos].getHabitacoes()[i]->setPago(j);
			}
		}
		return true;
	}
}

/**
 * Updates the vector of house pointers for every user in the condominium. This function never fails.
 * @retval TRUE Pointers successfully updated.
 */
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

/**
 * Sorts employees according to a specified option.
 * @param sortOption 0 = ID, 1 = Specialty, 2 = Occupation status.
 */
vector<Funcionario> Condominio::sortFuncionarios(int sortOption) {
	vector<Funcionario> funcionarios = this->getFuncionarios();
	if (sortOption == 0)
		insertionSort(funcionarios);
	else if (sortOption == 1)
		sort(funcionarios.begin(), funcionarios.end(),
				compFuncionarioEspecialidade);
	else if (sortOption == 2)
		sort(funcionarios.begin(), funcionarios.end(), compFuncionarioOcupacao);
	else if (sortOption == 3)
		sort(funcionarios.begin(), funcionarios.end(), compFuncionarioServicos);
	return funcionarios;
}
/**
 * Adds a given employee to the condominium.
 * @param funcionario Employee to be added.
 * @retval TRUE Employee successfully added to the vector of employees.
 * @retval FALSE Condominium can't afford a new employee.
 */
bool Condominio::addFuncionario(Funcionario funcionario) {
	if (this->fundos >= 1000) {
		this->funcionarios.insert(funcionario);
		this->fundos -= 1000;
		return true;
	} else
		return false;
}
/**
 * Removes a given employee from the condominium and cancels the service being done or waiting to be done by that employee.
 * @param pos Position of the employee in the condominium's vector of employees.
 * @retval TRUE Employee successfully removed.
 * @retval FALSE Invalid position.
 */
bool Condominio::eraseFuncionario(Funcionario &f1) {
	if (this->funcionarios.find(f1) == funcionarios.end())
		return false;
	if (f1.isOcupado())
		for (size_t i = 0; i < this->servicosEmCurso.size(); i++) {
			if (this->servicosEmCurso[i].getIDFuncionario() == f1.getID())
				this->eraseServico(i, 1);
		}
	else {
		for (size_t j = 0; j < this->servicosEmEspera.size(); j++)
			if (this->servicosEmEspera[j].getIDFuncionario() == f1.getID())
				this->eraseServico(j, 2);
	}
	this->funcionarios.erase(f1);
	return true;
}
/**
 * Sets an employee status to busy.
 * @param f1 Employee to be changed.
 */
void Condominio::setOcupado(Funcionario f1) {
	vector<Funcionario> funcionarios = this->getFuncionarios();
	for (size_t i = 0; i < funcionarios.size(); i++) {
		if (funcionarios[i] == f1) {
			funcionarios[i].setOcupado(true);
			break;
		}
	}
	this->setFuncionarios(funcionarios);
}

/**
 * @return Number of cleaning employees hired by the condominium.
 */
int Condominio::getNumFuncLimpeza() {
	vector<Funcionario> funcionarios = this->getFuncionarios();
	int total = 0;
	for (size_t i = 0; i < this->funcionarios.size(); i++)
		if (funcionarios[i].getEspecialidade() == "Limpeza")
			total++;
	return total;
}
/**
 * @return Number of cleaning employees available to do a service.
 */
int Condominio::getLivresLimpeza(vector<Funcionario> &funcionarios) {
	int total = 0;
	for (size_t i = 0; i < this->funcionarios.size(); i++)
		if (funcionarios[i].getEspecialidade() == "Limpeza")
			if (!funcionarios[i].isOcupado())
				total++;
	return total;
}
/**
 * @return Number of plumbers hired by the condominium.
 */
int Condominio::getNumFuncCanalizacao() {
	vector<Funcionario> funcionarios = this->getFuncionarios();
	int total = 0;
	for (size_t i = 0; i < this->funcionarios.size(); i++)
		if (funcionarios[i].getEspecialidade() == "Canalizacao")
			total++;
	return total;
}
/**
 * @return Number of plumbers available to do a service.
 */
int Condominio::getLivresCanalizacao(vector<Funcionario> &funcionarios) {
	int total = 0;
	for (size_t i = 0; i < this->funcionarios.size(); i++)
		if (funcionarios[i].getEspecialidade() == "Canalizacao")
			if (!funcionarios[i].isOcupado())
				total++;
	return total;
}
/**
 * @return Number of painters hired by the condominium.
 */
int Condominio::getNumFuncPintura() {
	vector<Funcionario> funcionarios = this->getFuncionarios();
	int total = 0;
	for (size_t i = 0; i < this->funcionarios.size(); i++)
		if (funcionarios[i].getEspecialidade() == "Pintura")
			total++;
	return total;
}
/**
 * @return Number of painters available to do a service.
 */
int Condominio::getLivresPintura(vector<Funcionario> &funcionarios) {
	int total = 0;
	for (size_t i = 0; i < this->funcionarios.size(); i++)
		if (funcionarios[i].getEspecialidade() == "Pintura")
			if (!funcionarios[i].isOcupado())
				total++;
	return total;
}

/**
 * Sorts the services according to a specified option.
 * @param vectorServicos Vector of services to be sorted.
 * @param sortOption 0 = ID, 1 = Type, 2 = Start Date, 3 = Requester's NIF.
 */
void Condominio::sortServicos(int vectorServicos, int sortOption) {
	if (vectorServicos == 0) {
		if (sortOption == 0)
			insertionSort(servicosTerminados);
		else if (sortOption == 1)
			sort(servicosTerminados.begin(), servicosTerminados.end(),
					compServicoTipo);
		else if (sortOption == 2)
			sort(servicosTerminados.begin(), servicosTerminados.end(),
					compServicoDataInicio);
		else if (sortOption == 3)
			sort(servicosTerminados.begin(), servicosTerminados.end(),
					compServicoNIF);
	} else if (vectorServicos == 1) {
		if (sortOption == 0)
			insertionSort(servicosEmCurso);
		else if (sortOption == 1)
			sort(servicosEmCurso.begin(), servicosEmCurso.end(),
					compServicoTipo);
		else if (sortOption == 2)
			sort(servicosEmCurso.begin(), servicosEmCurso.end(),
					compServicoDataInicio);
		else if (sortOption == 3)
			sort(servicosEmCurso.begin(), servicosEmCurso.end(),
					compServicoNIF);
	} else if (vectorServicos == 2) {
		if (sortOption == 0)
			insertionSort(servicosEmEspera);
		else if (sortOption == 1)
			sort(servicosEmEspera.begin(), servicosEmEspera.end(),
					compServicoTipo);
		else if (sortOption == 2)
			sort(servicosEmEspera.begin(), servicosEmEspera.end(),
					compServicoDataInicio);
		else if (sortOption == 3)
			sort(servicosEmEspera.begin(), servicosEmEspera.end(),
					compServicoNIF);
	}
}
/**
 * Adds a given service to the condominium.
 * @param vectorServicos 1 = servicosEmCurso, 2 = servicosEmEspera.
 * @param mes Current month.
 * @param servico Service to be added.
 * @retval TRUE Service successfully added.
 */
bool Condominio::addServico(int vectorServicos, string mes, Servico servico) {
	vector<Funcionario> funcionarios = this->getFuncionarios();
	if (vectorServicos == 1) {
		int idFuncionario = 0;
		for (size_t i = 0; i < funcionarios.size(); i++) {
			if (funcionarios[i].getEspecialidade()
					== servico.getEspecialidade())
				if (!funcionarios[i].isOcupado()) {
					idFuncionario = funcionarios[i].getID();
					funcionarios[i].setOcupado(true);
					break;
				}
		}
		servico.iniciarServico(mes, idFuncionario);
		servicosEmCurso.push_back(servico);
	} else if (vectorServicos == 2) {
		servicosEmEspera.push_back(servico);
	}
	this->setFuncionarios(funcionarios);
	return true;
}
/**
 * Deletes a service in the given vector from the condominium.
 * @param pos Position of the service in the given vector.
 * @param vectorServicos 0 = servicosTerminados, 1 = servicosEmCurso, 2 = servicosEmEspera.
 * @retval TRUE Service successfully deleted.
 * @retval False Invalid position.
 */
bool Condominio::eraseServico(int pos, int vectorServicos) {
	vector<Funcionario> funcionarios = this->getFuncionarios();

	if (vectorServicos == 0) { //Remover servico terminado
		if (pos >= servicosTerminados.size())
			return false;
		servicosTerminados.erase(servicosTerminados.begin() + pos);
		return true;
	} else if (vectorServicos == 1) { //Cancelar servico em curso
		for (size_t i = 0; i < this->funcionarios.size(); i++) {
			if (funcionarios[i].getID()
					== servicosEmCurso[pos].getIDFuncionario()) {
				funcionarios[i].setOcupado(false);
				this->setFuncionarios(funcionarios);
			}
		}
		for (size_t i = 0; i < this->servicosEmCurso.size(); i++) {
			if (pos == i) {
				for (size_t j = 0; j < this->habitacoes.size(); j++)
					if (this->habitacoes[j]->getServico()
							== servicosEmCurso[pos].getID()) {
						this->habitacoes[j]->setServico(-1);
						break;
					}
				this->servicosEmCurso.erase(servicosEmCurso.begin() + i);
				return true;
			}
		}
		return false;
	} else if (vectorServicos == 2) { //Cancelar servico em espera
		for (size_t i = 0; i < this->servicosEmEspera.size(); i++) {
			if (pos == i) {
				for (size_t j = 0; j < this->habitacoes.size(); j++)
					if (this->habitacoes[j]->getServico()
							== servicosEmEspera[pos].getID()) {
						this->habitacoes[j]->setServico(-1);
						break;
					}
				this->servicosEmEspera.erase(servicosEmEspera.begin() + i);
				return true;
			}
		}
		return false;
	}
	return false;
}
/**
 * Returns the minimum time a service of the specified type will be able to start.
 * @param tipo Type of service
 * @retval 0 Service can start immediately.
 * @return Time in which a service will be able to start, in seconds since Epoch.
 */
time_t Condominio::getDisponibilidadeServico(int tipo) {
	time_t disponibilidade = 0;
	vector<Funcionario> funcionarios = this->getFuncionarios();

	if (tipo == 0) { //Limpeza
		if (this->getLivresLimpeza(funcionarios) > 0)
			return disponibilidade;
		else {
			for (size_t i = 0; i < this->servicosEmEspera.size(); i++) {
				if (servicosEmEspera[i].getEspecialidade() == "Limpeza")
					if (servicosEmEspera[i].getDataRequisitado()
							> disponibilidade)
						disponibilidade =
								servicosEmEspera[i].getDataRequisitado()
										+ (2 * 60);
			}
			if (disponibilidade == 0) {
				for (size_t i = 0; i < this->servicosEmCurso.size(); i++) {
					if (servicosEmCurso[i].getEspecialidade() == "Limpeza") {
						if (disponibilidade == 0)
							disponibilidade = servicosEmCurso[i].getDataFim();
						else if (disponibilidade
								> servicosEmCurso[i].getDataFim())
							disponibilidade = servicosEmCurso[i].getDataFim();
					}
				}
			}
			return disponibilidade;
		}
	} else if (tipo == 1) { //Canalizacao
		if (this->getLivresCanalizacao(funcionarios) > 0)
			return disponibilidade;
		else {
			for (size_t i = 0; i < this->servicosEmEspera.size(); i++) {
				if (servicosEmEspera[i].getEspecialidade() == "Canalizacao")
					if (servicosEmEspera[i].getDataRequisitado()
							> disponibilidade)
						disponibilidade =
								servicosEmEspera[i].getDataRequisitado()
										+ (5 * 60);
			}
			if (disponibilidade == 0) {
				for (size_t i = 0; i < this->servicosEmCurso.size(); i++) {
					if (servicosEmCurso[i].getEspecialidade()
							== "Canalizacao") {
						if (disponibilidade == 0)
							disponibilidade = servicosEmCurso[i].getDataFim();
						else if (disponibilidade
								> servicosEmCurso[i].getDataFim())
							disponibilidade = servicosEmCurso[i].getDataFim();
					}
				}
			}
			return disponibilidade;
		}
	} else if (tipo == 2) { //Pintura
		if (this->getLivresPintura(funcionarios) > 0)
			return disponibilidade;
		else {
			for (size_t i = 0; i < this->servicosEmEspera.size(); i++) {
				if (servicosEmEspera[i].getEspecialidade() == "Pintura")
					if (servicosEmEspera[i].getDataRequisitado()
							> disponibilidade)
						disponibilidade =
								servicosEmEspera[i].getDataRequisitado()
										+ (10 * 60);
			}
			if (disponibilidade == 0) {
				for (size_t i = 0; i < this->servicosEmCurso.size(); i++) {
					if (servicosEmCurso[i].getEspecialidade() == "Pintura") {
						if (disponibilidade == 0)
							disponibilidade = servicosEmCurso[i].getDataFim();
						else if (disponibilidade
								> servicosEmCurso[i].getDataFim())
							disponibilidade = servicosEmCurso[i].getDataFim();
					}
				}
			}
			return disponibilidade;
		}
	}
	return 0;
}

/**
 * Checks if any service ended and "frees" its employee. Starts a waiting service, if there is a free employee.
 * @param mes Current month.
 * @param currentUser Pointer to the current user. Used to check if at least one of the currentUser's services ended.
 * @param servicosCurrentUser Number of services that ended of the current user.
 * @retval TRUE At least one service ended.
 * @retval FALSE No service ended.
 */
bool Condominio::updateServicos(string mes, Condomino* currentUser,
		int &servicosCurrentUser) {
	sortServicos(1, 2);

	int servicosQueAcabaram = 0;

	vector<Funcionario> funcionarios = this->getFuncionarios();

	//Verifica se algum servico terminou e liberta o funcionario
	for (size_t i = 0; i < servicosEmCurso.size(); i++) {
		if (servicosEmCurso[i].getDataFim() < time(NULL)) {
			for (size_t j = 0; j < funcionarios.size(); j++)
				if (funcionarios[j].getID()
						== servicosEmCurso[i].getIDFuncionario()) {
					funcionarios[j].setOcupado(false);
					funcionarios[j].addServicoEfectuado();
					break;
				}
			for (size_t k = 0; k < habitacoes.size(); k++) {
				if (habitacoes[k]->getServico() == servicosEmCurso[i].getID()) {
					habitacoes[k]->setServico(-1);
					break;
				}
			}
			servicosTerminados.push_back(servicosEmCurso[i]);
			servicosQueAcabaram++;
			if (currentUser != NULL)
				if (servicosEmCurso[i].getNIFcondomino()
						== currentUser->getNIF())
					servicosCurrentUser++;
			servicosEmCurso.erase(servicosEmCurso.begin() + i);
			if (!servicosEmCurso.empty())
				i--;
		}
	}

	int funcLimpeza = this->getLivresLimpeza(funcionarios);
	int funcCanalizacao = this->getLivresCanalizacao(funcionarios);
	int funcPintura = this->getLivresPintura(funcionarios);

	if (funcLimpeza > 0 || funcCanalizacao > 0 || funcPintura > 0) {
		for (size_t i = 0; i < servicosEmEspera.size(); i++) {
			if (funcLimpeza > 0) {
				if (servicosEmEspera[i].getEspecialidade() == "Limpeza") {
					this->addServico(1, mes, servicosEmEspera[i]);
					servicosEmEspera.erase(servicosEmEspera.begin() + i);
					if (!servicosEmEspera.empty())
						i--;
					funcLimpeza--;
				}
			} else if (funcCanalizacao > 0) {
				if (servicosEmEspera[i].getEspecialidade() == "Canalizacao") {
					this->addServico(1, mes, servicosEmEspera[i]);
					servicosEmEspera.erase(servicosEmEspera.begin() + i);
					if (!servicosEmEspera.empty())
						i--;
					funcCanalizacao--;
				}
			} else if (funcPintura > 0) {
				if (servicosEmEspera[i].getEspecialidade() == "Pintura") {
					this->addServico(1, mes, servicosEmEspera[i]);
					servicosEmEspera.erase(servicosEmEspera.begin() + i);
					if (!servicosEmEspera.empty())
						i--;
					funcPintura--;
				}
			}
		}
	}

	this->setFuncionarios(funcionarios);

	if (servicosQueAcabaram > 0)
		return true;
	else
		return false;
}
/**
 * Updates services at the end of the month. All services being done will end and
 * all services waiting to be done will be done, unless there isn't any employee of their type hired by the condominium.
 * @param mes Current month.
 * @retval TRUE At least one service ended.
 * @retval FALSE No service ended.
 */
bool Condominio::updateServicosFimMes(string mes) {
	sortServicos(1, 2);
	bool existemServicos = false;

	if (!servicosEmCurso.empty())
		existemServicos = true;

	vector<Funcionario> funcionarios = this->getFuncionarios();

	//Termina todos os servicos em curso e liberta os funcionarios
	for (size_t i = 0; i < servicosEmCurso.size(); i++) {
		servicosTerminados.push_back(servicosEmCurso[i]);
		for (size_t j = 0; j < funcionarios.size(); j++)
			if (funcionarios[j].getID()
					== servicosEmCurso[i].getIDFuncionario()) {
				funcionarios[j].setOcupado(false);
				funcionarios[j].addServicoEfectuado();
			}
		servicosEmCurso.erase(servicosEmCurso.begin() + i);
		if (!servicosEmCurso.empty())
			i--;
	}

	//Inicia ao mesmo tempo tantos servicos de limpeza em espera como os funcionarios de limpeza existentes,
	//a partir dai, os servicos iniciam-se sequencialmente, um apos o outro
	int funcLimpeza = this->getLivresLimpeza(funcionarios);
	time_t prevDataLimpeza = 0;

	//Inicia ao mesmo tempo tantos servicos de canalizacao em espera como os canalizadores existentes,
	//a partir dai, os servicos iniciam-se sequencialmente, um apos o outro
	int funcCanalizacao = this->getLivresCanalizacao(funcionarios);
	time_t prevDataCanalizacao = 0;

	//Inicia ao mesmo tempo tantos servicos de pintura em espera como os pintores existentes,
	//a partir dai, os servicos iniciam-se sequencialmente, um apos o outro
	int funcPintura = this->getLivresPintura(funcionarios);
	time_t prevDataPintura = 0;

	//Inicia e termina todos os servicos em espera possiveis
	for (size_t i = 0; i < servicosEmEspera.size(); i++) {
		if (servicosEmEspera[i].getEspecialidade() == "Limpeza") {
			//Se nao houver funcionarios de limpeza, o servico continua em espera no proximo mes
			if (this->getNumFuncLimpeza() == 0)
				continue;
			//Procura um funcionario que possa fazer o servico
			for (size_t j = 0; j < funcionarios.size(); j++) {
				if (funcionarios[j].getEspecialidade() == "Limpeza") {
					if (funcLimpeza > 0) {
						funcLimpeza--;
						servicosEmEspera[i].iniciarServico(mes,
								funcionarios[j].getID());
						if (funcLimpeza == 0)
							prevDataLimpeza = servicosEmEspera[i].getDataFim();
					} else if (funcLimpeza == 0) {
						servicosEmEspera[i].iniciarServico(mes,
								funcionarios[j].getID(), prevDataLimpeza);
						prevDataLimpeza = servicosEmEspera[i].getDataFim();
					}
					servicosTerminados.push_back(servicosEmEspera[i]);
					servicosEmEspera.erase(servicosEmEspera.begin() + i);
					if (!servicosEmEspera.empty())
						i--;
					break;
				}
			}
			continue;
		}
		if (servicosEmEspera[i].getEspecialidade() == "Canalizacao") {
			//Se nao houve canalizadores, o servico continua em espera no proximo mes
			if (this->getNumFuncCanalizacao() == 0)
				continue;
			//Procura um funcionario que possa fazer o servico
			for (size_t j = 0; j < funcionarios.size(); j++) {
				if (funcionarios[j].getEspecialidade() == "Canalizacao") {
					if (funcCanalizacao > 0) {
						funcCanalizacao--;
						servicosEmEspera[i].iniciarServico(mes,
								funcionarios[j].getID());
						if (funcCanalizacao == 0)
							prevDataCanalizacao =
									servicosEmEspera[i].getDataFim();
					} else if (funcCanalizacao == 0) {
						servicosEmEspera[i].iniciarServico(mes,
								funcionarios[j].getID(), prevDataCanalizacao);
						prevDataCanalizacao = servicosEmEspera[i].getDataFim();
					}
					servicosTerminados.push_back(servicosEmEspera[i]);
					servicosEmEspera.erase(servicosEmEspera.begin() + i);
					if (!servicosEmEspera.empty())
						i--;
					break;
				}
			}
			continue;
		}
		if (servicosEmEspera[i].getEspecialidade() == "Pintura") {
			//Se nao houver pintores, o servico continua em espera no proximo mes
			if (this->getNumFuncPintura() == 0)
				continue;
			//Procura um funcionario que possa fazer o servico
			for (size_t j = 0; j < funcionarios.size(); j++) {
				if (funcionarios[j].getEspecialidade() == "Pintura") {
					if (funcPintura > 0) {
						funcPintura--;
						servicosEmEspera[i].iniciarServico(mes,
								funcionarios[j].getID());
						if (funcPintura == 0)
							prevDataPintura = servicosEmEspera[i].getDataFim();
					} else if (funcPintura == 0) {
						servicosEmEspera[i].iniciarServico(mes,
								funcionarios[j].getID(), prevDataPintura);
						prevDataPintura = servicosEmEspera[i].getDataFim();
					}
					servicosTerminados.push_back(servicosEmEspera[i]);
					servicosEmEspera.erase(servicosEmEspera.begin() + i);
					if (!servicosEmEspera.empty())
						i--;
					break;
				}
			}
			continue;
		}
	}
	this->setFuncionarios(funcionarios);

	return existemServicos;
}

/**
 * Updates the month and gets the rent from every tenant.
 * @return Vector of tenants that didn't fully pay their rent.
 */
vector<Condomino> Condominio::fimDoMes() {
	vector<Condomino> caloteiros;

//Actualiza o mes actual. Se o ano acabar, reinicializa o estado da renda das habitacoes de todos os condominos
	if (this->currentMes < 11) //0 = Janeiro
		this->currentMes++;
	else if (this->currentMes == 11) { //11 = Dezembro
		this->currentMes = 0;
		for (size_t i = 0; i < this->moradores.size(); i++) {
			for (size_t j = 0; j < this->moradores[i].getHabitacoes().size();
					j++)
				this->moradores[i].getHabitacoes()[j]->resetPago();
		}
	}

	for (size_t i = 0; i < moradores.size(); i++) {
		//Fundos mensais que o condomino tem para pagar as rendas
		int fundosRestantes = moradores[i].getFundosMensais();
		//Actualizar o pagamento da renda para cada habitacao que ele possuir
		for (size_t j = 0; j < moradores[i].getHabitacoes().size(); j++) {
			if (fundosRestantes > 0) {
				int diferenca = fundosRestantes
						- moradores[i].getHabitacoes()[j]->calcRenda();
				//Adiciona a renda aos fundos do condominio e define como pago o mes actual da habitacao
				if (diferenca >= 0) {
					fundos += moradores[i].getHabitacoes()[j]->calcRenda();
					moradores[i].getHabitacoes()[j]->setPago(this->currentMes);
					fundosRestantes -=
							moradores[i].getHabitacoes()[j]->calcRenda();
				}
				//Se nao tiver fundos para pagar totalmente a renda, adiciona o que conseguir aos fundos do condominio
				//e adiciona à divida do condomino o montante que nao conseguiu pagar
				else {
					fundos += moradores[i].getHabitacoes()[j]->calcRenda()
							+ diferenca;
					moradores[i].addDivida(diferenca);
					fundosRestantes -=
							moradores[i].getHabitacoes()[j]->calcRenda();
				}
			}
			//Se nao tiver fundos, adiciona à divida do condomino a renda que nao conseguiu pagar
			else
				moradores[i].addDivida(
						-moradores[i].getHabitacoes()[j]->calcRenda());
		}
		//Se ainda restarem fundos e o condomino tiver uma divida,
		//ele usa esses fundos para saldar essa divida (total ou parcialmente)
		if (fundosRestantes > 0 && moradores[i].getDivida() < 0) {
			int novaDivida = moradores[i].getDivida() + fundosRestantes;
			if (novaDivida > 0)
				novaDivida = 0;
			moradores[i].setDivida(novaDivida);
		}
		//Se o condomino nao conseguiu pagar o mes, adiciona ao vector dos caloteiros que vai ser retornado
		if (fundosRestantes < 0)
			caloteiros.push_back(moradores[i]);
	}

//Actualiza o pagamento aos funcionarios
	fundos -= this->funcionarios.size() * 500;

	return caloteiros;
}

/**
 * Displays info of every single tenant in the condominium.
 */
void Condominio::infoMoradores() const {
	cout << "Numero de moradores = " << this->moradores.size() << "\n" << endl;
	for (size_t i = 0; i < this->moradores.size(); i++) {
		cout << i + 1 << " - ";
		this->moradores[i].infoCondomino();
	}
}
/**
 * Displays info of every single house in the condomonium.
 */
void Condominio::infoHabitacoes() const {
	cout << "Numero de habitacoes = " << habitacoes.size() << "\n" << endl;
	for (size_t i = 0; i < habitacoes.size(); i++) {
		cout << i + 1 << " - ";
		habitacoes[i]->info();
	}
}

/**
 * Adds new transport to the list
 * @param toAdd Transport to be added
 * @return void
 */
void Condominio::addTransporte(Transporte toAdd) {
	transportes.push(toAdd);
}

/*
 * Non-class functions
 */

/**
 * Compares two condominiums by ID for sorting purposes.
 * @retval TRUE If first condominium is "lower" than the second one.
 * @retval FALSE If the first condominium is "equal or higher" than the second one.
 */
bool compCondominioID(Condominio c1, Condominio c2) {
	return c1.getID() < c2.getID();
}
/**
 * Compares two condominiums by name for sorting purposes.
 * @retval TRUE If first condominium is "lower" than the second one.
 * @retval FALSE If the first condominium is "equal or higher" than the second one.
 */
bool compCondominioDesignacao(Condominio c1, Condominio c2) {
	if (c1.getDesignacao() < c2.getDesignacao())
		return true;
	else if (c1.getDesignacao() > c2.getDesignacao())
		return false;
	else
		return c1.getID() < c2.getID();
}
/**
 * Compares two condominiums by number of properties for sorting purposes.
 * @retval TRUE If first condominium is "lower" than the second one.
 * @retval FALSE If the first condominium is "equal or higher" than the second one.
 */
bool compCondominioPropriedades(Condominio c1, Condominio c2) {
	if (c1.getNumHabitacoes() < c2.getNumHabitacoes())
		return true;
	else if (c1.getNumHabitacoes() > c2.getNumHabitacoes())
		return false;
	else if (c1.getNumVivendas() < c2.getNumVivendas())
		return true;
	else if (c1.getNumVivendas() > c2.getNumVivendas())
		return false;
	else
		return c1.getID() < c2.getID();
}
/**
 * Compares two condominiums by address for sorting purposes.
 * @retval TRUE If first condominium is "lower" than the second one.
 * @retval FALSE If the first condominium is "equal or higher" than the second one.
 */
bool compCondominioLocalizacao(Condominio c1, Condominio c2) {
	if (c1.getLocalizacao().cidade < c2.getLocalizacao().cidade)
		return true;
	else if (c1.getLocalizacao().cidade > c2.getLocalizacao().cidade)
		return false;
	else
		return c1.getID() < c2.getID();
}

/**
 * Compares two tenants by name for sorting purposes.
 * @retval TRUE If first tenant is "lower" than the second tenant.
 * @retval FALSE If the first tenant is "equal or higher" than the second tenant.
 */
bool compCondominoNomeCivil(Condomino c1, Condomino c2) {
	if (c1.getNomeCivil() < c2.getNomeCivil())
		return true;
	else if (c1.getNomeCivil() > c2.getNomeCivil())
		return false;
	else
		return c1.getNomeUtilizador() < c2.getNomeUtilizador();
}
/**
 * Compares two tenants by NIF for sorting purposes.
 * @retval TRUE If first tenant is "lower" than the second tenant.
 * @retval FALSE If the first tenant is "equal or higher" than the second tenant.
 */
bool compCondominoNIF(Condomino c1, Condomino c2) {
	return c1.getNIF() < c2.getNIF();
}
/**
 * Compares two employees by specialty for sorting purposes.
 * @retval TRUE If first employee is "lower" than the second employee.
 * @retval FALSE If the first employee is "equal or higher" than the second employee.
 */
bool compFuncionarioEspecialidade(Funcionario f1, Funcionario f2) {
	if (f1.getEspecialidade() < f2.getEspecialidade())
		return true;
	else if (f1.getEspecialidade() > f2.getEspecialidade())
		return false;
	else
		return (f1.getID() < f2.getID());
}
/**
 * Compares two employees by occupation status for sorting purposes.
 * @retval TRUE If first employee is "lower" than the second employee.
 * @retval FALSE If the first employee is "equal or higher" than the second employee.
 */
bool compFuncionarioOcupacao(Funcionario f1, Funcionario f2) {
	if (f1.isOcupado() < f2.isOcupado())
		return true;
	else if (f1.isOcupado() > f2.isOcupado())
		return false;
	else
		return (f1.getID() < f2.getID());
}
/**
 * Compares two employees by the number of services for sorting purposes.
 * @retval TRUE If first employee is "lower" than the second employee.
 * @retval FALSE If the first employee is "equal or higher" than the second employee.
 */
bool compFuncionarioServicos(Funcionario f1, Funcionario f2) {
	if (f1.getServicosEfectuados() < f2.getServicosEfectuados())
		return true;
	else if (f1.getServicosEfectuados() > f2.getServicosEfectuados())
		return false;
	else
		return (f1.getID() < f2.getID());
}
/**
 * Compares two services by the type of service for sorting purposes.
 * @retval TRUE If first service is "lower" than the second service.
 * @retval FALSE If the first service is "equal or higher" than the second service.
 */
bool compServicoTipo(Servico s1, Servico s2) {
	if (s1.getEspecialidade() < s2.getEspecialidade())
		return true;
	else if (s1.getEspecialidade() > s2.getEspecialidade())
		return false;
	else
		return (s1.getID() < s2.getID());
}
/**
 * Compares two services by their start date for sorting purposes.
 * @retval TRUE If first service is "lower" than the second service.
 * @retval FALSE If the first service is "equal or higher" than the second service.
 */
bool compServicoDataInicio(Servico s1, Servico s2) {
	if (difftime(s2.getDataInicio(), s1.getDataInicio()) > 0)
		return true;
	else if (difftime(s2.getDataInicio(), s1.getDataInicio()) < 0)
		return false;
	else
		return (s1.getID() < s2.getID());
}
/**
 * Compares two services by the NIF of the tenants who requested them for sorting purposes.
 * @retval TRUE If first service is "lower" than the second service.
 * @retval FALSE If the first service is "equal or higher" than the second service.
 */
bool compServicoNIF(Servico s1, Servico s2) {
	if (s1.getNIFcondomino() < s2.getNIFcondomino())
		return true;
	else if (s1.getNIFcondomino() > s2.getNIFcondomino())
		return false;
	else
		return (s1.getID() < s2.getID());
}


bool compParagemNome(Paragem p1, Paragem p2){
	return p1.getNome() < p2.getNome();
}

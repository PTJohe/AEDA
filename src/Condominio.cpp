#include "../headers/Condominio.h"
/**
 * Default constructor.
 */
Condominio::Condominio() {
	this->fundos = 5000;
	this->currentMes = 0;
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
	return funcionarios;
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
	this->funcionarios = funcionarios;
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
 * Adds a tenant to the condominium.
 * @param condomino Tenant to be added.
 * @return Position of the new tenant in the vector of tenants. Position = -1 if tenant to be added is already in the vector.
 */
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
 * @param sortOption 0 = Type, 1 = Rent, 2 = Owner's NIF.
 */
void Condominio::sortHabitacoes(int sortOption) {
	if (sortOption == 0)
		sort(habitacoes.begin(), habitacoes.end(), compHabitacaoTipo);
	else if (sortOption == 1)
		sort(habitacoes.begin(), habitacoes.end(), compHabitacaoRenda);
	else if (sortOption == 2)
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
		sortHabitacoes(2);
		return true;
	} else
		return false;
}
/**
 * Removes a house from a given user.
 * @param condomino User whose house is being removed.
 * @param pos Position of the house in the owner's vector of owned houses.
 */
bool Condominio::eraseHabitacaoPossuida(Condomino condomino, int pos) {
	int pos1 = sequentialSearch(this->moradores, condomino);
	if (pos1 == -1) {
		return false;
	} else {
		Habitacao* h1 = moradores[pos1].getHabitacoes()[pos];
		int pos2 = this->findHabitacao(this->habitacoes, h1);
		if (pos2 != -1)
			this->habitacoes.erase(habitacoes.begin() + pos2);

		bool success = moradores[pos1].eraseHabitacao(pos);
		sortHabitacoes(2);
		return success;
	}
}
/**
 * Removes a house from the condominium.
 * @param pos Position of the house in the condominium's vector of houses.
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
		habitacoes.erase(habitacoes.begin() + pos);
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
			for (size_t j = 0; j <= this->currentMes; j++) {
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
 * Adds a given employee to the condominium.
 * @param funcionario Employee to be added.
 * @retval TRUE Employee successfully added to the vector of employees.
 * @retval FALSE Employee already exists in the vector of employees.
 */
bool Condominio::addFuncionario(Funcionario funcionario) {
	int pos = sequentialSearch(this->funcionarios, funcionario);
	if (pos == -1) {
		return false;
	}
	this->funcionarios.push_back(funcionario);
	return true;
}
/**
 * Adds a given service to the condominium.
 * @param servico Service to be added.
 * @retval TRUE Service successfully added.
 * @retval FALSE Service already exists or there aren't enough employees to do it.
 */
bool Condominio::addServico(Servico servico) {
	//if houver recursos, adiciona ao servicosEmCurso
	//else adiciona servicosEmEspera
	return true;
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

/*
 * Non-class functions
 */

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

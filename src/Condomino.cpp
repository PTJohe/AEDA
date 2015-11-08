#include "../headers/Condomino.h"

/**
 * Constructor
 * @param nomeUtilizador Username.
 * @param password Password.
 */
Condomino::Condomino(string nomeUtilizador, string password) {
	this->nomeUtilizador = nomeUtilizador;
	this->password = password;
	this->admin = false;
	this->nomeCivil = "NAO DEFINIDO";
	this->NIF = "NAO DEFINIDO";
	this->fundosMensais = 0;
	this->divida = 0;
}
/**
 * Contructor.
 * @param nomeUtilizador Username.
 * @param password Password.
 * @param nomeCivil Tenant's Name.
 * @param NIF Tenant's NIF.
 */
Condomino::Condomino(string nomeUtilizador, string password, string nomeCivil,
		string NIF) {
	this->nomeUtilizador = nomeUtilizador;
	this->password = password;
	this->admin = false;
	this->nomeCivil = nomeCivil;
	this->NIF = NIF;
	this->fundosMensais = 0;
	this->divida = 0;
}
/**
 * Complete constructor. Only used when importing tenant data.
 * @param nomeUtilizador Username.
 * @param password Password.
 * @param admin If true, tenant has admin rights, else, if false, tenant has a normal account.
 * @param nomeCivil Tenant's name.
 * @param NIF Tenant's NIF.
 * @param fundosMensais Tenant's monthly funds.
 * @param divida Tenant's debt.
 */
Condomino::Condomino(string nomeUtilizador, string password, bool admin,
		string nomeCivil, string NIF, long int fundosMensais, long int divida) {
	this->nomeUtilizador = nomeUtilizador;
	this->password = password;
	this->admin = admin;
	this->nomeCivil = nomeCivil;
	this->NIF = NIF;
	this->fundosMensais = fundosMensais;
	this->divida = divida;
}

/**
 * @return Account's username.
 */
string Condomino::getNomeUtilizador() const {
	return nomeUtilizador;
}
/**
 * @return Account's password.
 */
string Condomino::getPassword() const {
	return password;
}
/**
 * @retval TRUE User has administrator rights.
 * @retval FALSE User is not an administrator.
 */
bool Condomino::isAdmin() const {
	return admin;
}

/**
 * @return Tenant's name.
 */
string Condomino::getNomeCivil() const {
	return nomeCivil;
}
/**
 * @return Tenant's NIF.
 */
string Condomino::getNIF() const {
	return NIF;
}
/**
 * @return Tenant's monthly funds.
 */
int Condomino::getFundosMensais() const {
	return fundosMensais;
}
/**
 * @return Tenant's debt.
 */
int Condomino::getDivida() const {
	return divida;
}
/**
 * @return Tenant's owned houses.
 */
vector<Habitacao *> Condomino::getHabitacoes() {
	return habitacoes;
}
/**
 * @return Tenant's total monthly rent.
 */
int Condomino::getTotalRenda() const {
	int total = 0;
	for (size_t i = 0; i < habitacoes.size(); i++)
		total += habitacoes[i]->calcRenda();
	return total;
}

/**
 * Sets a new username.
 * @param novoNomeUtilizador New username.
 */
void Condomino::setNomeUtilizador(string novoNomeUtilizador) {
	this->nomeUtilizador = novoNomeUtilizador;
}
/**
 * Sets a new password.
 * @param novaPassword New password.
 */
void Condomino::setPassword(string novaPassword) {
	this->password = novaPassword;
}
/**
 * Sets administrators rights.
 * @param admin If true, sets admin rights, else, if false, revokes admin rights.
 */
void Condomino::setAdmin(bool admin) {
	this->admin = admin;
}

/**
 * Sets new tenant's name.
 * @param novoNomeCivil New name.
 */
void Condomino::setNomeCivil(string novoNomeCivil) {
	this->nomeCivil = novoNomeCivil;
}
/**
 * Sets new tenant's NIF.
 * @param novoNIF New NIF.
 */
void Condomino::setNIF(string novoNIF) {
	this->NIF = novoNIF;
	for (size_t i = 0; i < this->habitacoes.size(); i++) {
		this->habitacoes[i]->setProprietario(novoNIF);
	}
}
/**
 * Sets new tenant's monthly funds.
 * @param novosFundos New monthly funds.
 */
void Condomino::setFundosMensais(long int novosFundos) {
	this->fundosMensais = novosFundos;
}
/**
 * Sets new tenant's debt.
 * @param novaDivida New debt.
 */
void Condomino::setDivida(long int novaDivida) {
	this->divida = novaDivida;
}
/**
 * Adds a given amount to the tenant's current debt.
 * @param novaDivida Amount to add.
 */
void Condomino::addDivida(long int novaDivida) {
	this->divida += novaDivida;
}
/**
 * Sets new tenant's owned houses.
 * @param habitacoes New vector of owned houses.
 */
void Condomino::setHabitacoes(vector<Habitacao*> habitacoes) {
	this->habitacoes = habitacoes;
}

/**
 * Sorts tenant's owned houses by ID.
 */
void Condomino::sortHabitacoes() {
	sort(habitacoes.begin(), habitacoes.end(), compHabitacaoNIF);
}
/**
 * Adds a new house to the tenant's owned houses.
 * @param h1 House to be added.
 * @param currentMes Current month, used to set paid rent for previous months.
 */
void Condomino::addHabitacao(Habitacao* h1, int currentMes) {
	h1->setProprietario(this->NIF);
	for (size_t i = 0; i <= currentMes; i++)
		h1->setPago(i);
}
/**
 * Removes owned house from the condominium.
 * @param pos Position of the house in the tenant's vector of owned houses.
 * @retval TRUE House successfully removed.
 * @retval FALSE Invalid position.
 */
bool Condomino::eraseHabitacao(int pos) {
	if (pos != -1) {
		delete habitacoes[pos];
		habitacoes.erase(habitacoes.begin() + pos);
		return true;
	} else
		return false;
}

/**
 * Checks if the given password is equal to the account's password.
 * @param password Password to compare.
 * @retval TRUE Passwords are equal.
 * @retval FALSE Wrong password.
 */
bool Condomino::validPassword(string password) {
	if (this->password == password)
		return true;
	else
		return false;
}
/**
 * Checks if the tenant has valid name and NIF.
 * @retval TRUE Valid data.
 * @retval FALSE Either the tenant has an invalid name or an invalid NIF.
 */
bool Condomino::hasDados() const {
	if (this->nomeCivil == "NAO DEFINIDO" || this->NIF == "")
		return false;
	else
		return true;
}
/**
 * Compares two tenants by their username and NIF.
 * @param c1 Tenant to be compared.
 * @retval TRUE Equal username or NIF.
 * @retval FALSE Tenants are different.
 */
bool Condomino::operator==(const Condomino c1) const {
	if (this->nomeUtilizador == c1.nomeUtilizador) {
		return true;
	} else
		return (this->NIF == c1.NIF);
}
/**
 * Compares two tenants by their username using lexicographic ordering for sorting purposes.
 * @param c1 Tenant to be compared.
 * @retval TRUE Tenant has a "lower" username than c1.
 * @retval FALSE Tenant has an "equal or higher" username than c1.
 */
bool Condomino::operator<(const Condomino c1) const {
	return this->nomeUtilizador < c1.nomeUtilizador;
}

/**
 * Displays account info.
 */
void Condomino::infoConta() const {
	cout << "Nome de utilizador - " << nomeUtilizador << endl;
	cout << "Password - " << password << endl;
	cout << "Admin - ";
	if (this->admin)
		cout << "SIM" << endl;
	else
		cout << "NAO" << endl;
	cout << endl;
}
/**
 * Displays tenant info.
 */
void Condomino::infoCondomino() const {
	cout << this->nomeCivil << endl;
	cout << "NIF: " << this->NIF << endl;
	cout << "Numero de habitacoes: " << this->habitacoes.size() << endl;
	if (!habitacoes.empty())
		cout << "Renda total actual = " << this->getTotalRenda() << "$" << endl;
	cout << "Fundos Mensais = " << this->fundosMensais << "$" << endl;
	cout << "Divida = " << this->divida << "$" << "\n" << endl;
}
/**
 * Displays owned houses info.
 */
void Condomino::infoHabitacoes() const {
	cout << "Numero de habitacoes = " << this->habitacoes.size() << "\n"
			<< endl;

	for (size_t i = 0; i < this->habitacoes.size(); i++) {
		cout << i + 1 << " - ";
		habitacoes[i]->info();
	}
}
/**
 * Displays monthly rent info.
 */
void Condomino::infoRenda() const {
	cout << "ESTADO DA RENDA:" << endl;
	cout << "Numero de habitacoes = " << this->habitacoes.size() << "\n"
			<< endl;

	cout << "\t\tRenda\t J F M A M J J A S O N D" << endl;
	if (habitacoes.empty())
		cout << "Nao possui habitacoes." << endl;
	else {
		for (size_t i = 0; i < this->habitacoes.size(); i++) {
			cout << i + 1 << " - " << habitacoes[i]->getTipo() << "\t"
					<< habitacoes[i]->calcRenda() << "$" << "\t|";
			for (size_t j = 0; j < 12; j++) {
				if (this->habitacoes[i]->getPago(j) == 1)
					cout << "X|";
				else
					cout << " |";
			}
			cout << endl;
		}
	}
}

/*
 * Non-class functions
 */

/**
 * Compares two houses by ID for sorting purposes.
 * @retval TRUE If first tenant is "lower" than the second tenant.
 * @retval FALSE If the first tenant is "equal or higher" than the second tenant.
 */
bool compHabitacaoID(Habitacao* h1, Habitacao* h2) {
	return (h1->getID() < h2->getID());
}
/**
 * Compares two houses by type for sorting purposes.
 * @retval TRUE If first tenant is "lower" than the second tenant.
 * @retval FALSE If the first tenant is "equal or higher" than the second tenant.
 */
bool compHabitacaoTipo(Habitacao* h1, Habitacao* h2) {
	if (h1->getTipo() < h2->getTipo())
		return true;
	else if (h1->getTipo() > h2->getTipo())
		return false;
	else if (h1->getNIFProprietario() < h2->getNIFProprietario())
		return true;
	else if (h1->getNIFProprietario() > h2->getNIFProprietario())
		return false;
	else
		return (h1->getID() < h2->getID());
}
/**
 * Compares two houses by monthly rent for sorting purposes.
 * @retval TRUE If first tenant has a smaller rent than the second tenant.
 * @retval FALSE If the first tenant has an equal or bigger rent than the second tenant.
 */
bool compHabitacaoRenda(Habitacao* h1, Habitacao* h2) {
	if (h1->calcRenda() < h2->calcRenda())
		return true;
	else if (h1->calcRenda() > h2->calcRenda())
		return false;
	else if (h1->getNIFProprietario() < h2->getNIFProprietario())
		return true;
	else if (h1->getNIFProprietario() > h2->getNIFProprietario())
		return false;
	else
		return (h1->getID() < h2->getID());
}
 /**
 * Compares two houses by owner's NIF for sorting purposes.
 * @retval TRUE If first tenant is "lower" than the second tenant.
 * @retval FALSE If the first tenant is "equal or higher" than the second tenant.
 */
bool compHabitacaoNIF(Habitacao* h1, Habitacao* h2) {
	if (h1->getNIFProprietario() < h2->getNIFProprietario())
		return true;
	else if (h1->getNIFProprietario() > h2->getNIFProprietario())
		return false;
	else
		return (h1->getID() < h2->getID());
}

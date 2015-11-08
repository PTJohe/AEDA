#include "../headers/Habitacao.h"

/*
 * Habitacao
 */

static int nextId = 1;

/**
 * Constructor of an empty house.
 * @param morada House address.
 * @param codigoPostal House postal code.
 */
Habitacao::Habitacao(string morada, string codigoPostal) {
	this->id = nextId;
	nextId++;
	this->morada = morada;
	this->codigoPostal = codigoPostal;
	this->NIFProprietario = "";
	fill(this->pago, pago + sizeof(pago), 0);
	this->idServico = -1;
}
/**
 * Constructor of an owned house.
 * @param morada House address.
 * @param codigoPostal House postal code.
 * @param NIFProprietario Owner's NIF.
 */
Habitacao::Habitacao(string morada, string codigoPostal,
		string NIFProprietario) {
	this->id = nextId;
	nextId++;
	this->morada = morada;
	this->codigoPostal = codigoPostal;
	this->NIFProprietario = NIFProprietario;
	fill(this->pago, pago + sizeof(pago), 0);
	this->idServico = -1;
}
/**
 * Constructor of an owned house with rent.
 * @param morada House address.
 * @param codigoPostal House postal code.
 * @param NIFProprietario Owner's NIF.
 * @param pago[12] Paid rent for each month.
 */
Habitacao::Habitacao(string morada, string codigoPostal, string NIFProprietario,
		bool pago[12]) {
	this->id = nextId;
	nextId++;
	this->morada = morada;
	this->codigoPostal = codigoPostal;
	this->NIFProprietario = NIFProprietario;
	for (size_t i = 0; i < 12; i++) {
		this->pago[i] = pago[i];
	}
	this->idServico = -1;
}
/**
 * Complete constructor. This is only used to import house data.
 * @param id House ID.
 * @param morada House address.
 * @param codigoPostal House postal code.
 * @param NIFProprietario Owner's NIF.
 * @param pago[12] Paid rent for each month.
 * @param idService Service ID (-1 = No service).
 */
Habitacao::Habitacao(int id, string morada, string codigoPostal,
		string NIFProprietario, bool pago[12], int idServico) {
	this->id = id;
	if (id + 1 > nextId)
		nextId = id + 1;
	this->morada = morada;
	this->codigoPostal = codigoPostal;
	this->NIFProprietario = NIFProprietario;
	for (size_t i = 0; i < 12; i++) {
		this->pago[i] = pago[i];
	}
	this->idServico = idServico;
}

/**
 * @return House ID.
 */
int Habitacao::getID() const {
	return id;
}
/**
 * @return House address.
 */
string Habitacao::getMorada() const {
	return morada;
}
/**
 * @return House postal code.
 */
string Habitacao::getCodigoPostal() const {
	return codigoPostal;
}
/**
 * @return Owner's NIF.
 */
string Habitacao::getNIFProprietario() const {
	return NIFProprietario;
}
/**
 * @retval TRUE House has an owner.
 * @retval FALSE Empty house.
 */
bool Habitacao::hasProprietario() const {
	if (NIFProprietario == "")
		return false;
	else
		return true;
}
/**
 * Checks whether a given month was paid or not.
 * @param mes Month to check
 * @retval TRUE Month was paid.
 * @retval FALSE Month wasn't paid.
 */
bool Habitacao::getPago(int mes) const {
	return pago[mes];
}
/**
 * @return Service ID (-1 = No service)
 */
int Habitacao::getServico() const {
	return idServico;
}

/**
 * Sets house address.
 * @param morada New address.
 */
void Habitacao::setMorada(string morada) {
	this->morada = morada;
}
/**
 * Sets house postal code.
 * @param codigoPostal New postal code.
 */
void Habitacao::setCodigoPostal(string codigoPostal) {
	this->codigoPostal = codigoPostal;
}
/**
 * Sets owner's NIF.
 * @param nif New owner's NIF.
 */
void Habitacao::setProprietario(string nif) {
	this->NIFProprietario = nif;
}
/**
 * Sets a given month to paid.
 * @param mes Month to be paid.
 */
void Habitacao::setPago(int mes) {
	this->pago[mes] = true;
}
/**
 * Clears paid array. Used when the year ends.
 */
void Habitacao::resetPago() {
	for (size_t i = 0; i < 12; i++)
		this->pago[i] = false;
}
/**
 * Sets service id.
 * @param id New service id.
 */
void Habitacao::setServico(int id) {
	this->idServico = id;
}
/**
 * Decrements house ID. Used when creating a house just to compare and immediately delete it, without affecting houses id.
 */
void Habitacao::decID() {
	nextId--;
}

/*
 * Vivenda
 */

/**
 * Constructor of an empty house.
 * @param morada House address.
 * @param codigoPostal House postal code.
 * @param areaInterior Interior area.
 * @param areaExterior Exterior area.
 * @param piscina True if house has a swimming pool, false otherwise.
 */
Vivenda::Vivenda(string morada, string codigoPostal, float areaInterior,
		float areaExterior, bool piscina) :
		Habitacao(morada, codigoPostal) {
	this->areaInterior = areaInterior;
	this->areaExterior = areaExterior;
	this->piscina = piscina;
}
/**
 * Constructor of an owned house.
 * @param morada House address.
 * @param codigoPostal House postal code.
 * @param proprietario Owners' NIF.
 * @param areaInterior Interior area.
 * @param areaExterior Exterior area.
 * @param piscina True if house has a swimming pool, false otherwise.
 */
Vivenda::Vivenda(string morada, string codigoPostal, string proprietario,
		float areaInterior, float areaExterior, bool piscina) :
		Habitacao(morada, codigoPostal, proprietario) {
	this->areaInterior = areaInterior;
	this->areaExterior = areaExterior;
	this->piscina = piscina;
}
/**
 * Constructor of an owned house with rent.
 * @param morada House address.
 * @param codigoPostal House postal code.
 * @param proprietario Owners' NIF.
 * @param pago[12] Rent for each month.
 * @param areaInterior Interior area.
 * @param areaExterior Exterior area.
 * @param piscina True if house has a swimming pool, false otherwise.
 */
Vivenda::Vivenda(string morada, string codigoPostal, string proprietario,
		bool pago[12], float areaInterior, float areaExterior, bool piscina) :
		Habitacao(morada, codigoPostal, proprietario, pago) {
	this->areaInterior = areaInterior;
	this->areaExterior = areaExterior;
	this->piscina = piscina;
}
/**
 * Complete constructor. This is only used for importing house data.
 * @param id House id.
 * @param morada House address.
 * @param codigoPostal House postal code.
 * @param proprietario Owners' NIF.
 * @param pago[12] Rent for each month.
 * @param idServico Service ID (-1 = No service).
 * @param areaInterior Interior area.
 * @param areaExterior Exterior area.
 * @param piscina True if house has a swimming pool, false otherwise.
 */
Vivenda::Vivenda(int id, string morada, string codigoPostal,
		string proprietario, bool pago[12], int idServico, float areaInterior,
		float areaExterior, bool piscina) :
		Habitacao(id, morada, codigoPostal, proprietario, pago, idServico) {
	this->areaInterior = areaInterior;
	this->areaExterior = areaExterior;
	this->piscina = piscina;
}

/**
 * Sets interior area.
 * @param area New interior area.
 */
void Vivenda::setAreaInterior(float area) {
	this->areaInterior = area;
}
/**
 * Sets exterior area.
 * @param area New exterior area.
 */
void Vivenda::setAreaExterior(float area) {
	this->areaExterior = area;
}
/**
 * Sets if a house has a swimming pool or not.
 * @param piscina True if house now has a swimming pool, false otherwise.
 */
void Vivenda::setPiscina(bool piscina) {
	this->piscina = piscina;
}

/**
 * @return Interior area.
 */
float Vivenda::getAreaInterior() const {
	return areaInterior;
}
/**
 * @return Exterior area.
 */
float Vivenda::getAreaExterior() const {
	return areaExterior;
}
/**
 * @retval TRUE House has a swimming pool.
 * @retval FALSE House doesn't have a swimming pool.
 */
bool Vivenda::getPiscina() const {
	return piscina;
}

/**
 * @return Type of house. In this case = "Vivenda".
 */
string Vivenda::getTipo() const {
	string tipo = "Vivenda";
	return tipo;
}
/**
 * Calculates rent. Formula is 250 + 0.5 * Exterior Area. If house has a swimming pool, add 100$.
 * @return Monthly rent.
 */
float Vivenda::calcRenda() const {
	return (250 + 0.5 * areaExterior + 100 * piscina);
}

/**
 * Displays house info.
 */
void Vivenda::info() const {
	cout << "Vivenda" << endl;
	cout << "NIF Proprietario = " << NIFProprietario << endl;
	cout << "Morada - " << morada + ", " + codigoPostal << endl;
	cout << "Area Habitacional = " << areaInterior << endl;
	cout << "Area Exterior = " << areaExterior << endl;
	cout << "Piscina - ";
	if (this->piscina)
		cout << "Sim" << endl;
	else
		cout << "Nao" << endl;
	cout << "Renda = " << this->calcRenda() << "$\n" << endl;
}

/*
 * Apartamento
 */

/**
 * Constructor of an empty appartment.
 * @param morada House address.
 * @param codigoPostal House postal code.
 * @param tipologia Number of rooms.
 * @param areaInterior Interior area.
 * @param piso Floor.
 */
Apartamento::Apartamento(string morada, string codigoPostal, int tipologia,
		float areaInterior, int piso) :
		Habitacao(morada, codigoPostal) {
	this->tipologia = tipologia;
	this->areaInterior = areaInterior;
	this->piso = piso;
}
/**
 * Constructor of an owned appartment.
 * @param morada House address.
 * @param codigoPostal House postal code.
 * @param proprietario Owner's NIF.
 * @param tipologia Number of rooms.
 * @param areaInterior Interior area.
 * @param piso Floor.
 */
Apartamento::Apartamento(string morada, string codigoPostal,
		string proprietario, int tipologia, float areaInterior, int piso) :
		Habitacao(morada, codigoPostal, proprietario) {
	this->tipologia = tipologia;
	this->areaInterior = areaInterior;
	this->piso = piso;
}
/**
 * Constructor of an owned apartment with rent.
 * @param morada House address.
 * @param codigoPostal House postal code.
 * @param proprietario Owner's NIF.
 * @param pago[12] Paid rent for each month.
 * @param tipologia Number of rooms.
 * @param areaInterior Interior area.
 * @param piso Floor.
 */
Apartamento::Apartamento(string morada, string codigoPostal,
		string proprietario, bool pago[12], int tipologia, float areaInterior,
		int piso) :
		Habitacao(morada, codigoPostal, proprietario, pago) {
	this->tipologia = tipologia;
	this->areaInterior = areaInterior;
	this->piso = piso;
}
/**
 * Complete constructor. This is only used to import house data.
 * @param id Apartment ID.
 * @param morada House address.
 * @param codigoPostal House postal code.
 * @param NIFProprietario Owner's NIF.
 * @param pago[12] Paid rent for each month.
 * @param idService Service ID (-1 = No service).
 * @param tipologia Number of rooms.
 * @param areaInterior Interior area.
 * @param piso Floor.
 */
Apartamento::Apartamento(int id, string morada, string codigoPostal,
		string proprietario, bool pago[12], int idServico, int tipologia,
		float areaInterior, int piso) :
		Habitacao(id, morada, codigoPostal, proprietario, pago, idServico) {
	this->tipologia = tipologia;
	this->areaInterior = areaInterior;
	this->piso = piso;
}

/**
 * Sets new interior area.
 * @param area New interior area.
 */
void Apartamento::setAreaInterior(float area) {
	this->areaInterior = area;
}
/**
 * Sets new number of rooms.
 * @param tipologia New number of rooms.
 */
void Apartamento::setTipologia(int tipologia) {
	this->tipologia = tipologia;
}
/**
 * Sets new floor.
 * @param piso New floor.
 */
void Apartamento::setPiso(int piso) {
	this->piso = piso;
}

/**
 * @return Number of rooms.
 */
int Apartamento::getTipologia() const {
	return tipologia;
}
/**
 * @return Interior area.
 */
float Apartamento::getAreaInterior() const {
	return areaInterior;
}
/**
 * @return Floor.
 */
int Apartamento::getPiso() const {
	return piso;
}

/**
 * @return Type of house. In this case = "Apartamento".
 */
string Apartamento::getTipo() const {
	string tipo = "Apartamento";
	return tipo;
}
/**
 * Calculates rent. Formula is 150 + 25 * number of rooms + 10 * floor.
 * @return Monthly rent.
 */
float Apartamento::calcRenda() const {
	return (150 + 25 * tipologia + 10 * piso);
}

/**
 * Displays apartment info.
 */
void Apartamento::info() const {
	cout << "Apartamento" << endl;
	cout << "NIF Proprietario = " << NIFProprietario << endl;
	cout << "Morada - " << morada + ", " + codigoPostal << endl;
	cout << "Tipologia: T" << tipologia << endl;
	cout << "Piso " << piso << endl;
	cout << "Renda = " << this->calcRenda() << "$\n" << endl;
}

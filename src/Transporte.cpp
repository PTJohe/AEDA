#include "../headers/Transporte.h"
#include "../headers/Condominio.h"

/**
 * Constructor of a new transport.
 * @param tipo Type of transport
 * @param destino Destination of transport
 * @param condo Condominium it is relative to
 */
Transporte::Transporte(string tipo, string destino, Posicao condo) {
	this->tipo = tipo;
	this->destino = destino;
	this->condo = condo;
}

/**
 * Changes the transport destination
 * @param dest New destination
 * @return void
 */
void Transporte::mudarDestino(string dest) {
	this->destino = dest;
}

/**
 * Adds a stop to the route of the transport
 * @param par stop to be added
 * @return void
 */
void Transporte::addParagem(Paragem par) {
	paragens.push(par);
}

/**
 * Removes a stop from the route of the transport
 * @param  stop to be removed
 * @return void
 */
void Transporte::removeParagem(Paragem toRemove) {
	vector<Paragem> temp;
	while (!paragens.empty()) {
		temp.push_back(paragens.top());
		paragens.pop();
	}
	int index = sequentialSearch(temp, toRemove);

	temp.erase(temp.begin() + index);

	while (!temp.empty()) {
		paragens.push(temp.back());
		temp.pop_back();
	}
}

/**
 * Gets the type of transport
 * @return tipo
 */
string Transporte::getTipo() const {
	return tipo;
}

/**
 * Gets the destination of the transport
 * @return destino
 */
string Transporte::getDestino() const {
	return destino;
}

/**
 * Gets the stops queue
 * @return paragens
 */
priority_queue<Paragem> Transporte::getParagens() const {
	return paragens;
}

/**
 * Sets a new destination.
 * @param destino New destination.
 */
void Transporte::setDestino(string destino) {
	this->destino = destino;
}

/**
 * Compares two transports by their distance to the condominium.
 * @param trans Transport to be compared.
 * @retval TRUE Transport has a "lower" distance than trans.
 * @retval FALSE Transport has an "equal or higher" distance than trans.
 */
bool Transporte::operator <(const Transporte &trans) const {
	if (this->paragens.empty() && !trans.paragens.empty()) {
		return true;
	} else if (!this->paragens.empty() && trans.paragens.empty())
		return false;

	int xc, yc;
	xc = this->condo.x;
	yc = this->condo.y;

	int xo, yo;
	xo = this->paragens.top().getPos().x;
	yo = this->paragens.top().getPos().y;
	float dist1 = sqrt(pow(xc - xo, 2) + pow(yc - yo, 2));

	int xa, ya;
	xa = trans.paragens.top().getPos().x;
	ya = trans.paragens.top().getPos().y;
	float dist2 = sqrt(pow(xc - xa, 2) + pow(yc - ya, 2));

	//Inverti o retorno para que na fila o mais distante
	//em rela��o ao condom�nio fique em �timo lugar e vice-versa
	if (dist1 < dist2)
		return false;
	else
		return true;
}
/**
 * Compares two transports by their type, destination and number of stops.
 * @param trans Transport to be compared.
 * @retval TRUE Equal type, destination and number of stops.
 * @retval FALSE Transports are different.
 */
bool Transporte::operator ==(const Transporte &trans) const {
	if (this->tipo == trans.getTipo() && this->destino == trans.getDestino()
			&& this->paragens.size() == trans.getParagens().size())
		return true;
	return false;
}
/**
 * Constructor of a new stop.
 * @param nome Name of the stop
 * @param pos Position of the stop
 * @param condo Condominium it is relative to
 */
Paragem::Paragem(string nome, Posicao pos, Posicao condo) {
	this->nome = nome;
	this->pos = pos;
	this->condo = condo;
}

/**
 * Gets the name of the stop
 * @return Name
 */
string Paragem::getNome() const {
	return this->nome;
}
/**
 * Gets the position of the stop
 * @return Position
 */
Posicao Paragem::getPos() const {
	return pos;
}
/**
 * Compares two stops by their distance to the condominium.
 * @param par Stop to be compared.
 * @retval TRUE Stop has a "lower" distance than par.
 * @retval FALSE Stop has an "equal or higher" distance than par.
 */
bool Paragem::operator <(const Paragem &par) const {
	int xc, yc;
	xc = this->condo.x;
	yc = this->condo.y;

	int xo, yo;
	xo = this->pos.x;
	yo = this->pos.y;
	float dist1 = sqrt(pow(xc - xo, 2) + pow(yc - yo, 2));

	int xa, ya;
	xa = par.pos.x;
	ya = par.pos.y;
	float dist2 = sqrt(pow(xc - xa, 2) + pow(yc - ya, 2));

	//Inverti o retorno para que na fila o mais distante
	//em rela��o ao condom�nio fique em �timo lugar e vice-versa
	if (dist1 < dist2)
		return false;
	else
		return true;
}
/**
 * Compares two stops by their name and position.
 * @param par Stop to be compared.
 * @retval TRUE Equal name and position.
 * @retval FALSE Stops are different.
 */
bool Paragem::operator ==(const Paragem &par) const {
	if (nome == par.nome && pos.x == par.pos.x && pos.y == par.pos.y)
		return true;
	else
		return false;
}
/**
 * @return Distance of stop to condominium.
 */
float Paragem::calcDistancia() const {
	int xc, yc;
	xc = this->condo.x;
	yc = this->condo.y;

	int xo, yo;
	xo = this->pos.x;
	yo = this->pos.y;
	float dist1 = sqrt(pow(xc - xo, 2) + pow(yc - yo, 2));

	return dist1;
}

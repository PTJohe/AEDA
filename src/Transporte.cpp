#include "../headers/Transporte.h"

/**
 * Constructor of a new transport.
 * @param tipo Type of transport
 * @param destino Destination of transport
 * @param condo Condominium it is relative to
 */
Transporte::Transporte(string tipo, string destino,Condominio * condo) {
	this->tipo = tipo;
	this->destino = destino;
	this->condo = condo;
}

/**
 * Adds a stop to the route of the transport
 * @param par stop to be added
 * @return void
 */
void Transporte::addParagem(Paragem par){
	paragens.push(par);
}

/**
 * Removes a stop from the route of the transport
 * @param  stop to be removed
 * @return void
 */
void Transporte::removeParagem(Paragem toRemove){
	vector<Paragem> temp;
	while(!paragens.empty()){
		temp.push_back(paragens.top());
		paragens.pop();
	}
	int index = sequentialSearch(temp,toRemove);

	temp.erase(temp.begin()+index);

	while(!temp.empty()){
		paragens.push(temp.back());
		temp.pop_back();
	}
}


bool Transporte::operator <(const Transporte &trans) const{
	int xc,yc;
	xc = this->condo->getLocalizacao().x;
	yc = this->condo->getLocalizacao().y;

	int xo,yo;
	xo = this->paragens.top().getPos().x;
	yo = this->paragens.top().getPos().y;
	float dist1 = sqrt(pow(xc-xo,2)+pow(yc-yo,2));

	int xa,ya;
	xa = trans.paragens.top().getPos().x;
	ya = trans.paragens.top().getPos().y;
	float dist2 = sqrt(pow(xc-xa,2)+pow(yc-ya,2));


	//Inverti o retorno para que na fila o mais distante
	//em relação ao condomínio fique em útimo lugar e vice-versa
	if(dist1 < dist2)
		return false;
	else
		return true;
}



/**
 * Constructor of a new stop.
 * @param nome Name of the stop
 * @param pos Position of the stop
 * @param condo Condominium it is relative to
 */
Paragem::Paragem(string nome,Posicao pos,Condominio * condo){
	this->nome = nome;
	this->pos = pos;
	this->condo = condo;
}

/**
 * Gets de position of the stop
 * @return Position
 */
Posicao Paragem::getPos()const{
	return pos;
}



bool Paragem::operator <(const Paragem &par) const{
	int xc,yc;
	xc = this->condo->getLocalizacao().x;
	yc = this->condo->getLocalizacao().y;

	int xo,yo;
	xo = this->pos.x;
	yo = this->pos.y;
	float dist1 = sqrt(pow(xc-xo,2)+pow(yc-yo,2));

	int xa,ya;
	xa = par.pos.x;
	ya = par.pos.y;
	float dist2 = sqrt(pow(xc-xa,2)+pow(yc-ya,2));


	//Inverti o retorno para que na fila o mais distante
	//em relação ao condomínio fique em útimo lugar e vice-versa
	if(dist1 < dist2)
		return false;
	else
		return true;
}

bool Paragem::operator ==(const Paragem &par) const{
	if(nome == par.nome &&
		pos.x == par.pos.x &&
		pos.y == par.pos.y)
		return true;
	else
		return false;
}

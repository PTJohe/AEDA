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
 * @param pos Position of the stop
 * @return void
 */
void Transporte::addParagem(Paragem par){
	paragens.push(par);
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



bool Paragem::operator <(const Paragem &par){
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

	if(dist1 < dist2)
		return true;
	else
		return false;
}

#include "../headers/Transporte.h"


/**
 * Constructor of a new transport.
 * @param tipo Type of transport
 * @param destino Destination of transport
 */
Transporte::Transporte(string tipo, string destino) {
	this->tipo = tipo;
	this->destino = destino;
}

/**
 * Adds a stop to the route of the transport
 * @param pos Position of the stop
 * @return void
 */
void Transporte::addPos(Posicao pos){
	paragens.push_back(pos);
}

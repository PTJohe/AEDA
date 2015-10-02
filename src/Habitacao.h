#ifndef SRC_HABITICAO_H_
#define SRC_HABITACAO_H_

#include "Header.h"

class Habitacao {
protected:
	string morada;
	string codigoPostal;
public:
	Habitacao(string morada, string codigoPostal){
		this->morada = morada;
		this->codigoPostal = codigoPostal;
	}
};

class Vivenda: public Habitacao {
private:
	float areaInterior;
	float areaExterior;
	bool piscina;
public:
	Vivenda(string morada, string codigoPostal, float areaInterior, float areaExterior, bool piscina):Habitacao(morada, codigoPostal){
		this->areaInterior = areaInterior;
		this->areaExterior = areaExterior;
		this->piscina = piscina;
	}
};

class Apartamento: public Habitacao {
private:
	string tipologia;
	float areaInterior;
	int piso;
public:
	Apartamento(string morada, string codigoPostal, string tipologia, float areaInterior, int piso):Habitacao(morada, codigoPostal){
		this->tipologia = tipologia;
		this->areaInterior = areaInterior;
		this->piso = piso;
	}
};

#endif

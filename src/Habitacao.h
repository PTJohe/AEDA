#ifndef SRC_HABITICAO_H_
#define SRC_HABITACAO_H_

#include "Header.h"

class Habitacao {
protected:
	string morada;
	string codigoPostal;
public:
	virtual ~Habitacao(){};
	Habitacao(string morada, string codigoPostal){
		this->morada = morada;
		this->codigoPostal = codigoPostal;
	}
	virtual float calcRenda() const = 0;
	virtual void info() const = 0;
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
	float calcRenda() const;
	void info() const;
};

class Apartamento: public Habitacao {
private:
	int tipologia;
	float areaInterior;
	int piso;
public:
	Apartamento(string morada, string codigoPostal, int tipologia, float areaInterior, int piso):Habitacao(morada, codigoPostal){
		this->tipologia = tipologia;
		this->areaInterior = areaInterior;
		this->piso = piso;
	}
	float calcRenda() const;
	void info() const;
};

#endif

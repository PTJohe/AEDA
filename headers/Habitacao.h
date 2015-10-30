#ifndef HEADERS_HABITICAO_H_
#define HEADERS_HABITACAO_H_

#include "../headers/Header.h"

class Condomino;

class Habitacao {
protected:
	string morada;
	string codigoPostal;
	Condomino* proprietario;
public:
	virtual ~Habitacao() {
	}
	;
	Habitacao(string morada, string codigoPostal);
	virtual float calcRenda() const = 0;
	virtual void info() const = 0;
	bool operator ==(const Habitacao* h1) const;
	bool operator <(const Habitacao* h1) const;
};

class Vivenda: public Habitacao {
private:
	float areaInterior;
	float areaExterior;
	bool piscina;
public:
	Vivenda(string morada, string codigoPostal, float areaInterior,
			float areaExterior, bool piscina);
	float calcRenda() const;
	void info() const;
};

class Apartamento: public Habitacao {
private:
	int tipologia;
	float areaInterior;
	int piso;
public:
	Apartamento(string morada, string codigoPostal, int tipologia,
			float areaInterior, int piso);
	float calcRenda() const;
	void info() const;
};

#endif

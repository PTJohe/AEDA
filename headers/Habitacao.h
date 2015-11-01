#ifndef HEADERS_HABITICAO_H_
#define HEADERS_HABITACAO_H_

#include "../headers/Header.h"

class Condomino;

class Habitacao {
protected:
	string morada;
	string codigoPostal;
	string NIFProprietario;
	bool pago[12];
public:
	virtual ~Habitacao() {};
	Habitacao(string morada, string codigoPostal, string NIFProprietario);
	Habitacao(string morada, string codigoPostal, string NIFProprietario,
			bool pago[12]);
	string getMorada() const;
	string getCodigoPostal() const;
	string getNIFProprietario() const;
	bool getPago(int mes) const;

	void setMorada(string morada);
	void setCodigoPostal(string codigoPostal);
	void setProprietario(string nif);
	void setPago(int mes);

	virtual float calcRenda() const = 0;
	virtual string getTipo() const = 0;
	virtual float getAreaInterior() const = 0;
	virtual float getAreaExterior() const = 0;
	virtual bool getPiscina() const = 0;
	virtual int getTipologia() const = 0;
	virtual int getPiso() const = 0;
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
	Vivenda(string morada, string codigoPostal, string proprietario,
			float areaInterior, float areaExterior, bool piscina);
	Vivenda(string morada, string codigoPostal, string NIFProprietario,
			bool pago[12], float areaInterior, float areaExterior,
			bool piscina);
	float getAreaInterior() const;
	float getAreaExterior() const;
	bool getPiscina() const;

	int getTipologia() const {return 0;}
	int getPiso() const {return 0;}

	float calcRenda() const;
	string getTipo() const;
	void info() const;
};

class Apartamento: public Habitacao {
private:
	int tipologia;
	float areaInterior;
	int piso;
public:
	Apartamento(string morada, string codigoPostal, string NIFProprietario,
			int tipologia, float areaInterior, int piso);
	Apartamento(string morada, string codigoPostal, string NIFProprietario,
			bool pago[12], int tipologia, float areaInterior, int piso);
	int getTipologia() const;
	float getAreaInterior() const;
	int getPiso() const;

	float getAreaExterior() const {return 0;}
	bool getPiscina() const {return false;}

	float calcRenda() const;
	string getTipo() const;
	void info() const;
};

#endif

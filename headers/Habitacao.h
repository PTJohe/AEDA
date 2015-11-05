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
	int idServico;

public:
	virtual ~Habitacao() {
	}
	;
	Habitacao(string morada, string codigoPostal);
	Habitacao(string morada, string codigoPostal, string NIFProprietario);
	Habitacao(string morada, string codigoPostal, string NIFProprietario,
			bool pago[12]);
	string getMorada() const;
	string getCodigoPostal() const;
	string getNIFProprietario() const;
	bool hasProprietario() const;
	bool getPago(int mes) const;
	int getServico() const;

	void setMorada(string morada);
	void setCodigoPostal(string codigoPostal);
	void setProprietario(string nif);
	void setPago(int mes);
	void resetPago();
	void setServico(int id);

	virtual void setAreaInterior(float area) = 0;
	virtual void setAreaExterior(float area) = 0;
	virtual void setPiscina(bool piscina) = 0;
	virtual void setTipologia(int tipologia) = 0;
	virtual void setPiso(int piso) = 0;

	virtual float calcRenda() const = 0;
	virtual string getTipo() const = 0;
	virtual float getAreaInterior() const = 0;
	virtual float getAreaExterior() const = 0;
	virtual bool getPiscina() const = 0;
	virtual int getTipologia() const = 0;
	virtual int getPiso() const = 0;
	virtual void info() const = 0;
};

class Vivenda: public Habitacao {
private:
	float areaInterior;
	float areaExterior;
	bool piscina;
public:
	~Vivenda() {
	}
	Vivenda(string morada, string codigoPostal, float areaInterior,
			float areaExterior, bool piscina);
	Vivenda(string morada, string codigoPostal, string proprietario,
			float areaInterior, float areaExterior, bool piscina);
	Vivenda(string morada, string codigoPostal, string NIFProprietario,
			bool pago[12], float areaInterior, float areaExterior,
			bool piscina);
	float getAreaInterior() const;
	float getAreaExterior() const;
	bool getPiscina() const;

	void setAreaInterior(float area);
	void setAreaExterior(float area);
	void setPiscina(bool piscina);

	int getTipologia() const {
		return -1;
	}
	int getPiso() const {
		return -1;
	}
	void setTipologia(int tipologia) {
	}
	void setPiso(int piso) {
	}

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
	~Apartamento() {
	}
	Apartamento(string morada, string codigoPostal, int tipologia,
			float areaInterior, int piso);
	Apartamento(string morada, string codigoPostal, string NIFProprietario,
			int tipologia, float areaInterior, int piso);
	Apartamento(string morada, string codigoPostal, string NIFProprietario,
			bool pago[12], int tipologia, float areaInterior, int piso);
	int getTipologia() const;
	float getAreaInterior() const;
	int getPiso() const;

	void setAreaInterior(float area);
	void setTipologia(int tipologia);
	void setPiso(int piso);

	float getAreaExterior() const {
		return 0;
	}
	bool getPiscina() const {
		return false;
	}
	void setAreaExterior(float area) {return;}
	void setPiscina(bool piscina) {return;}

	float calcRenda() const;
	string getTipo() const;
	void info() const;

};

#endif

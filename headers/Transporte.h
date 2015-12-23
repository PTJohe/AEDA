#ifndef HEADERS_TRANSPORTE_H_
#define HEADERS_TRANSPORTE_H_

#include "../headers/Header.h"

class Condominio;


class Paragem {
private:
	string nome;
	Posicao pos;
	Condominio * condo;

public:
	Paragem(string nome,Posicao pos,Condominio * condo);

	string getNome() const;
	Posicao getPos() const;

	bool operator <(const Paragem &par) const;
	bool operator ==(const Paragem &trans) const;
};

class Transporte {
private:
	string tipo;
	string destino;
	priority_queue<Paragem> paragens;
	Condominio * condo;

public:
	Transporte(string tipo, string destino, Condominio * condo);

	void mudarDestino(string dest);
	void addParagem(Paragem par);
	void removeParagem(Paragem toRemove);

	string getTipo() const;
	string getDestino() const;
	priority_queue<Paragem> getParagens() const;

	bool operator <(const Transporte &trans) const;

};





#endif /* HEADERS_TRANSPORTE_H_ */

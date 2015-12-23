#ifndef HEADERS_TRANSPORTE_H_
#define HEADERS_TRANSPORTE_H_

#include "../headers/Header.h"

class Transporte {
private:
	string tipo;
	string destino;
	Posicao mais_proxima;
	vector<Posicao> paragens;

public:
	Transporte(string tipo, string destino);

	void addPos(Posicao pos);


};



#endif /* HEADERS_TRANSPORTE_H_ */

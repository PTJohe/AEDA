#ifndef HEADERS_CONDOMINIO_H_
#define HEADERS_CONDOMINIO_H_

#include "../headers/Condomino.h"
#include "../headers/Header.h"

class Condomino;
class Servico;

class Condominio{
private:
	int numFuncionarios;
	float fundos;
	vector <Condomino *> moradores;
	vector <Habitacao *> propriedades;
	vector <Servico *> servicosTerminados;
	vector <Servico *> servicosEmCurso;
	vector <Servico *> servicosEmEspera;
	int currentMes;

public:
	Condominio();
	vector <Condomino*> getMoradores();
	vector <Habitacao*> getPropriedades();
	void setMoradores(vector<Condomino*> moradores);
	void setPropriedades(vector<Habitacao*> propriedades);

	void fimDoMes();
	bool contratarFuncionarios(); //TODO contratarFuncionarios();
};

#endif

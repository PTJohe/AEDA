#ifndef HEADERS_CONDOMINIO_H_
#define HEADERS_CONDOMINIO_H_

#include "../headers/Condomino.h"
#include "../headers/Servico.h"
#include "../headers/Header.h"

class Condomino;

class Condominio {
private:
	long int fundos;
	vector<Condomino> moradores;
	vector<Habitacao*> habitacoes;
	vector<Funcionario> funcionarios;
	vector<Servico> servicosTerminados;
	vector<Servico> servicosEmCurso;
	vector<Servico> servicosEmEspera;
	int currentMes;

public:
	Condominio();
	long int getFundos() const;
	int getMes() const;
	vector<Condomino> getMoradores();
	vector<Habitacao*> getHabitacoes();
	void setFundos(long int fundos);
	void setCurrentMes(int currentMes);
	void setMoradores(vector<Condomino> moradores);
	void setHabitacoes(vector<Habitacao*> habitacoes);

	void sortMoradores();
	int addMorador(Condomino condomino);
	int eraseMorador(Condomino condomino);

	bool saldarDivida(Condomino condomino);

	int addHabitacao(Habitacao* h1);

	bool updateHabitacoesCondominos();

	void fimDoMes();
	bool contratarFuncionarios(); //TODO contratarFuncionarios();

	void infoMoradores() const;
	void infoHabitacoes() const;
};

#endif

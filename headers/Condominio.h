#ifndef HEADERS_CONDOMINIO_H_
#define HEADERS_CONDOMINIO_H_

#include "../headers/Condomino.h"
#include "../headers/Servico.h"
#include "../headers/Header.h"

class Condomino;

class Condominio {
private:
	float fundos;
	vector<Condomino> moradores;
	vector<Habitacao*> habitacoes;
	vector<Funcionario> funcionarios;
	vector<Servico> servicosTerminados;
	vector<Servico> servicosEmCurso;
	vector<Servico> servicosEmEspera;
	int currentMes;

public:
	Condominio();
	int getMes() const;
	vector<Condomino> getMoradores();
	vector<Habitacao*> getHabitacoes();
	void setMoradores(vector<Condomino> moradores);
	void setHabitacoes(vector<Habitacao*> habitacoes);

	int addMorador(Condomino condomino);
	bool eraseMorador(string nifMorador);

	int addHabitacao(Habitacao* h1);

	bool updateHabitacoesCondominos();

	void fimDoMes();
	bool contratarFuncionarios(); //TODO contratarFuncionarios();

	void infoMoradores() const;
	void infoHabitacoes() const;
};

#endif

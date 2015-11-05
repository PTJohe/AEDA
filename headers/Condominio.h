#ifndef HEADERS_CONDOMINIO_H_
#define HEADERS_CONDOMINIO_H_

#include "../headers/Header.h"
#include "../headers/Condomino.h"
#include "../headers/Servico.h"
#include "../headers/Funcionario.h"

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
	vector<Funcionario> getFuncionarios();
	Condomino* getCondomino(int pos);

	void setFundos(long int fundos);
	void setCurrentMes(int currentMes);
	void setMoradores(vector<Condomino> moradores);
	void setHabitacoes(vector<Habitacao*> habitacoes);
	void setFuncionarios(vector<Funcionario> funcionarios);


	void sortMoradores(int sort);
	int addMorador(Condomino condomino);
	int eraseMorador(Condomino condomino);

	void sortHabitacoes(int sort);
	int findHabitacao(vector<Habitacao*> habitacoes, Habitacao* habitacao);
	bool addHabitacao(Habitacao* h1);
	bool eraseHabitacao(int pos);
	bool eraseHabitacaoPossuida(Condomino condomino, int pos);


	//Funcoes Condomino
	bool setNomeUtilizador(Condomino condomino, string nomeUtilizador);
	bool setPassword(Condomino condomino, string password);
	bool setAdmin(Condomino condomino, bool admin);
	bool setNomeCivil(Condomino condomino, string nomeCivil);
	bool setNIF(Condomino condomino, string NIF);
	bool setFundosMensais(Condomino condomino, long int fundos);
	bool saldarDivida(Condomino condomino);

	//Funcoes Habitacao
	bool updateHabitacoesCondominos();

	//Funcoes Funcionario

	void sortFuncionarios(int sortOption);
	bool addFuncionario(Funcionario funcionario);
	int eraseFuncionario(int idFuncionario);

	//Funcoes Servico
	bool addServico(Servico servico);

	vector<Condomino> fimDoMes();

	void infoMoradores() const;
	void infoHabitacoes() const;
};

bool compCondominoNomeCivil(Condomino c1, Condomino c2);
bool compCondominoNIF(Condomino c1, Condomino c2);
bool compFuncionarioEspecialidade(Funcionario f1, Funcionario f2);
bool compFuncionarioOcupacao(Funcionario f1, Funcionario f2);

#endif

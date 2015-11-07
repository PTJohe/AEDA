#ifndef HEADERS_SERVICO_H_
#define HEADERS_SERVICO_H_

#include "../headers/Header.h"

class Servico {
private:
	int id; //ID unico de cada servico
	string especialidade; //Limpeza, Canalizacao ou Pintura
	float duracao; //Valor retornado em segundos. Limpeza = 2 min, Canalizacao = 5 min, Pintura = 10 min;
	string mesRequisitado;
	time_t dataRequisitado; //Em segundos desde epoch
	string mesInicio;
	time_t dataInicio; //Em segundos desde epoch
	time_t dataFim; //Em segundos desde epoch
	int idFuncionario;
	string NIFcondomino;

public:
	Servico(string especialidade, string NIFcondomino, string mesRequisitado, time_t dataRequisitado);
	Servico(string especialidade, string NIFcondomino, string mesRequisitado, time_t dataRequisitado, string mesActual, int idFuncionario);
	Servico(int id, string especialidade, string NIFcondomino, string mesRequisitado, time_t dataRequisitado, string mesInicio, time_t dataInicio, int idFuncionario);

	string getEspecialidade() const;
	int getID() const;
	string getMesRequisitado() const;
	time_t getDataRequisitado() const;
	string getMesInicio() const;
	time_t getDataInicio() const;
	float getDuracao() const;
	time_t getDataFim() const;
	int getIDFuncionario() const;
	string getNIFcondomino() const;

	void setEspecialidade(string especialidade);
	void setDuracao(float duracao);
	void setIDFuncionario(int idFuncionario);

	void iniciarServico(string mes, int idFuncionario);
	void iniciarServico(string mes, int idFuncionario, time_t dataInicio);

	bool operator< (const Servico s1) const;

	void info() const;

};

#endif

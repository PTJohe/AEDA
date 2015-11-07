#ifndef HEADERS_SERVICO_H_
#define HEADERS_SERVICO_H_

#include "../headers/Header.h"

class Servico {
private:
	string especialidade; //Limpeza, Canalizacao ou Pintura
	int id; //ID unico de cada servico
	float duracao; //Valor retornado em segundos. Limpeza = 2 min, Canalizacao = 5 min, Pintura = 10 min;
	string mes;
	time_t dataInicio; //Em segundos desde epoch
	time_t dataFim; //Em segundos desde epoch
	int idFuncionario;
	string NIFcondomino;

public:
	Servico(string especialidade, string NIFcondomino);
	Servico(string especialidade, string NIFcondomino, string mes, int idFuncionario);
	Servico(int id, string especialidade, string NIFcondomino, string mes, time_t dataInicio, int idFuncionario);

	string getEspecialidade() const;
	int getID() const;
	string getMes() const;
	time_t getDataInicio() const;
	float getDuracao() const;
	int getIDFuncionario() const;
	string getNIFcondomino() const;

	void setEspecialidade(string especialidade);
	void setDataInicio() const;
	void setDuracao(float duracao);
	void setIDFuncionario(int idFuncionario);

	void iniciarServico(string mes, int idFuncionario);

	bool operator< (const Servico s1) const;

	void info() const;

};

#endif

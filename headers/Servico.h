#ifndef HEADERS_SERVICO_H_
#define HEADERS_SERVICO_H_

#include "../headers/Header.h"

class Servico {
private:
	string especialidade; //Limpeza, Canalizacao ou Pintura
	int id; //ID unico de cada servico
	float duracao; //Valor retornado em segundos. Limpeza = 2 min, Canalizacao = 5 min, Pintura = 10 min;
	time_t dataInicio; //Em segundos desde epoch
	time_t dataFim; //Em segundos desde epoch
	int idFuncionario;

public:
	Servico(string especialidade);
	Servico(string especialidade, int idFuncionario);

	string getEspecialidade() const;
	int getID() const;
	time_t getDataInicio() const;
	float getDuracao() const;
	int getIDFuncionario() const;

	void setEspecialidade(string especialidade);
	void setDataInicio() const;
	void setDuracao(float duracao);
	void setIDFuncionario(int idFuncionario);

	void info() const;
};

#endif

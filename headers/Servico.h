#ifndef HEADERS_SERVICO_H_
#define HEADERS_SERVICO_H_

#include "../headers/Header.h"

class Servico {
private:
	string especialidade;
	int id; //id unico de cada servico
	float duracao; //em horas
	float preco; //em dolares
	int idFuncionario;

public:
	Servico(string especialidade,float duracao, float preco, int idFuncionario);

	string getEspecialidade() const;
	int getID() const;
	float getDuracao() const;
	float getPreco() const;
	int getIDFuncionario() const;

	void setEspecialidade(string especialidade);
	void setDuracao(float duracao);
	void setPreco(float preco);
	void setIDFuncionario(int idFuncionario);

	//class faltaPessoal{ }; //TODO isto tem que ir para a class Condominio, não aqui
};

#endif

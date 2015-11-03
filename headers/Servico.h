#ifndef HEADERS_SERVICO_H_
#define HEADERS_SERVICO_H_

#include "../headers/Header.h"
#include "../headers/Funcionario.h"

class Servico {
private:
	string nome;
	static int id; //id unico de cada servico
	float duracao; //em horas
	int numFuncionarios; //numero de funcionários necessários para a realização do serviço
	vector<Funcionario> funcionarios;
	float preco; //em dolares

public:
	Servico(string nome,float duracao,int numFuncionarios,Condominio &condo, float preco, string especialidade);

	string getNome(){return nome;}
	float getDuracao(){return duracao;}
	vector<Funcionario> getFuncionarios(){return funcionarios;}

	class faltaPessoal{ }; //excepção
};

#endif

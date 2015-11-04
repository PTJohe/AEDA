#include "../headers/Servico.h"

static int nextId = 1;

Servico::Servico(string especialidade, float duracao, float preco, int idFuncionario) {
	this->especialidade = especialidade;
	this->id = nextId;
	this->duracao = duracao;
	this->preco = preco;
	this->idFuncionario = idFuncionario;
	nextId++;
}


string Servico::getEspecialidade() const{
	return especialidade;
}
int Servico::getID() const{
	return id;
}
float Servico::getDuracao() const{
	return duracao;
}
float Servico::getPreco() const{
	return preco;
}
int Servico::getIDFuncionario() const{
	return idFuncionario;
}


void Servico::setEspecialidade(string especialidade){
	this->especialidade = especialidade;
}
void Servico::setDuracao(float duracao){
	this->duracao = duracao;
}
void Servico::setPreco(float preco){
	this->preco = preco;
}
void Servico::setIDFuncionario(int idFuncionario){
	this->idFuncionario = idFuncionario;
}

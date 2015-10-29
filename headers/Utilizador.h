#ifndef HEADERS_UTILIZADOR_H_
#define HEADERS_UTILIZADOR_H_

#include "../headers/Header.h"
#include "../headers/Condomino.h"

class Utilizador {
private:
	string nomeUtilizador;
	string password;
	bool admin;
	Condomino* dados;
public:
	Utilizador(string nomeUtilizador);
	Utilizador(string nomeUtilizador, string password);
	Utilizador(string nomeUtilizador, string password, bool admin);
	Utilizador(string nomeUtilizador, string password, bool admin, Condomino* dados);

	string getNomeUtilizador() const;
	string getPassword() const;
	Condomino* getDados() const;
	bool isAdmin() const;

	void setNomeUtilizador(string novoNome);
	void setPassword(string novaPassword);
	void setDados(Condomino* dados);
	void setAdmin();

	bool validPassword(string password);
	bool hasDados() const;
	bool operator < (const Utilizador u1) const;
	bool operator == (const Utilizador u1) const;
};

#endif

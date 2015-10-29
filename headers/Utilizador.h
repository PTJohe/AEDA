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
	Utilizador(string nomeUtilizador, string password);
	Utilizador(string nomeUtilizador, string password, bool admin);
	Utilizador(string nomeUtilizador, string password, bool admin, Condomino* dados);

	string getNomeUtilizador() const;
	Condomino* getDados() const;
	void setAdmin();
	bool setDados(Condomino* dados);
	bool validPassword(string password);
	bool isAdmin() const;
	bool operator < (const Utilizador u1) const;
	bool operator == (const Utilizador u1) const;
};

#endif

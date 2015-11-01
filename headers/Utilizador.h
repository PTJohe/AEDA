#ifndef HEADERS_UTILIZADOR_H_
#define HEADERS_UTILIZADOR_H_

#include "../headers/Condomino.h"

class Utilizador {
private:
	string nomeUtilizador;
	string password;
	bool admin;
	string nifCondomino;
public:
	Utilizador(string nomeUtilizador);
	Utilizador(string nomeUtilizador, string password);
	Utilizador(string nomeUtilizador, string password, bool admin);
	Utilizador(string nomeUtilizador, string password, bool admin, string nifCondomino);

	string getNomeUtilizador() const;
	string getPassword() const;
	string getNIFCondomino() ;
	bool isAdmin() const;

	void setNomeUtilizador(string novoNome);
	void setPassword(string novaPassword);
	void setNIFCondomino(string nif);
	void setAdmin(bool admin);

	bool validPassword(string password);
	bool hasDados() const;
	bool operator < (const Utilizador u1) const;
	bool operator == (const Utilizador u1) const;

	void info() const;
};

#endif

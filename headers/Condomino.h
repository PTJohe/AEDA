#ifndef HEADERS_CONDOMINO_H_
#define HEADERS_CONDOMINO_H_

#include "../headers/Header.h"
#include "../headers/Habitacao.h"

class Condomino {
private:
	string nomeUtilizador;
	string password;
	bool admin;
	string nomeCivil;
	string NIF;
	long int fundosMensais;
	long int divida;
	vector<Habitacao *> habitacoes;
public:
	Condomino(string nomeUtilizador, string password);
	Condomino(string nomeUtilizador, string password, string nomeCivil,
			string NIF);
	Condomino(string nomeUtilizador, string password, bool admin,
			string nomeCivil, string NIF, long int fundosMensais,
			long int divida);

	string getNomeUtilizador() const;
	string getPassword() const;
	bool isAdmin() const;

	string getNomeCivil() const;
	string getNIF() const;
	int getFundosMensais() const;
	int getDivida() const;
	vector<Habitacao *> getHabitacoes();

	void sortHabitacoes();
	bool addHabitacao(Habitacao* h1);
	bool eraseHabitacao(int pos);

	void setNomeUtilizador(string novoNomeUtilizador);
	void setPassword(string novaPassword);
	void setAdmin(bool admin);
	void setNomeCivil(string novoNomeCivil);
	void setNIF(string novoNIF);
	void setFundosMensais(long int novosFundos);
	void setDivida(long int novaDivida);
	void setHabitacoes(vector<Habitacao*> propriedades);

	bool validPassword(string password);
	bool hasDados() const;
	bool operator==(const Condomino c1) const;
	bool operator<(const Condomino c1) const;

	void requisitarLimpeza(); //TODO requisitarLimpeza()
	void requisitarCanalizacao(); //TODO requisitarCanalizacao()
	void requisitarPintura(); //TODO requisitarPintura()

	void infoConta() const;
	void infoCondomino() const;
	void infoHabitacoes() const;
	void infoRenda() const;
};

bool compHabitacao(Habitacao* h1, Habitacao* h2);

#endif

#ifndef HEADERS_MAIN_H_
#define HEADERS_MAIN_H_

#include "../headers/Header.h"
#include "../headers/Utilizador.h"
#include "../headers/Condominio.h"

class Main {
private:
	vector<vector<string> > menu;
	int option;
	vector<Utilizador> utilizadores;
	Condominio condominio;
	Utilizador* currentUser;

public:
	Main(){
		this->option = 0;
		this->currentUser = NULL;
	} //default constructor

	void displayTime();

	bool importCondominos();
	bool exportCondominos();
	bool importHabitacoes();
	bool exportHabitacoes();
	bool importUtilizadores();
	bool exportUtilizadores();
	int exitFunction();

	void setMenus(vector<vector<string> > menu);
	void setUtilizadores(vector<Utilizador> utilizadores);

	//Menu functions
	int menuInicial();
	int menuLogin();
	int menuRegisto();
	int menuUtilizador();
	int menuAdministrador();
	int menuEditDadosConta();
	int menuEditDadosCondomino();
	int menuPropriedadesAdquiridas();

	void resetOption();

	bool displayMenuOptions(int position);
	void displayAllUsers() const;
	void displayAllCondominos() const;
	void displayAllProperties() const;

	void displayCurrentUser() const;
	void displayCurrentUserProperties() const;
	void displayCurrentUserRent() const;

	bool editDadosConta(int option);
	bool editDadosCondomino(int option);

	bool validLogin(string utilizador, string password);
	bool validRegister(string utilizador, string password);

	bool addUtilizador(Utilizador utilizador);
	bool eraseUtilizador(string nomeUtilizador);
};

void displayLogo();
const string currentTime();
void pressEnterToContinue();
void createMesesAno();
void createMenuOptions();
bool hasWhitespace(string s);

int main();

#endif

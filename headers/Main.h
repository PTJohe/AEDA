#ifndef HEADERS_MAIN_H_
#define HEADERS_MAIN_H_

#include "../headers/Header.h"
#include "../headers/Utilizador.h"
#include "../headers/Condominio.h"

class Main {
private:
	vector<vector<string> > menu;
	int option = 0;
	vector<Utilizador> utilizadores;
	Condominio condominio;
	Utilizador* currentUser = NULL;

public:
	Main(){} //default constructor

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
	int menuEditDadosConta();
	int menuEditDadosCondomino();

	void resetOption();
	int displayMenuOptions(int position);
	void displayUsers() const;
	void displayCurrentUser() const;
	bool editDadosConta(int option);
	bool editDadosCondomino(int option);
	bool validLogin(string utilizador, string password);
	bool validRegister(string utilizador, string password);
	bool addUtilizador(Utilizador utilizador);
	bool eraseUtilizador(string nomeUtilizador);
};

const string currentDateTime();
void displayTime();
void pressEnterToContinue();
vector<vector<string> > createMenuOptions();
vector<Utilizador> createUtilizadores();
bool hasWhitespace(string s);
int main();

#endif /* HEADERS_MAIN_H_ */

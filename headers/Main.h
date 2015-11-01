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
	Main() {
		this->option = 0;
		this->currentUser = NULL;
	} //default constructor

	void displayTime();

	void setMenus(vector<vector<string> > menu);
	void setUtilizadores(vector<Utilizador> utilizadores);

	bool addUtilizador(Utilizador utilizador);
	bool eraseUtilizador(string nomeUtilizador);

	void resetOption();
	bool displayYesNo();
	bool displayMenuOptions(int position);
	bool displaySelectUtilizador();
	bool displaySelectCondomino(); //TODO displaySelectCondomino()
	bool displaySelectHabitacao(); //TODO displaySelectHabitacao()
	bool displaySelectFuncionario(); //TODO displaySelectFuncionario()
	bool displaySelectServico(); //TODO displaySelectServico()

	bool validLogin(string utilizador, string password);
	bool validRegister(string utilizador, string password);


	bool editDadosConta(int option);
	bool editDadosContaAdmin(int option, Utilizador* utilizador);
	bool editDadosCondomino(int option, Condomino* condomino);

	void displayCurrentUserInfo() const;
	void displayCurrentUserHabitacoes() const;
	void displayCurrentUserRenda() const;

	void displayAllUtilizadores() const;
	void displayAllCondominos() const;
	void displayAllHabitacoes() const;
	void displayAllFuncionarios() const; //TODO displayAllFuncionarios()
	void displayAllServicos() const; //TODO displayAllServicos()

	//Menu Functions
	int menuInicial();

	int menuLogin();
	int menuRegisto();

	//Menu Utilizador
	int menuUtilizador();

	int menuEditDadosConta(Utilizador* utilizador);
	int menuEditDadosCondomino(Condomino* condomino);
	int menuHabitacoesPossuidas();
	int menuRequisitarServico();

	//Menu Administrador
	int menuAdministrador();

	int menuGerirUtilizadores();
	int menuSelectUtilizador(bool editar);
	int menuEditUtilizador(Utilizador* utilizador);
	int menuDeleteUtilizador(Utilizador * utilizador);

	int menuGerirCondominos(); //TODO menuGerirCondominos()
	int menuGerirHabitacoes(); //TODO menuGerirHabitacoes()
	int menuGerirFuncionarios(); //TODO menuGerirFuncionarios()
	int menuGerirServicos(); //TODO menuGerirServicos()

	//Import & extract functions
	bool importCondominos();
	bool exportCondominos();

	bool importHabitacoes();
	bool exportHabitacoes();

	bool importUtilizadores();
	bool exportUtilizadores();

	int exitFunction();

};

bool hasWhitespace(string s);
bool isNumber(string s);
bool isName(string s);

void displayLogo();
const string currentTime();
void pressEnterToContinue();

void createMesesAno();
void createMenuOptions();

int main();

#endif

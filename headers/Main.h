#ifndef HEADERS_MAIN_H_
#define HEADERS_MAIN_H_

#include "../headers/Header.h"
#include "../headers/Condominio.h"

class Main {
private:
	vector<vector<string> > menu;
	int option;
	Condominio condominio;
	Condomino* currentUser;

public:
	Main() {
		this->option = 0;
		this->currentUser = NULL;
	} //default constructor

	void displayTime();

	void setMenus(vector<vector<string> > menu);
	void setCurrentUser(Condomino condomino);

	void resetOption();
	bool displayYesNo(int option);
	bool displayMenuOptions(int position);
	bool displaySelectUtilizador();
	bool displaySelectCondomino();
	bool displaySelectHabitacao();
	bool displaySelectHabitacaoPossuida();
	bool displaySelectFuncionario(); //TODO displaySelectFuncionario()
	bool displaySelectServico(); //TODO displaySelectServico()

	bool validLogin(string utilizador, string password);
	bool validRegister(string utilizador, string password);

	bool editDadosConta(int editOption);
	bool editDadosContaAdmin(int editOption, Condomino &condomino);
	bool editDadosCondomino(int editOption);
	bool editDadosCondominoAdmin(int editOption, Condomino &condomino);

	void displayCurrentUserInfoConta();
	void displayCurrentUserInfoCondomino();
	void displayCurrentUserHabitacao(int pos);
	void displayCurrentUserRenda();

	void displayCondominoInfo(int pos);
	void displayHabitacaoInfo(int pos);
	void displayAllHabitacoes();
	void displayAllFuncionarios() const; //TODO displayAllFuncionarios()
	void displayAllServicos() const; //TODO displayAllServicos()

	//Menu Functions
	int menuInicial();

	int menuLogin();
	int menuRegisto();

	//Menu Utilizador
	int menuUtilizador();

	int menuEditDadosConta(Condomino &condomino);
	int menuEditDadosCondomino(Condomino &condomino);
	int menuHabitacoesPossuidas();
	int menuSelectHabitacoesPossuida(bool remover);
	int menuEditDadosHabitacaoPossuida(Condomino condomino);
	int menuDeleteHabitacaoPossuida(int pos, int menuOption);
	int menuAdicionarHabitacao();
	int menuRequisitarServico();

	//Menu Administrador
	int menuAdministrador();

	int menuGerirCondominos();
	int menuDisplayAllCondominos();
	int menuSelectCondomino(bool editar);
	int menuEditCondomino(Condomino &condomino);
	int menuDeleteCondomino(Condomino &condomino, int menuOption);

	int menuGerirHabitacoes();
	int menuDisplayAllHabitacoes();
	int menuSelectHabitacao(bool editar);
	int menuEditHabitacao(Habitacao* habitacao);
	int menuDeleteHabitacao(Habitacao* habitacao);

	int menuGerirFuncionarios(); //TODO menuGerirFuncionarios()
	int menuGerirServicos(); //TODO menuGerirServicos()

	//Import & extract functions
	bool importCondominio();
	bool exportCondominio();

	bool importCondominos();
	bool exportCondominos();

	bool importHabitacoes();
	bool exportHabitacoes();

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

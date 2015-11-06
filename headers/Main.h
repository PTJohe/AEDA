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
	bool displayVivendaApartamento(int option);
	bool displayMenuOptions(int position);

	bool displaySelectCondomino();
	bool displaySelectHabitacao(vector<Habitacao*> habitacoes);
	bool displaySelectHabitacaoPossuida();
	bool displaySelectFuncionario();
	bool displaySelectServico(); //TODO displaySelectServico()

	bool validLogin(string utilizador, string password);
	bool validRegister(string utilizador, string password);

	bool editDadosConta(int editOption);
	bool editDadosContaAdmin(int editOption, Condomino &condomino);
	bool editDadosCondomino(int editOption);
	bool editDadosCondominoAdmin(int editOption, Condomino &condomino);
	bool editHabitacao(int editOption, Habitacao* h1);

	void displayCurrentUserInfoConta();
	void displayCurrentUserInfoCondomino();
	void displayCurrentUserHabitacao(int pos);
	void displayCurrentUserRenda();

	void displayCondominoInfo(int pos);
	void displayHabitacaoInfo(int pos);
	void displayFuncionarioInfo(int pos);

	bool fimDoMes();

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
	int menuDeleteHabitacaoPossuida(int pos, int menuOption);
	int menuSelectOrNewHabitacao();
	int menuSelectHabitacaoAdd(vector<Habitacao*> habitacoes);
	int menuAddHabitacao(Condomino condomino);
	int menuConfirmAddHabitacao(Condomino condomino, Habitacao* h1);

	int menuRequisitarServico();


	//Menu Administrador
	int menuAdministrador();

	int menuGerirCondominos();
	int menuDisplayCondominosBy();
	int menuDisplayAllCondominos();
	int menuSelectCondomino(bool remover);
	int menuEditCondomino(Condomino &condomino);
	int menuDeleteCondomino(Condomino &condomino, int menuOption);

	int menuGerirHabitacoes();
	int menuDisplayHabitacoesBy();
	int menuDisplayAllHabitacoes();
	int menuSelectHabitacao(bool editar);
	int menuEditHabitacao(Habitacao* habitacao);
	int menuSelectOrVacantHabitacao();
	int menuSelectOwnerHabitacao();
	int menuDeleteHabitacao(int pos, int menuOption);

	int menuGerirFuncionarios();
	int menuDisplayFuncionariosBy();
	int menuDisplayAllFuncionarios();
	int menuAddFuncionario();
	int menuConfirmAddFuncionario(int specialty, int menuOption);
	int menuFireFuncionario();
	int menuDeleteFuncionario(int pos, int menuOption);

	int menuGerirServicos(); //TODO menuGerirServicos()



	//Import & extract functions
	bool importCondominio();
	bool exportCondominio();

	bool importCondominos();
	bool exportCondominos();

	bool importHabitacoes();
	bool exportHabitacoes();

	bool importFuncionarios();
	bool exportFuncionarios();

	int exitFunction();

};

bool hasWhitespace(string s);
bool isNumber(string s);
bool isName(string s);

void displayLogo();
string currentTime();
void pressEnterToContinue();

void createMesesAno();
void createMenuOptions();

int main();

#endif

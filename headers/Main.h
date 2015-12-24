#ifndef HEADERS_MAIN_H_
#define HEADERS_MAIN_H_

#include "../headers/Header.h"
#include "../headers/Condominio.h"

class Main {
private:
	vector<vector<string> > menu;
	int option;
	Condominio* condominio;
	Condomino* currentUser;
	bool notificacaoAdmin;
	bool notificacaoUser;

	//Segunda parte
	BST<Condominio> condominios;

public:
	Main() {
		this->option = 0;
		this->currentUser = NULL;
		this->notificacaoAdmin = false;
		this->notificacaoUser = false;
	} //default constructor

	void displayTime();
	void verificaServicos();

	void setMenus(vector<vector<string> > menu);
	void setCurrentUser(Condomino condomino);

	void resetOption();
	bool displayYesNo(int option);
	bool displayVivendaApartamento(int option);
	bool displayMenuOptions(int position);

	bool displaySelectCondomino();
	bool displaySelectHabitacao(vector<Habitacao*> habitacoes);
	bool displaySelectHabitacaoPossuida();
	bool displaySelectFuncionario(vector<Funcionario> &func);
	bool displaySelectServico(int vector);
	bool displaySelectServicoRequisitado(vector<Servico> servicos);
	bool displaySelectTransporte();
	bool displaySelectParagem(Transporte &t1);

	bool validLogin(string utilizador, string password);
	bool validRegister(string utilizador, string password);

	bool editCondominio(int editOption, Condominio &c1);
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
	void displayServicoInfo(int pos, int vectorServicos);
	void displayServicoRequisitadoInfo(vector<Servico> servicos, int pos);

	bool searchFuncionario();

	bool fimDoMes();

	//Menu Functions
	int menuInicial();

	int menuLogin();
	int menuRegisto();

	/*
	 * Menu Utilizador
	 */
	int menuUtilizador();

	int menuEditDadosConta(Condomino &condomino);
	int menuEditDadosCondomino(Condomino &condomino);

	int menuHabitacoesPossuidas();
	int menuSelectHabitacoesPossuida(bool remover);
	int menuDeleteHabitacaoPossuida(int pos, int menuOption);
	int menuSelectOrNewHabitacao();
	int menuSelectHabitacaoAdd(vector<Habitacao*> habitacoes);
	int menuAddHabitacao(Condomino condomino);
	int menuConfirmAddHabitacao(Condomino condomino, Habitacao* h1, bool nova);

	int menuServicosRequisitados();
	int menuDisplayServicosRequisitadosBy(vector<Servico> servicos);
	int menuDisplayServicosRequisitados(vector<Servico> servicos,
			bool cancelar);
	int menuSelectHabitacaoServicoUtilizador(vector<Habitacao*> habitacoes);
	int menuRequisitarServico(int pos, int tipo, int menuOption);
	int menuCancelarServico(vector<Servico> servicos, int pos, int menuOption);

	/*
	 * Menu Administrador
	 */
	int menuAdministrador();

	//Gerir Condominos
	int menuGerirCondominos();
	int menuDisplayCondominosBy();
	int menuDisplayAllCondominos();
	int menuSelectCondomino(bool remover);
	int menuEditCondomino(Condomino &condomino);
	int menuDeleteCondomino(Condomino &condomino, int menuOption);

	//Gerir Habitacoes
	int menuGerirHabitacoes();
	int menuDisplayHabitacoesBy();
	int menuDisplayAllHabitacoes();
	int menuSelectHabitacao(bool editar);
	int menuEditHabitacao(Habitacao* habitacao);
	int menuSelectOrVacantHabitacao();
	int menuSelectOwnerHabitacao();
	int menuDeleteHabitacao(int pos, int menuOption);

	//Gerir Funcionarios
	int menuGerirFuncionarios();
	int menuDisplayFuncionariosBy();
	int menuDisplayAllFuncionarios(vector<Funcionario> &funcionarios);
	int menuAddFuncionario();
	int menuConfirmAddFuncionario(int specialty, int menuOption);
	int menuFireFuncionario();
	int menuDeleteFuncionario(int pos, int menuOption);

	//Gerir Servicos
	int menuGerirServicos();
	int menuDisplayServicosBy(int vectorServicos);
	int menuDisplayAllServicos(int vectorServicos, bool remover);
	int menuSelectHabitacaoServico();
	int menuSelectTipoServico(int pos, bool sameUser);
	int menuAddServico(int pos, int tipo, int menuOption, bool sameUser);
	int menuDeleteServico(int pos, int vectorServicos, int menuOption);

	string convertTime(int mes, time_t time);
	string convertTime(string mes, time_t time);

	//Import & extract functions
	bool importCondominios();
	bool exportCondominios();

	bool importCondominos(Condominio &cond);
	bool exportCondominos(Condominio &cond);

	bool importHabitacoes(Condominio &cond);
	bool exportHabitacoes(Condominio &cond);

	bool importFuncionarios(Condominio &cond);
	bool exportFuncionarios(Condominio &cond);

	bool importServicos(Condominio &cond);
	bool exportServicos(Condominio &cond);

	bool importTransportes(Condominio &cond);
	bool exportTransportes(Condominio &cond);

	int exitFunction();

	//Segunda Parte
	int menuGestaoCondominios();
	int menuDisplayAllCondominios(vector<Condominio> &conds);
	int menuDisplayCondominiosBy(vector<Condominio> &conds);
	int menuConfirmSelectCondominio(vector<Condominio> &conds, int menuOption);
	int menuFiltrarCondominios(vector<Condominio> &conds);
	int menuAddCondominio();
	int menuConfirmAddCondominio(Condominio &c1, int menuOption);
	int menuSelectCondominio(vector<Condominio> &conds, bool remover);
	int menuEditCondominio(Condominio &c1);
	int menuDeleteCondominio(Condominio &c1, int menuOption);

	vector<Condominio> getVectorCondominios();
	void sortCondominios(vector<Condominio> &conds, int sortOption);
	bool displaySelectCondominio(vector<Condominio> &conds);

	int menuParagemMaisProxima();
	int menuEspecificarDestino();

	bool paragemMaisProxima(priority_queue<Transporte> transportes);

	//Gerir Transportes
	int menuGerirTransportes();
	int menuSelectParagem(Transporte &t1);
	int menuDesactivarParagem(Transporte &t1, Paragem &p1, int menuOption);
	int menuNovaParagem(Transporte &t1);
	int menuConfirmAddParagem(Transporte &t1, Paragem &p1, int menuOption);

	int menuSelectTransporte(int editOption);
	int menuAlterarTransporte(Transporte t1);
	int menuAddTransporte();
	int menuConfirmAddTransporte(Transporte &t1, int menuOption);
};

/*
 * Exceptions
 */
class DadosInvalidos {
public:
public:
	friend ostream& operator<<(ostream& out, const DadosInvalidos &e) {
		out << "\nDados invalidos." << endl;
		return out;
	}
};
class NomeUtilizadorInvalido {
public:
	friend ostream& operator<<(ostream& out, const NomeUtilizadorInvalido &e) {
		out
				<< "O nome de utilizador tem que conter entre 1 a 20 caracteres inclusive."
				<< endl;
		return out;
	}
};
class PasswordInvalida {
public:
	friend ostream& operator<<(ostream& out, const PasswordInvalida &e) {
		out << "A password tem que conter entre 5 a 20 caracteres inclusive."
				<< endl;
		return out;
	}
};
class UtilizadorPasswordEspacos {
public:
	friend ostream& operator<<(ostream& out,
			const UtilizadorPasswordEspacos &e) {
		out << "O nome de utilizador e password nao podem conter espacos."
				<< endl;
		return out;
	}
};
class NomeUtilizadorIndisponivel {
	string nomeUtilizador;
public:
	NomeUtilizadorIndisponivel(string nomeUtilizador) {
		this->nomeUtilizador = nomeUtilizador;
	}
	string getNomeUtilizador() const {
		return nomeUtilizador;
	}
	friend ostream& operator<<(ostream& out,
			const NomeUtilizadorIndisponivel &e) {
		out << "O nome de utilizador \"" << e.getNomeUtilizador()
				<< "\" nao esta disponivel." << endl;
		return out;
	}
};

/*
 * Non-class functions
 */
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

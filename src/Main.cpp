#include "../headers/Main.h"

#include "../headers/Header.h"
#include "../headers/Utils.h"

#define pathLogo "../savedata/logo.txt"
#define pathCondominos "../savedata/condominos.txt"
#define pathHabitacoes "../savedata/habitacoes.txt"
#define pathUtilizadores "../savedata/utilizadores.txt"

const string currentTime();
void pressEnterToContinue();
bool hasWhitespace(string s);
bool isNumber(string s);
bool isName(string s);

vector<string> mesesAno;
vector<vector<string> > menu;

/*
 * Class functions
 */

// Displays time using currentDateTime()
void Main::displayTime() {
	string time = currentTime();
	gotoxy(50, 20);
	cout << mesesAno[this->condominio.getMes()] << "\t" << time;
}

void Main::setMenus(vector<vector<string> > menu) {
	this->menu = menu;
}
void Main::setUtilizadores(vector<Utilizador> utilizadores) {
	insertionSort(utilizadores);
	this->utilizadores = utilizadores;
}

bool Main::addUtilizador(Utilizador utilizador) {
	int pos1 = sequentialSearch(this->utilizadores, utilizador);
	if (pos1 != -1)
		return false;

	//Verifica se a adicao do novo utilizador vai obrigar a uma mudanca no apontador do currentUser
	if (utilizador < *(currentUser)) {
		int pos2 = sequentialSearch(this->utilizadores, *(currentUser));
		insertionSort(utilizadores);
		this->utilizadores.push_back(utilizador);
		this->currentUser = &utilizadores[pos2 + 1];
	} else {
		insertionSort(utilizadores);
		this->utilizadores.push_back(utilizador);
	}
	return true;
}
bool Main::eraseUtilizador(string nomeUtilizador) {
	Utilizador u1 = Utilizador(nomeUtilizador);
	int pos1 = sequentialSearch(this->utilizadores, u1);
	if (pos1 == -1)
		return false;
	int pos2 = sequentialSearch(this->utilizadores, *(currentUser));
	if (pos1 < pos2)
		this->currentUser = &this->utilizadores[pos2 - 1];

	this->utilizadores.erase(utilizadores.begin() + pos1);
	return true;
}

// Resets menu option. Called every time we switch to a new menu.
void Main::resetOption() {
	this->option = 0;
}
// Prints a Yes/No select screen at position (x,y);
bool Main::displayYesNo() {
	if (option >= 2) {
		return EXIT_FAILURE;
	}
	vector<string> YesNo;
	YesNo.push_back("Sim");
	YesNo.push_back("Nao");

	if (option == 0) {
		setcolor(BLACK, LIGHTGREY);
		cout << "Sim";
		setcolor(WHITE, BLACK);
		cout << "\tNao" << endl;
	} else if (option == 1) {
		setcolor(WHITE, BLACK);
		cout << "Sim\t";
		setcolor(BLACK, LIGHTGREY);
		cout << "Nao" << endl;
		setcolor(WHITE, BLACK);
	}
	return EXIT_SUCCESS;
}
// Prints a Menu Select screen
bool Main::displayMenuOptions(int position) {
	if (option >= menu[position].size()) {
		return EXIT_FAILURE;
	}
	for (size_t i = 0; i < menu[position].size(); i++) {
		gotoxy(25, 10 + i);
		if (i == option) {
			setcolor(BLACK, LIGHTGREY);
			cout << "=> " << left << setw(15) << setfill(' ')
					<< menu[position][option] << endl;
			setcolor(WHITE, BLACK);
		} else
			cout << menu[position][i] << endl;
	}
	return EXIT_SUCCESS;
}
bool Main::displaySelectUtilizador() {
	if (option >= utilizadores.size()) {
		return EXIT_FAILURE;
	}
	for (size_t i = 0; i < utilizadores.size(); i++) {
		gotoxy(0, 10 + i);
		if (i == option) {
			setcolor(BLACK, LIGHTGREY);
			cout << "=>" << utilizadores[i].getNomeUtilizador();
			setcolor(WHITE, BLACK);
			if (utilizadores[i].isAdmin()) {
				cout << "\t\t\t ADMIN" << endl;
			} else
				cout << endl;
		} else {
			cout << utilizadores[i].getNomeUtilizador();
			if (utilizadores[i].isAdmin()) {
				cout << "\t\t\t ADMIN" << endl;
			} else
				cout << endl;
		}
	}
	return EXIT_SUCCESS;
}
bool Main::displaySelectCondomino() {
	if (option >= this->condominio.getMoradores().size()) {
		return EXIT_FAILURE;
	}
	for (size_t i = 0; i < this->condominio.getMoradores().size(); i++) {
		gotoxy(0, 10 + i);
		if (i == option) {
			setcolor(BLACK, LIGHTGREY);
			cout << "=> " << left << setw(15) << setfill(' ')
					<< this->condominio.getMoradores()[i]->getNome();
			cout << "\t " << this->condominio.getMoradores()[i]->getNIF()
					<< endl;
			setcolor(WHITE, BLACK);
		} else {
			cout << this->condominio.getMoradores()[i]->getNome();
			cout << "\t " << this->condominio.getMoradores()[i]->getNIF()
					<< endl;
		}
	}
	return EXIT_SUCCESS;
}
bool Main::displaySelectHabitacao() {
	if (option >= this->condominio.getHabitacoes().size()) {
		return EXIT_FAILURE;
	}
	for (size_t i = 0; i < this->condominio.getHabitacoes().size(); i++) {
		gotoxy(0, 10 + i);
		if (i == option) {
			setcolor(BLACK, LIGHTGREY);
			cout << "=> " << left << setw(15) << setfill(' ')
					<< this->condominio.getHabitacoes()[i]->getTipo();
			cout << "\t " << this->condominio.getHabitacoes()[i]->getMorada()
					<< endl;
			setcolor(WHITE, BLACK);
		} else {
			cout << this->condominio.getHabitacoes()[i]->getTipo();
			cout << "\t " << this->condominio.getHabitacoes()[i]->getMorada()
					<< endl;
		}
	}
	return EXIT_SUCCESS;

}
// Checks if the user exists and, if so, updates currentUser.
bool Main::validLogin(string utilizador, string password) {
	Utilizador u1 = Utilizador(utilizador, password);
	int pos = sequentialSearch(this->utilizadores, u1);
	if (pos == -1)
		return false;
	if (utilizadores[pos].getPassword() != password)
		return false;
	this->currentUser = &utilizadores[pos];
	return true;
}
// Checks if username and password are within the rules
bool Main::validRegister(string utilizador, string password) {
	if (utilizador.size() < 1 || utilizador.size() > 20) {
		cout
				<< "\nO nome de utilizador tem que conter entre 1 a 20 caracteres inclusive."
				<< endl;
		return false;
	}
	if (password.size() < 5 || password.size() > 20) {
		cout << "\nA password tem que conter entre 5 a 20 caracteres inclusive."
				<< endl;
		return false;
	}
	if (hasWhitespace(utilizador) || hasWhitespace(password)) {
		cout << "\nO nome de utilizador e password nao podem conter espacos."
				<< endl;
		return false;
	}
	Utilizador u1 = Utilizador(utilizador, password);
	int pos = sequentialSearch(this->utilizadores, u1);
	if (pos == -1)
		return true;
	else {
		cout << "\nO nome de utilizador nao esta disponivel." << endl;
		return false;
	}
}

bool Main::editDadosConta(int option) {
	displayLogo();
	gotoxy(0, 8);
	if (option == 0) {
		cout << "Alterar nome de utilizador:\n" << endl;
		string utilizadorActual = this->currentUser->getNomeUtilizador();
		cout << "Nome actual: " << utilizadorActual << endl;
		string utilizadorNovo = "";
		cout << "Introduza o novo nome de utilizador: ";
		getline(cin, utilizadorNovo);
		string password = "";
		cout << "Introduza a sua password: ";
		getline(cin, password);
		if (password != this->currentUser->getPassword()) {
			cout << "\nNao foi possivel alterar o nome de utilizador." << endl;
			cout << "Password invalida." << endl;
			pressEnterToContinue();
			return false;
		}
		if (utilizadorActual == utilizadorNovo) {
			cout << "\nNao foi possivel alterar o nome de utilizador." << endl;
			cout << "O novo nome tem que ser diferente do actual." << endl;
			pressEnterToContinue();
			return false;
		}
		if (validRegister(utilizadorNovo, this->currentUser->getPassword())) {
			this->currentUser->setNomeUtilizador(utilizadorNovo);

			insertionSort(this->utilizadores);
			Utilizador u1 = Utilizador(utilizadorNovo);
			int pos = sequentialSearch(this->utilizadores, u1);
			this->currentUser = &utilizadores[pos];

			cout << "\nNome de utilizador alterado." << endl;
			pressEnterToContinue();
			return true;
		} else
			pressEnterToContinue();
		return false;
	} else if (option == 1) {
		cout << "Alterar password:\n" << endl;
		string passwordActual = this->currentUser->getPassword();
		string password = "";
		cout << "Introduza a sua password actual: ";
		getline(cin, password);
		if (password != passwordActual) {
			cout << "\nPassword invalida." << endl;
			pressEnterToContinue();
			return false;
		}
		string passwordNova = "";
		cout << "Introduza a nova password: ";
		getline(cin, passwordNova);
		if (passwordActual == passwordNova) {
			cout << "\nNao foi possivel alterar a password." << endl;
			cout << "A nova password tem que ser diferente da actual." << endl;
			pressEnterToContinue();
			return false;
		}
		if (validRegister(this->currentUser->getNomeUtilizador(),
				passwordNova)) {
			this->currentUser->setPassword(passwordNova);
			cout << "\nPassword alterada." << endl;
			pressEnterToContinue();
			return true;
		}
	}
	return false;
}

bool Main::editDadosContaAdmin(int option, Utilizador* utilizador) {
	displayLogo();
	gotoxy(0, 8);
	if (option == 0) {
		cout << "Alterar nome de utilizador:\n" << endl;
		string utilizadorActual = utilizador->getNomeUtilizador();
		cout << "Nome actual: " << utilizadorActual << endl;
		string utilizadorNovo = "";
		cout << "Introduza o novo nome de utilizador: ";
		getline(cin, utilizadorNovo);
		if (utilizadorActual == utilizadorNovo) {
			cout << "\nNao foi possivel alterar o nome de utilizador." << endl;
			cout << "O novo nome tem que ser diferente do actual." << endl;
			pressEnterToContinue();
			return false;
		}
		if (validRegister(utilizadorNovo, utilizador->getPassword())) {
			utilizador->setNomeUtilizador(utilizadorNovo);

			Utilizador u1 = Utilizador(this->currentUser->getNomeUtilizador());
			insertionSort(this->utilizadores);
			int pos = sequentialSearch(this->utilizadores, u1);
			this->currentUser = &utilizadores[pos];

			cout << "\nNome de utilizador alterado." << endl;
			pressEnterToContinue();
			return true;

		} else
			pressEnterToContinue();
		return false;
	} else if (option == 1) {
		cout << "Alterar password:\n" << endl;
		string passwordActual = utilizador->getPassword();
		string passwordNova = "";
		cout << "Introduza a nova password: ";
		getline(cin, passwordNova);
		if (passwordActual == passwordNova) {
			cout << "\nNao foi possivel alterar a password." << endl;
			cout << "A nova password tem que ser diferente da actual." << endl;
			pressEnterToContinue();
			return false;
		}
		if (validRegister(utilizador->getNomeUtilizador(), passwordNova)) {
			utilizador->setPassword(passwordNova);
			cout << "\nPassword alterada." << endl;
			pressEnterToContinue();
			return true;
		}
	} else if (option == 2) {
		cout << "Alterar estado de administrador:\n" << endl;
		string admin = "";
		if (utilizador->isAdmin())
			admin = "ADMIN";
		else
			admin = "Conta normal";
		cout << "Estado anterior = " << admin << endl;
		if (utilizador == this->currentUser) {
			cout << "\nNao foi possivel alterar o estado da conta." << endl;
			cout
					<< "Nao e possivel revogar direitos administrativos do proprio utilizador."
					<< endl;
			pressEnterToContinue();
			return false;
		} else if (utilizador->isAdmin()) {
			utilizador->setAdmin(false);
			cout << "\nO utilizador deixou de ser administrador." << endl;
			pressEnterToContinue();
			return true;
		} else {
			utilizador->setAdmin(true);
			cout << "\nO utilizador passou a ser administrador." << endl;
			pressEnterToContinue();
			return true;
		}
	}
	return false;
}
bool Main::editDadosCondomino(int option, Condomino* condomino) {
	displayLogo();
	gotoxy(0, 8);
	if (option == 0) {
		cout << "Alterar nome:\n" << endl;
		string nomeActual = this->currentUser->getDados()->getNome();
		cout << "Nome actual: " << nomeActual << endl;
		string nomeNovo = "";
		cout << "Introduza o novo nome: ";
		getline(cin, nomeNovo);
		if (!isName(nomeNovo)) {
			cout << "\nNao foi possivel alterar o nome." << endl;
			cout << "O nome que introduziu nao e valido." << endl;
			pressEnterToContinue();
			return false;
		}
		this->currentUser->getDados()->setNome(nomeNovo);
		cout << "\nNome alterado." << endl;
		pressEnterToContinue();
		return true;
	} else if (option == 1) {
		cout << "Alterar NIF:\n" << endl;
		string nifActual = this->currentUser->getDados()->getNIF();
		cout << "NIF actual: " << nifActual << endl;

		string nifNovo = "";
		cout << "Introduza o novo NIF: ";
		getline(cin, nifNovo);
		if (nifNovo.size() != 9 || !isNumber(nifNovo)) {
			cout << "\nNao foi possivel alterar o NIF." << endl;
			cout << "O NIF tem que ser um inteiro positivo de 9 digitos."
					<< endl;
			pressEnterToContinue();
			return false;
		}
		int pos = -1;
		for (size_t i = 0; i < this->condominio.getMoradores().size(); i++) {
			if (this->condominio.getMoradores()[i]->getNIF() == nifNovo)
				pos = i;
		}
		if (pos != -1) {
			cout << "\nNao foi possivel alterar o NIF." << endl;
			cout << "O NIF ja pertence a outro condomino." << endl;
			pressEnterToContinue();
			return false;
		}
		this->currentUser->getDados()->setNIF(nifNovo);
		cout << "\nNIF alterado." << endl;
		pressEnterToContinue();
		return true;

	}
	return false;
}

void Main::displayCurrentUserInfo() const {
	displayLogo();
	gotoxy(0, 8);
	cout << "DADOS:\n" << endl;
	this->currentUser->getDados()->info();
	pressEnterToContinue();
}
void Main::displayCurrentUserHabitacoes() const {
	displayLogo();
	gotoxy(0, 8);
	this->currentUser->getDados()->infoHabitacoes();
	pressEnterToContinue();
}
void Main::displayCurrentUserRenda() const {
	displayLogo();
	gotoxy(0, 8);
	this->currentUser->getDados()->infoRenda();
	cout << endl;
	pressEnterToContinue();
}

void Main::displayAllUtilizadores() const {
	displayLogo();
	gotoxy(0, 8);
	cout << "LISTA DE UTILIZADORES:" << endl;
	cout << "Numero de utilizadores = " << this->utilizadores.size() << "\n"
			<< endl;

	for (size_t i = 0; i < this->utilizadores.size(); i++) {
		cout << utilizadores[i].getNomeUtilizador();
		if (utilizadores[i].isAdmin())
			cout << "\t ADMIN" << endl;
		else
			cout << endl;
	}
	cout << endl;
	pressEnterToContinue();
}
void Main::displayAllCondominos() const {
	displayLogo();
	gotoxy(0, 8);
	cout << "LISTA DE CONDOMINOS:" << endl;
	this->condominio.infoMoradores();
	pressEnterToContinue();
}
void Main::displayAllHabitacoes() const {
	displayLogo();
	gotoxy(0, 8);
	cout << "LISTA DE Habitacoes:" << endl;
	this->condominio.infoHabitacoes();
	pressEnterToContinue();
}

/*
 * Menu functions
 */

int Main::menuInicial() {
	displayLogo();
	gotoxy(30, 8);
	cout << "MENU INICIAL\n" << endl;

	displayMenuOptions(0);

	displayTime();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < menu[0].size())
			option++;
		break;
	case KEY_ENTER:
		if (option == 0) {
			resetOption();
			return menuLogin();
		} else if (option == 1) {
			resetOption();
			menuRegisto();
		}
		return EXIT_SUCCESS;
		break;
	default:
		break;
	}

	return menuInicial();
}

int Main::menuLogin() {
	displayLogo();
	gotoxy(30, 8);
	cout << "LOGIN\n" << endl;
	cout << "Introduza os seus dados de login:\n";

	string utilizador = "";
	string password = "";

	cout << "Utilizador: ";
	getline(cin, utilizador);
	cout << "Password: ";
	getline(cin, password);

	if (validLogin(utilizador, password)) {
		resetOption();
		insertionSort(this->utilizadores);
		return menuUtilizador();
	} else {
		cout << "\nDados invalidos\n";
		pressEnterToContinue();
		resetOption();
		return menuInicial();
	}
	return EXIT_SUCCESS;
}
int Main::menuRegisto() {
	displayLogo();
	gotoxy(30, 8);
	cout << "REGISTO\n" << endl;
	cout << "Introduza os seus dados de login:\n";

	string utilizador = "";
	string password = "";

	cout << "Utilizador: ";
	getline(cin, utilizador);
	cout << "Password: ";
	getline(cin, password);

	if (validRegister(utilizador, password)) {
		Utilizador u1 = Utilizador(utilizador, password);
		this->addUtilizador(u1);
		cout << "\nConta criada com sucesso!" << endl;
	} else {
		cout << "Nao foi possivel criar uma conta." << endl;
	}
	insertionSort(utilizadores);
	pressEnterToContinue();
	resetOption();
	return EXIT_SUCCESS;
}

int Main::menuUtilizador() {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	int menuOption = -1;
	if (this->currentUser->isAdmin()) {
		menuOption = 1; //Admin menu
	} else {
		menuOption = 2; //Normal menu
	}

	gotoxy(30, 8);
	cout << "MENU UTILIZADOR" << endl;
	displayMenuOptions(menuOption);

	displayTime();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < menu[menuOption].size())
			option++;
		break;
	case KEY_ENTER:
		if (menuOption == 1)
			if (option == 0) {
				resetOption();
				return menuAdministrador();
			} else if (option == 1) {
				resetOption();
				return menuEditDadosConta(this->currentUser);
			} else if (option == 2) {
				displayCurrentUserInfo();
			} else if (option == 3) {
				resetOption();
				return menuEditDadosCondomino(this->currentUser->getDados());
			} else if (option == 4) {
				resetOption();
				return menuHabitacoesPossuidas();
			} else {
				resetOption();
				return menuInicial();
			}
		else if (menuOption == 2) {
			if (option == 0) {
				resetOption();
				return menuEditDadosConta(this->currentUser);
			} else if (option == 1) {
				displayCurrentUserInfo();
			} else if (option == 2) {
				resetOption();
				return menuEditDadosCondomino(this->currentUser->getDados());
			} else if (option == 3) {
				resetOption();
				return menuHabitacoesPossuidas();
			} else {
				resetOption();
				return menuInicial();
			}
		}
		break;
	default:
		break;
	}

	return menuUtilizador();
}
int Main::menuEditDadosConta(Utilizador* utilizador) {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "ALTERAR DADOS\n" << endl;
	displayMenuOptions(3);

	displayTime();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < menu[3].size())
			option++;
		break;
	case KEY_ENTER:
		if (option == 0) {
			editDadosConta(0);
			resetOption();
			return menuUtilizador();
		} else if (option == 1) {
			editDadosConta(1);
			resetOption();
			return menuUtilizador();
		} else if (option == 2)
			resetOption();
		return menuUtilizador();
		break;
	case KEY_ESC:
		resetOption();
		return menuUtilizador();
		break;
	default:
		break;
	}
	return menuEditDadosConta(utilizador);
}
int Main::menuEditDadosCondomino(Condomino* condomino) {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "ALTERAR DADOS\n" << endl;
	displayMenuOptions(4);

	displayTime();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < menu[4].size())
			option++;
		break;
	case KEY_ENTER:
		if (option == 0) {
			editDadosCondomino(0, condomino);
			resetOption();
			return menuUtilizador();
		} else if (option == 1) {
			editDadosCondomino(1, condomino);
			resetOption();
			return menuUtilizador();
		} else if (option == 2)
			resetOption();
		return menuUtilizador();
		break;
	case KEY_ESC:
		resetOption();
		return menuUtilizador();
		break;
	default:
		break;
	}
	return menuEditDadosCondomino(condomino);
}
int Main::menuHabitacoesPossuidas() {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "ALTERAR DADOS\n" << endl;
	displayMenuOptions(5);

	displayTime();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < menu[5].size())
			option++;
		break;
	case KEY_ENTER:
		if (option == 0) {
			displayCurrentUserHabitacoes();
		} else if (option == 1) {
			displayCurrentUserRenda();
		} else {
			resetOption();
			return menuUtilizador();
		}
		break;
	case KEY_ESC:
		resetOption();
		return menuUtilizador();
		break;
	default:
		break;
	}
	return menuHabitacoesPossuidas();
}

int Main::menuAdministrador() {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "MENU ADMINISTRADOR" << endl;
	displayMenuOptions(7);

	displayTime();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < menu[7].size())
			option++;
		break;
	case KEY_ENTER:
		if (option == 0) {
			resetOption();
			return menuGerirUtilizadores();
		} else if (option == 1) {
			resetOption();
			return menuGerirCondominos();
		} else if (option == 2) {
			resetOption();
			return menuGerirHabitacoes();
		} else {
			resetOption();
			return menuUtilizador();
		}
		break;
	case KEY_ESC:
		resetOption();
		return menuUtilizador();
		break;
	default:
		break;
	}

	return menuAdministrador();
}

int Main::menuGerirUtilizadores() {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "GERIR UTILIZADORES" << endl;
	displayMenuOptions(8);

	displayTime();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < menu[8].size())
			option++;
		break;
	case KEY_ENTER:
		if (option == 0) //Ver lista de utilizadores
			displayAllUtilizadores();
		else if (option == 1) { //Alterar dados de um utilizador
			resetOption();
			return menuSelectUtilizador(true);
		} else if (option == 2) { //Adicionar utilizador
			resetOption();
			Utilizador u1 = *currentUser;
			menuRegisto();
			int pos = sequentialSearch(this->utilizadores,u1);
			this->currentUser = &utilizadores[pos];
			return menuGerirUtilizadores();
		} else if (option == 3) { //Remover utilizador
			resetOption();
			return menuSelectUtilizador(false);
		} else {
			resetOption();
			return menuAdministrador();
		}
		break;
	case KEY_ESC:
		resetOption();
		return menuAdministrador();
		break;
	default:
		break;
	}

	return menuGerirUtilizadores();
}
int Main::menuSelectUtilizador(bool editar) {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "SELECIONE O UTILIZADOR:" << endl;
	cout << "[ESC] Voltar atras" << endl;
	displaySelectUtilizador();

	displayTime();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < utilizadores.size())
			option++;
		break;
	case KEY_ENTER:
		if (editar) {
			int pos = option;
			resetOption();
			return menuEditUtilizador(&utilizadores[pos]);
		} else {
			int pos = option;
			resetOption();
			return menuDeleteUtilizador(&utilizadores[pos]);
		}
		break;
	case KEY_ESC:
		resetOption();
		return menuGerirUtilizadores();
		break;
	default:
		break;
	}

	return menuSelectUtilizador(editar);

}
int Main::menuEditUtilizador(Utilizador* utilizador) {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "ALTERAR DADOS\n" << endl;
	displayMenuOptions(13);

	displayTime();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < menu[13].size())
			option++;
		break;
	case KEY_ENTER:
		if (option == 0) {
			editDadosContaAdmin(0, utilizador);
			resetOption();
			return menuGerirUtilizadores();
		} else if (option == 1) {
			editDadosContaAdmin(1, utilizador);
			resetOption();
			return menuGerirUtilizadores();
		} else if (option == 2) {
			editDadosContaAdmin(2, utilizador);
			resetOption();
			return menuGerirUtilizadores();
		} else {
			resetOption();
			return menuGerirUtilizadores();
		}
		break;
	case KEY_ESC:
		resetOption();
		return menuGerirUtilizadores();
		break;
	default:
		break;
	}

	return menuEditUtilizador(utilizador);
}

int Main::menuDeleteUtilizador(Utilizador* utilizador) {
	displayLogo();
	gotoxy(0, 8);
	cout << "DADOS DO UTILIZADOR A REMOVER:\n" << endl;
	cout << "Nome de utilizador - " << utilizador->getNomeUtilizador() << endl;
	if (utilizador->hasDados()) {
		cout << "\nDados do condomino:" << endl;
		utilizador->getDados()->info();
	}
	bool sameUser = false;
	if (this->currentUser == utilizador)
		sameUser = true;
	if (sameUser)
		cout << "Tem a certeza que pretende remover a sua conta?" << endl;
	else if (utilizador->hasDados())
		cout
				<< "Tem a certeza que pretende remover este utilizador e o condomino associado?"
				<< endl;
	else
		cout << "Tem a certeza que pretende remover este utilizador?" << endl;
	displayYesNo();

	int c = getch();
	switch (c) {
	case KEY_LEFT:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_RIGHT:
		if (option + 1 < 2)
			option++;
		break;
	case KEY_ENTER:
		if (option == 0) {
			if (eraseUtilizador(utilizador->getNomeUtilizador()))
				cout << "\nUtilizador removido." << endl;
			pressEnterToContinue();
			resetOption();
			if (sameUser)
				return menuInicial();
			else
				return menuGerirUtilizadores();
		} else if (option == 1) {
			resetOption();
			return menuGerirUtilizadores();
		}
		break;
	case KEY_ESC:
		resetOption();
		return menuGerirUtilizadores();
		break;
	default:
		break;
	}
	return menuDeleteUtilizador(utilizador);
}

int Main::menuGerirCondominos() {
	return EXIT_FAILURE;
}
int Main::menuGerirHabitacoes() {
	return EXIT_FAILURE;
}
int Main::menuGerirFuncionarios() {
	return EXIT_FAILURE;
} //TODO menuGerirFuncionarios()
int Main::menuGerirServicos() {
	return EXIT_FAILURE;
} //TODO menuGerirServicos()

// Extracts data from condominos.txt to create a vector of owners.
bool Main::importCondominos() {
	ifstream myfile(pathCondominos);
	string line = "";
	string nomeUtilizador = "";
	string nome = "";
	string NIF = "";
	int fundosMensais = 0;
	int divida = 0;

	vector<Condomino*> moradores;

	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			nomeUtilizador = line;
			getline(myfile, nome);
			getline(myfile, NIF);
			getline(myfile, line);
			fundosMensais = atoi(line.c_str());
			getline(myfile, line);
			divida = atoi(line.c_str());
			Utilizador u1 = Utilizador(nomeUtilizador);
			int pos = sequentialSearch(this->utilizadores, u1);
			if (pos != -1) {
				Condomino* c1 = new Condomino(nome, NIF, fundosMensais, divida);
				moradores.push_back(c1);
				utilizadores[pos].setDados(c1);
			}
			getline(myfile, line);
		}
		myfile.close();
		this->condominio.setMoradores(moradores);
		return true;
	} else {
		displayLogo();
		cout
				<< "ERRO: Ocorreu um problema ao aceder ao ficheiro de condominos.\n";
		pressEnterToContinue();
		return false;
	}

}
bool Main::exportCondominos() {
	ofstream myfile(pathCondominos, ios::trunc);

	if (myfile.is_open()) {
		for (size_t i = 0; i < this->utilizadores.size(); i++) {
			if (this->utilizadores[i].hasDados()) {
				myfile << this->utilizadores[i].getNomeUtilizador() << endl;
				myfile << this->utilizadores[i].getDados()->getNome() << endl;
				myfile << this->utilizadores[i].getDados()->getNIF() << endl;
				myfile << this->utilizadores[i].getDados()->getFundosMensais()
						<< endl;
				myfile << this->utilizadores[i].getDados()->getDivida() << endl;
				myfile << endl;
			}
		}
		myfile.close();
		return true;
	} else {
		displayLogo();
		cout
				<< "ERRO: Ocorreu um problema ao aceder ao ficheiro de condominos.\n";
		pressEnterToContinue();
		return false;
	}
}

bool Main::importHabitacoes() {
	ifstream myfile(pathHabitacoes);
	string line = "";
	string tipo = "";
	string morada = "";
	string codigoPostal = "";
	string nifProprietario = "";
	string substr = "";
	bool pago[12] = { 0 };

	float areaInterior = 0;
	float areaExterior = 0;
	bool piscina = false;

	int tipologia = 0;
	int piso = 0;

	vector<Habitacao*> habitacoes;

	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			tipo = line;
			getline(myfile, morada);
			getline(myfile, codigoPostal);
			getline(myfile, nifProprietario);
			getline(myfile, line);
			for (size_t i = 0; i < 12; i++) {
				substr = line.substr(i, 1);
				if (substr == "0")
					pago[i] = false;
				else
					pago[i] = true;
			}
			if (tipo == "Vivenda") {
				getline(myfile, line);
				areaInterior = atof(line.c_str());
				getline(myfile, line);
				areaExterior = atof(line.c_str());
				getline(myfile, line);
				if (line == "0")
					piscina = false;
				else
					piscina = true;

				int pos = -1;
				for (size_t i = 0; i < this->condominio.getMoradores().size();
						i++) {
					if (this->condominio.getMoradores()[i]->getNIF()
							== nifProprietario)
						pos = i;
				}
				if (pos != -1) {
					Vivenda* v1 = new Vivenda(morada, codigoPostal,
							this->condominio.getMoradores()[pos]->getNIF(),
							pago, areaInterior, areaExterior, piscina);
					habitacoes.push_back(v1);
					this->condominio.getMoradores()[pos]->addPropriedade(v1);
				}
			} else if (tipo == "Apartamento") {
				getline(myfile, line);
				tipologia = atoi(line.c_str());
				getline(myfile, line);
				areaInterior = atof(line.c_str());
				getline(myfile, line);
				piso = atoi(line.c_str());

				int pos = -1;
				for (size_t i = 0; i < this->condominio.getMoradores().size();
						i++) {
					if (this->condominio.getMoradores()[i]->getNIF()
							== nifProprietario)
						pos = i;
				}
				if (pos != -1) {
					Apartamento* a1 = new Apartamento(morada, codigoPostal,
							this->condominio.getMoradores()[pos]->getNIF(),
							pago, tipologia, areaInterior, piso);
					habitacoes.push_back(a1);
					this->condominio.getMoradores()[pos]->addPropriedade(a1);
				}
			}
			getline(myfile, line);
		}
		myfile.close();
		this->condominio.setHabitacoes(habitacoes);
		return true;
	} else {
		displayLogo();
		cout
				<< "ERRO: Ocorreu um problema ao aceder ao ficheiro de habitacoes.\n";
		pressEnterToContinue();
		return false;
	}
}
bool Main::exportHabitacoes() {
	ofstream myfile(pathHabitacoes, ios::trunc);

	if (myfile.is_open()) {
		for (size_t i = 0; i < this->condominio.getMoradores().size(); i++) {
			vector<Habitacao*> habitacoes =
					this->condominio.getMoradores()[i]->getHabitacoes();

			insertionSort(habitacoes);
			for (size_t j = 0; j < habitacoes.size(); j++) {
				Habitacao* habitacao =
						this->condominio.getMoradores()[i]->getHabitacoes()[j];
				myfile << habitacao->getTipo() << endl;
				myfile << habitacao->getMorada() << endl;
				myfile << habitacao->getCodigoPostal() << endl;
				myfile << habitacao->getNIFProprietario() << endl;
				for (size_t k = 0; k < 12; k++) {
					if (habitacao->getPago(k) == false)
						myfile << "0";
					else
						myfile << "1";
				}
				myfile << endl;
				if (habitacao->getTipo() == "Vivenda") {
					myfile << habitacao->getAreaInterior() << endl;
					myfile << habitacao->getAreaExterior() << endl;
					if (habitacao->getPiscina() == false)
						myfile << "0" << endl;
					else
						myfile << "1" << endl;
					myfile << endl;
				} else if (habitacao->getTipo() == "Apartamento") {
					myfile << habitacao->getTipologia() << endl;
					myfile << habitacao->getAreaInterior() << endl;
					myfile << habitacao->getPiso() << endl;
					myfile << endl;
				}
			}
		}
		myfile.close();
		return true;
	} else {
		displayLogo();
		cout
				<< "ERRO: Ocorreu um problema ao aceder ao ficheiro de habitacoes.\n";
		pressEnterToContinue();
		return false;
	}
}

// Extracts data from utilizadores.txt to create a vector of users.
bool Main::importUtilizadores() {
	ifstream myfile(pathUtilizadores);
	string line = "";
	string nomeUtilizador = "";
	string password = "";
	bool admin = false;

	vector<Utilizador> utilizadores;

	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			if (line == "1") {
				admin = true;
			} else if (line == "0") {
				admin = false;
			}
			getline(myfile, nomeUtilizador);
			getline(myfile, password);
			getline(myfile, line);
			Utilizador u = Utilizador(nomeUtilizador, password, admin);
			utilizadores.push_back(u);
		}
		myfile.close();
		this->setUtilizadores(utilizadores);
		return true;
	} else {
		displayLogo();
		cout
				<< "ERRO: Ocorreu um problema ao aceder ao ficheiro de utilizadores.\n";
		pressEnterToContinue();
		return false;
	}
}
bool Main::exportUtilizadores() {
	ofstream myfile(pathUtilizadores, ios::trunc);

	insertionSort(this->utilizadores);
	if (myfile.is_open()) {
		for (size_t i = 0; i < this->utilizadores.size(); i++) {
			if (this->utilizadores[i].isAdmin())
				myfile << "1" << endl;
			else
				myfile << "0" << endl;
			myfile << this->utilizadores[i].getNomeUtilizador() << endl;
			myfile << this->utilizadores[i].getPassword() << endl;
			myfile << endl;
		}
		myfile.close();
		return true;
	} else {
		displayLogo();
		cout
				<< "ERRO: Ocorreu um problema ao aceder ao ficheiro de utilizadores.\n";
		pressEnterToContinue();
		return false;
	}
}

int Main::exitFunction() {
	if (!this->exportUtilizadores() || !this->exportCondominos()
			|| !this->exportHabitacoes())
		return EXIT_FAILURE;
	else
		return EXIT_SUCCESS;
}

/*
 * Non-class functions
 */

// Checks if string has at least one space
bool hasWhitespace(string s) {
	for (size_t i = 0; i < s.size(); i++) {
		if (s[i] == ' ')
			return true;
	}
	return false;
}
// Checks if string is a positive integer
bool isNumber(string s) {
	string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it))
		++it;
	return (!s.empty() && it == s.end());
}
// Checks if string is a valid name:
// - Name must start with an uppercase letter;
// - No consecutive spaces;
// - Letter after space must be uppercase;
// - Name must end with a letter;
bool isName(string s) {
	if (s.empty() || islower(s[0]) || s[0] == ' ')
		return false;

	bool prevSpace = false;
	for (size_t i = 1; i < s.size(); i++) {
		if (prevSpace) {
			if (!isupper(s[i]))
				return false;
			else
				prevSpace = false;
		} else if (s[i] == ' ') {
			prevSpace = true;
		} else if (!islower(s[i]))
			return false;
	}

	if (s[s.size() - 1] == ' ')
		return false;
	return true;
}

// Displays the program logo
void displayLogo() {
	ifstream myfile(pathLogo);
	string line = "";
	clrscr();
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			setcolor(YELLOW, BLACK);
			cout << line << endl;
		}
		myfile.close();
		setcolor(WHITE, BLACK);
	} else {
		cout << "ERRO: Ocorreu um problema ao aceder ao ficheiro do logo."
				<< endl;
	}
}
// Get current date/time, format is HH:mm:ss
const string currentTime() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
//strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tstruct);
	strftime(buf, sizeof(buf), "%H:%M:%S", &tstruct);
	return buf;
}
// Waits until user presses Enter
void pressEnterToContinue() {
	cout << "Pressione ENTER para continuar." << endl;
	cin.ignore();
	fflush(stdin);
}

// Initializes vector<string> of months
void createMesesAno() {
	mesesAno.push_back("Janeiro");
	mesesAno.push_back("Fevereiro");
	mesesAno.push_back("Marco");
	mesesAno.push_back("Abril");
	mesesAno.push_back("Maio");
	mesesAno.push_back("Junho");
	mesesAno.push_back("Julho");
	mesesAno.push_back("Agosto");
	mesesAno.push_back("Setembro");
	mesesAno.push_back("Outubro");
	mesesAno.push_back("Novembro");
	mesesAno.push_back("Dezembro");
}
// Returns a vector with vectors of strings, containing the options for each menu.
void createMenuOptions() {
	vector<vector<string> > menuOptions;

	vector<string> menuInicial;
	menuOptions.push_back(menuInicial);

	menuOptions[0].push_back("Login");										//0
	menuOptions[0].push_back("Registo");									//1
	menuOptions[0].push_back("Sair");										//2

	vector<string> menuUtilizadorAdmin;
	menuOptions.push_back(menuUtilizadorAdmin);

	menuOptions[1].push_back("Menu Administrador");							//0
	menuOptions[1].push_back("Alterar dados da conta");						//1
	menuOptions[1].push_back("Ver dados de condomino");						//2
	menuOptions[1].push_back("Alterar dados de condomino");					//3
	menuOptions[1].push_back("Ver habitacoes possuidas");					//4
	menuOptions[1].push_back("Adicionar ou remover habitacao");				//5
	menuOptions[1].push_back("Requisitar um servico");						//6
	menuOptions[1].push_back("Sair");										//7

	vector<string> menuUtilizadorNormal;
	menuOptions.push_back(menuUtilizadorNormal);

	menuOptions[2].push_back("Alterar dados da conta");						//0
	menuOptions[2].push_back("Ver dados de condomino");						//1
	menuOptions[2].push_back("Alterar dados de condomino");					//2
	menuOptions[2].push_back("Ver habitacoes possuidas");					//3
	menuOptions[2].push_back("Adicionar ou remover habitacao");				//4
	menuOptions[2].push_back("Requisitar um servico");						//5
	menuOptions[2].push_back("Sair");										//6

	vector<string> menuDadosConta;
	menuOptions.push_back(menuDadosConta);

	menuOptions[3].push_back("Alterar nome de utilizador");					//0
	menuOptions[3].push_back("Alterar password");							//1
	menuOptions[3].push_back("Voltar atras");								//2

	vector<string> menuDadosCondomino;
	menuOptions.push_back(menuDadosCondomino);

	menuOptions[4].push_back("Alterar nome");								//0
	menuOptions[4].push_back("Alterar NIF");								//1
	menuOptions[4].push_back("Alterar fundos mensais");						//2
	menuOptions[4].push_back("Pagar divida");								//3
	menuOptions[4].push_back("Voltar atras");								//4

	vector<string> menuHabitacoesPossuidas;
	menuOptions.push_back(menuHabitacoesPossuidas);

	menuOptions[5].push_back("Ver informacao das habitacoes");				//0
	menuOptions[5].push_back("Alterar informacao de uma habitacao");		//1
	menuOptions[5].push_back("Ver estado da renda");						//2
	menuOptions[5].push_back("Voltar atras");								//3

	vector<string> menuRequisitarServico;
	menuOptions.push_back(menuRequisitarServico);

//
//
	menuOptions[6].push_back("Voltar atras");

	vector<string> menuAdmin;
	menuOptions.push_back(menuAdmin);

	menuOptions[7].push_back("Gerir utilizadores");							//0
	menuOptions[7].push_back("Gerir condominos");							//1
	menuOptions[7].push_back("Gerir habitacoes");							//2
	menuOptions[7].push_back("Gerir funcionarios");							//3
	menuOptions[7].push_back("Gerir servicos");								//4
	menuOptions[7].push_back("Fim do Mes");									//5
	menuOptions[7].push_back("Voltar atras");								//6

	vector<string> menuGerirUtilizadores;
	menuOptions.push_back(menuGerirUtilizadores);
	menuOptions[8].push_back("Ver lista de todos os utilizadores");			//0
	menuOptions[8].push_back("Alterar utilizador");							//1
	menuOptions[8].push_back("Adicionar utilizador");						//2
	menuOptions[8].push_back("Remover utilizador");							//3
	menuOptions[8].push_back("Voltar atras");								//4

	vector<string> menuGerirCondominos;
	menuOptions.push_back(menuGerirCondominos);
	menuOptions[9].push_back("Ver lista de todos os condominos");			//0
	menuOptions[9].push_back("Alterar condomino");							//1
	menuOptions[9].push_back("Adicionar condomino");						//2
	menuOptions[9].push_back("Remover condomino");							//3
	menuOptions[9].push_back("Voltar atras");								//4

	vector<string> menuGerirHabitacoes;
	menuOptions.push_back(menuGerirHabitacoes);
	menuOptions[10].push_back("Ver lista de todas as habitacoes");			//0
	menuOptions[10].push_back("Alterar habitacao");							//1
	menuOptions[10].push_back("Adicionar habitacao");						//2
	menuOptions[10].push_back("Remover habitacao");							//3
	menuOptions[10].push_back("Voltar atras");								//4

	vector<string> menuGerirFuncionarios;	//TODO acabar menuGerirFuncionarios
	menuOptions.push_back(menuGerirHabitacoes);
	menuOptions[11].push_back("Ver lista de todos os funcionarios");		//0
	menuOptions[11].push_back("Voltar atras");

	vector<string> menuGerirServicos;
	menuOptions.push_back(menuGerirHabitacoes);	//TODO acabar menuGerirServicos
	menuOptions[12].push_back("Ver lista de todos os servicos efectuados");	//0
	menuOptions[12].push_back("Ver lista de todos os servicos em curso");	//1
	menuOptions[12].push_back("Ver lista de todos os servicos em espera");	//2
	menuOptions[12].push_back("Voltar atras");

	vector<string> menuDadosContaUtilizador;
	menuOptions.push_back(menuDadosContaUtilizador);

	menuOptions[13].push_back("Alterar nome de utilizador");				//0
	menuOptions[13].push_back("Alterar password");							//1
	menuOptions[13].push_back("Alterar estado da conta");					//2
	menuOptions[13].push_back("Voltar atras");								//3

//
//

	menu = menuOptions;
}

// Main function
int main() {
	Main main = Main();

	createMesesAno();
	createMenuOptions();
	main.setMenus(menu);

	main.importUtilizadores();
	main.importCondominos();
	main.importHabitacoes();

	main.menuInicial();

	return main.exitFunction();
}


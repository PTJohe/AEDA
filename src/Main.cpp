#include "../headers/Main.h"

#include "../headers/Header.h"
#include "../headers/Utils.h"

#define pathLogo "../savedata/logo.txt"
#define pathCondominio "../savedata/condominio.txt"
#define pathCondominos "../savedata/condominos.txt"
#define pathHabitacoes "../savedata/habitacoes.txt"

const string currentTime();
void pressEnterToContinue();
bool compHabitacao(Habitacao* h1, Habitacao* h2);
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
void Main::setCurrentUser(Condomino condomino) {
	int pos = sequentialSearch(this->condominio.getMoradores(), condomino);
	if (pos == -1) {
		this->currentUser = NULL;
	} else
		this->currentUser = this->condominio.getCondomino(pos);
}

// Resets menu option. Called every time we switch to a new menu.
void Main::resetOption() {
	this->option = 0;
}
// Prints a Yes/No select screen at position (x,y);
bool Main::displayYesNo(int option) {
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

bool Main::displaySelectCondomino() {
	if (option >= this->condominio.getMoradores().size()) {
		return EXIT_FAILURE;
	}
	for (size_t i = 0; i < this->condominio.getMoradores().size(); i++) {
		gotoxy(0, 14 + i);
		if (i == option) {
			setcolor(BLACK, LIGHTGREY);
			cout << left << setw(10) << setfill(' ')
					<< this->condominio.getMoradores()[i].getNomeUtilizador()
					<< " - " << left << setw(20) << setfill(' ')
					<< this->condominio.getMoradores()[i].getNomeCivil() << left
					<< setw(10) << setfill(' ') << " - "
					<< this->condominio.getMoradores()[i].getNIF() << endl;
			setcolor(WHITE, BLACK);
		} else {
			cout << left << setw(10) << setfill(' ')
					<< this->condominio.getMoradores()[i].getNomeUtilizador()
					<< " - " << left << setw(20) << setfill(' ')
					<< this->condominio.getMoradores()[i].getNomeCivil() << left
					<< setw(10) << setfill(' ') << " - "
					<< this->condominio.getMoradores()[i].getNIF() << endl;
		}
	}
	return EXIT_SUCCESS;
}
bool Main::displaySelectHabitacao() {
	if (option >= this->condominio.getHabitacoes().size()) {
		return EXIT_FAILURE;
	}
	for (size_t i = 0; i < this->condominio.getHabitacoes().size(); i++) {
		gotoxy(0, 14 + i);
		if (i == option) {
			setcolor(BLACK, LIGHTGREY);
			cout << left << setw(12) << setfill(' ')
					<< this->condominio.getHabitacoes()[i]->getTipo() << " - "
					<< this->condominio.getHabitacoes()[i]->calcRenda() << "$"
					<< left << setw(10) << setfill(' ') << " - "
					<< this->condominio.getHabitacoes()[i]->getNIFProprietario()
					<< endl;
			setcolor(WHITE, BLACK);
		} else {
			cout << left << setw(12) << setfill(' ')
					<< this->condominio.getHabitacoes()[i]->getTipo() << " - "
					<< this->condominio.getHabitacoes()[i]->calcRenda() << "$"
					<< left << setw(10) << setfill(' ') << " - "
					<< this->condominio.getHabitacoes()[i]->getNIFProprietario()
					<< endl;
		}
	}
	return EXIT_SUCCESS;

}
bool Main::displaySelectHabitacaoPossuida() {
	if (option >= this->currentUser->getHabitacoes().size()) {
		return EXIT_FAILURE;
	}
	for (size_t i = 0; i < this->currentUser->getHabitacoes().size(); i++) {
		gotoxy(0, 14 + i);
		if (i == option) {
			setcolor(BLACK, LIGHTGREY);
			cout << left << setw(12) << setfill(' ')
					<< this->currentUser->getHabitacoes()[i]->getTipo() << " - "
					<< this->currentUser->getHabitacoes()[i]->calcRenda() << "$"
					<< left << setw(10) << setfill(' ') << " - "
					<< this->currentUser->getHabitacoes()[i]->getMorada()
					<< endl;
			setcolor(WHITE, BLACK);
		} else {
			cout << left << setw(12) << setfill(' ')
					<< this->currentUser->getHabitacoes()[i]->getTipo() << " - "
					<< this->currentUser->getHabitacoes()[i]->calcRenda() << "$"
					<< left << setw(10) << setfill(' ') << " - "
					<< this->currentUser->getHabitacoes()[i]->getMorada()
					<< endl;
		}
	}
	return EXIT_SUCCESS;
}
// Checks if the user exists and, if so, updates currentUser.
bool Main::validLogin(string utilizador, string password) {
	Condomino c1 = Condomino(utilizador, password);
	int pos = sequentialSearch(this->condominio.getMoradores(), c1);
	if (pos == -1)
		return false;
	if (this->condominio.getMoradores()[pos].getPassword() != password)
		return false;
	setCurrentUser(c1);
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
	Condomino c1 = Condomino(utilizador, password);
	int pos = sequentialSearch(this->condominio.getMoradores(), c1);
	if (pos == -1)
		return true;
	else {
		cout << "\nO nome de utilizador nao esta disponivel." << endl;
		return false;
	}
}

bool Main::editDadosConta(int editOption) {
	displayLogo();
	gotoxy(0, 8);
	if (editOption == 0) {
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

			Condomino c1 = Condomino(this->currentUser->getNomeUtilizador(),
					this->currentUser->getPassword());
			this->condominio.sortMoradores();
			int pos = sequentialSearch(this->condominio.getMoradores(), c1);
			this->currentUser = &this->condominio.getMoradores()[pos];

			cout << "\nNome de utilizador alterado." << endl;
			pressEnterToContinue();
			return true;
		} else
			pressEnterToContinue();
		return false;
	} else if (editOption == 1) {
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

bool Main::editDadosContaAdmin(int editOption, Condomino &condomino) {
	displayLogo();
	gotoxy(0, 8);
	if (editOption == 0) {
		cout << "Alterar nome de utilizador:\n" << endl;
		string utilizadorActual = condomino.getNomeUtilizador();
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
		if (validRegister(utilizadorNovo, condomino.getPassword())) {
			this->condominio.setNomeUtilizador(condomino, utilizadorNovo);
			condomino.setNomeUtilizador(utilizadorNovo);

			Condomino c1 = Condomino(this->currentUser->getNomeUtilizador(),
					this->currentUser->getPassword());
			this->condominio.sortMoradores();
			this->setCurrentUser(c1);

			cout << "\nNome de utilizador alterado." << endl;
			pressEnterToContinue();
			return true;

		} else
			pressEnterToContinue();
		return false;
	} else if (editOption == 1) {
		cout << "Alterar password:\n" << endl;
		string passwordActual = condomino.getPassword();
		string passwordNova = "";
		cout << "Introduza a nova password: ";
		getline(cin, passwordNova);
		if (passwordActual == passwordNova) {
			cout << "\nNao foi possivel alterar a password." << endl;
			cout << "A nova password tem que ser diferente da actual." << endl;
			pressEnterToContinue();
			return false;
		}
		if (validRegister(condomino.getNomeUtilizador(), passwordNova)) {
			this->condominio.setPassword(condomino, passwordNova);
			cout << "\nPassword alterada." << endl;
			pressEnterToContinue();
			return true;
		}
	} else if (editOption == 2) {
		cout << "Alterar estado de administrador:\n" << endl;
		string admin = "";
		if (condomino.isAdmin())
			admin = "ADMIN";
		else
			admin = "Conta normal";
		cout << "Estado anterior = " << admin << endl;
		if (condomino == *(this->currentUser)) {
			cout << "\nNao foi possivel alterar o estado da conta." << endl;
			cout
					<< "Nao e possivel revogar direitos administrativos do proprio utilizador."
					<< endl;
			pressEnterToContinue();
			return false;
		} else if (condomino.isAdmin()) {
			cout
					<< "Tem a certeza que pretende revogar os direitos administrativos do condomino?"
					<< endl;
		} else {
			cout
					<< "Tem a certeza que pretente tornar este condomino administrador?"
					<< endl;
		}
		displayYesNo(option);

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
				if (condomino.isAdmin()) {
					this->condominio.setAdmin(condomino, false);
					cout << "\nO condomino deixou de ser administrador."
							<< endl;
				} else {
					this->condominio.setAdmin(condomino, true);
					cout << "\nO condomino passou a ser administrador." << endl;
				}
				pressEnterToContinue();
				resetOption();
				return true;
			} else if (option == 1) {
				resetOption();
				return false;
			}
			break;
		case KEY_ESC:
			resetOption();
			return menuGerirCondominos();
			break;
		default:
			break;
		}
		return editDadosContaAdmin(editOption, condomino);
	}
	return false;
}

bool Main::editDadosCondomino(int editOption) {
	displayLogo();
	gotoxy(0, 8);
	if (editOption == 0) {
		cout << "Alterar nome civil:\n" << endl;
		string nomeActual = this->currentUser->getNomeCivil();
		cout << "Nome civil actual: " << nomeActual << endl;
		string nomeNovo = "";
		cout << "Introduza o novo nome civil: ";
		getline(cin, nomeNovo);
		if (!isName(nomeNovo)) {
			cout << "\nNao foi possivel alterar o nome civil." << endl;
			cout << "O nome civil que introduziu nao e valido." << endl;
			pressEnterToContinue();
			return false;
		}
		this->currentUser->setNomeCivil(nomeNovo);
		cout << this->currentUser->getNomeCivil() << endl;
		cout << "\nNome civil alterado." << endl;
		pressEnterToContinue();
		return true;
	} else if (editOption == 1) {
		cout << "Alterar NIF:\n" << endl;
		string nifActual = this->currentUser->getNIF();
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
		Condomino c1 = Condomino("nome", nifNovo);
		int pos1 = sequentialSearch(this->condominio.getMoradores(), c1);
		if (pos1 != -1) {
			cout << "\nNao foi possivel alterar o NIF." << endl;
			cout << "O NIF ja pertence a outro condomino." << endl;
			pressEnterToContinue();
			return false;
		}
		this->currentUser->setNIF(nifNovo);
		cout << this->currentUser->getNIF() << endl;
		cout << "\nNIF alterado." << endl;
		pressEnterToContinue();
		return true;

	} else if (editOption == 2) {
		cout << "Alterar fundos mensais:\n" << endl;
		long int fundosActuais = this->currentUser->getFundosMensais();
		cout << "Fundos mensais actuais: " << fundosActuais << endl;
		string novosFundos = "";
		cout << "Introduza os novos fundos mensais: ";
		getline(cin, novosFundos);
		if (novosFundos.size() > 9 || !isNumber(novosFundos)) {
			cout << "\nNao foi possivel alterar os fundos mensais." << endl;
			cout << "Os fundos mensais tem que ser um inteiro positivo."
					<< endl;
			pressEnterToContinue();
			return false;
		}
		long int fundosMensais = atoi(novosFundos.c_str());
		this->currentUser->setFundosMensais(fundosMensais);
		cout << "\nFundos Mensais alterados." << endl;
		pressEnterToContinue();
		return true;
	} else if (editOption == 3) {
		if (this->currentUser->getDivida() == 0) {
			cout << "\nNao foi possivel saldar a divida" << endl;
			cout << "O condomino nao tem divida." << endl;
			pressEnterToContinue();
			return false;
		}
		cout << "Pretende saldar a divida?";
		long int dividaActual = this->currentUser->getDivida();
		cout << "Divida actual = " << dividaActual << endl;
	}
	return false;
}
bool Main::editDadosCondominoAdmin(int editOption, Condomino &condomino) {
	displayLogo();
	gotoxy(0, 8);
	if (editOption == 0) {
		cout << "Alterar nome civil:\n" << endl;
		string nomeActual = condomino.getNomeCivil();
		cout << "Nome civil actual: " << nomeActual << endl;
		string nomeNovo = "";
		cout << "Introduza o novo nome civil: ";
		getline(cin, nomeNovo);
		if (!isName(nomeNovo)) {
			cout << "\nNao foi possivel alterar o nome civil." << endl;
			cout << "O nome civil que introduziu nao e valido." << endl;
			pressEnterToContinue();
			return false;
		}
		this->condominio.setNomeCivil(condomino, nomeNovo);
		cout << "\nNome civil alterado." << endl;
		pressEnterToContinue();
		return true;
	} else if (editOption == 1) {
		cout << "Alterar NIF:\n" << endl;
		string nifActual = condomino.getNIF();
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
		Condomino c1 = Condomino("nome", nifNovo);
		int pos1 = sequentialSearch(this->condominio.getMoradores(), c1);
		if (pos1 != -1) {
			cout << "\nNao foi possivel alterar o NIF." << endl;
			cout << "O NIF ja pertence a outro condomino." << endl;
			pressEnterToContinue();
			return false;
		}
		this->condominio.setNIF(condomino, nifNovo);
		cout << "\nNIF alterado." << endl;
		pressEnterToContinue();
		return true;

	} else if (editOption == 2) {
		cout << "Alterar fundos mensais:\n" << endl;
		long int fundosActuais = condomino.getFundosMensais();
		cout << "Fundos mensais actuais: " << fundosActuais << endl;
		string novosFundos = "";
		cout << "Introduza os novos fundos mensais: ";
		getline(cin, novosFundos);
		if (novosFundos.size() > 9 || !isNumber(novosFundos)) {
			cout << "\nNao foi possivel alterar os fundos mensais." << endl;
			cout << "Os fundos mensais tem que ser um inteiro positivo."
					<< endl;
			pressEnterToContinue();
			return false;
		}
		long int fundosMensais = atoi(novosFundos.c_str());
		this->condominio.setFundosMensais(condomino, fundosMensais);
		cout << "\nFundos Mensais alterados." << endl;
		pressEnterToContinue();
		return true;
	} else if (editOption == 3) {
		if (condomino.getDivida() == 0) {
			cout << "\nNao foi possivel saldar a divida" << endl;
			cout << "O condomino nao tem divida." << endl;
			pressEnterToContinue();
			return false;
		}
		cout << "Pretende saldar a divida?";
		long int dividaActual = condomino.getDivida();
		cout << "Divida actual = " << dividaActual << endl;

		displayYesNo(option);

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
				this->condominio.saldarDivida(condomino);
				cout << "\nDivida saldada." << endl;
				resetOption();
				pressEnterToContinue();
				return true;
			} else if (option == 1) {
				resetOption();
				return false;
			}
			break;
		case KEY_ESC:
			resetOption();
			return false;
			break;
		default:
			break;
		}
		return editDadosCondominoAdmin(editOption, condomino);
	}
	return false;
}

void Main::displayCurrentUserInfoConta() {
	displayLogo();
	gotoxy(0, 8);
	cout << "DADOS:\n" << endl;
	this->currentUser->infoConta();
	pressEnterToContinue();
}
void Main::displayCurrentUserInfoCondomino() {
	displayLogo();
	gotoxy(0, 8);
	cout << "DADOS:\n" << endl;
	(*this->currentUser).infoCondomino();
	pressEnterToContinue();
}
void Main::displayCurrentUserHabitacao(int pos) {
	displayLogo();
	gotoxy(0, 8);
	cout << "DADOS DA HABITACAO\n" << endl;
	cout << "Tipo: ";
	this->currentUser->getHabitacoes()[pos]->info();

	pressEnterToContinue();
}

void Main::displayCurrentUserRenda() {
	displayLogo();
	gotoxy(0, 8);
	cout << "Mes actual -> ";
	setcolor(YELLOW, BLACK);
	cout << mesesAno[this->condominio.getMes()] << endl << endl;
	setcolor(WHITE, BLACK);
	this->currentUser->infoRenda();
	cout << endl;
	pressEnterToContinue();
}

void Main::displayCondominoInfo(int pos) {
	displayLogo();
	gotoxy(0, 8);
	cout << "DADOS DO CONDOMINO\n" << endl;
	cout << "Nome Utilizador: "
			<< this->condominio.getMoradores()[pos].getNomeUtilizador() << endl
			<< endl;
	cout << "Nome Civil: ";
	this->condominio.getMoradores()[pos].infoCondomino();
	cout << endl;
	pressEnterToContinue();
}
void Main::displayHabitacaoInfo(int pos) {
	displayLogo();
	gotoxy(0, 8);
	cout << "DADOS DA HABITACAO" << endl;
	cout << "Tipo: ";
	this->condominio.getHabitacoes()[pos]->info();

	if (this->condominio.getHabitacoes()[pos]->hasProprietario()) {
		Condomino c1 = Condomino("nome", "password", "nomeCivil",
				this->condominio.getHabitacoes()[pos]->getNIFProprietario());
		int pos2 = sequentialSearch(this->condominio.getMoradores(), c1);

		cout << "PROPRIETARIO" << endl;
		cout << "Nome: " << this->condominio.getMoradores()[pos2].getNomeCivil()
				<< endl;
		cout << "NIF: " << this->condominio.getMoradores()[pos2].getNIF()
				<< endl;
	}
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
		Condomino c1 = Condomino(utilizador, password);
		this->condominio.addMorador(c1);
		cout << "\nConta criada com sucesso!" << endl;
	} else {
		cout << "Nao foi possivel criar uma conta." << endl;
	}
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
				return menuEditDadosConta(*(this->currentUser));
			} else if (option == 2) {
				displayCurrentUserInfoCondomino();
			} else if (option == 3) {
				resetOption();
				return menuEditDadosCondomino(*(this->currentUser));
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
				return menuEditDadosConta(*(this->currentUser));
			} else if (option == 1) {
				displayCurrentUserInfoCondomino();
			} else if (option == 2) {
				resetOption();
				return menuEditDadosCondomino(*(this->currentUser));
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
int Main::menuEditDadosConta(Condomino &condomino) {
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
		} else if (option == 2) {
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
	return menuEditDadosConta(condomino);
}
int Main::menuEditDadosCondomino(Condomino &condomino) {
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
			resetOption();
			editDadosCondomino(0);
			return menuUtilizador();
		} else if (option == 1) {
			resetOption();
			editDadosCondomino(1);
			return menuUtilizador();
		} else if (option == 2) {
			resetOption();
			editDadosCondomino(2);
			return menuUtilizador();
		} else if (option == 3) {
			resetOption();
			editDadosCondomino(3);
			return menuUtilizador();
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
	cout << "HABITACOES POSSUIDAS\n" << endl;
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
			resetOption();
			return menuSelectHabitacoesPossuida(false);
		} else if (option == 1) {
			displayCurrentUserRenda();
		} else if (option == 2) {
			resetOption();
			return menuSelectHabitacoesPossuida(true);
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
int Main::menuSelectHabitacoesPossuida(bool remover) {
	displayLogo();
	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "SELECIONE A HABITACAO:\n" << endl;
	if (remover)
		cout << "[ENTER] Remover" << endl;
	else
		cout << "[ENTER] Ver dados" << endl;
	cout << "[ESC] Voltar atras\n" << endl;
	cout << "Habitacao      Renda         Morada" << endl;

	if (this->currentUser->getHabitacoes().empty()) {
		cout << "Nao possui habitacoes.\n" << endl;
		pressEnterToContinue();
		resetOption();
		return menuHabitacoesPossuidas();
	}
	displaySelectHabitacaoPossuida();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < this->currentUser->getHabitacoes().size())
			option++;
		break;
	case KEY_ENTER:
		if (!remover)
			displayCurrentUserHabitacao(option);
		else {
			menuDeleteHabitacaoPossuida(option, 0);
			resetOption();
		}
		break;
	case KEY_ESC:
		resetOption();
		return menuHabitacoesPossuidas();
		break;
	default:
		break;
	}
	return menuSelectHabitacoesPossuida(remover);
}

int Main::menuDeleteHabitacaoPossuida(int pos, int menuOption) {
	displayLogo();
	gotoxy(0, 8);
	cout << "DADOS DA HABITACAO\n" << endl;
	cout << "Tipo: ";
	this->currentUser->getHabitacoes()[pos]->info();

	cout << "Tem a certeza que deseja remover esta habitacao?" << endl;
	displayYesNo(menuOption);

	int c = getch();
	switch (c) {
	case KEY_LEFT:
		if (menuOption - 1 >= 0)
			menuOption--;
		break;
	case KEY_RIGHT:
		if (menuOption + 1 < 2)
			menuOption++;
		break;
	case KEY_ENTER:
		if (option == 0) {
			this->condominio.eraseHabitacao(*currentUser, pos);
			cout << "\nHabitacao removida." << endl;
			if (this->option > 0)
				option--;
			pressEnterToContinue();
			return menuSelectHabitacoesPossuida(true);
		} else if (option == 1) {
			resetOption();
		}
		break;
	default:
		break;
	}
	return menuDeleteHabitacaoPossuida(pos, menuOption);
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
			return menuGerirCondominos();
		} else if (option == 1) {
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

int Main::menuGerirCondominos() {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "GERIR CONDOMINOS" << endl;
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
		if (option == 0) //Ver lista de condominos
			return menuDisplayAllCondominos();
		else if (option == 1) { //Alterar dados de um condomino
			resetOption();
			return menuSelectCondomino(false);
		} else if (option == 2) { //Adicionar condomino
			resetOption();
			Condomino c1 = *currentUser;
			menuRegisto();
			setCurrentUser(c1);
			return menuGerirCondominos();
		} else if (option == 3) { //Remover condomino
			resetOption();
			return menuSelectCondomino(true);
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
	return menuGerirCondominos();
}
int Main::menuDisplayAllCondominos() {
	displayLogo();
	gotoxy(0, 8);
	cout << "LISTA DE CONDOMINOS:" << endl;
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "SELECIONE O UTILIZADOR:\n" << endl;
	cout << "[ENTER] Ver dados" << endl;
	cout << "[ESC] Voltar atras\n" << endl;
	cout << "Utilizador   Nome Civil                    NIF" << endl;
	displaySelectCondomino();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < this->condominio.getMoradores().size())
			option++;
		break;
	case KEY_ENTER:
		displayCondominoInfo(option);
		break;
	case KEY_ESC:
		resetOption();
		return menuGerirCondominos();
		break;
	default:
		break;
	}

	return menuDisplayAllCondominos();
}
int Main::menuSelectCondomino(bool remover) {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "SELECIONE O UTILIZADOR:\n" << endl;
	if (remover)
		cout << "[ENTER] Remover condomino" << endl;
	else
		cout << "[ENTER] Alterar dados" << endl;
	cout << "[ESC] Voltar atras\n" << endl;
	cout << "Utilizador   Nome Civil                    NIF" << endl;
	displaySelectCondomino();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < this->condominio.getMoradores().size())
			option++;
		break;
	case KEY_ENTER:
		if (!remover) {
			int pos = option;
			resetOption();
			return menuEditCondomino(this->condominio.getMoradores()[pos]);
		} else {
			return menuDeleteCondomino(this->condominio.getMoradores()[option],
					0);
		}
		break;
	case KEY_ESC:
		resetOption();
		return menuGerirCondominos();
		break;
	default:
		break;
	}

	return menuSelectCondomino(remover);

}
int Main::menuEditCondomino(Condomino &condomino) {
	displayLogo();

	gotoxy(10, 6);
	cout << "Condomino a alterar -> ";
	setcolor(YELLOW, BLACK);
	cout << condomino.getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "ALTERAR DADOS\n" << endl;
	displayMenuOptions(12);

	displayTime();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < menu[12].size())
			option++;
		break;
	case KEY_ENTER:
		if (option == 0) {
			resetOption();
			editDadosContaAdmin(0, condomino); //Alterar nome de utilizador
		} else if (option == 1) {
			resetOption();
			editDadosContaAdmin(1, condomino); //Alterar password
		} else if (option == 2) {
			resetOption();
			editDadosContaAdmin(2, condomino); //Alterar direitos administrativos
		} else if (option == 3) {
			resetOption();
			editDadosCondominoAdmin(0, condomino); //Alterar nome civil
		} else if (option == 4) {
			resetOption();
			editDadosCondominoAdmin(1, condomino); //Alterar NIF
		} else if (option == 5) {
			resetOption();
			editDadosCondominoAdmin(2, condomino); //Alterar fundos mensais
		} else if (option == 6) {
			resetOption();
			editDadosCondominoAdmin(3, condomino); //Saldar divida
		} else {
			resetOption();
			return menuGerirCondominos();
		}
		break;
	case KEY_ESC:
		resetOption();
		return menuGerirCondominos();
		break;
	default:
		break;
	}
	return menuEditCondomino(condomino);
}
int Main::menuDeleteCondomino(Condomino &condomino, int menuOption) {
	displayLogo();
	gotoxy(0, 8);
	cout << "DADOS DO CONDOMINO A REMOVER:\n" << endl;
	cout << "Nome de utilizador - " << condomino.getNomeUtilizador() << endl;
	cout << "\nDados do condomino:" << endl;
	condomino.infoCondomino();

	bool sameUser = false;
	if (*(this->currentUser) == condomino)
		sameUser = true;
	if (sameUser)
		cout << "Tem a certeza que pretende remover a sua conta?" << endl;
	else
		cout << "Tem a certeza que pretende remover este condomino?" << endl;
	displayYesNo(menuOption);

	int c = getch();
	switch (c) {
	case KEY_LEFT:
		if (menuOption - 1 >= 0)
			menuOption--;
		break;
	case KEY_RIGHT:
		if (menuOption + 1 < 2)
			menuOption++;
		break;
	case KEY_ENTER:
		if (menuOption == 0) {
			Condomino c1 = *currentUser;
			if (this->condominio.eraseMorador(condomino))
				cout << "\nUtilizador removido." << endl;
			setCurrentUser(c1);
			pressEnterToContinue();
			resetOption();
			if (sameUser)
				return menuInicial();
			else {
				if (this->option > 0)
					option--;
				return menuSelectCondomino(true);
			}
		} else if (menuOption == 1) {
			return menuSelectCondomino(true);
		}
		break;
	case KEY_ESC:
		resetOption();
		return menuGerirCondominos();
		break;
	default:
		break;
	}
	return menuDeleteCondomino(condomino, menuOption);
}

int Main::menuGerirHabitacoes() {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "GERIR HABITACOES" << endl;
	displayMenuOptions(9);

	displayTime();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < menu[9].size())
			option++;
		break;
	case KEY_ENTER:
		if (option == 0) //Ver lista de habitacoes
			return menuDisplayAllHabitacoes();
		else if (option == 1) { //Alterar dados de uma habitacao
			resetOption();
			return menuSelectHabitacao(true);
		} else if (option == 2) { //Adicionar habitacao
			resetOption();
			return menuGerirHabitacoes();
		} else if (option == 3) { //Remover habitacao
			resetOption();
			return menuSelectHabitacao(false);
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
	return menuGerirHabitacoes();
}
int Main::menuDisplayAllHabitacoes() {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "SELECIONE A HABITACAO:\n" << endl;
	cout << "[ENTER] Ver dados" << endl;
	cout << "[ESC] Voltar atras\n" << endl;
	cout << "Habitacao      Renda         NIF Proprietario" << endl;
	displaySelectHabitacao();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < this->condominio.getHabitacoes().size())
			option++;
		break;
	case KEY_ENTER:
		displayHabitacaoInfo(option);
		break;
	case KEY_ESC:
		resetOption();
		return menuGerirHabitacoes();
		break;
	default:
		break;
	}
	return menuDisplayAllHabitacoes();
}
int Main::menuSelectHabitacao(bool editar) {

}
int Main::menuEditHabitacao(Habitacao* habitacao) {

}
int Main::menuDeleteHabitacao(Habitacao* habitacao) {

}
int Main::menuGerirFuncionarios() {
	return EXIT_FAILURE;
} //TODO menuGerirFuncionarios()
int Main::menuGerirServicos() {
	return EXIT_FAILURE;
} //TODO menuGerirServicos()

// Extracts data from condominio.txt to create condominio
bool Main::importCondominio() {
	ifstream myfile(pathCondominio);
	string line = "";
	long int fundos = 0;
	int currentMes = 0;

	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			fundos = atol(line.c_str());
			getline(myfile, line);
			currentMes = atoi(line.c_str());
			this->condominio.setFundos(fundos);
			this->condominio.setCurrentMes(currentMes);
		}
		myfile.close();
		return true;
	} else {
		displayLogo();
		cout
				<< "ERRO: Ocorreu um problema ao aceder ao ficheiro do condominio.\n";
		pressEnterToContinue();
		return false;
	}
}
bool Main::exportCondominio() {
	ofstream myfile(pathCondominio);

	if (myfile.is_open()) {
		myfile << this->condominio.getFundos() << endl;
		myfile << this->condominio.getMes() << endl;
		myfile.close();
		return true;
	} else {
		displayLogo();
		cout
				<< "ERRO: Ocorreu um problema ao aceder ao ficheiro do condominio.\n";
		pressEnterToContinue();
		return false;
	}
}

// Extracts data from condominos.txt to create a vector of condominos
bool Main::importCondominos() {
	ifstream myfile(pathCondominos);
	string line = "";
	bool admin = false;
	string nomeUtilizador = "";
	string password = "";
	string nomeCivil = "";
	string NIF = "";
	long int fundosMensais = 0;
	long int divida = 0;

	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			if (line == "1") {
				admin = true;
			} else if (line == "0") {
				admin = false;
			}
			getline(myfile, nomeUtilizador);
			getline(myfile, password);
			getline(myfile, nomeCivil);
			getline(myfile, NIF);
			getline(myfile, line);
			fundosMensais = atol(line.c_str());
			getline(myfile, line);
			divida = atol(line.c_str());
			Condomino c1 = Condomino(nomeUtilizador, password, admin, nomeCivil,
					NIF, fundosMensais, divida);
			this->condominio.addMorador(c1);
			getline(myfile, line);
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
bool Main::exportCondominos() {
	ofstream myfile(pathCondominos, ios::trunc);

	if (myfile.is_open()) {
		for (size_t i = 0; i < this->condominio.getMoradores().size(); i++) {
			if (this->condominio.getMoradores()[i].isAdmin())
				myfile << "1" << endl;
			else
				myfile << "0" << endl;
			myfile << this->condominio.getMoradores()[i].getNomeUtilizador()
					<< endl;
			myfile << this->condominio.getMoradores()[i].getPassword() << endl;
			myfile << this->condominio.getMoradores()[i].getNomeCivil() << endl;
			myfile << this->condominio.getMoradores()[i].getNIF() << endl;
			myfile << this->condominio.getMoradores()[i].getFundosMensais()
					<< endl;
			myfile << this->condominio.getMoradores()[i].getDivida() << endl;
			myfile << endl;
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

// Extracts data from habitacoes.txt to create vector of habitacoes
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

				Vivenda* v1 = new Vivenda(morada, codigoPostal, nifProprietario,
						pago, areaInterior, areaExterior, piscina);
				habitacoes.push_back(v1);
			} else if (tipo == "Apartamento") {
				getline(myfile, line);
				tipologia = atoi(line.c_str());
				getline(myfile, line);
				areaInterior = atof(line.c_str());
				getline(myfile, line);
				piso = atoi(line.c_str());
				Apartamento* a1 = new Apartamento(morada, codigoPostal,
						nifProprietario, pago, tipologia, areaInterior, piso);
				habitacoes.push_back(a1);
			}
			getline(myfile, line);
		}
		myfile.close();
		sort(habitacoes.begin(), habitacoes.end(), compHabitacao);
		this->condominio.setHabitacoes(habitacoes);
		this->condominio.updateHabitacoesCondominos();
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
		vector<Habitacao*> habitacoes = this->condominio.getHabitacoes();
		//insertionSort(habitacoes);
		//this->condominio.setHabitacoes(habitacoes);

		for (size_t j = 0; j < habitacoes.size(); j++) {
			myfile << habitacoes[j]->getTipo() << endl;
			myfile << habitacoes[j]->getMorada() << endl;
			myfile << habitacoes[j]->getCodigoPostal() << endl;
			myfile << habitacoes[j]->getNIFProprietario() << endl;
			for (size_t k = 0; k < 12; k++) {
				if (habitacoes[j]->getPago(k) == false)
					myfile << "0";
				else
					myfile << "1";
			}
			myfile << endl;
			if (habitacoes[j]->getTipo() == "Vivenda") {
				myfile << habitacoes[j]->getAreaInterior() << endl;
				myfile << habitacoes[j]->getAreaExterior() << endl;
				if (habitacoes[j]->getPiscina() == false)
					myfile << "0" << endl;
				else
					myfile << "1" << endl;
				myfile << endl;
			} else if (habitacoes[j]->getTipo() == "Apartamento") {
				myfile << habitacoes[j]->getTipologia() << endl;
				myfile << habitacoes[j]->getAreaInterior() << endl;
				myfile << habitacoes[j]->getPiso() << endl;
				myfile << endl;
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

int Main::exitFunction() {
	if (!this->exportCondominio() || !this->exportCondominos()
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
	menuOptions[1].push_back("Adicionar habitacao");						//5
	menuOptions[1].push_back("Requisitar um servico");						//6
	menuOptions[1].push_back("Sair");										//7

	vector<string> menuUtilizadorNormal;
	menuOptions.push_back(menuUtilizadorNormal);

	menuOptions[2].push_back("Alterar dados da conta");						//0
	menuOptions[2].push_back("Ver dados de condomino");						//1
	menuOptions[2].push_back("Alterar dados de condomino");					//2
	menuOptions[2].push_back("Ver habitacoes possuidas");					//3
	menuOptions[2].push_back("Adicionar habitacao");						//4
	menuOptions[2].push_back("Requisitar um servico");						//5
	menuOptions[2].push_back("Sair");										//6

	vector<string> menuDadosConta;
	menuOptions.push_back(menuDadosConta);

	menuOptions[3].push_back("Alterar nome de utilizador");					//0
	menuOptions[3].push_back("Alterar password");							//1
	menuOptions[3].push_back("Voltar atras");								//2

	vector<string> menuDadosCondomino;
	menuOptions.push_back(menuDadosCondomino);

	menuOptions[4].push_back("Alterar nome civil");							//0
	menuOptions[4].push_back("Alterar NIF");								//1
	menuOptions[4].push_back("Alterar fundos mensais");						//2
	menuOptions[4].push_back("Saldar divida");								//3
	menuOptions[4].push_back("Voltar atras");								//4

	vector<string> menuHabitacoesPossuidas;
	menuOptions.push_back(menuHabitacoesPossuidas);

	menuOptions[5].push_back("Ver informacao das habitacoes");				//0
	menuOptions[5].push_back("Ver estado da renda");						//1
	menuOptions[5].push_back("Remover habitacao");							//2
	menuOptions[5].push_back("Voltar atras");								//3

	vector<string> menuRequisitarServico;
	menuOptions.push_back(menuRequisitarServico);

	menuOptions[6].push_back("Voltar atras");

	vector<string> menuAdmin;
	menuOptions.push_back(menuAdmin);

	menuOptions[7].push_back("Gerir condominos");							//0
	menuOptions[7].push_back("Gerir habitacoes");							//1
	menuOptions[7].push_back("Gerir funcionarios");							//2
	menuOptions[7].push_back("Gerir servicos");								//3
	menuOptions[7].push_back("Fim do Mes");									//4
	menuOptions[7].push_back("Voltar atras");								//5

	vector<string> menuGerirCondominos;
	menuOptions.push_back(menuGerirCondominos);
	menuOptions[8].push_back("Ver lista de todos os condominos");			//0
	menuOptions[8].push_back("Alterar condomino");							//1
	menuOptions[8].push_back("Adicionar condomino");						//2
	menuOptions[8].push_back("Remover condomino");							//2
	menuOptions[8].push_back("Voltar atras");								//3

	vector<string> menuGerirHabitacoes;
	menuOptions.push_back(menuGerirHabitacoes);
	menuOptions[9].push_back("Ver lista de todas as habitacoes");			//0
	menuOptions[9].push_back("Alterar habitacao");							//1
	menuOptions[9].push_back("Adicionar habitacao");						//2
	menuOptions[9].push_back("Remover habitacao");							//3
	menuOptions[9].push_back("Voltar atras");								//4

	vector<string> menuGerirFuncionarios;	//TODO acabar menuGerirFuncionarios
	menuOptions.push_back(menuGerirFuncionarios);
	menuOptions[10].push_back("Ver lista de todos os funcionarios");		//0
	menuOptions[10].push_back("Alterar funcionario");						//1
	menuOptions[10].push_back("Adicionar funcionarios");					//2
	menuOptions[10].push_back("Remover funcionarios");						//3
	menuOptions[10].push_back("Voltar atras");								//4

	vector<string> menuGerirServicos;
	menuOptions.push_back(menuGerirServicos);	//TODO acabar menuGerirServicos
	menuOptions[11].push_back("Ver lista de todos os servicos efectuados");	//0
	menuOptions[11].push_back("Ver lista de todos os servicos em curso");	//1
	menuOptions[11].push_back("Ver lista de todos os servicos em espera");	//2
	menuOptions[11].push_back("Voltar atras");

	vector<string> menuDadosContaCondomino;
	menuOptions.push_back(menuDadosContaCondomino);

	menuOptions[12].push_back("Alterar nome de utilizador");				//0
	menuOptions[12].push_back("Alterar password");							//1
	menuOptions[12].push_back("Alterar estado da conta");					//2
	menuOptions[12].push_back("Alterar nome civil");						//3
	menuOptions[12].push_back("Alterar NIF");								//4
	menuOptions[12].push_back("Alterar fundos mensais");					//5
	menuOptions[12].push_back("Saldar divida");								//6
	menuOptions[12].push_back("Voltar atras");								//7

	vector<string> menuDadosVivenda;
	menuOptions.push_back(menuDadosVivenda);

	menuOptions[13].push_back("Alterar morada");							//0
	menuOptions[13].push_back("Alterar codigo postal");						//1
	menuOptions[13].push_back("Alterar area habitacional");					//2
	menuOptions[13].push_back("Alterar area exterior");						//3
	menuOptions[13].push_back("Alterar piscina");							//4
	menuOptions[13].push_back("Voltar atras");								//5

	vector<string> menuDadosApartamento;
	menuOptions.push_back(menuDadosApartamento);

	menuOptions[14].push_back("Alterar morada");							//0
	menuOptions[14].push_back("Alterar codigo postal");						//1
	menuOptions[14].push_back("Alterar tipologia");							//2
	menuOptions[14].push_back("Alterar area habitacional");					//3
	menuOptions[14].push_back("Alterar piso");								//4
	menuOptions[14].push_back("Voltar atras");								//5

	menu = menuOptions;
}

// Main function
int main() {
	Main main = Main();

	createMesesAno();
	createMenuOptions();
	main.setMenus(menu);

	main.importCondominio();
	main.importCondominos();
	main.importHabitacoes();

	main.menuInicial();
	//main.displayAllCondominos();
	//main.displayAllHabitacoes();
	return main.exitFunction();
}


#include "../headers/Main.h"

#include "../headers/Header.h"
#include "../headers/Utils.h"

#include "../sort&search/insertionSort.h"
#include "../sort&search/sequentialSearch.h"

#define pathLogo "../savedata/logo.txt"
#define pathUtilizadores "../savedata/utilizadores.txt"

const string currentDateTime();
void displayTime();
void displayLogo();
void pressEnterToContinue();
bool hasWhitespace(string s);

/*
 * Class functions
 */

void Main::setMenus(vector<vector<string> > menu) {
	this->menu = menu;
}
void Main::setUtilizadores(vector<Utilizador> utilizadores) {
	insertionSort(utilizadores);
	this->utilizadores = utilizadores;
}

bool Main::addUtilizador(Utilizador utilizador) {
	int pos = sequentialSearch(this->utilizadores, utilizador);
	if (pos != -1)
		return false;
	this->utilizadores.push_back(utilizador);
	insertionSort(this->utilizadores);
	return true;
}

bool Main::eraseUtilizador(string nomeUtilizador) {
	Utilizador u1 = Utilizador(nomeUtilizador);
	int pos = sequentialSearch(this->utilizadores, u1);
	if (pos == -1)
		return false;
	this->utilizadores.erase(utilizadores.begin() + pos);
	return true;
}

// Resets menu option. Called every time we switch to a new menu.
void Main::resetOption() {
	this->option = 0;
}
// Prints a Menu Select screen
int Main::displayMenuOptions(int position) {
	if (option >= menu.size())
		return -1;

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
	return 0;
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

void Main::displayUsers() const {
	displayLogo();
	gotoxy(0, 8);
	cout << "Lista de utilizadores:\n" << endl;

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
bool Main::editDadosConta(int option) {
	displayLogo();
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
			cout << "\nNome de utilizador alterado." << endl;
			pressEnterToContinue();
			return true;
		} else
			pressEnterToContinue();
		return false;
	}
	if (option == 1) {
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
		} else
			return false;
	}
	return false;
}

void Main::editDadosCondomino() {
	displayLogo();
	if (this->currentUser->hasDados()) {

	}

}

void Main::displayCurrentUser() const {
	displayLogo();
	gotoxy(0, 8);
	if (this->currentUser->hasDados())
		this->currentUser->getDados()->display();
	else
		cout << "Dados ainda nao foram definidos." << endl;
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
			return menuRegisto();
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
		Utilizador u1 = Utilizador(utilizador, password);
		this->addUtilizador(u1);
		cout << "\nConta criada com sucesso!\n" << "Ja pode fazer login."
				<< endl;
	} else {
		cout << "Nao foi possivel criar uma conta." << endl;
	}
	pressEnterToContinue();
	resetOption();
	return menuInicial();
}

int Main::menuUtilizador() {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, " << this->currentUser->getNomeUtilizador() << "\n"
			<< endl;
	gotoxy(30, 8);

	int menuOption {};
	if (this->currentUser->isAdmin()) {
		menuOption = 1; //Admin mode
		cout << "MENU ADMIN";
	} else {
		menuOption = 2; //Normal mode
		cout << "MENU UTILIZADOR";
	}
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
				return menuEditDadosConta();
			} else if (option == 1) {
				displayCurrentUser();
			} else if (option == 3) {
				displayUsers();
			} else {
				resetOption();
				return menuInicial();
			}
		else if (menuOption == 2) {
			if (option == 0) {
				resetOption();
				return menuEditDadosConta();
			} else if (option == 1) {
				displayCurrentUser();
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



int Main::menuEditDadosConta() {
	displayLogo();
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
		if (option + 1 < menu[0].size())
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
	default:
		break;
	}
	return menuEditDadosConta();
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
	} else {
		displayLogo();
		cout
				<< "ERRO: Ocorreu um problema ao aceder ao ficheiro de utilizadores.\n";
		pressEnterToContinue();
		return false;
	}
	return false;
}

bool Main::exportUtilizadores() {
	ofstream myfile(pathUtilizadores, ios::trunc);

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
	return false;
}

int Main::exitFunction() {
	if (this->exportUtilizadores())
		return EXIT_SUCCESS;
	else
		return EXIT_FAILURE;
}

/*
 * Non-class functions
 */

// Get current date/time, format is YYYY/MM/DD HH:mm:ss
const string currentDateTime() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y/%m/%d %H:%M:%S", &tstruct);

	return buf;
}

// Displays time using currentDateTime()
void displayTime() {
	string time = currentDateTime();
	gotoxy(50, 20);
	cout << time;
}

// Displays the program logo
void displayLogo() {
	ifstream myfile(pathLogo);
	string line = "";
	clrscr();
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			cout << line << endl;
		}
		myfile.close();
	} else {
		cout << "ERRO: Ocorreu um problema ao aceder ao ficheiro do logo."
				<< endl;
	}
}

// Waits until user presses Enter
void pressEnterToContinue() {
	cout << "Pressione ENTER para continuar." << endl;
	cin.ignore();
	fflush(stdin);
}

bool hasWhitespace(string s) {
	for (size_t i = 0; i < s.size(); i++) {
		if (s[i] == ' ')
			return true;
	}
	return false;
}

// Returns a vector with vectors of strings, containing the options for each menu.
vector<vector<string> > createMenuOptions() {
	vector<vector<string> > menuOptions;

	vector<string> menuInicial;
	menuOptions.push_back(menuInicial);

	menuOptions[0].push_back("Login");									//0
	menuOptions[0].push_back("Registo");								//1
	menuOptions[0].push_back("Sair");									//2

	vector<string> menuAdmin;
	menuOptions.push_back(menuAdmin);

	menuOptions[1].push_back("Alterar dados da conta"); 				//0
	menuOptions[1].push_back("Ver dados de condomino"); 				//1
	menuOptions[1].push_back("Alterar dados de condomino");				//2
	menuOptions[1].push_back("Ver lista de todos os utilizadores");		//3
	menuOptions[1].push_back("Sair");									//4

	vector<string> menuCondomino;
	menuOptions.push_back(menuCondomino);

	menuOptions[2].push_back("Alterar dados da conta");					//0
	menuOptions[2].push_back("Ver dados de condomino");					//1
	menuOptions[2].push_back("Alterar dados de condomino");				//2
	menuOptions[2].push_back("Sair");									//3

	vector<string> menuDadosConta;
	menuOptions.push_back(menuDadosConta);

	menuOptions[3].push_back("Alterar nome de utilizador");			//0
	menuOptions[3].push_back("Alterar password");						//1
	menuOptions[3].push_back("Voltar atras");							//2

	vector<string> menuDadosCondomino;
	menuOptions.push_back(menuDadosCondomino);

	menuOptions[4].push_back("Alterar nome");							//0
	menuOptions[4].push_back("Alterar NIF");							//1
	menuOptions[4].push_back("Voltar atras");							//2

//
//

	return menuOptions;
}

// Main function
int main() {
	Main main = Main();

	vector<vector<string> > menu = createMenuOptions();
	main.setMenus(menu);

	main.importUtilizadores();

	main.menuInicial();

	return main.exitFunction();
}


#include "../headers/Main.h"

#include "../headers/Header.h"
#include "../headers/Utils.h"

#include "../sort&search/insertionSort.h"
#include "../sort&search/sequentialSearch.h"

const string currentDateTime();
void displayTime();
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

// Resets menu option. Called every time we switch to a new menu.
void Main::resetOption() {
	this->option = 0;
}
// Prints a Menu Select screen
int Main::displayMenuOptions(int position) {
	if (option >= menu.size())
		return -1;

	for (size_t i = 0; i < menu[position].size(); i++) {
		if (i == option) {
			setcolor(BLACK, LIGHTGREY);
			cout << " " << left << setw(10) << setfill(' ')
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
	if (addUtilizador(u1) == false) {
		cout << "\nO nome de utilizador nao esta disponivel." << endl;
		return false;
	}
	return true;
}

void Main::displayUsers() const {
	clrscr();
	cout << "CONDOMINIO\n" << endl;
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

/*
 * Menu functions
 */

int Main::menuInicial() {
	clrscr();
	cout << "CONDOMINIO\n" << endl;

	displayMenuOptions(0);

	displayTime();

	int c = 0;
	switch ((c = getch())) {
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
	clrscr();
	cout << "CONDOMINIO\n" << endl;

	cout << "LOGIN\n" << endl;
	cout << "Introduza os seus dados de login:\n";

	string utilizador;
	string password;

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
		return menuLogin();
	}
	return EXIT_SUCCESS;
}

int Main::menuRegisto() {
	clrscr();
	cout << "CONDOMINIO\n" << endl;

	cout << "REGISTO\n" << endl;
	cout << "Introduza os seus dados de login:\n";

	string utilizador;
	string password;

	cout << "Utilizador: ";
	getline(cin, utilizador);
	cout << "Password: ";
	getline(cin, password);

	if (validRegister(utilizador, password)) {
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
	clrscr();
	cout << "CONDOMINIO\n" << endl;

	cout << "Bem-vindo, " << this->currentUser->getNomeUtilizador() << "\n"
			<< endl;

	int menuOption;
	if (this->currentUser->isAdmin())
		menuOption = 1; //Admin mode
	else
		menuOption = 2; //Normal mode

	displayMenuOptions(menuOption);

	displayTime();

	int c = 0;
	switch ((c = getch())) {
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
				displayUsers();
			} else {
				resetOption();
				return menuInicial();
			}
		else if (menuOption == 2) {
			resetOption();
			return menuInicial();
		}
		break;
	default:
		break;
	}

	return menuUtilizador();
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
	gotoxy(0, 20);
	cout << time;
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

	menuOptions[0].push_back("Login");
	menuOptions[0].push_back("Registo");
	menuOptions[0].push_back("Sair");

	vector<string> menuAdmin;
	menuOptions.push_back(menuAdmin);

	menuOptions[1].push_back("Ver lista de utilizadores.");
	menuOptions[1].push_back("Sair.");

	vector<string> menuCondomino;
	menuOptions.push_back(menuCondomino);

	menuOptions[2].push_back("Sair.");

	//
	//

	return menuOptions;
}

// Extracts data from utilizadores.txt to create a vector of users.
vector<Utilizador> createUtilizadores() {
	fstream myfile("../savedata/utilizadores.txt");
	string line;
	string nomeUtilizador;
	string password;
	bool admin;

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
		return utilizadores;
	} else
		cout
				<< "ERRO: Ocorreu um problema ao aceder ao ficheiro de utilizadores.\n";
	return utilizadores;
}

// Main function
int main() {
	Main main = Main();
	vector<vector<string> > menu = createMenuOptions();
	vector<Utilizador> utilizadores = createUtilizadores();
	main.setMenus(menu);
	main.setUtilizadores(utilizadores);

	main.menuInicial();

	return EXIT_SUCCESS;
}


#include "Condominio.h"

#include "Utils.h"

void Condominio::fimDoMes() {
	for (size_t i = 0; i < moradores.size(); i++)
		for (size_t j = 0; j < moradores[i]->getPropriedades().size(); j++)
			fundos += moradores[i]->getPropriedades()[j]->calcRenda();
	fundos -= numFuncionarios * 500;
}

// Get current date/time, format is YYYY/MM/DD HH:mm:ss
const std::string currentDateTime() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
	// for more information about date/time format
	strftime(buf, sizeof(buf), "%Y/%m/%d %H:%M:%S", &tstruct);

	return buf;
}

// Displays time using currentDateTime()
void displayTime() {
	string time = currentDateTime();
	gotoxy(0, 20);
	cout << time;
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

	//
	//

	vector<string> menuCondomino;
	menuOptions.push_back(menuCondomino);

	//
	//

	return menuOptions;
}

// Prints a Menu Select screen
int displayMenuOptions(vector<vector<string> > &menu, int position,
		int &option) {
	if (option >= menu.size())
		return -1;

	for (size_t i = 0; i < menu[position].size(); i++) {
		if (i == option) {
			setcolor(BLACK, LIGHTGREY);
			cout << " " << left << setw(10) << setfill(' ') << menu[position][option] << endl;
			setcolor(WHITE, BLACK);
		} else
			cout << menu[position][i] << endl;
	}
	return 0;
}

bool verificarLogin(string utilizador, string password) {
	fstream myfile("../savedata/utilizadores.txt");
	string line;
	bool found = false;

	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			if (line == "0" || line == "1") {
				getline(myfile, line);
				if (line == utilizador) {
					getline(myfile, line);
					if (line == password) {
						found = true;
						break;
					} else
						break;
				}
			}
		}
		myfile.close();
	} else
		cout
				<< "ERRO: Ocorreu um problema ao aceder ao ficheiro de utilizadores.\n";
	return found;
}

int menuLogin(vector<vector<string> > &menu, int &option) {
	string utilizador;
	string password;

	clrscr();
	cout << "LOGIN\n" << endl;
	cout << "Introduza os seus dados de login:\n";
	cout << "Utilizador: ";
	getline(cin, utilizador);
	cout << "Password: ";
	getline(cin, password);

	if (verificarLogin(utilizador, password))
		cout << "Sucesso\n";
	else
		cout << "Dados invalidos\n";
	system("pause");
	//else
	//menuLogin(menu,option);
	displayTime();
	return 0;
}

int menuInicial(vector<vector<string> > &menu, int &option) {

	clrscr();
	cout << "CONDOMINIO\n" << endl;
	displayMenuOptions(menu, 0, option);

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
			menuLogin(menu, option);
		} else
			return 0;
		break;
	default:
		break;
	}

	menuInicial(menu, option);

	return 0;
}

int main() {
	vector<vector<string> > menu = createMenuOptions();
	int option = 0;
	menuInicial(menu, option);

	return EXIT_SUCCESS;
}

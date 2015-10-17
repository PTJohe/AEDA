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

void displayTime() {
	string time = currentDateTime();
	gotoxy(0, 20);
	cout << time;
}

//Returns a vector with vectors of strings, containing the options for each menu.
vector<vector<string> > createMenuOptions() {
	vector<vector<string> > menuOptions;

	vector<string> menuInicial;
	menuOptions.push_back(menuInicial);

	menuOptions[0].push_back("Login");
	menuOptions[0].push_back("Exit");

	return menuOptions;
}

int menuInicial(vector<vector<string> > &menu, int &option) {

	clrscr();

	setcolor(WHITE, BLACK);
	cout << "CONDOMINIO\n" << endl;
	for (size_t i = 0; i < menu[0].size(); i++) {
		if (i == option) {
			setcolor(BLACK, LIGHTGREY);
			cout << menu[0][option] << endl;
			setcolor(WHITE, BLACK);
		} else
			cout << menu[0][i] << endl;
	}

	displayTime();

	int c = 0;
	switch ((c = getch())) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		menuInicial(menu, option);
		break;
	case KEY_DOWN:
		if (option + 1 <= 1)
			option++;
		menuInicial(menu, option);
		break;
	case KEY_ENTER:
		exit(EXIT_SUCCESS);
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
	return 0;
}

#include "../headers/Condominio.h"

Condominio::Condominio() {
	this->fundos = 5000;
	this->currentMes = 0;
}

long int Condominio::getFundos() const {
	return fundos;
}
int Condominio::getMes() const {
	return currentMes;
}

vector<Condomino> Condominio::getMoradores() {
	return moradores;
}
vector<Habitacao*> Condominio::getHabitacoes() {
	return habitacoes;
}
vector<Funcionario> Condominio::getFuncionarios() {
	return funcionarios;
}
void Condominio::setFundos(long int fundos) {
	this->fundos = fundos;
}
void Condominio::setCurrentMes(int currentMes) {
	this->currentMes = currentMes;
}
void Condominio::setMoradores(vector<Condomino> moradores) {
	this->moradores = moradores;
}
void Condominio::setHabitacoes(vector<Habitacao*> habitacoes) {
	this->habitacoes = habitacoes;
}
void Condominio::setFuncionarios(vector<Funcionario> funcionarios) {
	this->funcionarios = funcionarios;
}
Condomino* Condominio::getCondomino(int pos) {
	Condomino* p = &moradores[pos];
	return p;
}

void Condominio::sortMoradores(int sortOption) {
	if (sortOption == 0)
		insertionSort(moradores);
	else if(sortOption == 1)
		sort(moradores.begin(), moradores.end(), compCondominoNomeCivil);
	else if(sortOption == 2)
		sort(moradores.begin(), moradores.end(), compCondominoNIF);
}
int Condominio::addMorador(Condomino condomino) {
	int pos = sequentialSearch(this->moradores, condomino);
	if (pos == -1) {
		this->moradores.push_back(condomino);
		insertionSort(moradores);
		pos = sequentialSearch(this->moradores, condomino);
		return pos;
	} else
		return -1;
}
int Condominio::eraseMorador(Condomino condomino) {
	int pos = sequentialSearch(this->moradores, condomino);

	if (pos != -1) {
		this->moradores.erase(moradores.begin() + pos);
		insertionSort(moradores);
		for (size_t i = 0; i < this->habitacoes.size(); i++) {
			if (habitacoes[i]->getNIFProprietario() == condomino.getNIF())
				habitacoes[i]->setProprietario("");
		}
		sortHabitacoes(2);
		return pos;
	} else
		return -1;
}

void Condominio::sortHabitacoes(int sortOption) {
	if (sortOption == 0)
		sort(habitacoes.begin(), habitacoes.end(), compHabitacaoTipo);
	else if (sortOption == 1)
		sort(habitacoes.begin(), habitacoes.end(), compHabitacaoRenda);
	else if (sortOption == 2)
		sort(habitacoes.begin(), habitacoes.end(), compHabitacaoNIF);
	updateHabitacoesCondominos();
}
int Condominio::findHabitacao(vector<Habitacao*> habitacoes,
		Habitacao* habitacao) {
	int pos = -1;
	for (size_t i = 0; i < habitacoes.size(); i++) {
		if (habitacao->getMorada() == habitacoes[i]->getMorada()) {
			pos = i;
			return pos;
		}
	}
	return pos;
}

bool Condominio::addHabitacao(Habitacao* habitacao) {
	int pos = -1;
	for (size_t i = 0; i < this->habitacoes.size(); i++) {
		if (habitacoes[i]->getMorada() == habitacao->getMorada())
			pos = i;
	}
	if (pos == -1) {
		this->habitacoes.push_back(habitacao);
		sortHabitacoes(2);
		return true;
	} else
		return false;
}
bool Condominio::eraseHabitacaoPossuida(Condomino condomino, int pos) {
	int pos1 = sequentialSearch(this->moradores, condomino);
	if (pos1 == -1) {
		return false;
	} else {
		Habitacao* h1 = moradores[pos1].getHabitacoes()[pos];
		int pos2 = this->findHabitacao(this->habitacoes, h1);
		if (pos2 != -1)
			this->habitacoes.erase(habitacoes.begin() + pos2);

		bool success = moradores[pos1].eraseHabitacao(pos);
		sortHabitacoes(2);
		return success;
	}
}

bool Condominio::eraseHabitacao(int pos) {
	Condomino c1 = Condomino("nome", "password", "nomeCivil",
			this->habitacoes[pos]->getNIFProprietario());
	int pos1 = sequentialSearch(this->moradores, c1);

	if (pos1 == -1) {
		delete habitacoes[pos];
		habitacoes.erase(habitacoes.begin() + pos);
		return true;
	} else {
		int pos2 = this->findHabitacao(moradores[pos1].getHabitacoes(),
				habitacoes[pos]);
		habitacoes.erase(habitacoes.begin() + pos);
		return this->moradores[pos1].eraseHabitacao(pos2);
	}
}

bool Condominio::setNomeUtilizador(Condomino condomino, string nomeUtilizador) {
	int pos = sequentialSearch(this->moradores, condomino);
	if (pos == -1) {
		return false;
	}
	this->moradores[pos].setNomeUtilizador(nomeUtilizador);
	return true;
}
bool Condominio::setPassword(Condomino condomino, string password) {
	int pos = sequentialSearch(this->moradores, condomino);
	if (pos == -1) {
		return false;
	}
	this->moradores[pos].setPassword(password);
	return true;
}
bool Condominio::setAdmin(Condomino condomino, bool admin) {
	int pos = sequentialSearch(this->moradores, condomino);
	if (pos == -1) {
		return false;
	}
	this->moradores[pos].setAdmin(admin);
	return true;
}
bool Condominio::setNomeCivil(Condomino condomino, string nomeCivil) {
	int pos = sequentialSearch(this->moradores, condomino);
	if (pos == -1) {
		return false;
	}
	this->moradores[pos].setNomeCivil(nomeCivil);
	return true;
}
bool Condominio::setNIF(Condomino condomino, string NIF) {
	int pos = sequentialSearch(this->moradores, condomino);
	if (pos == -1) {
		return false;
	}
	this->moradores[pos].setNIF(NIF);
	return true;
}
bool Condominio::setFundosMensais(Condomino condomino, long int fundos) {
	int pos = sequentialSearch(this->moradores, condomino);
	if (pos == -1) {
		return false;
	}
	this->moradores[pos].setFundosMensais(fundos);
	return true;
}
bool Condominio::saldarDivida(Condomino condomino) {
	int pos = sequentialSearch(this->moradores, condomino);
	if (pos == -1) {
		return false;
	} else {
		this->moradores[pos].setDivida(0);
		for (size_t i = 0; i < this->moradores[pos].getHabitacoes().size();
				i++) {
			for (size_t j = 0; j <= this->currentMes; j++) {
				this->moradores[pos].getHabitacoes()[i]->setPago(j);
			}
		}
		return true;
	}
}

bool Condominio::updateHabitacoesCondominos() {
	for (size_t i = 0; i < this->moradores.size(); i++) {
		vector<Habitacao*> habitacoes;
		for (size_t j = 0; j < this->habitacoes.size(); j++) {
			if (this->moradores[i].getNIF()
					== this->habitacoes[j]->getNIFProprietario())
				habitacoes.push_back(this->habitacoes[j]);
		}
		this->moradores[i].setHabitacoes(habitacoes);
	}
	return true;
}

bool Condominio::addFuncionario(Funcionario funcionario) {
	/*
	 * TODO Verificar se o funcionario ja existe no vector antes de adicionar aqui
	 */
	this->funcionarios.push_back(funcionario);
}
bool Condominio::addServico(Servico servico) {
	//if houver recursos, adiciona ao servicosEmCurso
	//else adiciona servicosEmEspera
	return false;
}

//Retorna vector com condominos que nao pagaram totalmente as rendas nesse mes
vector<Condomino> Condominio::fimDoMes() {
	vector<Condomino> caloteiros;

	//Actualiza o mes actual. Se o ano acabar, reinicializa o estado da renda das habitacoes de todos os condominos
	if (this->currentMes < 11) //0 = Janeiro
		this->currentMes++;
	else if (this->currentMes == 11) { //11 = Dezembro
		this->currentMes = 0;
		for (size_t i = 0; i < this->moradores.size(); i++) {
			for (size_t j = 0; j < this->moradores[i].getHabitacoes().size();
					j++)
				this->moradores[i].getHabitacoes()[j]->resetPago();
		}
	}

	for (size_t i = 0; i < moradores.size(); i++) {
		//Fundos mensais que o condomino tem para pagar as rendas
		int fundosRestantes = moradores[i].getFundosMensais();
		//Actualizar o pagamento da renda para cada habitacao que ele possuir
		for (size_t j = 0; j < moradores[i].getHabitacoes().size(); j++) {
			if (fundosRestantes > 0) {
				int diferenca = fundosRestantes
						- moradores[i].getHabitacoes()[j]->calcRenda();
				//Adiciona a renda aos fundos do condominio e define como pago o mes actual da habitacao
				if (diferenca >= 0) {
					fundos += moradores[i].getHabitacoes()[j]->calcRenda();
					moradores[i].getHabitacoes()[j]->setPago(this->currentMes);
					fundosRestantes -=
							moradores[i].getHabitacoes()[j]->calcRenda();
				}
				//Se nao tiver fundos para pagar totalmente a renda, adiciona o que conseguir aos fundos do condominio
				//e adiciona à divida do condomino o montante que nao conseguiu pagar
				else {
					fundos += moradores[i].getHabitacoes()[j]->calcRenda()
							+ diferenca;
					moradores[i].addDivida(diferenca);
					fundosRestantes -=
							moradores[i].getHabitacoes()[j]->calcRenda();
				}
			}
			//Se nao tiver fundos, adiciona à divida do condomino a renda que nao conseguiu pagar
			else
				moradores[i].addDivida(
						-moradores[i].getHabitacoes()[j]->calcRenda());
		}
		//Se ainda restarem fundos e o condomino tiver uma divida,
		//ele usa esses fundos para saldar essa divida (total ou parcialmente)
		if (fundosRestantes > 0 && moradores[i].getDivida() < 0) {
			int novaDivida = moradores[i].getDivida() + fundosRestantes;
			if (novaDivida > 0)
				novaDivida = 0;
			moradores[i].setDivida(novaDivida);
		}
		//Se o condomino nao conseguiu pagar o mes, adiciona ao vector dos caloteiros que vai ser retornado
		if (fundosRestantes < 0)
			caloteiros.push_back(moradores[i]);
	}

	//Actualiza o pagamento aos funcionarios
	fundos -= this->funcionarios.size() * 500;

	return caloteiros;
}

void Condominio::infoMoradores() const {
	cout << "Numero de moradores = " << this->moradores.size() << "\n" << endl;
	for (size_t i = 0; i < this->moradores.size(); i++) {
		cout << i + 1 << " - ";
		this->moradores[i].infoCondomino();
	}
}
void Condominio::infoHabitacoes() const {
	cout << "Numero de habitacoes = " << habitacoes.size() << "\n" << endl;
	for (size_t i = 0; i < habitacoes.size(); i++) {
		cout << i + 1 << " - ";
		habitacoes[i]->info();
	}
}

/*
 * Non-class functions
 */

bool compCondominoNomeCivil(Condomino c1, Condomino c2) {
	if (c1.getNomeCivil() < c2.getNomeCivil())
		return true;
	else if (c1.getNomeCivil() > c2.getNomeCivil())
		return false;
	else
		return c1.getNomeUtilizador() < c2.getNomeUtilizador();
}
bool compCondominoNIF(Condomino c1, Condomino c2) {
	return c1.getNIF() < c2.getNIF();
}

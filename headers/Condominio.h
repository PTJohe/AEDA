#ifndef HEADERS_CONDOMINIO_H_
#define HEADERS_CONDOMINIO_H_

#include "../headers/Header.h"
#include "../headers/Condomino.h"
#include "../headers/Servico.h"
#include "../sort&search/HashTable.h"

class Condominio {
private:
	long int fundos;
	vector<Condomino> moradores;
	vector<Habitacao*> habitacoes;
	//vector<Funcionario> funcionarios;
	tabHFunc funcionarios;
	vector<Servico> servicosTerminados;
	vector<Servico> servicosEmCurso;
	vector<Servico> servicosEmEspera;
	int currentMes;

	//Segunda parte
	int id;
	string designacao;
	Posicao localizacao;
	priority_queue<Paragem> transportes;

public:
	Condominio();
	Condominio(string designacao, Posicao localizacao);
	Condominio(int id, long int fundos, int currentMes, string designacao,
			Posicao localizacao);

	int getID() const;
	void decID();
	long int getFundos() const;
	int getMes() const;
	string getDesignacao() const;
	Posicao getLocalizacao() const;
	Condomino* getCondomino(int pos);
	vector<Condomino> getMoradores();
	vector<Habitacao*> getHabitacoes();
	vector<Funcionario> getFuncionarios();
	Funcionario getFuncionario(int id);
	vector<Servico> getServicos(int vectorServicos);
	int getNumHabitacoes() const;
	int getNumVivendas() const;
	int getNumMoradores() const;

	void setFundos(long int fundos);
	void setCurrentMes(int currentMes);
	void setMoradores(vector<Condomino> moradores);
	void setHabitacoes(vector<Habitacao*> habitacoes);
	void setFuncionarios(vector<Funcionario> funcionarios);
	void setServicos(int vectorServicos, vector<Servico> servicos);
	void setDesignacao(string designacao);
	void setLocalizacao(Posicao localizacao);

	bool operator <(const Condominio &c1) const;
	bool operator ==(const Condominio &c1) const;

	friend ostream& operator<<(ostream& os, Condominio &c1);

	void sortMoradores(int sort);
	int addMorador(Condomino condomino);
	int eraseMorador(Condomino condomino);

	void sortHabitacoes(int sort);
	int findHabitacao(vector<Habitacao*> habitacoes, Habitacao* habitacao);
	bool addHabitacao(Habitacao* h1);
	bool eraseHabitacao(int pos);
	bool eraseHabitacaoPossuida(Condomino condomino, int pos);

	//Funcoes Condomino
	bool setNomeUtilizador(Condomino condomino, string nomeUtilizador);
	bool setPassword(Condomino condomino, string password);
	bool setAdmin(Condomino condomino, bool admin);
	bool setNomeCivil(Condomino condomino, string nomeCivil);
	bool setNIF(Condomino condomino, string NIF);
	bool setFundosMensais(Condomino condomino, long int fundos);
	bool saldarDivida(Condomino condomino);

	//Funcoes Habitacao
	bool updateHabitacoesCondominos();

	//Funcoes Funcionario

	vector<Funcionario> sortFuncionarios(int sortOption);
	bool addFuncionario(Funcionario funcionario);
	bool eraseFuncionario(Funcionario &f1);
	void setOcupado(Funcionario f1);
	int getNumFuncLimpeza();
	int getLivresLimpeza(vector<Funcionario> &funcionarios);
	int getNumFuncCanalizacao();
	int getLivresCanalizacao(vector<Funcionario> &funcionarios);
	int getNumFuncPintura();
	int getLivresPintura(vector<Funcionario> &funcionarios);

	//Funcoes Servico
	void sortServicos(int vectorServicos, int sortOption);
	bool addServico(int vectorServicos, string mes, Servico servico);
	bool eraseServico(int pos, int vectorServicos);
	time_t getDisponibilidadeServico(int tipo);
	bool updateServicos(string mes, Condomino* currentUser,
			int &servicosCurrentUser);
	bool updateServicosFimMes(string mes);

	vector<Condomino> fimDoMes();

	void infoMoradores() const;
	void infoHabitacoes() const;

};

/*
 * Exceptions
 */
class CondominoDuplicado {
public:
	friend ostream& operator<<(ostream& out, const CondominoDuplicado &e) {
		out << "Ja existe um condomino com o mesmo NIF." << endl;
		return out;
	}
};

/*
 * Non-class functions
 */
bool compCondominioID(Condominio c1, Condominio c2);
bool compCondominioDesignacao(Condominio c1, Condominio c2);
bool compCondominioPropriedades(Condominio c1, Condominio c2);
bool compCondominioLocalizacao(Condominio c1, Condominio c2);

bool compCondominoNomeCivil(Condomino c1, Condomino c2);
bool compCondominoNIF(Condomino c1, Condomino c2);
bool compFuncionarioEspecialidade(Funcionario f1, Funcionario f2);
bool compFuncionarioOcupacao(Funcionario f1, Funcionario f2);
bool compFuncionarioServicos(Funcionario f1, Funcionario f2);
bool compServicoTipo(Servico s1, Servico s2);
bool compServicoDataInicio(Servico s1, Servico s2);
bool compServicoNIF(Servico s1, Servico s2);

#endif

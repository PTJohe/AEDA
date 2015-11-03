#include "../headers/Servico.h"

int Servico::id = 1;

bool verificaFuncs(vector<Funcionario> funcionarios, int numFuncionarios, string especialidade){

	int i = 0;
	while(i < funcionarios.size() && numFuncionarios > 0){
		if(funcionarios[i].getStatus() == true)
			if(sequentialSearch(funcionarios[i].getEspecialidades(), especialidade) != -1)
				numFuncionarios--;
		i++;
	}
	if(numFuncionarios != 0)
		return false;
	else
		return true;
}

vector<Funcionario> atualizaFuncs(Condominio &condo,int numFuncionarios,string especialidade){
	vector<Funcionario> novo,velho,serv;
	velho = condo.getFuncionarios();
	Funcionario tmp;

	int i = 0;
	while(numFuncionarios > 0){
		tmp = velho[i];
		if(velho[i].getStatus() == true)
			if(sequentialSearch(velho[i].getEspecialidades(), especialidade) != -1){
				numFuncionarios--;
				tmp.giveStatus(false);
				serv.push_back(tmp);
			}
		novo.push_back(tmp);
		i++;
	}

	while(i < velho.size()){
		novo.push_back(velho[i]);
		i++;
	}

	condo.setFuncionarios(novo);
	return serv;
}

Servico::Servico(string nome,float duracao,int numFuncionarios,Condominio &condo, float preco, string especialidade)
{
	if(!verificaFuncs(condo.getFuncionarios(),numFuncionarios, especialidade))
		throw faltaPessoal();
	else{
		this->nome = nome;
		this->duracao = duracao;
		this->numFuncionarios = numFuncionarios;
		this->preco = preco;
		this->funcionarios =  atualizaFuncs(condo,numFuncionarios,especialidade);
		id++;
	}

}

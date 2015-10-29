#include "../headers/Condominio.h"

void Condominio::fimDoMes() {
	for (size_t i = 0; i < moradores.size(); i++)
		for (size_t j = 0; j < moradores[i]->getPropriedades().size(); j++)
			fundos += moradores[i]->getPropriedades()[j]->calcRenda();
	fundos -= numFuncionarios * 500;
}

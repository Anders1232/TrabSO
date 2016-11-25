#ifndef GERENCIADOR_MEMORIA_HPP
#define GERENCIADOR_MEMORIA_HPP

#include <list>
#include <vector>

struct regListaVazia
{
	int posicao;
	int tamanho;
	int operator<(regListaVazia &reg);
	regListaVazia(int, int);
};

class GerenciadorMemoria
{
	public:
		//retorna o endereço inicial no qual o processo foi alocado.Se não consegue alocar retorna -1
		int Alocar(int processo, int tamanho);
		bool Desalocar(int offsetMemoria,int numBlocosDeMemoria);
	private:
		std::vector<int> memoria;
		std::list<regListaVazia> listaDeEspacosVazios;
};

#endif

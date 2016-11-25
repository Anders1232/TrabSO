#include "GerenciadorMemoria.hpp"

//#include<iterator>

int regListaVazia::operator<(regListaVazia &reg)
{
	return this->tamanho > reg.tamanho;
}

regListaVazia::regListaVazia(int a, int b)
: posicao(a), tamanho(b)
{

}

int GerenciadorMemoria::Alocar(int processo, int tamanho){

	int auxPosicao,auxTamanho;

	for (std::list<regListaVazia>::iterator it=listaDeEspacosVazios.begin(); it != listaDeEspacosVazios.end(); ++it)
	{
		if(tamanho <= it->tamanho )
		{
				auxPosicao = it->posicao;
				auxTamanho = it->tamanho;
				listaDeEspacosVazios.erase(it);
				//Preenche a memória com dados ficticios
				for(int i = 0; i < tamanho ;i ++)
				{
					memoria[i] = processo;
				}
				//Verifica se sobrou espaço no bloco usado.Caso afirmativo,insere o espaço restante na lista
				if((auxTamanho - tamanho) > 0)
				{
					listaDeEspacosVazios.insert (it, regListaVazia(auxPosicao,auxTamanho - tamanho));
					listaDeEspacosVazios.sort();
				}
				return(auxPosicao);
		}
	}
	return(-1);
}

bool GerenciadorMemoria::Desalocar(int offsetMemoria,int numBlocosDeMemoria){

	std::list<regListaVazia>::iterator it = listaDeEspacosVazios.begin();
	listaDeEspacosVazios.insert (it, regListaVazia(offsetMemoria,numBlocosDeMemoria));
	listaDeEspacosVazios.sort();

}

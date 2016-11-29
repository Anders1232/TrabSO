#include "GerenciadorMemoria.hpp"

//#include<iterator>
#include<stdio.h>
#include<stdlib.h>

int regListaVazia::operator<(regListaVazia &reg)
{
	return this->tamanho > reg.tamanho;
}

regListaVazia::regListaVazia(int a, int b)
: posicao(a), tamanho(b)
{

}

GerenciadorMemoria::GerenciadorMemoria(int quantidadeDeBlocos)
{
	printf("Construtor do gerenciador de memória chamado! Tamanho da memória: %u\n", quantidadeDeBlocos);
	listaDeEspacosVazios.push_back(regListaVazia(0, quantidadeDeBlocos));
	memoria.resize(quantidadeDeBlocos, MEMORIA_NAO_USADA);
#ifdef DEVERIA_FUNCIONAR_MAS_NAO_FUNCIONA
	memoria.reserve(quantidadeDeBlocos);
	for(int cont =0; cont < quantidadeDeBlocos; cont++)
	{
		memoria[cont] = MEMORIA_NAO_USADA;
	}
#else
	memoria.resize(quantidadeDeBlocos, MEMORIA_NAO_USADA);
#endif
	printf("Construtor do gerenciador de memória chamado! Memória alocada: %lu\n", memoria.size());
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
					memoria[auxPosicao+i] = processo;
				}
				//Verifica se sobrou espaço no bloco usado.Caso afirmativo,insere o espaço restante na lista
				if((auxTamanho - tamanho) > 0)
				{
					listaDeEspacosVazios.push_back (regListaVazia(auxPosicao+tamanho, auxTamanho - tamanho));
					listaDeEspacosVazios.sort();
				}
				return(auxPosicao);
		}
	}
	return(ALOCACAO_FALHOU);
}
/*
bool GerenciadorMemoria::Desalocar(int offsetMemoria,int numBlocosDeMemoria){

	std::list<regListaVazia>::iterator it = listaDeEspacosVazios.begin();
	listaDeEspacosVazios.insert (it, regListaVazia(offsetMemoria,numBlocosDeMemoria));
	listaDeEspacosVazios.sort();

	return true;

}
*/

bool GerenciadorMemoria::Desalocar(int idProcesso)
{
	unsigned int indice, count=0;
	bool achou=false;

	for (unsigned int i=0; i<memoria.size(); i++)
	{
		if(memoria.at(i)==idProcesso)
		{
			achou=true;
			if(0 == count)
			{
				indice = i; 	//pega o primeiro espaço que ele ocupa
			}
			count++;

		}
		else if(achou) //caso esteja em blocos consecutivos
		{
			break;
		}
	}
	if(!achou)
	{
		fprintf(stderr, "\n\nDeu ruim %s:%d\n\n", __FILE__, __LINE__);
		exit(1);
	}
	adicionarNaLista(count, indice);


	//3


	/*
		1.Buscar local da memoria que ta o processo
		2.verificar quanto de memo ele ocupa
		3.Colocar essa memo na lista de espaços livres.
		4.Mudar esses blocos para blocos livres,
		5.por na lista de espaços livre
		6.verificar se tem alguma memo livre para juntar.
				
	*/

//	printf("Implementar %s:%d\n", __FILE__, __LINE__);
	return true;
}


void GerenciadorMemoria::adicionarNaLista(int tamanho,int offset){
	
	regListaVazia l(tamanho, offset);

	listaDeEspacosVazios.push_back(l);
	listaDeEspacosVazios.sort();

	std::list<regListaVazia>::iterator i = listaDeEspacosVazios.begin();
	std::list<regListaVazia>::iterator o = i;
//	printf("listaDeEspacosVazios.size() = %d\n", listaDeEspacosVazios.size());
	if(1 < listaDeEspacosVazios.size())
	{
		for (; i != listaDeEspacosVazios.end(); i++)
		{
			o++;
			if( (i->posicao) + (i-> tamanho) +1 == o->posicao)
			{
				//junta
				regListaVazia l1(i->posicao, (i->tamanho)+(o->tamanho));
				listaDeEspacosVazios.erase(i);
				listaDeEspacosVazios.erase(o);
				listaDeEspacosVazios.push_back(l1);
				listaDeEspacosVazios.sort();
				//recomeça o loop
				i= listaDeEspacosVazios.begin();
				o= i;
	//			break;
			}
		}
	}
}

int GerenciadorMemoria::ObterOffset(int idProcesso)
{
	for(unsigned int i = 0;i < memoria.size(); i++)
	{
		if(memoria[i] == idProcesso)
		{
			return i;
		}
	}
	return (-1);

}

void GerenciadorMemoria::printMemory(){
	int a = memoria.size();
	printf("%d\n",a);
	for(unsigned int i = 0;i < memoria.size(); i++)
	{
		printf("%d",memoria[i]);

	}
}

#include "Escalonador.hpp"
#include <algorithm>
#include <stdio.h>
#include <string>

bool RegistroProcessoEscalonador::operator<(RegistroProcessoEscalonador const &a) const
{
	return this->aging < a.aging;
}


void Escalonador::AdicionarProcesso(int idProcesso, int prioridadeInicial)
{
	if(PRIORIDADE_TEMPO_REAL == prioridadeInicial)
	{
		processosTempoReal.push_back(idProcesso);
	}
	else
	{
		RegistroProcessoEscalonador temp;
		temp.idProcesso = idProcesso;
		temp.aging = prioridadeInicial;
		temp.prioridadePos = prioridadeInicial+1;
		registroProcessos.push_back(temp);
	}
}
int Escalonador::Escalonar(void)//retorna o id do primeiro processo da fila que vai ser rodado
{
	int processoEscalonado;
	if(0!= processosTempoReal.size())
	{
		processoEscalonado= processosTempoReal.front();
//		ultimoProcessoEscalonado
//		return processosTempoReal.front();
	}
	else
	{
		std::stable_sort(registroProcessos.begin(), registroProcessos.end());
		for(unsigned int cont =0 ;cont < registroProcessos.size(); cont++)
		{
			(registroProcessos[cont].aging)--;
		}
		registroProcessos[0].aging= registroProcessos[0].prioridadePos;
		(registroProcessos[0].prioridadePos)++;
//		std::stable_sort(registroProcessos.begin(), registroProcessos.end());
		processoEscalonado= registroProcessos[0].idProcesso;
	}
	if(processoEscalonado != ultimoProcessoEscalonado)
	{
		ultimoProcessoEscalonado= processoEscalonado;
		printf("process %d =>\n", processoEscalonado);
	}
	return processoEscalonado;
}

void Escalonador::ProcessoTerminou(int idProcesso)
{
	if(idProcesso == processosTempoReal.front())
	{
		processosTempoReal.pop_front();
		return;
	}
	else
	{
/*		for(unsigned int cont =0; cont < registroProcessos.size(); cont++)
		{
			if(idProcesso == registroProcessos[cont].idProcesso)
			{
				registroProcessos.erase(cont);
				return;
			}
		}
*/
		for(std::vector<RegistroProcessoEscalonador>::iterator algo; algo != registroProcessos.end(); algo++)
		{
			if(algo->idProcesso == idProcesso)
			{
				registroProcessos.erase(algo);
				return;
			}
		}
	}
	char str[350];
	sprintf(str, "[ERRO] Processo não encontrado! Arquivo: %s\t\t:%d\n", __FILE__, __LINE__);
	throw new std::string(str);
}

/*
void Escalonador::AdicionarProcesso(int idProcesso, int prioridadeInicial)
{
	if(PRIORIDADE_TEMPO_REAL == prioridadeInicial)
	{
		processosTempoReal.push_back(idProcesso);
	}
	else
	{
		registroProcessos.push_back(RegistroProcessoEscalonador(idProcesso, prioridadeInicial, prioridadeInicial+1));
	}
}
*/

Escalonador::Escalonador(void)
{
	ultimoProcessoEscalonado= -1;
}

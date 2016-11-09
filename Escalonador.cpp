#include "Escalonador.hpp"

int RegistroProcessEscalonador::operator<(RegistroProcessoEscalonador &a)
{
	return this->aging < a.aging;
}


void Escolanador::AdicionarProcesso(int idProcesso, int prioridadeInicial)
{
	if(0== prioridadeInicial)
	{
		processosTempoReal.push_back(idProcesso);
	}
	else
	{
		RegistroProcessEscalonador temp;
		temp.idProcesso == idProcesso;
		temp.aging = prioridadeInicial;
		temp.prioridadePos = prioridadeInicial+1;
		registroProcessos.push_back(temp);
	}
}
int Escolanador::Escalonar(void)//retorna o id do primeiro processo da fila que vai ser rodado
{
	if(0!= processosTempoReal.size())
	{
		return processosTempoReal[0];
	}
	else
	{
		registroProcessos[0].aging= registroProcessos[0].prioridadePos;
		(registroProcessos[0].prioridadePos)++;
		registroProcessos.sort();
//		std::stable_sort(registroProcessos.begin(), registroProcessos.end());
		for(int cont =0 ;cont < registroProcessos.size(); cont++)
		{
			(registroProcessos[cont].aging)--;
		}
	}
	return registroProcessos[0].idProcesso;
}

void Escolanador::ProcessoTerminou(int idProcesso)
{
	if(idProcesso == processosTempoReal.front())
	{
		processosTempoReal.pop_front();
		return;
	}
	else
	{
		for(int cont =0; cont < registroProcessos.size(); cont++)
		{
			if(idProcesso == registroProcessos[cont].idProcesso)
			{
				registroProcessos.erase(cont);
				return;
			}
		}
	}
	throw new std::tring("[ERRO] Processo não encontrado! Arquivo: %s\t\t:%d\n", __FILE__, __LINE__);
}


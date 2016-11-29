#include"GerenciadorProcessos.hpp"
#include<cstdio>
#include<cstdlib>
#include <iostream>
#include <algorithm>
#include <unistd.h>


#define CONTINUE_LOOP_PRINCIPAL timeslice++;continue

#define ASSERT(arg1)\
	if(!arg1)\
	{\
		fprintf(stderr, "Assertion failed at %s:%d\n",__FILE__,__LINE__);\
		exit(1);\
	}
	

GerenciadorProcessos::GerenciadorProcessos(std::string &nomeArquivo)
{
	FILE *arq= fopen(nomeArquivo.c_str(), "r");
	ASSERT(arq);
	
	
	int arg1, arg2, arg3, arg4,/*agora os booleanos*/ arg5, arg6, arg7, arg8;
	int argumentosLidos=8;
	do
	{
		argumentosLidos= fscanf(arq, "%d, %d, %d, %d, %d, %d, %d, %d \n", &arg1, &arg2, &arg3, &arg4, &arg5, &arg6, &arg7, &arg8);
		if(8==argumentosLidos)
		{
			Processo *proc= new Processo(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
			processosQueNaoForamIniciados.push_back(proc);
			std::cout << "processo lido: ";
			std::cout << arg1 <<" "<< arg2<<" "<< arg3<<" "<< arg4<<" "<< arg5<<" "<< arg6<<" "<<arg7<<" "<< arg8 << std::endl;
		}
		else
		{
			break;
		}
	}
	while(1);
	std::cout <<"Lido:" << processosQueNaoForamIniciados.size() << std::endl;

	GO();
}

int ordenarTempoEntrada(Processo *A, Processo *B)
{
	return A->obterMomentoEntrada()<B->obterMomentoEntrada();
}

void GerenciadorProcessos::GO(){
	int timeslice=0;
	unsigned int numProcessosQueNaoRodaram= 0;
	unsigned int numProcessos= processosQueNaoForamIniciados.size();
	std::sort(processosQueNaoForamIniciados.begin(), processosQueNaoForamIniciados.end(), ordenarTempoEntrada );
	while(processosTerminados.size() + numProcessosQueNaoRodaram != numProcessos)
	{
		//verificar se tem processo na lista de  n-inicializados que vao entrar no timeslice
		//Se sim, verifica se tem memoria, se sim, remover da lista de n-inicializado e por na fila de execucao 
		while((processosQueNaoForamIniciados.size()>0)?	(timeslice==processosQueNaoForamIniciados.front()->obterMomentoEntrada() ) : false)
		{
			Processo * const proc = processosQueNaoForamIniciados.front();
			//verificar se usa algum recurso
			//ver se tem recurso que ele precisa
			bool recursosAlocados[4];
			for(int cont =0; cont < 4; cont++)
			{
				recursosAlocados[cont]= false;
			}
			//Processo &proc = *(processosQueNaoForamIniciados.begin());
			if(proc->usaImpressora())
			{
				recursosAlocados[0] = gereciadorRecursos.Alocar(RECURSO_IMPRESSORA);
				if(!recursosAlocados[0])
				{
					//não tem nada para desalocar
					printf("O processo %d não será executado pois a impressora já está alocada!\n", proc->ObterID());
					numProcessosQueNaoRodaram++;
					processosQueNaoForamIniciados.erase(processosQueNaoForamIniciados.begin());
//					CONTINUE_LOOP_PRINCIPAL;
					continue;
				}
			}
			if(proc->usaScanner())
			{
				recursosAlocados[1] = gereciadorRecursos.Alocar(RECURSO_SCANNER);
				if(!recursosAlocados[1])
				{
					//desalocar tudo que ja foi alocado pra nao rodar
					printf("O processo %d não será executado pois o scanner já esá alocado!\n", proc->ObterID());
					if(recursosAlocados[0])
					{
						gereciadorRecursos.Desalocar(RECURSO_IMPRESSORA);
					}
					numProcessosQueNaoRodaram++;
					processosQueNaoForamIniciados.erase(processosQueNaoForamIniciados.begin());
//					CONTINUE_LOOP_PRINCIPAL;
					continue;
				}
			}
			if(proc->usaModem())
			{
				recursosAlocados[2] = gereciadorRecursos.Alocar(RECURSO_MODEM);
				if(!recursosAlocados[2])
				{
					printf("O processo %d não será executado pois o modem já esá alocado!\n",proc->ObterID());
					for(int cont =0; cont < 3; cont++)
					{
						if(recursosAlocados[cont])
						{
							gereciadorRecursos.Desalocar(cont);
						}
					}
					numProcessosQueNaoRodaram++;
					processosQueNaoForamIniciados.erase(processosQueNaoForamIniciados.begin());
//					CONTINUE_LOOP_PRINCIPAL;
					continue;
				}
			}
			if(proc->usaSata())
			{
				recursosAlocados[3]= gereciadorRecursos.Alocar(RECURSO_SATA);
				if(!recursosAlocados[3])
				{
					//desalocar tudo que ja foi alocado pra nao rodar
				}
				recursosAlocados[3] = gereciadorRecursos.Alocar(RECURSO_MODEM);
				if(!recursosAlocados[3])
				{
					printf("O processo %d não será executado pois o modem já esá alocado!\n", proc->ObterID());
					for(int cont =0; cont < 4; cont++)
					{
						if(recursosAlocados[cont])
						{
							gereciadorRecursos.Desalocar(cont);
						}
					}
					numProcessosQueNaoRodaram++;
					processosQueNaoForamIniciados.erase(processosQueNaoForamIniciados.begin());
//					CONTINUE_LOOP_PRINCIPAL;
					continue;
				}
			}
			//ver se tem memoria
			int prio = proc->ObterPrioridade();
			ASSERT((0 <= prio));
			if(prio==PRIORIDADE_TEMPO_REAL)
			{
				//colocar na fila de tempo real. TEM DUAS FUNCOES CHAMADAS ALOCAR!
				if(ALOCACAO_FALHOU == memoriaTempoReal.Alocar(proc->ObterID(), proc->ObterQuantidadeMemoria() ))
				{
					printf("O processo %d não será executado pois não tem memória de tempo real suficiente para o mesmo ser executado!\n", proc->ObterID());
					for(int cont =0; cont < 4; cont++)
					{
						if(recursosAlocados[cont])
						{
							gereciadorRecursos.Desalocar(cont);
						}
					}
					numProcessosQueNaoRodaram++;
					processosQueNaoForamIniciados.erase(processosQueNaoForamIniciados.begin());
//					CONTINUE_LOOP_PRINCIPAL;
					continue;
				}
			}
			else
			{
				//fila dos normais
				if(ALOCACAO_FALHOU == memoriaComum.Alocar(proc->ObterID(), proc->ObterQuantidadeMemoria()))
				{
					printf("O processo %d não será executado pois não tem memória suficiente para o mesmo ser executado!\n", proc->ObterID());
					for(int cont =0; cont < 4; cont++)
					{
						if(recursosAlocados[cont])
						{
							gereciadorRecursos.Desalocar(cont);
						}
					}
					numProcessosQueNaoRodaram++;
					processosQueNaoForamIniciados.erase(processosQueNaoForamIniciados.begin());
					continue;
				}
			}
			escalonador.AdicionarProcesso(proc->ObterID(), proc->ObterPrioridade());
			processosEmExecucao.push_back(proc);
			processosQueNaoForamIniciados.erase(processosQueNaoForamIniciados.begin());
			Despachar(*proc);
		}

		if(0 == processosEmExecucao.size())
		{
			printf("Nesse timeslice não havia nenhum processo para ser executado, standby\n");
			sleep(1);
			CONTINUE_LOOP_PRINCIPAL;
		}
		else
		{
			int processoSelecionado= escalonador.Escalonar();
			for(std::vector<Processo*>::iterator it= processosEmExecucao.begin(); it != processosEmExecucao.end(); it++)
//			for(int cont =0; cont < processosEmExecucao.size(); cont++)
			{
				if( (*it)->ObterID() == processoSelecionado)
				{
					ResultadoExecucao res= (*it)->RodarProcesso();
					if(PROCESSO_TERMINOU == res)
					{
						if(PRIORIDADE_TEMPO_REAL == (*it)->ObterPrioridade())
						{
							memoriaTempoReal.Desalocar(processoSelecionado);
						}
						else
						{
							memoriaComum.Desalocar(processoSelecionado);
						}
						if((*it)->usaImpressora())
						{
							gereciadorRecursos.Desalocar(RECURSO_IMPRESSORA);
						}
						if((*it)->usaModem())
						{
							gereciadorRecursos.Desalocar(RECURSO_MODEM);
						}
						if((*it)->usaSata())
						{
							gereciadorRecursos.Desalocar(RECURSO_SATA);
						}
						if((*it)->usaScanner())
						{
							gereciadorRecursos.Desalocar(RECURSO_SCANNER);
						}
						processosTerminados.push_back(*it);
						processosEmExecucao.erase(it);
					}
				}
			}
		}
		timeslice++;//por ultimo é isso
	}

}

/*
dispatcher =>
PID: 1
offset: 0
blocks: 64
priority: 0
time: 3
printers: 0
scanners: 0
modems: 0
drives: 0
*/
void GerenciadorProcessos::Despachar(Processo &proc)
{
	int prioridade= proc.ObterPrioridade();
	int id = proc.ObterID();
	printf("dispatcher =>\n");
	printf("PID: %d\n", id);
	if(0 == prioridade)
	{
		printf("offset: %d\n", memoriaTempoReal.ObterOffset(id));
	}
	else
	{
		printf("offset: %d\n", memoriaComum.ObterOffset(id));
	}
	printf("blocks: %d\n", proc.ObterQuantidadeMemoria());
	printf("priority: %d\n", prioridade);
	printf("time: %d\n", proc.ObterTempoParaExecutar());
	printf("printers: %d\n", (proc.usaImpressora())? 1 : 0);
	printf("scanners: %d\n", (proc.usaScanner())? 1 : 0);
	printf("modems: %d\n", (proc.usaModem())? 1 : 0);
	printf("drives: %d\n", (proc.usaSata())? 1 : 0);
	printf("\n");
}

GerenciadorProcessos::~GerenciadorProcessos()
{
	for(unsigned int cont =0; cont < processosTerminados.size(); cont++)
	{
		delete processosTerminados[cont];
	}
}

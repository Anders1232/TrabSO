
#include"GerenciadorProcessos.hpp"
#include<cstdio>
#include<cstdlib>
#include <iostream>
#include <algorithm>



#define ASSERT(arg1)\
	if(!arg1)\
	{\
		fprintf(stderr, "Assertion failed at %s:%d\n",__FILE__,__LINE__);\
		exit(1);\
	}
	

void GerenciadorProcessos::LerArquivo(std::string &nomeArquivo)
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
			Processo proc(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
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

int ordenarTempoEntrada(Processo A, Processo B)
{
	return A.obterMomentoEntrada()<B.obterMomentoEntrada();
}

void GerenciadorProcessos::GO(){
	int timeslice=0;
	unsigned int numProcessosQueNaoRodaram= 0;
	unsigned int numProcessos= processosQueNaoForamIniciados.size();
	std::sort(processosQueNaoForamIniciados.begin(), processosQueNaoForamIniciados.end(), ordenarTempoEntrada );
	Processo &proc = *(processosQueNaoForamIniciados.begin());
	while(processosTerminados.size() + numProcessosQueNaoRodaram != numProcessos)
	{
		//verificar se tem processo na lista de  n-inicializados que vao entrar no timeslice
		//Se sim, verifica se tem memoria, se sim, remover da lista de n-inicializado e por na fila de execucao 
		while(timeslice==processosQueNaoForamIniciados.begin()->obterMomentoEntrada())
		{
			//verificar se usa algum recurso
			//ver se tem recurso que ele precisa
			bool recursosAlocados[4];
			for(int cont =0; cont < 4; cont++)
			{
				recursosAlocados[cont]= false;
			}
			//Processo &proc = *(processosQueNaoForamIniciados.begin());
			if(proc.usaImpressora())
			{
				recursosAlocados[0] = gereciadorRecursos.Alocar(IMPRESSORA);
				if(!recursosAlocados[0])
				{
					//não tem nada para desalocar
					printf("O processo %d não será executado pois a impressora já esá alocada!\n", proc.ObterID());
					numProcessosQueNaoRodaram++;
					processosQueNaoForamIniciados.erase(processosQueNaoForamIniciados.begin());
					continue;
				}
			}
			if(proc.usaScanner())
			{
				recursosAlocados[1] = gereciadorRecursos.Alocar(SCANNER);
				if(!recursosAlocados[1])
				{
					//desalocar tudo que ja foi alocado pra nao rodar
					printf("O processo %d não será executado pois o scanner já esá alocado!\n", proc.ObterID());
					if(recursosAlocados[0])
					{
						gereciadorRecursos.Desalocar(IMPRESSORA);
					}
					numProcessosQueNaoRodaram++;
					processosQueNaoForamIniciados.erase(processosQueNaoForamIniciados.begin());
					continue;
				}
			}
			if(proc.usaModem())
			{
				recursosAlocados[2] = gereciadorRecursos.Alocar(MODEM);
				if(!recursosAlocados[2])
				{
					printf("O processo %d não será executado pois o modem já esá alocado!\n",proc.ObterID());
					for(int cont =0; cont < 3; cont++)
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
			if(proc.usaSata())
			{
				recursosAlocados[3]= gereciadorRecursos.Alocar(SATA);
				if(!usarRecurso)
				{
					//desalocar tudo que ja foi alocado pra nao rodar
				}
				recursosAlocados[3] = gereciadorRecursos.Alocar(MODEM);
				if(!recursosAlocados[3])
				{
					printf("O processo %d não será executado pois o modem já esá alocado!\n", proc.ObterID());
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
			//ver se tem memoria
			int prio = proc.ObterPrioridade();
			ASSERT((0 <= prio));
			if(prio==0)
			{
				//colocar na fila de tempo real. TEM DUAS FUNCOES CHAMADAS ALOCAR!
				if(ALOCACAO_FALHOU == memoriaTempoReal.Alocar(proc.ObterQuantidadeMemoria() ))
				{
					printf("O processo %d não será executado pois não tem memória de tempo real suficiente para o mesmo ser executado!\n", proc.ObterID());
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
				else
				{
					/*colocar no escalonador*/
					escalonador.AdicionarProcesso(proc.ObterID(), proc.ObterPrioridade());
				}
			}
			else
			{
				//fila dos normais
				if(ALOCACAO_FALHOU == memoriaComum.Alocar(proc.ObterQuantidadeMemoria()))
				{
					printf("O processo %d não será executado pois não tem memória suficiente para o mesmo ser executado!\n", proc.ObterID());
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
				else
				{
					/*colocar no escalonador*/
					escalonador.AdicionarProcesso(proc.ObterID(), proc.ObterPrioridade());
				}
			}
		}
		processosEmExecucao.push_back(proc);
		processosQueNaoForamIniciados.erase(processosQueNaoForamIniciados.begin());

		//escalonar um processo pra ser executado
		//Se o processo acabar, por na lista de terminados e liberar seus recursos



		timeslice++;//por ultimo é isso
	}




}


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
			std::cout << arg1 <<" "<< arg2<<" "<< arg3<<" "<< arg4<<" "<< arg5<<" "<< arg6<<" "<<arg7<<" "<< arg8 << " \n ";
		}
		else
		{
			break;
		}
	}
	while(1);
	std::cout <<"Lido:" << processosQueNaoForamIniciados.size() <<" \n ";

	GO();
}

int ordenarTempoEntrada(Processo A, Processo B){

	return A.obterMomentoEntrada()<B.obterMomentoEntrada();
}

void GerenciadorProcessos::GO(){
	int timeslice=0, numProcessos=processosQueNaoForamIniciados.size();


	std::sort(processosQueNaoForamIniciados.begin(), processosQueNaoForamIniciados.end(), ordenarTempoEntrada );

	while(processosTerminados.size() != numProcessos){
		//verificar se tem processo na lista de  n-inicializados que vao entrar no timeslice
		//Se sim, verifica se tem memoria, se sim, remover da lista de n-inicializado e por na fila de execucao 
		//escalonar um processo pra ser executado
		//Se o processo acabar, por na lista de terminados e liberar seus recursos


		while(timeslice==processosQueNaoForamIniciados.begin().obterMomentoEntrada()){
			//verificar se usa algum recurso
			//ver se tem recurso que ele precisa
		
			Processo &proc = processosQueNaoForamIniciados.begin();
			if(proc.usaImpressora()){
				bool usarRecurso = gereciadorRecursos.Alocar(IMPRESSORA);
				if(!usarRecurso){
					//desalocar tudo que ja foi alocado pra nao rodar
				}
			}
			if(proc.usaScanner()){
				bool usarRecurso = gereciadorRecursos.Alocar(SCANNER);
				if(!usarRecurso){
					//desalocar tudo que ja foi alocado pra nao rodar
				}
			}
			if(proc.usaModem()){
				bool usarRecurso = gereciadorRecursos.Alocar(MODEM);
				if(!usarRecurso){
					//desalocar tudo que ja foi alocado pra nao rodar
				}
			}
			if(proc.usaSata()){
				bool usarRecurso = gereciadorRecursos.Alocar(SATA);
				if(!usarRecurso){
					//desalocar tudo que ja foi alocado pra nao rodar
				}
			}


			//ver se tem memoria
			
			int prio = proc.informarPrioridade();
			if(prio==0)
			{
				//colocar na fila de tempo real
				if(proc.informarQuantidadeMemoria()){
					//aloca
				}
				else{
					//nao aloca
				}
			}
			else if(prio<20){
				//colocar na fila de alto prioridade
			}
			else if(prio< 40){
				//prioridade media
			}
			else{
				//prioridade baixa :(
			}

			if(prio!=0)
			{ 
				if(proc.informarQuantidadeMemoria()){
					//aloca
				}
				else{
					//nao aloca
				}
			}
		}

		timeslice++;//por ultimo é isso
	}




}

#include "Processo.hpp"
#include "stdio.h"
#include "unistd.h"

Processo::Processo(

			int tempoInicializacao,
			int prioridade,
			int tempoProcessador,
			int numBlocosDeMemoria,
			int impressora,
			int scanner,
			int modem,
			int codigoDisco
):
	tempoInicializacao(tempoInicializacao),
	prioridade(prioridade),
	tempoProcessador(tempoProcessador),
	numBlocosDeMemoria(numBlocosDeMemoria),
	impressora((impressora>0)?true:false),
	scanner((scanner>0) ? true:false),
	modem((modem>0)? true: false),
	codigoDisco((codigoDisco>0)? true: false)
{
	offsetMemoria= PROCESSO_NAO_CARREGADO;
	static int identificador=0;
	this->id= identificador++;
}


int Processo::obterMomentoEntrada(void){

	return tempoInicializacao;
}


biiiiiirl Processo::usaImpressora(void){
	
	return impressora;
}
biiiiiirl Processo::usaScanner(void){
	
	return scanner;
}
biiiiiirl Processo::usaSata(void){
	
	return codigoDisco;
}
biiiiiirl Processo::usaModem(void){
	
	return modem;
} 

int Processo::ObterID(void)
{
	return id;
}

int Processo::ObterPrioridade(void)
{
	return prioridade;
}

int Processo::ObterQuantidadeMemoria(void)
{
	return numBlocosDeMemoria;
}

ResultadoExecucao Processo::RodarProcesso(void)
{
	printf("O processo %d está sendo executado.\n", id);
	sleep(1);
	tempoProcessador--;
	if(0 == tempoProcessador)
	{
		return PROCESSO_TERMINOU;
	}
	return PROCASSO_NAO_TERMINOU;
}


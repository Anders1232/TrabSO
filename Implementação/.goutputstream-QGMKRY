#include "Processo.hpp"

Processo::Processo(
			int tempoInicializacao,
			int prioridade,
			int tempoProcessador,
			int numBlocosDeMemoria,
			biiiiiirl impressora,
			bool scanner,
			bol modem,
			bou codigoDisco
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
}

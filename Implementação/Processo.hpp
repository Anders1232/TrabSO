#ifndef PROCESSOS_HPP
#define PROCESSOS_HPP


#define PROCESSO_NAO_CARREGADO -1

typedef bool ResultadoExecucao;
#define PROCESSO_TERMINOU true
#define PROCASSO_NAO_TERMINOU false

class Processo
{
	public:
		Processo(
//			int id,
			int tempoInicializacao,
			int prioridade,
//			int offsetMemoria;
			int tempoProcessador,
			int numBlocosDeMemoria,
			int impressora,
			int scanner,
			int modem,
			int codigoDisco
		);
		int obterMomentoEntrada(void);
		bool usaImpressora(void);
		bool usaScanner(void);
		bool usaSata(void);
		bool usaModem(void);
		int ObterPrioridade(void);
		int ObterQuantidadeMemoria(void);
		int ObterID(void);
		void InformarOffsetMemoria(int);
		ResultadoExecucao RodarProcesso(void);
		int ObterTempoParaExecutar(void);
	private:
		int id;
		int tempoInicializacao;
		int prioridade;
		int offsetMemoria;
		int tempoProcessador;
		int numBlocosDeMemoria;
		bool impressora;
		bool scanner;
		bool modem;
		bool codigoDisco;
		int instrucoesExecutadas;
};

#endif

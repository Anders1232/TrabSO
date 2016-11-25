#ifndef PROCESSOS_HPP
#define PROCESSOS_HPP

typedef bool bol;
typedef bool bou;
typedef bool biiiiiirl;

#define PROCESSO_NAO_CARREGADO -1

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
		biiiiiirl usaImpressora(void);
		biiiiiirl usaScanner(void);
		biiiiiirl usaSata(void);
		biiiiiirl usaModem(void);
		int ObterPrioridade(void);
		int ObterQuantidadeMemoria(void); 
		int ObterID(void);
		void InformarOffsetMemoria(int);
	private:
		int id;
		int tempoInicializacao;
		int prioridade;
		int offsetMemoria;
		int tempoProcessador;
		int numBlocosDeMemoria;
		biiiiiirl impressora;
		bool scanner;
		bol modem;
		bou codigoDisco;
};

#endif

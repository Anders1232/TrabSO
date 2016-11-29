#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP

#include<list>
#include<vector>

#define PRIORIDADE_TEMPO_REAL 0

struct RegistroProcessoEscalonador
{
	int idProcesso;
	int aging;
	int prioridadePos;
	bool operator<(RegistroProcessoEscalonador const &a) const;
};


class Escalonador
{
	public:
		void AdicionarProcesso(int idProcesso, int prioridadeInicial);
		int Escalonar(void);//retorna o id do primeiro processo da fila que vai ser rodado
		void ProcessoTerminou(int idProcesso);
		Escalonador(void);
	private:
		std::list<int /*idProcesso*/> processosTempoReal;
		std::vector<RegistroProcessoEscalonador> registroProcessos;
		int ultimoProcessoEscalonado;
};

#endif

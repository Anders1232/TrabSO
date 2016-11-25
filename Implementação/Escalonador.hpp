#include<list>
#include<vector>

struct RegistroProcessoEscalonador
{
	int idProcesso;
	int aging;
	int prioridadePos;
	int operator<(RegistroProcessoEscalonador &a);
};


class Escalonador
{
	public:
		void AdicionarProcesso(int idProcesso, int prioridadeInicial);
		int Escalonar(void);//retorna o id do primeiro processo da fila que vai ser rodado
		void ProcessoTerminou(int idProcesso);
	private:
		std::list<int /*idProcesso*/> processosTempoReal;
		std::vector<RegistroProcessoEscalonador> registroProcessos;
};

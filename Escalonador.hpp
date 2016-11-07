struct RegistroProcessEscalonador
{
	int idProcesso;
	int aging;
	int prioridadePos;
};


class Escolanador
{
	public:
		void AdicionarProcesso(int idProcesso, int prioridadeInicial);
		int Escalonar(void);//retorna o id do primeiro processo da fila que vai ser rodado
		void ProcessoTerminou(int idProcesso);
	private:
		vector<int /*idProcesso*/> processosTempoReal;
		vector<RegistroProcessoEscalonador> registroProcessos;
}

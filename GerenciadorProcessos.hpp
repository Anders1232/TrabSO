class GerenciadorProcessos
{
	public:
		void LerArquivo(void);
		void GO(void);
	private:
		vector<Processo> processos;
		GerenciadorMemoria gerenciadorMemoria;
		GerenciadorRecursos gereciadorRecursos;
		Escalonador escalonador;
}

#include<string>
#include<vector>
#include"Processo.hpp"
#include"GerenciadorMemoria.hpp"
#include"GerenciadorRecursos.hpp"
#include"Escalonador.hpp"

class GerenciadorProcessos
{
	public:
		void LerArquivo(std::string &nomeArquivo);
		void GO(void);
	private:
		std::vector<Processo> processos;
		GerenciadorMemoria gerenciadorMemoria;
		GerenciadorRecursos gereciadorRecursos;
		Escalonador escalonador;
};

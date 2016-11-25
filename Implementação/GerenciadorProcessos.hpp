#ifndef GERENCIADOR_PROCESSOS_HPP
#define GERENCIADOR_PROCESSOS_HPP

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

#endif

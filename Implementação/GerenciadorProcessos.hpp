#ifndef GERENCIADOR_PROCESSOS_HPP
#define GERENCIADOR_PROCESSOS_HPP

#include<string>
#include<vector>
#include"Processo.hpp"
#include"GerenciadorMemoria.hpp"
#include"GerenciadorRecursos.hpp"
#include"Escalonador.hpp"

#define TAMANHO_MEMORIA_COMUM 960
#define TAMANHO_MEMORIA_TEMPO_REAL 64

class GerenciadorProcessos
{
	public:
		void LerArquivo(std::string &nomeArquivo);
		void GO(void);
	private:
		std::vector<Processo> processosQueNaoForamIniciados;
		std::vector<Processo> processosEmExecucao;
		std::vector<Processo> processosTerminados;
		GerenciadorMemoria memoriaComum = TAMANHO_MEMORIA_COMUM;
		GerenciadorMemoria memoriaTempoReal= TAMANHO_MEMORIA_TEMPO_REAL;
		GerenciadorRecursos gereciadorRecursos;
		Escalonador escalonador;
};

#endif

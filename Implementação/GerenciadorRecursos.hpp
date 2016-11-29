#ifndef GERENCIADOR_RECURSOS_HPP
#define GERENCIADOR_RECURSOS_HPP

#include<stdbool.h>

/*enum Recurso
{
	IMPRESSORA=0,
	SATA=1,
	SCANNER=2,
	MODEM=3
};*/
typedef int Recurso;
#define RECURSO_IMPRESSORA 1
#define RECURSO_SATA 2
#define RECURSO_SCANNER 3
#define RECURSO_MODEM 4

class GerenciadorRecursos
{
	public:
		bool Alocar(Recurso rec);
		bool Desalocar(Recurso rec);
		GerenciadorRecursos(void);
	private:
		int impressora; //inicia com 2
		int scanner;// inicializa com 1
		int modem; //=1
		int sata;//=2
};

#endif

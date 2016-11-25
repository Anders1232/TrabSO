#include"GerenciadorRecursos.hpp"
#include<cstdio>
#include<cstdlib>

GerenciadorRecursos::GerenciadorRecursos(void)
{
	impressora=2;
	scanner=1;
	modem=1;
	sata=2;
}

bool GerenciadorRecursos::Alocar(Recurso rec)
{
	switch (rec)
	{
		case IMPRESSORA:
		{
			if(0== impressora)
			{
				return false;
			}
			impressora--;
			return true;
		}
		case SATA:
		{
			if(0== sata)
			{
				return false;
			}
			sata--;
			return true;
		}
		case SCANNER:
		{
			if(0== scanner)
			{
				return false;
			}
			scanner--;
			return true;
		}
		case MODEM:
		{
			if(0== modem)
			{
				return false;
			}
			modem--;
			return true;
		}
		default:
		{
			fprintf(stderr, "[ERRO]Tentando alocar recurso desconhecido.\t\t%s\t\t%d\n", __FILE__, __LINE__);
			exit(1);
		}
	}
}

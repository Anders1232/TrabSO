#include"GerenciadorRecursos.hpp"
#include<cstdio>
#include<cstdlib>

#define QUANTIDADE_IMPRESSORAS 2
#define QUANTIDADE_SCANNER 1
#define QUANTIDADE_MODEM 1
#define QUANTIDADE_SATA 2

GerenciadorRecursos::GerenciadorRecursos(void)
{
	impressora=QUANTIDADE_IMPRESSORAS;
	scanner= QUANTIDADE_SCANNER;
	modem= QUANTIDADE_MODEM;
	sata=QUANTIDADE_SATA;
}

bool GerenciadorRecursos::Alocar(Recurso rec)
{
	switch (rec)
	{
		case RECURSO_IMPRESSORA:
		{
			if(0== impressora)
			{
				return false;
			}
			impressora--;
			return true;
		}
		case RECURSO_SATA:
		{
			if(0== sata)
			{
				return false;
			}
			sata--;
			return true;
		}
		case RECURSO_SCANNER:
		{
			if(0== scanner)
			{
				return false;
			}
			scanner--;
			return true;
		}
		case RECURSO_MODEM:
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

bool GerenciadorRecursos::Desalocar(Recurso rec)
{
	switch (rec)
	{
		case RECURSO_IMPRESSORA:
		{
			if(QUANTIDADE_IMPRESSORAS== impressora)
			{
				return false;
			}
			impressora++;
			return true;
		}
		case RECURSO_SATA:
		{
			if(QUANTIDADE_SATA== sata)
			{
				return false;
			}
			sata++;
			return true;
		}
		case RECURSO_SCANNER:
		{
			if(QUANTIDADE_SCANNER== scanner)
			{
				return false;
			}
			scanner++;
			return true;
		}
		case RECURSO_MODEM:
		{
			if(QUANTIDADE_SCANNER== modem)
			{
				return false;
			}
			modem++;
			return true;
		}
		default:
		{
			fprintf(stderr, "[ERRO]Tentando alocar recurso desconhecido.\t\t%s\t\t%d\n", __FILE__, __LINE__);
			exit(1);
		}
	}
}

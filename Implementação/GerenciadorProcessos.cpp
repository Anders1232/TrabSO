#include"GerenciadorProcessos.hpp"
#include<cstdio>
#include<cstdlib>

#define ASSERT(arg1)\
	if(!arg1)\
	{\
		fprintf(stderr, "Assertion failed at %s:%d\n",__FILE__,__LINE__);\
	}\
	exit(1)

void GerenciadorProcessos::LerArquivo(std::string &nomeArquivo)
{
	FILE *arq= fopen(nomeArquivo.c_str(), "r");
	ASSERT(arq);
	int arg1, arg2, arg3, arg4,/*agora os booleanos*/ arg5, arg6, arg7, arg8;
	int argumentosLidos=0;
	do
	{
		argumentosLidos= fscanf(arq, "%d, %d, %d, %d, %d, %d, %d, %d\n", &arg1, &arg2, &arg3, &arg4, &arg5, &arg6, &arg7, &arg8);
		Processo proc(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		processos.push_back(proc);
	}
	while(8==argumentosLidos);
	printf("\n%lu processos lidos com sucesso!\n", processos.size());
		exit(1);
}

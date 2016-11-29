#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <string.h>

using namespace std;
#include "GerenciadorProcessos.hpp"
#include "GerenciadorMemoria.hpp"
#include "GerenciadorRecursos.hpp"
#include "Escalonador.hpp"


//faz leitura do arquivo process.txt
void leitura(const char*);
//leitura dos dados do processo n;
void lerProcesso(string linha);



int main(int argc, char const *argv[])
{
	string nomeArquivo;
	if(argv[1]){
		nomeArquivo= argv[1];
	}
	else{ //opcao 2!!
		cout << "de como entrada o nomo do arquivo de processos \n ex:process.txt\n";
		cin >> nomeArquivo;
		
	}
	GerenciadorProcessos Processao = GerenciadorProcessos(nomeArquivo);
	return 0;
}

//faz leitura do arquivo process.txt
void leitura(const char* fileName){
	short int proNum=0; //numero deo processo
	string linha;	//linha do arquivo

	ifstream arquivo (fileName); 		//abrindo file modo c++ pra nao ser mainstream

	if(arquivo.is_open()){
		while(getline(arquivo,linha)){	//pega cada linha do process.txt
			
			cout << "Processo " << ++proNum << "\n" << linha << '\n';
			
			lerProcesso(linha); 		//chama funcao que vai ler a linha(dados de cada processo n)
		}
		arquivo.close();

	}
	else
		cout << "oush, nao deu pra abrir :(";

	return;


}
//leitura dos dados do processo n(Que seria uma linha do process.txt)
void lerProcesso(string linha){
	char* item= new char[linha.length()+1]; //ou soca char item[100] nessa porra 

	strcpy(item,linha.c_str()); 			//convertendo tipo string pra char* pra usar strtok

	item = strtok (item," ,");				//strtok vai separar as linhas pelos tokens white_space e ","
	cout << "\n tempo de inicialização:" << item << "\n";	
 	while (item != NULL){ 					//continua até acabar o vetor
		cout << item << "\n";  				//cada campo é separado e impresso aqui!
    	item = strtok (NULL, " ,");
  	}

  	delete[] item;
  	return;
}

#include "GerenciadorMemória.cpp"
int Alocar(int processo, int tamanho){

	int auxPosicao,auxTamanho;

	for (iterator it = listaDeEspacosVazios.begin();it != listaDeEspacosVazios.end();it ++){
		
		if(tamanho <= it.tamanho ){
				
				auxPosicao = it.posicao;
				auxTamanho = it.tamanho;
				listaDeEspacosVazios.erase(it);
				//Preenche a memória com dados ficticios
				for(int i = 0; i < tamanho ;i ++){memoria[i] = processo;}
				//Verifica se sobrou espaço no bloco usado.Caso afirmativo,insere o espaço restante na lista
				if((auxTamanho - tamanho) > 0){

					listaDeEspacosVazios.insert (it,(auxPosicao,auxTamanho - tamanho));
					listaDeEspacosVazios.sort();

				}

				return(auxPosicao);

		}
	}

	return(-1);
}

bool Desalocar(int offsetMemoria,int numBlocosDeMemoria){

	it = listaDeEspacosVazios.begin();
	listaDeEspacosVazios.insert (it,(offsetMemoria,numBlocosDeMemoria));
	listaDeEspacosVazios.sort();

}

int ObterOffset(int idProcesso){

	for(int i = 0;i < memoria.size(); i++){

		if memoria[i] == idprocesso{return i;}	

	}

	return (-1);

}


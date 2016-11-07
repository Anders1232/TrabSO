//http://www.cplusplus.com/reference/list/list/sort/

struct regListaVazia
{
	int posicao;
	int tamanho;
};

class GerenciadorMemoria
{
	public:
		bool Alocar(int processo, int tamanho);
		bool Desalocar(int processo);
	private:
		vector<int> memoria;
		list<regListaVazia> listaDeEspacosVazios;
};

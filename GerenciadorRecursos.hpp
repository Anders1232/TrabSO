enum Recurso
{
	IMPRESSORA,
	SATA,
	SCANNER,
	MODEM
};

class GerenciadorRecursos
{
	public:
		bool Alocar(Recurso rec);
		bool Desalocar(Recurso rec);
		GerenciarRecursos();
	private:
		int impressora; //inicia com 2
		int scanner;// inicializa com 1
		int modem; //=1
		int sata;//=2
};

/*
if(rec == IMPRESSORA)
{
	if(impressora ==0)
	{
		return false;
	}
	else
	{
		impressora--;
		return true;
	}
}
*/

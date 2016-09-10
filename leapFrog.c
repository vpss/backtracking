#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define EMPTY ' '
#define FIM 1

/******************************************************************
 Executa o leapFrog com tamanho recebido pelo usuário.            *
 (Não aconselhável para valores grandes (crescimento exponencial) *
 ******************************************************************/


//vetores que serão alocados em tempo de execução(dependem do QTD)
char* vInic;
char* vFinal;

int  QTD;
int SIZE;

// inicializa os vetores
char init_vet()
{
	int i=-1,j;
	vInic  = malloc(sizeof(char) * SIZE+1);
	vFinal = malloc(sizeof(char) * SIZE+1);

    	//válidos?
	assert(vInic); assert(vFinal);

	//1a metade = 'X' , 2a metade = 'O'
	while((++i) <= SIZE)
		vInic[i] = (i<SIZE/2) ? 'X' : (i == (SIZE/2) ? EMPTY : (i == SIZE ? '\0' : 'O'));

    	//vFinal será igual ao inverso do vInic (como deve ficar depois de ser jogado)
    	for(i=0, j=SIZE-1; i<SIZE; i++,j--)
		vFinal[i] = (i == SIZE ? '\0' : vInic[j]);
}

// Funções que checam se é possvel realizar
// algum movimento dada a posição atual do vetor

// checa se é possível andar um espaço com X
int check1X(int pos)
{
	return (vInic[pos+1] == EMPTY ? 1 : 0);
}

// checa se é possível andar dois espaços com X
int check2X(int pos)
{
	return (vInic[pos+2] == EMPTY ? 1 : 0);
}

//...
int check1O(int pos)
{
	return (vInic[pos-1] == EMPTY ? 1 : 0);
}

//...
int check2O(int pos)
{
	return (vInic[pos-2] == EMPTY ? 1 : 0);
}

//verifica se o jogo acabou
int completo()
{
    int i;
    for(i=0; i<7; i++)
	if(vInic[i] != vFinal[i])
            return 0;
    return FIM;
}

// Os movimentos com a peça representada por O são negativos
// porque se movimentam no sentido constrário a X no vetor.
// n   = numero de "casas" que serão puladas = (1,2,-1,-2)
// aux = função auxiliar que faz o movimento da peça e testa
// todas as novas possibilidades geradas por esse movimento
int aux(int n, int atual)
{
    int i = 0;

    vInic[atual+n] = vInic[atual];
    vInic[atual]   = EMPTY;

    // testa todas as possibilidades
    for(; i<SIZE; i++)
	if(leapFrog(i) == FIM)
		return FIM;

    // se os movimentos não deram em nada, são desfeitos e a peça volta para a posição anterior
    vInic[atual]   = vInic[atual+n];
    vInic[atual+n] = EMPTY;
    return;
}

int leapFrog(int atual)
{
    if(completo())
	return FIM;

    if(vInic[atual] == EMPTY || atual >= SIZE)
  	return;

    if(vInic[atual] == 'X')
    {
	if(check1X(atual)) //movimento +1
		aux(1, atual);

	if(check2X(atual)) //movimento +2
		aux(2, atual);
    }

    if(vInic[atual] == 'O')
    {
	if(check1O(atual)) //movimento -1
		aux(-1,atual);

	if(check2O(atual)) //movimento -2
                aux(-2,atual);
    }

    //se não for possível movientar a peça atual, testa a próxima:
    return leapFrog(atual+1);
}
int main()
{
    while(QTD < 1)
    {
        printf("Quantidade de peças de cada tipo: ");
        scanf("%d", &QTD);
    }

    SIZE = (2*QTD)+1;

    //inicializa o vetor de tamnho SIZE com QTD peças/sapos
    init_vet(); //ex: QTD = 3 => XXX 000

    printf("Vetor antes do jogo:   %s\n",vInic);
    leapFrog(0);    //0 = primeira posição
    printf("Vetor apos a execucao: %s", vInic);

    free(vInic);    free(vFinal);
    return 0;
}

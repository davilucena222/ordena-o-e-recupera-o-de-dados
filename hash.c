#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//2 * 15 = 31 (15 elementos)
//definindo o tamanho do vetor 
#define TAMANHO 31

//estrutura para o no da lista
typedef struct no { 
	int chave; //valor que vai para a lista
	struct no *proximo; //ponteiro para o próximo nó da lista
} No;

//estrutura para a lista
typedef struct lista {
	No *inicio; //ponteiro para o inicio da lista
	int tamanho; //tamanho da lista
}Lista;

//função que inicializa a lista e o seu tamanho com valores nulos
void inicializar_lista(Lista *l){
	l -> inicio = NULL;
	l -> tamanho = 0;
}

//função que insere um valor na lista
void inserir_na_lista(Lista *l, int valor){
	//alocando um ponteiro para o nó
	No *novo = malloc(sizeof(No));

	//verificando se a alocação dinâmica foi bem sucedida
	if(novo){
		//recebendo o novo valor
		novo -> chave = valor;
		//fazendo o próximo apontar para o inicio, pois inserção é o no inicio da lista
		novo -> proximo = l -> inicio;
		//fazendo o ponteiro que aponta para o inicio receber o novo nó, pois a inserção é no inicio apenas
		l -> inicio = novo;
		//incrementando o tamanho da lista
		l -> tamanho++;
	} else {
		printf("\n\tErro ao alocar memória!\n");
	}
}

//função para buscar um elemento na lista
int buscar_na_lista(Lista *l, int valor){
	//criando uma nova variável que aponta para o inicio da lista
	No *aux = l -> inicio;
	//enquanto aux existir e o valor for diferente do que está no nó o while continua procurando
	while(aux && aux -> chave != valor){
		//fazendo aux apontar para o próximo elemento
		aux = aux -> proximo;
	}

	//valor encontrado
	if(aux){
		return aux -> chave;
	}

	return 0;
}

//função para imprimir todos os elementos da lista
void imprimir_lista(Lista *l){
	//fazendo a nova variável apontar para o inicio
	No *aux = l -> inicio;
	//exibindo o tamanho da lista 
	printf("Tamanho da lista: %d: ", l -> tamanho);
	//enquanto aux existir
	while(aux){
		//mostra o elemento na tela
		printf("%d ", aux -> chave);
		//incrementa aux para apontar para o próximo elemento
		aux = aux -> proximo;
	}
}

//função que percorre a tabela em cada posição e preenche as listas com zero
void incializarTabela(Lista tabela[]){
	int i;

	//percorrendo a tabela e preenchendo com zero
	for(i = 0; i < TAMANHO; i++){
		//inicializando a lista em cada posição da tabela com zero
		inicializar_lista(&tabela[i]);
	}
}

//retorna o índice da tabela para armazenar o valor
int hash(int chave){
	return chave % TAMANHO;
}

//função para inserir o valor na tabela
void insere_na_tabela(Lista tabela[], int valor){
	//calculando o índice do vetor para inserir
	int indice = hash(valor);
	//chamando a função para inserir na lista naquela determinada posição da tabela(vetor) que foi calculada
	inserir_na_lista(&tabela[indice], valor);
}

//função para buscar um elemento na tabela 
int busca_tabela(Lista tabela[], int chave){
	//calculando o índice da chave que foi fornecida 
	int indice = hash(chave);
	printf("\nÍndice gerado: %d\n", indice);
	//chamando a função para buscar na lista naquela determinada posição da tabela(vetor) que foi calculada
	//retornando a chave que foi encontrada
	return buscar_na_lista(&tabela[indice], chave);
	
	return 0;
}

//demonstrando elementos na tela
void mostra_tabela(Lista tabela[]){
	int i;
	for(i = 0; i < TAMANHO; i++){
		printf("%d = ", i);
		imprimir_lista(&tabela[i]);
		printf("\n");
	}
}

int main(void) {
	//definindo tamanho do vetor
	Lista tabela[TAMANHO];
	int opcao;
	int valor;
	int retorno;

	//inicializando a tabela em todas as posições com as listas
	incializarTabela(tabela);


	do {
		printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Buscar\n\t3 - Mostrar\n\n" );
		scanf("%d", &opcao);

		switch(opcao){
			case 1:
				printf("\tQual valor deseja inserir? ");
				scanf("%d", &valor);
				insere_na_tabela(tabela, valor);
				break;
			case 2:
				printf("\tQual valor deseja buscar? ");
				scanf("%d", &valor);
				retorno = busca_tabela(tabela, valor);
				if(retorno != 0){
					printf("\tValor encontrado: %d\n", retorno);
				} else {
					printf("\tValor não encontrado!");
				}
				break;
			case 3:
				mostra_tabela(tabela);
				break;
			default:
				printf("Opção inválida!\n");
		}
	} while(opcao != 0);

	return(0);
}

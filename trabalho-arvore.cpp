#include<iostream>
#include<stdlib.h>
#include<locale.h>
#include<strings.h>

struct Info {
	int CPF;
	char nome[100];
};

struct No {
	Info * info;
	struct No * esq;
	struct No * dir;
};

void insert(No * &arvoreCPF, Info * novo);
void emOrdem(No * arvoreCPF);
void remover(No * &arvoreCPF, int CPF);
int busca(No * arvoreCPF, int num);
No * maiorDireita(No * arvoreCPF);
Info * cadastro();

int main(){
	setlocale(LC_ALL,"Portuguese");
	No *arvoreCPF = NULL;
	int CPF;
	int num, op;
	
	while(true){
		system("cls");
		
		printf("\n=== ÁRVORE ===\n");
		emOrdem(arvoreCPF);
		
		printf("\n===\n\nDIGITE 1 PARA INSERÇÃO");
		printf("\nDIGITE 2 PARA REMOVER");
		printf("\nDIGITE 3 PARA BUSCAR");
		printf("\nDIGITE 0 PARA SAIR");
		printf("\n\nOpção: ");
		scanf("%d",&op);
		
		switch(op){
			case 1:
				insert(arvoreCPF, cadastro());
				break;
			case 2:
				printf("\nCPF: ");
				scanf("%d",&CPF);
				remover(arvoreCPF, CPF);
				break;
			case 3:
				printf("\nBUSCAR CPF: ");
				scanf("%d",&num);
				if(arvoreCPF != NULL){
					if(busca(arvoreCPF, num) == 1)
						printf("\nO número %d pertence a árvore!\n", num);
					else
	   	 		 		printf("\nO número %d NÃO pertence a árvore!\n", num);
				}else {
					printf("\nÁrvore vazia!\n", num);
				}
				system("pause");
				break;
			case 0:
				exit(0);
				break;
			default:
				printf("\nComando não encontrado\n");
				system("pause");
				break;	
		}	
	}
}

//parte da operação de remoção 
//retorna maior cpf da sae para posteriormente ser elevado a nó raiz
No * maiorDireita(No * arvoreCPF){
    if(arvoreCPF->dir != NULL) 
       return maiorDireita(arvoreCPF->dir);
    else{
       No * aux = arvoreCPF;
       
       if(arvoreCPF->esq != NULL) 
          arvoreCPF = arvoreCPF->esq;
       else
          arvoreCPF = NULL;
       return aux;
    }
}

void emOrdem(No * arvoreCPF){
	if(arvoreCPF != NULL){
		emOrdem(arvoreCPF->esq);
		printf(" %d ", arvoreCPF->info->CPF);
		emOrdem(arvoreCPF->dir);
	}
}

void remover(No * &arvoreCPF, int CPF){
	
	if(arvoreCPF != NULL){
		//se valor menor, navega à esquerda
		if(CPF < arvoreCPF->info->CPF){
			remover(arvoreCPF->esq, CPF);
			
		//se valor maior, navega à direita
		} else if(CPF > arvoreCPF->info->CPF){
			remover(arvoreCPF->dir, CPF);
		
		//qunando o valor a ser excluido for encontrado, verificar grau do nó
		}else if(CPF == arvoreCPF->info->CPF){
			No * arvoreAux = arvoreCPF;
			//nó folha
			if(arvoreCPF->esq == NULL && arvoreCPF->dir == NULL){
				arvoreCPF = NULL;
				free(arvoreCPF);
			}
			//apenas um filho
			//		à direita 
			else if(arvoreCPF->esq == NULL && arvoreCPF->dir != NULL){
				arvoreCPF = arvoreCPF->dir;
				arvoreAux->dir = NULL;
				free(arvoreAux);
				arvoreAux = NULL;
			}
			//		à esquerda 
			else if (arvoreCPF->esq != NULL && arvoreCPF->dir == NULL){
				arvoreCPF = arvoreCPF->esq;
				arvoreAux->esq = NULL;
				free(arvoreAux);
				arvoreAux = NULL; 
			}
			//dois filhos 
			else {
				//pega o maior cpf da sae
				arvoreAux = maiorDireita(arvoreCPF->esq);
				
				//remove o cpf da arvore utilizando métodos acima 
				remover(arvoreCPF, arvoreAux->info->CPF);
				
				//atualiza raiz com o novo cpf
				arvoreCPF->info = arvoreAux->info;
			}
		}
	}else if(arvoreCPF == NULL){
		printf("\nÁrvore vazia!\n");
		system("pause");
		
	}else{
		printf("\nCPF não encontrado\n");
		system("pause");
	}
}

//inicia interface para alocação de memória e preenchimento de dados para um novo cliente 
Info * cadastro(){
	Info * dados = (Info*) malloc(sizeof(Info));
	printf("\n======= CADASTRO =======");
	printf("\nInsira o nome: ");
	fflush(stdin); gets(dados->nome);

	printf("Insira o CPF: ");
	scanf("%d", &dados->CPF);
	return dados;
}

void insert(No * &arvoreCPF, Info * novo){
	/* Essa função insere os elementos de forma recursiva */
	
	if(arvoreCPF == NULL)
	{
		arvoreCPF = (No*) malloc(sizeof(No)); /* Aloca memória para a estrutura */
		arvoreCPF->esq = NULL; /* Subárvore à esquerda é NULL */
		arvoreCPF->dir = NULL; /* Subárvore à direita é NULL */
		arvoreCPF->info = novo; /* Armazena a informação */
		
		//std::cout << arvoreCPF->info->CPF;
	} else {
		if(novo->CPF < arvoreCPF->info->CPF) /* Se o número for menor então vai pra esquerda */ 
		{
			  /* Percorre pela subárvore à esquerda */
				insert(arvoreCPF->esq, novo);
		}
		if(novo->CPF > arvoreCPF->info->CPF) /* Se o número for maior então vai pra direita */
		{
		  /* Percorre pela subárvore à direita */
			insert(arvoreCPF->dir, novo);
		}
	}
}

//se o elemento for encontrado, retorna 0, senão, retorna 1
int busca(No * arvoreCPF, int num){
	
	if(arvoreCPF == NULL)
		return 0;
	
	if(num == arvoreCPF->info->CPF || busca(arvoreCPF->esq, num) || busca(arvoreCPF->dir, num))
		return 1;
}

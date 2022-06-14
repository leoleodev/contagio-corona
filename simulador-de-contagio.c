#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(){
	
//	DEFINIÇÃO DAS VAIRÁVEIS:

	int num_linhas=0;
	int num_colunas=0;
	int i=0,j=0, m=0, n=0; // vairiáveis auxiliares para os loops;
	int **espaco_amostral; // declaraçãoo da matriz dinâmica com ponteiros;
	int inspetor=0; // variável responsável por limitar o número de infectados inseridos;
	int taxa_isolamento=0; // taxa de isolamento;
	int num_infect_ini=0; // numero inicial de infectados;
	int espaco_vazio=0; // numero espaços vazios;
	int espaco_cheio=0; // numero de espaços com uma pessoa;
	
	
//	EXPRESSÃO PARA GERAÇÃO DE NUMEROS RANDÔMICOS:
	
	srand (time(NULL));
	
//	COLETA DOS DADOS PARA INICIALIZAÇÃO DA SIMULAÇÃO:

	printf("\n");
	printf("---------- COLETA DAS INFORMACOES SOBRE O ESPACO AMOSTRAL: ----------\n\n");

	printf("Insira o numero de linhas ");
	scanf("%d",&num_linhas);
	printf("Insira o numero de colunas ");
	scanf("%d",&num_colunas);
	printf("Insira valor da taxa de isolamento em porcentagem ");
	scanf("%d",&taxa_isolamento);
	
	do{
		printf("Insira o numero de individuo(s) infectado(s) *(maximo 04) ");
		scanf("%d",&num_infect_ini);
		
		if(num_infect_ini > 0 && num_infect_ini<=4){
			inspetor = 0;
		}else{
			inspetor = 1;
		}
		
	}while( inspetor == 1 );
	
	printf("\n");
	
//	MANIPULAÇÃO DO VALOR DA TAXA DE ISOLAMENTO:
	
	taxa_isolamento = ((num_linhas*num_colunas)*taxa_isolamento)/100;
	
//	DEFINIÇÃO DOS ESPAÇOS:

	espaco_vazio = taxa_isolamento;
	espaco_cheio = (num_linhas*num_colunas)-taxa_isolamento;
	
//	DADOS DE MAPEAMENTO DE PESSOAS INFECTADAS:

	int vet_linha[espaco_cheio];
	int vet_coluna[espaco_cheio];
	int x=0;
	int loops=0;
	int z=0;
	
//	Impressão dos dados colhidos e informações pertinentes:

	printf("\n");	
	printf("---------- INFORMACOES SOBRE O ESPACO AMOSTRAL: ----------\n\n");
	printf(" Quantidade de total de individuos: %d\n", num_linhas*num_colunas);	
	printf(" Quantidade de individuos isolados: %d\n", espaco_vazio);
	printf(" Quantidade de individuos nao isolados: %d\n", espaco_cheio);	
	printf("\n");
	
//	ALOCAÇÃO DINÂMICA DO ESPAÇO AMOSTRAL EM UMA MATRIZ DINÂMICA:
	
	espaco_amostral = (int**) malloc(num_linhas*sizeof(int *));
	
	for(i=0;i<num_linhas;i++){
		espaco_amostral[i] = (int*)malloc(num_colunas*sizeof(int));
	}
		
//	Geração aleatória das posições vazias e posições com pessoas:
	
	// INSERÇÃO DE PESSOAS NOS ESPAÇOS ALEATÓRIOS:
	for(i=0;i<espaco_cheio;i++){
		
		n = rand() % num_linhas;
		m = rand() % num_colunas;
		
		if(espaco_amostral[n][m] == 1){
			i--;
		}else{
			espaco_amostral [n] [m] = 1;
		}		
	}
	
// INSERÇÃO DE VAZIOS NOS ESPAÇOS ALEATÓRIOS:
	for(i=0;i<num_linhas;i++){
		for(j=0;j<num_colunas;j++){
				
			if(espaco_amostral[i][j] != 1){
				espaco_amostral[i][j] = 0;
			}
		}
	}
	
// INSERÇÃO DO INDIVIDUO INFECTADO:
	
	for(i=0;i<num_infect_ini;i++){
		
		n = rand() % num_linhas;
		m = rand() % num_colunas;
		
		if(espaco_amostral[n][m] == 1){
			espaco_amostral [n][m] = 2;
		}
		else{
			i--;
		}	
	}
	
//	IMPRESSÃO DA MATRIZ INCIAL:

	printf("\n----- MATRIZ INCIAL-----\n");

	for(i=0;i<num_linhas;i++){
			for(j=0;j<num_colunas;j++){
				
				if(espaco_amostral[i][j] == 2){
					printf("(%d)", espaco_amostral[i][j]);
				}else{
					printf(" %d ", espaco_amostral[i][j]);
				}			
			}
			printf("\n");
		}

//	INÍCIO DAS ITERAÇÕES

	while(loops == 0){
		
		printf("\n----- iteracao-----\n");
		
		x=-1;
		loops=1;
		z=0;
		
		for(i=0;i<num_linhas;i++){
			for(j=0;j<num_colunas;j++){
				if(espaco_amostral[i][j] == 2){
					x++;
					vet_linha[x] = i;
					vet_coluna[x] = j;
				}
			}
		}
		
		for(i=0;i<num_linhas;i++){
			for(j=0;j<num_colunas;j++){
					
				if(i == vet_linha[z] && j == vet_coluna[z]){
					
					if(espaco_amostral[i+1][j] == 1){
					
						espaco_amostral[i+1][j] = 2;
						loops = 0;
				
					}
					if(espaco_amostral[i][j-1] == 1){
					
						espaco_amostral[i][j-1] = 2;
						loops = 0;
					
					}
					if(espaco_amostral[i-1][j] == 1){
					
						espaco_amostral[i-1][j] = 2;
						loops = 0;
					
					}
					if(espaco_amostral[i][j+1] == 1){
					
						espaco_amostral[i][j+1] = 2;
						loops = 0;
					
					}
					z++;
				}
					
			}			
				
		}		
		
		for(i=0;i<num_linhas;i++){
			for(j=0;j<num_colunas;j++){
				
				if(espaco_amostral[i][j] == 2){
					printf("(%d)", espaco_amostral[i][j]);
				}else{
					printf(" %d ", espaco_amostral[i][j]);
				}			
			}
			printf("\n");
		}		
		printf("\n");
	}
	
//for(i=0;i<num_linhas;i++){
//	free(espaco_amostral[i]);
//}
//free(espaco_amostral);

return 0;
}



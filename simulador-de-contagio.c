#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(){
	
//	DEFINI��O DAS VAIR�VEIS:

	int num_linhas=0;
	int num_colunas=0;
	int i=0,j=0, m=0, n=0; // vairi�veis auxiliares para os loops;
	int **espaco_amostral; // declara��oo da matriz din�mica com ponteiros;
	int inspetor=0; // vari�vel respons�vel por limitar o n�mero de infectados inseridos;
	int taxa_isolamento=0; // taxa de isolamento;
	int num_infect_ini=0; // numero inicial de infectados;
	int espaco_vazio=0; // numero espa�os vazios;
	int espaco_cheio=0; // numero de espa�os com uma pessoa;
	
	
//	EXPRESS�O PARA GERA��O DE NUMEROS RAND�MICOS:
	
	srand (time(NULL));
	
//	COLETA DOS DADOS PARA INICIALIZA��O DA SIMULA��O:

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
	
//	MANIPULA��O DO VALOR DA TAXA DE ISOLAMENTO:
	
	taxa_isolamento = ((num_linhas*num_colunas)*taxa_isolamento)/100;
	
//	DEFINI��O DOS ESPA�OS:

	espaco_vazio = taxa_isolamento;
	espaco_cheio = (num_linhas*num_colunas)-taxa_isolamento;
	
//	DADOS DE MAPEAMENTO DE PESSOAS INFECTADAS:

	int vet_linha[espaco_cheio];
	int vet_coluna[espaco_cheio];
	int x=0;
	int loops=0;
	int z=0;
	
//	Impress�o dos dados colhidos e informa��es pertinentes:

	printf("\n");	
	printf("---------- INFORMACOES SOBRE O ESPACO AMOSTRAL: ----------\n\n");
	printf(" Quantidade de total de individuos: %d\n", num_linhas*num_colunas);	
	printf(" Quantidade de individuos isolados: %d\n", espaco_vazio);
	printf(" Quantidade de individuos nao isolados: %d\n", espaco_cheio);	
	printf("\n");
	
//	ALOCA��O DIN�MICA DO ESPA�O AMOSTRAL EM UMA MATRIZ DIN�MICA:
	
	espaco_amostral = (int**) malloc(num_linhas*sizeof(int *));
	
	for(i=0;i<num_linhas;i++){
		espaco_amostral[i] = (int*)malloc(num_colunas*sizeof(int));
	}
		
//	Gera��o aleat�ria das posi��es vazias e posi��es com pessoas:
	
	// INSER��O DE PESSOAS NOS ESPA�OS ALEAT�RIOS:
	for(i=0;i<espaco_cheio;i++){
		
		n = rand() % num_linhas;
		m = rand() % num_colunas;
		
		if(espaco_amostral[n][m] == 1){
			i--;
		}else{
			espaco_amostral [n] [m] = 1;
		}		
	}
	
// INSER��O DE VAZIOS NOS ESPA�OS ALEAT�RIOS:
	for(i=0;i<num_linhas;i++){
		for(j=0;j<num_colunas;j++){
				
			if(espaco_amostral[i][j] != 1){
				espaco_amostral[i][j] = 0;
			}
		}
	}
	
// INSER��O DO INDIVIDUO INFECTADO:
	
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
	
//	IMPRESS�O DA MATRIZ INCIAL:

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

//	IN�CIO DAS ITERA��ES

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



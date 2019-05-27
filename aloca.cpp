 /* Alocador de Memoria Pessoal
 Ingrid Santos, João Alberto Cappucho
 */
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include <queue>  


#include <stdlib.h>

using namespace std;

#define BESTFIT 0
#define FIRSTFIT 1
#define NEXTFIT 2



typedef struct{

	int inicio;
	int tam;

}livre;

int numeromagico1;   
int numeromagico2; 

char *memoria;
char *novoinicio;

vector <livre> lista;

int politica;

char* ultimaalocacao;
int co = 0;


bool anterior(const livre& x, const livre& y){return (x.inicio < y.inicio);}


void meualoc(int tamanhoMemoria,int politicaMem){

	memoria = (char*) malloc (tamanhoMemoria * sizeof(char));

	politica = politicaMem;

}


void imprimeDados(){
	cout<<endl<<"<<<<<<<<<<<<<<<<<<<<<<<LIVRE<<<<<<<<<<<<<<<<<<<"<<endl<<endl;

	//sort(lista.begin(),lista.end(),anterior);

	int numelementos = 0;
	int maior = 0;
	int somatamanhos = 0;
	

	for(int t=0;t<lista.size();t++){

		numelementos++;
		if(lista.at(t).tam > maior){ maior =  lista.at(t).tam ;}
		somatamanhos += lista.at(t).tam;

		//DEBUG 
		cout<<"espaco: "<<t<<": inicio: "<<lista.at(t).inicio<<" tam: "<<lista.at(t).tam<<endl;
		
	}

	cout<<"Espacos livres:      "<<numelementos<<endl;
	cout<<"Maior espaco livre:  "<<maior<<endl;
	if(numelementos>0){
	cout<<"Media de tamanhos:   "<<somatamanhos/numelementos<<endl;
	}
	cout<<endl;
	cout<<"<<<<<<<<<<<<<<<<<<<<<<<LIVRE<<<<<<<<<<<<<<<<<<<"<<endl<<endl;

}

char *aloca(unsigned short int tamanho){	
	
	cout<<endl<<"<<<<<<<<<<<<<<<<<<<<<<<ALOCANDO<<<<<<<<<<<<<<<<"<<endl<<endl;
	
	

	int tamnecessario = tamanho + 4;

	if( politica == 0){		//***********************************************************BestFit
		
		sort(lista.begin(),lista.end(),anterior);

		int mtp = 0; 		//guarda o indice do menor tamanho possivel
		int modificou = 0;

		for (int i = 0; i < lista.size(); ++i){

			if(lista.at(i).tam > tamnecessario and lista.at(i).tam <= lista.at(mtp).tam ){
				mtp = i;
				modificou = 1;
			}else if(lista.at(i).tam == tamnecessario and lista.at(i).tam <= lista.at(mtp).tam ){
				mtp = i;
				modificou = 2;
			}
		}

		
		if(modificou == 1){
			
			novoinicio = &memoria[lista.at(mtp).inicio];
			//cout<<"novo inicio: "<<&*novoinicio<<endl;
			printf("Indice de inicio do novo processo: %p\n",&*novoinicio);

			//arrumar
			int p;
			for(p=0;p<tamnecessario;p++){
	
				if(p == 0 ){
					//parte 1 do numero magico
					memoria[lista.at(mtp).inicio + p ] = numeromagico1;
				}else if(p == 1){
					//parte 2 do numero magico
					memoria[lista.at(mtp).inicio + p ] = numeromagico2;
				}else if(p == 2){
					//parte 1 do tamanho
					memoria[lista.at(mtp).inicio + p ] = tamnecessario;
				}else if(p == 3){
					//parte 2 do tamanho
					memoria[lista.at(mtp).inicio + p ] = tamnecessario;
				}else{
					//resto
					memoria[lista.at(mtp).inicio + p ] = 'j';
				}
	
				//printf("%d\n",memoria[lista.at(mtp).inicio + p ]);
		
			}

			//modifica o espaco livre
			lista.at(mtp).tam = lista.at(mtp).tam - tamnecessario;
			lista.at(mtp).inicio  =  ((lista.at(mtp).inicio) + tamnecessario);
			sort(lista.begin(),lista.end(),anterior);

			cout<<"Alocou e diminuiu um espaco"<<endl;
			cout<<endl<<"<<<<<<<<<<<<<<<<<<<<<<<ALOCANDO<<<<<<<<<<<<<<<<"<<endl<<endl;
			return novoinicio;

		}else if(modificou == 2){
			
			novoinicio = &memoria[lista.at(mtp).inicio];
			//cout<<"novo inicio: "<<&*novoinicio<<endl;
			printf("Indice de inicio do novo processo: %p\n",&*novoinicio);

			//arrumar
			int p;
			for(p=0;p<tamnecessario;p++){
	
				if(p == 0 ){
					//parte 1 do numero magico
					memoria[lista.at(mtp).inicio + p ] = numeromagico1;
				}else if(p == 1){
					//parte 2 do numero magico
					memoria[lista.at(mtp).inicio + p ] = numeromagico2;
				}else if(p == 2){
					//parte 1 do tamanho
					memoria[lista.at(mtp).inicio + p ] = tamnecessario;
				}else if(p == 3){
					//parte 2 do tamanho
					memoria[lista.at(mtp).inicio + p ] = tamnecessario;
				}else{
					//resto
					memoria[lista.at(mtp).inicio + p ] = 'j';
				}
	
				//printf("%d\n",memoria[lista.at(mtp).inicio + p ]);
		
			}
			
			lista.erase(lista.begin()+mtp);
			sort(lista.begin(),lista.end(),anterior);

			cout<<"Alocou e apagou um espaco"<<endl;
			cout<<endl<<"<<<<<<<<<<<<<<<<<<<<<<<ALOCANDO<<<<<<<<<<<<<<<<"<<endl<<endl;
			return novoinicio;

		}else{
			cout<<"Nao tem espaco para alocar"<<endl;
			cout<<endl<<"<<<<<<<<<<<<<<<<<<<<<<<ALOCANDO<<<<<<<<<<<<<<<<"<<endl<<endl;
			return NULL;
		}


	}
	if( politica == 1){		//********************************************************************************************************************************************FirstFit
		
		sort(lista.begin(),lista.end(),anterior);

		int op = 0;
		

		for (int i = 0; i < lista.size(); ++i){
			
			if(lista.at(i).tam > tamnecessario){			//TAMANHO DO ESPACO MAIOR DO QUE O PROCESSO
				//cout<<"1"<<endl;
				
				novoinicio = &memoria[lista.at(i).inicio];
				//cout<<"novo inicio: "<<&*novoinicio<<endl;
				printf("Indice de inicio do novo processo: %p\n",&*novoinicio);
	
				//arrumar
				int p;
				for(p=0;p<tamnecessario;p++){
	
					if(p == 0 ){
						//parte 1 do numero magico
						memoria[lista.at(i).inicio + p ] = numeromagico1;
					}else if(p == 1){
						//parte 2 do numero magico
						memoria[lista.at(i).inicio + p ] = numeromagico2;
					}else if(p == 2){
						//parte 1 do tamanho
						memoria[lista.at(i).inicio + p ] = tamnecessario;
					}else if(p == 3){
						//parte 2 do tamanho
						memoria[lista.at(i).inicio + p ] = tamnecessario;
					}else{
						//resto
						memoria[lista.at(i).inicio + p ] = 'j';
					}
	
					//printf("%d\n",memoria[lista.at(i).inicio + p ]);
		
				}
				
				//modifica o espaco livre
				lista.at(i).tam = lista.at(i).tam - tamnecessario;
				lista.at(i).inicio  =  ((lista.at(i).inicio) + tamnecessario);
				sort(lista.begin(),lista.end(),anterior);
				

				op = 1 ;
	
	
				
			}else if(lista.at(i).tam == tamnecessario){				//TAMANHO DO ESPACO IGUAL O DO PROCESSO
				//cout<<"2"<<endl;
				
				novoinicio = &memoria[lista.at(i).inicio];
				//cout<<"novo inicio: "<<&novoinicio<<endl;
				printf("Indice de inicio do novo processo: %p\n",&*novoinicio);
	
				//arrumar
				int p;
				for(p=0;p<tamnecessario;p++){
	
					if(p == 0 ){
						//parte 1 do numero magico
						memoria[lista.at(i).inicio + p ] = numeromagico1;
					}else if(p == 1){
						//parte 2 do numero magico
						memoria[lista.at(i).inicio + p ] = numeromagico2;
					}else if(p == 2){
						//parte 1 do tamanho
						memoria[lista.at(i).inicio + p ] = tamnecessario;
					}else if(p == 3){
						//parte 2 do tamanho
						memoria[lista.at(i).inicio + p ] = tamnecessario;
					}else{
						//resto
						memoria[lista.at(i).inicio + p ] = 'j';
					}
	
					//printf("%d\n",memoria[lista.at(i).inicio + p ]);	
				}
	
				//remove esse espaco da lista de livre
				lista.erase(lista.begin()+i);
				sort(lista.begin(),lista.end(),anterior);

				op = 2;
				
	
				
			}else{
				op = 3;
				
			}

			if(op == 1){
				cout<<"Alocou e diminuiu um espaco"<<endl;
				cout<<endl<<"<<<<<<<<<<<<<<<<<<<<<<<ALOCANDO<<<<<<<<<<<<<<<<"<<endl<<endl;
				return novoinicio;

			}else if(op == 2){
				cout<<"Alocou e apagou um espaco"<<endl;
				cout<<endl<<"<<<<<<<<<<<<<<<<<<<<<<<ALOCANDO<<<<<<<<<<<<<<<<"<<endl<<endl;
				return novoinicio;
			}else if(op == 3){
				cout<<"Nao tem espaco para alocar"<<endl;
				cout<<endl<<"<<<<<<<<<<<<<<<<<<<<<<<ALOCANDO<<<<<<<<<<<<<<<<"<<endl<<endl;
				return NULL;
			}else{
				cout<<"Nao tem espaco para alocar"<<endl;
				cout<<endl<<"<<<<<<<<<<<<<<<<<<<<<<<ALOCANDO<<<<<<<<<<<<<<<<"<<endl<<endl;
				return NULL;
			}


		}
	}
	if( politica == 2){		//**************************************************************************************************************NextFit
		
		sort(lista.begin(),lista.end(),anterior);

		if(co = 0){ ultimaalocacao = &memoria[lista.at(0).inicio];co = 1;}					//COMECA A VERIFICAÇÃO PELO COMECO DOS ENDERECOS
		

		if( ultimaalocacao == &memoria[lista.at(lista.size()-1).inicio]){			//DEU UMA VOLTA NOS ENDERECOS
			ultimaalocacao = &memoria[lista.at(0).inicio];
		}

		cout<<"ultima "<<&*ultimaalocacao<<endl;



		for (int i = 0; i < lista.size(); ++i){


			if(lista.at(i).tam > tamnecessario and (&memoria[lista.at(i).inicio] > ultimaalocacao) ){			//TAMANHO DO ESPACO MAIOR DO QUE O PROCESSO
				//cout<<"1"<<endl;
				
				novoinicio = &memoria[lista.at(i).inicio];
				ultimaalocacao = &*novoinicio;
				//cout<<"novo inicio: "<<&*novoinicio<<endl;
				printf("Indice de inicio do novo processo: %p\n",&*novoinicio);
	
				//arrumar
				int p;
				for(p=0;p<tamnecessario;p++){
	
					if(p == 0 ){
						//parte 1 do numero magico
						memoria[lista.at(i).inicio + p ] = numeromagico1;
					}else if(p == 1){
						//parte 2 do numero magico
						memoria[lista.at(i).inicio + p ] = numeromagico2;
					}else if(p == 2){
						//parte 1 do tamanho
						memoria[lista.at(i).inicio + p ] = tamnecessario;
					}else if(p == 3){
						//parte 2 do tamanho
						memoria[lista.at(i).inicio + p ] = tamnecessario;
					}else{
						//resto
						memoria[lista.at(i).inicio + p ] = 'j';
					}
	
					//printf("%d\n",memoria[lista.at(i).inicio + p ]);
		
				}
				

				//modifica o espaco livre
				lista.at(i).tam = lista.at(i).tam - tamnecessario;
				lista.at(i).inicio  =  ((lista.at(i).inicio) + tamnecessario);
				sort(lista.begin(),lista.end(),anterior);

				cout<<"Alocou e criou um espaco"<<endl;
				cout<<endl<<"<<<<<<<<<<<<<<<<<<<<<<<ALOCANDO<<<<<<<<<<<<<<<<"<<endl<<endl;
				return novoinicio;
	
	
				
			} else if(lista.at(i).tam == tamnecessario and (&memoria[lista.at(i).inicio] > ultimaalocacao) ){				//TAMANHO DO ESPACO IGUAL O DO PROCESSO
				//cout<<"2"<<endl;
				
				
				novoinicio = &memoria[lista.at(i).inicio];
				ultimaalocacao = &*novoinicio;
				//cout<<"novo inicio: "<<&novoinicio<<endl;
				printf("Indice de inicio do novo processo: %p\n",&*novoinicio);
	
				//arrumar
				int p;
				for(p=0;p<tamnecessario;p++){
	
					if(p == 0 ){
						//parte 1 do numero magico
						memoria[lista.at(i).inicio + p ] = numeromagico1;
					}else if(p == 1){
						//parte 2 do numero magico
						memoria[lista.at(i).inicio + p ] = numeromagico2;
					}else if(p == 2){
						//parte 1 do tamanho
						memoria[lista.at(i).inicio + p ] = tamnecessario;
					}else if(p == 3){
						//parte 2 do tamanho
						memoria[lista.at(i).inicio + p ] = tamnecessario;
					}else{
						//resto
						memoria[lista.at(i).inicio + p ] = 'j';
					}
	
					//printf("%d\n",memoria[lista.at(i).inicio + p ]);	
				}
	
				//remove esse espaco da lista de livre
				lista.erase(lista.begin()+i);
				sort(lista.begin(),lista.end(),anterior);

				cout<<"Alocou e apagou o espaco"<<endl;
				cout<<endl<<"<<<<<<<<<<<<<<<<<<<<<<<ALOCANDO<<<<<<<<<<<<<<<<"<<endl<<endl;
				return novoinicio;
	
				
			}else{
	
				cout<<"Nao tem espaco para alocar"<<endl;
				cout<<endl<<"<<<<<<<<<<<<<<<<<<<<<<<ALOCANDO<<<<<<<<<<<<<<<<"<<endl<<endl;
				return NULL;
			}
		}
	}
	

	
	
}

char* verifica(char* ponteiro,int posicao=0){

	cout<<endl<<"<<<<<<<<<<<<<<<<<<<<<<<VERIFICANDO<<<<<<<<<<<<<"<<endl<<endl;

	if(ponteiro != NULL){

		printf("Ponteiro: %p\n",&*ponteiro);
		//printf("%c\n",*ponteiro);
		//printf("%c\n",*(ponteiro+1));
	
		if(*ponteiro == numeromagico1 and *(ponteiro+1) == numeromagico2 ){
			cout<<"Endereco em uso"<<endl;
			cout<<endl<<"<<<<<<<<<<<<<<<<<<<<<<<VERIFICANDO<<<<<<<<<<<<<"<<endl<<endl;
			return ponteiro;
		}else{
			cout<<"Endereco livre"<<endl;
			cout<<endl<<"<<<<<<<<<<<<<<<<<<<<<<<VERIFICANDO<<<<<<<<<<<<<"<<endl<<endl;
			return NULL;
		}

	}else{
		cout<<"Ponteiro invalido"<<endl;
		cout<<endl<<"<<<<<<<<<<<<<<<<<<<<<<<VERIFICANDO<<<<<<<<<<<<<"<<endl<<endl;
		return NULL;
	}
	
}


int libera(char* ponteiro){

	cout<<endl<<"<<<<<<<<<<<<<<<<<<<<<<<LIBERANDO<<<<<<<<<<<<<<<<"<<endl<<endl;

	printf("liberando ponteiro: %p\n",&*ponteiro);

	if(verifica(ponteiro,0) != NULL){

		//achar o tamaho
		//printf("%d\n",*(ponteiro+2));
		int tam = *(ponteiro+2);
		cout<<"Tamanho do espaco que sera liberado: "<<tam<<endl;
		int p;
		for(p=0;p<tam;p++){

			//printf("antes da limpeza: %d\n",*(ponteiro+p));
			*(ponteiro+p) = ' ';
			//printf("depois da limpeza: %d\n",*(ponteiro+p));

		}


		cout<<"Liberou"<<endl;

		cout<<"Criando novo espaco livre"<<endl;
		
		//CHECAR SE É PARA ADICIONAR OU ENTAO JUNTAR = CHECAR SE ALGUM COMECA ONDE ESSE TERMINA OU ENTAO TERMINA ONDE ESSE COMECA
		for (int i = 0; i < lista.size(); ++i){

			if( lista.at(i).inicio ==  ((&*ponteiro - &memoria[0]) +  tam) ){		

				lista.at(i).inicio = &*ponteiro - &memoria[0];
				lista.at(i).tam = lista.at(i).tam + tam;
				cout<<"Somou a esquerda de um espaco livre na lista"<<endl;
				break;


			}else if(lista.at(i).inicio + lista.at(i).tam == (&*ponteiro - &memoria[0])){	

				lista.at(i).tam = lista.at(i).tam + tam;
				cout<<"Somou a direita de um espaco livre na lista"<<endl;
				break;

			}else{

				//adiciona espaco livre
				livre novo;
				novo.inicio = &*ponteiro - &memoria[0] ;
				printf("Indice do espaco alocado: %d\n",novo.inicio);
				novo.tam = tam;
				lista.push_back(novo);	
				cout<<"Adicionou o espaco livre na lista"<<endl;
				break;

			}

		}
		
		cout<<endl<<"<<<<<<<<<<<<<<<<<<<<<<<LIBERANDO<<<<<<<<<<<<<<<<"<<endl<<endl;
		return 1;

	}else{

		cout<<"Quer liberar espaco nao alocado"<<endl;
		cout<<endl<<"<<<<<<<<<<<<<<<<<<<<<<<LIBERANDO<<<<<<<<<<<<<<<<"<<endl<<endl;
		return 0;

	}

}




int main(){

	numeromagico1 =  rand() % 100;
	numeromagico2 =  rand() % 100;

	int n;
	cout<<"Insira o n:"<<endl;
	cin>>n;

	int politica;
	cout<<"Escolha a politica - BESTFIT (0), FIRSTFIT(1) ou NEXTFIT(2):"<<endl;
	cin>>politica;

	//memoria = (char*) malloc (n * sizeof(char));

	meualoc(n,politica);

	printf("endereco da memoria: %p\n",&memoria);
	printf("endereco da memoria[0]: %p\n",&memoria[0]);

	

	livre inicio;

	inicio.inicio = 0;
	inicio.tam = n;
	lista.push_back(inicio);

	/*inicio.inicio = 21;
	inicio.tam = 50;
	lista.push_back(inicio);

	inicio.inicio = 71;
	inicio.tam = 10;
	lista.push_back(inicio);

	inicio.inicio = 81;
	inicio.tam = 40;
	lista.push_back(inicio);*/

	
	imprimeDados();

	char *processo1;
	char *processo2;
	char *processo3;

	processo1 = aloca(10);
	processo2 = aloca(10);

	verifica(processo1,0);
	verifica(processo2,0);

	//libera(processo1);
	//libera(processo2);

	imprimeDados();

	processo3 = aloca(8);

	imprimeDados();

	//final
	free(memoria);

	return 0;
}
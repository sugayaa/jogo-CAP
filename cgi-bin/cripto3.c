#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define KEY 3

typedef struct user{
	char nome[300];
	char senha1[300];
	char senha2[300];
	int nivel;
}usuario;


int tamNome(char *ponteiro);
void ferramenta_arquivo(int opcao, usuario a);
void crip1(char *nome);
void crip2(char *nome);
void Desafio1(char *senha,char *nome);
void Desafio2(char *nome);
void Desafio3(char *nome);

int main(int argc, char** argv)
{
	srand(time(NULL));
	int nivel;
	char nome[300],senha[300],senha1[300],senha2[300];
	char *seq, *pGuardar, *data, *auxnome,*psenha;
	int valor,i=0, achou=0, j=0;
	FILE *escreve, *consulta, *adiciona;
	usuario jogador, auxiliar;

	freopen("arquivo.txt","w",stderr);
	escreve = fopen("log.dat","wb");
	adiciona = fopen("log.dat","ab");
	consulta = fopen("log.dat","rb");

	data = getenv("QUERY_STRING");
	seq = strstr(data,"nome=");

	if(data == NULL)
		printf("<P>Erro! Erro na passagem dos dados \n");
	else
	{
		if (seq != NULL)
		{


			//Recortando nome
			if(strstr(seq,"&")==NULL){				/*~~~~~~~~~~~~~~~~~~~~~~*/			
				//						//Formatos do data:	//
				pGuardar= strstr(seq,"nome=");			//nome=umnome		//
				pGuardar+=5;					//			//
				//						//nome=umnome&senha=abc	//
				strcpy(nome,seq+5);				/*~~~~~~~~~~~~~~~~~~~~~~*/

			}else{				
				pGuardar = strstr(seq,"&");
				strncpy(nome,seq+5,pGuardar-(seq+5));//auxnome-> posição &nivel...  (10)-(0+5) = tamanho nome da pessoa
			}


			while(nome[i]!=0 && nome[i]!=13){ //Diferente de nulo e enter
				if(nome[i]==43)	
					nome[i]=32; //O data query vem com os espaços trocados pelo +, aqui estamos destrocando
				i++;
			}

			//Escrita do nome antes de inserí-lo na função crip
			strcpy(senha1,nome);
			strcpy(senha2,nome);

			/**********************VERIFICA SE  O JOGADOR SE EXISTE NO ARQUIVO******************************************/


			while(fread(&auxiliar,sizeof(usuario),1,consulta)!= 0){
				if(strcmp(nome,auxiliar.nome)==0){
					achou=1;
					break; 
				}
			}

			/************************************************************************************************************/


			if(achou==0){

				//Escrita do nome na struct
				strcpy(jogador.nome,nome);

				//f(x)=y
				crip1(senha1);
				strcpy(jogador.senha1,senha1);


				//g(x)=z
				crip2(senha2);
				strcpy(jogador.senha2,senha2);

				//Nivel 0, já que não foi achado cadastro anterior
				jogador.nivel = 0;
				fwrite(&jogador,sizeof(usuario),1,adiciona);
				fclose(adiciona);
			}
			if(achou==1){	//Caso "achou", a struct auxiliar está com os parâmetros do jogador
				freopen("arquivo.txt","w",stderr);
				strcpy(jogador.nome, auxiliar.nome);
				strcpy(jogador.senha1,auxiliar.senha1);
				strcpy(jogador.senha2,auxiliar.senha2);
				jogador.nivel = auxiliar.nivel;
				//Agora todos os parâmetros se encontram em jogador, caso ele tenha jogado antes ou não
			}
			nivel=jogador.nivel;

			if(nivel==0){


				//Recebendo senha enviada e verificando se está correta
				if(strstr(data,"senha=")!=NULL){ //Caso na URL contenha &senha=
					psenha = strstr(data,"senha=");
					strcpy(senha,psenha+6);

					if(strcmp(senha,jogador.senha1)==0){//Caso acerta a senha
						//atualizar no arquivo, struct auxiliar está apontando para nome achado
						auxiliar.nivel=1;
						nivel++;
						fwrite(&auxiliar,sizeof(usuario),1,escreve);
						fclose(escreve);
					}else{ //Caso erre
						Desafio1(jogador.senha1,jogador.nome);
					}
				}else {
					Desafio1(jogador.senha1,jogador.nome);
				}
			}
			if(nivel==1){

				Desafio2(jogador.nome);
				jogador.nivel=2;
				nivel++;
				fwrite(&auxiliar, sizeof(usuario),1,escreve);
				fclose(escreve);
			}
			if(nivel==2){

				Desafio3(jogador.nome);
				if(strstr(data,"senha=")!=NULL){
					psenha = strstr(data,"senha=");
					pGuardar = &data[strlen(data)];
					strncpy(senha1,psenha+6,pGuardar-(psenha+6));
					senha1[strlen(senha1)-1] ='\0';

					if(strcmp(senha1,senha2)==0){
						//printa tela de fim
						printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);

						printf("<meta http-equiv=\"refresh\" content=\"0; url=http://cap.dc.ufscar.br/~743576/terminei.html\">");						
						//atualizar no arquivo, struct auxiliar está apontando para nome achado					
						auxiliar.nivel=3;
						nivel++;
						fwrite(&auxiliar,sizeof(usuario),1,escreve);
						fclose(escreve);
					}

				}
			//}else{
			}
		}else{	
				printf("<P>Erro! Parametro nao encontrado \n");
		//	}

		}
	}//ADICIONEI NA ULTIMA EDICAO
	return 0;
}

int tamNome(char *ponteiro){
	int tamanho=0;
	while(*ponteiro!=0 && *ponteiro!=13){
		ponteiro++;
		tamanho++;
	}
	return tamanho;
}

/*
   void ferramenta_arquivo(int opcao, usuario a){
   FILE *escreve, *consulta, *adiciona;
   switch(opcao){

   case 1:
   escreve = fopen("log.dat","wb");
   fwrite(&a,sizeof(usuario),1,escreve); //Perguntar para o antonio onde esta o ponteiro
   fclose(escreve);
   break;
   case 2:
   adiciona = fopen("log.dat","ab");
   fwrite(&a,sizeof(usuario),1,adiciona);
   fclose(adiciona);
   break;
   case 3:
   consulta = fopen("log.dat","rb");
   fread(&a,sizeof(usuario),1,consulta);
   fclose(consulta);
   break;

   }

   }
   */
/*
 *
 *PRIMEIRA CRIPTO
 *
 */

void crip1(char *var){

	int l=0,k=1, tam_nome=0, i=0;
	while(var[i]!=0 && var[i]!=13){ //0 = espaço nulo no vetor, 13 = ENTER
		i++;
		tam_nome++;

	}

	char nome[tam_nome];

	for(i=0;i<=tam_nome;i++){
		nome[i]=var[i];
	}

	if(tam_nome%2==0){

		for(i=0;i<(tam_nome/2);i++){
			var[i] = nome[l];
			l=l+2;
		}
		for(i=(tam_nome)/2;i<=tam_nome;i++){
			if(k<=tam_nome){
				var[i]=nome[k];
			}
			if(k>tam_nome){
				var[i]='\0';
			}
			k=k+2;
		}

	}
	if(tam_nome%2!=0){
		l=0;
		for(i=0;i<=(tam_nome)/2;i++){

			var[i] = nome[l];
			l = l+2;
		}

		for(i=(tam_nome/2)+1;i<=tam_nome;i++){
			var[i] = nome[k];
			k= k+2;
		}
	}


}


/*
 *
 *SEGUNDA CRIPTO
 *
 */

void crip2(char *nome_crip){

	int i,tam_nome,controle_cesar=23;
	tam_nome = strlen(nome_crip);

	fprintf(stderr, "size: %d\n", tam_nome);
	for(i=0;i<tam_nome;i++){

		if((nome_crip[i]+KEY>'Z'&&nome_crip[i]+KEY<'a')||nome_crip[i]+KEY>'z'){  
			nome_crip[i] = nome_crip[i] - controle_cesar;          
		}                                                         

		else{
			if(nome_crip[i]==32){                                  
				nome_crip[i] = 32;                            
			}
			else{
				nome_crip[i] = nome_crip[i] +3;
			}
		}
	}

	nome_crip[tam_nome]='\0';  

}

/*
 *
 *Printa Desafio1
 *
 */
void Desafio1(char *senha, char *nome){
	int l;

	printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
	//freopen("log2.txt","w",stdout);
	printf("<!DOCTYPE html>\n<html>\n");

	//AQUI VAI O TITULO
	printf("<title>Desafio 0</title>");

	//CORPO
	printf("<em>MASSS, SEU COMPUTADOR ACABA DE SER HACKEADO</em>, voc&ecirc; tem uma hora para recuperar o acesso ao seu computador antes que seu chefe chegue, apesar de habilidoso o criminoso deixou algumas falhas para tr&aacute;s. Boa sorte!");
	printf("<h3>A senha est&aacute; nessa p&aacute;gina</h3>");
	printf("<form action=\"cripto\">\nSenha:<input type=\"hidden\" name=\"nome\" value=\"%s\"> <input type=\"text\" name=\"senha\" size=\"50\">\n<input type=\"submit\"  value=\"Pr&oacute;ximo\">\n</form>", nome);

	for(l=0;l<296;l++)
		printf("<br>\n");

	printf("<div align=\"right\"><font size=\"1\" face=\"Verdana\"> Teclando CTRL + U voc&ecirc; pode visualizar o c&oacute;digo fonte da p&aacute;gina</font></div>");
	printf("<!--A sua senha eh: %s -->",senha);
	printf("</html>");

}

/*
 *
 *Printa Desafio2
 *
 */
void Desafio2(char *nome){
	int i, j;
	//freopen("log.txt","w",stdout);
	printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
	printf("<!DOCTYPE><html><body>\n<title>Desafio 2</title>\n</body>\n <b><i>\"For&ccedil;a bruta</b>, mais conhecido como Brute-force, consiste em um m&eacute;todo de tentativa e erro para a obten&ccedil;&atilde;o de algo desejado. Um ataque de for&ccedil;a bruta consiste no atacante tentar a maior quantidade de senhas ou chaves poss&iacute;veis a fim de eventualmente descobrir a correta.\"\n</i>\n<br>\n<br>\nApesar de hoje em dia n&atilde;o ser muito eficaz, boa sorte ao tentar encontrar o bot&atilde;o.\n<br>\n<br>\n<p>\nSim, bot&atilde;o. >:)\n<br>\n<br>\n");

	//GERA n BOTOES antes do botao verdadeiro

	for(i=0;i<rand()%237;i++)
		printf("<input type=\"button\" name=\"botao%d\" value=\"Clique Aqui!\">\n<br>\n<p>\n", i);

	//BOTAO VERDADEIRO

	printf("<form action=\"desafio3\">\n<input type=\"hidden\" name=\"nome\" value=\"%s\"><input type=\"submit\" value=\"Clique Aqui!\">\n</form>\n<p>\n",nome);

	//GERA n BOTOES depois do botao verdadeiro 

	for(j=0;j<rand()%216;j++)
		printf("<input type=\"button\" name=\"botao%d\" value=\"Clique Aqui\">\n<br>\n<p>\n", i+j);
	printf("</html>\n");

}
/*
 *
 *
 *Imprime desafio3
 *
 */
void Desafio3(char *nome){

	printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
	printf("<!DOCTYPE html>\n<html>\n");

	//AQUI VAI O TITULO
	printf("<title>Desafio 3</title>");

	//CORPO
	printf("<body background=\"https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQ32C5GtBTm2IbsNwYVNdPSOVCv9xTQ1hqyAtRi9X2fotqjAsk82w\" bgproperties=\"fixed\">");
	printf("<form action=\"cripto\"><input type=\"hidden\" name=\"nome\" value=\"%s\">\nSenha: <input type=\"text\" name=\"senha\" size=\"50\">\n<input type=\"submit\" value=\"Enviar\">\n</form>",nome);
	printf("<img \" vspace=\"15px\" hspace=\"200px\" title=\"A resposta esta na imagem\" width=\"600px\" height=\"600px\"  src=\"https://lh3.googleusercontent.com/gng6rflm2gY4rQ-HVST2mtI0dacf0aWzETn9s4JU6xqM_2GTQO4cjFUbwL0yC7Tu5kcRh64Mv_YltGE=w1366-h612-rw\"/>");
	printf("</body>");
	printf("</html>");


}

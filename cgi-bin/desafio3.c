#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY 3

typedef struct user{
	char nome[300];
	char senha1[300];
	char senha2[300];
	int nivel;
}usuario;

void cript2(char *nome);
void Desafio3(char *nome);

int main(){
	char *data, *seq, *p;
	char nome[300], senha[300];

	freopen("arquivo.txt","w",stderr);
	data = getenv("QUERY_STRING");
	seq = strstr(data,"nome=");

	if(data == NULL)
		printf("<P>Erro! Erro na passagem dos dados \n");
	else
	{ 
		if (seq != NULL)//Caso nao receba a senha pela URL
		{
			if(strstr(data,"&senha=")==NULL){
				strcpy(nome,seq+5);//Recebe o nome e imprime o desafio3
				Desafio3(nome);
			}else{
				p =strstr(data,"&senha=");	//Se recebe senha
				strcpy(senha,p+7);		
				strncpy(nome,seq+5,p-(seq+5));	//Recebe nome da URL com senha
				nome[strlen(nome)-1]='\0';	
				fprintf(stderr,"nome: %s\n", nome);
				
				cript2(nome);			
				fprintf(stderr,"nome: %s\n", nome);
				fprintf(stderr,"senha: %s\n", senha);

				//Caso as senhas estiverem corretas
				if(strcmp(nome,senha)==0){	//Caso usuario acerta senha
					printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
					printf("<meta http-equiv=\"refresh\" content=\"0; url=http://cap.dc.ufscar.br/~743605/terminei.html\">");
				}else{
					Desafio3(nome); //Caso nao acerte imprimir desafio3 novamente
				}
			}
		}

	}
}

void cript2(char *nome){

	int i,tam_nome,controle_cesar=23;
	tam_nome = strlen(nome);


	for(i=0;i<tam_nome;i++){

		if((nome[i]+KEY>'Z'&&nome[i]+KEY<'a')||nome[i]+KEY>'z'){
			nome[i] = nome[i] - controle_cesar;
		}

		else{
			if(nome[i]==32){
				nome[i] = 32;
			}
			else{
				nome[i] = nome[i] +3;
			}
		}
	}

	nome[tam_nome]='\0';


}

void Desafio3(char *nome){

	printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
	printf("<!DOCTYPE html>\n<html>\n");

	//AQUI VAI O TITULO
	printf("<title>Desafio 3</title>");

	//CORPO
	printf("<body background=\"https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQ32C5GtBTm2IbsNwYVNdPSOVCv9xTQ1hqyAtRi9X2fotqjAsk82w\" bgproperties=\"fixed\">");
	printf("<form action=\"desafio3\"><input type=\"hidden\" name=\"nome\" value=\"%s\">\nSenha: <input type=\"text\" name=\"senha\" size=\"50\">\n<input type=\"submit\" value=\"Enviar\">\n</form>",nome);
	printf("<br>\n<br>\n<a href=\"https://goo.gl/BtmtFD\" target=\"_blank\">Pedir ajuda</a><br>\n<br>\n");
	printf("<img \" vspace=\"15px\" hspace=\"300px\" title=\"A resposta esta na imagem\" width=\"600px\" height=\"600px\"  src=\"../cesar.png\"/>");
	printf("</body>");
	printf("</html>");


}

#include <stdio.h>
#include <math.h>  //Biblioteca matematica
#include <locale.h> // biblioteca caracteres especiais
#include <string.h>
#include <stdlib.h> // bibliotea que faz a leitura de caracteres digitados
#include "systemAcademico.c"

int main(){ //funcao principal que inicia o programa
	setlocale(LC_ALL, "Portuguese");//permite usar caracteres especiais do portugues
	char opcao[1], op2[1];
	int numero=0;
	Function_GetFiles(); // function que vai pegar todos os dados do arquivo
	while(numero != 8){
		printf(" (1) \t Cadastrar Aluno\n"); // DONE!
		printf(" (2) \t Cadastrar disciplina\n"); // DONE!
		printf(" (3) \t Matricular na disciplina\n"); // DONE!
		printf(" (4) \t Registrar notas e faltas\n"); //DONE!
		printf(" (5) \t Remover Aluno\n");
		printf(" (6) \t Remover disciplinas\n");
		printf(" (7) \t Consultas\n"); //  DONE!
		printf(" (8) \t Sair\n"); // DONE!
		
		printf("\nEntre com o Codigo da action: ");
		scanf("%s",&opcao);

//		CODIGO QUE FARÁ  SEMPRE REPETIR O WHILE QUANDO A FOR DIGITADO STRINGS E NÚMEROS
		op2[0] = opcao[0];
		op2[1] = '\0';
		numero = atoi(op2);
		if(numero >= 1 && numero <= 7){
			acaoSisAcademico(numero);	
		}
		system("clear || cls");
	}
	//if (numero == 9) acaoSisAcademico(numero);

    return 0;
}





		

#include <stdio.h>
#include <locale.h> // biblioteca caracteres especiais
#include <string.h>
#include <stdlib.h> // bibliotea que faz a leitura de caracteres digitados
#include <conio.h> // usar getch() similar ao system("pause")

struct id_Tudo{
	int idp ; // chave de matricula dos alunos, essa propriedade serve para criar o contador  para registrar todos os estudantes
	int idcd; // chave de cadastro de disciplinas
	int idga; // chave de cadastro de alunos nas materias
};
struct id_Tudo it;

//struct matricula aluno
struct matricula_Aluno{
	int key_mA;
	char nome[101];
	char sexo[1];
	int idade;	
	char email[101];
};
struct matricula_Aluno mA[1000];
// fim da matricula aluno

//STRUCT QUE FAZ O CADASTRO DAS DISCIPLINAS
struct cadastro_Diciplina{ 
	int key_cD;
	char nome_materia[101];
	int fk_prof; // chave estrangeira professor
	int carga_H;
	int qtd_avaliao;
};
struct cadastro_Diciplina c_D[100];
// FIM DA STRUCT DE CADASTRO DE DISCIPLINAS

//struct que representa a grade curricular do aluno por periodo
struct grade_Aluno{
	int fk_mA; // chave estrangeira matricula_Aluno
	int semestre[11] ;
	int semestre_materia[11][11]; // essa matriz permite armazena 10 semestres em cada semestre 10 materias
	float notas[11][11][11]; //semestre[],materia[], até 10 indices notas[]
	int faltas[11][11][1]; //semestre[],materia[], até 10 indices faltas[]
	float media_nota[11][11][1]; //semestre[],materia[], até 10indices media notas[]
	float media_falta[11][11][1]; //semestre[],materia[], até 10indices medias de falta[]
};
struct grade_Aluno g_A[1000];
//fim dagrade do aluno


/**********************MENU 1 ************************/
//CADASTRAR ALUNOS---------(1)
int Matricular_Aluno(){	
	int sair = 1;
	char s[1];
	while(sair == 1){
		printf("Digite o nome do aluno: ");
		scanf(" %100[^\n]", &mA[it.idp].nome);
		
		printf("Entre com o sexo do Aluno:\n(m - Masculino || f - Feminino) ");
		scanf("%s",&s);
		mA[it.idp].sexo[0] = tolower(s[0]); // so da pra transformar string minuscula se for caracter por caracter
		//mA[it.idp].sexo[1] = '\0';
		
		printf("Digite a idade do aluno: ");
		scanf("%d", &mA[it.idp].idade);
			
		printf("Digite o e-mail do aluno: ");
		scanf(" %100[^\n]", &mA[it.idp].email);
		
		mA[it.idp].key_mA = it.idp;
		
		printf("\nID Aluno = %d\nNome = %s\nSexo = %s\nidade = %d\nemail = %s\n",mA[it.idp].key_mA, mA[it.idp].nome,mA[it.idp].sexo, mA[it.idp].idade, mA[it.idp].email);
		
		it.idp++;
		
		printf("\nCadastrar mais Aluno?\n1 - SIM || 2 - NOT\t ");
		scanf("%d",&sair);
		if(sair != 1 ) break;	
	}
}

//CADASTRAR DISCIPLINA---------(2)
int Cadastrar_Diciplina(){
	int sair = 1;
	while(sair == 1){
				
		printf("Escreva o nome da disciplina: ");
		scanf(" %100[^\n]", &c_D[it.idcd].nome_materia);
		
//		printf("Digite o nome do professor da disciplina: ");
//		scanf(" %100[^\n]", &NomeProf[IDD]);
		
		printf("Carga horaria: ");
		scanf("%d",&c_D[it.idcd].carga_H);
		
		printf("Quantas avaliaçoes aplicar: (max. 10) ");
		scanf("%d",&c_D[it.idcd].qtd_avaliao);
		if (c_D[it.idcd].qtd_avaliao > 0 && c_D[it.idcd].qtd_avaliao <= 10){ // verifica se o usuario colocou o num de 1 a 10
		}else {
			printf("Quantidade de notas invalido.\n");
			continue;
		}
		c_D[it.idcd].key_cD = it.idcd;
		
		printf("\nCodigo = %d\nDisciplina = %s\nCarga horaria = %d\nQuantidade de Avaliaçoes = %d\n",c_D[it.idcd].key_cD, c_D[it.idcd].nome_materia, c_D[it.idcd].carga_H, c_D[it.idcd].qtd_avaliao);
		
		it.idcd++;
			
		printf("\nDeseja cadastrar outra disciplina agora?\n1 - SIM || 2 - NOT\t");
		scanf("%d",&sair);
	}
}

//FUNCAO QUE MATRICULA ALUNO NAS DISCIPLINAS ---(3)
int Matricular_Aluno_Diciplina(){
	system("cls");
	int sair = 1;
    while(sair == 1){ 
		int i,cod_m,cod_aluno;
		for(i=1; i< it.idcd; i++){ // estrutura de repeticao for que vai printa todas as disciplinas
			if(c_D[i].key_cD <= 0) continue; // se o codigo da disciplina for 0 ou negativo significa que a disciplina n existe
			printf("(%d)\t Disciplina\t %s\n",i,c_D[i].nome_materia);
		}
		printf("Digite o código da disciplina: ");// entrada do cod da disciplina
		scanf("%d", &cod_m);
		
		if(c_D[cod_m].key_cD == cod_m){ // vai verificar se o codigo da disciplina existe
			int cont=0, g, q;
			printf("Digite o codigo do aluno: "); // entrada do cod do aluno
			scanf(" %d", &cod_aluno);
			if(mA[cod_aluno].key_mA == cod_aluno){ // verifica se o cod do aluno existe
				int n_semestre, b;
				printf("Informe o Semestre: "); // entrada de dado do semestre
				scanf(" %d", &n_semestre);
					
				if(n_semestre >=1 && n_semestre <= 10){ // verifica se o semestre digitado esta entre 1 a 10
					for(g=1;g<=10;g++) {
						if(g_A[cod_aluno].semestre_materia[n_semestre][g] == 0 ){
							break;
						}	
					}
					g_A[cod_aluno].fk_mA = cod_aluno; // chave estrangeira da struct matricula aluno
					g_A[cod_aluno].semestre[n_semestre] = n_semestre;
					g_A[cod_aluno].semestre_materia[n_semestre][g] = cod_m;
					int nM = g_A[cod_aluno].semestre_materia[n_semestre][g];
						
					printf("\nCod = %d \nEstudante = %s\n", g_A[cod_aluno].fk_mA, mA[cod_aluno].nome);
					printf("Semestre = %d\n",g, g_A[cod_aluno].semestre[n_semestre]);
					printf("Materia = %s\n",c_D[nM].nome_materia);
					it.idga++;
				}else printf("Semestre invalido.\n"); // senao semestre						
			}else printf("\nCodigo invalido ou aluno não encontrado.\n"); // senao aluno
		}else printf("Codigo da diciplina invalido.\n");// senao disciplina	
		
		printf("\nDeseja continuar matriculando alunos nas disciplinas:\n1 - SIM || 2 - NOT\t");
		scanf("%d",&sair);
		if(sair != 1) break;
		
	}//fim do while
		
}
//*********************FIM MENU 3*************************//
//*********************MENU 4 ***********************/
// REGISTRO DE NOTAS PARTE 1---------------(4)
int Registrar_Notas(){
	int entraA, i, sair=1;
	while (sair ==1 ){
		printf("Entre com o codigo do Aluno: ");
		scanf("%d",&entraA);
		
		if(entraA >= 1 &&  entraA < it.idp){
			for(i=1; i<it.idp; i++){ // essa estrutura de repeticao vai verificar se a entrada do codigo do aluno bate com alguma chave registrada no sistema
				if(entraA == mA[i].key_mA){
					regi_Notas2(entraA); // CHAMADA DA FUNCAO  REGISTRO DE NOTAS PARTE 2
					break;
				}
				else if(i >= it.idp) {
					printf("\nO Aluno não foi encontrado.\n");
					break;
				}
			}			
		}else printf("\nO codigo do Aluno está inválido.\n");
		
		printf("\nDeseja continuar lançando notas: \n1 - SIM || 2 - NOT\t");
		scanf("%d",&sair);
		if(sair != 1) break;
	}
}
int regi_Notas2(int entraA){ // REGISTRO DE NOTAS PARTE-- 2
	int i, entraS,c_materia;
	
	for(i=1; i <= 10 ;i++){ //estrutura laço que permite mostrar os semestre disponiveis de acordo com o cod do aluno.
		if (g_A[entraA].semestre[i] == 0) continue;
		else printf("(%d)\tSemestre %d\n",i, g_A[entraA].semestre[i]);
	}
	printf("Entre com o número do semestre: ");
	scanf("%d",&entraS);
	
	if(entraS >=1 && entraS <= 10 ){ // essa condicional vai verificar a entrada de dado esta entre 1 a 10
		for(i=1; i <= 10 ;i++){ //estrutura laço que permite mostrar os semestre disponiveis de acordo com o cod do aluno.
			if (g_A[entraA].semestre[i] == entraS) { 
				
				regi_Notas3(entraA, entraS); // CHAMADA DA FUNCAO REGISTRO DE NOTAS PARTE 3
				break;
			}
			else if(g_A[entraA].semestre[i] == 0) continue;	
		}//fim do FOR
		
		if (g_A[entraA].semestre[i] != entraS){
			printf("\nSemestre invalido ou não encontrado.\n");	
		}
		
	}else printf("\nSemestre invalido ou não encontrado.\n");
}
int regi_Notas3(int entraA, int entraS){ // REGISTRO DE NOTAS PARTE-- 3
		int i, entraD, dprint;
		
		for (i=1;i <= 10 ;i++) { //  estrutura que cria o laço que mostrara todas as disciplinas vinculadas no semestre
			if(g_A[entraA].semestre_materia[entraS][i] == 0) continue;
			else {
				dprint = g_A[entraA].semestre_materia[entraS][i];
				printf("(%d)\tDisciplina\t%s\n", dprint, c_D[dprint].nome_materia);
			}
		}
		printf("\nEntre com o código da Disciplina: ");
		scanf("%d",&entraD);
		
		if(entraD >= 1 && entraD < it.idcd){ // essa estrutura vai verificar se o codigo da disciplina esta registrado para o aluno 
			for (i=1;i <= 10 ;i++) {
				if(g_A[entraA].semestre_materia[entraS][i] == entraD){
					regi_Notas4(entraA, entraS, entraD,i); // CHAMADA DA FUNCAO REGISTRO DE NOTAS PARTE 4
					
					break;
				}else if (g_A[entraA].semestre_materia[entraS][i] == 0) continue;
			}	//FIM DO FOR
		}else printf("\nCodigo da Disciplina invalido.\n");
}
int regi_Notas4 (int entraA, int entraS, int entraD, int i){ // CHAMADA DA FUNCAO REGISTRO DE NOTAS PARTE-- 4
	int ii,ava,sair=1, qtdfaltas,cont=0; // ava significa avaliacao, essa variavel esta recebendo a quantidade de provas por disciplina
	float soma_notas=0, mediaNota, mediafalta, mediafrequencia;
	ava = c_D[entraD].qtd_avaliao;
	
	printf("\nPara a disciplina %s será feito %d avaliação(ões).\n", c_D[entraD].nome_materia, c_D[entraD].qtd_avaliao);
	
	for (ii=1; ii <= ava; ii++){
		printf("Entre com a %dª nota: ",ii);
		scanf("%f",&g_A[entraA].notas[entraS][i][ii]);
		cont++;
		soma_notas += g_A[entraA].notas[entraS][i][ii];
	}
	mediaNota = soma_notas / cont;
	//mediaNota = soma_notas;
	g_A[entraA].media_nota[entraS][i][0] = mediaNota; // passa para a variavel do struct o valor da media
	
	while(sair == 1){
		printf("\nEntre com a quantidade de faltas: ");
		scanf("%d",&qtdfaltas);	
		if(qtdfaltas < c_D[entraD].carga_H){
			g_A[entraA].faltas[entraD][i][0] = qtdfaltas; // entrada com a quantidade de faltas
			break;
		}else{
			printf("\nA quantidade de faltas ultrapassa a carga horaria da disciplina.\n");
		}
	}
	mediafalta = (qtdfaltas * 100) / c_D[entraD].carga_H;
	mediafrequencia = 100 - mediafalta;
	g_A[entraA].media_falta[entraS][i][0] = mediafalta;
	
	printf("\n%s atingiu a media de %.2f pontos no %dº semestre na disciplina  %s.\n", mA[entraA].nome, mediaNota, g_A[entraA].semestre[entraS] ,c_D[entraD].nome_materia);
	printf("%s tem %d faltas com frenquencia de %.2f porcento.\n",mA[entraA].nome, qtdfaltas, mediafrequencia);
}
//********************************************//
/********************MENU 5 E 6 *****************************/
// REMOVE O ALUNO
int Remover_Aluno(){ // FUNCTION MENU 5
	int sair=1, entraA,removerA;
	while(sair == 1){
		printf("Entre com o codigo do aluno: ");
		scanf("%d",&entraA);
		if(mA[entraA].key_mA == entraA){
			printf("Realmente deseja remover %s:\n1 - SIM || 2 - NOT\t", mA[entraA].nome);
			scanf("%d",&removerA);
			if(removerA == 1){
				mA[entraA].key_mA =  - mA[entraA].key_mA ;	
				printf("%s removido com sucesso!\n ",mA[entraA].nome);
			}
		}else printf("Codigo do Aluno invalido.\n");
		
		printf("\nDeseja continuar removendo Alunos?\n1 - SIM || 2 - NOT \t");
		scanf("%d",&sair);	
	}	
}
// REMOVE A DISCIPLINA
int Remover_Disciplina(){ // FUNCTION DO MENU 6
	int sair=1,entraD, removerD;
	while(sair == 1){
		printf("Entre com o codigo da Disciplina: ");
		scanf("%d",&entraD);
		if(c_D[entraD].key_cD == entraD){
			
			printf("Realmente deseja remover %s:\n1 - SIM || 2 - NOT\t", c_D[entraD].nome_materia);
			scanf("%d",&removerD);
			
			if(removerD == 1){
				c_D[entraD].key_cD = - c_D[entraD].key_cD ;
				printf("%s removido com sucesso!\n ",c_D[entraD].nome_materia);
			}
		}else printf("Codigo da Disciplina invalido.\n");
		
		printf("Deseja continuar removendo Disciplinas?\n1 - SIM || 2 - NOT \t");
		scanf("%d",&sair);
		
	}
	
}
/*********************FIM MENU 5 E 6*************************/

////**********************MENU 7 ***************************//
//// FUNCAO DE APENAS CONSULTA DOS ALUNOS REGISTRADOS 
int pesquisa_Aluno(){ // função de consulta alunos
	int sair = 1;
	while(sair == 1){
		int consultaR, entraA, i, j, k,a,num;
		
		printf("(1)\t Consultar todos os Aluno\n");
		printf("(2)\t Consultar pelo Código do Aluno\n");
		printf("Entre com o codigo da ação: ");
		scanf("%d",&consultaR);
		if(consultaR == 1){ // consulta de todos os alunos
			for(i=1;i < it.idp;i++){
				if(mA[i].key_mA <=0 ) continue; // esse condicional vai impedir mostrar na tela os alunos que foram removidos
				printf("\nID\t=\t %d\n",mA[i].key_mA);
				printf("Nome\t=\t %s\n",mA[i].nome);
				printf("Sexo\t=\t %s\n",mA[i].sexo);
				printf("Idade\t=\t %d\n",mA[i].idade);
				printf("E-mail\t=\t %s\n",mA[i].email);
			
				for(j=1; j <= 10 ;j++){ // LAÇO QUE LÊ AS OS MATERIAS E SEMESTRES REGISTRADAS NA PESSOA
					if(g_A[i].semestre[j] == 0) continue;
					else {
						printf("Semestre: %d\nDisciplinas: ",g_A[i].semestre[j]);
						for(k=1; k <= 10; k++){ // vai mostrar as materias de cada semestre
							if(g_A[i].semestre_materia[j][k] == 0) continue;
							a = g_A[i].semestre_materia[j][k];
							printf("%s  ",c_D[a].nome_materia);
						}
						printf("\n");	
					} 
				}
			}
		}else{ // pesquisa especifica por aluno
//sem o tratamento de erro da entrada do codigo do usuario
			printf("Entre com o codigo do Aluno: ");
			scanf("%d",&entraA);

			if(mA[entraA].key_mA <= 0) {// esse condicional vai impedir mostrar na tela os alunos que foram removidos
				printf("Codigo do Aluno não encontrado.\n");
				break;	
			}else{
				printf("\nID\t=\t %d\n",mA[entraA].key_mA);
				printf("Nome\t=\t %s\n",mA[entraA].nome);
				printf("Sexo\t=\t %s\n",mA[entraA].sexo);
				printf("Idade\t=\t %d\n",mA[entraA].idade);
				printf("E-mail\t=\t %s\n",mA[entraA].email);
				
				for(i=1;i<10;i++){ // estrtura de repeticao aninhado para mostrar o resultado do semestre e as disciplinas registradas
					if(g_A[entraA].semestre[i] == 0) continue;
					printf("Semestre: %d\nDisciplinas: ",g_A[entraA].semestre[i]);
					for(k=1; k <= 10; k++){ // vai mostrar as materias de cada semestre
						if(g_A[entraA].semestre_materia[i][k] == 0) continue;
						a = g_A[entraA].semestre_materia[i][k];
						printf("%s  ",c_D[a].nome_materia);
					}
					printf("\n");
				}//fim da estrutura de repeticao que informa as materias e o semestre
			}
		}// fim da condicional que consulta o aluno pelo codigo	
		printf("\nDeseja consultar novamente?\n1 - SIM || 2 - NOT\t");
		scanf("%d",&sair);
		if (sair != 1) break;
	}
}
//CONSULTA DE NOTAS
int pesquisa_Nota(){
	char action[1];
	printf("(1)\tPesquisar por Disciplina\n"); // feito
	printf("(2)\tPesquisar por Aluno\n");
	//printf("(3)\tConsultar todos os resultados\n");
	printf("Entre com o codigo da option: ");
	scanf("%s",&action);
	
	if(strcmp(action, "1")==0) pesquisaNotasOp1();
	//else if (strcmp(action, "2")==0) pesquisaNotasOp2();
	else pesquisaNotasOp2();
}
// pesquisa de notas OPCAO 1
int pesquisaNotasOp1(){
	int entraD, i, j, entraS;
	for(i=1; i<it.idcd ; i++){
		if(c_D[i].key_cD > 0) printf("(%d)\tDisciplina %s\n",i, c_D[i].nome_materia);
	}
	printf("Entre com o codigo da disciplina: ");
	scanf("%d",&entraD);
	if(entraD >= 1 && entraD < it.idcd){
		printf("Entre com o codigo do semestre: ");
		scanf("%d",&entraS);
		if(entraS >= 1 && entraS <= 10){
			for(i=1; i < it.idp ;i++){
				if(mA[i].key_mA <= 0) continue; // esse condicional vai impedir mostrar na tela os alunos que foram removidos
				for(j=1; j <= 10; j++){
					if(g_A[i].semestre_materia[entraS][j] ==  entraD){				
						mostrarNotas1(entraD, entraS,i,j);
						break;
					}
				}
			}
		}else printf("Codigo do semestre invalido");
	}else printf("Codigo invalido.\n");
}
int mostrarNotas1(int entraD, int entraS,int i,int j){
	int k;
	char rmnota[30], rmfalta[30];
	printf("\nCod = %d\nNome = %s\nSemestre = %d\nDisciplina: %s\n",mA[i].key_mA, mA[i].nome, entraS, c_D[entraD].nome_materia );
	for(k=1; k <= 10 ;k++){
		if(g_A[i].notas[entraS][j][k] == 0) break;
			printf("Nota %d = %.2f\n", k, g_A[i].notas[entraS][j][k]);
	}
	if(g_A[i].media_nota[entraS][j][0] > 6) strcpy(rmnota,"Aprovado por nota");
	else strcpy(rmnota,"Reprovado por nota");
	if(g_A[i].media_falta[entraS][j][0] > 25 ) strcpy(rmfalta,"Reprovado por falta");
	else strcpy(rmfalta,"Aprovado por frequencia");
	
	printf("Nota media: %.2f (%s) ", g_A[i].media_nota[entraS][j][0],rmnota);
	printf("\nFrequencia: %.2f porcento (%s)\n\n",100 - g_A[i].media_falta[entraS][j][0], rmfalta);
}
//PESQUISA NOTAS OPCAO 2
int pesquisaNotasOp2(){
	int entraA,i;
	
	printf("Entre com o codigo do aluno: ");
	scanf("%d",&entraA);
	
	if(entraA >=1 && entraA < it.idp){
		if(mA[entraA].key_mA == entraA) {
			printf("\nEstudante = %s\n",mA[entraA].nome);
			mostrasemestreop2(entraA);
		}else printf("Codigo do Aluno invalido.\n");
	}else printf("Codigo do Aluno invalido.\n");
}
int mostrasemestreop2(int entraA){
	int i;
	for (i=1;i<=10;i++){
		if (g_A[entraA].semestre[i] == 0) continue;
		printf("Semestre %d\n",g_A[entraA].semestre[i]);
		mostranotasop2(entraA,i);
	}
}
int mostranotasop2(int entraA, int i){
	int j, escritaD,qtdnotas,k;
	char rmnota[30],rmfalta[30];
	
	for(j=1;j<=10;j++){
		if (g_A[entraA].semestre_materia[i][j] == 0) continue;
		escritaD = g_A[entraA].semestre_materia[i][j];
		
		printf("Disciplina %s\n",c_D[escritaD].nome_materia);
		for(k=1;k<= c_D[escritaD].qtd_avaliao;k++){
			printf("Nota %.2f  ",g_A[entraA].notas[i][j][k]);
		}
		
		if(g_A[entraA].media_nota[i][j][0] > 6) strcpy(rmnota,"Aprovado por nota");
		else strcpy(rmnota,"Reprovado por nota");
		if(g_A[entraA].media_falta[i][j][0] > 25 ) strcpy(rmfalta,"Reprovado por falta");
		else strcpy(rmfalta,"Aprovado por frequencia");
		
		printf("Nota media: %.2f (%s) ", g_A[entraA].media_nota[i][j][0],rmnota);
		printf("\nFrequencia: %.2f porcento (%s)\n",100 - g_A[entraA].media_falta[i][j][0], rmfalta);
	}
}
// fim da opcao 2
//CONSULTA DAS DISCIPLINAS
int pesquisadisciplina(){
	int i;
	printf("\n");
	for (i=1;i< it.idcd;i++){
		if(c_D[i].key_cD > 0) printf("Disciplina (%d)\t%s\tCarga horaria %d\n",i, c_D[i].nome_materia, c_D[i].carga_H);
	}
}
// HEART DA OPTION 5
int Consultas(){
	int consulta;
	printf("(1)\tPesquisar Alunos\n"); //feito
	printf("(2)\tPesquisar Notas dos Alunos\n"); //feito
	printf("(3)\tConsultar Disciplinas\n"); 
	printf("Entre com o codigo da ação: ");
	scanf("%d",&consulta);
	if(consulta == 1) pesquisa_Aluno();
	else if (consulta == 2) pesquisa_Nota();
	else pesquisadisciplina();
}
/*******************FIM MENU 7***********************/

//	MENU DE ACOES DISPONIVEIS QUE INICIA O PROGRAMA
int acaoSisAcademico(int numero){	
	switch(numero){
		case 1: //Cadastrar Aluno
			Matricular_Aluno();
		break;
		case 2: // Cadastrar disciplina
			Cadastrar_Diciplina();
		break;
		case 3: // Matricular na disciplina
			Matricular_Aluno_Diciplina();
		break;  
		case 4: // Lançar notas e faltas
			Registrar_Notas(); 
		break;
		case 5: // remove o aluno
			Remover_Aluno();
		break;
		case 6: // remove a disciplina
			Remover_Disciplina();
		break;
		case 7: // Consultas
			Consultas();
		break;

	}
	functionID(); // atualiza o id do aluno e disciplina
	functionAluno(); // atualiza o cadastro dos alunos
	functionDisciplina();
	functionGradeAluno();
	printf("\nPrecione \"ENTER\" para continuar ");
	getch();
//	system("pause");
}
//funcoes que salvam as informacoes no arquivo txt
int functionID(){ // ids
	FILE *file_id = fopen("Dados/IdTudo.txt", "w");
	if(file_id == NULL){
		printf("Erro na abertura do arquivo!\n");
		getchar();
		return 1;
	}
	fprintf(file_id,"%d\n%d\n%d", it.idp, it.idcd, it.idga); // vai pegar a quantidade de alunos e disciplinas cadastradas
	fclose(file_id);
}
int functionAluno(){ // aluno
	FILE *file_A = fopen("Dados/cadastroAluno.txt", "w");
	int i;
	for(i=1; i < it.idp ; i++){
		fprintf(file_A, "%d\n%s\n%s\n%d\n%s\n",mA[i].key_mA, mA[i].nome, mA[i].sexo, mA[i].idade,mA[i].email);
	}
	fclose(file_A);
}

int functionDisciplina(){ // disciplina
	int i;
	FILE *file_D = fopen("Dados/cadastroDisciplina.txt", "w");
	for(i=1;i< it.idcd ;i++){
		fprintf(file_D,"%d\n%s\n%d\n%d\n", c_D[i].key_cD, c_D[i].nome_materia, c_D[i].carga_H, c_D[i].qtd_avaliao);
	}
	fclose(file_D);
}
int functionGradeAluno(){
	int i,j,k,l;
	FILE *file_GA = fopen("Dados/cadastroGradeAluno.txt", "w");
	if(file_GA == NULL){	
	printf("Erro ao ler o arquivo.\n");
	getch();
	return -1;
	}
	
	for(i=1; i<it.idp; i++){
		if (g_A[i].fk_mA == 0) continue; // condicional que pula a grade do aluno nao matriculado na disciplina	
		for(j=1;j<=10;j++){ // estrutura for que vai verificar se tem o semestreregistrado
			if(g_A[i].semestre[j] == 0) continue; // condicional			
			for(k=1;k<=10;k++){ // materia/disciplina
				if(g_A[i].semestre_materia[j][k] == 0) break; // condicional que sai do for quando chegar no indice 0
				fprintf(file_GA,"%d\n",g_A[i].fk_mA);// inseri no arquivo o id aluno
				fprintf(file_GA,"%d\n",g_A[i].semestre[j]); // inseri do arquivo o cod do semestre
				fprintf(file_GA,"%d\n",g_A[i].semestre_materia[j][k]); //inseri no arquivo o cod da disciplina
				int sm = g_A[i].semestre_materia[j][k]; // passa para variavel o cod da disciplina
				for(l=1; l <= c_D[sm].qtd_avaliao; l++){
					fprintf(file_GA,"%.2f\n",g_A[i].notas[j][k][l]); // notas		
				}
				// inseri no arquivo a media de faltas, media nota, notas, faltas
				fprintf(file_GA,"%d\n%.2f\n%.2f\n",g_A[i].faltas[j][k][0], g_A[i].media_falta[j][k][0], g_A[i].media_nota[j][k][0]);	
			}		
		}
	}
	fclose(file_GA);
}


int Function_GetFiles(){
	int i,j,k,l;
	it.idp = 1;
	it.idga = 1;
	it.idcd = 1;
	FILE *fileid = fopen("Dados/IdTudo.txt", "r");
	if(fileid == NULL) {
		printf("Erro ao ler a arquivo IdTudo\n");
		getch();
		return 0;
	}
	fscanf(fileid,"%d %d %d ",&it.idp, &it.idcd, &it.idga);
	fclose(fileid);
	
	FILE *file_MA = fopen("Dados/cadastroAluno.txt", "r");
	if(file_MA == NULL) {
		printf("Erro ao ler a arquivo cadastroAluno\n");
		getch();
		return 0;
	}
	for(i=1; i < it.idp ; i++){
		if(mA[i].key_mA == -1) continue;
		fscanf(file_MA," %d %100[^\n] %100[^\n] %d  %100[^\n]", &mA[i].key_mA, &mA[i].nome, &mA[i].sexo, &mA[i].idade, &mA[i].email);
	}
	fclose(file_MA);
	
	FILE *file_DC = fopen("Dados/cadastroDisciplina.txt", "r");
	if(file_DC == NULL) {
		printf("Erro ao ler a arquivo cadastroDisciplina\n");
		getch();
		return 0;
	}
	for(i=1; i < it.idcd ; i++){   
		fscanf(file_DC," %d %100[^\n] %d %d ", &c_D[i].key_cD, &c_D[i].nome_materia, &c_D[i].carga_H, &c_D[i].qtd_avaliao);
	}
	//chamar uma funcao que importa todos os dados do arquivo
	fclose(file_DC);
	
	FILE *fileGA = fopen("Dados/cadastroGradeAluno.txt", "r");
	if(fileGA == NULL){	
		printf("Erro ao ler o arquivo.\n");
		getch();
		return -1;
	}
	int getA, getS, getD;
	for(k=1;k < it.idga; k++){ // vai repetir a quantidade de vezes que foi feito o cadastro nas disciplinas
		fscanf(fileGA," %d %d %d ", &getA, &getS, &getD);// inseri no arquivo o id aluno
		g_A[getA].fk_mA = getA; // cod aluno
		g_A[getA].semestre[getS] = getS; // semestre
		//printf("%d\t%d\t\t",g_A[getA].fk_mA, g_A[getA].semestre[getS]);
		
		for(i=1;i<=10;i++){ // verifica a disciplina
			if(g_A[getA].semestre_materia[getS][i] > 0) continue;
			
			else if(g_A[getA].semestre_materia[getS][i] == 0){
				g_A[getA].semestre_materia[getS][i] = getD;
				//printf("%d\t",g_A[getA].semestre_materia[getS][i]);
				for (j=1; j <= c_D[getD].qtd_avaliao; j++){
					fscanf(fileGA,"%f ", &g_A[getA].notas[getS][i][j]);
					//printf("%.2f\t ",g_A[getA].notas[getS][i][j]);
				}
				fscanf(fileGA,"%d %f %f ", &g_A[getA].faltas[getS][i][0], &g_A[getA].media_falta[getS][i][0], &g_A[getA].media_nota[getS][i][0]);
				//printf("%d\t%.2f\t%.2f\n",g_A[getA].faltas[getS][i][0], g_A[getA].media_falta[getS][i][0], g_A[getA].media_nota[getS][i][0]);
				break;
			}
		}	
	}
	fclose(fileGA);
}



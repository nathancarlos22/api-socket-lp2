#include <iostream>
#include <windows.h>
#include <string>
#include "contas.h"
#include <stdio.h>

using namespace std;

void contas::cadastro(string login, string senha, string ip, string porta) {
	FILE *arq;
	arq = fopen("contas.txt","a");
		
	fprintf(arq, "%s %s %s %s\n", login.c_str(), senha.c_str(), ip.c_str(), porta.c_str());
	system("cls");
	printf("\nConta criada!\n");
	system("pause");
	fclose(arq);

}

bool contas::login(string username, string senha){
	FILE *arq;
	arq = fopen("contas.txt", "rt");
	
	char Cusername[20];
	char Csenha[20];
	char ignore[20];
	char ignore2[20];
	
	while(fscanf(arq, "%s %s %s %s", Cusername, Csenha, ignore, ignore2) != EOF) 
		if(strcmp(Cusername, username.c_str()) == 0 && strcmp(Csenha, senha.c_str()) == 0) {
			this->username = username;
			this->senha = senha;
			this->ip = ignore;
			this->porta = ignore2;
			
			return true;
		}
	
	return false;
	fclose(arq);
}

void contas::argumento(string nome) {
	FILE *arq;
	arq = fopen("contas.txt", "rt");
	
	char Cusername[20];
	char Csenha[20];
	char ip[20];
	char porta[20];
	
	while(fscanf(arq, "%s %s %s %s", Cusername, Csenha, ip, porta) != EOF) {
		if(strcmp(Cusername, nome.c_str()) == 0) {
			char argv[50];
			sprintf(argv, "Api-socket.exe client %s %s", ip, porta);
			
			system(argv);
			system("pause");
			return;
		
		}
		else{
			cout << "Username nao encontrado!" << endl;
			break;
			return;
			
		}
	}
}
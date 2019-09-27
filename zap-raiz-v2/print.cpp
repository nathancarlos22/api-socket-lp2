#include <iostream>
#include <windows.h>
#include "print.h"

using namespace std;

void print::menu() {
	system("cls");
	cout << "\n TELA INICIAL \n";
	cout << "1. Cadastrar\n2. Login\n3. Sair" << endl;
	
}

void print::login() {
	system("cls");
	cout << "\n TELA LOGIN \n";	
	cout << "1. Envar mensagem\n2. Participar de uma conversa\n3. Logout" << endl;
	
}

void print::printContas(){
	FILE *arq;
	arq = fopen("contas.txt", "rt");
	
	char Cusername[50], Csenha[50], ip[50], porta[50];
	
	cout << "********Contas**********" << endl;
	while(fscanf(arq, "%s %s %s %s", Cusername, Csenha, ip, porta) != EOF) {
		
		printf("\n");
		
		cout << "User: " << Cusername << endl;
		cout << "Ip: " << ip << endl;
		cout << "Porta: " << porta << endl;
		printf("\n");
	
	}
	fclose(arq);
}

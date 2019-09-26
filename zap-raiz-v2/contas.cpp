#include <iostream>
#include <windows.h>
#include <string>
#include "contas.h"
#include <stdio.h>
#include <thread> 
//#include <tchar.h>
//#include <strsafe.h>

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

void contas::argumentoClient(string nome) {
	FILE *arq;
	arq = fopen("contas.txt", "rt");
	
	char Cusername[20];
	char Csenha[20];
	char ip[20];
	char porta[20];
	char argumento4[20];
	
	while(fscanf(arq, "%s %s %s %s", Cusername, Csenha, ip, porta) != EOF) {
		if(strcmp(Cusername, nome.c_str()) == 0) {
			char argv[50];
			sprintf(argv, "start Api-socket.exe client %s %s %s", "2", ip, porta);
			
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
void contas::argumentoServidor() {
	char argv[50];
	sprintf(argv, "start Api-socket.exe servidor %s", this->porta.c_str());
	system(argv);
}

void argumento (string nome, string buffer) {
	FILE *arq;
	arq = fopen("contas.txt", "rt");
	
	char Cusername[20];
	char Csenha[20];
	char ip[20];
	char porta[20];
	
	while(fscanf(arq, "%s %s %s %s", Cusername, Csenha, ip, porta) != EOF) {
		if(strcmp(Cusername, nome.c_str()) == 0) {
			char argv[50];
			sprintf(argv, "start Api-socket.exe client %s %s %s %s", "1", ip, porta, buffer.c_str());
			
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
void contas::enviar (int x) {
	//contas *c = new contas();	
	string nome;
	string buffer;
	string usuarios[x];
	
	cout << "Digite a mensagem: ";
	cin.ignore();
	getline(cin, buffer);
	
	for(int i=0; i<x; i++){
		cout << "Digite o nome dos " << x << " usuarios: ";
		
		cin >> nome;
		usuarios[i] = nome;
	
	}
	thread * enviar = new thread[x];
	for(int i=0; i<x; i++){
		enviar[i] = thread(argumento, usuarios[i], buffer);			
	}
	
	for(int i=0; i<x; i++){
		enviar[i].join();
	}
	
	delete [] enviar;
}

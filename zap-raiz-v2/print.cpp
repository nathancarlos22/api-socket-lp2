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
	cout << "1. Envar mensagem privada\n2. Enviar mensagem para mais de uma pessoa\n3. Logout" << endl;
	
}

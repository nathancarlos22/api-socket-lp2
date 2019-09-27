#include <iostream>
#include <windows.h>
#include "print.h"
#include "contas.h"

using namespace std;

int main (){
	print *p = new print();
	contas *c = new contas();
	int x;
	while(x != 3){
		p->menu();
		
		cin >> x;
		switch(x){
			case 1:
				{
				string login, senha, ip, porta;
				
				cout<<"\nDigite seu LOGIN: ";
			    cin >> login;
			    
			    cout << "\nDigite sua SENHA: ";
			    cin >> senha;
			    
			    cout << "\nDigite sua seu IP: ";
			    cin >> ip;
			    
			    cout << "\nDigite a sua PORTA: ";
				cin >> porta;
				
				c->cadastro(login, senha, ip, porta);
				break;
				}
			case 2:
				{
				string username, senha;
				
				cout << "Usuario: ";
				cin >> username;
				cout << "\nSenha: ";
				cin >> senha;
				
				if(c->login(username, senha) == false) 
					cout << "Nao possivel logar" << endl;
				else
				{
					cout << "Logado com sucesso! " << endl;
					
					int op;
					while(op!= 3){
						p->login();
						cin >> op;
						
						switch(op) {
							case 1:
								{
								string destino;
								cout << "Digite o nome de usuario do destinatario: ";
								cin >> destino;
								
								c->argumentoClient(destino);
								break;
								}
							
							case 2:
								{
									c->argumentoServidor();
									break;
								}
							case 3:
								break;
							
						}
					}
					op=0;
				}
				system("pause");
				break;
				}
			case 3:
				break;
		}
	}
}

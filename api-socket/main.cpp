#include<iostream>
#include <winsock2.h>
#include <stdio.h>
#include <string>
#include "Includes/Headers/InetAddress.h"
#include "Includes/Headers/ExcessaoHost.h"
#include "Includes/Headers/Socket.h"
#include "Includes/Headers/ServerSocket.h"
#include <thread>
#include <process.h>
#include <vector>

using namespace std;

void send_clients(){
	
}

void send_msg(Socket *s){
	char message[1024] = "Connectado";
	while(true) {
		s->send(message, 1024);
		memset(message, 0, 1024);
		cout << "Envie: ";
		cin.getline(message, 256);
	}

}

void rec_msg(Socket *s) {
	char buffer[1024];
	
	while (true) {
		memset(buffer, 0, 1024);
		s->recv(buffer, 1024);
		cout << "Recebeu: " << buffer << endl;
	}
}

int main(int argc, char *argv[])
{
	vector <Socket*> clientes;
	//Inicializando winsock
	WSADATA wsaData;
    int iResult;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup falhou: %d\n", iResult);
        return 1;
    }
    try {
        InetAddress *IA;
        Socket *s;
        char ip[50];
        int porta;
        char buffer[1024];
        if (strcmp(argv[1], "servidor") == 0) {
            porta = atoi(argv[2]);
            
            try {
                ServerSocket *ss;
                ss = new ServerSocket(porta);
                
                while(true){
					s = ss->accept();
                
					//rec_msg(s);
					thread t1(rec_msg, s);
					clientes.push_back(s);
					//t1.join();
                }
				
            }catch(UnknownHostException &u){
                cout << u.what() << endl;
            }catch(IOException &io) {
                cout << io.what() << endl;
            }
            system("pause");
        }
        if (strcmp(argv[1], "client") == 0) {
            //cout << "ip: " << endl;
            //cin >> ip;
            // cout << "porta: " << endl;
			//cin >> porta;
			
			strcpy(ip, argv[3]);
            porta = atoi(argv[4]);
            //strcpy(buffer, argv[5]);
            //printf("%s %s"), buffer, argv[5];
            try {
                //IA = InetAddress::getByName(ip); /*Se quiser pegar pelo nome ou endereco eh so aqui*/
                IA = InetAddress::getByAddress(ip);
                s = new Socket(IA, porta);
				if (strcmp(argv[2], "1") == 0) {
					strcpy(buffer, argv[5]);
					s->send(buffer, strlen(buffer));
					
					cout << "enviado" << endl;
					system("pause");
				}
				if (strcmp(argv[2], "2") == 0){
					thread t2(send_msg, s);
					t2.join();
					
				}
				//vector<thread> threads;
				
            }catch(UnknownHostException &u) {
                cout << u.what() << endl;
            }catch(IOException &io) {
                cout << io.what() << endl;
            }
        }
	}
	catch(UnknownHostException &a){
	    cout << a.what() << endl;
	}
	return 0;
}

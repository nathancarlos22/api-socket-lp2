#include<iostream>
#include <winsock2.h>
#include <stdio.h>
#include <string>
#include "Includes/Headers/InetAddress.h"
#include "Includes/Headers/ExcessaoHost.h"
#include "Includes/Headers/Socket.h"
#include "Includes/Headers/ServerSocket.h"

using namespace std;

int main(int argc, char *argv[])
{
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
            
            try{
                ServerSocket *ss;
                ss = new ServerSocket(porta);
                s = ss->accept();

                while(true) {
                    s->recv(buffer, 1024);
                    if (strcmp(buffer, "sair") == 0)
                        break;
                    cout << buffer << endl;
                    memset(&buffer, 0, sizeof(buffer));
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
			
			strcpy(ip, argv[2]);
            porta = atoi(argv[3]);
            //strcpy(buffer, argv[4]);
            
            try {
                //IA = InetAddress::getByName(ip); /*Se quiser pegar pelo nome ou endereco eh so aqui*/
                IA = InetAddress::getByAddress(ip);
                s = new Socket(IA, porta);

                while(true) {
					cout << "Digite a msg ('sair' para sair)" << endl;
					cin.getline(buffer,1024);
                    s->send(buffer, strlen(buffer));
					if (strcmp(buffer, "sair") == 0) break;
					
                }
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

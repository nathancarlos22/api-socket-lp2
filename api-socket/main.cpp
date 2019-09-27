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
#include <pthread.h>
#include <chrono>
#include <unistd.h>

using namespace std;

int pessoas=0;
int clientesConectados[50];
vector <Socket*> ListaSockets;
//Socket *ListaSockets[10];

constexpr std::chrono::seconds operator ""s(unsigned long long s)
{
    return std::chrono::seconds(s);
}

void *send_clientes(void *b){
	char buffer[1024];
	char *buffer2 = ((char*)b);

	strcpy(buffer, buffer2);



}

void *send_msg(void *x){
	Socket *s = ((Socket*)x);
	char message[1024];
	cout << "Envie: ";
	while(true) {
		printf("\n");
		//cout << "Envie: ";
		cin.getline(message, 1024);
		s->send(message, strlen(message));

		if(strcmp(message, "sair") == 0){
			break;
		}
	}
	printf("saiu\n");
}


void *rec_msg(void *x) {
	Socket *s = ((Socket*)x);
	char buffer[1024];

	while(true){
		memset(&buffer, 0, sizeof(buffer));
		s->recv(buffer, 1024 );
		printf("\n");
		cout << "Recebeu: **" << buffer << "**"<< endl;

	/*Envia para uma lista de pessoas*/
		for(int i=0; i<(ListaSockets.size()); i++) {
				//IA = ListaSockets[i]->getLocalAddress();
			char resultado[1024];           /*gambiarra pra poder colocar a primeira pessoa como pessoa 1 e a segunda 2... etc*/
			char parte2[1024]= "da Pessoa ";
			char buffer2[1024];
			sprintf(resultado, " %s %s", parte2, s->nome);
			strcpy(buffer2, buffer);
			strcat(buffer, resultado);

			if(ListaSockets[i] == s) {
				//memset(&buffer, 0, sizeof(buffer));
				strcpy(buffer, buffer2);
				continue; /*se o socket que enviou for igual ao oq ta na lista, pula, volta pro for, nao executa o send*/
			}
			ListaSockets[i]->send(buffer, strlen(buffer));

			//memset(&buffer, 0, sizeof(buffer));
			strcpy(buffer, buffer2);
		}

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

        pthread_t t1, t2, t3;
		//char nome[50];
        if (strcmp(argv[1], "servidor") == 0) {
            porta = atoi(argv[2]);
            //printf("%s", argv[3]);

            try {
                ServerSocket *ss;
                ss = new ServerSocket(porta);

                while(true){
					s = ss->accept();
					strcpy(s->nome, argv[3]);
					//s->nome = nome;
					//ListaSockets[pessoas] = (s);
					ListaSockets.push_back(s);
					pessoas++;

					pthread_create(&t1, 0, rec_msg, (void*)s);
				}
				//pthread_join(t1, 0);

            }catch(UnknownHostException &u){
                cout << u.what() << endl;
            }catch(IOException &io) {
                cout << io.what() << endl;
            }
            system("pause");
        }
        if (strcmp(argv[1], "client") == 0) {

			strcpy(ip, argv[3]);
            porta = atoi(argv[4]);

            try {
                //IA = InetAddress::getByName(ip); /*Se quiser pegar pelo nome ou endereco eh so aqui*/
                IA = InetAddress::getByAddress(ip);
                s = new Socket(IA, porta);
				if (strcmp(argv[2], "1") == 0) { /*Argumento 1 envia so uma mensage e para*/
					system("pause");
				}

				if (strcmp(argv[2], "2") == 0){ //argumento 1 pergunta para enviar a msg
					pthread_create(&t2, 0, send_msg, (void *)s);
					pthread_create(&t3, 0, rec_msg, (void*)s);
					pthread_join(t3, 0);
				}
				//pthread_join(t2, 0);


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

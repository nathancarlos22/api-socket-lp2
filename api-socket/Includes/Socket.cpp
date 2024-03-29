#include <iostream>
#include <winsock2.h>
#include "Headers/ExcessaoHost.h"
#include "Headers/Socket.h"

using namespace std;

//descritor do socket
Socket::Socket(){
    this->descritor = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

};

void Socket::connect(InetAddress *remoteAddr)throw (IOException, UnknownHostException){

    this->descritorRemote = ::connect(this->descritor, (struct sockaddr *) &(this->localAddr)->ip_address, sizeof(remoteAddr->ip_address));

    if (this->descritorRemote == SOCKET_ERROR){

        throw IOException("Erro ao conectar");
    }

};

Socket::Socket(string hostName, int port) throw (IOException, UnknownHostException){
    this->remotePort = port;

    this->remoteAddr  = InetAddress::getByName(hostName);
    this->remoteAddr->ip_address.sin_port = htons(port);

    this->localAddr = InetAddress::getLocalHost();
    this->localAddr->ip_address.sin_port = htons(port);


    this->connect(this->remoteAddr);

    };

Socket::Socket(InetAddress *addr, int port)  throw (IOException){

    this->descritor = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (this->descritor == INVALID_SOCKET){

       throw IOException("Erro ao criar o socket");
    }

    this->remotePort = port;

    this->remoteAddr  = addr;
    this->remoteAddr->ip_address.sin_port = htons(port);

    this->localAddr = InetAddress::getLocalHost();
    this->localAddr->ip_address.sin_port = htons(port);

    this->connect(this->remoteAddr);

};

int Socket::send(char * msg, int size) throw (IOException){
    //int message_length = strlen(msg);
    this->descritorRemote = ::send(this->descritor, msg, size, 0);
        // envia a mensagem para o servidor
    if (this->descritorRemote == SOCKET_ERROR)
    {
        throw IOException("Erro");
    }
    return this->descritorRemote;

};
    //sobrecarregando operador para enviar msg
void Socket::operator>>(const char* msg) throw (IOException)
{
};
    //Ler size bytes do socket remoto e armazena no array msg.
int Socket::recv(char * msg,int size) throw (IOException)
{
    int message_length = ::recv(this->descritor, msg, size, 0);

    if(message_length == SOCKET_ERROR)
        throw IOException("Erro na mensagem");

    return message_length;

};

    //Retorna o endere�o em que o socket est� conectado.
InetAddress* Socket::getInetAddress(){
    return this->remoteAddr;

};

    //Retorna o endere�o local em que o socket est� amarrado.
InetAddress* Socket::getLocalAddress(){

    return this->localAddr;

};
    //Retorna o n�mero porta local em que o socket est� amarrado.
int Socket::getLocalPort(){

    return this->localPort;


};
    //Retorna o n�mero da porta remota em que o socket est� conectado.
int Socket::getPort(){

    return this->remotePort;
};

int Socket::getDescritor(){
    return this->descritor;
}


/*Cria um socket e o conecta a um n�mero de porta e em um endere�o IP espec�ficos.*/

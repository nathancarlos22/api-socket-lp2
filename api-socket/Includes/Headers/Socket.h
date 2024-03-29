#ifndef SOCKET_H
#define SOCKET_H

#include "InetAddress.h"
#include "ExcessaoHost.h"
#include "IOException.h"
#include <stdio.h>
class Socket
{
public:
    //Cria um objeto socket n�o conectado.
    Socket();
    //Cria um socket e com um ip e porta
    Socket(InetAddress *addr, int port) throw (IOException);
    //Cria um socket e o conecta para um n�mero de porta e nome de host espec�fico.
    Socket(string hostName, int port) throw (IOException, UnknownHostException);
    //Fecha este socket.
    void close() throw (IOException);

    //Envia a string no array msg para o socket remoto.
    void operator<<(const char* msg) throw (IOException);
    //envia informacao a um socket conectado
    int send(char * msg, int size) throw (IOException);
    //Ler a string do socket remoto e armazena no array msg.
    void operator>>(const char* msg) throw (IOException);
    //recebe informacao de um socket conectado
    int recv(char * msg,int size) throw (IOException);

    //Retorna o endere�o em que o socket est� conectado.
    InetAddress *getInetAddress();
    //Retorna o endere�o local em que o socket est� amarrado.
    InetAddress *getLocalAddress();
    //Retorna o n�mero porta local em que o socket est� amarrado.
    int getLocalPort();
    //Retorna o n�mero da porta remota em que o socket est� conectado.
    int getPort();
    char nome[50];

    int getDescritor();
    ~Socket();//destrutor
      int descritorRemote;
private:
    void connect(InetAddress* remoteAddr)throw (IOException, UnknownHostException);
    int descritor;

    int localPort;
    int remotePort;
    InetAddress *localAddr;
    InetAddress *remoteAddr;
    friend void recv_t(Socket *s);
    friend class ServerSocket;

};
#endif // SOCKET_H

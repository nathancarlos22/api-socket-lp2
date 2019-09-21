#include "Headers/ServerSocket.h"

ServerSocket::ServerSocket()throw (IOException){
    this->descritor = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); /*criando socket*/
    if (this->descritor == INVALID_SOCKET)
    {
        throw IOException("Erro");
    }
};

void ServerSocket::bind(int port) throw (IOException){
    this->localAddr->ip_address.sin_port = htons(port);

    if (::bind(this->descritor,(struct sockaddr *)&(*this->localAddr).ip_address, sizeof(this->localAddr->ip_address)) < 0){
        throw IOException("Erro em Bind()");
   }

}

void ServerSocket::listen() throw (IOException){
    if (::listen(this->descritor, 5) < 0){
        throw IOException("Erro no listen()");
    }
}

ServerSocket::ServerSocket(int port) throw (IOException) { // cria o socket local
    this->localAddr = InetAddress::getLocalHost();

    this->descritor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); /*criando socket*/

    if (this->descritor == INVALID_SOCKET || port == 0)
    {
        throw IOException("Erro" + port);
    }
    this->localPort = port;
    this->bind(port); //associa o endereco de ip ao socket
    this->listen();

}

Socket* ServerSocket::accept() throw (IOException)
{
    cout<<"Aceitando conexao"<<endl;
    Socket * remoteSocket;
    remoteSocket = new Socket();

    int remote_length =sizeof(remoteSocket->remoteAddr->ip_address);

    remoteSocket->remoteAddr =  InetAddress::getLocalHost(); //coloca o nome do host
    remoteSocket->descritor = ::accept(this->descritor, (struct sockaddr *)& remoteSocket->remoteAddr->ip_address,&remote_length );

    if(remoteSocket->descritor == INVALID_SOCKET){
         throw IOException("Erro ao aceitar");
    }
    cout<<"Conexao Estabelecida"<<endl;
    return remoteSocket;
}

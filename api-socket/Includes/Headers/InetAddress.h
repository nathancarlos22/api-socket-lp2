#ifndef _INETADDRESS_H
#define _INETADDRESS_H
#include <iostream>
#include <exception>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include "ExcessaoHost.h"

using namespace std;

class InetAddress
{
	public:
		//Retorna o endereço de IP de um host pelo seu nome.
		static InetAddress *getByName(string host) throw(UnknownHostException);
		//Retorna o endereço de IP dando um endereço de IP.
		static InetAddress *getByAddress(string addr) throw (UnknownHostException);
		//Retorna o endereço de IP do host Local.
		static InetAddress *getLocalHost() throw (UnknownHostException);

		//Retorna o Nome do Host.
		string getHostName();
		//Retorna o Endereço de IP do Host.
		string getHostAddress();
		//Destrutor da Classe.
		void setHostName(string hostName);
		void setHostAddr(string hostAddr);
		~InetAddress(){};
		string hostAddr;
	private:
		InetAddress(){};
		static InetAddress *create(struct hostent *ht);
		string hostName; // Variavel que guarda o nome do Host.
		 // Variavel que guarda o Ip do host.
		sockaddr_in ip_address;

		friend class Socket;
		friend class ServerSocket;
};

#endif

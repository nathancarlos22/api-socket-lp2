#include "Headers/InetAddress.h"
#include <ws2tcpip.h>
#include <iostream>

/*retorno normal name e adress do host*/

string InetAddress::getHostName() {
	return this->hostName;
}

string InetAddress::getHostAddress() {
	return this->hostAddr;
}
void InetAddress::setHostName(string host) {
	this->hostName = host;

}

InetAddress *InetAddress::create(struct hostent *he) { /*funcao create cria um objto para retorna-lo*/
	InetAddress * address = new InetAddress(); //alocando endereço
    memset(&(*address).ip_address, 0, sizeof(address->ip_address)); //zera o endereço toda vez que cria um novo

    memcpy(&(*address).ip_address.sin_addr.s_addr, he->h_addr_list[0], he->h_length);
    address->ip_address.sin_family = AF_INET;

    address->hostAddr = string(inet_ntoa(*(struct in_addr*)he->h_addr));
    address->hostName = string(he->h_name);

    return address;
}

InetAddress *InetAddress::getByName(string host) throw (UnknownHostException)
{
	struct hostent *remoteHost;

	remoteHost = gethostbyname(host.c_str()); //pegando o host e transformando em string do c.
	if(remoteHost == NULL)
	{			/*excessao caso o host esteja incorreto*/
		throw UnknownHostException(host + "  is Nonexistent");
	}
	//cout << "Host encontrado!" << endl;
	return InetAddress::create(remoteHost);
}

//Retorna o endereço IP do host local.
InetAddress *InetAddress::getLocalHost() throw (UnknownHostException)
{
    return InetAddress::getByName("localhost");
}

InetAddress *InetAddress::getByAddress(string addr) throw (UnknownHostException)
{
	struct in_addr hostaddr; //estrutura para o endereço do host

	hostaddr.S_un.S_addr = inet_addr(addr.c_str());

	hostent *ht = gethostbyaddr((const char *)&hostaddr, sizeof(hostaddr), AF_INET); //pegando o host
	if(ht == NULL)
	{
		throw UnknownHostException(addr + "  is Nonexistent");
	}

	//cout << "Host encontrado!" << endl;

	return InetAddress::create(ht);
}



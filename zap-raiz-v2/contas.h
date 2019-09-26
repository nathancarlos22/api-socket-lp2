#ifndef CONTAS_H
#define CONTAS_H

#include <iostream>

using namespace std;

class contas {
	public:
		bool login(string username, string senha);
		void cadastro (string nome, string senha, string ip, string porta);
		void argumentoClient(string nome);
		void argumentoServidor();
		void enviar(int x);
		contas(){};
		~contas(){};
	private:
		string username;
		string senha;
		string porta;
		string ip;
		
};
#endif

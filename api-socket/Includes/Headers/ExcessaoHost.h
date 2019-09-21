#ifndef _EXCESSAO_HOST_H
#define _EXCESSAO_HOST_H

#include <exception>

using namespace std;

class UnknownHostException : public exception
{
	public:
		UnknownHostException(string mensagem)
		{
			this->mensagem = mensagem;
		}
		virtual const char* what() const throw()
		{
			return mensagem.c_str();
		}
		virtual ~UnknownHostException() throw(){}
	private:
		string mensagem;
};
#endif

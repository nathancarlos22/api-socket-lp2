#ifndef IOEXCEPTION_H
#define IOEXCEPTION_H

#include<string>
#include<exception>

using namespace std;

class IOException : public exception
{
    public:
        IOException(string mensagem)
        {
            this->mensagem = mensagem;
        }
        virtual const char* what() const throw()
        {
            return mensagem.c_str();
        }
        virtual ~IOException() throw(){}
    private:
        string mensagem;
};
#endif // IOEXCEPTION
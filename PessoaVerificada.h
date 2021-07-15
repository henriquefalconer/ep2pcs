#ifndef PESSOAVERIFICADA_H
#define PESSOAVERIFICADA_H

#include <string>
using namespace std;

#include "Pessoa.h"

class PessoaVerificada: public Pessoa {
   private:
    string email;

   public:
    PessoaVerificada(string nome, string email, int id);
    PessoaVerificada(string nome, string email);
    PessoaVerificada(string nome);
    virtual ~PessoaVerificada();
    // Getters
    string getEmail();
    // Methods
    void imprimir();
};

#endif  // PESSOAVERIFICADA_H

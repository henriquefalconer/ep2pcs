#ifndef PAGINA_H
#define PAGINA_H

#include <string>
using namespace std;

#include "Pessoa.h"

#include "PessoaVerificada.h"

class Pagina: public Pessoa {
   private:
    PessoaVerificada* proprietario;

   public:
    Pagina(string nome, PessoaVerificada* proprietario, int id);
    Pagina(string nome, PessoaVerificada* proprietario);
    virtual ~Pagina();
    // Getters
    PessoaVerificada* getProprietario();
    // Methods
    void imprimir();
};

#endif  // PAGINA_H

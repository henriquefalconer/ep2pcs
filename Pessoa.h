#ifndef PESSOA_H
#define PESSOA_H

#include "Perfil.h"

class Pessoa: public Perfil {
   public:
    Pessoa(string nome, int id);
    Pessoa(string nome);
    virtual ~Pessoa();
};

#endif  // PESSOA_H

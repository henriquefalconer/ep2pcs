#ifndef REDESOCIAL_H
#define REDESOCIAL_H

#include "Perfil.h"

class RedeSocial {
   private:
    vector<Perfil*>* perfis;

   public:
    RedeSocial();
    virtual ~RedeSocial();
    // Getters
    Perfil* getPerfil(int id);
    vector<Perfil*>* getPerfis();
    // Methods
    void adicionar(Perfil* perfil);
    void imprimirEstatisticas();
    void imprimir();
};

#endif  // REDESOCIAL_H

#ifndef POSTAGEM_H
#define POSTAGEM_H

#include <string>
using namespace std;

#include "Perfil.h"
class Perfil;

class Postagem {
   protected:
    string texto;
    int data;
    Perfil* autor;

   public:
    Postagem(string texto, int data, Perfil* autor);
    virtual ~Postagem();
    // Getters
    string getTexto();
    int getData();
    Perfil* getAutor();
    // Methods
    void imprimir();
};

#endif  // POSTAGEM_H

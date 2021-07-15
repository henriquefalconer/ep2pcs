#ifndef STORY_H
#define STORY_H

#include "Postagem.h"

class Story: public Postagem {
   private:
    int dataDeFim;

   public:
    Story(string texto, int data, int dataDeFim, Perfil* autor);
    virtual ~Story();
    // Getters
    int getDataDeFim();
    // Methods
    void imprimir();
};

#endif  // STORY_H

#ifndef PERSISTENCIADAREDE_H
#define PERSISTENCIADAREDE_H

#include <string>
using namespace std;

#include "RedeSocial.h"

class PersistenciaDaRede {
   private:
    string arquivo;

   public:
    PersistenciaDaRede(string arquivo);
    virtual ~PersistenciaDaRede();
    // Methods
    void salvar(RedeSocial* r);
    RedeSocial* carregar();
};

#endif  // PERSISTENCIADAREDE_H

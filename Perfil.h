#ifndef PERFIL_H
#define PERFIL_H

#include <list>
#include <string>
#include <vector>

using namespace std;

#include "Postagem.h"
class Postagem;

class Perfil {
   protected:
    string nome;
    vector<Perfil*>* contatos;
    list<Postagem*>* postagens;
    int id;
    static int ultimoId;

   public:
    Perfil(string nome, int id);
    Perfil(string nome);
    virtual ~Perfil() = 0;
    // Getters
    int getId();
    static int getUltimoId();
    string getNome();
    virtual vector<Perfil*>* getContatos();
    virtual list<Postagem*>* getPostagens();
    virtual list<Postagem*>* getPostagensDosContatos(int data);
    virtual list<Postagem*>* getPostagensDosContatos();
    // Setters
    static void setUltimoId(int ultimoId);
    // Methods
    virtual void adicionar(Perfil* contato);
    virtual void adicionar(Postagem* p);
    virtual void imprimir();
};

#endif  // PERFIL_H

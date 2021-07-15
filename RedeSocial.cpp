#include "RedeSocial.h"
#include "iofuncs.h"

#include <algorithm>

#include "PerfilInexistente.h"

#include "Pagina.h"
#include "Perfil.h"
#include "Pessoa.h"
#include "PessoaVerificada.h"
#include "Postagem.h"

RedeSocial::RedeSocial(): perfis(new vector<Perfil*>()) {}

RedeSocial::~RedeSocial() {
    print("Destrutor de RedeSocial: ", perfis->size(), " perfis ");

    while (!perfis->empty()) {
        auto ultimo = perfis->back();
        perfis->pop_back();
        delete ultimo;
    }

    delete perfis;

    print("RedeSocial deletada ");
}

// Getters
Perfil* RedeSocial::getPerfil(int id) {
    for (auto perfil : *perfis)
        if (perfil->getId() == id) return perfil;
    throw new PerfilInexistente();
}

vector<Perfil*>* RedeSocial::getPerfis() { return perfis; }

// Methods
void RedeSocial::adicionar(Perfil* perfil) {
    auto it = find(perfis->begin(), perfis->end(), perfil);
    if (it != perfis->end())
        throw new invalid_argument("Perfil ja adicionado");
    perfis->push_back(perfil);
}

void RedeSocial::imprimirEstatisticas() {
    int quantidadePessoasVerificadas = 0;
    int quantidadePessoasNaoVerificadas = 0;
    int quantidadePaginas = 0;
    int quantidadePerfis = 0;
    for (auto perfil : *perfis) {
        if (dynamic_cast<PessoaVerificada*>(perfil))
            quantidadePessoasVerificadas++;

        else if (dynamic_cast<Pessoa*>(perfil))
            quantidadePessoasNaoVerificadas++;

        else if (dynamic_cast<Pagina*>(perfil))
            quantidadePaginas++;

        else
            quantidadePerfis++;
    }
    print("Pessoa: ", quantidadePessoasNaoVerificadas);
    print("PessoaVerificada: ", quantidadePessoasVerificadas);
    print("Pagina: ", quantidadePaginas);
    print("Perfil: ", quantidadePerfis);
}

void RedeSocial::imprimir() {
    print("==================================");
    print("Rede Social: ", perfis->size(), " perfis");
    print("==================================");
    if (perfis->size() == 0) {
        print("Sem perfis");
        print("==================================");
    } else {
        for (auto perfil : *perfis) {
            perfil->imprimir();
            print("==================================");
        }
    }
    print();
}

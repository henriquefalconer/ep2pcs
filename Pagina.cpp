#include "Pagina.h"
#include "iofuncs.h"

#include <iostream>

Pagina::Pagina(string nome, PessoaVerificada* proprietario, int id)
    : Pessoa(nome, id), proprietario(proprietario) {}

Pagina::Pagina(string nome, PessoaVerificada* proprietario)
    : Pessoa(nome), proprietario(proprietario) {
    adicionar(proprietario);
}

Pagina::~Pagina() {}

// Getters
PessoaVerificada* Pagina::getProprietario() { return proprietario; }

// Methods
void Pagina::imprimir() {
    print("\nNome: ", nome, " - id: ", id, " - Proprietario: ", proprietario->getNome());
}

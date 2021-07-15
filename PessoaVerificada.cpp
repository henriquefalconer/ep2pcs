#include "PessoaVerificada.h"
#include "iofuncs.h"

PessoaVerificada::PessoaVerificada(string nome, string email, int id)
    : Pessoa(nome, id), email(email) {}

PessoaVerificada::PessoaVerificada(string nome, string email)
    : Pessoa(nome), email(email) {}

PessoaVerificada::PessoaVerificada(string nome)
    : PessoaVerificada(nome, "email.padrao@usp.br") {}

PessoaVerificada::~PessoaVerificada() {}

// Getters
string PessoaVerificada::getEmail() { return email; }

// Methods
void PessoaVerificada::imprimir() {
    print(email);
    Pessoa::imprimir();
}

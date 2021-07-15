#include "Pessoa.h"

Pessoa::Pessoa(string nome, int id): Perfil(nome, id) {}

Pessoa::Pessoa(string nome): Perfil(nome) {}

Pessoa::~Pessoa() {}

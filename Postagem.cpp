#include "Postagem.h"
#include "iofuncs.h"

Postagem::Postagem(string texto, int data, Perfil* autor)
    : texto(texto), data(data), autor(autor) {}

Postagem::~Postagem() { print("Destrutor de postagem: ", texto); }

// Getters
string Postagem::getTexto() { return texto; }

int Postagem::getData() { return data; }

Perfil* Postagem::getAutor() { return autor; }

// Methods
void Postagem::imprimir() {
    print("Texto: ", texto, " - Data: ", data, " - Autor: ", autor->getNome());
}

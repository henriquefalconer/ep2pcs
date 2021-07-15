#include "Story.h"
#include "iofuncs.h"

Story::Story(string texto, int data, int dataDeFim, Perfil* autor)
    : Postagem(texto, data, autor), dataDeFim(dataDeFim) {}

Story::~Story() {}

// Getters
int Story::getDataDeFim() { return dataDeFim; }

// Methods
void Story::imprimir() {
    print(
        "Texto: ", 
        texto, 
        " - Data: ", 
        data, 
        " - Data De Fim: ", 
        dataDeFim, 
        " - Autor: ", 
        autor->getNome()
    );
}

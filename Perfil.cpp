#include "Perfil.h"
#include "iofuncs.h"

int Perfil::ultimoId = 0;

Perfil::Perfil(string nome, int id):
    id(id),
    nome(nome),
    contatos(new vector<Perfil*>()),
    postagens(new list<Postagem*>()) {}

Perfil::Perfil(string nome):
    Perfil(nome, ++Perfil::ultimoId) {}

Perfil::~Perfil() {
    print("Destrutor de perfil: ",
        nome,
        " - Quantidade de postagens feitas: ",
        postagens->size());

    delete contatos;

    while (!postagens->empty()) {
        auto ultimo = postagens->back();
        postagens->pop_back();
        delete ultimo;
    }

    delete postagens;

    print("Perfil deletado");
}

// Getters
int Perfil::getId() { return id; }

int Perfil::getUltimoId() { return Perfil::ultimoId; }

string Perfil::getNome() { return nome; }

list<Postagem*>* Perfil::getPostagens() { return postagens; }

list<Postagem*>* Perfil::getPostagensDosContatos(int data) {
    auto postagensDosContatos = new list<Postagem*>();

    for (auto contato : *contatos) {
        auto postagens = contato->getPostagens();

        for (auto postagem : *postagens) {
            if (data >= postagem->getData() && data - postagem->getData() <= 3)
                postagensDosContatos->push_back(postagem);
        }
    }

    return postagensDosContatos;
}

list<Postagem*>* Perfil::getPostagensDosContatos() {
    auto postagensDosContatos = new list<Postagem*>();

    for (auto contato : *contatos) {
        auto postagens = contato->getPostagens();
        postagensDosContatos->insert(postagensDosContatos->begin(), postagens->begin(), postagens->end());
    }

    return postagensDosContatos;
}

vector<Perfil*>* Perfil::getContatos() { return contatos; }

// Setters
void Perfil::setUltimoId(int ultimoId) { Perfil::ultimoId = ultimoId; }

// Methods
void Perfil::adicionar(Perfil* contato) {
    if (contato == this) throw new invalid_argument("Perfil adicionando ele mesmo");

    for (auto c : *contatos)
        if (c == contato) throw new invalid_argument("Perfil ja adicionado");

    contatos->push_back(contato);

    for (auto c : *contato->contatos)
        if (c == this) return;

    contato->adicionar(this);
}

void Perfil::adicionar(Postagem* p) {
    postagens->push_back(p);
}

void Perfil::imprimir() {
    print("\nNome: ", nome, " - id: ", id);
    print("Numero de postagens feitas: ", postagens->size());

    for (auto postagem : *postagens)
        print("Postagens na data ", postagem->getData(), " - Texto: ", postagem->getTexto());

    if (contatos->empty())
        print("Sem contatos ");
    else {
        for (auto contato : *contatos) {
            for (auto postagem : *contato->getPostagens())
                print(
                    "Postagens na data ", 
                    postagem->getData(), 
                    " do contato ", 
                    contato->getNome(), 
                    " - Texto: ", 
                    postagem->getTexto()
                );
        }
    }
}

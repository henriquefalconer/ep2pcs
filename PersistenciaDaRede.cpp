#include "PersistenciaDaRede.h"
#include <fstream>

#include "Pagina.h"
#include "PessoaVerificada.h"

PersistenciaDaRede::PersistenciaDaRede(string arquivo): arquivo(arquivo) {}

PersistenciaDaRede::~PersistenciaDaRede() {}

// Methods
void PersistenciaDaRede::salvar(RedeSocial* r) {
    ofstream output;

    output.open(arquivo);

    if (!output)  // output.bad() || output.fail()
        throw new logic_error("Erro ao escrever");

    auto pessoasVerificadas = new vector<PessoaVerificada*>();
    auto pessoas = new vector<Pessoa*>();
    auto paginas = new vector<Pagina*>();

    for (auto p : *r->getPerfis()) {
        if (auto pv = dynamic_cast<PessoaVerificada*>(p))
            pessoasVerificadas->push_back(pv);

        else if (auto pnv = dynamic_cast<Pessoa*>(p))
            pessoas->push_back(pnv);

        else if (auto pg = dynamic_cast<Pagina*>(p))
            paginas->push_back(pg);
    }

    output << Perfil::getUltimoId() << endl;

    output << pessoas->size() << endl;

    for (auto pnv : *pessoas)
        output << pnv->getId() << " " << pnv->getNome() << " ";

    output << pessoasVerificadas->size() << endl;

    for (auto pv : *pessoasVerificadas)
        output << pv->getId() << " " << pv->getNome() << " " << pv->getEmail()
               << endl;

    output << paginas->size() << endl;

    for (auto pg : *paginas)
        output << pg->getId() << " " << pg->getNome() << " "
               << pg->getProprietario()->getId() << endl;

    for (auto perfil : *r->getPerfis())
        for (auto contato : *perfil->getContatos())
            output << perfil->getId() << " " << contato->getId() << endl;
}

RedeSocial* PersistenciaDaRede::carregar() {
    auto r = new RedeSocial();

    ifstream input;

    input.open(arquivo);

    if (!input.good()) return r;

    string nome, email;
    int ultimoId, id, idProprietario, idContato;
    int qntdPessoas, qntdPessoasVerificadas, qntdPaginas;

    input >> ultimoId >> qntdPessoas;

    Perfil::setUltimoId(ultimoId);

    for (int i = 0; i < qntdPessoas; i++) {
        input >> id >> nome;
        r->adicionar(new Pessoa(nome, id));
    }

    input >> qntdPessoasVerificadas;

    for (int i = 0; i < qntdPessoasVerificadas; i++) {
        input >> id >> nome >> email;
        r->adicionar(new PessoaVerificada(nome, email, id));
    }

    input >> qntdPaginas;

    for (int i = 0; i < qntdPaginas; i++) {
        input >> id >> nome >> idProprietario;
        auto p = dynamic_cast<PessoaVerificada*>(r->getPerfil(idProprietario));
        r->adicionar(new Pagina(nome, p, id));
    }

    while (true) {
        input >> id >> idContato;
        if (!input) break;
        auto p = r->getPerfil(id);
        auto c = r->getPerfil(idContato);
        try {
            p->adicionar(c);
        } catch (...) {
            // Fazer nada
        }
    }

    if (!input.eof()) throw new logic_error("Erro de leitura");

    return r;
}

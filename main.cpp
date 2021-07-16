#include "iofuncs.h"
#include "trycatch.h"
#include <functional>

#include "Pagina.h"
#include "Perfil.h"
#include "Pessoa.h"
#include "PessoaVerificada.h"
#include "Postagem.h"
#include "PersistenciaDaRede.h"
#include "Story.h"

using FuncaoDeRede = function<void(RedeSocial*)>;
using CriadorDeFuncaoDeRede = function<FuncaoDeRede(Perfil*)>;

template<typename T>
int encontrarIndice(T item, T* lista, int quantidade) {
    for (int i = 0; i < quantidade; i++)
        if (lista[i] == item) return i;
    return -1;
}

bool imprimirOpcoes(
    RedeSocial* redeSocial,
    string textoInicial,
    string textoFinal,
    int quantidadeDeOpcoes,
    string* opcoes,
    FuncaoDeRede* funcoes,
    bool temOpcaoZero = false,
    int* numeros = NULL
) {
    print(textoInicial);

    for (int i = 1; i <= quantidadeDeOpcoes; i++) {
        int numero = numeros == NULL
            ? i % (quantidadeDeOpcoes + 1 - temOpcaoZero)
            : numeros[i - 1];

        print(numero, ") ", opcoes[i - 1]);
    }

    int escolha = input<int>(textoFinal, '\n');

    if (escolha <= 0 || escolha > quantidadeDeOpcoes - temOpcaoZero)
        return false;

    int posicao = numeros != NULL 
        ? encontrarIndice(escolha, numeros, quantidadeDeOpcoes)
        : escolha - 1;

    funcoes[posicao](redeSocial);

    return true;
}

void cadastroPessoa(RedeSocial* redeSocial) {
    string nome = input("Informe os dados da pessoa\nNome: ");
    bool verificada = simOuNao("Verificada (s/n)? ");
    if (!verificada) {
        redeSocial->adicionar(new Pessoa(nome));
        print();
        return;
    }
    string email = input("Email: ", '\n');
    redeSocial->adicionar(new PessoaVerificada(nome, email));
}

void criarOpcoesUsuario(
    RedeSocial* redeSocial,
    string* opcoesUsuario,
    FuncaoDeRede* funcoes,
    int* idsUsuarios,
    CriadorDeFuncaoDeRede criarFuncao
) {
    int i = 0;
    for (auto perfil : *redeSocial->getPerfis()) {
        opcoesUsuario[i] = perfil->getNome() 
            + (dynamic_cast<PessoaVerificada*>(perfil) ? " (Verificada)" : "");

        funcoes[i] = criarFuncao(perfil);
        idsUsuarios[i] = perfil->getId();
        i++;
    }
}

bool mostrarOpcoesUsuario(
    RedeSocial* redeSocial,
    string textoInicial,
    CriadorDeFuncaoDeRede criarFuncao
) {
    int quantidadeDePerfis = redeSocial->getPerfis()->size();

    auto opcoesUsuario = new string[quantidadeDePerfis];
    auto idsUsuarios = new int[quantidadeDePerfis];
    auto funcoes = new FuncaoDeRede[quantidadeDePerfis];

    criarOpcoesUsuario(redeSocial, opcoesUsuario, funcoes, idsUsuarios, criarFuncao);

    bool opcaoEscolhida = imprimirOpcoes(redeSocial,
        textoInicial,
        "Digite o numero ou 0 para cancelar: ",
        quantidadeDePerfis,
        opcoesUsuario,
        funcoes,
        false,
        idsUsuarios
    );

    delete[] opcoesUsuario;
    delete[] funcoes;

    return opcaoEscolhida;
}

void cadastroPagina(RedeSocial* redeSocial) {
    string nome = input("Informe os dados da pagina\nNome: ", '\n');

    auto criarFuncao = [&](Perfil* perfil) -> FuncaoDeRede {
        return [&, perfil](RedeSocial* redeSocial) {
            if (auto pessoaVerificada = dynamic_cast<PessoaVerificada*>(perfil))
                redeSocial->adicionar(new Pagina(nome, pessoaVerificada));

            else
                print("Somente pessoas verificadas podem ser proprietarias\n");
        };
    };

    mostrarOpcoesUsuario(redeSocial, "Proprietario:", criarFuncao);
}

FuncaoDeRede opcoesLogadas(Perfil* perfil) {
    auto fazerPostagem = [perfil](RedeSocial* redeSocial) {
        int dataDeFim;
        bool ehStory = simOuNao("Story (s/n): ");
        int data = input<int>("Data: ");
        if (ehStory) dataDeFim = input<int>("Data de fim: ");
        string texto = input("Texto: ", '\n');

        perfil->adicionar(
            ehStory 
                ? new Story(texto, data, dataDeFim, perfil)
                : new Postagem(texto, data, perfil)
        );
    };

    auto verPostagens = [perfil](RedeSocial* redeSocial) {
        int data = input<int>("Data: ");

        auto postagens = perfil->getPostagensDosContatos(data);

        print("Postagens dos ultimos 3 dias:");

        for (auto p : *postagens) p->imprimir();
        
        delete postagens;

        print();
    };

    auto listaDeAdicionarContato = [perfil](RedeSocial* redeSocial) {
        bool foiPossivelAdicionar = true;

        auto adicionarContato = [&, perfil](Perfil* novoContato) {
            return [&, perfil, novoContato](RedeSocial* redeSocial) {
                tryCatch(
                    [=]() { perfil->adicionar(novoContato); },
                    [&]() { foiPossivelAdicionar = false; }
                );
            };
        };

        bool opcaoEscolhida =
            mostrarOpcoesUsuario(redeSocial, "Perfil:", adicionarContato);

        if (!opcaoEscolhida || !foiPossivelAdicionar)
            print("Contato nao adicionado");
    };

    return [=](RedeSocial* redeSocial) {
        bool repetir;

        do {
            printinl(perfil->getNome());

            if (auto pessoaVerificada = dynamic_cast<PessoaVerificada*>(perfil))
                printinl(" - ", pessoaVerificada->getEmail());

            else if (auto pagina = dynamic_cast<Pagina*>(perfil))
                printinl("\nProprietario ", pagina->getProprietario()->getNome());

            print("\nContatos: ", perfil->getContatos()->size(), "\n---");

            string opcoes[] = { 
                "Fazer postagem",
                "Ver postagens dos contatos",
                "Adicionar contato",
                "Deslogar" 
            };

            FuncaoDeRede funcoes[] = {
                fazerPostagem, 
                verPostagens, 
                listaDeAdicionarContato 
            };

            repetir = imprimirOpcoes(
                redeSocial, 
                "Escolha uma opcao:", 
                "", 
                4, 
                opcoes, 
                funcoes, 
                true
            );
        } while (repetir);
    };
}

void logar(RedeSocial* redeSocial) {
    mostrarOpcoesUsuario(redeSocial, "Escolha um perfil:", opcoesLogadas);
}

void interfaceGrafica(RedeSocial* redeSocial) {
    string opcoes[] = { 
        "Cadastrar Pessoa", 
        "Cadastrar Pagina", 
        "Logar", 
        "Terminar"
    };

    FuncaoDeRede funcoes[] = { cadastroPessoa, cadastroPagina, logar };

    while (imprimirOpcoes(redeSocial, "Escolha uma opcao", "", 4, opcoes, funcoes, true)) {}
}

int main() {
    string arquivo = input("Arquivo: ");

    auto persistenciaDeRede = new PersistenciaDaRede(arquivo);

    auto redeSocial = persistenciaDeRede->carregar();

    interfaceGrafica(redeSocial);

    bool salvar = simOuNao("Deseja salvar? (s/n) ");

    if (salvar) persistenciaDeRede->salvar(redeSocial);

    delete redeSocial;

    return 0;
}

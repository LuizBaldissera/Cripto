#include "cripto.h"
#include <fstream>
#include <sstream>
#include <algorithm>

// divide uma string em tokens
std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// converte string para maiúsculas
std::string paraMaiusculo(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

// conecta com a base de dados (arquivo CSV)
int conectarComBase(std::vector<Cripto>& lista) {
    std::ifstream file("cripto.csv");
    if (!file.is_open()) return 0;

    std::string linha;
    while (std::getline(file, linha)) {
        std::vector<std::string> dados = split(linha, ';');
        if (dados.size() == 3) {
            Cripto cripto{paraMaiusculo(dados[0]), paraMaiusculo(dados[1]), std::stod(dados[2])};
            lista.push_back(cripto);
        }
    }
    file.close();
    return lista.size();
}

//lista as criptomoedas
void listar(const std::vector<Cripto>& lista) {
    if (lista.empty()) {
        std::cout << "Lista vazia\n";
        return;
    }
    for (const auto& cripto : lista) {
        std::cout << "Nome: " << cripto.nome << ", Sigla: " << cripto.sigla << ", Valor: " << cripto.valor << '\n';
    }
}

//verifica se a criptomoeda ja esta cadastrada
bool jaCadastrado(const std::vector<Cripto>& lista, const std::string& nome, const std::string& sigla) {
    for (const auto& cripto : lista) {
        if (cripto.nome == nome || cripto.sigla == sigla) return true;
    }
    return false;
}

// atualiza o cadastro no arquivo CSV
void atualizarCadastro(const Cripto& novaCripto) {
    std::ofstream file("cripto.csv", std::ios::app);
    if (file.is_open()) {
        file << novaCripto.nome << ";" << novaCripto.sigla << ";" << novaCripto.valor << '\n';
        file.close();
    }
}

//atualiza a remoção no arquivo CSV
void atualizarRemocao(const std::vector<Cripto>& lista) {
    std::ofstream file("cripto.csv");
    for (const auto& cripto : lista) {
        file << cripto.nome << ";" << cripto.sigla << ";" << cripto.valor << '\n';
    }
    file.close();
}

// cadastra uma nova criptomoeda
void cadastrar(std::vector<Cripto>& lista) {
    Cripto novaCripto;
    std::cout << "Digite o nome: ";
    std::getline(std::cin, novaCripto.nome);
    novaCripto.nome = paraMaiusculo(novaCripto.nome);

    std::cout << "Digite a sigla: ";
    std::getline(std::cin, novaCripto.sigla);
    novaCripto.sigla = paraMaiusculo(novaCripto.sigla);

    std::cout << "Digite o valor: ";
    std::cin >> novaCripto.valor;
    std::cin.ignore();

    // Verifica se ja existe pelo nome ou sigla
    if (!jaCadastrado(lista, novaCripto.nome, novaCripto.sigla)) {
        lista.push_back(novaCripto);
        atualizarCadastro(novaCripto);
        std::cout << "Criptomoeda cadastrada com sucesso\n";
    } else {
        std::cout << "Criptomoeda ja cadastrada (nome ou sigla ja existe)\n";
    }
}

// remove uma criptomoeda
void remover(std::vector<Cripto>& lista) {
    std::string nome;
    std::cout << "Digite o nome da criptomoeda para remover: ";
    std::getline(std::cin, nome);
    nome = paraMaiusculo(nome);

    auto it = std::remove_if(lista.begin(), lista.end(), [&](const Cripto& cripto) {
        return cripto.nome == nome;
    });

    if (it != lista.end()) {
        lista.erase(it, lista.end());
        atualizarRemocao(lista);
        std::cout << "Criptomoeda removida com sucesso.\n";
    } else {
        std::cout << "Criptomoeda nao encontrada.\n";
    }
}

void menu() {
    std::vector<Cripto> lista;
    conectarComBase(lista);

    int opcao;
    do {
        std::cout << "\nMenu:\n1: Listar\n2: Cadastrar\n3: Remover\n4: Sair\nEscolha uma opcao: ";
        std::cin >> opcao;
        std::cin.ignore();

        switch (opcao) {
            case 1:
                listar(lista);
                break;
            case 2:
                cadastrar(lista);
                break;
            case 3:
                remover(lista);
                break;
            case 4:
                std::cout << "Saindo...\n";
                break;
            default:
                std::cout << "Opcao invalida\n";
        }
    } while (opcao != 4);
}

#ifndef CRIPTO_H
#define CRIPTO_H

#include <iostream>
#include <string>
#include <vector>

struct Cripto {
    std::string nome;
    std::string sigla;
    double valor;
};


std::vector<std::string> split(const std::string& str, char delimiter);
std::string paraMaiusculo(std::string str);

// Funções principais
int conectarComBase(std::vector<Cripto>& lista);
void listar(const std::vector<Cripto>& lista);
bool jaCadastrado(const std::vector<Cripto>& lista, const std::string& sigla);
void atualizarCadastro(const Cripto& novaCripto);
void atualizarRemocao(const std::vector<Cripto>& lista);
void cadastrar(std::vector<Cripto>& lista);
void remover(std::vector<Cripto>& lista);
void menu();

#endif // CRIPTO_H

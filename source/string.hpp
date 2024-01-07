//
//          String
//          Por Gabriel Ferreira (versão 1.0)
//          UFPR 2024
//
//      Implementa algumas funções para a manipulação de
//  strings em c++. Essas funções são necessárias para o
//  processamento inicial dos dados brutos, fazendo o parser
//  dos arquivos de saída do Google Forms e do programa da
//  NENC.
//
#ifndef __STRING_H__
#define __STRING_H__

#include <string>
#include <vector>

/////////////////////////////////////////////////////////////////////////////
//      Verifica se o trecho final de uma string termina como o desejado.
//  (string) str: string para análise.
//  (string) value: valor a ser comparado no final da string.
bool EndsWith(const std::string& str, const std::string& value);
/////////////////////////////////////////////////////////////////////////////
//      Quebra uma string a partir de um delimitador alvo.
//  (string) str: string a ser quebrada.
//  (string) target: valor alvo que indica os pontos a serem quebrados na string.
std::vector<std::string> Split(const std::string& str, const std::string& target);
/////////////////////////////////////////////////////////////////////////////
//      Remove um trecho específico de uma string repetidas vezes.
//  (string) str: string a ter um trecho removida.
//  (string) target: valor a ser removido da string.
std::string Remove(const std::string& str, const std::string& target);
/////////////////////////////////////////////////////////////////////////////
//      Substituí um trecho específico de uma string por outro.
//  (string) str: string alvo.
//  (string) old: valor na string a ser substituído.
//  (string) value: novo valor a ser inserido no lugar.
std::string Replace(const std::string& str, const std::string& old, const std::string& value);
/////////////////////////////////////////////////////////////////////////////

#endif
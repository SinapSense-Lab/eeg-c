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
#include "string.hpp"

#include <string>
#include <vector>

/////////////////////////////////////////////////////////////////////////////
//      Verifica se o trecho final de uma string termina como o desejado.
//  (string) str: string para análise.
//  (string) value: valor a ser comparado no final da string.
//  Base: https://devptr.com/check-if-string-ends-with-substring-in-c/
bool EndsWith(const std::string& str, const std::string& value)
{
    size_t strLen = str.length();
    size_t subStrLen = value.length();

    return strLen >= subStrLen && str.compare(strLen - subStrLen, subStrLen, value) == 0;
}
/////////////////////////////////////////////////////////////////////////////
//      Quebra uma string a partir de um delimitador alvo.
//  (string) str: string a ser quebrada.
//  (string) target: valor alvo que indica os pontos a serem quebrados na string.
//  Base: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
std::vector<std::string> Split(const std::string& str, const std::string& target)
{
    std::string s = str;
    size_t pos = s.find(target);

    std::vector<std::string> result;

    while (pos != std::string::npos)
    {
        pos = s.find(target);
        result.push_back(s.substr(0, pos));
        s.erase(0, pos + target.length());
    }
    return result;
}
/////////////////////////////////////////////////////////////////////////////
//      Remove um trecho específico de uma string repetidas vezes.
//  (string) str: string a ter um trecho removida.
//  (string) target: valor a ser removido da string.
std::string Remove(const std::string& str, const std::string& target)
{
    std::string s = str;
    size_t pos = s.find(target);

    while (pos != std::string::npos)
    {
        s.erase(pos, pos + target.length());
        pos = s.find(target);
    }

    return s;
}
/////////////////////////////////////////////////////////////////////////////
//      Substituí um trecho específico de uma string por outro.
//  (string) str: string alvo.
//  (string) old: valor na string a ser substituído.
//  (string) value: novo valor a ser inserido no lugar.
std::string Replace(const std::string& str, const std::string& old, const std::string& value)
{
    std::string s = str;
    size_t pos = s.find(old);

    while (pos != std::string::npos)
    {
        s.replace(pos, old.length(), value);
        pos = s.find(old); 
    }
    return s;
}
/////////////////////////////////////////////////////////////////////////////


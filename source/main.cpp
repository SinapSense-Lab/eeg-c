//
//      main.cpp
//      Por Gabriel Ferreira.
//      Script's documentation in Brazilian Portuguese.
//      Please, contact the SinapSense Laboratory at Federal University of Parana, Brazil.
//      E-mail: sseeg.ufpr@gmail.com
//
//      Ponto de entrada do programa. A estrutura será carregada via
//  comando de terminal no estilo:
//
//      `eeg-c [PASTA DE DADOS] [PASTA DE SAÍDA]`
//
//      * Versão 1.0:
//      Os arquivos .cfg dentro da pasta de dados serão interpretados como
//  informações qualitativas, enquanto os arquivos .json seram tratados
//  como dados brutos obtidos do equipamento de eeg. (Modelo do NINC)
//
//      O programa deverá pré-processar esses dados brutos e separar o conjunto
//  de dados que será utilizado adequadamente. Esses dados recebem uma filtragem
//  interna, utilizando transformadas de Wavelet, em seguida são construídos
//  espectrogramas para os dados filtrados e por fim os dados são classificados
//  utilizando alguns modelos de rede neural.
//
#include <iostream>
#include <stdexcept>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2) { cout << "Invalid arguments: use `eeg-c [data folder] [output folder]`.\n"; return 1; }
    cout << "Hello World!\0";
}
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
//  https://github.com/fastlib/fCWT
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Configurações:
#define _fs 250
#define _f0 6.0f
#define _f1 70.0f
#define _fn 3000
#define _nthreads 2
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "structs/ql.hpp"
#include "structs/qt.hpp"

#include "string.hpp"

#include "load.hpp"

#include <math.h>
#include <fcwt.h>
#include <vector>
#include <string>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    std::cout << "Teste!" << std::endl;
    
    if (argc != 3) { std::cout << "Invalid arguments: use `eeg-c [data folder] [output folder]`." << std::endl; return 1; }
    
    std::vector<std::string> files = GetFiles(argv[1]);
    std::vector<QLSample> ql = GetQL(files);
    std::vector<QTCollect> qt = GetQT(files);

    std::cout << "Teste!" << std::endl;

    for (auto qtcollect = qt.begin(); qtcollect !=  qt.end(); ++qtcollect)
    {
        for (auto task = (*qtcollect).tasks.begin(); task != (*qtcollect).tasks.end(); ++task)
        {
            int n = (*task).values.size();

            std::vector<complex<float>> tfm(n * _fn);

            Wavelet* wavelet;
            Morlet morl(2.0f);
            wavelet = &morl;

            FCWT fcwt(wavelet, _nthreads, true, false);

            Scales scs(wavelet, FCWT_LINFREQS, _fs, _f0, _f1, _fn);

            fcwt.cwt(&(*task).values[0], n, &tfm[0], &scs);

            for (auto res = tfm.begin(); res != tfm.end(); ++res)
                std::cout << *res << std::endl;

            break;
        }
        break;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
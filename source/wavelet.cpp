//
//      Wavelet
//      Por Gabriel Ferreira (versão 1.0)
//      UFPR 2024
//
//      Lib: https://github.com/fastlib/fCWT
//
//      Ambientaliza o uso de Wavelets para o processamento do
//  sinal, criando as funções responsáveis por gerar a Wavelet,
//  por fazer o soft denoising do sinal, por calcular o espectrograma
//  e por fazer a transformada inversa a partir dos coeficientes.
//
#include "wavelet.hpp"

#include <math.h>
#include <fcwt.h>
#include <vector>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////////////////////////////
//      Função responsável por gerar a tranformada de Wavelet e calcular os coeficientes
//  da transformada para um determinado conjunto de dados, retornando-os como resultado.
//      (vector<float>) data: conjunto de dados passado para a função.
//      (int) fs = 250 Hz: frequência de coleta de dados, basicamente é o tamanho do dataset divido
//  pelo intervalo de coleta.
//      (float) sigma = 2.0f: coeficiente de definição da Wavelet de Morlet.
//      (float) f0 = 1.0f Hz: frequência inicial para o intervalo de domínio da Wavelet.
//      (float) f1 = 70.0f Hz: frequência final para o intervalo de domínio da Wavelet.
//      (int) fn = 3000: quantidade de janelas com as quais a Wavelet vai trabalhar.
//      (int) nthreads = 1: número de threads que devem ser utilizadas para o cálculo da Wavelet.
//  Precisa da biblioteca omp.h para funcionar!
std::vector<complex<float>> cwt(std::vector<float> data, int fs, float sigma, float f0, float f1, int fn, int nthreads)
{
    std::cout << "\tInicializando componentes..." << std::endl;
    int n = data.size();
    std::vector<complex<float>> coefficients(n * fn);

    Wavelet* wavelet;

    Morlet morl(sigma);
    wavelet = &morl;
    FCWT fcwt(wavelet, nthreads, true, false);
    Scales scs(wavelet, FCWT_LINFREQS, fs, f0, f1, fn);

    fcwt.cwt(&data[0], n, &coefficients[0], &scs);
    return coefficients;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
//      Faz a remoção de ruídos a partir de um processo de soft denoising aplicado alguns limiares
//  aos coeficientes da transformada de wavelet calculados a partir do conjunto de dados passado como
//  parâmetro para a função.
//      (vector<float>) data: conjunto de dados passado para a função.
//      (float) factor: fator do limiar de exclusão dos coeficientes.
//      (int) windowSize: tamanho das janelas de processamento de ruído. Zero para ser o domínio inteiro.
//      (int) fs = 250 Hz: frequência de coleta de dados, basicamente é o tamanho do dataset divido
//  pelo intervalo de coleta.
//      (float) sigma = 2.0f: coeficiente de definição da Wavelet de Morlet.
//      (float) f0 = 1.0f Hz: frequência inicial para o intervalo de domínio da Wavelet.
//      (float) f1 = 70.0f Hz: frequência final para o intervalo de domínio da Wavelet.
//      (int) fn = 3000: quantidade de janelas com as quais a Wavelet vai trabalhar.
//      (int) nthreads = 1: número de threads que devem ser utilizadas para o cálculo da Wavelet.
//  Precisa da biblioteca omp.h para funcionar!
std::vector<complex<float>> denoising(std::vector<float> data, float factor, int windowSize, int fs, float sigma, float f0, float f1, int fn, int nthreads)
{
    //  Calcula os coeficientes dos dados.
    std::vector<complex<float>> coefficients = cwt(data, fs, sigma, f0, f1, fn, nthreads);

    //  Vetor de denoising.
    std::vector<complex<float>> denoise(coefficients.size(), complex<float>(0.0f, 0.0f));

    //  Calcula o número de blocos e o número restante de elementos.
    int blocks = coefficients.size() / windowSize;

    for (int block = 0; block < blocks; block++)
    {
        float sum = 0.0f;
        for (int i = (block * windowSize); i < ((block + 1) * windowSize); i++)
        {
            sum += std::abs(coefficients[i]);
        }

        float mean = sum / coefficients.size();
        float var = 0.0f;

        for (int i = (block * windowSize); i < ((block + 1) * windowSize); i++)
        {
            var += std::pow(std::abs(coefficients[i]) - mean, 2);
        }

        float stdDeviation = std::sqrt(var / coefficients.size());
        float threshold = stdDeviation * factor;

        for (int i = (block * windowSize); i < ((block + 1) * windowSize); i++)
        {
            if (std::abs(coefficients[i]) > threshold)
            {
                denoise[i] = coefficients[i] - std::polar(threshold, std::arg(coefficients[i]));
            }
            else
            {
                denoise[i] = 0.0f;
            }
        }
    }

    return denoise;
}
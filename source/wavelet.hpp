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
#ifndef __WAVELET_HPP__
#define __WAVELET_HPP__

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
std::vector<complex<float>> cwt(std::vector<float> data, int fs = 250, float sigma = 2.0f, float f0 = 1.0f, float f1 = 70.0f, int fn = 3000, int nthreads = 1);
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
std::vector<complex<float>> denoising(std::vector<float> data, float factor, int windowSize, int fs = 250, float sigma = 2.0f, float f0 = 1.0f, float f1 = 70.0f, int fn = 3000, int nthreads = 1);
////////////////////////////////////////////////////////////////////////////////////////////////////////
//      Calcula o espectrograma a partir de um conjunto de dados passado como argumento e retorna o
//  resultado do cálculo do espectrograma.
//      (vector<float>) data: conjunto de dados passado para a função.
//      (int) fs = 250 Hz: frequência de coleta de dados, basicamente é o tamanho do dataset divido
//  pelo intervalo de coleta.
//      (float) sigma = 2.0f: coeficiente de definição da Wavelet de Morlet.
//      (float) f0 = 1.0f Hz: frequência inicial para o intervalo de domínio da Wavelet.
//      (float) f1 = 70.0f Hz: frequência final para o intervalo de domínio da Wavelet.
//      (int) fn = 3000: quantidade de janelas com as quais a Wavelet vai trabalhar.
//      (int) nthreads = 1: número de threads que devem ser utilizadas para o cálculo da Wavelet.
//  Precisa da biblioteca omp.h para funcionar!
void spectrogram(std::vector<complex<float>> coefficients, int windowSize, int overleap, int numScales, int fs = 250, float sigma = 2.0f, float f0 = 1.0f, float f1 = 70.0f, int fn = 3000, int nthreads = 1);
////////////////////////////////////////////////////////////////////////////////////////////////////////
 
#endif
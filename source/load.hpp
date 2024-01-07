//
//          Load
//          Por Gabriel Ferreira (versão 1.0)
//          UFPR 2024
//
//      Carrega os conjuntos de dados que serão utilizados
//  pelo sistema para a análise. Os dados se dividem em
//  arquivos qualitativos e quantitativos.
//
#ifndef __LOAD_HPP__
#define __LOAD_HPP__

#include <string>
#include <vector>

#include "structs/ql.hpp"
#include "structs/qt.hpp"

/////////////////////////////////////////////////////////////////////////////
//      Carrega os arquivos presentes em uma determinada pasta.
//  (const char*) path: diretório de onde os arquivos devem ser tomados.
std::vector<std::string> GetFiles (const char* path);
/////////////////////////////////////////////////////////////////////////////
//      Pega os dados qualitativos a partir dos respectivos arquivos .csv
//  encontrados nos arquivos passados de referência.
//  (vector<string>) files: arquivos a serem analisados. Apenas os arquivos
//  .csv encontrados serão carregados como qualitativos na estrutura QL.
std::vector<QLSample> GetQL (const std::vector<std::string>& files);
/////////////////////////////////////////////////////////////////////////////
//      Pega os dados quantitativos a partir dos respectivos arquivos .json
//  encontrados nos arquivos passados de referência.
//  (vector<string>) files: arquivos a serem analisados. Apenas os arquivos
//  .json encontrados serão carregados como qualitativos na estrutura QT.
std::vector<QTCollect> GetQT (const std::vector<std::string>& files);
/////////////////////////////////////////////////////////////////////////////

#endif
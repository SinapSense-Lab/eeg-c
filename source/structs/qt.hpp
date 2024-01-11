//
//          Structs QT.
//          Por Gabriel Ferreira (versão 1.0)
//          UFPR 2024.
//
//      Estruturas dos dados quantitativos associados aos teste.
//  Dividem-se em duas estruturas simples, QTTask e QTCollect.
//      A estrutura QTTask representa uma tarefa submetida a um
//  indivíduo durante os testes. Ela contém a identificação da
//  tarefa e os valores associado a ela.
//      Por sua vez, a estrutura QTCollect contém a coletânia
//  de dados para cada tarefa realizado no decorrer do teste.
#ifndef __QT_HPP__
#define __QT_HPP__

#include <vector>

/////////////////////////////////////////////////////////////////////////////
//      Estrutura que repreesenta as tarefas.
//  (int) id: identificação da tarefa.
//  (int) ql: valor qualitativo carregado a partir da correlação com QLTask.
//  (vector<float>) values: valores quantitativos medidos com o equipamento
//  de eletroencefalografia no decorrer da exibição de uma tarefa.
struct QTTask
{
    int id;
    int ql;

    std::vector<std::vector<float>> values;
};
/////////////////////////////////////////////////////////////////////////////
//  (int) id: identificação da coleta.
//  (int) sample: identificação da amostra à qual a coleta pertence.
//  (vector<QTTask>) tasks: conjunto de tarefas realizadas na respectiva coleta.
struct QTCollect
{
    int id;
    int sample;

    std::vector<QTTask> tasks;
};
/////////////////////////////////////////////////////////////////////////////

#endif
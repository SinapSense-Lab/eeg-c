//
//          Structs QL.
//          Por Gabriel Ferreira. (versão 1.0)
//          UFPR 2024
//
//      Estruturas para os dados qualitativos que são carregadas
//  pelo sistema para o funcionamento. Os dados qualitativos são
//  classificados em 3 estruturas: QLTask, QLCollect e QLSample.
//      A estrutura QLTask é a mais básica das 3, ela engloba o
//  valor da informação qualitativa e a identificação da tarefa
//  ao qual esse valor está associado.
//      A estrutura seguinte é a QLCollect, englobando um conjunto
//  de tarefas (QLTask). O elemento QLCollect representa uma coleta
//  do experimento, para um indíviduo específico. Junto aos dados
//  da coleta (QLTask) está associado um código de identificação
//  da coleta e a idade do invíduo que participou do teste.
//      Por fim, tem-se a estrutra QLSample, representando um
//  experimento desenvolvido e todas as amostrar realizadas com
//  esse experimento, ou catálogadas com determinado código.
//
#ifndef __QL_HPP__
#define __QL_HPP__

#include <vector>

/////////////////////////////////////////////////////////////////////////////
//      QLTask: dados qualitativos de uma tarefa.
//  (int) id: identificação da tarefa no espectro de um experimento proejado.
//  (int) value: valor qualitativo associado a tarefa realizada.
struct QLTask
{
    int id;
    int value;
};
/////////////////////////////////////////////////////////////////////////////
//      QLCollect: experimento realizado com um determinado indivíduo.
//  (int) id: identificação de uma coleta de informações.
//  (int) age: idade do indivíduo que respondeu o questionário.
//  (vector<QLTask>) tasks: agrupamento de dados qualitativos associado à coleta.
struct QLCollect
{
    int id;
    int age;

    std::vector<QLTask> tasks;
};
/////////////////////////////////////////////////////////////////////////////
//  (int) id: identificação do experimento.
//  (vector<QLCollect>) collects: agrupamento de coletar associados ao experimento.
struct QLSample
{
    int id;

    std::vector<QLCollect> collects;
};

#endif
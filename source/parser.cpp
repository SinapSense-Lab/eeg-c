/*
//
//      NINC JSON Parser (.cpp file)
//      Por Gabriel Ferreira (versão 1.0)
//      UFPR, 2024
#include "parser.hpp"

#include <list>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>

#include "aux.hpp"

using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////////
struct QLTask
{
    int id;
    int value;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////
struct QLCollect
{
    int id;
    int age;
    vector<QLTask> tasks;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////
struct QLSample
{
    int id;
    vector<QLCollect> collects;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////
struct QTCollect
{
    int id;
    int sample;

    QLCollect ql;

    vector<QTTask> tasks;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////
struct QTTask
{
    int id;
    vector<float> values;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////
list<QTCollect> GetData(const char* path)
{
    //  Carrega os arquivo de dados.
    list<string> files = GetRawFiles(path);

    //  Pega os dados dos arquivos encontrados.
    list<QLSample> ql = GetRawQL(files);
    list<QTCollect> qt = GetRawQT(files);

    return qt;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
list<QTCollect> GetRawQT(std::list<std::string> files)
{
    list<QTCollect> result;

    cout << "Carregando dados quantitativos..." << endl;

    //  Separa os arquivos .json tomando eles como dados brutos quantitativos.
    list<string> qtFiles;
    for (auto file = files.begin(); file != files.end(); ++file)
        if (stringEndsWith(*file, ".json")) qtFiles.push_back(*file);

    //  Lê o arquivo.
    for (auto file = qtFiles.begin(); file != qtFiles.end(); ++file)
    {
        QTCollect collect;
        //  Abre o arquivo .json.
        ifstream fpoint (*file);
        if (!fpoint.is_open()) { cout << "Falha ao abrir o arquivo \'" << *file << "\'." << endl; continue; }

        //  Lê o arquivo caracter por caracter.
        string content;
        while(fpoint)
            content.push_back(fpoint.get());

        //  Fecha o arquivo.
        fpoint.close();

        //  Remove alguns caracteres.
        //  Quebra o conteúdo a partir de ':'.
        vector<string> splited = stringSplit(content, ":");

        //  Pega a identificação da coleta.
        collect.id = stoi(stringRemove(stringSplit(splited[1], ",")[0], "\""));

        //  Pega a identificação da amostra.
        collect.sample = stoi(stringRemove(stringSplit(splited[2], ",")[0], "\""));

        //  Separa os dados brutos do arquivo.
        for (int i = 25; i < splited.size(); i += 11)
        {
            string data = stringRemove(stringRemove(splited[i], "\"]},\"Collector.Model.Tarefa\""), "[\"");
            vector<string> dataSplited = stringSplit(data, "_");

            QTTask task;
            task.id = (i - 14) / 11;
            
            for (auto value = dataSplited.begin(); value != dataSplited.end(); ++value)
                task.values.push_back(stof(stringReplace(*value, ",", ".")));

            collect.tasks.push_back(task);
        }
        result.push_back(collect);
    }

    cout << "Dados quantitativos carregados com sucesso!" << endl;

    return result;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
list<QLSample> GetRawQL(list<std::string> files)
{
    list<QLSample> result;

    //  Separa os arquivos .cfg tomando eles como dados brutos qualitativos.
    list<string> qlFiles;
    cout << "Carregando arquivos qualitativos..." << endl;
    for (auto file = files.begin(); file != files.end(); ++file)
        if (stringEndsWith(*file, ".csv")) qlFiles.push_back(*file);

    //  Processa os arquivos qualitativos.
    for (auto file = qlFiles.begin(); file != qlFiles.end(); ++file)
    {
        //  Pega o nome do arquivo como identificador de amostragem.
        string split = stringSplit(stringSplit(*file, "/").back(), ".")[0];
        
        QLSample sample;
        sample.id = stoi(split);
        
        //  Abre o arquivo CSV e lê o conteúdo dele separando por linha.
        ifstream fpoint (*file);
        if (!fpoint.is_open()) { cout << "Falha ao abrir o arquivo \'" << *file << "\'." << endl; continue; }

        vector<string> lines;
        while (fpoint)
        {
            string line;
            getline(fpoint, line);
            if (line.empty()) continue;
            lines.push_back(line);
        }
                
        //  Fecha o arquivo.
        fpoint.close();

        //  Processa as linhas do arquivo (ignorando a primeira linha).
        for (auto line = lines.begin() + 1; line != lines.end(); ++line)
        {
            //  Elemento de coleta.
            QLCollect collect;
            //  Quebra a linha para separar os dados.
            vector<string> content = stringSplit(*line, ",");
            //  O index 0 é a data, ignora. O index 1 é Id, logo:
            collect.id = stoi(content[1]);
            //  O index 2 é a idade, então:
            collect.age = stoi(content[2]);

            //  A sequência é o conjunto de valores para cada tarefa, então:
            for (int i = 3; i < content.size(); i++)
            {
                QLTask task;
                task.id = i - 2;

                if (content[i].find("Muito Fofo") != string::npos) task.value = 10;
                else if (content[i].find("Repulsivo") != string::npos) task.value = 1;
                else { task.value = stoi(content[i]); }

                collect.tasks.push_back(task);
            }
        }
        result.push_back(sample);
    }
    cout << "Carregamento dos arquivos qualitativos finalizado!" << endl;
    return result;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
list<string> GetRawFiles(const char* path)
{
    //  Instância a lista.
    list<string> result;

    //  Pega os arquivos e diretórios do caminho passado.
    for (const auto & entry : filesystem::directory_iterator(path))
    {
        string path = entry.path();

        // Ignora arquivos .DS_Store para o caso de Mac.
        if (stringEndsWith(path, ".DS_Store")) continue;

        //  Se não possuir o caracter `.` ele interpreta como sendo um diretório e carrega os arquivos dentro dele.
        if (path.find('.') == string::npos)
        {
            list<string> subfiles = GetRawFiles(path.c_str());
            for (auto file = subfiles.begin(); file != subfiles.end(); ++file)
                result.push_back(*file);
        }
        
        //  Adiciona o diretório na lista.
        result.push_back(path);
    }

    return result;
}
*/
//
//          Load
//          Por Gabriel Ferreira (versão 1.0)
//          UFPR 2024
//
//      Carrega os conjuntos de dados que serão utilizados
//  pelo sistema para a análise. Os dados se dividem em
//  arquivos qualitativos e quantitativos.
#include "load.hpp"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>

#include "structs/ql.hpp"
#include "structs/qt.hpp"
#include "string.hpp"

/////////////////////////////////////////////////////////////////////////////
//      Carrega os arquivos presentes em uma determinada pasta.
//  (const char*) path: diretório de onde os arquivos devem ser tomados.
std::vector<std::string> GetFiles (const char* path)
{
    std::vector<std::string> result;

    for (const auto & entry : std::filesystem::directory_iterator(path))
    {
        std::string dir = entry.path();

        if (EndsWith(dir, ".DS_Store")) continue;

        if (dir.find(".") == std::string::npos)
        {
            std::vector<std::string> subfiles = GetFiles(dir.c_str());
            for (auto file = subfiles.begin(); file != subfiles.end(); ++file)
                result.push_back(*file);
        }

        result.push_back(dir);
    }

    return result;
}
/////////////////////////////////////////////////////////////////////////////
//      Pega os dados qualitativos a partir dos respectivos arquivos .csv
//  encontrados nos arquivos passados de referência.
//  (vector<string>) files: arquivos a serem analisados. Apenas os arquivos
//  .csv encontrados serão carregados como qualitativos na estrutura QL.
std::vector<QLSample> GetQL (const std::vector<std::string>& files)
{
    std::vector<QLSample> result;

    std::vector<std::string> qlfiles;
    for (auto file = files.begin(); file != files.end(); ++file)
        if (EndsWith(*file, ".csv")) qlfiles.push_back(*file);

    for (auto file = qlfiles.begin(); file != qlfiles.end(); ++file)
    {
        std::string name = Split(Split(*file, "/").back(), ".")[0];

        QLSample sample;
        sample.id = std::stoi(name);

        std::ifstream fpoint (*file);
        if (!fpoint.is_open()) { std::cout << "Falha ao abrir o arquivo \'" << *file << "\'." << std::endl; continue; }

        std::vector<std::string> lines;
        while (fpoint)
        {
            std::string line;
            getline(fpoint, line);
            if (line.empty()) continue;
            lines.push_back(line);
        }

        fpoint.close();

        for (auto line = lines.begin() + 1; line != lines.end(); ++line)
        {
             QLCollect collect;

             std::vector<std::string> content = Split(*line, ",");
             collect.id = std::stoi(content[1]);
             collect.age = std::stoi(content[2]);

            for (int i = 3; i < content.size(); i++)
            {
                QLTask task;
                task.id = i - 2;

                if (content[i].find("Muito Fofo") != std::string::npos) task.value = 10;
                else if (content[i].find("Repulsivo") != std::string::npos) task.value = 1;
                else { task.value = stoi(content[i]); }

                collect.tasks.push_back(task);
            }

            sample.collects.push_back(collect);
        }
        result.push_back(sample);
    }

    return result;
}
/////////////////////////////////////////////////////////////////////////////
//      Pega os dados quantitativos a partir dos respectivos arquivos .json
//  encontrados nos arquivos passados de referência.
//  (vector<string>) files: arquivos a serem analisados. Apenas os arquivos
//  .json encontrados serão carregados como qualitativos na estrutura QT.
std::vector<QTCollect> GetQT (const std::vector<std::string>& files)
{
    std::vector<QTCollect> result;

    std::vector<std::string> qtfiles;
    for (auto file = files.begin(); file != files.end(); ++file)
        if (EndsWith(*file, ".json")) qtfiles.push_back(*file);

    for (auto file = qtfiles.begin(); file != qtfiles.end(); ++file)
    {
        QTCollect collect;

        std::ifstream fpoint (*file);
        if (!fpoint.is_open()) { std::cout << "Falha ao abrir o arquivo \'" << *file << "\'." << std::endl; continue; }

        std::string content;
        while(fpoint)
            content.push_back(fpoint.get());

        fpoint.close();

        std::vector<std::string> splited = Split(content, ":");
        collect.id = std::stoi(Remove(Split(splited[1], ",")[0], "\""));
        collect.sample = std::stoi(Remove(Split(splited[2], ",")[0], "\""));

        for (int i = 25; i < splited.size(); i += 11)
        {
            std::string data = Remove(Remove(splited[i], "\"]},\"Collector.Model.Tarefa\""), "[\"");
            std::vector<std::string> dataSplited = Split(data, "_");

            QTTask task;
            task.id = (i - 14) / 11;
            
            for (auto value = dataSplited.begin(); value != dataSplited.end(); ++value)
                task.values.push_back(std::stof(Replace(*value, ",", ".")));

            collect.tasks.push_back(task);
        }
        result.push_back(collect);
    }

    return result;
}
/////////////////////////////////////////////////////////////////////////////
//
//      NINC JSON Parser (.cpp file)
//      Por Gabriel Ferreira (versão 1.0)
//      UFPR, 2024
#include "parser.hpp"

#include <list>
#include <string>
#include <iostream>
#include <filesystem>

#include "aux.hpp"
#include "collect.hpp"

using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////////
list<Collect> RawParse(const char* rawpath)
{
    GetRawFiles(rawpath);
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
        if (!(path.find('.') != string::npos))
        {
            list<string> subfiles = GetRawFiles(path.c_str());
            for (auto file = subfiles.begin(); file != subfiles.end(); ++file)
            {
                cout << "Add: " << *file << endl;
                result.push_back(*file);
            }
            continue;
        }
        
        cout << path << endl;
    }

    return result;
}
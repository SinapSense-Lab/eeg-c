//
//      Aux functions (.cpp file)
//      Por Gabriel Ferreira (versão 1.0)
//      UFPR, 2024
#include "aux.hpp"

#include <string>
#include <vector>
#include <iostream>

using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Base: https://devptr.com/check-if-string-ends-with-substring-in-c/
bool stringEndsWith(const string& str, const string& subStr)
{
    size_t strLen = str.length();
    size_t subStrLen = subStr.length();

    return strLen >= subStrLen && str.compare(strLen - subStrLen, subStrLen, subStr) == 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Base: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
vector<string> stringSplit(const string& str, const string& delimiter)
{
    string s = str;
    size_t pos = s.find(delimiter);

    vector<string> result;

    while (pos != std::string::npos)
    {
        pos = s.find(delimiter);
        result.push_back(s.substr(0, pos));
        s.erase(0, pos + delimiter.length());
    }
    return result;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string stringRemove(const std::string& str, const std::string& target)
{
    string s = str;
    size_t pos = s.find(target);

    while (pos != std::string::npos)
    {
        s.erase(pos, pos + target.length());
        pos = s.find(target);
    }

    return s;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string stringReplace(const std::string& str, const std::string& old, const std::string& replace)
{
    string s = str;
    size_t pos = s.find(old);

    while (pos != std::string::npos)
    {
        s.replace(pos, old.length(), replace);
        pos = s.find(old); 
    }
    return s;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////∂
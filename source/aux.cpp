//
//      Aux functions (.cpp file)
//      Por Gabriel Ferreira (versão 1.0)
//      UFPR, 2024
#include "aux.hpp"

#include <string>

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
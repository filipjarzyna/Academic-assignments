// Filip Jarzyna
#include <cstdarg>
#include <string>
using namespace std;

const string* VaListToString(int count, int index, va_list args, string result[])
{
    if (count > 0) {
        result[index] = va_arg(args, const char*);
        return VaListToString(count - 1, index + 1, args, result);
    }
    return result;
}
//
string Operation(string (*oper)(int num, const string* args), int num, const string* args)
{
    return (*oper)(num, args);
}

////////////////////////// TO NIE DZIALA
string Operation(string (*oper)(int num, const string* args), int count, ...)
{
    va_list argsV;
    va_start(argsV, count);
    string converted[count];
    const string* args = VaListToString(count, 0, argsV, converted);
    va_end(argsV);
    return (*oper)(count, args);
}

////////////////////////// TO NIE DZIALA
void Operation(string* result, string (*oper)(int num, const string* args), int count, ...)
{
    va_list argsV;
    va_start(argsV, count);
    string converted[count];
    const string* args = VaListToString(count, 0, argsV, converted);
    va_end(argsV);
    *result = (*oper)(count, args);
}

void Operation(string* result, string (*oper)(int num, const string* args), int num, const string* args)
{
    *result = (*oper)(num, args);
}

void Operation(string& result, void (*oper)(string* result, int num, const string* args), int num, const string* args)
{
    (*oper)(&result, num, args);
}

////////////////////////// TO NIE DZIALA
void Operation(string& result, void (*oper)(string* result, int num, const string* args), int count, ...)
{
    va_list argsV;
    va_start(argsV, count);
    string converted[count];
    const string* args = VaListToString(count, 0, argsV, converted);
    va_end(argsV);
    (*oper)(&result, count, args);
}
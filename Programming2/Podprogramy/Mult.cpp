// Filip Jarzyna
#include <cstdarg>
#include <string>
using namespace std;

void CleanString(string* str);
string SumTwoStrings(string *str1, string *str2);

void MultByOneElem(string* result, string* arg, char multiplier, int index, char carry)
{
    if (index < 0) {
        (*result)[0] = carry + 48;
        return;
    }
    char elem = (*arg)[index];
    elem -= 48;
    char sum = (multiplier * elem) + carry; // max 90
    carry = sum / 10;
    sum -= carry * 10;
    (*result)[index + 1] = sum + 48;

    MultByOneElem(result, arg, multiplier, index - 1, carry);
}

// arg1 >= arg2  i len1 >= len2
void FullMult(string* result, string arg1, string arg2, int len1,  int index2, int multByTen)
{
    if (index2 < 0) {
        char sign1 = arg1[0];
        char sign2 = arg2[0];
        if ((sign1 == '-' && sign2 == '+') || sign1 == '+' && sign2 == '-') {
            (*result)[0] = '-';
        }

        return;
    }

    string multBySingle(len1 + 1, '0');
    MultByOneElem(&multBySingle, &arg1, arg2[index2] - 48, len1 - 1, 0);
    
    multBySingle.append(multByTen, '0');

    *result = SumTwoStrings(result, &multBySingle);
    FullMult(result, arg1, arg2, len1, index2 - 1, multByTen + 1);
}

string MultTwoStrings(string arg1, string arg2)
{
    char sign1 = arg1[0];
    char sign2 = arg2[0];
    CleanString(&arg1);
    CleanString(&arg2);

    if (sign1 == '-') {
        arg1.erase(0, 1);
    } else {
        sign1 = '+';
    }

    if (sign2 == '-' || sign2 == '+') {
        arg2.erase(0, 1);
    } else {
        sign2 = '+';
    }

    int len1 = arg1.length();
    int len2 = arg2.length();
    int size = len1 + len2;
    bool isNeg = false;

    if (sign1 != sign2) {
        isNeg = true;
        size++; // miejsce dodatkowe na '-'
    }

    string result(size, '0');

    bool FirstBigger = false;

    if (len1 > len2) {
        FirstBigger = true;
    } else if (len1 == len2) {
        if (arg1.compare(arg2) < 0) {
            FirstBigger = true;
        }
    }

    if (FirstBigger)
        FullMult(&result, arg1, arg2, len1, len2 - 1, 0);
    else
        FullMult(&result, arg2, arg1, len2, len1 - 1, 0);

    CleanString(&result);
    if (isNeg && result[0] != '0') {
        result = "-" + result;
    }
    return result;
}

void MultAll(string* result, const string* args, int num)
{
    if (num > 0) {
        string firstArg = args[num - 1];
        *result = MultTwoStrings(*result, firstArg);
        MultAll(result, args, num - 1);
    } else {
        CleanString(result);
    }
}

void MultAll(int count, string* result, va_list args)
{
    if (count > 0) {
        *result = MultTwoStrings(*result, (string)va_arg(args, char*));
        MultAll(count - 1, result, args);
    } else {
        CleanString(result);
    }
}

string Mult(int num, const string* args)
{
    string result = "1";
    MultAll(&result, args, num);
    return result;
}

string Mult(int count, ...)
{
    va_list args;
    va_start(args, count);
    string result = "1";
    MultAll(count, &result, args);
    va_end(args);
    return result;
}

void Mult(string* result, int num, const string* args)
{
    *result = "1";
    MultAll(result, args, num);
}

void Mult(string& result, int num, const string* args)
{
    result = "1";
    MultAll(&result, args, num);
}

void Mult(string* result, int count, ...)
{
    va_list args;
    va_start(args, count);
    *result = "1";
    MultAll(count, result, args);
    va_end(args);
}

void Mult(string& result, int count, ...)
{
    va_list args;
    va_start(args, count);
    result = "1";
    MultAll(count, &result, args);
    va_end(args);
}
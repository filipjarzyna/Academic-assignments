// Filip Jarzyna
#include <cstdarg>
#include <string>
using namespace std;

void CleanString(string* str)
{
    // +0000002 ==> +2
    int length = (*str).length();
    if ((*str)[0] != '-' && (*str)[0] != '+') { // gdy nie ma znaku z przodu
        unsigned int pos = (*str).find_first_not_of('0');
        if (pos >= length)
            pos = length - 1; // gdyby same 0 byly

        if (pos >= 0) {
            (*str).erase(0, pos);
        }
    } else if ((*str)[1] == '0') {
        unsigned int pos = (*str).find_first_not_of("0-+");
        if (pos >= length)
            pos = length - 1; // gdyby same 0 byly

        (*str).erase(1, pos - 1);
    }
}

// zakladamy str1 >= str2 i index1 >= index2
void FullAdder(string* result, string* str1, string* str2, int index1, int index2, char carryIn)
{
    if (index1 < 0) {
        (*result)[1] = carryIn + 48;
        return;
    }
    char sum = 0;
    char arg1 = (*str1)[index1];
    char arg2 = '0';

    if (index2 >= 0)
        arg2 = (*str2)[index2];

    arg1 -= 48;
    arg2 -= 48;

    sum = arg1 + arg2 + carryIn;
    if (sum > 9) {
        sum -= 10;
        carryIn = 1;
    } else {
        carryIn = 0;
    }
    sum += 48;
    (*result)[index1 + 2] = sum;

    FullAdder(result, str1, str2, index1 - 1, index2 - 1, carryIn);
}

// str1 - str2  zakladamy ze |str1| >= |str2|
void FullSub(string* result, string* str1, string* str2, int index1, int index2, char carryIn)
{
    if (index1 < 0) {
        return;
    }

    char sum = 0;
    char arg1 = (*str1)[index1];
    char arg2 = '0';

    if (index2 >= 0)
        arg2 = (*str2)[index2];

    arg1 -= 48;
    arg2 -= 48;

    sum = arg1 - arg2 - carryIn; // max -10
    if (sum < 0) {
        sum += 10;
        carryIn = 1;
    } else {
        carryIn = 0;
    }
    sum += 48;
    (*result)[index1 + 2] = sum;

    FullSub(result, str1, str2, index1 - 1, index2 - 1, carryIn);
}

string SumTwoStrings(string *str1, string *str2)
{
    char sign1 = (*str1)[0];
    char sign2 = (*str2)[0];
    CleanString(str1); // czysci 0
    CleanString(str2);

    // jesli bez znaku to wiemy ze dodatnie
    if (sign1 == '+' || sign1 == '-') {
        (*str1).erase(0, 1);
    }
    if (sign2 == '+' || sign2 == '-') {
        (*str2).erase(0, 1);
    }

    int length1 = (*str1).length();
    int length2 = (*str2).length();
    int size = length2 + 2;

    bool FirstBigger = false;
    int comp = (*str1).compare((*str2));

    if (length1 > length2) {
        FirstBigger = true;
        size = length1 + 2;
    } else if (length1 == length2) {
        if (comp > 0) {
            FirstBigger = true;
            size = length1 + 2;
        }
    }

    string result(size, '0'); // string z samymi charami 0
    char negs = 0;

    if (sign1 == '-')
        negs++;
    if (sign2 == '-')
        negs++;

    switch (negs) {
    case 0: // + +
        if (FirstBigger)
            FullAdder(&result, str1, str2, length1 - 1, length2 - 1, 0);
        else
            FullAdder(&result, str2, str1, length2 - 1, length1 - 1, 0);
        break;
    case 1: // - + albo + -
        if (comp == 0) {
            return "0";
        }
        if (FirstBigger) {
            FullSub(&result, str1, str2, length1 - 1, length2 - 1, 0);
            if (sign1 == '-')
                result[0] = sign1;
        } else {
            FullSub(&result, str2, str1, length2 - 1, length1 - 1, 0);
            if (sign2 == '-')
                result[0] = sign2;
        }
        break;
    case 2: //- -
        if (FirstBigger)
            FullAdder(&result, str1, str2, length1 - 1, length2 - 1, 0);
        else
            FullAdder(&result, str2, str1, length2 - 1, length1 - 1, 0);

        if (result[1] != '0') {
            result[0] = '-';
        } else {
            result[1] = '-';
            result.erase(0, 1); // usun pierwszy char bo zbedny
        }

        break;
    }

    CleanString(&result);
    return result;
}

void SumAllStrings(string* result, const string* args, int num)
{
    if (num > 0) {
        string firstArg = args[num - 1];
        *result = SumTwoStrings(result, &firstArg);
        SumAllStrings(result, args, num - 1);
    } else {
        CleanString(result);
    }
}

void SumAllStrings(int count, string* result, va_list args)
{
    if (count > 0) {
        string firstArg = (string)va_arg(args, char*);
        *result = SumTwoStrings(result, &firstArg);
        SumAllStrings(count - 1, result, args);
    } else {
        CleanString(result);
    }
}

// 1
string Sum(int num, const string* args)
{
    string result = "0";
    SumAllStrings(&result, args, num);
    return result;
}

string Sum(int count, ...)
{
    va_list args;
    va_start(args, count);
    string result = "0";
    SumAllStrings(count, &result, args);
    va_end(args);
    return result;
}

/// nie dziala na dole

void Sum(string* result, int num, const string* args)
{
    *result = Sum(num, args);
}

void Sum(string* result, int count, ...)
{
    va_list args;
    va_start(args, count);
    *result = "0";
    SumAllStrings(count, result, args);
    va_end(args);
}

void Sum(string& result, int num, const string* args)
{
    result = Sum(num, args);
}

void Sum(string& result, int count, ...)
{
    va_list args;
    va_start(args, count);
    result = "0";
    SumAllStrings(count, &result, args);
    va_end(args);
}
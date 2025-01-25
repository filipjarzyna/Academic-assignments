#include <iostream>
using namespace std;

/*
Napisać program wyliczający wartość wyrażenia z argumentów wywołania. Operandy mogą być liczbami całkowitymi z zakresu typu int,
zaś operatory mogą być jedynie czterema tradycyjnymi operatorami działań arytmetycznych. Należy jednak dopuścić użycie jednej pary okrągłych nawiasów.
Można przyjąć rozsądny (nie  ograniczający nadmiernie) zakres ilości znaków argumentu (na przykład 128)
oraz podobnie nie ograniczającą maksymalna liczbę operatorów i operandów (na przykład 16).
Uwaga: obsługiwana postać wyrażenia z punktu widzenia spacji musi być zgodna z indywidualnie używaną postacią wyrażeń arytmetycznych w zadaniach na BaCy.
*/

bool WiekszyPriorytet(char znak1[], char znak2[])
{
    char temp1 = znak1[0];
    char temp2 = znak2[0];

    if (temp1 == '+' || temp1 == '-') {
        if (temp2 == '/' || temp2 == '*') {
        }
    } else {
        return false;
    }
}

int WykonajDzialanie(int a, int b, char znak)
{
    int wynik;
    if (znak == '+')
        wynik = a + b;
    else if (znak == '-')
        wynik = a - b;
    else if (znak == '/')
        wynik = a / b;
    else if (znak == '*')
        wynik = a * b;

    return wynik;
}

int CharToInt(char liczba[])
{
    int i = 0;
    int wynik = 0;
    int minus = 1;

    if (liczba[0] = '-') {
        minus = -1;
        i = 1;
    }

    while (liczba[i] != 0) {
        wynik += (liczba[i] - 48);
    }

    return (wynik * minus);
}

int main(int argc, char* argv[])
{
    // priorytety operacji (wymyslone)
    //  /   ->  0
    //  *   ->  0
    //  +   ->  1
    //  -   ->  1
    // brak -> 2
    if (argc > 0) {
        int operand1 = CharToInt(argv[0]);
        int operand2 = 1;
        char operat; // nazwa "operator" jest chyba zarezerwowana bo sie sra
        bool Op2Wczytany = 0;
        bool Op1Wczytany = 0;
        int priorytetOperatora = 2;
        int priorytetOperatoraNastepnego = 2;

        // 1 + 2 + 3 / 4

        int i = 1;
        while (i < argc) {

            operat = argv[i];
            operand2 = CharToInt(argv[i + 1]);
            // niby to argv jest dwuwymiarowa ale tak chyba git?
            char kolejnyZnak = argv[i + 2];
            //gdy napotkamy za nimi / lub *
            if (WiekszyPriorytet(kolejnyZnak, operat)) {
                int operand3 = CharToInt(argv[i + 3]);
                operand2 = WykonajDzialanie(operand2, operand3, kolejnyZnak);
                // skipowac nastepna pare bo juz wykonana operacja
                i += 2;
            }

            operand1 = WykonajDzialanie(operand1, operand2, operat);

            i += 2
        }
    }
}
#include <iostream>
using namespace std;

void Mnozenie(char licz1[], char licz2[], int dlug1, int dlug2)
{
    int index = dlug1 + dlug2;
    char wynik[index];

    for (int i = 0; i < index; i++) {
        wynik[i] = 0;
    }

    for (int i = 0; i < dlug1; i++) {
        licz1[i] -= 48;
    }
    for (int i = 0; i < dlug2; i++) {
        licz2[i] -= 48;
    }

    dlug1 -= 1;
    dlug2 -= 1;

    char przeniesienie = 0;
    for (int i = dlug1; i >= 0; i--) {
        for (int k = dlug2; k >= 0; k--) {

            wynik[k + i + 1] += (licz2[k] * licz1[i]) + przeniesienie;
            przeniesienie = wynik[k + i + 1] / 10;
            wynik[k + i + 1] -= przeniesienie * 10;
        }
    }
    if (przeniesienie != 0) {
        wynik[0] = przeniesienie;
    }
    


    int t;
    for (t = 0; t < dlug1 + dlug2 + 1; t++) {
        if (wynik[t] != 0) {
            break;
        }

    }

    for (int i = 0; i < index; i++) {
        wynik[i] += 48;
    }

    while (t < dlug1 + dlug2 + 2) {
        cout << wynik[t];
        t++;
    }
}

int main()
{
    int dlugosc1;
    int dlugosc2;

    cout << "dlugosc1: " << endl;
    cin >> dlugosc1;
    cout << "dlugosc2: " << endl;
    cin >> dlugosc2;

    char licz1[dlugosc1];
    char licz2[dlugosc2];

    cout << "licz1: " << endl;
    for (int i = 0; i < dlugosc1; i++) {
        cin >> licz1[i];
    }
    cout << "licz2: " << endl;
    for (int i = 0; i < dlugosc2; i++) {
        cin >> licz2[i];
    }

    if (dlugosc1 > dlugosc2) {
        Mnozenie(licz1, licz2, dlugosc1, dlugosc2);
    } else {
        Mnozenie(licz1, licz2, dlugosc1, dlugosc2);
    }

    return 0;
}
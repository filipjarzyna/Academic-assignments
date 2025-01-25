#include <iostream>
using namespace std;

void Mnozenie(float wielW[], float wielM[], int wspolW, int wspolM)
{
    int ileWspolWynik = wspolW + wspolM - 1;
    float wynik[ileWspolWynik];

    for (int i = 0; i < ileWspolWynik; i++) {
        wynik[i] = 0;
    }

    for (int i = 0; i < wspolW; i++) {
        for (int k = 0; k < wspolM; k++) {
            wynik[i + k] += (wielW[i] * wielM[k]);
        }
    }

    for (int i = 0; i < ileWspolWynik; i++) {
        if (wynik[i] != 0) {
            cout << wynik[i] << "x^" << (ileWspolWynik - 1 - i) << " ";
        }
    }
}

int main()
{

    int wspol1;
    int wspol2;

    cout << "wspol1: " << endl;
    cin >> wspol1;
    cout << "wspol2: " << endl;
    cin >> wspol2;

    float wiel1[wspol1];
    float wiel2[wspol2];

    cout << "wiel1: " << endl;
    for (int i = 0; i < wspol1; i++) {
        cin >> wiel1[i];
    }
    cout << "wiel2: " << endl;
    for (int i = 0; i < wspol2; i++) {
        cin >> wiel2[i];
    }
    // mnozenie
    if (wspol1 > wspol2) {
        Mnozenie(wiel1, wiel2, wspol1, wspol2);
    } else {
        Mnozenie(wiel2, wiel1, wspol2, wspol1);
    }
}
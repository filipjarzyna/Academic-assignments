#include <iostream>
using namespace std;

int main()
{

    int ile1 = 0;
    int ile2 = 0;

    cout << "ile wspolczynnikow wielomianu 1: " << endl;
    cin >> ile1;

    cout << "ile wspolczynnikow wielomianu 2: " << endl;
    cin >> ile2;

    float wielomian1[ile1];
    float wielomian2[ile2];

    cout << "wspolczynniki 1: " << endl;
    for (int i = 0; i < ile1; i++) {
        cin >> wielomian1[i];
    }

    cout << "wspolczynniki 2: " << endl;
    for (int i = 0; i < ile2; i++) {
        cin >> wielomian2[i];
    }

    bool ile1Wiekszy = 0;

    if (ile1 > ile2) {
        for (int i = 0; i < ile2; i++) {
            wielomian1[i] += wielomian2[i];
        }
    } else {
        for (int i = 0; i < ile1; i++) {
            wielomian2[i] += wielomian1[i];
        }
    }
    
    bool sameZera = 1;

    if (ile1 > ile2) {
        for (int i = 0; i < ile1; i++) {
            if (wielomian1[i] != 0) {
                cout << wielomian1[i] << "x^" << i << " ";
                sameZera = 0;
            } 
        }
    } else {
        for (int i = 0; i < ile2; i++) {
            if (wielomian2[i] != 0) {
                cout << wielomian2[i] << "x^" << i << " ";
                sameZera = 0;
            }
        }
    }
    if(sameZera){
        cout << 0 << endl;
    }
    return 0;
}
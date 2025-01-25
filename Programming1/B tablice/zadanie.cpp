// Filip Jarzyna
#include <iostream>
using namespace std;

int main()
{

    int ileSesji; // Z+
    int i = 0;

    cin >> ileSesji;
    // SESJA
    while (i < ileSesji) {
        int ileElementow;
        int t;

        cin >> ileElementow;
        int tablica[ileElementow];
        t = 0;
        while (t < ileElementow) {
            cin >> tablica[t];
            t = t + 1;
        }
        // wypisanie tablicy przed zmianą
        t = 0;
        while (t < ileElementow) {
            cout << tablica[t] << " ";
            t = t + 1;
        }
        cout << endl;

        char literaOperacji = 'x';
        while (literaOperacji != 'F') {

            cin >> literaOperacji;
            // ODWRACANIE
            if (literaOperacji == 'R') {
                // par1 = indeks pierwszego elementu fragmentu (dowolna Z)
                // par2 = długość fragmentu (0 <= x <= ileElementow)
                int par1R = 0;
                int par2R = 0;
                cin >> par1R >> par2R;

                if (par2R != 0) {
                    int poczFragR; // poczatek framgentu
                    int konFragR; // koniec fragmentu
                    int tempR; // zmienna do swapa
                    int fR; // zmienna do while dla operacji
                    int xR;
                    int ileZamianR;
                    int ileFragmentowR;
                    int BezwzglPoczatekR;
                    // liczenie rzeczywistego indeksu
                    par1R = ((par1R % ileElementow) + ileElementow) % ileElementow;
                    ileFragmentowR = ileElementow / par2R;
                    BezwzglPoczatekR = par1R;
                    poczFragR = par1R;
                    konFragR = ((par1R + par2R - 1) % ileElementow) % ileElementow;
                    ileZamianR = par2R / 2;
                    // odwracanie po kolei
                    fR = 0;
                    xR = 0;
                    while (fR < ileFragmentowR) {
                        xR = 0;
                        while (xR < ileZamianR) {
                            tempR = tablica[poczFragR];
                            tablica[poczFragR] = tablica[konFragR];
                            tablica[konFragR] = tempR;

                            poczFragR = ((poczFragR + 1) % ileElementow + ileElementow) % ileElementow;
                            konFragR = (((konFragR - 1) % ileElementow + ileElementow) % ileElementow) % ileElementow;
                            xR = xR + 1;
                        }

                        BezwzglPoczatekR = (((BezwzglPoczatekR + par2R) % ileElementow) + ileElementow) % ileElementow;
                        konFragR = (((BezwzglPoczatekR + par2R - 1) % ileElementow) + ileElementow) % ileElementow;
                        poczFragR = BezwzglPoczatekR;
                        fR = fR + 1;
                    }
                }
            }
            // PRZESUNIECIE
            else if (literaOperacji == 'M') {
                int par1M;
                int par2M;
                int par3M;
                cin >> par1M >> par2M >> par3M;
                // par1 = indeks pierwszego elemntu (Z)
                // par2 = dlugosc fragmentu (0 < = par2 < = ileElementow)
                // par3 = przesuniecie (dodatnia = w prawo , ujemna = w lewo)
                if (par2M != 0) {
                    int przesuniecieFragmentuDziwnM;
                    int tempM; // zmienna do swapa
                    int fM; // zmienna do while dla operacji
                    int yM;
                    int xM;
                    int wM;
                    int ileFragmentowM;
                    int dlugoscFragmDziwnegoM = 0;
                    int BezwzglPoczatekM;
                    // liczenie rzeczywistego indeksu
                    par1M = ((par1M % ileElementow) + ileElementow) % ileElementow;
                    ileFragmentowM = ileElementow / par2M;
                    dlugoscFragmDziwnegoM = ileElementow % par2M;
                    BezwzglPoczatekM = par1M;

                    // Przesuniecie Rzeczywiste
                    if (par3M < 0) {
                        if (dlugoscFragmDziwnegoM > 0)
                            przesuniecieFragmentuDziwnM = (par3M % dlugoscFragmDziwnegoM) + dlugoscFragmDziwnegoM;
                        par3M = (par3M % par2M) + par2M;
                    } else {
                        if (dlugoscFragmDziwnegoM > 0)
                            przesuniecieFragmentuDziwnM = (par3M % dlugoscFragmDziwnegoM);
                        par3M = par3M % par2M;
                    }
                    // POMYSL 1 POJEDYNCZE PRZESUNIECIE
                    // zmienne do while
                    // dla kazdego fragmentu
                    fM = 0;
                    while (fM < ileFragmentowM) {
                        par1M = (BezwzglPoczatekM + (par2M * fM)) % ileElementow;
                        // ile razy przesuwamy o 1
                        yM = 0;
                        while (yM < par3M) {
                            // przesuniecie o 1
                            tempM = tablica[(par1M + par2M - 1) % ileElementow];
                            xM = (par1M + par2M - 1) % ileElementow;
                            // z = (x - 1 + ileElementow) % ileElementow;
                            wM = 0;
                            while (wM < (par2M - 1)) {
                                tablica[(xM - wM + ileElementow) % ileElementow] = tablica[(xM - wM - 1 + ileElementow) % ileElementow];

                                // x = (x - 1 + ileElementow) % ileElementow;
                                // z = (x - 1 + ileElementow) % ileElementow;
                                wM = wM + 1;
                            }
                            tablica[par1M] = tempM;
                            yM = yM + 1;
                        }
                        fM = fM + 1;
                    }
                    // przesuwanie fragmentu (dziwnego) co ma mniejsza dlugosc od normalnych
                    if (dlugoscFragmDziwnegoM > 1) {

                        par1M = (BezwzglPoczatekM + (par2M * fM)) % ileElementow;
                        // ile razy przesuwamy o 1
                        yM = 0;
                        while (yM < przesuniecieFragmentuDziwnM) {

                            // przesuniecie o 1
                            tempM = tablica[(par1M + dlugoscFragmDziwnegoM - 1) % ileElementow];
                            xM = (par1M + dlugoscFragmDziwnegoM - 1) % ileElementow;
                            // z = (x 1 + ileElementow) % ileElementow;
                            wM = 0;
                            while (wM < (dlugoscFragmDziwnegoM - 1)) {
                                tablica[(xM - wM + ileElementow) % ileElementow] = tablica[(xM - wM - 1 + ileElementow) % ileElementow];
                                wM = wM + 1;
                            }
                            tablica[par1M] = tempM;
                            yM = yM + 1;
                        }
                    }
                }
            } // ZAMIANA PARAMI
            else if (literaOperacji == 'C') {
                int par1C;
                int par2C;
                cin >> par1C >> par2C;
                // par1 indeks (Z)
                // par2 dlugosc fragmentu (0 <= par2 < ileElementow)

                if (par2C != 0) {
                    int poczFragC; // poczatek framgentu
                    int konFragC; // koniec fragmentu
                    int tempC; // zmienna do swapa
                    int fC; // zmienna do while dla operacji
                    int xC;
                    int ileFragmentowC;
                    int BezwzglPoczatekC;
                    int ilePar;
                    // liczenie rzeczywistego indeksu
                    par1C = ((par1C % ileElementow) + ileElementow) % ileElementow;
                    
                    BezwzglPoczatekC = par1C;
                    poczFragC = par1C;
                    konFragC = (par1C + par2C) % ileElementow; // drugi fragment poczatek
                    ileFragmentowC = ileElementow / par2C;
                    ilePar = ileFragmentowC / 2;

                    if (ilePar != 0) {
                        fC = 0;
                        while (fC < ilePar) {
                            xC = 0;
                            // kolejna zamiana
                            while (xC < par2C) {
                                tempC = tablica[poczFragC];
                                tablica[poczFragC] = tablica[konFragC];
                                tablica[konFragC] = tempC;

                                poczFragC = (poczFragC + 1) % ileElementow;
                                konFragC = (konFragC + 1) % ileElementow;
                                xC = xC + 1;
                            }

                            BezwzglPoczatekC = (BezwzglPoczatekC + (2 * par2C)) % ileElementow;
                            konFragC = (BezwzglPoczatekC + par2C) % ileElementow;
                            poczFragC = BezwzglPoczatekC;
                            fC = fC + 1;
                        }
                    }
                }

            } else if (literaOperacji == 'S') {
                int par1S;
                int par2S;
                cin >> par1S >> par2S;
                // par1 indeks (Z)
                // par2 dlugosc fragmentu (Z)
                if (par2S != 0) {
                    int tempS; // zmienna do swapa
                    int fS; // zmienna do while dla operacji
                    int yS;
                    int xS;
                    int zS;
                    int wS;
                    int ileFragmentowS;
                    int dlugoscFragmDziwnegoS = 0;

                    bool ujemnySort = false; // czy sortujemy malejaco czy rosnaco
                    if (par2S < 0) {
                        ujemnySort = true;
                        par2S = par2S * (-1);
                    }
                    // liczenie rzeczywistego indeksu
                    par1S = ((par1S % ileElementow) + ileElementow) % ileElementow;
                    
                    ileFragmentowS = ileElementow / par2S;
                    dlugoscFragmDziwnegoS = ileElementow % par2S;
                    bool brakZamiany;
                    int indeks;
                    fS = 0;
                    while (fS < ileFragmentowS) {
                        xS = (par1S + (par2S * fS)) % ileElementow; // indeks pierwszego
                        zS = (par1S + (par2S * (fS + 1)) - 1 + ileElementow) % ileElementow; // indeks ostatniego
                        yS = 0;
                        brakZamiany = false;

                        if (ujemnySort) {
                            // malejacy sort
                            while (brakZamiany == false) {
                                brakZamiany = true;
                                wS = 1;
                                while (wS < par2S) {
                                    indeks = (xS + 1) % ileElementow;
                                    if (tablica[xS] < tablica[indeks]) {
                                        // zamiana
                                        tempS = tablica[xS];
                                        tablica[xS] = tablica[indeks];
                                        tablica[indeks] = tempS;
                                        brakZamiany = false;
                                    }
                                    wS = wS + 1;
                                    xS = (xS + 1) % ileElementow;
                                }
                                xS = (par1S + (par2S * fS)) % ileElementow;
                            }
                        } else {
                            // rosnący sort
                            while (brakZamiany == false) {
                                brakZamiany = true;
                                wS = 1;
                                while (wS < par2S) {
                                    indeks = (xS + 1) % ileElementow;
                                    if (tablica[xS] > tablica[indeks]) {
                                        // zamiana
                                        tempS = tablica[xS];
                                        tablica[xS] = tablica[indeks];
                                        tablica[indeks] = tempS;
                                        brakZamiany = false;
                                    }
                                    wS = wS + 1;
                                    xS = (xS + 1) % ileElementow;
                                }
                                xS = (par1S + (par2S * fS)) % ileElementow;
                            }
                        }

                        fS = fS + 1;
                    }
                    if (dlugoscFragmDziwnegoS > 0) {
                        xS = (par1S + (par2S * fS)) % ileElementow;
                        zS = (xS + dlugoscFragmDziwnegoS - 1 + ileElementow) % ileElementow;
                        yS = 0;
                        brakZamiany = false;
                        if (ujemnySort) {
                            // malejacy sort
                            while (brakZamiany == false) {
                                brakZamiany = true;
                                wS = 1;
                                while (wS < dlugoscFragmDziwnegoS) {
                                    indeks = (xS + 1) % ileElementow;
                                    if (tablica[xS] < tablica[indeks]) {
                                        // zamiana
                                        tempS = tablica[xS];
                                        tablica[xS] = tablica[indeks];
                                        tablica[indeks] = tempS;
                                        brakZamiany = false;
                                    }
                                    wS = wS + 1;
                                    xS = (xS + 1) % ileElementow;
                                }
                                xS = (par1S + (par2S * fS)) % ileElementow;
                            }
                        } else {
                            // rosnący sort
                            while (brakZamiany == false) {
                                brakZamiany = true;
                                wS = 1;
                                while (wS < dlugoscFragmDziwnegoS) {
                                    indeks = (xS + 1) % ileElementow;
                                    if (tablica[xS] > tablica[indeks]) {
                                        // zamiana
                                        tempS = tablica[xS];
                                        tablica[xS] = tablica[indeks];
                                        tablica[indeks] = tempS;
                                        brakZamiany = false;
                                    }
                                    wS = wS + 1;
                                    xS = (xS + 1) % ileElementow;
                                }
                                xS = (par1S + (par2S * fS)) % ileElementow;
                            }
                        }
                    }
                }

            } else if (literaOperacji == 'F') {
                int fF;
                fF = 0;
                while (fF < ileElementow) {
                    cout << tablica[fF] << " ";
                    fF = fF + 1;
                }
                cout << endl;
            }
        }
        i = i + 1;
    }
    return 0;
}

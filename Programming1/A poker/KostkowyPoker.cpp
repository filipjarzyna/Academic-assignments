// Filip Jarzyna
#include <iostream>
using namespace std;

int main()
{
    int gralA = 0;
    int gralB = 0;
    int gralC = 0;
    int gralD = 0;
    int gralE = 0;
    // przegrane z roznicy sie obliczy
    bool wygranaL = 0;
    int wygraneA = 0;
    int wygraneB = 0;
    int wygraneC = 0;
    int wygraneD = 0;
    int wygraneE = 0;
    int przegraneA = 0;
    int przegraneB = 0;
    int przegraneC = 0;
    int przegraneD = 0;
    int przegraneE = 0;
    int remisyA = 0;
    int remisyB = 0;
    int remisyC = 0;
    int remisyD = 0;
    int remisyE = 0;
    int ileRozgrywek;
    // L - lewy gracz  P - prawy gracz
    // jaka litera gracza
    char graczL = 'L';
    char graczP = 'P';

    int rzut1L;
    int rzut2L;
    int rzut3L;
    int rzut4L;
    int rzut1P;
    int rzut2P;
    int rzut3P;
    int rzut4P;
    // wystarczy jedna bo potem zapiszemy wyniki w zdobytePunkty
    int zdobytePunkty = 0;
    // punkty gracza lewego i prawego dla pojedynczej partii
    int zdobytePunktyL;
    int zdobytePunktyP;

    int ileJednakowych = 0;
    int bezPowtorzen = 0;
    // zmienne do petli
    int t = 1;
    int i = 0;
    int d = 0;
    int maxL = 0;
    int maxP = 0;
    cin >> ileRozgrywek;
    while (i < ileRozgrywek) {
        // reset wynikow graczy
        zdobytePunktyL = 0;
        zdobytePunktyP = 0;
        cin >> graczL >> rzut1L >> rzut2L >> rzut3L >> rzut4L >> graczP >> rzut1P >> rzut2P >> rzut3P >> rzut4P;
        // algorytm szukania par i liczenia wyniku
        // zerowanie zmiennych do petli
        zdobytePunkty = 0;
        t = 1;
        ileJednakowych = 0;
        bezPowtorzen = 0;
        // dla graczaL
        while (t < 5) {
            if (rzut1L == t) {
                ileJednakowych = ileJednakowych + 1;
            }
            if (rzut2L == t) {
                ileJednakowych = ileJednakowych + 1;
            }
            if (rzut3L == t) {
                ileJednakowych = ileJednakowych + 1;
            }
            if (rzut4L == t) {
                ileJednakowych = ileJednakowych + 1;
            }

            // obliczanie wyniku
            if (ileJednakowych == 1) {
                bezPowtorzen = bezPowtorzen + 1;
            } else if (ileJednakowych == 2) {
                if ((rzut1L == rzut2L && rzut3L == rzut4L) || (rzut1L == rzut3L && rzut2L == rzut4L) || (rzut1L == rzut4L && rzut2L == rzut3L)) {
                    // dla 2 roznych par
                    zdobytePunkty = 3;
                } else {
                    zdobytePunkty = 1;
                }
                t = 5;
            } else if (ileJednakowych == 3) {
                zdobytePunkty = 2;
                t = 5;
            } else if (ileJednakowych == 4) {
                zdobytePunkty = 5;
                t = 5;
            }
            if (bezPowtorzen == 4) {
                zdobytePunkty = 4;
            }
            // ustawia lepszy wynik
            if (zdobytePunkty > zdobytePunktyL) {
                zdobytePunktyL = zdobytePunkty;
            }

            t = t + 1;
            ileJednakowych = 0;
        }

        // dla graczaP
        zdobytePunkty = 0;
        t = 1;
        ileJednakowych = 0;
        bezPowtorzen = 0;
        while (t < 5) {
            if (rzut1P == t) {
                ileJednakowych = ileJednakowych + 1;
            }
            if (rzut2P == t) {
                ileJednakowych = ileJednakowych + 1;
            }
            if (rzut3P == t) {
                ileJednakowych = ileJednakowych + 1;
            }
            if (rzut4P == t) {
                ileJednakowych = ileJednakowych + 1;
            }

            // obliczanie wyniku
            if (ileJednakowych == 1) {
                bezPowtorzen = bezPowtorzen + 1;
            } else if (ileJednakowych == 2) {
                if ((rzut1P == rzut2P && rzut3P == rzut4P) || (rzut1P == rzut3P && rzut2P == rzut4P) || (rzut1P == rzut4P && rzut2P == rzut3P)) {
                    // dla 2 roznych par
                    zdobytePunkty = 3;
                } else {
                    zdobytePunkty = 1;
                }
                t = 5;
            } else if (ileJednakowych == 3) {
                zdobytePunkty = 2;
                t = 5;
            } else if (ileJednakowych == 4) {
                zdobytePunkty = 5;
                t = 5;
            }

            if (bezPowtorzen == 4) {
                zdobytePunkty = 4;
            }
            // ustawia lepszy wynik
            if (zdobytePunkty > zdobytePunktyP) {
                zdobytePunktyP = zdobytePunkty;
            }

            t = t + 1;
            ileJednakowych = 0;
        }
        // TO U GÓRY DZIALA ^
        maxL = 0;
        maxP = 0;
        if (zdobytePunktyL == zdobytePunktyP) {
            if (zdobytePunktyL == 3) {
                if (rzut1L == rzut2L) {
                    if (rzut1L > rzut3L) {
                        maxL = rzut1L;
                    } else {
                        maxL = rzut3L;
                    }
                } else {
                    if (rzut1L > rzut2L) {
                        maxL = rzut1L;
                    } else {
                        maxL = rzut2L;
                    }
                }
                // DLA MAXP
                if (rzut1P == rzut2P) {
                    if (rzut1P > rzut3P) {
                        maxP = rzut1P;
                    } else {
                        maxP = rzut3P;
                    }
                } else {
                    if (rzut1P > rzut2P) {
                        maxP = rzut1P;
                    } else {
                        maxP = rzut2P;
                    }
                }
            } else if (zdobytePunktyL == 4) {
                maxL = maxP;
            } else {
                if (zdobytePunktyL == 5) {
                    maxL = rzut1L;
                    maxP = rzut1P;
                } else if (zdobytePunktyL == 2) {
                    if (rzut1L == rzut2L) {
                        maxL = rzut1L;
                    } else if (rzut1L == rzut3L) {
                        maxL = rzut1L;
                    } else {
                        maxL = rzut2L;
                    }

                    if (rzut1P == rzut2P) {
                        maxP = rzut1P;
                    } else if (rzut1P == rzut3P) {
                        maxP = rzut1P;
                    } else {
                        maxP = rzut2P;
                    }
                } else {
                    if (rzut1L == rzut2L || rzut1L == rzut3L || rzut1L == rzut4L) {
                        maxL = rzut1L;
                    } else if (rzut2L == rzut3L || rzut2L == rzut4L) {
                        maxL = rzut2L;
                    } else {
                        maxL = rzut3L;
                    }

                    if (rzut1P == rzut2P || rzut1P == rzut3P || rzut1P == rzut4P) {
                        maxP = rzut1P;
                    } else if (rzut2P == rzut3P || rzut2P == rzut4P) {
                        maxP = rzut2P;
                    } else {
                        maxP = rzut3P;
                    }
                }
            }
        }
        // obliczanie kto wygral
        d = 0;
        while (d < 1) {

            if (zdobytePunktyL > zdobytePunktyP || maxL > maxP) {
                if (graczL == 'a') {
                    gralA = gralA + 1;
                    wygraneA = wygraneA + 1;
                } else if (graczL == 'b') {
                    gralB = gralB + 1;
                    wygraneB = wygraneB + 1;
                } else if (graczL == 'c') {
                    gralC = gralC + 1;
                    wygraneC = wygraneC + 1;
                } else if (graczL == 'd') {
                    gralD = gralD + 1;
                    wygraneD = wygraneD + 1;
                } else if (graczL == 'e') {
                    gralE = gralE + 1;
                    wygraneE = wygraneE + 1;
                }
                if (graczP == 'a') {
                    gralA = gralA + 1;
                    przegraneA = przegraneA + 1;
                } else if (graczP == 'b') {
                    gralB = gralB + 1;
                    przegraneB = przegraneB + 1;
                } else if (graczP == 'c') {
                    gralC = gralC + 1;
                    przegraneC = przegraneC + 1;
                } else if (graczP == 'd') {
                    gralD = gralD + 1;
                    przegraneD = przegraneD + 1;
                } else if (graczP == 'e') {
                    gralE = gralE + 1;
                    przegraneE = przegraneE + 1;
                }
            } else if (zdobytePunktyP > zdobytePunktyL || maxP > maxL) {
                if (graczP == 'a') {
                    gralA = gralA + 1;
                    wygraneA = wygraneA + 1;
                } else if (graczP == 'b') {
                    gralB = gralB + 1;
                    wygraneB = wygraneB + 1;
                } else if (graczP == 'c') {
                    gralC = gralC + 1;
                    wygraneC = wygraneC + 1;
                } else if (graczP == 'd') {
                    gralD = gralD + 1;
                    wygraneD = wygraneD + 1;
                } else if (graczP == 'e') {
                    gralE = gralE + 1;
                    wygraneE = wygraneE + 1;
                }
                if (graczL == 'a') {
                    gralA = gralA + 1;
                    przegraneA = przegraneA + 1;
                } else if (graczL == 'b') {
                    gralB = gralB + 1;
                    przegraneB = przegraneB + 1;
                } else if (graczL == 'c') {
                    gralC = gralC + 1;
                    przegraneC = przegraneC + 1;
                } else if (graczL == 'd') {
                    gralD = gralD + 1;
                    przegraneD = przegraneD + 1;
                } else if (graczL == 'e') {
                    gralE = gralE + 1;
                    przegraneE = przegraneE + 1;
                }
            } else if (maxL == maxP) {
                maxL = rzut1L + rzut2L + rzut3L + rzut4L;
                maxP = rzut1P + rzut2P + rzut3P + rzut4P;
                if (maxL == maxP) {
                    if (graczP == 'a') {
                        gralA = gralA + 1;
                        remisyA = remisyA + 1;
                    } else if (graczP == 'b') {
                        gralB = gralB + 1;
                        remisyB = remisyB + 1;
                    } else if (graczP == 'c') {
                        gralC = gralC + 1;
                        remisyC = remisyC + 1;
                    } else if (graczP == 'd') {
                        gralD = gralD + 1;
                        remisyD = remisyD + 1;
                    } else if (graczP == 'e') {
                        gralE = gralE + 1;
                        remisyE = remisyE + 1;
                    }
                    if (graczL == 'a') {
                        gralA = gralA + 1;
                        remisyA = remisyA + 1;
                    } else if (graczL == 'b') {
                        gralB = gralB + 1;
                        remisyB = remisyB + 1;
                    } else if (graczL == 'c') {
                        gralC = gralC + 1;
                        remisyC = remisyC + 1;
                    } else if (graczL == 'd') {
                        gralD = gralD + 1;
                        remisyD = remisyD + 1;
                    } else if (graczL == 'e') {
                        gralE = gralE + 1;
                        remisyE = remisyE + 1;
                    }
                } else if (maxL > maxP) {
                    d = d - 1;
                } else {
                    d = d - 1;
                }
            }
            d = d + 1;
        }
        i = i + 1;
    }

    // KONCOWE WYNIKI
    if (gralA > 0) {
        cout << "gracz a" << endl;
        if (wygraneA > 0) {
            cout << "wygrane: " << (100.0 * wygraneA) / gralA << "%" << endl;
        }
        if (remisyA > 0) {
            cout << "remisy: " << (100.0 * remisyA) / gralA << "%" << endl;
        }
        if (przegraneA > 0) {
            cout << "przegrane: " << (100.0 * przegraneA) / gralA << "%" << endl;
        }
        cout << endl;
    }
    if (gralB > 0) {
        cout << "gracz b" << endl;
        if (wygraneB > 0) {
            cout << "wygrane: " << (100.0 * wygraneB) / gralB << "%" << endl;
        }
        if (remisyB > 0) {
            cout << "remisy: " << (100.0 * remisyB) / gralB << "%" << endl;
        }
        if (przegraneB > 0) {
            cout << "przegrane: " << (100.0 * przegraneB) / gralB << "%" << endl;
        }
        cout << endl;
    }
    if (gralC > 0) {
        cout << "gracz c" << endl;
        if (wygraneC > 0) {
            cout << "wygrane: " << (100.0 * wygraneC) / gralC << "%" << endl;
        }
        if (remisyC > 0) {
            cout << "remisy: " << 100.0 * (remisyC / gralC) << "%" << endl;
        }
        if (przegraneC > 0) {
            cout << "przegrane: " << (100.0 * przegraneC) / gralC << "%" << endl;
        }
        cout << endl;
    }
    if (gralD > 0) {
        cout << "gracz d" << endl;
        if (wygraneD > 0) {
            cout << "wygrane: " << (100.0 * wygraneD) / gralD << "%" << endl;
        }
        if (remisyD > 0) {
            cout << "remisy: " << (100.0 * remisyD) / gralD << "%" << endl;
        }
        if (przegraneD > 0) {
            cout << "przegrane: " << (100.0 * przegraneD) / gralD << "%" << endl;
        }
        cout << endl;
    }
    if (gralE > 0) {
        cout << "gracz e" << endl;
        if (wygraneE > 0) {
            cout << "wygrane: " << (100.0 * wygraneE) / gralE << "%" << endl;
        }
        if (remisyE > 0) {
            cout << "remisy: " << (100.0 * remisyE) / gralE << "%" << endl;
        }
        if (przegraneE > 0) {
            cout << "przegrane: " << (100.0 * przegraneE) / gralE << "%" << endl;
        }
        cout << endl;
    }
    return 0;
}
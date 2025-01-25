// Filip Jarzyna
#include <iostream>
using namespace std;

void CheckDirection(int l, int v, int p, int length, int& dirH, int& dirW, int& dirD)
{
    dirH = 1;
    dirW = 1;
    dirD = 1;
    length /= 2;
    if (l > length) {
        dirH = -1;
    }
    if (v > length) {
        dirW = -1;
    }
    if (p > length) {
        dirD = -1;
    }
}

int main()
{
    int lengthCube;
    cin >> lengthCube;
    int dataCube[lengthCube][lengthCube][lengthCube];

    // dataCube[w][h][d]

    for (int i = 0; i < lengthCube; i++) {
        for (int k = 0; k < lengthCube; k++) {
            for (int t = 0; t < lengthCube; t++) {
                cin >> dataCube[t][k][i];
            }
        }
    }

    char op = 'x';

    while (op != 'E') {
        cin >> op;

        if (op == 'C') {
            int l;
            int v;
            int p;
            int h;
            int w;
            int d;
            cin >> l >> v >> p >> h >> w >> d;
            int dirL;
            int dirV;
            int dirP;
            int H;
            int W;
            int D;
            int sum = 0;

            CheckDirection(l, v, p, lengthCube, dirL, dirV, dirP);

            for (int i = 0; i <= h; i++) {
                for (int k = 0; k <= w; k++) {
                    for (int t = 0; t <= d; t++) {
                        H = l + (dirL * i);
                        W = v + (dirV * k);
                        D = p + (dirP * t);
                        // warunek ze bedzie w data cubie
                        if ((0 <= H && H < lengthCube) && (W >= 0 && W < lengthCube) && (D >= 0 && D < lengthCube)) {
                            // cout << "tablica[" << D << ']' << '[' << W << ']' << '[' << H << ']' << dataCube[W][H][D] << endl;
                            sum += dataCube[W][H][D];
                        }
                    }
                }
            }
            cout << sum << endl;

        } else if (op == 'T') {
            int l;
            int v;
            int p;
            int e;
            cin >> l >> v >> p >> e;
            int dirL;
            int dirV;
            int dirP;
            int sum = 0;
            int H;
            int W;
            int D;

            CheckDirection(l, v, p, lengthCube, dirL, dirV, dirP);

            for (int i = 0; i <= e; i++) {
                for (int k = 0; k <= e; k++) {
                    for (int t = 0; t <= e; t++) {
                        H = l + (dirL * i);
                        W = v + (dirV * k);
                        D = p + (dirP * t);
                        // warunek na czworoscian
                        if ((0 <= H && H < lengthCube) && (W >= 0 && W < lengthCube) && (D >= 0 && D < lengthCube) && (i + k + t <= e)) {
                            // cout << "tablica[" << D << ']' << '[' << W << ']' << '[' << H << ']' << dataCube[W][H][D] << endl;
                            sum += dataCube[W][H][D];
                        }
                    }
                }
            }

            cout << sum << endl;

        } else if (op == 'O') {
            int l;
            int v;
            int p;
            int r;
            cin >> l >> v >> p >> r;
            int dirL;
            int dirV;
            int dirP;
            int sum = 0;
            int H;
            int W;
            int D;

            CheckDirection(l, v, p, lengthCube, dirL, dirV, dirP);

            for (int i = 0; i <= r; i++) {
                for (int k = 0; k <= r; k++) {
                    for (int t = 0; t <= r; t++) {
                        H = l + (dirL * i);
                        W = v + (dirV * k);
                        D = p + (dirP * t);
                        // warunek na oktal chyba dziala
                        if ((0 <= H && H < lengthCube) && (W >= 0 && W < lengthCube) && (D >= 0 && D < lengthCube) && (i * i + k * k + t * t <= r * r)) {
                            // cout << "tablica[" << D << ']' << '[' << W << ']' << '[' << H << ']' << dataCube[W][H][D] << endl;
                            sum += dataCube[W][H][D];
                        }
                    }
                }
            }
            cout << sum << endl;
            // Octal(dataCube, lengthCube, l, v, p, r);
        } else if (op == 'D') {
            char k; // poziom pion lub panel (l v lub p)
            int i; // indeks tablicy danych
            cin >> k >> i;
            long long det = 1;
            long long matrix[lengthCube][lengthCube];

            if (k == 'l') {
                for (int j = 0; j < lengthCube; j++) {
                    for (int k = 0; k < lengthCube; k++) {
                        matrix[k][j] = dataCube[j][i][k];
                    }
                }
            } else if (k == 'v') {
                for (int j = 0; j < lengthCube; j++) {
                    for (int k = 0; k < lengthCube; k++) {
                        matrix[k][j] = dataCube[i][j][k];
                    }
                }
            } else if (k == 'p') {
                for (int j = 0; j < lengthCube; j++) {
                    for (int k = 0; k < lengthCube; k++) {
                        matrix[k][j] = dataCube[k][j][i];
                    }
                }
            }
            // bareis
            // wskaznik
            bool detIs0 = 0;
            if (lengthCube != 0) {
                for (int k = 0; k < lengthCube - 1; k++) {
                    // zamiana wierszy gdy zero sie trafi
                    if (matrix[k][k] == 0) {
                        int s;
                        for (s = k + 1; s < lengthCube; s++) {
                            if (matrix[s][k] != 0) {
                                for (int s1 = 0; s1 < lengthCube; s1++) {
                                    long long temp;
                                    temp = matrix[s][s1];
                                    matrix[s][s1] = matrix[k][s1];
                                    matrix[k][s1] = temp;
                                }
                                det *= -1; // gdy zamiana wierszy zmienia sie znak
                                break;
                            }
                        }
                        if (s == lengthCube) {
                            detIs0 = 1;
                        }
                    }
                    if (!detIs0) {
                        for (int t = k + 1; t < lengthCube; t++) {
                            for (int j = k + 1; j < lengthCube; j++) {

                                matrix[t][j] = matrix[t][j] * matrix[k][k] - matrix[t][k] * matrix[k][j];
                                if (k != 0) {
                                    matrix[t][j] /= matrix[k - 1][k - 1];
                                }
                            }
                        }
                    }
                }
            }
            if (!detIs0) {
                cout << det * matrix[lengthCube - 1][lengthCube - 1] << endl;
            } else {
                cout << 0 << endl;
            }
        }
    }
    return 0;
}
// Filip Jarzyna
#include <iostream>
using namespace std;

struct SLOT {
    unsigned short int amount;
    char label[2];
};

struct SHELF {
    unsigned char usedSlots;
    SLOT slots[128];
};

struct RACK {
    unsigned char usedShelves;
    SHELF shelves[128];
};

struct WAREHOUSE {
    unsigned char usedRacks;
    RACK racks[128];
    SHELF handyShelf;
};

struct DEPOT {
    unsigned char usedWare;
    WAREHOUSE warehouses[128];
    RACK handyRack;
    SHELF handyShelf;
};

unsigned long long int suma = 0;

DEPOT depot;

unsigned char SmallerOne(unsigned char a, unsigned char b)
{
    if (a > b)
        return b;
    else
        return a;
}

char CommandCase()
{
    char comCase = 0;
    char command[6];
    cin >> command;
    if (command[0] == 'S' && command[1] == 'E' && command[2] == 'T' && command[3] == '-') {
        if (command[4] == 'A') {
            if (command[5] == 'P') {
                comCase = 1;
            } else if (command[5] == 'S') {
                comCase = 2;
            } else if (command[5] == 'R') {
                comCase = 3;
            } else if (command[5] == 'W') {
                comCase = 4;
            }
        } else if (command[4] == 'H') {
            if (command[5] == 'W') {
                comCase = 5;
            } else if (command[5] == 'R') {
                comCase = 6;
            } else if (command[5] == 'S') {
                comCase = 7;
            }
        } else if (command[4] == 'L') {
            if (command[5] == 'W') {
                comCase = 29;
            } else if (command[5] == 'H') {
                comCase = 30;
            } else if (command[5] == 'R') {
                comCase = 31;
            } else if (command[5] == 'S') {
                comCase = 32;
            }
        }

    } else if (command[0] == 'P' && command[1] == 'U' && command[2] == 'T' && command[3] == '-') {
        if (command[4] == 'W') {
            comCase = 8;
        } else if (command[4] == 'H') {
            comCase = 9;
        } else if (command[4] == 'R') {
            comCase = 10;
        } else if (command[4] == 'S') {
            comCase = 11;
        }
    } else if (command[0] == 'F' && command[1] == 'I' && command[2] == 'L' && command[3] == 'L') {
        comCase = 12;
    } else if (command[0] == 'P' && command[1] == 'O' && command[2] == 'P' && command[3] == '-') {
        if (command[4] == 'W') {
            comCase = 13;
        } else if (command[4] == 'H') {
            comCase = 14;
        } else if (command[4] == 'R') {
            comCase = 15;
        } else if (command[4] == 'S') {
            comCase = 16;
        }
    } else if (command[0] == 'M' && command[1] == 'O' && command[2] == 'V' && command[3] == '-') {
        if (command[4] == 'W') {
            comCase = 17;
        } else if (command[4] == 'H') {
            comCase = 18;
        } else if (command[4] == 'R') {
            comCase = 19;
        } else if (command[4] == 'S') {
            comCase = 20;
        }
    } else if (command[0] == 'G' && command[1] == 'E' && command[2] == 'T' && command[3] == '-') {
        if (command[4] == 'E') {
            comCase = 21;
        } else if (command[4] == 'W') {
            comCase = 22;
        } else if (command[4] == 'R') {
            if (command[5] == 'W') {
                comCase = 23;
            } else if (command[5] == 'H') {
                comCase = 24;
            }
        } else if (command[4] == 'S') {
            if (command[5] == 'W') {
                comCase = 25;
            } else if (command[5] == 'H') {
                comCase = 26;
            } else if (command[5] == 'R') {
                comCase = 27;
            } else if (command[5] == 0) {
                comCase = 28;
            }

        } else if (command[4] == 'L') {
            if (command[5] == 'W') {
                comCase = 33;
            } else if (command[5] == 'H') {
                comCase = 34;
            } else if (command[5] == 'R') {
                comCase = 35;
            } else if (command[5] == 'S') {
                comCase = 36;
            }
        }
    } else if (command[0] == 'E' && command[1] == 'N' && command[2] == 'D') {
        comCase = 100;
    }

    return comCase;
}

void ErrorHandle(int max, bool& exit, int& temp)
{
    if (!exit) {
        if (!(temp >= 0 && temp <= max)) {
            exit = 1;
            temp = 0;
        }
    } else {
        temp = 0;
    }
}

void LabelCheck(char label[2], bool& exit)
{
    if (!exit) {
        if (label[0] >= '0' && label[1] >= '0' && label[0] <= '9' && label[1] <= '9') {
        } else {
            exit = 1;
        }
    }
}

void DisplayLabel(char label[2], bool& exit)
{
    if (!exit) {
        if (label[0] >= '0' && label[1] >= '0' && label[0] <= '9' && label[1] <= '9') {
            cout << label[0] << label[1] << endl;
        } else {
            if (label[0] == 0 && label[1] == 0) {
                cout << "--" << endl;
            } else {
                exit = 1;
            }
        }
    }
}

//  KOMENDY

void SetAP(unsigned short int w, unsigned short int r, unsigned short int s, unsigned short int P)
{

    unsigned char oldActiveSlots = depot.warehouses[w].racks[r].shelves[s].usedSlots;
    depot.warehouses[w].racks[r].shelves[s].usedSlots = P;
    for (unsigned char i = oldActiveSlots; i < P; i++) {
        depot.warehouses[w].racks[r].shelves[s].slots[i].amount = 0;
        depot.warehouses[w].racks[r].shelves[s].slots[i].label[0] = 0;
        depot.warehouses[w].racks[r].shelves[s].slots[i].label[1] = 0;
    }

    // usuwane
    if (oldActiveSlots > P) {
        for (int i = P; i < oldActiveSlots; i++) {
            suma -= depot.warehouses[w].racks[r].shelves[s].slots[i].amount;
        }
    }
}

void SetAS(unsigned short int w, unsigned short int r, unsigned short int S, unsigned short int P)
{

    unsigned char oldActiveShelves = depot.warehouses[w].racks[r].usedShelves;
    depot.warehouses[w].racks[r].usedShelves = S;

    // dla nowych
    for (int i = oldActiveShelves; i < S; i++) {
        depot.warehouses[w].racks[r].shelves[i].usedSlots = P;
        for (int k = 0; k < P; k++) {
            depot.warehouses[w].racks[r].shelves[i].slots[k].amount = 0;
            depot.warehouses[w].racks[r].shelves[i].slots[k].label[0] = 0;
            depot.warehouses[w].racks[r].shelves[i].slots[k].label[1] = 0;
        }
    }

    // dla starych
    unsigned char lim = SmallerOne(oldActiveShelves, S);
    for (int k = 0; k < lim; k++) {
        unsigned char oldActiveSlots = depot.warehouses[w].racks[r].shelves[k].usedSlots;
        depot.warehouses[w].racks[r].shelves[k].usedSlots = P;
        // nowe sloty, stare zostaja bez zmian wiec nie robim
        for (int i = oldActiveSlots; i < P; i++) {
            depot.warehouses[w].racks[r].shelves[k].slots[i].amount = 0;
            depot.warehouses[w].racks[r].shelves[k].slots[i].label[0] = 0;
            depot.warehouses[w].racks[r].shelves[k].slots[i].label[1] = 0;
        }
        // dla usuwanych
        if (oldActiveSlots > P) {
            for (int i = P; i < oldActiveSlots; i++) {
                suma -= depot.warehouses[w].racks[r].shelves[k].slots[i].amount;
            }
        }
    }

    // dla usuwanych shelves
    for (int is = S; is < oldActiveShelves; is++) {
        unsigned char c = depot.warehouses[w].racks[r].shelves[is].usedSlots;
        for (int ip = 0; ip < c; ip++) {
            suma -= depot.warehouses[w].racks[r].shelves[is].slots[ip].amount;
        }
    }
}

void SetAR(unsigned short int w, unsigned short int R, unsigned short int S, unsigned short int P)
{

    unsigned char oldActiveRacks = depot.warehouses[w].usedRacks;
    depot.warehouses[w].usedRacks = R;
    // dla nowych racks
    for (int ir = oldActiveRacks; ir < R; ir++) {
        depot.warehouses[w].racks[ir].usedShelves = S;
        for (int is = 0; is < S; is++) {
            depot.warehouses[w].racks[ir].shelves[is].usedSlots = P;
            for (int ip = 0; ip < P; ip++) {
                depot.warehouses[w].racks[ir].shelves[is].slots[ip].amount = 0;
                depot.warehouses[w].racks[ir].shelves[is].slots[ip].label[0] = 0;
                depot.warehouses[w].racks[ir].shelves[is].slots[ip].label[1] = 0;
            }
        }
    }
    // dla starych racks
    unsigned char limR = SmallerOne(oldActiveRacks, R);
    for (int ir = 0; ir < limR; ir++) {
        unsigned char oldActiveShelves = depot.warehouses[w].racks[ir].usedShelves;
        depot.warehouses[w].racks[ir].usedShelves = S;
        // nowych shelves
        for (int is = oldActiveShelves; is < S; is++) {
            unsigned char oldActiveSlots = depot.warehouses[w].racks[ir].shelves[is].usedSlots;
            depot.warehouses[w].racks[ir].shelves[is].usedSlots = P;
            for (int ip = oldActiveSlots; ip < P; ip++) {
                depot.warehouses[w].racks[ir].shelves[is].slots[ip].amount = 0;
                depot.warehouses[w].racks[ir].shelves[is].slots[ip].label[0] = 0;
                depot.warehouses[w].racks[ir].shelves[is].slots[ip].label[1] = 0;
            }
        }
        // starych shelves
        unsigned char limS = SmallerOne(oldActiveShelves, S);
        for (int is = 0; is < limS; is++) {
            unsigned char oldActiveSlots = depot.warehouses[w].racks[ir].shelves[is].usedSlots;
            depot.warehouses[w].racks[ir].shelves[is].usedSlots = P;
            for (int ip = oldActiveSlots; ip < P; ip++) {
                depot.warehouses[w].racks[ir].shelves[is].slots[ip].amount = 0;
                depot.warehouses[w].racks[ir].shelves[is].slots[ip].label[0] = 0;
                depot.warehouses[w].racks[ir].shelves[is].slots[ip].label[1] = 0;
            }
        }
        // dla usuwanych shelves
        for (int is = S; is < oldActiveShelves; is++) {
            unsigned short int c = depot.warehouses[w].racks[ir].shelves[is].usedSlots;
            for (int ip = 0; ip < c; ip++) {
                suma -= depot.warehouses[w].racks[ir].shelves[is].slots[ip].amount;
            }
        }
    }

    // dla usuwanych racks
    for (int ir = R; ir < oldActiveRacks; ir++) {
        unsigned short int c = depot.warehouses[w].racks[ir].usedShelves;
        for (int is = 0; is < c; is++) {
            unsigned short int c1 = depot.warehouses[w].racks[ir].shelves[is].usedSlots;
            for (int ip = 0; ip < c1; ip++) {
                suma -= depot.warehouses[w].racks[is].shelves[is].slots[ip].amount;
            }
        }
    }
}

void SetAW(unsigned short int W, unsigned short int R, unsigned short int S, unsigned short int P)
{

    unsigned char oldActiveWare = depot.usedWare;
    depot.usedWare = W;

    // dla nowych warehouses
    for (int l = oldActiveWare; l < W; l++) {
        unsigned char oldActiveRacks = depot.warehouses[l].usedRacks;
        depot.warehouses[l].usedRacks = R;
        // dla nowych racks
        for (int i = oldActiveRacks; i < R; i++) {
            depot.warehouses[l].racks[i].usedShelves = S;
            for (int t = 0; t < S; t++) {
                depot.warehouses[l].racks[i].shelves[t].usedSlots = P;
                for (int k = 0; k < P; k++) {
                    depot.warehouses[l].racks[i].shelves[t].slots[k].amount = 0;
                    depot.warehouses[l].racks[i].shelves[t].slots[k].label[0] = 0;
                    depot.warehouses[l].racks[i].shelves[t].slots[k].label[1] = 0;
                }
            }
        }
        // handyShelf
        for (int k = 0; k < P; k++) {
            depot.warehouses[l].handyShelf.slots[k].amount = 0;
            depot.warehouses[l].handyShelf.slots[k].label[0] = 0;
            depot.warehouses[l].handyShelf.slots[k].label[1] = 0;
        }
    }

    unsigned short int limW = SmallerOne(oldActiveWare, W);
    for (int l = 0; l < limW; l++) {
        SetAR(l, R, S, P);
    }

    for (int iw = W; iw < oldActiveWare; iw++) {
        unsigned short int c1 = depot.warehouses[iw].usedRacks;
        for (int ir = 0; ir < c1; ir++) {
            unsigned short int c2 = depot.warehouses[iw].racks[ir].usedShelves;
            for (int is = 0; is < c2; is++) {
                unsigned short int c3 = depot.warehouses[iw].racks[ir].shelves[is].usedSlots;
                for (int ip = 0; ip < c3; ip++) {
                    suma -= depot.warehouses[iw].racks[ir].shelves[is].slots[ip].amount;
                }
            }
        }
    }

    /*
    // dla starych racks
    // unsigned char limR = SmallerOne(oldActiveRacks, R);
    if (oldActiveRacks < R) {
        for (int ir = 0; ir < oldActiveRacks; ir++) {
            unsigned char oldActiveShelves = depot.warehouses[l].racks[ir].usedShelves;
            depot.warehouses[l].racks[ir].usedShelves = S;
            // nowych shelves
            for (int k = oldActiveShelves; k < S; k++) {
                unsigned short int oldActiveSlots = depot.warehouses[l].racks[ir].shelves[k].usedSlots;
                depot.warehouses[l].racks[ir].shelves[k].usedSlots = P;
                for (int t = oldActiveSlots; t < P; t++) {
                    depot.warehouses[l].racks[ir].shelves[k].slots[t].amount = 0;
                    depot.warehouses[l].racks[ir].shelves[k].slots[t].label[0] = 0;
                    depot.warehouses[l].racks[ir].shelves[k].slots[t].label[1] = 0;
                }
            }
            // starych shelves
            // unsigned char limS = SmallerOne(oldActiveShelves, S);
            if (oldActiveShelves < S) {
                for (int k = 0; k < oldActiveShelves; k++) {
                    unsigned short int oldActiveSlots = depot.warehouses[l].racks[ir].shelves[k].usedSlots;
                    depot.warehouses[l].racks[ir].shelves[k].usedSlots = P;
                    for (int i = oldActiveSlots; i < P; i++) {
                        depot.warehouses[l].racks[ir].shelves[k].slots[i].amount = 0;
                        depot.warehouses[l].racks[ir].shelves[k].slots[i].label[0] = 0;
                        depot.warehouses[l].racks[ir].shelves[k].slots[i].label[1] = 0;
                    }
                }
            } else {
                for (int k = 0; k < S; k++) {
                    unsigned short int oldActiveSlots = depot.warehouses[l].racks[ir].shelves[k].usedSlots;
                    depot.warehouses[l].racks[ir].shelves[k].usedSlots = P;
                    for (int i = oldActiveSlots; i < P; i++) {
                        depot.warehouses[l].racks[ir].shelves[k].slots[i].amount = 0;
                        depot.warehouses[l].racks[ir].shelves[k].slots[i].label[0] = 0;
                        depot.warehouses[l].racks[ir].shelves[k].slots[i].label[1] = 0;
                    }
                }
            }
        }
    } else {
        for (int ir = 0; ir < R; ir++) {
            unsigned char oldActiveShelves = depot.warehouses[l].racks[ir].usedShelves;
            depot.warehouses[l].racks[ir].usedShelves = S;
            // nowych shelves
            for (int k = oldActiveShelves; k < S; k++) {
                unsigned short int oldActiveSlots = depot.warehouses[l].racks[ir].shelves[k].usedSlots;
                depot.warehouses[l].racks[ir].shelves[k].usedSlots = P;
                for (int t = oldActiveSlots; t < P; t++) {
                    depot.warehouses[l].racks[ir].shelves[k].slots[t].amount = 0;
                    depot.warehouses[l].racks[ir].shelves[k].slots[t].label[0] = 0;
                    depot.warehouses[l].racks[ir].shelves[k].slots[t].label[1] = 0;
                }
            }
            // starych shelves
            // unsigned char limS = SmallerOne(oldActiveShelves, S);
            if (oldActiveShelves < S) {
                for (int k = 0; k < oldActiveShelves; k++) {
                    unsigned short int oldActiveSlots = depot.warehouses[l].racks[ir].shelves[k].usedSlots;
                    depot.warehouses[l].racks[ir].shelves[k].usedSlots = P;
                    for (int i = oldActiveSlots; i < P; i++) {
                        depot.warehouses[l].racks[ir].shelves[k].slots[i].amount = 0;
                        depot.warehouses[l].racks[ir].shelves[k].slots[i].label[0] = 0;
                        depot.warehouses[l].racks[ir].shelves[k].slots[i].label[1] = 0;
                    }
                }
            } else {
                for (int k = 0; k < S; k++) {
                    unsigned short int oldActiveSlots = depot.warehouses[l].racks[ir].shelves[k].usedSlots;
                    depot.warehouses[l].racks[ir].shelves[k].usedSlots = P;
                    for (int i = oldActiveSlots; i < P; i++) {
                        depot.warehouses[l].racks[ir].shelves[k].slots[i].amount = 0;
                        depot.warehouses[l].racks[ir].shelves[k].slots[i].label[0] = 0;
                        depot.warehouses[l].racks[ir].shelves[k].slots[i].label[1] = 0;
                    }
                }
            }
        }
    }
}
// dla starych warehouses
unsigned char limW = SmallerOne(oldActiveWare, W);
for (int l = 0; l < limW; l++) {
    unsigned char oldActiveRacks = depot.warehouses[l].usedRacks;
    depot.warehouses[l].usedRacks = R;
    // dla nowych racks
    for (int i = oldActiveRacks; i < R; i++) {
        depot.warehouses[l].racks[i].usedShelves = S;
        for (int t = 0; t < S; t++) {
            depot.warehouses[l].racks[i].shelves[t].usedSlots = P;
            for (int k = 0; k < P; k++) {
                depot.warehouses[l].racks[i].shelves[t].slots[k].amount = 0;
                depot.warehouses[l].racks[i].shelves[t].slots[k].label[0] = 0;
                depot.warehouses[l].racks[i].shelves[t].slots[k].label[1] = 0;
            }
        }
    }
    // dla starych racks
    unsigned char limR = SmallerOne(oldActiveRacks, R);
    for (int ir = 0; ir < limR; ir++) {
        unsigned char oldActiveShelves = depot.warehouses[l].racks[ir].usedShelves;
        depot.warehouses[l].racks[ir].usedShelves = S;
        // nowych shelves
        for (int k = oldActiveShelves; k < S; k++) {
            unsigned char oldActiveSlots = depot.warehouses[l].racks[ir].shelves[k].usedSlots;
            depot.warehouses[l].racks[ir].shelves[k].usedSlots = P;
            for (int t = oldActiveSlots; t < P; t++) {
                depot.warehouses[l].racks[ir].shelves[k].slots[t].amount = 0;
                depot.warehouses[l].racks[ir].shelves[k].slots[t].label[0] = 0;
                depot.warehouses[l].racks[ir].shelves[k].slots[t].label[1] = 0;
            }
        }
        // starych shelves
        unsigned char limS = SmallerOne(oldActiveShelves, S);
        for (int k = 0; k < limS; k++) {
            unsigned char oldActiveSlots = depot.warehouses[l].racks[ir].shelves[k].usedSlots;
            depot.warehouses[l].racks[ir].shelves[k].usedSlots = P;
            for (int i = oldActiveSlots; i < P; i++) {
                depot.warehouses[l].racks[ir].shelves[k].slots[i].amount = 0;
                depot.warehouses[l].racks[ir].shelves[k].slots[i].label[0] = 0;
                depot.warehouses[l].racks[ir].shelves[k].slots[i].label[1] = 0;
            }
        }
        // dla usuwanych shelves
        for (int is = S; is < oldActiveShelves; is++) {
            unsigned short int c = depot.warehouses[l].racks[ir].shelves[is].usedSlots;
            for (int ip = 0; ip < c; ip++) {
                suma -= depot.warehouses[l].racks[ir].shelves[is].slots[ip].amount;
            }
        }
    }
    // usuwane handyshelf
    unsigned char oldActiveHandySlots = depot.warehouses[l].handyShelf.usedSlots;
    for (int u = P; u < oldActiveHandySlots; u++) {
        suma -= depot.warehouses[l].handyShelf.slots[u].amount;
    }

    // dla usuwanych racks
    for (int ir = R; ir < oldActiveRacks; ir++) {
        unsigned short int c = depot.warehouses[l].racks[ir].usedShelves;
        for (int is = 0; is < c; is++) {
            for (int ip = 0; depot.warehouses[l].racks[ir].shelves[is].usedSlots; ip++) {
                suma -= depot.warehouses[l].racks[is].shelves[is].slots[ip].amount;
            }
        }
    }
}

// dla usuwanych warehouses

for (int iw = W; iw < oldActiveWare; iw++) {
    unsigned short int c1 = depot.warehouses[iw].usedRacks;
    for (int ir = 0; ir < c1; ir++) {
        unsigned short int c2 = depot.warehouses[iw].racks[ir].usedShelves;
        for (int is = 0; is < c2; is++) {
            unsigned short int c3 = depot.warehouses[iw].racks[ir].shelves[is].usedSlots;
            for (int ip = 0; ip < c3; ip++) {
                suma -= depot.warehouses[iw].racks[ir].shelves[is].slots[ip].amount;
            }
        }
    }
}
*/
}

void SetHW(unsigned short int w, unsigned short int P)
{

    unsigned char oldActiveSlots = depot.warehouses[w].handyShelf.usedSlots;
    depot.warehouses[w].handyShelf.usedSlots = P;
    // dla nowych miejsc
    for (int i = oldActiveSlots; i < P; i++) {
        depot.warehouses[w].handyShelf.slots[i].amount = 0;
        depot.warehouses[w].handyShelf.slots[i].label[0] = 0;
        depot.warehouses[w].handyShelf.slots[i].label[1] = 0;
    }

    // dla usuwanych
    for (int i = P; i < oldActiveSlots; i++) {
        suma -= depot.warehouses[w].handyShelf.slots[i].amount;
    }
}

void SetHR(unsigned short int S, unsigned short int P)
{

    unsigned char oldActiveShelves = depot.handyRack.usedShelves;
    depot.handyRack.usedShelves = S;
    // dla nowych shelves
    for (int k = oldActiveShelves; k < S; k++) {
        depot.handyRack.shelves[k].usedSlots = P;
        for (int i = 0; i < P; i++) {
            depot.handyRack.shelves[k].slots[i].amount = 0;
            depot.handyRack.shelves[k].slots[i].label[0] = 0;
            depot.handyRack.shelves[k].slots[i].label[1] = 0;
        }
    }

    // dla starych shelves
    unsigned char limS = SmallerOne(oldActiveShelves, S);
    for (int k = 0; k < limS; k++) {
        unsigned char oldActiveSlots = depot.handyRack.shelves[k].usedSlots;
        depot.handyRack.shelves[k].usedSlots = P;
        for (int i = oldActiveSlots; i < P; i++) {
            depot.handyRack.shelves[k].slots[i].amount = 0;
            depot.handyRack.shelves[k].slots[i].label[0] = 0;
            depot.handyRack.shelves[k].slots[i].label[1] = 0;
        }

        for (int i = P; i < oldActiveSlots; i++) {
            suma -= depot.handyRack.shelves[k].slots[i].amount;
        }
    }
    // dla usuwanych shelves
    for (int k = S; k < oldActiveShelves; k++) {
        unsigned short int c = depot.handyRack.shelves[k].usedSlots;
        for (int i = 0; i < c; i++) {
            suma -= depot.handyRack.shelves[k].slots[i].amount;
        }
    }
}

void SetHS(unsigned short int P)
{

    unsigned char oldActiveSlots = depot.handyShelf.usedSlots;
    depot.handyShelf.usedSlots = P;

    for (int i = oldActiveSlots; i < P; i++) {
        depot.handyShelf.slots[i].amount = 0;
        depot.handyShelf.slots[i].label[0] = 0;
        depot.handyShelf.slots[i].label[1] = 0;
    }

    // dla usuwanych slotow

    for (int i = P; i < oldActiveSlots; i++) {
        suma -= depot.handyShelf.slots[i].amount;
    }
}

void PutW(unsigned short int w, unsigned short int r, unsigned short int s, unsigned short int p, unsigned int A)
{

    if (depot.warehouses[w].racks[r].shelves[s].slots[p].amount <= 65535 - A) {
        depot.warehouses[w].racks[r].shelves[s].slots[p].amount += A;
        suma += A;
    } else {
        suma += 65535;
        suma -= depot.warehouses[w].racks[r].shelves[s].slots[p].amount;
        depot.warehouses[w].racks[r].shelves[s].slots[p].amount = 65535;
    }
}

void PutH(unsigned short int w, unsigned short int p, unsigned int A)
{

    if (depot.warehouses[w].handyShelf.slots[p].amount <= 65535 - A) {
        depot.warehouses[w].handyShelf.slots[p].amount += A;
        suma += A;
    } else {
        suma += 65535;
        suma -= depot.warehouses[w].handyShelf.slots[p].amount;
        depot.warehouses[w].handyShelf.slots[p].amount = 65535;
    }
}

void PutR(unsigned short int s, unsigned short int p, unsigned int A)
{

    if (depot.handyRack.shelves[s].slots[p].amount <= 65535 - A) {
        depot.handyRack.shelves[s].slots[p].amount += A;
        suma += A;
    } else {
        suma += 65535;
        suma -= depot.handyRack.shelves[s].slots[p].amount;
        depot.handyRack.shelves[s].slots[p].amount = 65535;
    }
}

void PutS(unsigned short int p, unsigned int A)
{

    if (depot.handyShelf.slots[p].amount <= 65535 - A) {
        depot.handyShelf.slots[p].amount += A;
        suma += A;
    } else {
        suma += 65535;
        suma -= depot.handyShelf.slots[p].amount;
        depot.handyShelf.slots[p].amount = 65535;
    }
}

void Fill(unsigned short int W, unsigned short int R, unsigned short int S, unsigned short int P, unsigned short int A)
{

    depot.usedWare = W;
    // handy shelf depot
    depot.handyShelf.usedSlots = P;
    for (int i = 0; i < P; i++) {
        depot.handyShelf.slots[i].amount = A;
        depot.handyShelf.slots[i].label[0] = 0;
        depot.handyShelf.slots[i].label[1] = 0;
    }

    // handy rack depot
    depot.handyRack.usedShelves = S;
    for (int i = 0; i < S; i++) {
        depot.handyRack.shelves[i].usedSlots = P;
        for (int k = 0; k < P; k++) {
            depot.handyRack.shelves[i].slots[k].amount = A;
            depot.handyRack.shelves[i].slots[k].label[0] = 0;
            depot.handyRack.shelves[i].slots[k].label[1] = 0;
        }
    }

    // all warehouses
    for (int iw = 0; iw < W; iw++) {

        // handy shelf
        depot.warehouses[iw].handyShelf.usedSlots = P;
        for (int i = 0; i < P; i++) {
            depot.warehouses[iw].handyShelf.slots[i].amount = A;
            depot.warehouses[iw].handyShelf.slots[i].label[0] = 0;
            depot.warehouses[iw].handyShelf.slots[i].label[1] = 0;
        }
        // racks
        depot.warehouses[iw].usedRacks = R;
        for (int ir = 0; ir < R; ir++) {
            depot.warehouses[iw].racks[ir].usedShelves = S;
            for (int is = 0; is < S; is++) {
                depot.warehouses[iw].racks[ir].shelves[is].usedSlots = P;
                for (int ip = 0; ip < P; ip++) {
                    depot.warehouses[iw].racks[ir].shelves[is].slots[ip].amount = A;
                    depot.warehouses[iw].racks[ir].shelves[is].slots[ip].label[0] = 0;
                    depot.warehouses[iw].racks[ir].shelves[is].slots[ip].label[1] = 0;
                }
            }
        }
    }

    suma = W;
    suma *= R;
    suma *= S;
    suma *= P;
    suma += W * P;
    suma += P + (S * P);
    suma *= A;

    // suma = (((W * R) * (S * P)) + (W * P) + S + (S * P)) * A;
}

void PopW(unsigned short int w, unsigned short int r, unsigned short int s, unsigned short int p, unsigned int A)
{
    if (depot.warehouses[w].racks[r].shelves[s].slots[p].amount <= A) {
        suma -= depot.warehouses[w].racks[r].shelves[s].slots[p].amount;
        depot.warehouses[w].racks[r].shelves[s].slots[p].amount = 0;
    } else {
        depot.warehouses[w].racks[r].shelves[s].slots[p].amount -= A;
        suma -= A;
    }
}

void PopH(unsigned short int w, unsigned short int p, unsigned int A)
{

    if (depot.warehouses[w].handyShelf.slots[p].amount <= A) {
        suma -= depot.warehouses[w].handyShelf.slots[p].amount;
        depot.warehouses[w].handyShelf.slots[p].amount = 0;
    } else {
        depot.warehouses[w].handyShelf.slots[p].amount -= A;
        suma -= A;
    }
}

void PopR(unsigned short int s, unsigned short int p, unsigned int A)
{

    if (depot.handyRack.shelves[s].slots[p].amount <= A) {
        suma -= depot.handyRack.shelves[s].slots[p].amount;
        depot.handyRack.shelves[s].slots[p].amount = 0;
    } else {
        depot.handyRack.shelves[s].slots[p].amount -= A;
        suma -= A;
    }
}

void PopS(unsigned short int p, unsigned int A)
{

    if (depot.handyShelf.slots[p].amount <= A) {
        suma -= depot.handyShelf.slots[p].amount;
        depot.handyShelf.slots[p].amount = 0;
    } else {
        depot.handyShelf.slots[p].amount -= A;
        suma -= A;
    }
}

void MovW(unsigned short int w1, unsigned short int r1, unsigned short int s1, unsigned short int w2, unsigned short int r2, unsigned short int s2, unsigned short int p, unsigned int A)
{

    // depot.warehouses[w1].racks[r1].slots[s1].slots[p] --> depot.warehouses[w2].racks[r2].slots[r2].slots[p]
    if (A > 65535) {
        A = 65535;
    }

    if (A > depot.warehouses[w1].racks[r1].shelves[s1].slots[p].amount) {
        A = depot.warehouses[w1].racks[r1].shelves[s1].slots[p].amount;
    }

    if (depot.warehouses[w2].racks[r2].shelves[s2].slots[p].amount > 65535 - A) {
        A = 65535 - depot.warehouses[w2].racks[r2].shelves[s2].slots[p].amount;
    }
    depot.warehouses[w2].racks[r2].shelves[s2].slots[p].amount += A;
    depot.warehouses[w1].racks[r1].shelves[s1].slots[p].amount -= A;
}

void MovH(unsigned short int w, unsigned short int r, unsigned short int s, unsigned short int p, unsigned int A)
{

    // depot.warehouses[w].racks[r].shelves[s].slots[p] --> depot.warehouses[w].handyShelf.slots[p]
    if (A > 65535) {
        A = 65535;
    }

    if (A > depot.warehouses[w].racks[r].shelves[s].slots[p].amount) {
        A = depot.warehouses[w].racks[r].shelves[s].slots[p].amount;
    }

    if (depot.warehouses[w].handyShelf.slots[p].amount > 65535 - A) {
        A = 65535 - depot.warehouses[w].handyShelf.slots[p].amount;
    }
    depot.warehouses[w].handyShelf.slots[p].amount += A;
    depot.warehouses[w].racks[r].shelves[s].slots[p].amount -= A;
}

void MovR(unsigned short int w, unsigned short int r, unsigned short int s1, unsigned short int s2, unsigned short int p, unsigned int A)
{

    // depot.warehouses[w].racks[r].shelves[s1].slots[p] --> depot.handyRack.shelves[s2].slots[p]

    if (A > 65535) {
        A = 65535;
    }

    if (A > depot.warehouses[w].racks[r].shelves[s1].slots[p].amount) {
        A = depot.warehouses[w].racks[r].shelves[s1].slots[p].amount;
    }

    if (depot.handyRack.shelves[s2].slots[p].amount > 65535 - A) {
        A = 65535 - depot.handyRack.shelves[s2].slots[p].amount;
    }
    depot.warehouses[w].racks[r].shelves[s1].slots[p].amount -= A;
    depot.handyRack.shelves[s2].slots[p].amount += A;
}

void MovS(unsigned short int s, unsigned short int p, unsigned int A)
{
    // depot.handyRack.shelves[s].slots[p] --> depot.handyShelf.slots[p]

    if (A > 65535) {
        A = 65535;
    }

    if (A > depot.handyRack.shelves[s].slots[p].amount) {
        A = depot.handyRack.shelves[s].slots[p].amount;
    }

    if (depot.handyShelf.slots[p].amount > 65535 - A) {
        A = 65535 - depot.handyShelf.slots[p].amount;
    }
    depot.handyShelf.slots[p].amount += A;
    depot.handyRack.shelves[s].slots[p].amount -= A;
}

void GetE()
{
    /*
    unsigned long long int sum = 0;
    // sumuje z handy rack depot
    for (int is = 0; is < depot.handyRack.usedShelves; is++) {
        for (int ip = 0; ip < depot.handyRack.shelves[is].usedSlots; ip++) {
            sum += depot.handyRack.shelves[is].slots[ip].amount;
        }
    }
    // sum handy shelf depot
    for (int ip = 0; ip < depot.handyShelf.usedSlots; ip++) {
        sum += depot.handyShelf.slots[ip].amount;
    }

    // sum warehouses
    for (unsigned short int iw = 0; iw < depot.usedWare; iw++) {
        // handy shelf
        for (unsigned short int ip = 0; ip < depot.warehouses[iw].handyShelf.usedSlots; ip++) {
            sum += depot.warehouses[iw].handyShelf.slots[ip].amount;
        }
        // racks
        for (unsigned short int ir = 0; ir < depot.warehouses[iw].usedRacks; ir++) {
            for (unsigned short int is = 0; is < depot.warehouses[iw].racks[ir].usedShelves; is++) {
                for (unsigned short int ip = 0; ip < depot.warehouses[iw].racks[ir].shelves[is].usedSlots; ip++) {
                    sum += depot.warehouses[iw].racks[ir].shelves[is].slots[ip].amount;
                }
            }
        }
    }
    */
    cout << suma << endl;
}

void GetW(unsigned short int w)
{
    unsigned long long int sum = 0;

    for (int is = 0; is < depot.warehouses[w].handyShelf.usedSlots; is++) {
        sum += depot.warehouses[w].handyShelf.slots[is].amount;
    }
    for (int ir = 0; ir < depot.warehouses[w].usedRacks; ir++) {
        for (int is = 0; is < depot.warehouses[w].racks[ir].usedShelves; is++) {
            for (int ip = 0; ip < depot.warehouses[w].racks[ir].shelves[is].usedSlots; ip++) {
                sum += depot.warehouses[w].racks[ir].shelves[is].slots[ip].amount;
            }
        }
    }
    cout << sum << endl;
}

void GetRW(unsigned short int w, unsigned short int r)
{
    unsigned long long int sum = 0;

    for (int is = 0; is < depot.warehouses[w].racks[r].usedShelves; is++) {
        for (int ip = 0; ip < depot.warehouses[w].racks[r].shelves[is].usedSlots; ip++) {
            sum += depot.warehouses[w].racks[r].shelves[is].slots[ip].amount;
        }
    }
    cout << sum << endl;
}

void GetRH()
{
    unsigned long long int sum = 0;

    for (int is = 0; is < depot.handyRack.usedShelves; is++) {
        for (int ip = 0; ip < depot.handyRack.shelves[is].usedSlots; ip++) {
            sum += depot.handyRack.shelves[is].slots[ip].amount;
        }
    }
    cout << sum << endl;
}

void GetSW(unsigned short int w, unsigned short int r, unsigned short int s)
{
    unsigned long long int sum = 0;

    for (int ip = 0; ip < depot.warehouses[w].racks[r].shelves[s].usedSlots; ip++) {
        sum += depot.warehouses[w].racks[r].shelves[s].slots[ip].amount;
    }
    cout << sum << endl;
}

void GetSH(unsigned short int w)
{

    unsigned long long int sum = 0;

    for (int ip = 0; ip < depot.warehouses[w].handyShelf.usedSlots; ip++) {
        sum += depot.warehouses[w].handyShelf.slots[ip].amount;
    }
    cout << sum << endl;
}

void GetSR(unsigned short int s)
{
    unsigned long long int sum = 0;

    for (int ip = 0; ip < depot.handyRack.shelves[s].usedSlots; ip++) {
        sum += depot.handyRack.shelves[s].slots[ip].amount;
    }
    cout << sum << endl;
}

void GetS()
{
    unsigned long long int sum = 0;
    for (int ip = 0; ip < depot.handyShelf.usedSlots; ip++) {
        sum += depot.handyShelf.slots[ip].amount;
    }
    cout << sum << endl;
}

/*
comCase
0       END
1       SET-AP
2       SET-AS
3       SET-AR
4       SET-AW
5       SET-HW
6       SET-HR
7       SET-HS
8       PUT-W
9       PUT-H
10      PUT-R
11      PUT-S
12      FILL
13      POP-W
14      POP-H
15      POP-R
16      POP-S
17      MOV-W
18      MOV-H
19      MOV-R
20      MOV-S
21      GET-E
22      GET-W
23      GET-RW
24      GET-RH
25      GET-SW
26      GET-SH
27      GET-SR
28      GET-S
29      SET-LW
30      SET-LH
31      SET-LR
32      SET-LS
33      GET-LW
34      GET-LH
35      GET-LR
36      GET-LS
*/
int main()
{

    // na wszelki wszystko
    depot.usedWare = 0;
    depot.handyRack.usedShelves = 0;
    depot.handyShelf.usedSlots = 0;
    for (unsigned char w = 0; w < 128; w++) {
        depot.warehouses[w].handyShelf.usedSlots = 0;
        depot.warehouses[w].usedRacks = 0;
        for (unsigned char r = 0; r < 128; r++) {
            depot.warehouses[w].racks[r].usedShelves = 0;
            for (unsigned char s = 0; s < 128; s++) {
                depot.warehouses[w].racks[r].shelves[s].usedSlots = 0;
            }
        }
    }
    char command = 0;
    while (command != 100) {
        bool exit = 0;
        command = CommandCase();
        int a, b, c, d, e, f;
        char dd[2];
        switch (command) {
        case 1:
            cin >> a >> b >> c >> d;
            ErrorHandle(depot.usedWare - 1, exit, a);
            ErrorHandle(depot.warehouses[a].usedRacks - 1, exit, b);
            ErrorHandle(depot.warehouses[a].racks[b].usedShelves - 1, exit, c);
            ErrorHandle(128, exit, d);
            if (!exit)
                SetAP(a, b, c, d);
            break;
        case 2:
            cin >> a >> b >> c >> d;

            ErrorHandle(depot.usedWare - 1, exit, a);
            ErrorHandle(depot.warehouses[a].usedRacks - 1, exit, b);
            ErrorHandle(128, exit, c);
            ErrorHandle(128, exit, d);
            if (!exit)
                SetAS(a, b, c, d);
            break;
        case 3:
            cin >> a >> b >> c >> d;

            ErrorHandle(depot.usedWare - 1, exit, a);
            ErrorHandle(128, exit, b);
            ErrorHandle(128, exit, c);
            ErrorHandle(128, exit, d);
            if (!exit)
                SetAR(a, b, c, d);
            break;
        case 4:
            cin >> a >> b >> c >> d;

            if (0 <= a && a < 129 && b >= 0 && b < 129 && c >= 0 && c < 129 && d >= 0 && d < 129) {
                SetAW(a, b, c, d);
            } else {
                cout << "error" << endl;
            }
            break;
        case 5:
            cin >> a >> b;

            ErrorHandle(depot.usedWare - 1, exit, a);
            ErrorHandle(128, exit, b);
            if (!exit)
                SetHW(a, b);
            break;
        case 6:
            cin >> a >> b;

            ErrorHandle(128, exit, a);
            ErrorHandle(128, exit, b);
            if (!exit)
                SetHR(a, b);
            break;
        case 7:
            cin >> a;

            ErrorHandle(128, exit, a);
            if (!exit)
                SetHS(a);
            break;
        case 8:
            cin >> a >> b >> c >> d >> e;

            ErrorHandle(depot.usedWare - 1, exit, a);
            ErrorHandle(depot.warehouses[a].usedRacks - 1, exit, b);
            ErrorHandle(depot.warehouses[a].racks[b].usedShelves - 1, exit, c);
            ErrorHandle(depot.warehouses[a].racks[b].shelves[c].usedSlots - 1, exit, d);
            if (e < 0)
                exit = 1;

            if (!exit)
                PutW(a, b, c, d, e);
            break;
        case 9:
            cin >> a >> b >> c;

            ErrorHandle(depot.usedWare - 1, exit, a);
            ErrorHandle(depot.warehouses[a].handyShelf.usedSlots - 1, exit, b);
            if (c < 0)
                exit = 1;
            if (!exit)
                PutH(a, b, c);
            break;
        case 10:
            cin >> a >> b >> c;

            ErrorHandle(depot.handyRack.usedShelves - 1, exit, a);
            ErrorHandle(depot.handyRack.shelves[a].usedSlots - 1, exit, b);
            if (c < 0)
                exit = 1;
            if (!exit)
                PutR(a, b, c);
            break;
        case 11:
            cin >> a >> b;

            ErrorHandle(depot.handyShelf.usedSlots - 1, exit, a);
            if (b < 0)
                exit = 1;
            if (!exit)
                PutS(a, b);
            break;
        case 12:
            cin >> a >> b >> c >> d >> e;

            ErrorHandle(128, exit, a);
            ErrorHandle(128, exit, b);
            ErrorHandle(128, exit, c);
            ErrorHandle(128, exit, d);
            ErrorHandle(65535, exit, e);
            if (!exit)
                Fill(a, b, c, d, e);
            break;
        case 13:
            cin >> a >> b >> c >> d >> e;

            ErrorHandle(depot.usedWare - 1, exit, a);
            ErrorHandle(depot.warehouses[a].usedRacks - 1, exit, b);
            ErrorHandle(depot.warehouses[a].racks[b].usedShelves - 1, exit, c);
            ErrorHandle(depot.warehouses[a].racks[b].shelves[c].usedSlots - 1, exit, d);
            if (e < 0)
                exit = 1;

            if (!exit)
                PopW(a, b, c, d, e);
            break;
        case 14:
            cin >> a >> b >> c;

            ErrorHandle(depot.usedWare - 1, exit, a);
            ErrorHandle(depot.warehouses[a].handyShelf.usedSlots - 1, exit, b);
            if (c < 0)
                exit = 1;
            if (!exit)
                PopH(a, b, c);
            break;
        case 15:
            cin >> a >> b >> c;

            ErrorHandle(depot.handyRack.usedShelves - 1, exit, a);
            ErrorHandle(depot.handyRack.shelves[a].usedSlots - 1, exit, b);
            if (c < 0)
                exit = 1;
            if (!exit)
                PopR(a, b, c);
            break;
        case 16:
            cin >> a >> b;

            ErrorHandle(depot.handyShelf.usedSlots - 1, exit, a);
            if (b < 0)
                exit = 1;
            if (!exit)
                PopS(a, b);
            break;
        case 17:
            int g, h;
            cin >> a >> b >> c >> d >> e >> f >> g >> h;

            ErrorHandle(depot.usedWare - 1, exit, a);
            ErrorHandle(depot.warehouses[a].usedRacks - 1, exit, b);
            ErrorHandle(depot.warehouses[a].racks[b].usedShelves - 1, exit, c);
            ErrorHandle(depot.warehouses[a].racks[b].shelves[c].usedSlots - 1, exit, g);
            ErrorHandle(depot.usedWare - 1, exit, d);
            ErrorHandle(depot.warehouses[d].usedRacks - 1, exit, e);
            ErrorHandle(depot.warehouses[d].racks[e].usedShelves - 1, exit, f);
            ErrorHandle(depot.warehouses[d].racks[e].shelves[f].usedSlots - 1, exit, g);
            if (h < 0)
                exit = 1;
            if (!exit)
                MovW(a, b, c, d, e, f, g, h);
            break;
        case 18:
            cin >> a >> b >> c >> d >> e;

            ErrorHandle(depot.usedWare - 1, exit, a);
            ErrorHandle(depot.warehouses[a].usedRacks - 1, exit, b);
            ErrorHandle(depot.warehouses[a].racks[b].usedShelves - 1, exit, c);
            ErrorHandle(depot.warehouses[a].racks[b].shelves[c].usedSlots - 1, exit, d);
            ErrorHandle(depot.handyShelf.usedSlots - 1, exit, d);
            if (e < 0)
                exit = 1;
            if (!exit)
                MovH(a, b, c, d, e);
            break;
        case 19:
            cin >> a >> b >> c >> d >> e >> f;

            ErrorHandle(depot.usedWare - 1, exit, a);
            ErrorHandle(depot.warehouses[a].usedRacks - 1, exit, b);
            ErrorHandle(depot.warehouses[a].racks[b].usedShelves - 1, exit, c);
            ErrorHandle(depot.handyRack.usedShelves - 1, exit, d);
            ErrorHandle(depot.warehouses[a].racks[b].shelves[c].usedSlots - 1, exit, e);
            ErrorHandle(depot.handyRack.shelves[d].usedSlots - 1, exit, e);
            if (f < 0)
                exit = 1;
            if (!exit)
                MovR(a, b, c, d, e, f);
            break;
        case 20:
            cin >> a >> b >> c;

            ErrorHandle(depot.handyRack.usedShelves - 1, exit, a);
            ErrorHandle(depot.handyRack.shelves[a].usedSlots - 1, exit, b);
            ErrorHandle(depot.handyShelf.usedSlots - 1, exit, b);
            if (c < 0) {
                exit = 1;
            }

            if (!exit)
                MovS(a, b, c);

            break;
        case 21:
            GetE();
            break;
        case 22:
            cin >> a;

            ErrorHandle(depot.usedWare - 1, exit, a);

            if (!exit)
                GetW(a);
            break;
        case 23:
            cin >> a >> b;

            ErrorHandle(depot.usedWare - 1, exit, a);
            ErrorHandle(depot.warehouses[a].usedRacks - 1, exit, b);

            if (!exit)
                GetRW(a, b);
            break;
        case 24:
            GetRH();
            break;
        case 25:
            cin >> a >> b >> c;

            ErrorHandle(depot.usedWare - 1, exit, a);
            ErrorHandle(depot.warehouses[a].usedRacks - 1, exit, b);
            ErrorHandle(depot.warehouses[a].racks[b].usedShelves - 1, exit, c);

            if (!exit)
                GetSW(a, b, c);
            break;
        case 26:
            cin >> a;

            ErrorHandle(depot.usedWare - 1, exit, a);

            if (!exit)
                GetSH(a);
            break;
        case 27:
            cin >> a;
            ErrorHandle(depot.handyRack.usedShelves - 1, exit, a);
            if (!exit)
                GetSR(a);
            break;
        case 28:
            GetS();
            break;
        case 29: // SET-LW
            cin >> a >> b >> c >> d >> dd[0] >> dd[1];
            ErrorHandle(depot.usedWare - 1, exit, a);
            ErrorHandle(depot.warehouses[a].usedRacks - 1, exit, b);
            ErrorHandle(depot.warehouses[a].racks[b].usedShelves - 1, exit, c);
            ErrorHandle(depot.warehouses[a].racks[b].shelves[c].usedSlots - 1, exit, d);
            LabelCheck(dd, exit);

            if (!exit) {
                depot.warehouses[a].racks[b].shelves[c].slots[d].label[0] = dd[0];
                depot.warehouses[a].racks[b].shelves[c].slots[d].label[1] = dd[1];
            }
            break;

        case 30: // SET-LH
            cin >> a >> b >> dd[0] >> dd[1];
            ErrorHandle(depot.usedWare - 1, exit, a);
            ErrorHandle(depot.warehouses[a].handyShelf.usedSlots - 1, exit, b);
            LabelCheck(dd, exit);

            if (!exit) {
                depot.warehouses[a].handyShelf.slots[b].label[0] = dd[0];
                depot.warehouses[a].handyShelf.slots[b].label[1] = dd[1];
            }
            break;

        case 31: // SET-LR
            cin >> a >> b >> dd[0] >> dd[1];
            ErrorHandle(depot.handyRack.usedShelves - 1, exit, a);
            ErrorHandle(depot.handyRack.shelves[a].usedSlots - 1, exit, b);
            LabelCheck(dd, exit);

            if (!exit) {
                depot.handyRack.shelves[a].slots[b].label[0] = dd[0];
                depot.handyRack.shelves[a].slots[b].label[1] = dd[1];
            }
            break;

        case 32: // SET-LS
            cin >> a >> dd[0] >> dd[1];
            ErrorHandle(depot.handyShelf.usedSlots - 1, exit, a);
            LabelCheck(dd, exit);

            if (!exit) {
                depot.handyShelf.slots[a].label[0] = dd[0];
                depot.handyShelf.slots[a].label[1] = dd[1];
            }
            break;

        case 33: // GET-LW
            cin >> a >> b >> c >> d;
            ErrorHandle(depot.usedWare - 1, exit, a);
            ErrorHandle(depot.warehouses[a].usedRacks - 1, exit, b);
            ErrorHandle(depot.warehouses[a].racks[b].usedShelves - 1, exit, c);
            ErrorHandle(depot.warehouses[a].racks[b].shelves[c].usedSlots - 1, exit, d);

            if (!exit) {
                DisplayLabel(depot.warehouses[a].racks[b].shelves[c].slots[d].label, exit);
            }

            break;
        case 34: // GET-LH
            cin >> a >> b;
            ErrorHandle(depot.usedWare - 1, exit, a);
            ErrorHandle(depot.warehouses[a].handyShelf.usedSlots - 1, exit, b);

            if (!exit) {
                DisplayLabel(depot.warehouses[a].handyShelf.slots[b].label, exit);
            }
            break;
        case 35: // GET-LR
            cin >> a >> b;
            ErrorHandle(depot.handyRack.usedShelves - 1, exit, a);
            ErrorHandle(depot.handyRack.shelves[a].usedSlots - 1, exit, b);

            if (!exit) {
                DisplayLabel(depot.handyRack.shelves[a].slots[b].label, exit);
            }
            break;
        case 36: // GET-LS
            cin >> a;
            ErrorHandle(depot.handyShelf.usedSlots - 1, exit, a);

            if (!exit)
                DisplayLabel(depot.handyShelf.slots[a].label, exit);
            break;
        default:
            break;
        }
        if (exit)
            cout << "error" << endl;
    }

    return 0;
}

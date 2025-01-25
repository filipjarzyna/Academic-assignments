// Filip Jarzyna
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

struct SORTCOUNT {
    unsigned long int index;
    int intType;
    int charSum;
}

struct BUCF {
    bool boolType;
    unsigned short int uncharType;
    float floatType;
};
struct DANA {
    int intType;
    string stringType;
    char charType;
    BUCF bucf1;
    BUCF bucf2;
    BUCF bucf3;
    BUCF bucf4;
};

bool CheckIfEmpty(fstream& dfile)
{
    dfile.seekg(0, fstream::end);
    bool is = (dfile.tellg() == 0);
    dfile.clear();
    return is;
}

//////////// ERROR CHECK /////////
/*
int err0 = 0;
int err1 = 0;
int err2 = 0;
void ErrorCheck(fstream& fileA, fstream& fileB, fstream& helpf, int& errA, int& errB, int& errH)
{
    errA = fileA.rdstate();
    errB = fileB.rdstate();
    errH = helpf.rdstate();
}
*/
/////////////////////////////////

bool CompareDana(DANA dana1, DANA dana2)
{
    bool isSame = 1;
    if (dana1.intType == dana2.intType) {
        if (dana1.stringType == dana2.stringType) {
            if (dana1.charType == dana2.charType) {
                if ((dana1.bucf1.boolType == dana2.bucf1.boolType) && (dana1.bucf1.uncharType == dana2.bucf1.uncharType) && (dana1.bucf1.floatType == dana2.bucf1.floatType)) {
                    if ((dana1.bucf2.boolType == dana2.bucf2.boolType) && (dana1.bucf2.uncharType == dana2.bucf2.uncharType) && (dana1.bucf2.floatType == dana2.bucf2.floatType)) {
                        if ((dana1.bucf3.boolType == dana2.bucf3.boolType) && (dana1.bucf3.uncharType == dana2.bucf3.uncharType) && (dana1.bucf3.floatType == dana2.bucf3.floatType)) {
                            if (!((dana1.bucf1.boolType == dana2.bucf1.boolType) && (dana1.bucf1.uncharType == dana2.bucf1.uncharType) && (dana1.bucf1.floatType == dana2.bucf1.floatType))) {
                                isSame = 0;
                            }
                        } else
                            isSame = 0;
                    } else
                        isSame = 0;
                } else
                    isSame = 0;
            } else
                isSame = 0;
        } else
            isSame = 0;
    } else
        isSame = 0;

    return isSame;
}

bool LgreaterThenP(DANA L, DANA P)
{
    bool isGreater = 0;
    if (L.intType > P.intType) {
        isGreater = 1;
    } else if (L.intType == P.intType) {
        if ((L.bucf1.uncharType + L.bucf2.uncharType + L.bucf3.uncharType + L.bucf4.uncharType) > (P.bucf1.uncharType + P.bucf2.uncharType + P.bucf3.uncharType + P.bucf4.uncharType)) {
            isGreater = 1;
        } else {
            isGreater = 0;
        }
    } else {
        isGreater = 0;
    }

    return isGreater;
}

void DanaPut(fstream& dataFile, DANA dana)
{
    if (dataFile.tellp() > 1)
        dataFile << '\n';

    dataFile << dana.intType << '\n'
             << dana.stringType << '\n'
             << dana.charType << '\n'
             << dana.bucf1.boolType << " " << dana.bucf1.uncharType << " " << dana.bucf1.floatType << '\n'
             << dana.bucf2.boolType << " " << dana.bucf2.uncharType << " " << dana.bucf2.floatType << '\n'
             << dana.bucf3.boolType << " " << dana.bucf3.uncharType << " " << dana.bucf3.floatType << '\n'
             << dana.bucf4.boolType << " " << dana.bucf4.uncharType << " " << dana.bucf4.floatType;
}

bool DanaRead(fstream& dfile, DANA& dana)
{
    bool noError = 1;

    if (dfile >> dana.intType) {
        string s;
        getline(dfile, s); // przechodzi do nastepnej linijki po wczytywaniu inta
        getline(dfile, dana.stringType);
        dana.charType = dfile.get();
        dfile >> dana.bucf1.boolType >> dana.bucf1.uncharType >> dana.bucf1.floatType >> dana.bucf2.boolType >> dana.bucf2.uncharType >> dana.bucf2.floatType >> dana.bucf3.boolType >> dana.bucf3.uncharType >> dana.bucf3.floatType >> dana.bucf4.boolType >> dana.bucf4.uncharType >> dana.bucf4.floatType;
    } else {
        noError = 0;
        dfile.clear();
    }

    return noError;
}

bool IndexAlreadyAdded(fstream& intFile, int index)
{
    bool isInside = 0;
    if (!CheckIfEmpty(intFile)) {
        intFile.seekg(0, fstream::beg);
        int temp;
        while (intFile >> temp) {
            if (temp == index) {
                isInside = 1;
                break;
            }
        }
        intFile.clear();
    }

    return isInside;
}

long unsigned int DanaCounter(fstream& dataFile)
{
    DANA garbageDana;
    long unsigned int count = 0;
    dataFile.seekg(0, fstream::beg);
    while (DanaRead(dataFile, garbageDana)) {
        count++;
    }
    dataFile.clear();
    return count;
}

void SymmetricDifference(string fileName1, string fileName2, string helpName)
{

    fstream fileA;
    fstream fileB;
    fstream helpf;
    helpf.open(helpName.c_str(), fstream::trunc | fstream::out);
    helpf.close();
    fileA.open(fileName1.c_str(), fstream::out | fstream::in);
    fileB.open(fileName2.c_str(), fstream::in);
    helpf.open(helpName.c_str(), fstream::trunc | fstream::trunc);
    /*
    helpf.open(helpName, fstream::trunc | fstream::out);
    helpf.close();
    fileB.open(fileName2, fstream::in);
    fileA.open(fileName1, fstream::in | fstream::out | fstream::app);
    helpf.open(helpName, fstream::out | fstream::app);
    */

    // int danaCountA = 0;
    // int danaAdded = 0;
    long unsigned int danaCountA;
    danaCountA = DanaCounter(fileA);

    bool exit;
    exit = !(fileA.good() && fileA.good() && helpf.good() && !CheckIfEmpty(fileB));

    if (!exit) {
        DANA danaB;
        DANA danaA;
        bool alreadyIn;

        fileB.seekg(0, fstream::beg);
        while (DanaRead(fileB, danaB)) {
            // check if danaB is in fileA
            alreadyIn = 0;
            fileA.seekg(0, fstream::beg);
            int i = 0;
            while ((DanaRead(fileA, danaA)) && (i < danaCountA)) {
                if (CompareDana(danaA, danaB)) {
                    alreadyIn = 1;
                    break;
                }
            }
            if (alreadyIn) {
                DanaPut(helpf, danaB);
            } else {
                fileA.clear();
                DanaPut(fileA, danaB);
            }
            fileA.clear();
        }
    }
    fileA.close();
    fileB.close();
    helpf.close();

    if (!exit) {
        fileB.open(fileName2.c_str(), fstream::trunc | fstream::out);
        fileB.close();
        fileB.open(fileName2.c_str(), fstream::out);
        helpf.open(helpName.c_str(), fstream::in);
        /*
        fileB.open(fileName2, fstream::trunc | fstream::out);
        fileB.close();
        fileB.open(fileName2, fstream::out);
        helpf.open(helpName, fstream::in);
        */
        if (helpf.good() && fileB.good()) {
            DANA temp;
            helpf.seekg(0, fstream::beg);
            // help --> fileB
            while (DanaRead(helpf, temp)) {
                DanaPut(fileB, temp);
            }
        }

        helpf.close();
        fileB.close();
    }
}

void SortCount(string fileName, string helpName1, string helpName2)
{
    /*
        SOURTCOUNT: index int unsignedcharSum
        dfile  SORTCOUNT  ---> help2
        porownac dfile i help2, od najwiekszej wrzucac ----> help1
        help1 = dfile
    */

    fstream dfile;
    fstream help1;
    fstream help2;

    dfile.open(fileName, fstream::in);
    help1.open(helpName1, fstream::out | fstream::app);
    help2.open(helpName2, fstream::out | fstream::app);

    bool exit;
    exit = !(dfile.good() && help1.good() && help2.good() && !CheckIfEmpty(dfile));

    long unsigned int danaCount = DanaCounter(dfile);
    // dfile  SORTCOUNT  ---> help2
    for (int i = 0; i < danaCount; i++) {
        DANA dana1;
        DANA dana2;
        int copyCount = 0;

        // zeby wczytywalo kolejne dane i skipowalo te juz liczone
        dfile.seekg(0, fstream::end);
        while (k = 0; k <= i; k++) {
            DanaRead(dfile, dana1);
        }

        dfile.clear()
        dfile.seekg(0, fstream::beg);
        while (DanaRead(dfile, dana2)) {
            if (CompareDana(dana1, dana2)) {
                count++;
            }
        }
        dfile.clear();
        int tempInt = dana1.bucf1.uncharType + dana1.bucf2.uncharType + dana1.bucf3.uncharType + dana1.bucf4.uncharType;
        help1 << i << " " << dana1.intType << " " << tempInt << '\n';
    }




}

void SortInt(string fileName, string helpName1, string helpName2)
{
    /*
        file1 od najmniejszej do najwiekszej danej wzgledem int--> help1
        help2 trzyma dodane juz do help1 indexy danych w file1
    */

    fstream dfile;
    fstream help1;
    fstream help2;
    /*
    help1.open(helpName1, fstream::out | fstream::trunc);
    help2.open(helpName2, fstream::out | fstream::trunc);
    help1.close();
    help2.close();
    dfile.open(fileName, fstream::in);
    help1.open(helpName1, fstream::out | fstream::app);
    help2.open(helpName2, fstream::in | fstream::out | fstream::app);
    */
    help1.open(helpName1.c_str(), fstream::out | fstream::trunc);
    help2.open(helpName2.c_str(), fstream::out | fstream::trunc);
    help1.close();
    help2.close();
    dfile.open(fileName.c_str(), fstream::in);
    help1.open(helpName1.c_str(), fstream::out | fstream::app);
    help2.open(helpName2.c_str(), fstream::in | fstream::out | fstream::app);
    bool exit;
    exit = !(dfile.good() && help1.good() && !CheckIfEmpty(dfile));

    if (!exit) {
        long unsigned int danaCount = DanaCounter(dfile);
        dfile.seekg(0, fstream::beg);

        DANA dana;
        DANA lastDana;
        DANA lastDanaAdded;
        DANA addThisDana;
        // na wszelki zeby na pewno nie mogla istniec taka dana z warunkow zadania
        lastDanaAdded.bucf1.uncharType = 4201;
        lastDana.bucf1.uncharType = 4202;

        int minInt = -2147483648;
        int lastMinInt = -2147483648;
        long unsigned int lastAddedDanaIndex = 0;

        for (long unsigned int i = 0; i < danaCount; i++) {
            dfile.seekg(0, fstream::beg);
            long unsigned int danaIndex = 0;
            long unsigned int addThisIndex;
            minInt = 2147483647;
            while (DanaRead(dfile, dana)) {
                int temp = dana.intType;
                if ((temp >= lastMinInt) && !(IndexAlreadyAdded(help2, danaIndex))) {
                    if (temp < minInt) {
                        minInt = temp;
                        addThisDana = dana;
                        addThisIndex = danaIndex;
                        // przypadek rownych intow
                    } else if (temp == minInt) {
                        // sprawdza czy tego indexu jeszcze nie bylo
                        if (danaIndex > lastAddedDanaIndex) {
                            // jesli nie dodawalismy jeszcze poprzedniej danej o tym samym int to skipujemy, zeby dodac ta poprzednia
                            // jesli juz dodalismy to ustawiamy ta dana co teraz wczytalismy jako nowy najmniejszy index o tym samym incie czyli olewamy wszystkie dane o tym samym incie ktore sa przed nia(maja mniejszy index), bo wiemy ze juz je dodalismy
                            if (addThisIndex == lastAddedDanaIndex) {
                                addThisIndex = danaIndex;
                                addThisDana = dana;
                                // dodamy dana ktora jest nowa dolna granica indexow danych o tych samych intach
                                // i tak kolejno bedziemy przesuwac granice o jedna dana az dojdziemy do konca danych o tych samych intow
                            }
                        }
                    }
                }
                danaIndex++;
            }
            lastDanaAdded = addThisDana;
            lastMinInt = minInt;
            lastAddedDanaIndex = danaIndex;
            // dodaj dana do helpa
            DanaPut(help1, addThisDana);
            // dodaj index do help2
            help2 << addThisIndex << '\n';
            dfile.clear();
        }
    }

    dfile.close();
    help1.close();
    help2.close();

    if (!exit) {

        // help1 ---> dfile
        /*
        dfile.open(fileName, fstream::trunc | fstream::out);
        dfile.close();
        dfile.open(fileName, fstream::out | fstream::app);
        help1.open(helpName1, fstream::in);
        */
        dfile.open(fileName.c_str(), fstream::trunc | fstream::out);
        dfile.close();
        dfile.open(fileName.c_str(), fstream::out | fstream::app);
        help1.open(helpName1.c_str(), fstream::in);
        if (dfile.good() && help1.good()) {
            help1.seekg(0, fstream::beg);
            DANA tempDana;
            while (DanaRead(help1, tempDana)) {
                DanaPut(dfile, tempDana);
            }
        }
    }

    dfile.close();
    help1.close();
}

void SortString(string fileName, string helpName1, string helpName2)
{
    /*
        file1 od najmniejszej do najwiekszej danej wzgledem int--> help1
        help2 trzyma dodane juz do help1 indexy danych w file1
    */

    fstream dfile;
    fstream help1;
    fstream help2;
    help1.open(helpName1, fstream::out | fstream::trunc);
    help2.open(helpName2, fstream::out | fstream::trunc);
    help1.close();
    help2.close();
    dfile.open(fileName, fstream::in);
    help1.open(helpName1, fstream::out | fstream::app);
    help2.open(helpName2, fstream::in | fstream::out | fstream::app);
    /*
    help1.open(helpName1.c_str(), fstream::out | fstream::trunc);
    help2.open(helpName2.c_str(), fstream::out | fstream::trunc);
    help1.close();
    help2.close();
    dfile.open(fileName.c_str(), fstream::in);
    help1.open(helpName1.c_str(), fstream::out | fstream::app);
    help2.open(helpName2.c_str(), fstream::in | fstream::out | fstream::app);
    */
    bool exit;
    exit = !(dfile.good() && help1.good() && !CheckIfEmpty(dfile));

    if (!exit) {
        long unsigned int danaCount = DanaCounter(dfile);
        dfile.seekg(0, fstream::beg);

        DANA dana;
        DANA lastDana;
        DANA lastDanaAdded;
        DANA addThisDana;
        // na wszelki zeby na pewno nie mogla istniec taka dana z warunkow zadania
        lastDanaAdded.bucf1.uncharType = 4201;
        lastDana.bucf1.uncharType = 4202;

        string minString = "                                              ";
        string lastMinString = "~~~~~~~~~~~~~~~~~~~~~~~~";
        long unsigned int lastAddedDanaIndex = 0;

        for (long unsigned int i = 0; i < danaCount; i++) {
            dfile.seekg(0, fstream::beg);
            long unsigned int danaIndex = 0;
            long unsigned int addThisIndex;
            minString = "                                              ";
            while (DanaRead(dfile, dana)) {
                string temp = dana.stringType;
                if ((temp >= lastMinString) && !(IndexAlreadyAdded(help2, danaIndex))) {
                    if (temp < minString) {
                        minString = temp;
                        addThisDana = dana;
                        addThisIndex = danaIndex;
                        // przypadek rownych intow
                    } else if (temp == minString) {
                        // sprawdza czy tego indexu jeszcze nie bylo
                        if (danaIndex > lastAddedDanaIndex) {
                            // jesli nie dodawalismy jeszcze poprzedniej danej o tym samym int to skipujemy, zeby dodac ta poprzednia
                            // jesli juz dodalismy to ustawiamy ta dana co teraz wczytalismy jako nowy najmniejszy index o tym samym incie czyli olewamy wszystkie dane o tym samym incie ktore sa przed nia(maja mniejszy index), bo wiemy ze juz je dodalismy
                            if (addThisIndex == lastAddedDanaIndex) {
                                addThisIndex = danaIndex;
                                addThisDana = dana;
                                // dodamy dana ktora jest nowa dolna granica indexow danych o tych samych intach
                                // i tak kolejno bedziemy przesuwac granice o jedna dana az dojdziemy do konca danych o tych samych intow
                            }
                        }
                    }
                }
                danaIndex++;
            }
            lastDanaAdded = addThisDana;
            lastMinString = minString;
            lastAddedDanaIndex = danaIndex;
            // dodaj dana do helpa
            DanaPut(help1, addThisDana);
            // dodaj index do help2
            help2 << addThisIndex << '\n';
            dfile.clear();
        }
    }

    dfile.close();
    help1.close();
    help2.close();

    if (!exit) {

        // help1 ---> dfile
        dfile.open(fileName, fstream::trunc | fstream::out);
        dfile.close();
        dfile.open(fileName, fstream::out | fstream::app);
        help1.open(helpName1, fstream::in);
        /*
        dfile.open(fileName.c_str(), fstream::trunc | fstream::out);
        dfile.close();
        dfile.open(fileName.c_str(), fstream::out | fstream::app);
        help1.open(helpName1.c_str(), fstream::in);
        */
        if (dfile.good() && help1.good()) {
            help1.seekg(0, fstream::beg);
            DANA tempDana;
            while (DanaRead(help1, tempDana)) {
                DanaPut(dfile, tempDana);
            }
        }
    }

    dfile.close();
    help1.close();
}

int main()
{
    // SymmetricDifference("A.txt", "B.txt", "help.txt", "help2.txt");
    // SortInt("A.txt", "help.txt", "help2.txt");
    SortString("A.txt", "help.txt", "help2.txt");
}
/*
 */

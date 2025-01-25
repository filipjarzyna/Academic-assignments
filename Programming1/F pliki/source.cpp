// Filip Jarzyna
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

struct DANA2 {
    bool boolType;
    unsigned short int uncharType;
    float floatType;
};

struct DANA {
    int intType;
    string strType;
    char charType;
    DANA2 buf1;
    DANA2 buf2;
    DANA2 buf3;
    DANA2 buf4;
};

int DataCounter(fstream& dataFile)
{
    dataFile.seekg(0, fstream::beg);
    int count = 0;
    do {
        if (dataFile.eof())
            break;
        int tempInt;
        char tempChar;
        string tempTrash;
        bool tempBool;
        float tempFloat;
        dataFile >> tempInt;
        getline(dataFile, tempTrash);
        getline(dataFile, tempTrash);
        tempChar = dataFile.get();
        dataFile >> tempBool >> tempInt >> tempFloat;
        dataFile >> tempBool >> tempInt >> tempFloat;
        dataFile >> tempBool >> tempInt >> tempFloat;
        dataFile >> tempBool >> tempInt >> tempFloat;
        count++;
    } while (true);

    return count;
}

bool BufCompare(DANA2 buf1, DANA2 buf2)
{
    return (buf1.uncharType == buf2.uncharType) && (buf1.floatType == buf2.floatType) && (buf1.boolType == buf2.boolType);
}

bool DanaCompare(DANA dana1, DANA dana2)
{
    // 1 d1 == d2
    // 0 d1 != d2
    bool isSame = 1;
    if (dana1.intType == dana2.intType) {
        if (dana1.strType == dana2.strType) {
            if (dana1.charType == dana2.charType) {
                if (BufCompare(dana1.buf1, dana2.buf1)) {
                    if (BufCompare(dana1.buf2, dana2.buf2)) {
                        if (BufCompare(dana1.buf3, dana2.buf3)) {
                            if (!(BufCompare(dana1.buf4, dana2.buf4))) {
                                isSame = false;
                            }
                        } else {
                            isSame = false;
                        }
                    } else {
                        isSame = false;
                    }
                } else {
                    isSame = false;
                }
            } else {
                isSame = false;
            }
        } else {
            isSame = false;
        }
    } else {
        isSame = false;
    }

    return isSame;
}

void ReadDana(fstream& dataFile, DANA& dana)
{
    string tempTrash;
    dataFile >> dana.intType;
    getline(dataFile, tempTrash);
    getline(dataFile, dana.strType);
    dana.charType = dataFile.get();
    dataFile >> dana.buf1.boolType >> dana.buf1.uncharType >> dana.buf1.floatType;
    dataFile >> dana.buf2.boolType >> dana.buf2.uncharType >> dana.buf2.floatType;
    dataFile >> dana.buf3.boolType >> dana.buf3.uncharType >> dana.buf3.floatType;
    dataFile >> dana.buf4.boolType >> dana.buf4.uncharType >> dana.buf4.floatType;

    // dataFile >> dana.intType >> dana.strType >> dana.charType >> dana.buf1.boolType >> dana.buf1.uncharType >> dana.buf1.floatType >> dana.buf2.boolType >> dana.buf2.uncharType >> dana.buf2.floatType >> dana.buf3.boolType >> dana.buf3.uncharType >> dana.buf3.floatType >> dana.buf4.boolType >> dana.buf4.uncharType >> dana.buf4.floatType;
}

void PutDana(fstream& dataFile, DANA& dana)
{
    /*
    dataFile << dana.intType << '\n';
    dataFile << dana.strType << '\n';
    dataFile << dana.charType << '\n';
    dataFile << dana.buf1.boolType << '\n';
    dataFile << dana.buf1.uncharType << '\n';
    dataFile << dana.buf1.floatType << '\n';
    dataFile << dana.buf2.boolType << '\n';
    dataFile << dana.buf2.uncharType << '\n';
    dataFile << dana.buf2.floatType << '\n';
    dataFile << dana.buf3.boolType << '\n';
    dataFile << dana.buf3.uncharType << '\n';
    dataFile << dana.buf3.floatType << '\n';
    dataFile << dana.buf4.boolType << '\n';
    dataFile << dana.buf4.uncharType << '\n';
    dataFile << dana.buf4.floatType << '\n';
    */

    dataFile << dana.intType << '\n'
             << dana.strType << '\n'
             << dana.charType << '\n'
             << dana.buf1.boolType << " " << dana.buf1.uncharType << " " << dana.buf1.floatType << '\n'
             << dana.buf2.boolType << " " << dana.buf2.uncharType << " " << dana.buf2.floatType << '\n'
             << dana.buf3.boolType << " " << dana.buf3.uncharType << " " << dana.buf3.floatType << '\n'
             << dana.buf4.boolType << " " << dana.buf4.uncharType << " " << dana.buf4.floatType << '\n';
}

void SymmetricDifference(string fileName1, string fileName2, string helpName)
{
    fstream fileA;
    fstream fileB;
    fstream helpf;

    // A += B \ A     H = A /\ B
    /*
    fileA.open(fileName1.c_str(), fstream::in | fstream::out | fstream::app);
    fileB.open(fileName2.c_str(), fstream::in);
    helpf.open(helpName.c_str(), fstream::out | fstream::trunc);
    */
    fileB.open(fileName2, fstream::in);
    helpf.open(helpName, fstream::out | fstream::trunc);
    fileA.open(fileName1, fstream::out | fstream::app | fstream::in);

    if (fileA.good() && fileB.good() && helpf.good()) {
        int dataNumberA = DataCounter(fileA);
        fileB.seekg(0, fstream::beg);
        helpf.seekg(0, fstream::beg);
        int i = 0;
        do {
            DANA danaB;
            bool isInside = false;
            ReadDana(fileB, danaB);
            if (fileB.eof())
                break;
            fileA.seekg(0, fstream::beg);
            do {
                DANA danaA;
                ReadDana(fileA, danaA);
                if (fileA.eof())
                    break;
                if (DanaCompare(danaA, danaB)) {
                    isInside = true;
                    break;
                }
                i++;
            } while (i < dataNumberA);

            if (isInside) {
                // H += A /\ B
                helpf.seekp(0, fstream::end);
                PutDana(helpf, danaB);
            } else {
                // A += B \ A
                // DLACZEGO TO NIE DZIALA?????????????
                PutDana(fileA, danaB);
            }
        } while (true);
        fileA.close();
        fileB.close();
        helpf.close();
        /*
        fileB.open(fileName2, fstream::out | fstream::trunc);
        helpf.open(helpName, fstream::in);
        */
        fileB.open(fileName2, fstream::out | fstream::trunc);
        helpf.open(helpName, fstream::in);
        if (fileB.good() && helpf.good()) {

            do {
                DANA temp;
                ReadDana(helpf, temp);
                if (helpf.eof())
                    break;
                PutDana(fileB, temp);
            } while (true);
        }
        fileB.close();
        helpf.close();
    } else {
        fileA.close();
        fileB.close();
        helpf.close();
    }
}

void SortCount(string fileName, string helpName1, string helpName2)
{
}

void SortInt(string fileName, string helpName1, string helpName2)
{
}

void SortString(string fileName, string helpName1, string helpName2)
{
}

int main()
{
    SymmetricDifference("file1.txt", "file2.txt", "help.txt");
    return 0;
}
/*
 */

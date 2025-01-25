#include <fstream>
#include <iostream>
#include <string>
using namespace std;

struct BUCF {
    bool boolType;
    unsigned char uncharType;
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

//////////// ERROR CHECK /////////
/*
 */
int erA = 0;
int erB = 0;
int erH = 0;
/////////////////////////////////

void ErrorCheck(fstream& fileA, fstream& fileB, fstream& helpf, int& errA, int& errB, int& errH)
{
    errA = fileA.rdstate();
    errB = fileB.rdstate();
    errH = helpf.rdstate();
}

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

void ReadDana(fstream& dataFile, DANA& dana)
{
    string tempTrash;
    dataFile >> dana.intType;
    getline(dataFile, tempTrash);
    getline(dataFile, dana.stringType);
    dana.charType = dataFile.get();
    dataFile >> dana.bucf1.boolType >> dana.bucf1.uncharType >> dana.bucf1.floatType;
    dataFile >> dana.bucf2.boolType >> dana.bucf2.uncharType >> dana.bucf2.floatType;
    dataFile >> dana.bucf3.boolType >> dana.bucf3.uncharType >> dana.bucf3.floatType;
    dataFile >> dana.bucf4.boolType >> dana.bucf4.uncharType >> dana.bucf4.floatType;

    dataFile >> dana.intType >> dana.stringType >> dana.charType >> dana.bucf1.boolType >> dana.bucf1.uncharType >> dana.bucf1.floatType >> dana.bucf2.boolType >> dana.bucf2.uncharType >> dana.bucf2.floatType >> dana.bucf3.boolType >> dana.bucf3.uncharType >> dana.bucf3.floatType >> dana.bucf4.boolType >> dana.bucf4.uncharType >> dana.bucf4.floatType;
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

int main()
{
    DANA dana1;
    fstream file1;
    fstream file2;

    file1.open("1.txt", fstream::in | fstream::out);
    file2.open("2.txt", fstream::in | fstream::out);

    if (file1.good() && file2.good()) {  
        while (file1 >> dana1.intType >> dana1.stringType >> dana1.charType >> dana1.bucf1.boolType >> dana1.bucf1.uncharType >> dana1.bucf1.floatType >> dana1.bucf2.boolType >> dana1.bucf2.uncharType >> dana1.bucf2.floatType >> dana1.bucf3.boolType >> dana1.bucf3.uncharType >> dana1.bucf3.floatType >> dana1.bucf4.boolType >> dana1.bucf4.uncharType >> dana1.bucf4.floatType) {
            file2.seekp(0, fstream::end);
            DanaPut(file2, dana1);
            cout << "dupa" << endl;
        }
    }
    file1.close();
    file2.close();
    return 0;
}
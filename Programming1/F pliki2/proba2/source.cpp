// Filip Jarzyna
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

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
int err0 = 0;
int err1 = 0;
int err2 = 0;
/*
 */
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

int DanaCounter(fstream& dataFile)
{
    int count = 0;
    /*
    do {
        string stringT;
        if (!dataFile.eof()) {
            count++;
        } else
            break;
        for (int i = 0; i < 7; i++) {
            getline(dataFile, stringT);
        }

    } while (true);
    */
    int itemp;
    string stemp;
    char ctemp;
    float ftemp;
    bool btemp;
    while (dataFile >> itemp >> stemp >> ctemp >> btemp >> itemp >> ftemp >> btemp >> itemp >> ftemp >> btemp >> itemp >> ftemp >> btemp >> itemp >> ftemp) {
        count++;
    }
    dataFile.clear();
    return count;
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

bool IntIsInside(fstream& intFile, int num)
{
    bool isInside = 0;

    if (!CheckIfEmpty(intFile)) {
        intFile.seekg(0, fstream::beg);
        do {
            int temp;
            intFile >> temp;
            if (temp == num) {
                isInside = 1;
                break;
            }
        } while (intFile.eof());
        intFile.clear();
    }

    return isInside;
}

void SymmetricDifference(string fileName1, string fileName2, string helpName)
{

    fstream fileA;
    fstream fileB;
    fstream helpf;
    /*
    fileA.open(fileName1.c_str(), fstream::out | fstream::in);
    fileB.open(fileName2.c_str(), fstream::in);
    helpf.open(helpName.c_str(), fstream::out | fstream::trunc);
    */
    fileA.open(fileName1, fstream::out | fstream::in);
    fileB.open(fileName2, fstream::in);
    helpf.open(helpName, fstream::out | fstream::trunc);

    int danaCountA = 0;
    int danaAdded = 0;
    danaCountA = DanaCounter(fileA); // how many DANA in fileA

    bool exit;
    exit = !(fileA.good() && fileA.good() && helpf.good());

    if (!exit) {
        DANA danaB;
        DANA danaA;
        bool alreadyIn;

        fileB.seekg(0, fstream::beg);
        while (fileB >> danaB.intType >> danaB.stringType >> danaB.charType >> danaB.bucf1.boolType >> danaB.bucf1.uncharType >> danaB.bucf1.floatType >> danaB.bucf2.boolType >> danaB.bucf2.uncharType >> danaB.bucf2.floatType >> danaB.bucf3.boolType >> danaB.bucf3.uncharType >> danaB.bucf3.floatType >> danaB.bucf4.boolType >> danaB.bucf4.uncharType >> danaB.bucf4.floatType) {
            // check if danaB is in fileA
            alreadyIn = 0;
            fileA.seekg(0, fstream::beg);
            while (fileA >> danaA.intType >> danaA.stringType >> danaA.charType >> danaA.bucf1.boolType >> danaA.bucf1.uncharType >> danaA.bucf1.floatType >> danaA.bucf2.boolType >> danaA.bucf2.uncharType >> danaA.bucf2.floatType >> danaA.bucf3.boolType >> danaA.bucf3.uncharType >> danaA.bucf3.floatType >> danaA.bucf4.boolType >> danaA.bucf4.uncharType >> danaA.bucf4.floatType) {
                if (CompareDana(danaA, danaB)) {
                    alreadyIn = 1;
                    break;
                }
            }
            fileA.clear();

            if (alreadyIn) {
                // danaB --> helpf    dana in A & B
                helpf.seekp(0, fstream::end);
                DanaPut(helpf, danaB);
            } else {
                // danaB --> fileA    dana in B / A
                fileA.seekp(0, fstream::end);
                DanaPut(fileA, danaB);
            }
            fileA.clear();
            helpf.clear();
        }
    }
    fileB.clear();

    fileA.close();
    fileB.close();
    helpf.close();
    //
    if (!exit) {
        /*
        helpf.open(helpName.c_str(), fstream::in);
        fileB.open(fileName2.c_str(), fstream::out | fstream::  );
        */
        helpf.open(helpName, fstream::in);
        fileB.open(fileName2, fstream::out | fstream::trunc);
        if (helpf.good() && fileB.good()) {
            DANA temp;
            helpf.seekg(0, fstream::beg);
            // help --> fileB
            while (helpf >> temp.intType >> temp.stringType >> temp.charType >> temp.bucf1.boolType >> temp.bucf1.uncharType >> temp.bucf1.floatType >> temp.bucf2.boolType >> temp.bucf2.uncharType >> temp.bucf2.floatType >> temp.bucf3.boolType >> temp.bucf3.uncharType >> temp.bucf3.floatType >> temp.bucf4.boolType >> temp.bucf4.uncharType >> temp.bucf4.floatType) {
                DanaPut(fileB, temp);
            }
        }

        helpf.close();
        fileB.close();
    }
}

void SortCount(string dataFile, string helpName1, string helpName2)
{
}

void SortInt(string fileName, string helpName1, string helpName2)
{

    /*
    dfile od najmniejszego do najwiekszego inta ---> help1
    dfile przy uzyciu help1 posortowane dane ----> help2
    dfile trunc
    help2 = dfile
    */

    fstream dfile;
    fstream help1;
    fstream help2;
    dfile.open(fileName, fstream::in);
    help1.open(helpName1, fstream::out | fstream::in | fstream::app);
    /*
    dfile.open(fileName.c_str(), fstream::in);
    help1.open(helpName1.c_str(), fstream::out | fstream::in | fstream::app);
    */

    bool exit;
    exit = !(dfile.good() && help1.good());

    if (!exit) {
        //ErrorCheck(dfile, help1, help2, err0, err1, err2);
        DANA dana;

        int minInt;
        int danaCount;
        danaCount = DanaCounter(dfile);

        for (int i = 0; i < danaCount; i++) {
            
            minInt = 2147483647;
            dfile.seekg(0, fstream::beg);
           
            while (dfile >> dana.intType >> dana.stringType >> dana.charType >> dana.bucf1.boolType >> dana.bucf1.uncharType >> dana.bucf1.floatType >> dana.bucf2.boolType >> dana.bucf2.uncharType >> dana.bucf2.floatType >> dana.bucf3.boolType >> dana.bucf3.uncharType >> dana.bucf3.floatType >> dana.bucf4.boolType >> dana.bucf4.uncharType >> dana.bucf4.floatType) {
                int tempi;
                tempi = dana.intType;
                if (minInt > tempi) {
                    if (!IntIsInside(help1, tempi)) {
                        minInt = tempi;
                    }
                }
            }
            dfile.clear();
            if (i != 0) {
                help1 << '\n'
                      << minInt;
                ErrorCheck(dfile, help1, help2, err0, err1, err2);
            } else {
                help1 << minInt;
                ErrorCheck(dfile, help1, help2, err0, err1, err2);
            }
            ErrorCheck(dfile, help1, help2, err0, err1, err2);
            dfile.clear();
            help1.clear();
        }
        help1.clear();
        dfile.clear();
        help2.open(helpName2, fstream::out | fstream::app);
        if (help2.good()) {
            help1.seekg(0, fstream::beg);
            for (int i = 0; i < danaCount; i++) {
                int helpInt;
                help1 >> helpInt;
                dfile.seekg(0, fstream::beg);
                for (int k = 0; k < danaCount; k++) {
                    ReadDana(dfile, dana);
                    ErrorCheck(dfile, help1, help2, err0, err1, err2);
                    if (dana.intType == helpInt) {
                        DanaPut(help2, dana);
                        break;
                    }
                }
                dfile.clear();
            }
        }

        dfile.close();
        help1.close();
        help2.close();

        dfile.open(fileName, fstream::trunc | fstream::out);
        help2.open(helpName2, fstream::in);
        exit = !(help2.good() && dfile.good());
        if (!exit) {
            for (int i = 0; i < danaCount; i++) {
                ReadDana(help2, dana);
                DanaPut(dfile, dana);
            }
        }
        dfile.close();
        help2.close();

    } else {
        dfile.close();
        help1.close();
        help2.close();
    }
}

void SortString(string dfile, string help1, string help2)
{
}

int main()
{
    SymmetricDifference("A.txt", "B.txt", "help.txt");
    // SortInt("A.txt", "help.txt", "help2.txt");
    return 0;
}
/*
 */
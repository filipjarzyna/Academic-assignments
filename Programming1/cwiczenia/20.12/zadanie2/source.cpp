#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main () {
    fstream fileA;
    fstream fileB;

    fileA.open("1.txt", fstream::in);
    fileB.open("2.txt", fstream::out | fstream::trunc);

    if (fileA.good() && fileB.good()) {
        fileA.seekg(0, fstream::end);
        fileA.seekg(-1, fstream::cur);
        while(fileA.good()) {
            char c;
            c = fileA.get();
            fileA.seekg(-2, fstream::cur);
            fileB << c;
        }
        fileA.close();
        fileB.close();
    }
}
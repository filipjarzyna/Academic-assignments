#include <iostream>
using namespace std;

int main() {
    int** tab = new int*[5];

    cout << &tab << endl;
    cout << *tab << endl;
    cout << &(**tab) << endl;

}
// Filip Jarzyna
#include <cmath>
// #include <iomanip>
#include <iostream>
using namespace std;

class Solution {
private:
    /// tablica wczytanych liczb
    // potem do niego wyniki sa wpisywane dlatego szerokosc == 3
    float** arr;
    int size;

    void readInput()
    {
        size = 0;
        cin >> size;

        if (size <= 0)
            return;

        arr = new float*[size];

        for (int i = 0; i < size; i++) {
            arr[i] = new float[3];
            arr[i][2] = 0;

            cin >> arr[i][0] >> arr[i][1];
        }
    }

    void printArr()
    {
        // cout << scientific << setprecision(10);
        cout.precision(10);
        for (int i = 0; i < size; i++) {
            cout << arr[i][0] << " " << arr[i][1] << " " << arr[i][2] << endl;
        }
    }

    void setSolutionToInvalid(int index)
    {
        arr[index][0] = 0;
        arr[index][1] = 0;
        arr[index][2] = 0;
    }

    void calculateSingle(int index)
    {
        // suma S i iloczyn P
        float P = arr[index][0];
        float S = arr[index][1];

        if (P == 0) {
            setSolutionToInvalid(index);
            return;
        }

        // z P = x1 * x2 * x3
        float x2 = cbrt(P);
        // pair<float, float> qs = findQ(x2, S);

        float p = (S - x2) / (2 * x2);

        float delta = p * p - 1;

        if (delta < 0) {
            setSolutionToInvalid(index);
            return;
        }

        float t = sqrt(delta);
        float q1;
        float q2;

        if (p >= 0) {
            q1 = p + t;
            q2 = 1 / q1;
        } else {
            q2 = p - t;
            q1 = 1 / q2;
        }

        if (q1 == 0 && q1 == 0) {
            setSolutionToInvalid(index);
            return;
        }

        float x1 = 0;
        float x3 = 1;

        if (q1 != 0) {
            x1 = x2 / q1;
            x3 = x2 * q1;
        }

        if (x1 < x3 && q2 != 0) {
            x1 = x2 / q2;
            x3 = x2 * q2;
        }

        if (x1 < x3) {
            setSolutionToInvalid(index);
            return;
        }

        arr[index][0] = x1;
        arr[index][1] = x2;
        arr[index][2] = x3;
    }

    // szukamy pierwiastkow:
    // q^2 - 2((x2 - S) / -2x2 )q + 1 = 0
    // liczyny na podstawie wyprowadzonych uproszczonych wzorow
    // pair<float, float> findQ(float x2, float S)
    // {
    //     float p = (S - x2) / (2 * x2);

    //     float delta =  p * p - 1;

    //     if (delta < 0) {
    //         return { 0, 0 };
    //     }

    //     float t = sqrt(delta);
    //     float q1;
    //     float q2;

    //     if (p >= 0) {
    //         q1 = p + t;
    //         q2 = 1 / q1;
    //     } else {
    //         q2 = p - t;
    //         q1 = 1 / q2;
    //     }

    //     return { q1, q2 };
    // }

public:
    void solve()
    {
        readInput();

        for (int i = 0; i < size; i++) {
            calculateSingle(i);
        }

        printArr();
    }

    Solution()
        : size(0)
        , arr(NULL)
    {
    }

    ~Solution()
    {
        for (int i = 0; i < size; i++) {
            delete[] arr[i];
        }

        delete[] arr;
    }
};

int main()
{
    // cout.precision(10) nie dziala z jakiegos powodu
    Solution s;
    s.solve();

    return 0;
}
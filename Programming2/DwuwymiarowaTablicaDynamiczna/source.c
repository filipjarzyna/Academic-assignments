// Filip Jarzyna
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/////////////////////// POMOCNICZE MOJE

void DeleteArray(int*** arr, int** len, int* rows)
{
    if (*arr != NULL && arr != NULL && len != NULL && rows != NULL) {

        if (*arr == NULL) {
            return;
        }

        int i;
        for (i = 0; i < *rows; i++) {
            free(*(*arr + i));
        }

        free(*arr);
        free(*len);
        *arr = NULL;
        *len = NULL;
        *rows = 0;
    }
}

void Cube10(int*** arr, int** len, int* rows)
{

    if (rows != 0 || arr != NULL || len != NULL) {
        DeleteArray(arr, len, rows);
    }
    *rows = 10;
    *arr = (int**)calloc(*rows, sizeof(int*));
    *len = (int*)calloc(*rows, sizeof(int));
    int i;
    for (i = 0; i < *rows; i++) {
        *(*len + i) = *rows;
    }

    for (i = 0; i < *rows; i++) {
        *(*arr + i) = (int*)calloc(*rows, sizeof(int));
        int k;
        for (k = 0; k < *rows; k++) {
            *(*(*arr + i) + k) = k;
        }
    }
}

void PrintLen(int* len, int rows)
{
    printf("len: ");
    int i;
    for (i = 0; i < rows; i++) {
        printf(" %d", *(len + i));
    }
    printf("\n");
}

void PrintArr(int** arr, int* len, int rows)
{
    if (arr == NULL || rows == 0)
        printf("NULL\n");
    else {
        int i;
        for (i = 0; i < rows; i++) {
            printf("row %d:", i);
            int k;
            for (k = 0; k < *(len + i); k++) {
                printf(" %d", *(*(arr + i) + k));
            }
            printf("\n");
        }
    }
}

void PrintRows(int rows)
{
    printf("rows: %d\n", rows);
}

void AppRows(int*** arr, int** len, int* rows, int add)
{
    *rows += add;
    *arr = (int**)realloc(*arr, sizeof(int*) * (*rows));
    *len = (int*)realloc(*len, sizeof(int) * (*rows));

    // ustawia nowo dodane na NULL i 0
    int i;
    for (i = (*rows) - 1; i > *rows - add - 1; i--) {
        *(*arr + i) = NULL;
        *(*len + i) = 0;
    }
}

void AppInRow(int*** arr, int** len, int* rows, int row, int add)
{
    *(*len + row) += add;
    *(*arr + row) = (int*)realloc(*(*arr + row), sizeof(int) * (*(*len + row)));

    // zerowanie nowo dodanych wartosci
    int i;
    for (i = *(*len + row) - 1; i > *(*len + row) - add - 1; i--) {
        *(*(*arr + row) + i) = 0;
    }
}

void ShiftRowsDownByOne(int*** arr, int** len, int* rows, int limL, int limP)
{
    // INDEXY:   0 1 2 3 4 limL 6 7 8 9 limP
    // WARTOSCI: 0 1 2 3 4  5   6 7 8 9  0
    //  PO SHIFT --->
    // WARTOSCI: 0 1 2 3 4  5   5 6 7 8  9
    //  limL sie nie zmienia
    //  limP znika

    // shift kazdego elementu od lim (lim tez sie przesunie)
    int i;
    for (i = limP; i > limL; i--) {
        *(*arr + i) = *(*arr + i - 1);
        *(*len + i) = *(*len + i - 1);
    }
}

void ShiftRowsUpByOne(int*** arr, int** len, int* rows, int limL, int limP)
{
    // INDEXY:   0 1 2 3 4 limL 6 7 8 9 limP
    // WARTOSCI: 0 1 2 3 4  0   5 6 7 8  9
    //  PO SHIFT --->
    // WARTOSCI: 0 1 2 3 4  5   6 7 8 9  9
    //  limP sie nie zmienia
    //  limL znika

    // shift kazdego elementu od lim (lim tez sie przesunie)
    int i;
    for (i = limL; i < limP; i++) {
        *(*arr + i) = *(*arr + i + 1);
        *(*len + i) = *(*len + i + 1);
    }
}

void ShiftElemInRowRight(int*** arr, int** len, int* rows, int row, int lim)
{
    // shift kazdego elementu od lim (lim tez sie przesunie)
    // INDEXY:   0 1 2 3 4 lim 6 7 8 9 10
    // WARTOSCI: 0 1 2 3 4  5  6 7 8 9  0
    // PO SHIFT --->
    // WARTOSCI: 0 1 2 3 4  5  5 6 7 8  9
    // lim sie przesuwa jego wartosc zostaje na  ostatnia wartosc znika
    int k;
    for (k = *(*len + row) - 1; k > lim; k--) {
        *(*(*arr + row) + k) = *(*(*arr + row) + k - 1);
    }
}

void ShiftElemInRowLeft(int*** arr, int** len, int* rows, int row, int lim)
{
    // INDEXY:   0 1 2 3 4 lim 6 7 8 9
    // WARTOSCI: 0 1 2 3 4  0  5 6 7 8
    //  PO SHIFT --->
    // WARTOSCI: 0 1 2 3 4  5  6 7 8 8
    //  lim ZNIKA    na koncu zostaje ta co byla

    int k;
    for (k = lim; k < *(*len + row) - 1; k++) {
        *(*(*arr + row) + k) = *(*(*arr + row) + k + 1);
    }
}

/////////////////////////////////////////////////////////////
void RMC(int*** arr, int** len, int* rows, int c);
void RMR(int*** arr, int** len, int* rows, int r);

void AFR(int*** arr, int** len, int* rows)
{
    // wczytanie wejscia
    int num = 0;
    scanf("%d", &num);
    if (num <= 0)
        return;

    int* temp = (int*)calloc(num, sizeof(int));
    int i;
    for (i = 0; i < num; i++) {
        scanf("%d", (temp + i));
    }

    // dlugsc zwiekszenie o 1
    AppRows(arr, len, rows, 1);
    ShiftRowsDownByOne(arr, len, rows, 0, *rows - 1);

    *(*arr + 0) = temp; // zamiana adresu pierwszego pointera w tablicy na adres tej tablicy z wczytanymi liczbami
    *(*len + 0) = num;
}

void ALR(int*** arr, int** len, int* rows)
{
    // wczytanie wejscia
    int num = 0;
    scanf("%d", &num);
    if (num <= 0)
        return;

    int* temp = (int*)calloc(num, sizeof(int));
    int i;
    for (i = 0; i < num; i++) {
        scanf("%d", (temp + i));
    }

    AppRows(arr, len, rows, 1);

    *(*arr + *rows - 1) = temp; // zamiana adresu pierwszego pointera w tablicy na adres tej tablicy z wczytanymi liczbami
    *(*len + *rows - 1) = num;
}

void AFC(int*** arr, int** len, int* rows)
{
    // WCZYTANIE
    int h = 0;
    scanf("%d", &h);
    if (h <= 0)
        return;

    int* temp = (int*)calloc(h, sizeof(int));
    int i;
    for (i = 0; i < h; i++) {
        scanf("%d", (temp + i));
    }
    ////

    // jesli za malo wierszy zwieksz ilosc wierszy
    if (h > *rows) {
        AppRows(arr, len, rows, h - *rows);
    }

    for (i = 0; i < h; i++) {
        AppInRow(arr, len, rows, i, 1);
        ShiftElemInRowRight(arr, len, rows, i, 0);
        *(*(*arr + i) + 0) = *(temp + i); // ustawia pierwszy element na wczytany
    }

    free(temp);
}

void ALC(int*** arr, int** len, int* rows)
{
    // WCZYTANIE
    int h = 0;
    scanf("%d", &h);
    if (h <= 0)
        return;

    int* temp = (int*)calloc(h, sizeof(int));
    int i;
    for (i = 0; i < h; i++) {
        scanf("%d", (temp + i));
    }
    ////

    // jesli za malo wierszy zwieksz ilosc wierszy
    if (h > *rows) {
        AppRows(arr, len, rows, h - *rows);
    }

    for (i = 0; i < h; i++) {
        // (*(*len + i))++; // zwieksza dlugosc wiersza
        // *(*arr + i) = (int*)realloc(*(*arr + i), (*(*len + i)) * sizeof(int)); // zwieksza wielkosc wiersza

        AppInRow(arr, len, rows, i, 1);
        *(*(*arr + i) + *(*len + i) - 1) = *(temp + i); // ustawia ostatni element na wczytany
    }

    free(temp);
}

void IBR(int*** arr, int** len, int* rows)
{
    // WCZYTANIE
    int r = 0;
    int w = 0;
    scanf("%d %d", &r, &w);
    if (w <= 0 || r < 0)
        return;

    int* temp = (int*)calloc(w, sizeof(int));
    int i;
    for (i = 0; i < w; i++) {
        scanf("%d", (temp + i));
    }
    ////

    // jesli za malo wierszy nic nie rob
    if (r < *rows) {
        // dlugsc zwiekszenie o 1
        AppRows(arr, len, rows, 1);
        ShiftRowsDownByOne(arr, len, rows, r, *rows - 1);

        *(*arr + r) = temp; // zamiana adresu pierwszego pointera w tablicy na adres tej tablicy z wczytanymi liczbami
        *(*len + +r) = w; // update dlugosci
    } else {
        free(temp);
    }
}

void IAR(int*** arr, int** len, int* rows)
{
    // WCZYTANIE
    int r = 0;
    int w = 0;
    scanf("%d %d", &r, &w);
    if (w <= 0 || r < 0)
        return;

    int* temp = (int*)calloc(w, sizeof(int));
    int i;
    for (i = 0; i < w; i++) {
        scanf("%d", (temp + i));
    }
    ////

    // jesli za malo wierszy nic nie rob
    if (r <= *rows - 1) {
        // dlugsc zwiekszenie o 1
        // (*rows)++;
        // *len = (int*)realloc(*len, sizeof(int) * (*rows));
        // *arr = (int**)realloc(*arr, sizeof(int*) * (*rows));

        AppRows(arr, len, rows, 1);

        // for (int i = (*rows) - 1; i > r + 1; i--) { // shift kazdego wiersza zeby bylo miejsce
        //     *(*arr + i) = *(*arr + i - 1);
        //     *(*len + i) = *(*len + i - 1); // shift tablicy z dlugosciami
        // }
        ShiftRowsDownByOne(arr, len, rows, r + 1, *rows - 1);

        *(*arr + r + 1) = temp; // zamiana adresu pierwszego pointera w tablicy na adres tej tablicy z wczytanymi liczbami
        *(*len + r + 1) = w; // update dlugosci
    } else {
        free(temp);
    }
}

void IBC(int*** arr, int** len, int* rows)
{
    // WCZYTANIE
    int c = 0;
    int h = 0;
    scanf("%d %d", &c, &h);
    if (h == 0)
        return;

    int* temp = (int*)calloc(h, sizeof(int));
    int i;
    for (i = 0; i < h; i++) {
        scanf("%d", (temp + i));
    }
    ////

    // jesli za malo wierszy powieksz tablice
    if (h > *rows) {
        AppRows(arr, len, rows, h - *rows);
    }

    for (i = 0; i < h; i++) { // wiersze
        int lim = c;

        // jesli za maly wiersz dodaj elem na koniec
        if (*(*len + i) <= c) {
            lim = *(*len + i); // index ostatniej kolumny
        }
        AppInRow(arr, len, rows, i, 1);
        ShiftElemInRowRight(arr, len, rows, i, lim);

        *(*(*arr + i) + lim) = *(temp + i); // zamiana wolenego elem na ustalony
    }

    free(temp);
}

void IAC(int*** arr, int** len, int* rows)
{
    // WCZYTANIE
    int c = 0;
    int h = 0;
    scanf("%d %d", &c, &h);
    if (h == 0)
        return;

    int* temp = (int*)calloc(h, sizeof(int));
    int i;
    for (i = 0; i < h; i++) {
        scanf("%d", (temp + i));
    }
    ////

    // jesli za malo wierszy powieksz tablice
    if (h > *rows) {
        AppRows(arr, len, rows, h - *rows);
    }

    for (i = 0; i < h; i++) { // wiersze
        int lim = c + 1;

        AppInRow(arr, len, rows, i, 1); // zwieksza len automatycznie
        // jesli c wyjezdza gdzies poza wiersz
        if (*(*len + i) - 1 <= lim) {
            lim = *(*len + i) - 1; // index ostatniej kolumny
        } else {
            ShiftElemInRowRight(arr, len, rows, i, lim);
        }
        *(*(*arr + i) + lim) = *(temp + i); // zamiana wolenego elem na ustalony
    }

    free(temp);
}

void SWR(int*** arr, int** len, int* rows)
{
    // WCZYTANIE
    int r = 0;
    int s = 0;
    scanf("%d %d", &r, &s);
    ///
    if (r < 0 || s < 0)
        return;

    if ((r < (*rows)) && (s < (*rows))) {
        int* temp;
        int* temp2;
        int tempLen;

        tempLen = *(*len + r);
        *(*len + r) = *(*len + s);
        *(*len + s) = tempLen;

        temp = *(*arr + r);
        *(*arr + r) = *(*arr + s);
        *(*arr + s) = temp;

        if (*(*arr + r) == NULL || *(*arr + s) == NULL)
            printf("dupa\n");
        // *(*arr + s) = (int*) realloc (*(*arr + s), sizeof(int) * (*(*len + s)));
        // *(*arr + r) = (int*) realloc (*(*arr + r), sizeof(int) * (*(*len + r)));
    }
}

void SWC(int*** arr, int** len, int* rows)
{
    // WCZYTANIE
    int c = 0;
    int d = 0;
    scanf("%d %d", &c, &d);
    ///

    int lim = c; // ustala ktora wieksza zeby sprawdzac czy sie miesci w zakresie
    if (c < d)
        lim = d;

    int temp;
    int i;
    for (i = 0; i < *rows; i++) {
        if (*(*len + i) > lim) { // zamienia wartosci w kolumnach
            temp = *(*(*arr + i) + c);
            *(*(*arr + i) + c) = *(*(*arr + i) + d);
            *(*(*arr + i) + d) = temp;
        }
    }
}

void DFR(int*** arr, int** len, int* rows)
{
    RMR(arr, len, rows, 0);
}

void DLR(int*** arr, int** len, int* rows)
{
    if (*rows > 0)
        RMR(arr, len, rows, *rows - 1);
}

void DFC(int*** arr, int** len, int* rows)
{
    RMC(arr, len, rows, 0);
}

void DLC(int*** arr, int** len, int* rows)
{
    int i;
    for (i = 0; i < *rows; i++) {
        if (*(*len + i) <= 1) {
            free(*(*arr + i));
            *(*arr + i) = NULL;
        } else {
            (*(*len + i))--;
            *(*(*arr + i) + (*(*len + i))) = 0; // zeruje ostatni element wiersza na wszelki
            *(*arr + i) = (int*)realloc(*(*arr + i), sizeof(int) * (*(*len + i))); // zmniejsza rozmiar wiersza o 1
        }
    }

    // koncowe usuwanie wierszy
    int count = 0;
    int oldRows = *rows;
    for (i = 0; i < *rows; i++) {
        if (*(*arr + i) == NULL) {
            RMR(arr, len, rows, i); // lecimy od gory i jesli znajdziemy NULL to usuwamy i wszystkie wiersze shiftuja wiec trzeba zrobic i--
            i--;
            count++;
            if (*rows == 0 || count >= oldRows)
                break;
        }
    }
}

void RMR(int*** arr, int** len, int* rows, int r)
{
    if (r < *rows) {
        free(*(*arr + r));
        ShiftRowsUpByOne(arr, len, rows, r, *rows - 1); // wartosc *(*arr + r) znika z tablicy
        (*rows)--;
        *(*arr + *rows) = NULL; // ustawia ostatni wskaÄšĹnik na null i potem go usuwamy
        if (*rows > 0) {
            *arr = (int**)realloc(*arr, sizeof(int*) * (*rows));
        } else {
            *arr = NULL;
        }
    }
}

void RMC(int*** arr, int** len, int* rows, int c)
{

    int i;
    for (i = *rows - 1; i >= 0; i--) {
        if (c < *(*len + i)) { // czy jest w zakresie
            ShiftElemInRowLeft(arr, len, rows, i, c);
            (*(*len + i))--;
            if ((*(*len + i)) > 0) {
                *(*arr + i) = (int*)realloc(*(*arr + i), sizeof(int) * (*(*len + i))); // zmniejsza o 1, ten ostatni zostanie uciety
            } else { // usuwa zawartosc wiersza ale wiersz jeszcze caly trzeba usunac
                free(*(*arr + i));
                *(*arr + i) = NULL;
                *(*len + i) = 0;
            }
        }
    }

    // koncowe usuwanie wierszy
    int count = 0;
    int oldRows = *rows;
    for (i = 0; i < *rows; i++) {
        if (*(*arr + i) == NULL) {
            RMR(arr, len, rows, i);
            i--;
            count++;
            if (*rows == 0 || count >= oldRows)
                break;
        }
    }
}

void RMB(int*** arr, int** len, int* rows)
{
    // WCZYTANIE
    int r = 0;
    int h = 0;
    int c = 0;
    int w = 0;
    scanf("%d %d %d %d", &r, &h, &c, &w);
    ///
    if (h <= 0 || w <= 0)
        return;

    int lim = r + h;
    if (r + h > *rows)
        lim = *rows;

    int i;
    for (i = r; i < lim; i++) {

        // przeniesienie kazdego elementu za blokiem na przed blokiem
        if (c < *(*len + i)) { // nic nie usuwaj jesli c poza wierszem

            int k;
            for (k = c; k + w < *(*len + i); k++) {
                *(*(*arr + i) + k) = *(*(*arr + i) + k + w);
            }

            int delCount = w; // ile usunie
            if (c + w > *(*len + i)) {
                delCount = *(*len + i) - c; // jesli blok wychodzi poza zakres wiersza
            }
            if (delCount > 0) {
                *(*arr + i) = (int*)realloc(*(*arr + i), sizeof(int) * (*(*len + i) - delCount));
                (*(*len + i)) -= delCount;
            }

            if ((*(*len + i)) <= 0) {
                *(*arr + i) = NULL;
            }
        }
    }

    int count = 0;
    // koncowe usuwanie wierszy
    for (i = r; i < lim; i++) {
        if (*(*arr + i) == NULL) {
            RMR(arr, len, rows, i);
            i--;
            count++;
            if (*rows <= 0 || count > h)
                break;
        }
    }
}

void ISB(int*** arr, int** len, int* rows)
{
    //// WCZYTANIE
    int r = 0; // wiersz o indexie r
    int h = 0; // h wierszy
    int c = 0; // kolumnie o indexie c
    int w = 0; // w kolumn
    scanf("%d %d %d %d", &r, &c, &h, &w);
    if (h <= 0 || w <= 0)
        return;

    int** block = NULL;
    block = (int**)calloc(h, sizeof(int*));
    int i;

    for (i = 0; i < h; i++) {
        *(block + i) = (int*)calloc(w, sizeof(int));
        int k;
        for (k = 0; k < w; k++) {
            scanf("%d", (*(block + i) + k));
        }
    }
    //////////

    // jakby r wybiegalo bog wie gdzie
    if (r > *rows) {
        r = *rows;
    }

    // dodaj wiersze
    if (r + h > *rows) {
        AppRows(arr, len, rows, r + h - *rows);
    }

    for (i = r; i < r + h; i++) {
        int limL = c;
        if (c > *(*len + i)) {
            limL = *(*len + i);
        }

        AppInRow(arr, len, rows, i, w);

        int k;
        for (k = *(*len + i) - 1; k >= limL + w; k--) {
            *(*(*arr + i) + k) = *(*(*arr + i) + k - w); // przesuwa elem przed blokiem zeby zrobic mu miejsce
        }

        // zamienia wartosci elementow zwolnionych na te wczytane
        for (k = limL; k < limL + w; k++) {
            *(*(*arr + i) + k) = *(*(block + i - r) + k - limL);
        }
    }

    // usuwa temp tablice
    for (i = 0; i < h; i++) {
        free(*(block + i));
        *(block + i) = NULL;
    }
    free(block);
}

void WRF(int*** arr, int** len, int* rows)
{
    char* name = (char*)calloc(17, sizeof(char));
    scanf("%s", name);
    FILE* file = fopen(name, "wb");

    if (file == NULL) {
        free(name);
        return;
    }

    fprintf(file, "%d\n", *rows); // Write number of rows

    int i, k;
    for (i = 0; i < *rows; i++) { // Row
        unsigned char tempS = (*(*len + i) >> 8); // Extract higher byte
        fwrite(&tempS, sizeof(unsigned char), 1, file);

        for (k = 0; k < *(*len + i); k++) { // Column
            int temp2 = *(*(*arr + i) + k);
            fwrite(&temp2, sizeof(int), 1, file); // Write the entire integer
        }
    }

    fclose(file);
    free(name);
}

void RDF(int*** arr, int** len, int* rows)
{
    char* name = (char*)calloc(17, sizeof(char));
    scanf("%s", name);
    DeleteArray(arr, len, rows);

    FILE* file = fopen(name, "rb");
    int temp;
    char garbage;
    fscanf(file, "%d", &temp);
    fscanf(file, "%c", &garbage);

    // nowa tablica wiersze rozmiary
    *rows = temp;
    *arr = (int**)calloc(temp, sizeof(int*));
    *len = (int*)calloc(temp, sizeof(int));

    int i;
    for (i = 0; i < *rows; i++) {
        int rowCount = 0; // ile elem w wierszu
        temp = 0;

        fread(&temp, 1, 1, file);
        rowCount += (temp << 8);
        fread(&temp, 1, 1, file);
        rowCount += temp;

        // dodaj wiersz i ustaw dlugosc
        *(*arr + i) = (int*)realloc(*(*arr + i), sizeof(int) * rowCount);
        *(*len + i) = rowCount;

        int k;
        for (k = 0; k < rowCount; k++) {
            // wczytanie kolejno elementow wiersza
            int elem = 0;
            temp = 0;

            // czytanie elementow po 4 bajty
            fread(&temp, 1, 1, file);
            elem += (temp << 24);
            fread(&temp, 1, 1, file);
            elem += (temp << 16);
            fread(&temp, 1, 1, file);
            elem += (temp << 8);
            fread(&temp, 1, 1, file);
            elem += temp;
            *(*(*arr + i) + k) = elem;
        }
    }

    fclose(file);
    free(name);
}

void PRT(int** arr, int* len, int rows)
{
    printf("%d\n", rows);
    if (arr != NULL || rows != 0) {
        int i;
        for (i = 0; i < rows; i++) {
            printf("%d", *(len + i));
            int k;
            for (k = 0; k < *(len + i); k++) {
                printf(" %d", *(*(arr + i) + k));
            }
            printf("\n");
        }
    }
}
/////////////////////////////////////////////////////////////////////////////

int ReadOp(int*** arr, int** len, int* rows)
{
    char* c = (char*)calloc(4, sizeof(char));
    scanf("%s", c);

    if (strcmp(c, "AFR") == 0) {
        AFR(arr, len, rows);
    } else if (strcmp(c, "ALR") == 0) {
        ALR(arr, len, rows);
    } else if (strcmp(c, "AFC") == 0) {
        AFC(arr, len, rows);
    } else if (strcmp(c, "ALC") == 0) {
        ALC(arr, len, rows);
    } else if (strcmp(c, "IBR") == 0) {
        IBR(arr, len, rows);
    } else if (strcmp(c, "IAR") == 0) {
        IAR(arr, len, rows);
    } else if (strcmp(c, "IBC") == 0) {
        IBC(arr, len, rows);
    } else if (strcmp(c, "IAC") == 0) {
        IAC(arr, len, rows);
    } else if (strcmp(c, "SWR") == 0) {
        SWR(arr, len, rows);
    } else if (strcmp(c, "SWC") == 0) {
        SWC(arr, len, rows);
    } else if (strcmp(c, "DFR") == 0) {
        DFR(arr, len, rows);
    } else if (strcmp(c, "DLR") == 0) {
        DLR(arr, len, rows);
    } else if (strcmp(c, "DFC") == 0) {
        DFC(arr, len, rows);
    } else if (strcmp(c, "DLC") == 0) {
        DLC(arr, len, rows);
    } else if (strcmp(c, "RMR") == 0) {
        // WCZYTANIE
        int r;
        scanf("%d", &r);
        ///
        if (r >= 0)
            RMR(arr, len, rows, r);
    } else if (strcmp(c, "RMC") == 0) {
        // WCZYTANIE
        int c = 0;
        scanf("%d", &c);
        ///
        if (c >= 0)
            RMC(arr, len, rows, c);
    } else if (strcmp(c, "RMB") == 0) {
        RMB(arr, len, rows);
    } else if (strcmp(c, "ISB") == 0) {
        ISB(arr, len, rows);
    } else if (strcmp(c, "WRF") == 0) {
        WRF(arr, len, rows);
    } else if (strcmp(c, "RDF") == 0) {
        RDF(arr, len, rows);
    } else if (strcmp(c, "PRT") == 0) {
        PRT(*arr, *len, *rows);
    } else if (strcmp(c, "END") == 0) {
        free(c);
        return 0;
    }
    /// MOJE POMOCNICZE
    else if (strcmp(c, "CUB") == 0) {
        Cube10(arr, len, rows);
    } else if (strcmp(c, "LEN") == 0) {
        PrintLen(*len, *rows);
    } else if (strcmp(c, "PRR") == 0) {
        PrintArr(*arr, *len, *rows);
    } else if (strcmp(c, "ROW") == 0) {
        PrintRows(*rows);
    }

    free(c);
    return 1;
}

int main()
{

    int** arr = NULL;
    int* len = NULL;
    int rows = 0;

    while (ReadOp(&arr, &len, &rows) != 0) { }

    DeleteArray(&arr, &len, &rows);
}
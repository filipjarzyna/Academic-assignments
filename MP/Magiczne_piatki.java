// Filip Jarzyna - gr 6
/*
OGOLNA IDEA
W rekurencyjnej funkcji dokonuje kolejnych partycji:
0. Sprawdzam czy k jest w zakresie tablicy glownej, jesli nie jest to przechodze do nastepnego k i powtarzam.
Jesli nie ma juz wiecej zapytan to koniec.
Jesli jest w zakresie to przechodze do kolejnych krokow:
1. w danej podtablicy (na poczatku jest to cala tablica) dziele tablice na 5 elementowe podtablice,
 ktore kolejno sortuje i przenosze mediane kazdej na poczatek podtablicy,
 nastepnie wybieram z nich mediane i zamieniam z elementem na prawym koncu podtablicy
2. ustawiam wybrany pivot na swoje miejsce sposobem Lomuto
3. sprawdzam czy pivot jest K-tym elementem:
    tak -> printuje wynik i przechodze do kolejnego k z tablicy zapytan
    jest mniejszy -> przechodze do prawej podtablicy i powtarzam algorytm
    jest wiekszy -> przechodze do lewej podtablicy i powtarzam algorytm


 */
import java.util.Scanner;

class Source {
    static int[] arr; //tablica glowna
    static int[] arrK; // tablica z zapytaniami o k-ty element
    static void Print(int k, int num) { //funkcja do printowania wyniku
        if (num < 0) {
            System.out.printf("%d brak\n", k);
        } else {
            System.out.printf("%d %d\n", k, num);
        }
    }

    static void InsertSort(int L, int R) // proste sortowanie przez insercje w podanych granicach L i R
    {
        for (int i = L + 1; i <= R; ++i) {
            int key = arr[i];
            int j = i - 1;

            while (j >= L && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    static void swap(int i, int j) {// zamiana polozenia dwoch elementow
        int tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
    }
    static int Partition(int L, int R) { // wersja Lomuto
        MedianOfMedians(L, R); //wybiera pivot z magicznych piatek
        int i = L - 1;
        for (int j = L; j < R; j++) {
            if (arr[j] <= arr[R] ) { //po prawej pivotu x > arr[pivot]  po lewej x =< arr[pivot]
                i++; //indeks wolnego miejsca
                swap (i, j);
            }
        }

        swap(i + 1, R); //ustawia pivot na wlasciwy element
        return (i + 1); //zwraca pivot
    }

    static void MedianOfMedians (int L, int R) {
        int tempL = L;
        int i = 0; //wolne miejsce na mediane
        while (tempL + 4 <= R) {
            InsertSort(tempL, tempL + 4);
            swap(L + i, tempL + 2); //ustawia kolejne mediany piatek na lewa strone tablicy
            tempL+=5; //przejscie do kolejnej piatki
            i++;
        }
        //ostatnia (nie) piatka
        if (tempL != R) {
            InsertSort(tempL, R);
            swap(L + i, (tempL + R) / 2);
        }

        InsertSort(L, L + i); //sortowanie median
        swap(L + i/2, R); //ustawia mediane median na prawo(pivot nasz)
    }

    static void FindKthElement(int kIndex, int L, int R) {
        if (kIndex < arrK.length) {
            if (arrK[kIndex] <= arr.length && arrK[kIndex] > 0) {
                int pivot = Partition(L, R);
                if (pivot + 1 == arrK[kIndex]) { //jesli znalezlismy element
                    Print(arrK[kIndex], arr[pivot]);
                } else if (pivot + 1 < arrK[kIndex]) {
                    FindKthElement(kIndex, pivot + 1, R); //przechodzi do prawej podtablicy i tam szuka
                    return;
                } else {
                    FindKthElement(kIndex, L, pivot - 1); //przechodzi do lewej podtablicy i tam szuka
                    return;
                }
            } else {
                Print(arrK[kIndex], -69); //nie znalazlo wyniku bo k wychodzi poza tablice
            }
            FindKthElement(kIndex + 1, 0, arr.length - 1); //przechodzi do kolejnego k z tablicy
        }
    }

    public static Scanner sc = new Scanner(System.in);
    public static void main(String[] args) {
        int zestawy = sc.nextInt();
        while (zestawy-- > 0) {
            //wczytywanie tablicy glownej
            int size = sc.nextInt();
            arr = new int[size];
            for (int i = 0; i < size; i++) {
                arr[i] = sc.nextInt();
            }
            //wczytywanie tablicy zapytan
            size = sc.nextInt();
            arrK = new int[size];
            for (int i = 0; i < size; i++) {
                arrK[i] = sc.nextInt();
            }
            FindKthElement(0, 0, arr.length - 1);
        }

    }

}
/*
TESTY:
100
8
2 10 6 7 5 8 5 5
2
6 1
29
31 7 27 20 21 19 29 22 1 31 23 18 2 19 11 9 27 21 4 23 19 14 20 7 19 17 10 13 7
16
30 23 2 1 4 12 19 16 10 7 13 3 21 5 26 22
13
4 2 1 6 9 11 4 1 11 9 1 12 2
10
14 10 1 14 7 9 13 5 12 1
22
18 23 16 17 14 18 23 9 16 9 16 9 7 4 4 20 3 24 9 22 15 15
3
20 21 19
10
6 9 2 3 3 2 9 8 8 2
8
8 9 3 9 11 5 7 10
13
8 10 9 12 7 6 15 4 2 2 9 8 13
11
9 2 9 4 8 12 13 7 4 12 8
19
7 21 12 17 10 20 18 14 21 14 10 21 19 8 17 3 15 6 20
15
6 15 20 14 18 11 2 11 11 14 4 12 3 3 16
28
19 12 30 11 26 21 2 30 12 23 14 6 11 7 30 15 15 18 24 16 27 15 22 27 23 24 2 28
16
20 3 10 3 23 8 3 1 19 2 13 13 14 17 7 19
13
13 2 10 3 4 12 7 12 15 6 6 3 14
6
12 4 6 13 2 10
8
10 2 8 7 7 5 10 6
8
2 9 9 3 9 1 4 2
8
5 3 10 5 2 3 1 7
6
6 1 2 3 6 6
24
18 18 2 22 24 22 1 2 25 25 6 19 21 8 25 12 22 24 23 20 2 6 16 26
2
5 5
3
4 4 3
1
1
2
1 3
2
1 1
1
1
1
1
9
5 10 3 2 3 7 10 6 8
2
10 4
30
16 17 10 12 17 21 6 7 21 10 9 16 11 14 1 14 25 27 15 31 22 31 25 22 32 16 18 24 7 21
24
21 24 1 30 1 2 17 29 7 11 20 23 11 7 5 8 21 22 18 2 25 21 29 14
2
3 4
2
3 3
23
6 19 2 9 16 15 25 24 1 17 14 6 20 17 4 21 16 13 16 13 15 23 24
16
4 8 14 11 21 17 3 5 3 6 15 17 9 1 9 15
26
4 3 13 16 13 27 13 6 1 23 5 1 7 23 2 2 26 12 18 17 28 25 13 19 4 17
25
26 25 24 25 12 23 21 13 17 14 20 21 1 16 14 16 5 9 1 6 9 14 26 7 21
24
13 19 14 4 21 16 2 9 15 13 20 12 19 25 19 22 4 12 16 4 23 24 4 12
8
4 22 25 14 1 19 19 2
23
8 10 2 25 9 9 12 5 6 16 9 18 18 7 15 1 10 6 1 6 18 9 7
21
21 5 2 24 21 20 21 1 5 6 12 21 21 3 19 11 12 22 4 17 17
10
6 2 6 1 2 10 9 3 2 2
1
5
15
16 13 10 15 15 13 12 7 15 9 2 11 7 7 2
3
14 11 3
28
28 20 30 17 11 15 4 20 5 11 22 21 30 10 15 8 20 8 8 14 5 9 27 2 21 20 30 29
21
12 16 13 4 27 19 26 12 18 18 15 21 17 14 9 2 23 6 12 16 8
28
15 13 15 29 28 12 14 26 7 24 5 14 17 6 16 25 15 29 26 1 11 28 18 11 3 10 1 10
24
22 21 26 22 7 2 1 25 6 5 9 23 24 8 12 6 3 4 2 9 24 26 15 4
19
6 7 12 15 2 14 11 19 6 13 21 7 19 15 15 20 10 20 16
2
2 12
20
15 17 21 17 14 2 12 17 1 9 17 10 12 9 19 18 19 21 15 17
4
11 10 6 10
6
8 5 7 3 1 5
2
2 6
2
2 4
2
3 3
8
7 4 10 10 9 3 5 4
1
7
19
6 14 20 16 20 3 19 15 15 12 16 8 4 9 20 5 7 1 2
1
15
8
8 4 2 7 10 9 10 6
3
2 9 5
14
4 11 5 5 8 12 9 12 4 13 7 8 4 6
8
8 9 12 10 12 13 5 5
28
6 18 11 11 24 10 25 14 22 26 22 15 11 11 26 21 19 15 14 5 20 9 22 30 1 25 11 14
1
20
26
27 3 7 9 15 8 1 12 20 27 6 8 25 26 10 14 22 8 17 27 22 28 18 6 19 25
10
10 20 23 17 3 17 18 3 1 7
1
3
1
1
12
5 10 8 1 10 8 13 5 3 8 7 6
2
3 11
5
1 2 4 1 3
1
3
27
14 11 12 28 25 7 16 12 14 6 5 14 9 1 24 22 18 1 15 4 19 5 18 11 1 1 22
13
14 20 22 6 11 22 4 16 2 17 3 28 2
29
31 20 5 25 28 25 4 4 31 28 23 12 10 14 26 1 8 30 26 25 26 18 2 12 18 18 8 30 8
16
13 27 25 7 17 25 11 29 21 7 22 6 4 3 6 3
2
4 2
2
1 1
30
17 30 25 29 23 6 22 9 32 20 5 13 6 3 14 1 28 20 27 6 25 19 4 32 30 1 22 23 5 25
29
26 14 3 6 1 8 29 20 28 29 11 18 31 1 8 5 30 9 13 13 20 4 13 5 30 24 20 1 12
4
4 6 3 1
4
4 4 4 3
3
1 3 1
2
3 3
29
30 27 26 27 4 10 14 16 23 6 31 17 3 30 5 24 13 2 23 3 6 24 17 24 19 23 5 3 27
23
24 16 4 15 23 22 18 27 3 20 25 22 6 9 12 3 10 19 19 2 22 13 25
13
8 6 1 7 13 15 8 10 4 7 13 14 7
9
2 10 13 4 6 7 4 1 8
13
12 4 2 8 15 7 5 6 2 7 1 9 10
6
1 6 8 10 8 10
6
8 3 5 2 6 1
2
2 1
17
18 8 10 16 16 1 19 1 8 4 14 10 1 18 2 3 3
4
17 8 1 13
22
11 20 20 11 12 22 6 4 5 9 14 6 7 11 1 7 21 11 22 20 22 17
7
22 16 15 10 8 23 15
15
11 13 2 17 3 1 7 14 11 1 6 7 1 12 6
14
12 10 5 8 5 16 11 9 15 16 1 5 16 4
30
22 26 12 20 29 3 21 26 6 31 17 28 10 31 22 18 12 18 32 14 4 14 20 16 6 25 22 18 29 32
4
2 29 3 21
30
28 7 10 4 17 8 28 23 23 19 5 2 18 19 17 12 6 23 18 28 25 25 9 10 12 17 25 4 23 4
6
27 8 25 6 4 19
4
1 5 6 1
2
3 2
17
4 2 11 8 19 13 12 4 10 8 4 12 10 8 11 5 11
11
11 2 9 18 9 16 4 5 18 6 17
19
21 15 15 2 13 17 2 12 12 7 1 8 17 8 11 12 3 10 17
16
15 6 8 16 13 1 8 17 6 2 3 19 8 19 15 18
24
26 15 9 14 22 9 12 6 16 20 21 18 10 12 18 7 24 16 19 15 18 26 9 26
9
11 24 11 14 25 18 25 12 21
22
20 14 5 10 4 10 4 23 10 16 14 10 7 12 11 2 4 9 20 16 20 13
19
5 3 16 9 14 13 6 1 16 23 13 12 8 14 14 12 13 13 1
7
8 3 9 2 7 6 7
6
3 6 8 5 5 2
7
6 5 9 7 7 4 9
4
5 1 7 8
16
4 8 11 7 6 14 10 2 14 7 10 11 15 1 9 3
16
13 16 17 11 9 12 4 3 7 10 11 15 5 5 9 10
2
4 4
2
3 1
27
19 21 14 3 20 12 24 26 2 7 1 9 3 23 19 7 23 9 11 23 1 16 2 1 13 25 3
27
24 19 21 16 21 7 6 16 4 2 17 8 5 15 2 23 7 9 3 27 27 27 17 27 27 13 15
30
10 4 2 9 5 15 9 6 31 25 23 22 30 27 27 24 16 13 28 2 17 10 23 31 25 19 22 22 11 18
14
16 8 13 24 6 16 6 1 5 2 2 16 27 22
7
6 5 5 7 6 6 2
2
8 4
10
3 2 9 2 3 1 1 6 4 5
4
2 6 10 7
6
7 7 3 4 8 3
2
1 7
25
27 8 26 9 1 22 8 23 17 3 8 11 19 25 17 10 27 5 12 24 3 11 9 27 17
15
18 19 4 14 15 8 1 24 19 5 18 17 7 10 4
13
12 8 9 13 6 8 13 3 5 2 2 14 14
1
7
6
4 6 7 6 7 6
4
7 3 2 1
9
7 11 2 11 3 9 8 1 7
6
6 6 3 7 7 1
19
1 4 3 20 7 17 2 2 18 19 18 8 6 6 9 15 14 8 17
11
4 4 12 15 8 16 1 5 19 7 4
7
2 4 6 4 3 3 3
5
6 5 4 7 3
25
21 7 18 24 7 23 5 24 8 14 21 19 4 4 20 11 12 20 25 8 1 23 23 21 18
19
5 21 10 22 22 9 18 17 6 19 3 24 11 23 6 12 10 14 16
21
22 22 2 21 6 19 8 19 6 10 4 11 1 12 8 16 18 22 20 18 8
12
6 22 16 9 15 22 6 4 18 13 19 18
19
9 1 2 10 17 3 17 13 16 7 15 11 12 14 20 9 8 16 2
6
2 3 20 15 6 5
18
9 20 13 8 16 16 9 14 5 12 11 19 19 18 10 13 12 20
3
2 11 10
17
14 19 6 8 6 9 13 2 3 9 15 16 3 5 1 11 3
8
18 7 4 5 8 9 1 1
29
24 28 16 11 2 1 7 19 11 21 8 14 1 27 10 28 2 20 21 4 4 24 17 26 29 10 16 17 29
29
9 29 24 11 20 7 12 16 14 10 30 12 29 17 28 11 26 12 19 19 27 14 13 28 24 20 3 3 23
10
11 11 11 9 3 12 3 3 6 10
2
1 1
7
7 3 8 3 4 2 3
7
5 7 1 2 8 4 5
8
8 8 3 10 3 8 9 6
4
5 1 3 5
28
20 3 12 24 16 14 10 4 21 14 16 13 10 25 8 2 28 2 1 2 29 26 5 4 21 24 27 8
26
11 10 20 10 6 8 22 11 5 26 10 28 10 7 7 15 9 25 7 10 28 17 22 11 25 4
25
11 25 23 12 3 15 26 23 20 12 22 27 17 5 10 6 18 19 23 1 25 1 14 27 6
11
26 5 7 3 9 3 11 2 25 13 5
7
4 1 2 1 2 3 1
6
4 3 5 5 6 4
25
24 15 20 23 7 20 9 17 6 4 21 18 26 22 1 1 24 19 6 22 19 3 22 8 12
20
26 10 25 23 14 21 15 6 24 14 14 25 6 10 6 12 12 11 22 8
26
4 19 6 13 23 12 26 24 23 1 23 27 9 21 8 28 8 28 11 16 24 2 4 8 16 26
9
4 7 16 23 2 2 18 6 21
12
13 7 7 4 2 8 12 8 12 7 9 10
11
5 2 9 8 6 13 6 4 7 2 3
16
10 12 13 1 10 13 18 6 2 14 13 5 16 9 17 10
2
6 1
29
27 23 21 11 22 3 11 14 31 5 9 3 2 10 20 11 30 15 9 14 30 14 3 21 7 13 3 1 25
20
8 19 21 6 24 26 17 28 17 21 1 23 25 9 25 4 7 23 6 10
9
6 9 9 5 11 2 5 8 6
2
10 1
5
2 7 6 3 4
2
2 2
3
3 2 5
3
2 1 4
14
10 12 12 2 13 11 8 11 16 8 11 9 13 16
13
13 11 4 1 2 8 13 2 4 4 5 6 3
30
1 26 12 20 9 27 10 26 12 22 4 10 31 23 29 23 32 23 5 4 2 13 9 28 3 25 21 28 13 9
6
31 25 21 10 22 17
29
6 19 1 2 11 31 31 25 7 28 26 23 9 9 8 21 21 28 21 20 13 21 8 6 5 9 3 24 10
28
30 30 14 10 27 15 5 30 14 20 7 16 5 1 17 16 2 2 30 30 3 22 2 7 19 7 10 5
13
2 8 4 12 2 4 12 15 9 12 12 15 15
13
11 8 8 10 9 5 7 11 9 4 12 8 13
12
13 9 9 3 10 12 1 1 1 11 13 3
12
1 1 11 7 12 10 3 4 8 10 12 7
9
6 2 10 3 6 7 7 9 8
7
9 9 7 6 8 1 8
 */
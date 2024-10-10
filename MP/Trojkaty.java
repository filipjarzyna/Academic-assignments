// Filip Jarzyna - 6

import java.util.Scanner;

/*  OGOLNA IDEA
Na poczatku wybiera 1 odcinek zaczynajac od lewej(np. odcinek A), a potem kolejny
odcinek(np. odcinek B) zaczynajac od prawej strony wybranego juz odcinka. Nastepnie sume dlugosci tych odcinkow (a + b) wrzuca do metody
BinSearchFirst, ktora zwraca index. Index ten jest indexem największego odcinka (np. odcinek C), spelniajacego warunek na istnienie trojkata
mianowicie a + b > c. Dzieki temu indeksowi wiemy ze kazdy indeks miedzy indeksami odcinka od B + 1 do C spelnia to rownanie
i mozemy go dobrac do pary wybranych już A i B jako trzeci odcinek do trojkata. Gdy juz przekroczy 10 dobranych trojkatow,
przestaje zapisywac ich indeksy do wczesniej przygotowanej tablicy. Potem wszystko wrzuca na wyjscie tak jak w warunkach zadania.
 */





class Triangles {
    static public int[] arr;

    static private int BinSearchFirst(int x) {
        // troche zmieniony klasyczny algorytm binary search, zwraca najwiekszy indeks wartosci mniejszej niz x
        // Jesli nie ma nic co spelnia powyzsze warunki zwraca -1. Wszystko to oznacza, ze funkcja ta zwroci nam granice
        // indeksowa, ktora posluzy nam do wyznaczenia wszystkich mozliwych trojkatow dla danej dobranej pary odcinkow
        int length = arr.length;
        int left = 0; //granica lewa
        int right = length - 1; //granica prawa
        int closest = right; // najblizsza do x mniejsza liczba

        while (left <= right) {
            int mid = left + (right - left) / 2; //liczy indeks srodka miedzy granicami

            if (arr[left] == x) {
                closest = left - 1; // jesli x jest po lewej to moge zakonczyc bo juz wiadomo gdzie jest granica lewostronna
                // jesli left = 0 to closest == -1 i wiadomo ze nie ma zadnych mniejszych
                break;
            } else if (arr[mid] < x) {
                left = mid + 1; // jesli x jest gdzies po prawej srodka to przesuwam lewa granice na indeks o jeden dalej niz srodek
                closest = mid;
            } else if (arr[mid] == x) {
                right = mid - 1; // jesli rowne no to moge przesunac prawa granice o jeden dalej w lewo niz srodek bo szukam najmniejszej najblizej x
                closest = right; // na razie ustawiam ta najmniejsza na o jedna w lewo od x
            } else { // arr[mid] > x
                right = mid - 1; // i jesli jest w lewej polowie to analogicznie przesuwam prawa granice
            }
        }
        // jesli closest nie wychodzi poza tablice to zwraca jego wartosc, jak sie psuje to zwraca -1 i wiadomo ze nie ma mniejszych
        if (closest < length) {
            return closest;
        } else {
            return -1;
        }


    }
    //prosta metoda do printowania tablicy wedlug warunkow zadania
   static void PrintSortedArr() {
        int length = arr.length;
        int numOfRows = length / 25; //zeby nie liczyc zadnego modulo to licze ile wyjdzie wierszy

        // np. gdy length == 49 to numOfRows == 1 wiec trzeba inkrementacje zrobic
        // czyli troche jakbysmy sufit liczyli z tamtego dzielenia wyzej
        if (length > numOfRows * 25) {
            numOfRows++;
        }

        int numOfLastElem = length - (25 * (numOfRows - 1)); // ile liczb w ostatniej linijce

        for (int i = 0; i < numOfRows; i++) {
            int lim = 25 * (i + 1); // aktualizacja granicy

            if (i == (numOfRows - 1)) { // jesli ostatni wiersz to nie printuje 25 elementow tylko tyle ile zostalo
                lim = numOfLastElem + (25 * i);
            }

            //prosty loop na print elementow
            for (int k = i * 25; k < lim; k++) {
                System.out.printf("%d ", arr[k]);
            }
            System.out.printf("\n");
        }
    }



    static void BubbleSort() {
        int length = arr.length; // zmienna by nie siegac ciagle do arr.length
        //prosty algorytm sortowania
        for (int i = 0; i < length - 1; i++) {
            for (int j = 0; j < length - i - 1; j++) {
                if (arr[j] > arr[j+1]) { //zamiana tylko jak element przed jest mniejszy (otrzymamy ciag niemalejacy)
                    int temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
            }
        }
    }

    static void PrintTriangles(int array[], int count) {
        if (count > 0) {
            int lim = 10; //ustalanie ile trojkatow ma printowac
            if (count < 10) {
                lim = count;
            }

            for (int i = 0; i < lim; i++) {
                int index = 3 * i;
                //(0,2,3) (0,4,5) (1,2,3) (1,4,5) (2,3,4) (2,3,5) (2,4,5) (3,4,5)
                System.out.printf("(%d,%d,%d) ", array[index], array[index + 1], array[index + 2]);
            }
            System.out.printf("\n");
        }

    }

    // Algorytm do liczenia trojkatow uzywajacy BinSearchFirst. Wypisuje on pierwsze 10 trojkatow jak w warunku zadania,
    // a potem juz tylko liczy ile ich jest i zwraca ile jest mozliwych trojkatow
    static int FindTriangles() {
        int count = 0; // zmienna do zliczania trojkatow

        int[] triangles = new int[30];
        int length = arr.length;

        // (l, p, k >= indexLimLeft)
        for (int l = 0; l < length - 2; l++) {
            for (int p = l + 1; p < length; p++) {
                //obie te petle maja zlozonosc O(n), wiec poniewaz sa zagniezdzone to mamy zlozonosc O(n^2)
                //nastepnie wywolujemy algorytm binary search ktory ma zlozonosc logn
                // wszystko jest w sobie zagniezdzone stad calosiowa zlosonosc wynosi O(n^2 * logn)
                int indexLimRight = BinSearchFirst( arr[l] + arr[p]);// z warunku istnienia trojkata a + b > c

                // tym warunkiem przy okazji sprawdzamy czy indexLimRight nie jest przypadkiem rowny -1
                if (!(indexLimRight < p)) {
                    int trianglesToAdd = indexLimRight - p;
                    int indexLimLeft = p + 1;
                    if (count < 10) {
                        //przekazuje indeksy do tablicy bezposrednio indeksy
                        // ktora intuicyjnie ma postac:
                        // a1, a2, a3, b1, b2, b3 .... gdzie a = (a1, a2, a3) to trojkat itd.
                        for (int i = count; i < 10; i++) {
                            int index = i * 3;
                            triangles[index] = l;
                            triangles[index + 1] = p;
                            triangles[index + 2] = indexLimLeft;
                            indexLimLeft++;
                        }
                    }
                    count += trianglesToAdd; //dodaje do ogolnej sumy znalezione dla wybranej pary odcinkow trojkaty
                }

            }
        }

        PrintTriangles(triangles,count); //printuje trojkaty

        return count; //zwraca sume
    }
}

public class Source {
    public static Scanner scanner = new Scanner(System.in);

    public static void main(String args[]) {

        int numOfSets = 0;
        numOfSets = scanner.nextInt();
        Triangles triangles = new Triangles();
        for (int count = 1; count <= numOfSets; count++) {
            int length = scanner.nextInt();
            triangles.arr = new int[length];

            for (int i = 0; i < length; i++) {
                triangles.arr[i] = scanner.nextInt();
            }

            System.out.printf("%d: n= %d\n", count, length);
            triangles.BubbleSort(); //sortowanie tablicy
            triangles.PrintSortedArr(); //print posortowanej tablicy na wyjscie
            System.out.printf("Total number of triangles is: %d\n", triangles.FindTriangles()); // printuje wedlug warunku zadania

        }

    }

}

/* TESTY
INPUT:
20
5
2 16 1 16 6
16
10 4 2 16 20 15 8 12 12 5 1 12 9 17 8 17
18
17 20 3 19 6 13 20 13 14 15 20 8 12 13 7 20 15 8
19
3 20 14 20 16 19 10 14 6 11 17 8 15 3 20 14 8 15 20
6
1 15 13 17 14 19
13
4 12 16 20 2 6 12 13 13 17 15 11 13
7
15 11 6 15 6 20 6
10
4 19 4 4 9 10 8 6 9 9
16
13 5 16 8 20 14 5 15 16 3 11 12 14 9 14 11
9
6 12 18 14 16 9 10 2 19
5
7 3 13 13 13
10
18 7 19 10 6 16 20 19 6 1
10
16 1 3 15 4 2 6 8 12 9
19
1 13 7 16 11 17 13 16 15 19 16 6 8 20 6 10 9 14 9
17
15 14 13 5 7 12 10 6 20 20 11 7 12 2 6 3 11
4
6 7 3 10
5
17 9 18 15 14
8
3 15 3 19 15 9 7 15
12
13 15 13 18 2 1 4 14 18 20 17 12
18
19 6 15 14 17 18 15 18 17 14 9 19 20 8 6 12 14 1

OUTPUT:
1: n= 5
1 2 6 16 16
(0,3,4) (1,3,4) (2,3,4)
Total number of triangles is: 3
2: n= 16
1 2 4 5 8 8 9 10 12 12 12 15 16 17 17 20
(0,4,5) (0,8,9) (0,8,10) (0,9,10) (0,13,14) (1,2,3) (1,4,5) (1,4,6) (1,5,6) (1,6,7)
Total number of triangles is: 282
3: n= 18
3 6 7 8 8 12 13 13 13 14 15 15 17 19 20 20 20 20
(0,1,2) (0,1,3) (0,1,4) (0,2,3) (0,2,4) (0,3,4) (0,5,6) (0,5,7) (0,5,8) (0,5,9)
Total number of triangles is: 617
4: n= 19
3 3 6 8 8 10 11 14 14 14 15 15 16 17 19 20 20 20 20
(0,2,3) (0,2,4) (0,3,4) (0,3,5) (0,4,5) (0,5,6) (0,7,8) (0,7,9) (0,7,10) (0,7,11)
Total number of triangles is: 674
5: n= 6
1 13 14 15 17 19
(1,2,3) (1,2,4) (1,2,5) (1,3,4) (1,3,5) (1,4,5) (2,3,4) (2,3,5) (2,4,5) (3,4,5)
Total number of triangles is: 10
6: n= 13
2 4 6 11 12 12 13 13 13 15 16 17 20
(0,3,4) (0,3,5) (0,4,5) (0,4,6) (0,4,7) (0,4,8) (0,5,6) (0,5,7) (0,5,8) (0,6,7)
Total number of triangles is: 199
7: n= 7
6 6 6 11 15 15 20
(0,1,2) (0,1,3) (0,2,3) (0,3,4) (0,3,5) (0,4,5) (0,4,6) (0,5,6) (1,2,3) (1,3,4)
Total number of triangles is: 23
8: n= 10
4 4 4 6 8 9 9 9 10 19
(0,1,2) (0,1,3) (0,2,3) (0,3,4) (0,3,5) (0,3,6) (0,3,7) (0,4,5) (0,4,6) (0,4,7)
Total number of triangles is: 66
9: n= 16
3 5 5 8 9 11 11 12 13 14 14 14 15 16 16 20
(0,1,2) (0,3,4) (0,4,5) (0,4,6) (0,5,6) (0,5,7) (0,5,8) (0,6,7) (0,6,8) (0,7,8)
Total number of triangles is: 416
10: n= 9
2 6 9 10 12 14 16 18 19
(0,2,3) (0,7,8) (1,2,3) (1,2,4) (1,2,5) (1,3,4) (1,3,5) (1,4,5) (1,4,6) (1,5,6)
Total number of triangles is: 49
11: n= 5
3 7 13 13 13
(0,2,3) (0,2,4) (0,3,4) (1,2,3) (1,2,4) (1,3,4) (2,3,4)
Total number of triangles is: 7
12: n= 10
1 6 6 7 10 16 18 19 19 20
(0,1,2) (0,7,8) (1,2,3) (1,2,4) (1,3,4) (1,5,6) (1,5,7) (1,5,8) (1,5,9) (1,6,7)
Total number of triangles is: 57
13: n= 10
1 2 3 4 6 8 9 12 15 16
(1,2,3) (1,5,6) (1,8,9) (2,3,4) (2,4,5) (2,5,6) (2,8,9) (3,4,5) (3,4,6) (3,5,6)
Total number of triangles is: 29
14: n= 19
1 6 6 7 8 9 9 10 11 13 13 14 15 16 16 16 17 19 20
(0,1,2) (0,5,6) (0,9,10) (0,13,14) (0,13,15) (0,14,15) (1,2,3) (1,2,4) (1,2,5) (1,2,6)
Total number of triangles is: 676
15: n= 17
2 3 5 6 6 7 7 10 11 11 12 12 13 14 15 20 20
(0,2,3) (0,2,4) (0,3,4) (0,3,5) (0,3,6) (0,4,5) (0,4,6) (0,5,6) (0,7,8) (0,7,9)
Total number of triangles is: 374
16: n= 4
3 6 7 10
(0,1,2) (1,2,3)
Total number of triangles is: 2
17: n= 5
9 14 15 17 18
(0,1,2) (0,1,3) (0,1,4) (0,2,3) (0,2,4) (0,3,4) (1,2,3) (1,2,4) (1,3,4) (2,3,4)
Total number of triangles is: 10
18: n= 8
3 3 7 9 15 15 15 19
(0,2,3) (0,4,5) (0,4,6) (0,5,6) (1,2,3) (1,4,5) (1,4,6) (1,5,6) (2,3,4) (2,3,5)
Total number of triangles is: 27
19: n= 12
1 2 4 12 13 13 14 15 17 18 18 20
(0,4,5) (0,9,10) (1,3,4) (1,3,5) (1,4,5) (1,4,6) (1,5,6) (1,6,7) (1,8,9) (1,8,10)
Total number of triangles is: 115
20: n= 18
1 6 6 8 9 12 14 14 14 15 15 17 17 18 18 19 19 20
(0,1,2) (0,6,7) (0,6,8) (0,7,8) (0,9,10) (0,11,12) (0,13,14) (0,15,16) (1,2,3) (1,2,4)
Total number of triangles is: 609





 */
// Filip Jarzyna - 6
import java.util.Scanner;

/*
OGOLNA IDEA :

Algorytm nizej przedstawiony polega na tym ze rozwazam wszystkie mozliwe przypadki jesli chodzi o kolumny
ustawiam kolejno lewa granice oraz prawa w dwoch loopach, nastepnie tworze sobie pomocnicza tablice w ktorej przechowuje
sumy liczb z kazdego wiersza (oczywisce w rozwazanym zakresie kolumn) a nastepnie stosuje na nim zmodyfikowany algorytm Kadane,
ktory pomaga mi znalezc  gorna granice oraz dolna potencjalnej tablicy o najwiekszej sumie(lewa i prawa granica jest juz ustalone wedlug poczatkowych 2 loopow),
sprawdzam w razie zajscia rownosci czy rozmiar tablicy jest mniejszy oraz leksykograficzna kolejnosc indexow.
Jak ten algorytm wyloni mi podtablice o najwiekszej sumie dla danego zakresu kolumn,
to porownuje ja w analogiczny sposob z dotychczasowa podtablica o najwiekszej sumie, tym razem dla ogolnego zakresu tablicy oraz jesli wyjdzie mi ze nowo znaleziona
podtablica jest lepsza, no to ja zamieniam i przechodze do kolejnego zakresu kolumnowego powtarzajac caly proces az dojde do konca. Gdy dojdzie do konca zwraca obiekt Result,
w ktorym znajduja sie informacje o indeksach i sumie danej podtablicy, co potem wyswietla w konsoli
 */




public class Source {
    // klasa reprezentujaca wynik algorytmu
    static class Result {
        private int maxSum;
        private int leftBound;
        private int rightBound;
        private int topBound;
        private int bottomBound;

        // Konstruktor
        public Result(int maxsm, int left, int right, int top, int bottom) {
            this.maxSum = maxsm;
            this.leftBound = left;
            this.rightBound = right;
            this.topBound = top;
            this.bottomBound = bottom;
        }
        //metoda do printowania wynikow w konsoli
        public void printResult(int tabNumber) {
                if (this.bottomBound < 0) {
                    System.out.println(tabNumber +  ": ms_tab is empty");
                } else {
                    System.out.println(tabNumber + ": ms_tab = a[" + this.topBound + ".." + this.bottomBound + "][" + this.leftBound + ".." + this.rightBound + "], msum=" + this.maxSum);
                    //6: ms_tab = a[0..0][0..0], msum=0
                }
        }
    }





    // Zastosowanie algorytmu kadane dla dwuwymiarowej tablicy
    private static Result Kadane2d(int[][] arr) {
        int n = arr.length; // wyznacza granice tablicy (ile wierszy)
        int m = arr[0].length; //wyznacza granice tablicy (ile kolumn)
        int maxSum = Integer.MIN_VALUE; // maksymalna suma dla podtablicy

        //sprawdza czy wszystkie elementy tablicy są mniejsze od 0 lub wszystkie rowne 0
        boolean ujemne = true;
        boolean zerowe = true;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!(ujemne || zerowe)) {
                    break;
                }
                if (arr[i][j] < 0) {
                    zerowe = false;
                } else if (arr[i][j] == 0) {
                    ujemne = false;
                } else {
                    ujemne = false;
                    zerowe = false;
                    break;
                }
            }
        }

        if (ujemne) {
            return (new Result(0, -420, -420, -420, -420)); //zwraca ujemne indeksy to bedzie wiadomo ze osiagnelismy ten przypadek
        }

        if (zerowe) {
            return (new Result(0, 0, 0, 0, 0)); // zwraca wartosci z warunku zadania
        }

        int rowSum[] = new int[n]; //pomocnicza tablica do sumowania wyrazow w wierszach w danym zakresie kolumnowym

        // prostokat jest skrotem myslowym, chodzi oczywiscie o podtablice

        int limLeft = 0; // lewa granica (kolumna)
        int limRight = 0; // prawa granica (kolumna)
        int maxLimLeft = 0; // lewa granica prostokata z najwieksza suma
        int maxLimRight = 0; // prawa granica prostokata
        int maxLimTop = 0; // gorna granica prostokata
        int maxLimBottom = 0; // dolna granica prostokata
        int maxSize = n * m; // wielkosc prostokata o najwiekszej do porownywania czy potencjalny max prostokat jest mniejszy od dotychczasowego max

        //stopniowo lewa granice bedziemy przesuwac o jeden w prawo az do konca tablicy
        while (limLeft < m) {
            limRight = limLeft; // prawa granica zaczyna od lewej i porusza sie w prawo az do ostatniej kolumny
            for (int i = 0; i < n; i++) {
                rowSum[i] = 0; // zeruje wszystkie elementy sumy tablicy bo musimy miec nowa sume dla granicy
            }
            while (limRight < m) {
                // aktualizacja rowSum, uwzglednia do sumy kolumne (o indexie prawej granicy) w sumie wierszy
                for (int i = 0; i <  n; i++) {
                    int temp = arr[i][limRight]; // tymczasowa zmienna zeby nie siegac ciagle do tablicy
                    if (temp < 0) {
                        rowSum[i] += 2 * temp; // wedlug podanego wzoru na sume ujemne maja mnoznik 2
                    } else {
                        rowSum[i] += 3 * temp; //analogczinie dla dodatnich mamy mnoznik tym razem 3
                    }
                }

                // Algorytm Kadane dla rowSum (szukamy najlepszych granic gornych i dolnych prostokata w zakresie wytyczonym przez granice kolumnowe limLeft i limRight)
                // trzeba zauwazyc ze juz mamy "przeskalowane" wartosci w tablicy rowSum wiece nie trzeba uwzgledniac zadnego mnoznika dla ujmenych czy dodatnich
                //maksymalna suma podtablicy sum w rowSum
                int maxEnd = 0; //zmienna do porownywania wedlug algorytmu kadane przechowujaca sume aktualnego ciagu
                int curMax = Integer.MIN_VALUE; // najwieksza suma prosotkata w tym zakresie
                int curLimTopR = 0; // granica lewa aktualnego ciagu w tym zakresie
                int curLimBottR = 0; // granica prawa aktualnego ciagu w tym zakresie
                int maxLimBottR = 0; // granica prawa ciagu o najwiekszej sumie wykrytego w tym zakresie kolumnowym
                int maxLimTopR = 0; // granica lewa ciagu o najwieszej sumie wykrytego w tym zakresie kolumnowym


                for (int i = 0; i < n; i++) {
                    curLimBottR = i; // aktualizacja granicy
                    maxEnd = maxEnd + rowSum[i]; // aktualizacja sumy ciagu

                    if (maxEnd > curMax) {
                        // jesli suma jest wieksza aktualizuje dolne i gorne granice oraz najwieksza sume
                        curMax = maxEnd;
                        maxLimBottR = curLimBottR;
                        maxLimTopR = curLimTopR;
                    } else if (maxEnd == curMax) {
                        // jesli dlugosc jest mniejsza to też aktualizuje nowe granice gorne i dolne oraz najwieksza sume
                        // w celu znalezienia tablicy o mniejszym rozmiarze
                        if ((curLimBottR - curLimTopR) < (maxLimBottR - maxLimTopR)) {
                            maxLimBottR = curLimBottR;
                            maxLimTopR = curLimTopR;

                            // gdy suma i dlugosc taka sama sprawdzamy kolejnosc leksykograficzna (wiemy ze indeksy kolumnowe maja te same wiec wystarczy sprawdzic wiersze)
                        } else if ((curLimBottR - curLimTopR) == (maxLimBottR - maxLimTopR)) {
                            boolean swap = true;
                            // wieksze sa gorsze
                            if (maxLimTopR < curLimTopR) {
                                swap = false;
                            } else if (maxLimTopR == curLimTopR) {
                                if (maxLimBottR < curLimBottR) {
                                    swap = false;
                                }
                            }
                            // jesli mniejsza kolejnosc leksykograficzna no to zamieniamy
                            if (swap) {
                                maxLimBottR = curLimBottR;
                                maxLimTopR = curLimTopR;
                            }
                        }
                    }

                    // jesli suma ujemna lub rowna 0 to wybieramy kolejny poczatek zamiast kontynuowac ciagu
                    if (maxEnd <= 0) {
                        maxEnd = 0;
                        curLimTopR = i + 1;
                    }
                }

                //aktualizacja max prostokata w tablicy 2 wymiarowej
                if (curMax > maxSum) {
                    maxSum = curMax;
                    //podmiana indexow granic
                    maxLimTop = maxLimTopR;
                    maxLimBottom = maxLimBottR;
                    maxLimLeft = limLeft;
                    maxLimRight = limRight;

                    maxSize = (maxLimBottom - maxLimTop + 1) * (maxLimRight - maxLimLeft + 1);

                    // sprawdzenie czy jesli suma taka sama to czy rozmiar jest mniejszy
                } else if (curMax == maxSum) {
                    if (maxSize > ((maxLimBottR - maxLimTopR + 1) * (limRight - limLeft + 1))) {
                        //podmiana indexow granic, suma juz wiadomo ze ta sama
                        maxLimTop = maxLimTopR;
                        maxLimBottom = maxLimBottR;
                        maxLimLeft = limLeft;
                        maxLimRight = limRight;

                        maxSize = (maxLimBottom - maxLimTop + 1) * (maxLimRight - maxLimLeft + 1);

                        // jeszcze sprawdzenie kolejnosci leksykograficznej
                    } else if (maxSize == ((maxLimBottR - maxLimTopR + 1) * (limRight - limLeft + 1))){

                        // a[" + this.topBound + ".." + this.bottomBound + "][" + this.leftBound + ".." + this.rightBound + "]
                        //  a[i .. j] [k .. l] o najmniejszej liczbie
                        //elementów, której indeksy: i, j, k, l tworzą ciąg leksykograficznie najmniejszy.

                        boolean swap = true; // bool nosi wartosc logczina czy zamieniamy max prostokat na nowo wykryty

                        // wiekszy jest gorszy
                        if (maxLimTop < maxLimTopR) {
                            swap = false;
                        } else if (maxLimTop == maxLimTopR){
                            if (maxLimBottom < maxLimBottR) {
                                swap = false;
                            } else if (maxLimBottom == maxLimBottR) {
                                if (maxLimLeft < limLeft) {
                                    swap = false;
                                } else if (maxLimLeft == limLeft) {
                                    if (maxLimRight < limRight) {
                                        swap = false;
                                    }
                                }
                            }
                        }

                        if (swap) {
                            //podmiana indexow granic, suma juz wiemy ze ta sama jest, oraz maxSize tez ten sam
                            maxLimTop = maxLimTopR;
                            maxLimBottom = maxLimBottR;
                            maxLimLeft = limLeft;
                            maxLimRight = limRight;
                        }
                    }
                }



                limRight++; //przesuwa prawa granice w prawo
            }
            limLeft++; //przesuwa lewa granice w prawo
        }




        return (new Result(maxSum, maxLimLeft, maxLimRight, maxLimTop, maxLimBottom));
    }

    public static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        // wczytywanie kolejnych zestawow danych
        int dataCount = scanner.nextInt();

        for (int i = 0; i < dataCount; i++) {

            int arrNum = scanner.nextInt();
            scanner.next().charAt(0);
            int rows = scanner.nextInt();
            int width = scanner.nextInt();
            int arr[][] = new int[rows][width];

            for (int j = 0; j < rows; j++) {
                for (int k = 0; k < width; k++) {
                    arr[j][k] = scanner.nextInt();
                }
            }

            // print wynikow do konsoli
            Result result = Kadane2d(arr);
            result.printResult(arrNum);
        }
    }

}

/////////////////////////   TESTY    ////////////////////////
/*
INPUT:
20
1 : 7 3
0 0 -2
0 4 -1
3 4 0
0 1 -4
4 -4 -1
-1 -2 2
0 2 -3
2 : 7 5
0 0 3 2 0
1 0 0 -1 3
2 -4 0 0 -3
4 -4 0 1 -4
2 1 0 0 -4
0 2 2 4 4
1 3 0 4 -4
3 : 10 5
4 2 0 0 -3
-1 2 -2 0 1
-3 0 1 4 -1
-1 2 -2 -2 2
-4 4 -4 0 -1
-1 -3 -1 0 -1
0 0 0 0 -4
-1 4 -3 -1 2
1 -2 1 2 -3
-4 -2 3 1 3
4 : 7 9
-4 -2 1 1 -2 3 0 1 1
-4 -1 -3 0 -2 -2 4 3 -4
4 -4 -4 3 -3 4 0 3 -1
0 3 3 -4 -2 4 2 -1 -2
0 -2 -1 -3 -4 0 -2 3 1
3 3 1 -1 0 1 -3 0 1
1 2 -4 4 1 0 2 4 -2
5 : 8 9
-3 -3 -2 1 4 -3 3 1 0
0 2 -1 -3 0 0 1 -3 4
4 1 1 -1 0 -3 -4 3 3
3 4 -4 0 1 -3 0 4 -4
-4 4 3 -2 0 -1 2 0 3
0 -1 -1 -3 0 -3 4 4 0
-4 -2 -3 3 3 -2 0 0 -4
4 -4 -2 0 2 0 -1 3 1
6 : 9 4
3 -4 0 0
0 -1 -2 1
-2 -4 -3 -3
3 2 1 -4
3 -1 1 1
-4 -4 -4 2
2 4 -4 4
-4 3 1 3
-4 1 -1 2
7 : 9 2
3 4
-2 3
1 -4
0 3
2 -1
3 -3
-1 2
3 4
0 -1
8 : 9 3
-3 -4 -4
2 4 2
-4 -2 2
0 -1 4
3 -3 -4
0 3 -2
0 4 4
0 -4 -2
3 0 0
9 : 4 8
3 -3 4 -3 1 -3 0 2
4 2 1 4 -3 4 -4 0
-4 -1 0 -3 3 -2 1 -4
0 0 3 3 0 -3 0 -3
10 : 7 4
2 0 -2 4
-2 -2 -1 1
3 0 -4 4
0 4 1 -3
1 1 -2 0
1 4 3 0
4 -3 -1 0
11 : 9 4
-2 -4 -1 -1
2 0 -2 2
4 -4 -3 1
-4 4 0 2
1 3 1 -2
3 3 2 4
3 -2 0 2
3 -4 0 2
-3 -3 -2 -3
12 : 9 6
4 -1 1 0 4 -1
-4 0 0 0 -1 2
-1 -2 -3 4 -1 -1
0 -4 1 -4 3 -1
-1 1 -1 1 2 2
-4 -1 0 0 -2 -1
-3 1 -2 -2 -2 2
-3 -4 2 1 4 2
-3 0 -4 -4 0 -1
13 : 2 4
0 -4 4 -1
-1 0 -3 0
14 : 5 7
-4 0 -1 0 0 -3 1
1 1 -2 -1 0 0 -4
4 0 4 -2 0 3 4
-1 -4 0 -2 3 -2 -3
-1 1 0 3 4 0 -1
15 : 2 4
-4 0 0 4
0 0 0 4
16 : 2 1
-3
-4
17 : 4 9
3 2 1 -3 -2 -2 -4 4 3
-3 1 -3 2 0 2 0 0 0
4 -2 3 4 0 -1 2 -3 -4
3 -3 0 4 -3 4 2 -4 2
18 : 5 8
-2 -1 2 -1 4 -2 2 -1
-3 -3 0 0 4 -3 -1 -1
3 0 -4 -1 -4 3 2 1
-3 2 3 4 -4 0 0 2
3 2 -3 1 0 2 -4 4
19 : 10 10
1 0 4 3 0 -2 2 1 3 0
1 0 4 -2 -3 -4 -1 2 -2 4
4 0 4 2 4 -1 -4 0 3 0
-2 -2 -1 -4 -4 4 -3 3 4 -3
0 3 0 1 2 -1 0 -1 0 3
1 0 4 -3 0 2 -2 -1 0 1
-4 -1 3 -3 -1 1 0 4 -3 0
4 -1 -3 -2 4 -4 -1 -4 2 -1
-2 3 3 -3 3 0 -2 2 3 0
-2 3 -4 -4 -4 3 -4 3 0 2
20 : 8 4
-4 0 1 0
3 0 -2 -4
-1 0 -3 3
4 0 -4 0
2 -2 4 0
3 -1 0 -1
-4 -4 3 -2
0 3 -1 -1

OUTPUT:
1: ms_tab = a[1..4][0..1], msum=40
2: ms_tab = a[0..6][0..3], msum=78
3: ms_tab = a[0..7][1..1], msum=36
4: ms_tab = a[0..6][5..7], msum=86
5: ms_tab = a[0..7][0..8], msum=80
6: ms_tab = a[6..8][1..3], msum=44
7: ms_tab = a[0..7][0..1], msum=62
8: ms_tab = a[1..6][0..2], msum=52
9: ms_tab = a[0..3][0..4], msum=50
10: ms_tab = a[0..6][0..3], msum=59
11: ms_tab = a[1..7][0..3], msum=84
12: ms_tab = a[0..7][3..5], msum=49
13: ms_tab = a[0..0][2..2], msum=12
14: ms_tab = a[2..4][0..6], msum=46
15: ms_tab = a[0..1][3..3], msum=24
16: ms_tab is empty
17: ms_tab = a[0..3][0..8], msum=64
18: ms_tab = a[2..4][0..7], msum=50
19: ms_tab = a[0..8][0..9], msum=144
20: ms_tab = a[1..5][0..0], msum=34
 */

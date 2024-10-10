// Filip Jarzyna - gr 6
import java.util.Scanner;

/*
OGOLNA IDEA

Po wczytaniu tablicy algorytm quick sort wyglada tak:
jesli dlugosc jest mniejsza niz 20 to robimy insertSort (tak jak w warunku zadania) na aktualnej podtablicy i cofamy sie do poprzedniej podtablicy jesli taka jest. Do cofania sie uzywamy
wczesniej zaznaczonych granic wyjasnionych nizej, do znalezienia lewej granicy uzywamy algorytmu BinSearch z modyfikacja by znajdywal element mniejszy najblizszy wartosci przekazanej argumentem.
jesli nie to dokonujemy partycji, wybieramy pivota na podstawie mediany z trzech elementow(pierwszego, srodkowego, ostatniego)
nastepnie te 3 elementy sortujemy i ustawiamy pivot na przedostatnia pozycje podtablicy (R-1),
nastepnie zgodnie z algorytmem quick sort swapujemy wartosci tak by mniejsze od pivota byly po lewej a wieksze po prawej od niego
przy modyfikacji polegajacej rownoczesnym wyznaczaniu elementow najmniejszego i drugiego najmniejszego. Gdy wszystkie elementy beda w odpowiednich pozycjach
ustawiamy element najmniejszy na pierwszej pozycji podtablicy, natomiast drugi najmniejszy dajemy przed pivotem tak by oznaczaly one granice podtablicy przed pivotem.
Nastepnie powtarzamy algorytm na prawej podtablicy od pivotu.
 */


public class Source {
    static long[] arr;

    static void InsertSort(int L, int R) // proste sortowanie przez insercje w podanych granicach L i R
    {
        int n = arr.length;
        for (int i = L + 1; i <= R; ++i) {
            long key = arr[i];
            int j = i - 1;

            while (j >= L && arr[j] > key) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
    }

    static void swap(int i, int j) {// zamiana polozenia dwoch elementow
        long tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
    }

    static int chosePivot(int L, int R) { //wybranie pivotu wedlug mediany z trzech elementow
        int mid = L + (R - L) / 2; // wybranie srodka
        // sortowanie L, R i mid
        if (arr[L] > arr[mid]) {
            swap(L, mid);
        }
        if (arr[L] > arr[R]){
            swap(L, R);
        }
        if (arr[mid] > arr[R]) {
            swap(mid, R);
        }
        swap(mid, R - 1); // ustawia pivot na przedostatni element podtablicy
        return R - 1; // zwraca indeks pivotu
    }


    static int Partition(int L, int R) { // wersja Lomuto (zmodyfikowana pod mediane 3)
        int i = L;
        int pivot = chosePivot(L, R); // przedostatni element jest dzielcy
        int lowest = L; //najmniejszy elem podtablicy
        int secondLow = pivot; // drugi najmniejszy elem podtablicy

        for (int j = L + 1; j < R - 1; j++) {
            if (arr[j] <= arr[pivot] ) {
                i++; //indeks wolnego miejsca
                swap (i, j);
                if (arr[lowest] > arr[i]) { //korekta wartosci najmniejszych
                    secondLow = lowest;
                    lowest = i;
                } else if (arr[secondLow] > arr[i]) {
                    secondLow = i;
                }
            }
        }
        swap (i+1, R - 1); //ustawia pivot na miejsce poprawne
        if (lowest == i + 1) { //korekta wartosci najmniejszych
            lowest = R - 1;
        }

        swap(secondLow, i); // ustawiamy prawa granice partycji na druga najmniejsza
        if (i == lowest) {
            swap(secondLow, L); // jesli w poprzednimy swapie zamienilismy miejsce lowest
        } else {
            swap(lowest, L); // najmniejsza liczba idzie na lewa granice podtablicy wynikowej z partycji
        }
        if (i == L) { //jesli drugi najmniejszy jest pivotem, to zwraca wartosc dalsza zeby sie nie posypalo potem bo secondLow ma byc L - 1
            return (i + 2);
        }
        return (i + 1); //zwraca pivot
    }


    public static void QuickSort() {
        int L = 0;
        int R = arr.length - 1;
        while (true) {
            if (R - L > 18) { //dlugosc wieksza lub rowna 20
                L = Partition(L, R);
            } else {
                InsertSort(L, R); //insert sort gdy elementow jest mniej niz 20
                if (L <= 1) { //ostatni insert wykonany
                    return;
                }
                R = L - 1; //granica na element jeden dalej niz stary pivot ktory juz jest na swoim miejscu dzieki metodzie partycji
                long secondLow = arr[R]; //druga najmniejsza wartosc ktora zaznaczylismy poczatek poprzedniej partycji
                L = BinSearchFirst(secondLow, 0, R - 1); //znajduje mniejsza liczbe ktora zaznaczylismy koniec partycji poprzedniej (lewa granice)
                swap(R, L + 1); //zeby pivot nie byl secondLow bo wtedy tworza sie bardzo male partycje
            }
        }
    }

    static private int BinSearchFirst(long x, int L, int R) {
        // troche zmieniony klasyczny algorytm binary search, zwraca najwiekszy indeks wartosci mniejszej niz x
        // Jesli nie ma nic co spelnia powyzsze warunki zwraca -1. Wszystko to oznacza, ze funkcja ta zwroci nam granice
        // indeksowa, ktora posluzy nam do wyznaczenia wszystkich mozliwych trojkatow dla danej dobranej pary odcinkow
        int length = arr.length;
        int closest = R; // x jest na R + 1 wiec zwezamy

        while (L <= R) {
            int mid = L + (R - L) / 2; //liczy indeks srodka miedzy granicami
//            if (arr[L] == x) {
//                closest = L - 1; // jesli x jest po lewej to moge zakonczyc bo juz wiadomo gdzie jest granica lewostronna
//                // jesli left = 0 to closest == -1 i wiadomo ze nie ma zadnych mniejszych
//                break;
//            } else
            if (arr[mid] < x) {
                L = mid + 1; // jesli x jest gdzies po prawej srodka to przesuwam lewa granice na indeks o jeden dalej niz srodek
                closest = mid;
            } else if (arr[mid] == x) {
                R = mid - 1; // jesli rowne no to moge przesunac prawa granice o jeden dalej w lewo niz srodek bo szukam najmniejszej najblizej x
                closest = R; // na razie ustawiam ta najmniejsza na o jedna w lewo od x
            } else { // arr[mid] > x
                R = mid - 1; // i jesli jest w lewej polowie to analogicznie przesuwam prawa granice
            }
        }
        // jesli closest nie wychodzi poza tablice to zwraca jego wartosc, jak sie psuje to zwraca -1 i wiadomo ze nie ma mniejszych
        if (closest >= 0) {
            return closest;
        } else {
            return 0;
        }


    }
//    static void SortTest(int zestawy) { // test sortowania wlasny nie robi nic na bacy
//        for (int i = 1; i < arr.length; i++) {
//            if (arr[i - 1] > arr[i]) {
//                System.out.printf("\n--------------------------------------------------------\n");
//                System.out.printf("ZLE POSORTOWANE\n");
//                System.out.printf("zestaw: %d\n", zestawy);
//                PrintArr();
//                System.out.printf("--------------------------------------------------------\n");
//                return;
//            }
//        }
////        System.out.printf("jest g\n");
//    }

//    static void PrintArr() { //funkcja do wyswietlania array
//        for (int i = 0; i < arr.length; i++) {
//            System.out.printf("%d ", arr[i]);
//        }
//        System.out.println();
//    }
    static void PrintArr() { //funkcja do wyswietlania array
        StringBuilder sb = new StringBuilder();
        for (long l : arr) {
            sb.append(l);
            sb.append(" ");
        }
        System.out.println(sb);
    }

    public static Scanner sc = new Scanner(System.in);

    public static void main(String[] args) {
        int zestawy = sc.nextInt();
//        long startTime = System.nanoTime();
        while (zestawy-- > 0) {
            int size = sc.nextInt();
            arr = new long[size];
            for (int i = 0; i < size; i++) {
                arr[i] = sc.nextInt();
            }
            QuickSort();
//            SortTest(zestawy);
            PrintArr();
        }
//        long endTime = System.nanoTime();
//        long duration = endTime - startTime; // in nanoseconds
//        double durationInSeconds = (double) duration / 1_000_000_000.0; // converting to seconds
//        System.out.printf("time: %.9f sec", durationInSeconds);

    }


}

/*
TESTY:
5
9
-8 -5 -4 7 -10 6 -3 3 4
2
-2 -1
9
-8 -5 7 -9 1 4 3 0 -3
3
-5 -4 7
1
0
 */
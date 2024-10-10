// Filip Jarzyna - gr 6

/*
OGOLNA IDEA

Obie funkcje korzystaja ze stosu typu Int do przechowywania zawartosci plecaka,
w stosie dolaczylem rowniez funkcje Print oraz zmienna sledzaca sume wszystkich elementow.
Obie funkcje opieraja sie na rozwijaniu drzewa mozliwosci pakowania plecaka, galezie sa kolejno rozwijane
w kolejnosci leksykograficznej wejscia jak wyamga tego zadania. Gdy suma w plecaku osiagnie dokladnie
maksymalna wage to zalacza Print i zaprzestaje dalsze szukanie odpowiednich galezi.
*/

import java.util.Scanner;

//stos bedzie przechowywal wagi przedmiotow (bedzie pelnil role plecaka)
class IntStack {
    private int maxSize; // rozmiar tablicy zawierającej stos
    private int[] Elem; // tablica zawierająca stos
    private int top; // indeks wierzchołka stosu
    private int sum;

    public IntStack(int size) { // konstruktor - Create()
        maxSize = size; // ustawiamy rozmiar tablicy
        Elem = new int[maxSize]; // tworzymy tablicę dla elementów
        top = maxSize; // na razie brak elementów (stos rośnie w górę)
        sum = 0;
    }
    public int getSum() {
        return sum;
    }

    public void push(int x) {
        if(isFull()) return;
        else Elem[--top] = x; // zmniejszamy top, odkładamy element
        sum += x;
    }

    public int peek() {
        if(!isEmpty()) {
            return Elem[top];
        }
        return -10;
    }

    public int pop() {
        if(!isEmpty()) {
            sum -= Elem[top];
            return Elem[top++];
        }
        return -10;
    }

    public void Print(boolean rec) {
        if (rec) {
            System.out.printf("REC: ");
        } else {
            System.out.printf("ITER: ");
        }

        System.out.printf("%d =", sum);
        for (int i = maxSize - 1; i >= top; i--) {
            System.out.printf(" %d", Elem[i]);
        }
        System.out.printf("\n");
    }

    public boolean isEmpty(){ // zwraca true, jeżeli stos pusty
        return (top == maxSize);
    }
    public boolean isFull(){ // zwraca true, jeżeli stos pełny
        return (top == 0);
    }
}

public class Source {
    static int[] arr;


    static boolean recPackage(int weight, IntStack backpack, int takeThis) {
        if (backpack.getSum() == weight) {
            backpack.Print(true);
//            backpack.Print(false);
            return true;
        }
        //jesli nie mozemy rozbudowywac kolejnych galezi cofamy sie o jedna nizej
        if (takeThis < 0 || backpack.getSum() > weight) {
            return false;
        }

        //pakujemy kolejny element do plecaka i rozbudowujemy galezie z niego
        backpack.push(arr[takeThis]);
        if (recPackage(weight, backpack, takeThis - 1)) {
            return true;
        }

        // jesli nie znajdzie tam to sprawdzaym kolejna galaz
        backpack.pop(); //zdejmujemy to ktora nie wyszla
        return recPackage(weight,backpack,takeThis - 1);
    }

    static void StackSimPackage(int weight) {
        int takeThis = arr.length - 1;
        IntStack backpack = new IntStack(arr.length);
        IntStack index = new IntStack(arr.length); //stos z mozliwosciami rozwijania galezi
        index.push(takeThis); //poczatkowe mozliwosci rozwoju galezi

        while (true) {
            //jesli znajdzie odpowiednia wage
            if (backpack.getSum() == weight) {
                backpack.Print(false);
                return;
            }
            takeThis = index.pop();
            if (takeThis == -10) return;

            if (takeThis < 0) { //jesli juz nie ma galezi do sprawdzania cofnij sie o jeden
                int last = backpack.pop();
                if (last == -10) { //jesli tablica jest pusta BRAK
                    //BRAK
                    return;
                }
            } else { //jesli moze rozwijac galaz
                backpack.push(arr[takeThis]);
                index.push(takeThis - 1); //zwraca na stak mozliwosci aktualnej galezi
                if (backpack.getSum() > weight) { //sprawdza czy mozna dodac nastepna wartosc
                    backpack.pop();
                } else {
                    index.push(takeThis - 1); //jesli rozwinelismy galaz dodaje mozliwosci rozwoju dla niej do stosu
                }
            }
        }
    }

    static Scanner scanner = new Scanner(System.in);

    public static void main(String args[]) {
        int count = 0;
        count = scanner.nextInt();

        while (count-- > 0) {
            //wczytanie danych
            int weight = scanner.nextInt();
            int numOfW = scanner.nextInt();
            arr = new int[numOfW];

            for (int i = numOfW - 1; i >= 0; i--) {
                arr[i] = scanner.nextInt();
            }
            if (recPackage(weight, new IntStack(numOfW), arr.length - 1)) {
                StackSimPackage(weight);
            } else {
                System.out.printf("BRAK\n"); //jesli nie znajdzie rozwiazania
            }
        }


    }
}

/*
TESTY
5
30
10
1 2 3 4 5 6 7 8 9 10
1
10
10 9 8 7 6 5 4 3 2 1
90
15
99 40 20 15 14 17 30 18 19 11 23 32 77 23 44
5
8
10 9 16 7 2 5 3 7
13
9
2 4 6 8 9 10 3 12 17 13
 */
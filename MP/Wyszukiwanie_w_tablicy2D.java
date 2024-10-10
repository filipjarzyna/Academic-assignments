// Filip Jarzyna - gr 6
import java.util.Scanner;

/*
OGOLNA IDEA
Program implementuje w 4 funkcjach algorytm oparty na Binary Search. W recFirst oraz iterFirst zaczyna od pierwszego wiersza nastepnie
w kolejnych wierszach (do znalezienia szkanej lub konca wierszy) szuka pierwszego wystapienia danej liczby, wykorzystujac algorytm oparty na Binary Search,
znajdujacy pierwsze wystapienie szukanej liczby.
Podobnie dziala to w iterLast, oraz recLast, jednak zaczynamy wtedy od ostatniego wiersza oraz szukamy ostatniego wystapienia w kazdym,
ponownie przy uzyciu algorytmu opartego na Binary Search tym razem jednak znajdujacego ostatnie wystapienie.
 */





public class Source {
    static int[][] arr; //tablica 2d

    //stosujemy bin search kolejno na kazdym wierszu i szukamy pierwszej instancji szukanej
    //jesli nie znajdzie to zwraca -1
    public static void RecFirst(int row, int left, int right, int target, int result) {
        if (left > right) { //jesli nie znaleziono przejdz do nastepnego wiersza
            if (result != -1) {
                System.out.printf("recFirst: %d = a[%d][%d]\n", target, row, result);
            } else if (row == arr.length - 1) { //jesli w zadnym nie znalezlismy
                System.out.printf("recFirst: %d missing in array\n", target);
            } else { //przejdz do nastepnego wiersza
                RecFirst(row + 1, 0, arr[0].length - 1, target, result);
            }
        } else { //if (left < right)
            int mid = left + (right - left) / 2;

            if (arr[row][mid] == target) {
                result = mid;
                right = mid - 1;
            } else if (arr[row][mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }

            RecFirst(row, left, right, target, result);
        }
    }

    public static void RecLast(int row, int left, int right, int target, int result) {
        if (left > right) { //jesli nie znaleziono przejdz do nastepnego wiersza
            if (result != -1) { //jesli znaleziono print i zakoncz
                System.out.printf("recLast: %d = a[%d][%d]\n", target, row, result);
            } else if (row == 0) { //jesli w ostatnim nie znalezlismy
                System.out.printf("recLast: %d missing in array\n", target);
            } else { //jesli nic nie znaleziono przejdz do kolejnego wiersza
                RecLast(row - 1, 0, arr[0].length - 1, target, result);
            }
        } else { //if (left < right)
            int mid = left + (right - left) / 2; //srodek

            //update granic left i right
            if (arr[row][mid] == target) {
                result = mid; //potencjalny last
                left = mid + 1;
            } else if (arr[row][mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
            RecLast(row, left, right, target, result);
        }
    }

    public static void IterFirst(int target) {
        int row = 0;
        int result = -1; //indeks pierwszego targetu(jesli nie znajdzie pozostanie wartosc -1)

        //idzie po wierszach
        while (row < arr.length) {
            int left = 0; //granica lewa
            int right = arr[row].length - 1; //granica prawa

            while (left <= right) {
                int mid = left + (right - left) / 2;

                //update granic
                if (arr[row][mid] == target) {
                    result = mid; //potencjalny indeks first
                    right = mid - 1;
                } else if (arr[row][mid] < target) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }

            //jesli znalazlo target
            if (result != -1) {
//                return new int[]{row, left, target};
                System.out.printf("iterFirst: %d = a[%d][%d]\n", target, row, result);
                return;
            }
            row++;
        }

        //jesli nic nie znaleziono
        System.out.printf("iterFirst: %d missing in array\n", target);
    }

    public static void IterLast(int target) {
        int row = arr.length - 1; //zaczynamy od ostatniego wiersza

        int result = -1; //indeks szukanej liczby

        while (row >= 0) {
            int left = 0; // lewa granica
            int right = arr[row].length - 1; //prawa granica
            while (left <= right) {
                int mid = left + (right - left) / 2;

                //update granic (przesuwanie blizej srodka
                if (arr[row][mid] == target) {
                    result = mid; //potencjalny indeks last
                    left = mid + 1;
                } else if (arr[row][mid] < target) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }

            //jesli znalazl target w wierszu
            if (result != -1) {
                System.out.printf("iterLast: %d = a[%d][%d]\n", target, row, result);
                return;
            }
            row--;
        }
        //jesli nic nie znaleziono
        System.out.printf("iterLast: %d missing in array\n", target);

    }
    /* ZLOZONOSC
      Kazda funkcja ma zlozonosc m * logn, poniewaz przechodzimy liniowo po m wierszach
      i na kazdym stosujemy algorytm oparty na Binary Search, ktory za kazdym razem
      dzieli dana tablice(1 wymiarowa) na polowe (zlozonosc logn).
     */




    public static Scanner in = new Scanner(System.in);
    public static void main(String[] args) {
        int count = in.nextInt();
        while (count-- > 0) { //wczytywanie danych wedlug tresci zadania
            int height = in.nextInt();
            int width = in.nextInt();
            arr = new int[height][width];
            for (int i = 0; i < height; i++) {
                for (int k = 0; k < width; k++) {
                    arr[i][k] = in.nextInt();
                }
            }
            int target = in.nextInt();
            RecFirst(0,0,width - 1, target, -1);
            RecLast(height - 1,0, width - 1, target, -1);
            IterFirst(target);
            IterLast(target);
            System.out.printf("---\n");
        }
    }
}


/* TESTY
INPUT:
4
3 4
10 10 10 10
10 20 20 30
20 20 20 40
20
3 4
10 10 10 10
10 20 20 30
20 20 20 40
50
3 3
10 10 10
10 20 20
20 20 20
10
5 4
10 20 30 40
15 25 35 45
27 29 37 48
28 29 39 50
33 34 40 51
40

OUTPUT:
recFirst: 20 = a[1][1]
recLast: 20 = a[2][2]
iterFirst: 20 = a[1][1]
iterLast: 20 = a[2][2]
---
recFirst: 50 missing in array
recLast: 50 missing in array
iterFirst: 50 missing in array
iterLast: 50 missing in array
---
recFirst: 10 = a[0][0]
recLast: 10 = a[1][0]
iterFirst: 10 = a[0][0]
iterLast: 10 = a[1][0]
---
recFirst: 40 = a[0][3]
recLast: 40 = a[4][2]
iterFirst: 40 = a[0][3]
iterLast: 40 = a[4][2]
---
 */
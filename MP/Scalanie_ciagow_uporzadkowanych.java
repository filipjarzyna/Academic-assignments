// Filip Jarzyna - gr 6

/*
OGOLNA IDEA
Bierzemy pierwsze elementy z kazdej tablicy na MinHeap,
potem bierzemy element minimalny z heapa i wrzucamy go na output.
Wkladamy na heap nastepny element tablicy z ktorej pochodzil wyjety minimalny
Powtarzamy to az skoncza sie elementy w kazdej z tablic, czyli gdy heap bedzie pusty
*/

import java.util.Scanner;


public class Source {
    static int[][] arr; //tablica tablic podawanych na input

    public static class Node {
        int arrayIndex; //index tablicy
        int index; //index w tablicy
        int value; //wartosc

        public Node(int arrayIndex, int index) {
            this.arrayIndex = arrayIndex;
            this.index = index;
            this.value = arr[arrayIndex][index];
        }
    }

    public static class MinHeap {
        Node[] a; //tablica heapa
        int size; //aktualny rozmiar heapa

        public MinHeap(int sizeMax) { //konstruktor
            a = new Node[sizeMax];
            size = 0;
        }

        void swap(int i, int j) { //prosty swap
            Node temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }

        // rekurencyjna funkcja do naprawy kopca przesiewa w dol
        public void downHeap(int index) {
            int smallest = index;
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;

            // sprawdzamy czy lewe dziecko jest mniejsze niz obecny node
            if (leftChild < size && a[leftChild].value < a[smallest].value) {
                smallest = leftChild;
            }

            // sprawdzamy czy prawe dziecko jest mniejsze niz obecny node (lub lewe dziecko)
            if (rightChild < size && a[rightChild].value < a[smallest].value) {
                smallest = rightChild;
            }

            // jezeli najmniejszy element nie jest obecnym node zamieniamy je i kontynuujemy
            if (smallest != index) {
                swap(index, smallest);
                downHeap(smallest);
            }
        }

        public void Insert(Node add) {
            a[size] = add; //dodaje element na koniec heapa
            // index ostatniego elem
            int index = size;
            // porownuje element z rodzicem i swapuje jesli wartosc wieksza
            while (index > 0
                    && a[(index - 1) / 2].value > a[index].value) {
                swap(index, (index - 1) / 2);
                // przechodzi do kolejnego rodzica
                index = (index - 1) / 2;
            }
            size++; //ziwksza rozmiar
        }

        public Node popMin() {
            if (isEmpty()) return null;

            swap(0, --size);//ustawia min na koniec
            if (size != 0)
                downHeap(0); //ustawia nowy Min

            return a[size]; //zwraca minimalna wartosc
        }

        public boolean isEmpty() {
            return (size == 0);
        } //czy heap jest pusty
    }

    public static void MergeArrays(int totalSize, int[] len) {
        MinHeap heap = new MinHeap(totalSize); //min heap

        for (int i = 0; i < arr.length; i++) { //dodaje pierwsze wartosci z kazdej tablicy do heapa
            heap.Insert(new Node(i, 0));
        }

        StringBuilder output = new StringBuilder("");

        while (!heap.isEmpty()) {
            Node min = heap.popMin(); //wyciaga min z heapa
            output.append(min.value + " "); //wrzuca min na koncowy output
            if (min.index < len[min.arrayIndex] - 1) { //jesli jest jeszcze jakis element w danej tablicy
                heap.Insert(new Node(min.arrayIndex, min.index + 1)); //dodaje do heapa kojeny element tablicy

            }
        }

        System.out.println(output);
    }

    static public Scanner sc = new Scanner(System.in);

    public static void main(String[] args) {
        int sets = sc.nextInt();
        while (sets-- > 0) {
            int numOfArr = sc.nextInt();
            arr = new int[numOfArr][]; //wczytywanie
            int[] len = new int[numOfArr]; //tablica z dlugosciami
            int totalSize = 0;
            for (int i = 0; i < numOfArr; i++) {
                len[i] = sc.nextInt();
                totalSize += len[i];
                arr[i] = new int[len[i]];
            }
            for (int i = 0; i < numOfArr; i++) {
                for (int j = 0; j < len[i]; j++) {
                    arr[i][j] = sc.nextInt();
                }
            }

            MergeArrays(totalSize, len);
        }
    }
}

/*
INPUT
1
5
1 5 6 8 9
9
1 2 3 4 5
0 4 5 7 8 69
0 8 9 10 15 17 18 42
0 2 3 4 5 6 7 8 9
 */
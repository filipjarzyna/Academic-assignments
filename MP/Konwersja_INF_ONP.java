// Filip Jarzyna - gr 6

import java.util.Scanner;

/*
OGOLNA IDEA
Poczatkowo program wczytuje zestawy danych wedlug tresci zadania, nastepnie wywoluje odpowiednio konwersje na ONP lub INF.
Na poczatku funkcji konwertujacych sprawdza poprawnosc danych wejsciowychna podstawie automatu
przedstawionego w tresci zadania (w razie potrzeby wyswietla error i nie rozpoczyna konwersji).
Nastepnie na podstawie algorytmu przedstawionego na wykladzie, konwertuje dane wejsciowe na wybrana notacje i przekazuje je na wyjscie.
 */



class ArrayStack{ // stos rośnie w górę
    private int maxSize = 256; // rozmiar tablicy zawierającej stos
    private String[] Elem; // tablica zawierająca stos
    private int top; // indeks wierzchołka stosu


    public ArrayStack(int size) { // konstruktor - Create()
        Elem = new String[maxSize]; // tworzymy tablicę dla elementów
        top = maxSize; // na razie brak elementów (stos rośnie w górę)
    }

    public void push(String x) {
        if(!isFull())
            Elem[--top] = x; // zmniejszamy top, odkładamy element
    }

    public String pop(){
        if(!isEmpty()) {
            return Elem[top++];
        }

        return "#";
    }

    public String peek(){
        if ( !isEmpty() )
            return Elem[top];

        return "#";
    }

    public boolean isEmpty(){ // zwraca true, jeżeli stos pusty
        return (top == maxSize);
    }
    public boolean isFull(){ // zwraca true, jeżeli stos pełny
        return (top == 0);
    }
}

class ArrayStackInt {
    private int maxSize = 256; // rozmiar tablicy zawierającej stos
    private int[] Elem; // tablica zawierająca stos
    private int top; // indeks wierzchołka stosu

    public ArrayStackInt(int size) { // konstruktor - Create()
        // ustawiamy rozmiar tablicy
        Elem = new int[maxSize]; // tworzymy tablicę dla elementów
        top = maxSize; // na razie brak elementów (stos rośnie w górę)
    }

    public void push(int x) {
        if(!isFull()) Elem[--top] = x; // zmniejszamy top, odkładamy element
    }

    public int pop(){
        if(!isEmpty()) {
            return Elem[top++];
        }
        return -10;
    }

    public int peek() {
        if ( !isEmpty() )
            return Elem[top];
        return -10;
    }

    public boolean isEmpty() { // zwraca true, jeżeli stos pusty
        return (top == maxSize);
    }
    public boolean isFull() { // zwraca true, jeżeli stos pełny
        return (top == 0);
    }
}



public class Source {
    public static String arr = "";

    public static void Error(int c) {
        if (c == 0)
            System.out.println("ONP: error");
        else
            System.out.println("INF: error");
    }

    static int Priority(char x) { // ustawia priorytet dla x
        if (x == '(' || x == ')') {
            return 1;
        } else if (x == '!' || x == '~') {
            return 2;
        } else if (x == '^') {
            return 3;
        } else if (x == '*' || x == '/' || x == '%') {
            return  4;
        } else if (x == '+' || x == '-') {
            return  5;
        } else if (x == '>' || x == '<') {
            return 6;
        } else if (x == '&') {
            return 7;
        } else if (x == '|') {
            return 8;
        } else if (x == '=') {
            return  9;
        } else if (x <= 'z' && x >= 'a') {
            return 0;
        }
        return -2;
    }

    public static void INFtoONP() {

        int size = arr.length();

        // DO SPRAWDZANIA POPRAWNOSCI
        char stan = 0;
        ArrayStack nawiasy = new ArrayStack(size);
        int operat = 0;
        int operand = 0;
        ////


        ArrayStack stack = new ArrayStack(size);
        String output = "";

        //wczytujemy kolejne znaki z wejscia
        for (int i = 0; i < size; i++) {

            char c = arr.charAt(i);
            String cS = "" + c;
            int cP = Priority(c);


            // POPRAWNOSC SPRAWDZARKA NA PODSTAWIE GRAFU Z TRESCI ZADANIA
            if (stan == 0) {

                if (cP == 0) { //jesli operand
                    stan = 1;
                } else if (cP == 2) { //jesli jednoarg operat
                    stan = 2;
                } else if (c != '(') { // error dla tego stanu
                    Error(0);
                    return;
                }

            } else if (stan == 1) {

                if (cP > 2 && cP <= 9) { // operator dwuarg
                    stan = 0;
                } else if (c != ')') { // error dla stanu
                    Error(0);
                    return;
                }

            } else { //stan 2

                if (cP == 0) { //operand
                    stan = 1;
                } else if (c == '(') {
                    stan = 0;
                } else if (cP != 2) { //error dla stanu
                    Error(0);
                    return;
                }

            }


            //////

            // KONWERSJA ALGORYTM
            if (c == '(') {
                stack.push(cS);
                nawiasy.push("("); //spr
            } else if (c == ')') {
                if (nawiasy.pop().equals("#")) { //spr
                    Error(0);
                    return;
                }

                while (!stack.isEmpty() && !stack.peek().equals("(")) {
                    output += stack.pop();
                }

               stack.pop();

            } else if (cP == 0) {  // jest operandem
                output += c;
                operand++;// spr

            } else if (cP > 1) { //gdy jest operatorem
                if (cP != 2) operat++; //spr (bez jendoarg

                //gdy prawostronne laczny
                if (cP == 2 || cP == 3 || cP == 9) {

                    while (!stack.isEmpty() && Priority(stack.peek().charAt(0)) < cP && !stack.peek().equals("(")) {
                        output += stack.pop();
                    }
                    stack.push(cS);

                } else { //gdy lewostronnie laczny
                    while (!stack.isEmpty() && Priority(stack.peek().charAt(0)) <= cP && !stack.peek().equals("(")) {
                        output += stack.pop();
                    }
                    stack.push(cS);
                }
            }

        }

        // SPRAWDZARKA
        if (!nawiasy.isEmpty()) {
            Error(0);
            return;
        }
        /////

        // na koniec zwraca wszystko ze stosu na wyjscie
        while (!stack.isEmpty()) {
            output += stack.pop();
        }

        System.out.printf("ONP:");

        for (int i = 0; i < output.length(); i++) {
            System.out.printf(" %c", output.charAt(i));
        }
        System.out.printf("\n");

    }

    public static void ONPtoINF() {
        ArrayStack stack = new ArrayStack(arr.length());
        ArrayStackInt stackInt = new ArrayStackInt(arr.length()); // stos z priorytetami odpowiednich elementow stosu pierwszego

        // SPRAWDZARKA  (sprawdza czy liczba operandow zgadza sie z liczba operatorow oraz czy kolejnosc jest ok)
        int operand = 0;
        //

        //wczytujemy kolejne znaki z wejscia
        for (int i = 0; i < arr.length(); i++) {
            String first;
            String second;
            int firstP;
            int secondP;

            char c = arr.charAt(i);
            String cS = "" + c;
            int cP = Priority(c);

            // Sprawdzanie przypadkow wczytanego chara
            if (cP == 0) {  // jest operandem
                stack.push(cS);
                stackInt.push(0);
                operand++;
            } else if (cP > 1) { //gdy jest operatorem
                if (cP > 2 ) { //dla operatorow przyjmujacych dwa argumenty
                    if (--operand <= 0) { //spr
                        Error(1);
                        return;
                    }
                    // wyciagamy ze stosu dwa elementy wiemy ze sa conajmniej dwa z warunku wyzej
                    first = stack.pop();
                    firstP = stackInt.pop();
                    second = stack.pop();
                    secondP = stackInt.pop();

                    //PRAWOSTRONNIE DWUARG
                    if (cP == 9 || cP == 3) {
                        //odpowiednio dodajemy nawiasy w zaleznosci od priorytetu
                         // jesli nie operandy dodaj nawiasy odpowiednio
                            if (firstP > cP)
                                first = "(" + first + ")";

                            if (secondP >= cP)
                                second = "(" + second + ")";


                    } else { // LEWOSTORNNIE DWUARG
                        //odpowiednio dodajemy nawiasy w zaleznosci od priorytetu
                         // jesli nie operand dodaj nawiasy jesli trzeba
                            if (firstP >= cP )
                                first = "(" + first + ")";

                            if (secondP > cP)
                                second = "(" + second + ")";

                    }

                    stack.push(second + cS + first);
                    stackInt.push(cP); // priorytet operatora tego wyrazenia

                } else { //operatory o jednym argumencie
                    if (operand == 0) {
                        Error(1);
                        return;
                    }

                    firstP = stackInt.pop();
                    first = stack.pop();
                    if (firstP > cP) {
                        stack.push(cS + "(" + first + ")");
                        stackInt.push(cP);
                    } else {
                        stack.push(cS + first);
                        stackInt.push(cP);
                    }
                }
            }

        }

        if (operand != 1) {
            Error(1);
            return;
        }

        //SPRAWDZENIE
        String temp = stack.pop();
        if (temp.equals("#")) {
            Error(1);
            return;
        }

        System.out.printf("INF:");

        for (int i = 0; i < temp.length(); i++) {
            System.out.printf(" %c", temp.charAt(i));
        }
        System.out.printf("\n");

    }

    public static void main (String[] args) {
        Scanner scanner = new Scanner(System.in);
        //loop do wczytywania zestawow danych

        int count = Integer.parseInt(scanner.nextLine());

        while (count-- > 0) {
            arr = scanner.nextLine();
            int size = arr.length();
            StringBuilder cleaned = new StringBuilder();
            if (arr.charAt(0) == 'I') {
                for (int i = 0; i < size; i++) {
                    char c = arr.charAt(i);
                    if (Priority(c) != -2) {
                        cleaned.append(c);
                    }
                }
                arr = cleaned.toString();
                if (arr.isEmpty())
                    System.out.println("ONP: ");
                else
                    INFtoONP();
            } else if (arr.charAt(0) == 'O') {
                for (int i = 0; i < size; i++) {
                    char c = arr.charAt(i);
                    if (Priority(c) != -2 && c != '(' && c != ')') {
                        cleaned.append(c);
                    }
                }
                arr = cleaned.toString();
                if (arr.isEmpty())
                    System.out.println("INF: ");
                else
                    ONPtoINF();
            }

        }


    }
}

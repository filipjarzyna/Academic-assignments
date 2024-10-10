// Filip Jarzyna - gr. 6

import java.util.Scanner;
/*
OGOLNA IDEA
Aplikacja dzialajaca na kolejce priorytetowej MIN/MAX zawierajacej elementy typu Person,
 w ktorych priorytety sie powtarzaja i zrealizowanej jako drzewo BST
 */

class Stack {

    // A linked list node
    private class stackNode {

        Node data;
        int status;
        stackNode prev;
    }

    stackNode top;

    Stack() {
        this.top = null;
    }

    public void push(Node x) // insert at the beginning
    {
        stackNode temp = new stackNode();

        temp.data = x;
        temp.prev = top;
        top = temp;
    }

    public void push(Node x, int i) // insert at the beginning
    {
        stackNode temp = new stackNode();
        temp.data = x;
        temp.prev = top;
        temp.status = i;
        top = temp;
    }

    public int peekStatus() {
        return top.status;
    }

    public boolean isEmpty() {
        return top == null;
    }

    public Node peek() {
        if (!isEmpty()) {
            return top.data;
        }
        return null;
    }

    public Node pop() {
        if (top == null) {
            return null;
        }

        stackNode temp = top;
        top = (top).prev;
        return temp.data;
    }

    public void display() {
        if (top == null) {
            System.out.println("Empty");
        } else {
            stackNode temp = top;
            while (temp != null) {
                System.out.println(temp.data);
                temp = temp.prev;
            }
        }
    }
}

class Person {
    public int priority;
    public String name;
    public String surname;

    public Person(int priority, String name, String surname) {
        this.priority = priority;
        this.name = name;
        this.surname = surname;
    }

    // : 37 - Ola Nowicka
    @Override
    public String toString() {
        return (priority + " - " + name + " " + surname);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        return priority == ((Person) o).priority && ((Person) o).name.equals(name) && ((Person) o).surname.equals(surname);
    }
}

class Node {
    public Person info;
    public Node left;
    public Node right;

    public Node(Person info, Node left, Node right) {
        this.info = info;
        this.left = left;
        this.right = right;
    }

    public Node(Node copy) {
        info = copy.info;
        left = copy.left;
        right = copy.right;
    }
}


class Tree {
    public Node root; //korzen drzewa

    public void AddNew(Node add) {
        if (root == null) {
            root = add;
            return;
        }
        Node check = root; //sprawdzana galaz
        while (true) {
            if (check.info.priority <= add.info.priority) { //jesli wiekszy sprawdzamy prawa galaz
                if (check.right == null) {
                    check.right = add;
                    break;
                }
                check = check.right;
            } else { //jesli mniejszy lub rowny sprawdzamy lewa galaz
                if (check.left == null) {
                    check.left = add;
                    break;
                }
                check = check.left;
            }
        }
    }

    public Tree(Node root) {
        this.root = root;
    }

    //print w kolejnosci postorder

    public String PreorderIter() { // analogicznie jak inorder tylko w innej kolejnosci
        Node cur = root; //current element
        StringBuilder output = new StringBuilder(); //output
        Stack stack = new Stack(); //stos

        while (cur != null || !stack.isEmpty()) {
            if (cur != null) {
                stack.push(cur); // push na stos
                output.append(cur.info).append(", "); // cur na output
                cur = cur.left;
            } else {
                cur = stack.pop(); //jesli doszlismy do konca cofka
                cur = cur.right;
            }
        }

        return output.substring(0,output.length() - 2);
    }

    public String PostorderIter() {
        StringBuilder output = new StringBuilder(); //output
        Stack s1 = new Stack(); //stos
        Stack s2 = new Stack(); //stos
        s1.push(root);
        while (!s1.isEmpty()) {
            Node temp = s1.pop(); //popujemy z stosu 1 ma stos 2
            s2.push(temp);

            if (temp.left != null) { //jesli jest lewo push na sots1
                s1.push(temp.left);
            }
            if (temp.right != null) { // jesli jest prawo push na stos 1
                s1.push(temp.right);
            }
        }
        //dodaje wszystkie elementu z drugiego stosu do outputu
        while(!s2.isEmpty()) {
            output.append(s2.pop().info).append(", ");
        }

        return output.substring(0,output.length() - 2);
    }

    public String InorderIter() { //algorytm analogiczny do pokazanego na wykladzie
        Node cur = root;
        StringBuilder output = new StringBuilder();
        Stack stack = new Stack();

        while (cur != null || !stack.isEmpty()) { //dopoki sa elementy
            if (cur != null) {
                stack.push(cur); //push na stos
                cur = cur.left; //idziemy lewo
            } else {
                cur = stack.pop();
                output.append(cur.info).append(", "); //daje na output
                cur = cur.right; //idziemy prawo
            }
        }

        return output.substring(0,output.length() - 2);
    }

    public Node ClosestBigger(int priority) {
        if (root == null) {
            return null;
        }

        Node cur = root;
        Node closest = null;
        boolean found = false;

        while(cur != null) {
            if (cur.info.priority > priority) {
                closest = cur;
                cur = cur.left;
            } else {
                if (cur.info.priority == priority) {
                    found = true;
                }
                cur = cur.right;
            }

        }

        if (!found) return null;

        return closest;
    }

    public Node ClosestSmaller(int priority) {
        if (root == null) {
            return null;
        }

        Node cur = root;
        Node closest = null;
        boolean found = false;
        while (cur != null) {
            if (cur.info.priority >= priority) { //dla duplikatow rowniez idzie w prawo
                if (cur.info.priority == priority) {
                    found = true;

                }

                cur = cur.left;
            } else { // znaleziono mniejsze
                closest = cur; //update closest
                cur = cur.right;
            }
        }

        if (!found) return null;

        return closest;
    }


    public void DelMin() {
        if (root == null) return;
        if (root.left == null) { //jesli korzen jest najmniejszy
            System.out.printf("DEQUEMIN: %s\n", root.info);
            root = root.right;
            return;
        }
        Node cur = root.left; //szukane minimum
        Node prev = root; //rodzic

        //element najmniejszy bedzie elementem maksymalnie na lewo
        while (cur.left != null) {
            prev = cur;
            cur = cur.left;
        }

        System.out.printf("DEQUEMIN: %s\n", cur.info);
        prev.left = cur.right; //usuwa ostatni element ustawiajac lewa galaz rodzica na prawa galaz najmniejszego elementu
    }

    public void DelMax() {
        if (root == null) return;

        if (root.right == null) { //jesli korzen jest najwiekszy
            System.out.printf("DEQUEMAX: %s\n", root.info);
            root = root.left;
            return;
        }
        Node cur = root.right; //szukane max
        Node prev = root; //rodzic

        //element najwiekszy bedzie elementem maksymalnie na prawo
        while (cur.right != null) {
            prev = cur;
            cur = cur.right;
        }

        System.out.printf("DEQUEMAX: %s\n", cur.info);
        prev.right = cur.left; //usuwa ostatni(najwiekszy) element ustawiajac prawa galaz rodzica na lewa galaz najwiekszego elementu
    }

    public boolean Del(int priority) {
        Node cur = root; //wskaznik na aktualna node
        Node parent = null; //rodzic wskaznika

        while (cur != null) {
            if (cur.info.priority > priority) { //szukamy mniejszego
                parent = cur;
                cur = cur.left;
            } else if (cur.info.priority < priority) { //szukamy wiekszego
                parent = cur;
                cur = cur.right;
            } else { // ==
                //sprawdzanie dla duplikatow ktorych nie powinno byc z tresci zadania
                if (cur.right != null) {
                    Node temp = cur.right;
                    Node dupParent = cur;
                    //szuka duplikatu ktory powinien byc najmniejszym elementem z prawej current
                    while (temp.left != null) {
                        dupParent = temp;
                        temp = temp.left;
                    }

                    if (temp.info.priority == cur.info.priority) {
                        dupParent.left = null;
                        return true;
                    }
                }

                if (parent == null) { //jesli jestesmy w root
                    if (cur.right == null) { //robimy to samo jak nizej tylko dla roota
                        root = cur.left;
                    } else {
                        if (cur.left == null) {
                            root = cur.right;
                        } else { //usuwany ma dwoch potomkow
                            Node temp = cur.right;
                            parent = cur;
                            while (temp.left != null) { //szuka najmniejszego z wiekszych od cur
                                parent = temp;
                                temp = temp.left;
                            }
                            if (parent == cur) {
                                SwapNodes(cur, temp);
                                cur.right = temp.right;
                            } else {
                                SwapNodes(cur, temp);
                                parent.left = temp.right;
                            }
                        }
                    }
                } else { //gdy jest rodzic
                    if (parent.right != null && cur.info.priority == parent.right.info.priority) {
                        if (cur.right == null) { //jesli ma jedno dziecko cur
                            parent.right = cur.left;
                        } else {
                            if (cur.left == null) {
                                parent.right = cur.right;
                            } else { //usuwany ma dwoch potomkow
                                Node temp = cur.right;
                                parent = cur;
                                while (temp.left != null) { //szuka najmniejszego z wiekszych od cur
                                    parent = temp;
                                    temp = temp.left;
                                }
                                if (parent == cur) {
                                    SwapNodes(cur, temp);
                                    cur.right = temp.right;
                                } else {
                                    SwapNodes(cur, temp);
                                    parent.left = temp.right;
                                }
                            }
                        }
                    } else { //cur jest lewym potomkiem
                        if (cur.right == null) { //jesli ma jedno dziecko cur
                            parent.left = cur.left;
                        } else {
                            if (cur.left == null) {
                                parent.left = cur.right;
                            } else { //usuwany ma dwoch potomkow
                                Node temp = cur.right;
                                parent = cur;
                                while (temp.left != null) { //szuka najmniejszego z wiekszych od cur
                                    parent = temp;
                                    temp = temp.left;
                                }
                                if (parent == cur) {
                                    SwapNodes(cur, temp);
                                    cur.right = temp.right;
                                } else {
                                    SwapNodes(cur, temp);
                                    parent.left = temp.right;
                                }
                            }
                        }
                    }
                }
                return true;
            }
        }

        return false;
    }

    public int Height(Node cur) {
        if (cur == null) {
            return 0;
        }

        int hL = Height(cur.left); //liczy wysokosc lewej galezi
        int hR = Height(cur.right); //wysokosc prawej galezi

        return Integer.max(hL, hR) + 1; //zwraca wieksza wysokosc
    }

    private void SwapNodes(Node n1, Node n2) {
        Person info = n1.info;// prosty swap ktory zamienia tylko dane, nie zamienia miejscami nod
        n1.info = n2.info;//
        n2.info = info;//
    }

}


public class Source {

    public static Node PostToBST(Person arr[], int L, int R) {

        if (L > R) return null;

        //najbardziej po prawej root
        Node node = new Node(arr[R], null, null);
        int rootPriority = arr[R].priority;
        int i; //szuka pierwszego mniejszego
        for (i = R - 1; i >= L; i--) {
            if (arr[i].priority <= rootPriority) {
                break;
            }
        }
        int j; //szuka pierwszego wiekszego
        for (j = R - 1; j >= L; j--) {
            if (arr[j].priority >= rootPriority) {
                break;
            }//
        }//

        node.left = PostToBST(arr, L, i); //ustawia lewa node analogicznie
        node.right = PostToBST(arr, i + 1, j);  //ustawia prawa node i rekurencyjnie powtarza algorytm

        return node;
    }

    public static Node PreToBST(Person arr[], int L, int R) {

        if (L > R) return null;
        //najbardziej po prawej root
        Node node = new Node(arr[L], null, null);
        int rootPriority = arr[L].priority;
        int i; //szuka pierwszego mniejszego
        for (i = L + 1; i <= R; i++) {
            if (arr[i].priority <= rootPriority) {
                break;
            }
        }

        int j; //szuka pierwszego wiekszego
        for (j = L + 1; j <= R; j++) {
            if (arr[j].priority > rootPriority) {
                break;
            }
        }

        node.right = PreToBST(arr, j, R); //ustawia prawa node i rekurencyjnie powtarza algorytm
        node.left = PreToBST(arr, i, j - 1); //ustawia lewa node analogicznie

        return node;
    }


    public static Scanner sc = new Scanner(System.in);

    public static void main(String[] args) {

        // wczytywanie wedlug warunkow zadania
        int sets = sc.nextInt();
        for (int j = 1; j <= sets; j++) {
            Tree tree = new Tree(null);
            System.out.printf("ZESTAW %d\n", j);
            int count = sc.nextInt();
            while (count-- > 0) {
                String str = sc.next();
                if (str.equals("CREATE")) {
                    String order = sc.next();
                    int n = sc.nextInt();
                    Person[] arr = new Person[n];
                    for (int i = 0; i < n; i++) {
                        arr[i] = new Person(sc.nextInt(), sc.next(), sc.next());
                    }

                    if (order.equals("POSTORDER")) {
                        tree.root = PostToBST(arr, 0, n - 1);
                    } else if (order.equals("PREORDER")) {
                        tree.root = PreToBST(arr, 0, n - 1);
                    }
                } else if (str.equals("ENQUE")) {
                    tree.AddNew(new Node(new Person(sc.nextInt(), sc.next(), sc.next()), null, null));
                } else if (str.equals("DEQUEMAX")) {
                    tree.DelMax();
                } else if (str.equals("DEQUEMIN")) {
                    tree.DelMin();
                } else if (str.equals("NEXT")) {
                    int prio = sc.nextInt();
                    Node temp = tree.ClosestBigger(prio);
                    if (temp == null) {
                        System.out.printf("NEXT %d: BRAK\n", prio);
                    } else {
                        System.out.printf("NEXT %d: %s\n", prio, temp.info);
                    }
                } else if (str.equals("PREV")) {
                    int prio = sc.nextInt();
                    Node temp = tree.ClosestSmaller(prio);
                    if (temp == null) {
                        System.out.printf("PREV %d: BRAK\n", prio);
                    } else {
                        System.out.printf("PREV %d: %s\n", prio, temp.info);
                    }
                } else if (str.equals("PREORDER")) {
                    System.out.printf("PREORDER: %s\n", tree.PreorderIter());
                } else if (str.equals("INORDER")) {
                    System.out.printf("INORDER: %s\n", tree.InorderIter());
                } else if (str.equals("POSTORDER")) {
                    System.out.printf("POSTORDER: %s\n", tree.PostorderIter());
                } else if (str.equals("HEIGHT")) {
                    System.out.printf("HEIGHT: %d\n", tree.Height(tree.root) - 1);
                } else if (str.equals("DELETE")) {
                    int prio = sc.nextInt();
                    if (!tree.Del(prio)) {
                        System.out.printf("DELETE %d: BRAK\n", prio);
                    }
                }
            }

        }
    }
}
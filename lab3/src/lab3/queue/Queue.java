package lab3.queue;

public class Queue<T> {

    private class Node {
        T item;
        Node next;

        Node(T item) {
            this.item = item;
            this.next = null;
        }
    }

    private int size = 0;
    private Node head;
    private Node tail;

    public void add(T element) {
        if (size == 0) {
            head = new Node(element);
            tail = head;
        } else {
            tail.next = new Node(element);
            tail = tail.next;
        }
        size++;
    }

    public T get() {
        if (size == 0) {
            return null;
        }
        Node temp = head;
        head = head.next;
        size--;
        return temp.item;
    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

}

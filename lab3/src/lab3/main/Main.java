package lab3.main;

import lab3.animalClasses.*;
import lab3.queue.Queue;
import lab3.util.Utilities;

public class Main {
    public static void main(String[] args) {
        try {
            executeTask();
        }
        catch(Exception e) {
            e.printStackTrace();
            System.exit(2);
        }
    }

    public static void executeTask() {
        int upperBound = Utilities.getUpperBoundFromUser();
        if(upperBound == 0){
            System.out.println("Wrong number of class.");
            return;
        }
        System.out.print("\n");
        int lowerBound = Utilities.getLowerBoundFromUser();
        if(lowerBound == 0){
            System.out.println("Wrong number of class.");
            return;
        }
        if (lowerBound < upperBound) {
            System.out.println("Wrong bounds set.");
            return;
        }
        Queue<Animals> upperBoundQueue = produce(Utilities.getClassByNumber(upperBound));
        Queue<Animals> queue = produce(Utilities.getClassByNumber(upperBound));

        System.out.println("---------------------");
        System.out.println("Upper bound queue is:");
        while (!queue.isEmpty()) {
            System.out.println(queue.get().toString());
        }
        queue = consume(upperBoundQueue, Utilities.getClassByNumber(lowerBound));
        System.out.println("---------------------");
        System.out.println("Lower bound queue is:");
        while (!queue.isEmpty()) {
            System.out.println(queue.get().toString());
        }
    }

    public static Queue<Animals> produce(Class<? extends Animals> upperBound) {
        Queue<Animals> queue = new Queue<>();
        if (upperBound.isAssignableFrom(Animals.class)) {
            queue.add(new Animals());
        }
        if (upperBound.isAssignableFrom(Chordal.class)) {
            queue.add(new Chordal());
        }
        if (upperBound.isAssignableFrom(Mammals.class)) {
            queue.add(new Mammals());
        }
        if (upperBound.isAssignableFrom(Predatory.class)) {
            queue.add(new Predatory());
        }
        if (upperBound.isAssignableFrom(Feline.class)) {
            queue.add(new Feline());
        }
        if (upperBound.isAssignableFrom(Cat.class)) {
            queue.add(new Cat());
        }
        return queue;
    }

    public static Queue<Animals> consume(Queue<Animals> queue, Class<? super Cat> lowerBound) {
        Queue<Animals> lowerBoundQueue = new Queue<>();
        while (!queue.isEmpty()) {
            Animals animal = queue.get();
            if (animal.getClass().isAssignableFrom(lowerBound)) {
                lowerBoundQueue.add(animal);
            }
        }
        return lowerBoundQueue;
    }
}

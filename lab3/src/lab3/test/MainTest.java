package lab3.test;

import lab3.animalClasses.*;
import lab3.main.Main;
import lab3.queue.Queue;
import lab3.util.Utilities;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

class MainTest {

    @Test
    void getClassByNumber() {
        assertEquals(Animals.class, Utilities.getClassByNumber(1));
        assertEquals(Chordal.class, Utilities.getClassByNumber(2));
        assertEquals(Mammals.class, Utilities.getClassByNumber(3));
        assertEquals(Predatory.class, Utilities.getClassByNumber(4));
        assertEquals(Feline.class, Utilities.getClassByNumber(5));
        assertEquals(Cat.class, Utilities.getClassByNumber(6));

        assertEquals(Animals.class, Utilities.getClassByNumber(7));
        assertEquals(Animals.class, Utilities.getClassByNumber(0));
        assertEquals(Animals.class, Utilities.getClassByNumber(-34));
    }

    @Test
    void produceTest() {
        Queue<Animals> queue = Main.produce(Animals.class);

        assertEquals(queue.get().getClass(), Animals.class);
        assertEquals(queue.get().getClass(), Chordal.class);
        assertEquals(queue.get().getClass(), Mammals.class);
        assertEquals(queue.get().getClass(), Predatory.class);
        assertEquals(queue.get().getClass(), Feline.class);
        assertEquals(queue.get().getClass(), Cat.class);
        assertTrue(queue.isEmpty());

        queue = Main.produce(Predatory.class);
        assertEquals(queue.get().getClass(), Predatory.class);
        assertEquals(queue.get().getClass(), Feline.class);
        assertEquals(queue.get().getClass(), Cat.class);
        assertTrue(queue.isEmpty());
    }

    @Test
    void consume() {
        Queue<Animals> queue = Main.produce(Chordal.class);
        Queue<Animals> resultQueue = Main.consume(queue, Predatory.class);

        assertEquals(resultQueue.get().getClass(), Chordal.class);
        assertEquals(resultQueue.get().getClass(), Mammals.class);
        assertEquals(resultQueue.get().getClass(), Predatory.class);
        assertTrue(resultQueue.isEmpty());
    }
}
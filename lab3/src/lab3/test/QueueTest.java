package lab3.test;

import lab3.queue.Queue;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class QueueTest {

    @Test
    void testAddGetSizeMethods() {
        Queue<Integer> queue = new Queue<>();
        queue.add(1);
        queue.add(2);
        queue.add(3);
        assertEquals(3, queue.size());
        for(int i = 1;i<4;i++){
            assertEquals(i, queue.get());
        }
    }

    @Test
    void isEmpty() {
        Queue<Integer> queue = new Queue<>();
        assertTrue(queue.isEmpty());

        queue.add(1);
        queue.add(1);
        queue.get();
        queue.get();

        assertTrue(queue.isEmpty());
    }
}
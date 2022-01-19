package com.company.tasks;

import java.util.Random;
import java.util.concurrent.BlockingQueue;

public class WritingTask implements Runnable {

    private BlockingQueue<String> queue;
    private final String[] strings = new String[]{"hello", "world", "something", "phrase", "how are you"};

    public WritingTask(BlockingQueue<String> queue) {
        this.queue = queue;
    }

    @Override
    public void run() {
        Random random = new Random();
        while (true) {
            try {
                Thread.sleep(2000 + random.nextInt(3000));
                queue.put(strings[random.nextInt(strings.length)]);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

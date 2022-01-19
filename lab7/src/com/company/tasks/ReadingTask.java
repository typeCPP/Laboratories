package com.company.tasks;

import java.util.Random;
import java.util.concurrent.BlockingQueue;

public class ReadingTask implements Runnable{

    private BlockingQueue<String> queue;

    public ReadingTask(BlockingQueue<String> queue) {
        this.queue = queue;
    }

    @Override
    public void run() {
        Random random = new Random();
        while (true) {
            try {
                Thread.sleep(1000 + random.nextInt(2000));
                System.out.println(Thread.currentThread().getName() + " got " + queue.take());
                System.out.println("-----------------------------");
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

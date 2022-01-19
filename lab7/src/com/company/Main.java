package com.company;

import com.company.factories.ReadingThreadFactory;
import com.company.factories.WritingThreadFactory;
import com.company.tasks.ReadingTask;
import com.company.tasks.WritingTask;

import java.util.concurrent.*;

public class Main {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Wrong number of arguments.");
            System.exit(1);
        }
        int threadsCount = 0;
        try {
            threadsCount = Integer.parseInt(args[0]);
        } catch (NumberFormatException error) {
            error.printStackTrace();
            System.exit(2);
        }
        if (threadsCount < 1) {
            System.out.println("Wrong number of threads.");
            System.exit(3);
        }

        executeTask(threadsCount);
    }

    public static void executeTask(int threadsCount) {
        ExecutorService writingService = Executors.newFixedThreadPool(threadsCount, new WritingThreadFactory());
        ExecutorService readingService = Executors.newFixedThreadPool(threadsCount, new ReadingThreadFactory());

        BlockingQueue<String> queue = new LinkedBlockingQueue<>(threadsCount);

        WritingTask writingTask = new WritingTask(queue);
        ReadingTask readingTask = new ReadingTask(queue);

        for (int i = 0; i < threadsCount; i++) {
            writingService.execute(writingTask);
            readingService.execute(readingTask);
        }
    }
}

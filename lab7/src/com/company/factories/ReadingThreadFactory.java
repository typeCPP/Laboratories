package com.company.factories;

import java.util.concurrent.ThreadFactory;

public class ReadingThreadFactory implements ThreadFactory {
    private static int num = 0;
    @Override
    public Thread newThread(Runnable r) {
        ++num;
        return new Thread(r, "readingThread-" + num);
    }
}

package com.company.factories;

import java.util.concurrent.ThreadFactory;

public class WritingThreadFactory implements ThreadFactory {
    private static int num = 0;

    @Override
    public Thread newThread(Runnable r) {
        ++num;
        return new Thread(r, "writingThread-" + num);
    }
}

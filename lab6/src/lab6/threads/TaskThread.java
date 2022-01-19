package lab6.threads;

import java.util.Random;

public class TaskThread implements Runnable {

    static final Object mutex = new Object();
    private boolean needsRestart = false;
    private boolean needsStop = false;
    ThreadStatus status = ThreadStatus.RUNNING;
    double value = 0.5;

    Runnable daemonTask = () -> {
        Random random = new Random();
        while (!Thread.currentThread().isInterrupted()) {
            synchronized (mutex) {
                while (status != ThreadStatus.RUNNING) {
                    try {
                        mutex.wait();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                status = ThreadStatus.values()[random.nextInt(4)];
                System.out.println("Current status is " + status + ".");
                printIfRunning();
                mutex.notify();
            }
            try {
                Thread.sleep(3000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    };

    public void calculate() {
        value = Math.sin(value) * Math.E;
    }

    private void resetValue() {
        value = 0.5;
        needsRestart = false;
    }

    private void printIfRunning() {
        if (status == ThreadStatus.RUNNING) {
            System.out.println("value = " + value);
            System.out.println("--------------------------------------------");
        }
    }

    public void restart() {
        System.out.println("Restarting.");
        System.out.println("--------------------------------------------");
        status = ThreadStatus.RUNNING;
        needsRestart = true;
    }

    public void stopRunning() {
        System.out.println("Stopping.");
        System.out.println("--------------------------------------------");
        needsStop = true;
    }

    @Override
    public void run() {
        Thread daemon = new Thread(daemonTask);
        daemon.setDaemon(true);
        daemon.start();
        while (!needsStop) {
            if (needsRestart) {
                resetValue();
            }
            calculate();
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

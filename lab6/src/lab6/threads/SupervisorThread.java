package lab6.threads;

public class SupervisorThread implements Runnable {
    TaskThread taskThread;

    public SupervisorThread(TaskThread taskThread) {
        this.taskThread = taskThread;
    }

    @Override
    public void run() {
        while (taskThread.status != ThreadStatus.FATAL_ERROR) {
            synchronized (TaskThread.mutex) {
                while (taskThread.status == ThreadStatus.RUNNING) {
                    try {
                        TaskThread.mutex.wait();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                checkThreadStatus();
            }
        }
    }

    private void checkThreadStatus() {
        switch (taskThread.status) {
            case UNKNOWN, STOPPING -> {
                taskThread.restart();
                TaskThread.mutex.notify();
            }
            case FATAL_ERROR -> {
                taskThread.stopRunning();
                TaskThread.mutex.notify();
            }
        }
    }
}

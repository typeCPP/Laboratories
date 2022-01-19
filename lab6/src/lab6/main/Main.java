package lab6.main;

import lab6.threads.SupervisorThread;
import lab6.threads.TaskThread;

public class Main {

    public static void main(String[] args) {
        TaskThread taskThread = new TaskThread();
        SupervisorThread supervisorThread = new SupervisorThread(taskThread);
        new Thread(taskThread).start();
        new Thread(supervisorThread).start();
    }
}

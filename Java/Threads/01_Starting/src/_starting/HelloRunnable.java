package _starting;

/**
 *
 * @author batas2
 */
public class HelloRunnable implements Runnable {

    public void run() {
        for (int i = 0; i < 5; i++) {
            System.out.println("Hello from a RunnableThread!");
        }
    }
}

package _starting;

import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author batas2
 */
public class HelloRunnable implements Runnable {

    public void run() {
        for (int i = 0; i < 5; i++) {
            try {
                System.out.println("Hello from a RunnableThread!");
                Thread.sleep(1000);
            } catch (InterruptedException ex) {
                Logger.getLogger(HelloRunnable.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
}

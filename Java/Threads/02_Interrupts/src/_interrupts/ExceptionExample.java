/*
 * 
 * 
 */
package _interrupts;

/**
 *
 * @author batas2
 */
public class ExceptionExample implements Runnable {

    @Override
    public void run() {
        for (int i = 1; i <= 10; i++) {
            System.out.println(i * i);
            try {
                Thread.sleep(1000);
            } catch (InterruptedException ex) {
                System.out.println("Wątek " + toString() + " został przerwany");
                System.out.println(ex);
                return;
            }
        }
    }

    @Override
    public String toString() {
        return "ExceptionExample";
    }
}

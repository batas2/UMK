/*
 * 
 * 
 */
package _interrupts;

/**
 *
 * @author batas2
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Thread et = new Thread(new ExceptionExample());
        et.start();

        try {
            Thread.sleep(5000);
        } catch (InterruptedException ex) {
            System.out.print(ex);
        }

        et.interrupt();

        Thread it = new Thread(new InterruptedExample());
        it.start();

        try {
            Thread.sleep(5000);
        } catch (InterruptedException ex) {
            System.out.print(ex);
        }

        it.interrupt();
    }
}

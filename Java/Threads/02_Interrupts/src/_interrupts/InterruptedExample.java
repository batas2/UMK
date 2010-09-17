/*
 * 
 * 
 */
package _interrupts;

/**
 *
 * @author batas2
 */
public class InterruptedExample implements Runnable {

    @Override
    public void run() {
        for (int i = 1; i <= 10; i++) {
            System.out.println(i * i);
            myExp();
            if (Thread.interrupted()) {
                System.out.println("Wątek " + toString() +" został przerwany");
                return;
            }
        }
    }

    private void myExp() {
        for (int i = 0; i < Integer.MAX_VALUE / 100; i++) {
            Math.exp(i);
        }
    }

    @Override
    public String toString(){
        return "InterruptedExample";
    }
}

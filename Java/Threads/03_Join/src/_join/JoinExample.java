/*
 * 
 * 
 */
package _join;

/**
 *
 * @author batas2
 */
public class JoinExample implements Runnable {

    @Override
    public void run() {
        for (int i = 1; i <= 10; i++) {
            System.out.println(i * i);
            try {
                Thread.sleep(1000);
            } catch (InterruptedException ex) {
                return;
            }
        }
    }
}

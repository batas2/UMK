/*
 * 
 * 
 */
package _starting;

/**
 *
 * @author batas2
 */
public class HelloThread extends Thread {

    @Override
    public void run() {
        for (int i = 0; i < 5; i++) {
            System.out.println("Hello from a thread!");
        }
    }
}

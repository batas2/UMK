/*
 * 
 * 
 */
package _starting;

/**
 *
 * @author batas2
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {


        Thread runable = new Thread(new HelloRunnable());
        Thread thread = new HelloThread();

        runable.setDaemon(true);
        runable.start();
        thread.start();

    }
}

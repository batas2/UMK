package _interference;

/**
 *
 * @author batas2
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Counter c = new Counter();
        Thread[] t = new Thread[10];

        for (int i = 0; i < 10; i++) {
            t[i] = new Thread(new InterferenceThread(c));

        }
        for (int i = 0; i < 10; i++) {
            t[i].start();
        }

        for (int i = 0; i < 10; i++) {
            try {
                t[i].join();
            } catch (InterruptedException ex) {
                System.out.print(ex);
            }
        }

        System.out.println(c.value());
    }
}

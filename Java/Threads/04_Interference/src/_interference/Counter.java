package _interference;

/**
 *
 * @author batas2
 */
public class Counter {

    private long c = 0;

    public synchronized void increment() {
        System.out.println("in " + Thread.currentThread().getName());
        c++;
        try {
            Thread.sleep(100);
        } catch (InterruptedException ex) {
            System.out.print(ex);
        }
        System.out.println("out " + Thread.currentThread().getName());
    }
    
//    public void increment() {
//        synchronized (this) {
//            System.out.println("in " + Thread.currentThread().getName());
//            c++;
//            try {
//                Thread.sleep(100);
//            } catch (InterruptedException ex) {
//                System.out.print(ex);
//            }
//            System.out.println("out " + Thread.currentThread().getName());
//        }
//    }

    public long value() {
        return c;
    }
}

/*
 * Open source
 * Author: batas2, http://www.batas2.boo.pl/
 */
package zad2;

import java.util.LinkedList;

/**
 *
 * @author batas2
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws InterruptedException {
        LinkedList<Thread> l = new LinkedList<Thread>();
        DirHistory dh = new DirHistory();

        for (int i = 1; i < args.length; i++) {
            l.add(new Thread(new DirThread(args[0], args[i], dh)));
        }

        for (Thread t : l) {
            t.start();
        }
    }
}

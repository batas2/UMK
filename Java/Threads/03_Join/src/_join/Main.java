/*
 * 
 * 
 */

package _join;

import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author batas2
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Thread t = new Thread(new JoinExample());

        t.start();
        try {
            t.join();
        } catch (InterruptedException ex) {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        }
        System.out.println("Wątek zakonczyl prace!");
    }

}

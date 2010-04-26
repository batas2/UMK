/*
 * 
 * 
 */

package _join;

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
        
        System.out.println("Wątek zakonczyl prace!");
    }

}

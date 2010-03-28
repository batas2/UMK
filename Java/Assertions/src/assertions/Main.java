/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package assertions;

/**
 *
 * @author batas2
 */
public class Main {

    static void asserion1(int v) {
        if (v % 3 == 0) {
            System.out.println("Reszta z dzielnia: 0");
        } else if (v % 3 == 1) {
            System.out.println("Reszta z dzielnia: 1");
        } else {
            assert v % 4 == 2 : v;
            System.out.println("Reszta z dzielnia: 2");
        }
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        asserion1(5);
    }
}

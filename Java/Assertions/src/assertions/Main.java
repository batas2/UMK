package assertions;

import java.io.*;
import java.util.*;

/**
 *
 * @author batas2
 */
enum CarType {

    Sedan, Coupe, Combi, Hatchback
}

public class Main {

    static void asserionIf(int v) {
        if (v % 3 == 0) {
            System.out.println("Reszta z dzielnia: 0");
        } else if (v % 3 == 1) {
            System.out.println("Reszta z dzielnia: 1");
        } else {
            assert v % 4 == 2 : v;
            System.out.println("Reszta z dzielnia: 2");
        }
    }

    static void assertionSwitchA(CarType car) {
        switch (car) {
            case Combi:
                System.out.println("Mamy Combi!");
                break;
            case Coupe:
                System.out.println("Mamy Coupe!");
                break;
            case Sedan:
                System.out.println("Mamy Sedan!");
                break;
            case Hatchback:
                System.out.println("Mamy Hatchback!");
                break;
            default:
                assert false : car;
//            default:
//                throw new AssertionError(car);
        }
    }

    static String assertionSwitchB(CarType car) {
        switch (car) {
            case Combi:
                return "Mamy Combi!";
            case Coupe:
                return "Mamy Coupe!";
            case Sedan:
                return "Mamy Sedan!";
            case Hatchback:
                return "Mamy Hatchback!";
//            default:
//                assert false : car;
            default:
                throw new AssertionError(car);
        }

    }
    static void assertionFlow() {
        int[] b = {1, 2, 3, 4, 5, -1};
        for (int i = 0; i < b.length; i++) {

            //Cos tu robimy

            if (b[i] < 0) {
                return;
            }
        }
        assert false;
    }

    static void assertionArray(final int[] array) {
        // Inner class that saves state and performs final consistency check
        class DataCopy {

            private int[] arrayCopy;

            DataCopy() {
                arrayCopy = (int[]) array.clone();
            }

            boolean isConsistent() {
                return Arrays.equals(array, arrayCopy);
            }
        }

        DataCopy copy = null;
        // Always succeeds; has side effect of saving a copy of array
        assert ((copy = new DataCopy()) != null);

        Arrays.sort(array);

        // Ensure array has same ints in same order as before manipulation.
        assert copy.isConsistent();
    }

    public static int assertionParameters(int a, int b) {
        if (a < 0 || b < 0) {
            throw new IllegalArgumentException("Oba parametry musza byc wieksze od 0");
        }
        return a + b;
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {

//        assert Expression1 ;
        //    assert Expression1 : Expression2 ;
        //assert false : "blad";
        //asserionIf(5);
//        assertionSwitchA(CarType.Hatchback);
//        assertionSwitchB(CarType.Sedan);
//        assertionFlow();
//        assertionArray(new int[]{5, 4, 2, 4});
//        assertionParameters(5, 8);


        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String line = new String();
        int n = 0;
        try {
            line = in.readLine();
            n = Integer.parseInt(line);
        } catch (IOException e) {
            System.out.print(e);
        }

        if (n == 0) {
            throw new RuntimeException();
        }

        Integer[] tab = new Integer[n];

        try {
            for (int i = 0; i < n; i++) {
                line = in.readLine();
                int v = Integer.parseInt(line);
                tab[i] = v;
            }

        } catch (IOException e) {
            System.out.print(e);
        }

        Arrays.sort(tab, Collections.reverseOrder());

        assert tab[2] < tab[3] : "nie ma";

    }
}

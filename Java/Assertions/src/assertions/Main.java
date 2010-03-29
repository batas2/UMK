/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package assertions;

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
            assert v % 3 == 2 : v;
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

    static void asserionFlow() {
        int[] b = {1, 2, 3, 4, 5, -1};
        for (int i = 0; i < b.length; i++) {

            //Cos tu robimy

            if (b[i] < 0) {
                return;
            }
        }
        assert false;
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        asserionIf(5);
        assertionSwitchA(CarType.Hatchback);
        assertionSwitchB(CarType.Sedan);
        asserionFlow();
    }
}

/*
 * Open source
 * Author: batas2, http://www.batas2.boo.pl/
 */
package randomargs;

import java.util.*;
import randomargs.*;
import randomargs.StringComparator;

/**
 *
 * @author batas2
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void TrimList(List<String> l) {
        for (int i = 0; i < l.size(); i++) {
            l.set(i, l.get(i).trim());
        }
    }

    public static int compare(Object o1, Object o2) {
        String a = String.valueOf(o1);
        String b = String.valueOf(o2);

        return a.compareTo(b);
    }

    public static boolean FindDups(String[] args) {
        SortedSet<String> s = new TreeSet<String>(new StringComparator());
        for (String a : args) {
            if (!s.add(a)) {
                System.out.println(a + " to jest duplikat");
            }
        }
        return false;
    }

    public static void main(String[] args) {
        List<String> l = Arrays.asList(args);
        Collections.shuffle(l);
        for (int i = 0; i < l.size(); i++) {
            System.out.println(l.get(i));
        }

        System.out.println("Trimowane parametry: ");
        TrimList(l);
        for (int i = 0; i < l.size(); i++) {
            System.out.println(l.get(i));
        }
        FindDups(args);
    }
}

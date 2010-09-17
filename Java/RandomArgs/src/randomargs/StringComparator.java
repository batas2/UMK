/*
 * Open source
 * Author: batas2, http://www.batas2.boo.pl/
 */
package randomargs;

import java.util.Comparator;

/**
 *
 * @author batas2
 */
public class StringComparator implements Comparator {

    public int compare(Object o1, Object o2) {
        String a = String.valueOf(o1);
        String b = String.valueOf(o2);
        return a.compareToIgnoreCase(b);
    }
}

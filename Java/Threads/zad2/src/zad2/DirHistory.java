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
public class DirHistory {

    private LinkedList<String> l = null;

    public DirHistory() {
        l = new LinkedList<String>();
    }

    public synchronized boolean Check(String s) {
        if (l.indexOf(s) == -1) {
            l.add(s);
            return true;
        } else {
            return false;
        }
    }
}

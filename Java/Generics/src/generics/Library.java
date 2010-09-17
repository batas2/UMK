/*
 * Open source
 * Author: batas2, http://www.batas2.boo.pl/
 */
package generics;

import Media.*;
import java.util.*;

/**
 *
 * @author batas2
 */
public class Library<T extends Media> {

    private LinkedList<T> _list;

    public Library() {
        _list = new LinkedList<T>();
    }

    public void addMedia(T item) {
        _list.add(item);
    }

    public T getLast() {
        return _list.pollLast();
    }

    public int Size() {
        return _list.size();
    }
}

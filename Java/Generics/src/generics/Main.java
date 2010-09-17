/*
 * Open source
 * Author: batas2, http://www.batas2.boo.pl/
 */
package generics;

import Media.*;

/**
 *
 * @author batas2
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Book b = new Book("Ksiazka");
        Cd c = new Cd("Cd");
        Video v = new Video("Wideo");

        Library<Media> l = new Library<Media>();

        l.addMedia(b);
        l.addMedia(c);
        l.addMedia(v);

        l.addMedia(new Cd("Płyta 2"));
        l.addMedia(new Book("Jakas ksiazka"));

        int n = l.Size();
        for (int i = 0; i < n; i++) {
            System.out.println(l.getLast().getClass().toString());
        }


    }
}

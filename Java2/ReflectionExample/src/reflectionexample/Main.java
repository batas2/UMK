/*
 * Autor: Bartosz Frąckowiak
 * E-mail: batas2@boo.pl
 * WWW: www.batas2.boo.pl
 */
package reflectionexample;

import java.lang.reflect.Constructor;
import java.lang.reflect.Method;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLClassLoader;

/**
 *
 * @author batas2
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        URL url = null;
        try {
            url = new URL("file: " + args[0] + args[1] + ".class");
        } catch (MalformedURLException ex) {
            System.out.println(ex);
            return;
        }

        try {
            URLClassLoader cl = new URLClassLoader(new URL[]{url});
            Class<?> c = cl.loadClass(args[1]);

            Constructor<?> con = c.getConstructors()[0];
            Object o = con.newInstance();
            Method privateMethod = c.getDeclaredMethod("MyMethod2", String.class);

            privateMethod.setAccessible(true);
            privateMethod.invoke(o, "Test wywolania metody prywatnej");

            AnnotationPrinter ap = new AnnotationPrinter(c);
            ap.printAll();
        } catch (Exception ex) {
            System.out.println(ex);
            return;
        }
    }
}

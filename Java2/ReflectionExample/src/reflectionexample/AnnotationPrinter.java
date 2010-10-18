/*
 * Autor: Bartosz Frąckowiak
 * E-mail: batas2@boo.pl
 * WWW: www.batas2.boo.pl
 */
package reflectionexample;

import java.lang.annotation.Annotation;
import java.lang.reflect.AnnotatedElement;
import java.lang.reflect.Field;
import java.lang.reflect.Method;

/**
 *
 * @author batas2
 */
public class AnnotationPrinter {

    private Class _c;

    public AnnotationPrinter(Class c) {
        _c = c;
    }

    private void printAnnotations(AnnotatedElement e) {
        System.out.println("Adnotacje: =>");
        for (Annotation a : e.getDeclaredAnnotations()) {
            System.out.println(a);
        }
        System.out.println();
    }

    public void printClassAnnotations() {
        System.out.println("Klasa: " + _c);
        printAnnotations(_c);

    }

    public void printMethodAnnotations() {
        for (Method m : _c.getDeclaredMethods()) {
            System.out.println("Metoda: " + m);
            printAnnotations(m);
        }
    }

    public void printFieldAnnotations() {
        for (Field f : _c.getDeclaredFields()) {
            System.out.println("Pole: " + f);
            printAnnotations(f);
        }
    }

    public void printAll() {
        printClassAnnotations();
        printMethodAnnotations();
        printFieldAnnotations();
    }
}

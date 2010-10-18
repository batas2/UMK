/*
 * Autor: Bartosz Frąckowiak
 * E-mail: batas2@boo.pl
 * WWW: www.batas2.boo.pl
 */
/**
 *
 * @author batas2
 */
@Annotation(arrayValues = {1, 2, 3, 4, 5}, intValue = 3, stringValue = "Moja adnotaca")
public class OwnAnnotation {

    public OwnAnnotation() {
    }
    @Annotation(arrayValues = {0}, stringValue = "Moje prywatne pole")
    private int _intValue;

    @Annotation(arrayValues = {1}, stringValue = "Moja publiczna metoda")
    public void MyMethod1() {
        return;
    }

    @Annotation(arrayValues = {2}, stringValue = "Moja prywatna metoda")
    private void MyMethod2(String s) {
        System.out.println(s);
        return;
    }
}

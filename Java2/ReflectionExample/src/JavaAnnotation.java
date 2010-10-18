/*
 * Autor: Bartosz Frąckowiak
 * E-mail: batas2@boo.pl
 * WWW: www.batas2.boo.pl
 */
/**
 *
 * @author batas2
 */
@SuppressWarnings(value = "unchecked")
public class JavaAnnotation {

    @Deprecated
    private int _intValue;

    @Deprecated
    public void deprecated() {
        return;
    }

    @Override
    public String toString(){
        return "Example";
    }

    @Override
    public boolean equals(Object obj) {
	return false;
    }
}

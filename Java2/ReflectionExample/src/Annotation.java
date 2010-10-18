/*
 * Autor: Bartosz Frąckowiak
 * E-mail: batas2@boo.pl
 * WWW: www.batas2.boo.pl
 */
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

/**
 *
 * @author batas2
 */
@Retention(RetentionPolicy.RUNTIME)
public @interface Annotation {
    String stringValue();
    int intValue() default 5;
    int[] arrayValues();
}

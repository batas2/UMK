/*
 * Autor: Bartosz Frąckowiak
 * E-mail: batas2@boo.pl
 * WWW: www.batas2.boo.pl
 */
package stax;

import java.io.*;
import java.util.Iterator;
import javax.xml.stream.*;
import javax.xml.stream.events.*;

/**
 *
 * @author batas2
 */
public class Main {

    private final static String attrValue = "urn:oasis:names:tc:SAML:1.1:nameid-format:X509SubjectName";
    private final static String attrName = "Format";

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws XMLStreamException, FileNotFoundException {

        XMLInputFactory iFactory = XMLInputFactory.newInstance();
        iFactory.setProperty("javax.xml.stream.isNamespaceAware", Boolean.TRUE);

        XMLEventReader reader = iFactory.createXMLEventReader(
                new BufferedInputStream(new FileInputStream("src/input.xml")));

        String parent = "";
        boolean b = false;

        while (reader.hasNext()) {
            XMLEvent event = reader.nextEvent();

            switch (event.getEventType()) {
                case XMLStreamConstants.START_ELEMENT:
                    StartElement startElem = event.asStartElement();
                    Iterator<?> attrs = startElem.getAttributes();
                    while (attrs.hasNext()) {

                        Attribute a = (Attribute) attrs.next();

                        if (a.getName().toString().equals(attrName) && a.getValue().equals(attrValue)) {
                            System.out.println("Element: " + startElem.getName());
                            System.out.println("Parent: " + parent);
                            b = true;
                        }
                    }
                    parent = startElem.getName().toString();
                    break;
                case XMLStreamConstants.CHARACTERS:
                    if (b) {
                        Characters c = event.asCharacters();
                        System.out.println("Value: " + c.getData());
                        System.out.println();
                        b = false;
                    }
                    break;
            }
        }
    }
}

/*
 * Autor: Bartosz Frąckowiak
 * E-mail: batas2@boo.pl
 * WWW: www.batas2.boo.pl
 */
package stax;

import java.io.*;
import java.util.Stack;
import javax.xml.namespace.QName;
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
        XMLEventReader reader = iFactory.createXMLEventReader(
                new BufferedInputStream(new FileInputStream("src/input.xml")));

        Stack<String> stack = new Stack<String>();

        while (reader.hasNext()) {
            XMLEvent event = reader.nextEvent();

            switch (event.getEventType()) {
                case XMLStreamConstants.START_ELEMENT:

                    StartElement startElem = event.asStartElement();
                    Attribute a = startElem.getAttributeByName(new QName(attrName));

                    if (a != null && a.getValue().equals(attrValue)) {
                        System.out.println("Element: " + startElem.getName());
                        System.out.println("Parent: " + stack.pop());

                        XMLEvent characterEvent = reader.nextEvent();

                        if (characterEvent.isCharacters()) {
                            Characters c = characterEvent.asCharacters();
                            System.out.println("Value: " + c.getData());
                        } else {
                            System.out.println("No Value");
                        }

                        System.out.println();
                    }

                    stack.push(startElem.getName().toString());
                    break;
                case XMLStreamConstants.END_ELEMENT:
                    if (!stack.empty()) {
                        stack.pop();
                    }
                    break;
            }
        }
    }
}

/*
 * Autor: Bartosz Frąckowiak
 * E-mail: batas2@boo.pl
 * WWW: www.batas2.boo.pl
 */
package jaxb;

import java.util.LinkedList;
import java.util.List;
import javax.xml.bind.*;
import org.purl.atom.ns_.*;

/**
 *
 * @author batas2
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    private static JAXBElement<AuthorType> getAuthor(ObjectFactory factory) {
        JAXBElement<AuthorType> jaxAuthor = factory.createEntryTypeAuthor(factory.createAuthorType());

        AuthorType author = new AuthorType();

        StringType authorName = new StringType();
        authorName.setValue("Bartosz Frackowiak");

        author.setName(authorName);

        EmailType authorEmail = new EmailType();
        authorEmail.setValue("bartosz.frackowiak@studenlive.com");

        author.setEmail(authorEmail);
        jaxAuthor.setValue(author);

        return jaxAuthor;
    }

    private static List<EntryType> getContent(ObjectFactory factory) {
        List<EntryType> list = new LinkedList<EntryType>();

        JAXBElement<ContentType> jaxContent = factory.createEntryTypeContent(factory.createContentType());
        EntryType entry = new EntryType();

        ContentType content = new ContentType();
        content.getContent().add("Moja zawartosc");

        jaxContent.setValue(content);
        entry.getTitleOrAuthorOrId().add(jaxContent);

        list.add(entry);

        return list;
    }

    public static void main(String[] args) {

        ObjectFactory factory = new ObjectFactory();

        JAXBElement<FeedType> jaxFeed = factory.createFeed(factory.createFeedType());

        FeedType feedType = new FeedType();
        FeedinfoType feedInfoType = new FeedinfoType();

        feedInfoType.getTitleOrAuthorOrContributor().add(getAuthor(factory));
        for (EntryType entry : getContent(factory)) {
            feedType.getEntry().add(entry);
        }

        feedType.setFeedinfo(feedInfoType);
        jaxFeed.setValue(feedType);

        JAXBContext jc;
        try {
            jc = JAXBContext.newInstance("org.purl.atom.ns_");
            Marshaller m = jc.createMarshaller();
            m.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT, true);
            m.marshal(jaxFeed, System.out);
        } catch (JAXBException ex) {
            System.out.println(ex);
        }
    }
}

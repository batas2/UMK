/*
 * Open source
 * Author: batas2, http://www.batas2.boo.pl/
 */
package Media;

/**
 *
 * @author batas2
 */
public class Video implements Media {

    private String _title;

    public Video(String _title) {
        this._title = _title;
    }

    public String getTitle() {
        return _title;
    }
}

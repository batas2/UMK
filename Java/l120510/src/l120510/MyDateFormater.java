/*
 * Open source
 * Author: batas2, http://www.batas2.boo.pl/
 */
package l120510;

import java.text.*;
import java.util.*;

/**
 *
 * @author batas2
 */
public class MyDateFormater {

    private String date;

    public MyDateFormater(String date) {
        this.date = date;
    }

    public String Format() {
        StringBuilder sb = new StringBuilder();

        Date d = new Date();
        SimpleDateFormat df = new SimpleDateFormat(("yyyy-MM-dd"));

        try {
            d = df.parse(this.date);
        } catch (ParseException ex) {
            System.out.print(ex);
        }

        Calendar c = Calendar.getInstance();
        c.setTime(d);

        sb.append("Dzien roku: " + c.get(Calendar.DAY_OF_YEAR) + "\n");
        sb.append("Dzien miesiaca: " + c.get(Calendar.DAY_OF_MONTH) + "\n");
        sb.append("Dzien tygodnia: " + c.get(Calendar.DAY_OF_WEEK) + "\n");
        sb.append("Miesiąc: " + c.get(Calendar.MONTH));
        return sb.toString();
    }
}


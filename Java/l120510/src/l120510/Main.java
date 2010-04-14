package l120510;

import java.io.*;
import l120510.*;

/**
 *
 * @author batas2
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        try {

            BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
            String linia;
            linia = in.readLine();
            MyDateFormater mdf = new MyDateFormater(linia);
            System.out.print(mdf.Format());
        } catch (IOException e) {
            System.out.print(e);
        }

    }
}

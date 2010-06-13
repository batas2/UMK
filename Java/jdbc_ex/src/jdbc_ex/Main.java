/*
 * 
 * Open source
 * Author: batas2, http://www.batas2.boo.pl/
 * 
 */
package jdbc_ex;

import View.MainForm;
import java.sql.Connection;
import javax.swing.SwingUtilities;

/**
 *
 * @author batas2
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        Connection c = MySQLConnection.getConnection();
        SwingUtilities.invokeLater(new Runnable() {

            public void run() {
                new MainForm().setVisible(true);
            }
        });
    }
}

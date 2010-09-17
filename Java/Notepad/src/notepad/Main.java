/*
 * Open source
 * Author: batas2, http://www.batas2.boo.pl/
 */
package notepad;

import javax.swing.*;

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
            UIManager.setLookAndFeel("com.sun.java.swing.plaf.nimbus.NimbusLookAndFeel");
        } catch (Exception ex) {
            System.out.print(ex);
        }

        SwingUtilities.invokeLater(new Runnable() {

            public void run() {
                new MainForm().setVisible(true);
            }
        });
    }
}

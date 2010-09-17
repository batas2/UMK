/*
 * Open source
 * Author: batas2, http://www.batas2.boo.pl/
 */
package swing;

import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

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
            //try {
            UIManager.setLookAndFeel("com.sun.java.swing.plaf.nimbus.NimbusLookAndFeel");
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        } catch (UnsupportedLookAndFeelException ex) {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        }
        UIManager.LookAndFeelInfo[] l = UIManager.getInstalledLookAndFeels();
        for (UIManager.LookAndFeelInfo a : l) {
            System.out.println(a.getClassName());
        }

        SwingUtilities.invokeLater(new Runnable() {

            public void run() {
                new MyForm().setVisible(true);
            }
        });
    }
}

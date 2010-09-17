/*
 * Open source
 * Author: batas2, http://www.batas2.boo.pl/
 */
package notepad;

import java.awt.event.*;
import java.io.*;
import javax.swing.*;

/**
 *
 * @author batas2
 */
public class MainForm extends JFrame {

    private JTextArea _textField;
    private JMenuBar menuBar;
    private JMenu fileMenu;
    private JMenu editMenu;
    private JMenuItem newAction;
    private JMenuItem openAction;
    private JMenuItem saveAction;
    private JMenuItem saveAsAction;
    private JMenuItem exitAction;
    private JMenuItem cutAction;
    private JMenuItem copyAction;
    private JMenuItem pasteAction;

    /**
     *
     */
    public MainForm() {
        InitGui();
    }

    private void InitGui() {
        setSize(400, 400);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setTitle("Notepad");

        menuBar = new JMenuBar();
        setJMenuBar(menuBar);

        fileMenu = new JMenu("Plik");
        editMenu = new JMenu("Edycja");
        menuBar.add(fileMenu);
        menuBar.add(editMenu);

        newAction = new JMenuItem("Nowy");
        openAction = new JMenuItem("Owtorz");
        saveAction = new JMenuItem("Zapisz");
        saveAsAction = new JMenuItem("Zapisz jako");
        exitAction = new JMenuItem("Koniec");
        cutAction = new JMenuItem("Wytnij");
        copyAction = new JMenuItem("kopiuj");
        pasteAction = new JMenuItem("wklej");

        newAction.addActionListener(new ActionListener() {

            public void actionPerformed(ActionEvent evt) {
                _textField.setText("");
            }
        });

        openAction.addActionListener(new ActionListener() {

            public void actionPerformed(ActionEvent e) {
                final JFileChooser fc = new JFileChooser();

                int returnVal = fc.showOpenDialog(MainForm.this);

                if (returnVal == JFileChooser.APPROVE_OPTION) {
                    File file = fc.getSelectedFile();

                    try {
                        BufferedReader in = new BufferedReader(
                                new InputStreamReader(
                                new FileInputStream(file.getAbsolutePath())));
                        String str;
                        while ((str = in.readLine()) != null) {
                            _textField.append(str + "\n");
                        }

                    } catch (IOException ex) {
                        System.out.print(ex);
                    }
                }
            }
        });


        saveAction.addActionListener(
                new ActionListener() {

                    public void actionPerformed(ActionEvent evt) {
                    }
                });

        saveAsAction.addActionListener(new ActionListener() {

            public void actionPerformed(ActionEvent evt) {
            }
        });

        exitAction.addActionListener(new ActionListener() {

            public void actionPerformed(ActionEvent evt) {
                System.exit(0);
            }
        });

        cutAction.addActionListener(new ActionListener() {

            public void actionPerformed(ActionEvent evt) {
                _textField.cut();
            }
        });
        copyAction.addActionListener(new ActionListener() {

            public void actionPerformed(ActionEvent evt) {
                _textField.copy();
            }
        });
        pasteAction.addActionListener(new ActionListener() {

            public void actionPerformed(ActionEvent evt) {
                _textField.paste();
            }
        });

        fileMenu.add(newAction);
        fileMenu.add(openAction);
        fileMenu.add(saveAction);
        fileMenu.add(saveAsAction);
        fileMenu.addSeparator();

        fileMenu.add(exitAction);

        editMenu.add(cutAction);
        editMenu.add(copyAction);
        editMenu.add(pasteAction);

        _textField = new JTextArea();
        add(_textField);

    }
}

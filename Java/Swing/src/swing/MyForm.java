/*
 * Open source
 * Author: batas2, http://www.batas2.boo.pl/
 */
package swing;

import java.awt.*;
import javax.swing.*;

/**
 *
 * @author batas2
 */
public class MyForm extends JFrame {

    private JPanel pTop;
    private JPanel pBottom;
    private JTextField txtInput;
    private int _A, _B;
    private String _action;
    private boolean reset;
    private JButton[] btnZ;
    private boolean[] visible;

    public MyForm() {
        _A = 0;
        _B = 0;
        _action = "";

        pTop = new JPanel();
        pBottom = new JPanel();
        txtInput = new JTextField();
        InitGUI();
    }

    private void InitGUI() {
        setSize(200, 400);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setTitle("Kalkulator");

        pTop.setLayout(new BoxLayout(pTop, BoxLayout.X_AXIS));
        pTop.add(txtInput);

        pBottom.setLayout(new GridLayout(6, 3));

        for (int i = 0; i < 9; i++) {
            JButton btn = new JButton("" + (i + 1));
            btn.addActionListener(new java.awt.event.ActionListener() {

                public void actionPerformed(java.awt.event.ActionEvent evt) {
                    btnCyfraActionPerformed(evt);
                }
            });
            pBottom.add(btn);
        }

        JButton btn0 = new JButton("0");
        JButton btnMinus = new JButton("-");
        JButton btnPlus = new JButton("+");
        JButton btnRazy = new JButton("*");
        JButton btnDziel = new JButton("/");
        JButton btnRowna = new JButton("=");

        btnMinus.addActionListener(new java.awt.event.ActionListener() {

            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnAkcjaActionPerformed(evt);
            }
        });

        btn0.addActionListener(new java.awt.event.ActionListener() {

            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnCyfraActionPerformed(evt);
            }
        });

        btnPlus.addActionListener(new java.awt.event.ActionListener() {

            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnAkcjaActionPerformed(evt);
            }
        });

        btnRazy.addActionListener(new java.awt.event.ActionListener() {

            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnAkcjaActionPerformed(evt);
            }
        });

        btnDziel.addActionListener(new java.awt.event.ActionListener() {

            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnAkcjaActionPerformed(evt);
            }
        });

        btnRowna.addActionListener(new java.awt.event.ActionListener() {

            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnAkcjaActionPerformed(evt);
            }
        });





        pBottom.add(btnMinus);
        pBottom.add(btn0);
        pBottom.add(btnPlus);

        pBottom.add(btnRazy);
        pBottom.add(btnDziel);
        pBottom.add(btnRowna);

        btnZ = new JButton[2];
        visible = new boolean[2];

        for (int i = 0; i < 2; i++) {
            btnZ[i] = new JButton(Integer.valueOf(i).toString());
            btnZ[i].addActionListener(new java.awt.event.ActionListener() {

                public void actionPerformed(java.awt.event.ActionEvent evt) {
                    btnZnikActionPerformed(evt);
                }
            });
            pBottom.add(btnZ[i]);
            visible[i] = true;
        }

        Container c = getContentPane();
        setLayout(new BoxLayout(c, BoxLayout.Y_AXIS));

        c.add(pTop);
        c.add(Box.createVerticalStrut(10));
        c.add(pBottom);
    }

    private void btnAkcjaActionPerformed(java.awt.event.ActionEvent evt) {
        JButton btn = (JButton) evt.getSource();

        if (!btn.getText().equals(" = ")) {
            if (_action.equals("")) {
                _A = Integer.valueOf(txtInput.getText());
                _action = btn.getText();
            }
            txtInput.setText("");
        } else {
            _B = Integer.valueOf(txtInput.getText());
            double r = 0;
            if (_action.equals("-")) {
                r = _A - _B;
            } else if (_action.equals("+")) {
                r = _A + _B;
            } else if (_action.equals("*")) {
                r = _A * _B;
            } else if (_action.equals("/")) {
                r = _A / _B;
            }

            txtInput.setText(Double.valueOf(r).toString());
            _A = 0;
            _B = 0;
            _action = "";
            reset = true;
        }

    }

    private void btnCyfraActionPerformed(java.awt.event.ActionEvent evt) {
        JButton btn = (JButton) evt.getSource();
        if (reset) {
            txtInput.setText("");
            reset = false;
        }
        String str = txtInput.getText();
        str += btn.getText();
        txtInput.setText(str);
    }

    private void btnZnikActionPerformed(java.awt.event.ActionEvent evt) {
        JButton btn = (JButton) evt.getSource();
        int index = Integer.valueOf(btn.getText());
        int _index = index == 0 ? 1 : 0;

        boolean z = false;

        if (visible[index] && visible[_index]) {
            btnZ[_index].setVisible(false);
            visible[_index] = false;
            z = true;
        }

        if (!z && visible[index] && !visible[_index]) {
            btnZ[_index].setVisible(true);
            visible[_index] = true;
        }



    }
}

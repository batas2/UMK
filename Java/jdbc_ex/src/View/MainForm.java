/*
 * 
 * Open source
 * Author: batas2, http://www.batas2.boo.pl/
 * 
 */
package View;

import Model.GridModel;
import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.SQLException;
import javax.swing.*;
import javax.swing.JTable;
import javax.swing.event.TableModelEvent;
import javax.swing.event.TableModelListener;

/**
 *
 * @author batas2
 */
public class MainForm extends JFrame implements TableModelListener {

    private JTable _grid;
    private GridModel _gridModel;
    private JMenu _mMain;
    private JMenuBar _menuBar;
    private JMenuItem _itemAdd;
    private JMenuItem _itemEdit;
    private JMenuItem _itemDelete;

    public MainForm() {
        initForm();
    }

    public void tableChanged(TableModelEvent e) {
        _grid.setModel(_gridModel);
    }

    private void initForm() {

        _menuBar = new JMenuBar();
        _mMain = new JMenu();
        _itemAdd = new JMenuItem();
        _itemEdit = new JMenuItem();
        _itemDelete = new JMenuItem();

        _itemAdd.setText("Dodaj");
        _itemAdd.addActionListener(new ActionListener() {

            public void actionPerformed(ActionEvent e) {
                try {
                    _gridModel.AddRow();
                } catch (Exception ex) {
                    System.out.println(ex);
                }
                pack();
            }
        });
        _itemEdit.setText("Edytuj");
        _itemEdit.addActionListener(new ActionListener() {

            public void actionPerformed(ActionEvent e) {
                try {
                    _gridModel.Update(_grid.getSelectedRow());
                } catch (Exception ex) {
                    System.out.println(ex);
                }
                pack();
            }
        });
        _itemDelete.setText("Wywal");
        _itemDelete.addActionListener(new ActionListener() {

            public void actionPerformed(ActionEvent e) {
                try {
                    _gridModel.Delete(_grid.getSelectedRow());
                } catch (Exception ex) {
                    System.out.println(ex);
                }
            }
        });

        _mMain.setText("Menu");
        _mMain.add(_itemAdd);
        _mMain.add(_itemEdit);
        _mMain.add(_itemDelete);
        _menuBar.add(_mMain);

        setJMenuBar(_menuBar);

        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        _grid = new JTable();
        _gridModel = new GridModel();
        _grid.getModel().addTableModelListener(this);
        _grid.setSelectionMode(javax.swing.ListSelectionModel.SINGLE_SELECTION);
        _grid.setModel(_gridModel);
         _grid.setAutoCreateRowSorter(true);


        Container pane = getContentPane();

        pane.add(_grid, BorderLayout.CENTER);
        pack();
        setLocationRelativeTo(null);
    }
}

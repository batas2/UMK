/*
 * 
 * Open source
 * Author: batas2, http://www.batas2.boo.pl/
 * 
 */
package Model;

import java.sql.SQLException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.List;
import javax.swing.table.AbstractTableModel;

/**
 *
 * @author batas2
 */
public class GridModel extends AbstractTableModel {

    private final int _coulmnCount = 5;
    private String[] _columns;
    private Object[][] _data;
    private List<java_ex_table> _list;
    private SimpleDateFormat sdf;

    public GridModel() {
        sdf = new SimpleDateFormat("yyyy-MM-dd");
        _columns = new String[_coulmnCount];

        _columns[0] = "id";
        _columns[1] = "name";
        _columns[2] = "count";
        _columns[3] = "time";
        _columns[4] = "sold";

        try {
            _list = java_ex_table.FindAll();
        } catch (SQLException ex) {
            System.out.println(ex);
        }

        update();

    }

    private void update() {
        _data = new Object[_list.size()][_columns.length];
        for (int i = 0; i < _list.size(); i++) {
            fillRow(_list.get(i), i);
        }
    }

    private void fillRow(java_ex_table item, int i) {
        _data[i][0] = item.getId();
        _data[i][1] = item.getName();
        _data[i][2] = item.getCount();
        _data[i][3] = item.getTime();
        _data[i][4] = item.isSold();
    }

    public int getRowCount() {
        return _list.size();
    }

    public int getColumnCount() {
        return _coulmnCount;
    }

    public Object getValueAt(int rowIndex, int columnIndex) {
        return _data[rowIndex][columnIndex];
    }

    @Override
    public String getColumnName(int col) {
        return _columns[col];
    }

    public void Delete(int i) throws SQLException {
        _list.get(i).Delete();
        _list.remove(i);
        update();
        fireTableDataChanged();
    }

    @Override
    public boolean isCellEditable(int row, int col) {
        if (col == 0) {
            return false;
        } else {
            return true;
        }
    }

    @Override
    public Class getColumnClass(int c) {
        return getValueAt(0, c).getClass();
    }

    @Override
    public void setValueAt(Object value, int row, int col) {
        java_ex_table item = _list.get(row);
        switch (col) {
            case 1:
                item.setName(String.valueOf(value));
                break;
            case 2:
                item.setCount(Integer.parseInt(String.valueOf(value)));
                break;
            case 3:

//                Date date = null;
//                try {
//                    date = (Date) sdf.parse(String.valueOf(value));
//                } catch (ParseException ex) {
//                    Logger.getLogger(GridModel.class.getName()).log(Level.SEVERE, null, ex);
//                }
                item.setTime(String.valueOf(value));
                break;
            case 4:
                item.setSold(Boolean.valueOf(String.valueOf(value)));
                break;
        }
        _data[row][col] = value;
        fireTableCellUpdated(row, col);
    }

    public void AddRow() throws SQLException, ParseException {
        java_ex_table i = new java_ex_table("Nazwa", 0, "1990-01-01", false);
        i.Insert();
        _list.add(i);
        update();
        fireTableDataChanged();
    }

    public void Update(int i) throws SQLException, ParseException {
        _list.get(i).Update();
        update();
        fireTableDataChanged();
    }
}

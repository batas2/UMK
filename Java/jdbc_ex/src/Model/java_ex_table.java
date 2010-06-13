/*
 * 
 * Open source
 * Author: batas2, http://www.batas2.boo.pl/
 * 
 */
package Model;

import com.mysql.jdbc.Statement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;
import jdbc_ex.MySQLConnection;

/**
 *
 * @author batas2
 */
public class java_ex_table {

    private int _id;
    private String _name;
    private int _count;
    private String _time;
    private boolean _sold;
    private SimpleDateFormat sdf;

    public java_ex_table() {
        sdf = new SimpleDateFormat("yyyy-MM-dd");
    }

    public java_ex_table(int _id, String _name, int _count, String _time, boolean _sold) {
        this._id = _id;
        this._name = _name;
        this._count = _count;
        this._time = _time;
        this._sold = _sold;
        sdf = new SimpleDateFormat("yyyy-MM-dd");
    }

    public java_ex_table(String _name, int _count, String _time, boolean _sold) {
        this._name = _name;
        this._count = _count;
        this._time = _time;
        this._sold = _sold;
        sdf = new SimpleDateFormat("yyyy-MM-dd");
    }

    public int getCount() {
        return _count;
    }

    public void setCount(int _count) {
        this._count = _count;
    }

    public int getId() {
        return _id;
    }

    public void setId(int _id) {
        this._id = _id;
    }

    public String getName() {
        return _name;
    }

    public void setName(String _name) {
        this._name = _name;
    }

    public boolean isSold() {
        return _sold;
    }

    public void setSold(boolean _sold) {
        this._sold = _sold;
    }

    public String getTime() {
        return _time;
    }

    public void setTime(String _time) {
        this._time = _time;
    }

    public static List<java_ex_table> FindAll() throws SQLException {
        List<java_ex_table> result = new LinkedList<java_ex_table>();
        Statement s = (Statement) MySQLConnection.getConnection().createStatement();
        System.out.println("SELECT * FROM java_ex_table");
        s.executeQuery("SELECT * FROM java_ex_table");
        ResultSet rs = s.getResultSet();
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
        while (rs.next()) {
            result.add(new java_ex_table(rs.getInt("java_ex_table_id"), rs.getString("java_ex_table_name"), rs.getInt("java_ex_table_count"), sdf.format(rs.getDate("java_ex_table_time")), rs.getBoolean("java_ex_table_sold")));
        }
        return result;
    }

    public void Delete() throws SQLException {
        Statement s = (Statement) MySQLConnection.getConnection().createStatement();
        System.out.println("DELETE FROM java_ex_table WHERE java_ex_table.java_ex_table_id = " + _id);
        s.executeUpdate("DELETE FROM java_ex_table WHERE java_ex_table.java_ex_table_id = " + _id);
        s.close();
    }

    public void Update() throws SQLException, ParseException {
        Statement s = (Statement) MySQLConnection.getConnection().createStatement();
        String sold;
        if (_sold) {
            sold = "1";
        } else {
            sold = "0";
        }
        Date date = sdf.parse(_time);
        System.out.println("UPDATE java_ex.java_ex_table SET java_ex_table_id = " + _id + ", java_ex_table_name = '" + _name + "', java_ex_table_count = " + _count + ", java_ex_table_time = " + sdf.format(date) + ", java_ex_table_sold = " + sold + " WHERE java_ex_table.java_ex_table_id = " + _id);
        s.executeUpdate("UPDATE java_ex.java_ex_table SET java_ex_table_name = '" + _name + "', java_ex_table_count = " + _count + ", java_ex_table_time = '" + sdf.format(date) + "', java_ex_table_sold = " + sold + " WHERE java_ex_table.java_ex_table_id = " + _id);
        s.close();
    }

    public void Insert() throws SQLException, ParseException {
        Statement s = (Statement) MySQLConnection.getConnection().createStatement();

        String sold;
        if (_sold) {
            sold = "1";
        } else {
            sold = "0";
        }
        Date date = sdf.parse(_time);
        System.out.println("INSERT INTO java_ex.java_ex_table (`java_ex_table_name` ,`java_ex_table_count` ,`java_ex_table_time` ,`java_ex_table_sold` )VALUES ('" + _name + "', '" + _count + "', '" + sdf.format(date) + "' , '" + sold + "');");
        s.executeUpdate("INSERT INTO java_ex.java_ex_table (`java_ex_table_name` ,`java_ex_table_count` ,`java_ex_table_time` ,`java_ex_table_sold` )VALUES ('" + _name + "', '" + _count + "', '" + sdf.format(date) + "' , '" + sold + "');");
        s.executeQuery("SELECT LAST_INSERT_ID() AS 'LAST_ID';");

        ResultSet rs = s.getResultSet();
        while (rs.next()) {
            _id = rs.getInt("LAST_ID");
        }
        s.close();
    }
}

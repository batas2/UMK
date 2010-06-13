/*
 * 
 * Open source
 * Author: batas2, http://www.batas2.boo.pl/
 * 
 */
package jdbc_ex;

import com.mysql.jdbc.Connection;
import java.sql.DriverManager;

/**
 *
 * @author batas2
 */
public class MySQLConnection {

    private static Connection _connection = null;

    public static Connection getConnection() {
        if (_connection != null) {
            return _connection;
        } else {
            try {
                String userName = "java_ex";
                String password = "qwerty";
                String url = "jdbc:mysql://localhost/java_ex";
                Class.forName("com.mysql.jdbc.Driver").newInstance();
                _connection = (Connection) DriverManager.getConnection(url, userName, password);
                return _connection;
            } catch (Exception e) {
                System.out.println(e);
            }
            return null;
        }
    }
}

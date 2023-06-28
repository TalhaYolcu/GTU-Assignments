package db;

import constants.CONSTANTS;

import java.sql.Connection;
import java.sql.DriverManager;

public class TravelBookingConnection {
    private static TravelBookingConnection instance=new TravelBookingConnection();
    public static final String URL = CONSTANTS.MYSQL_URL;
    public static final String DRIVER_CLASS = CONSTANTS.MYSQL_CLASS_NAME;

    private TravelBookingConnection() {
        try {
            Class.forName(DRIVER_CLASS);
        }
        catch (Exception ex) {
            ex.printStackTrace();
        }
    }
    private Connection createConnection() {
        Connection con=null;
        try {
            Class.forName(CONSTANTS.MYSQL_CLASS_NAME);
            con = DriverManager.getConnection(CONSTANTS.MYSQL_URL,CONSTANTS.MYSQL_USERNAME,CONSTANTS.MYSQL_PASSWORD);
            System.out.println("Connection success");

        }
        catch (Exception ex) {
            ex.printStackTrace();
        }
        return con;
    }
    public static Connection getConnection() {
        return instance.createConnection();
    }

}

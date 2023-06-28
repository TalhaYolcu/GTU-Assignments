package main;

import db.TravelBookingConnection;
import gui.MainWindow;

import javax.swing.*;
import java.sql.*;

public class Main {


    public static void main(String[] args) {




        Main m=new Main();

        m.initMainWindow();
/*
        m.initDatabase();

        try {
            TravelBookingConnection.getConnection().close();
        }
        catch (Exception ex) {
            ex.printStackTrace();
        }
*/
    }



    private void initMainWindow() {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                new MainWindow().setVisible(true);
            }
        });



    }

    private void viewPersonTable() {
        try {
            Statement st = TravelBookingConnection.getConnection().createStatement();
            String query = "select * from person";
            ResultSet rs = st.executeQuery(query);

            while(rs.next()) {
                System.out.println(rs.getInt(1)+"\t"+rs.getString(2)+"\t"+rs.getInt(3));
            }
            st.close();
        }
        catch (Exception ex) {
            ex.printStackTrace();
        }

    }

    private void insertPerson(int id,String name,int age,int budget) {

        try {

            PreparedStatement st = TravelBookingConnection.getConnection().prepareStatement("INSERT INTO person(person_id,name,age) VALUES (?,?,?)");
            st.setInt(1,id);
            st.setString(2,name);
            st.setInt(3,age);

            st.execute();
        }
        catch (Exception ex) {
            ex.printStackTrace();
        }


    }

    private void initDatabase() {
        viewPersonTable();

        insertPerson(3,"yakup",22,10000);

        viewPersonTable();
    }
}
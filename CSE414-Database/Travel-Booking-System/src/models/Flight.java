package models;

import interfaces.ModelInterface;

import java.sql.ResultSet;
import java.sql.SQLException;

public class Flight implements ModelInterface<Flight> {

    private int flight_id;
    private int guide_id;
    private int company_id;
    private int price;
    private String flight_info;

    public Flight() {
    }

    public int getFlight_id() {
        return flight_id;
    }

    public void setFlight_id(int flight_id) {
        this.flight_id = flight_id;
    }

    public int getGuide_id() {
        return guide_id;
    }

    public void setGuide_id(int guide_id) {
        this.guide_id = guide_id;
    }

    public int getCompany_id() {
        return company_id;
    }

    public void setCompany_id(int company_id) {
        this.company_id = company_id;
    }

    public int getPrice() {
        return price;
    }

    public void setPrice(int price) {
        this.price = price;
    }

    public String getFlight_info() {
        return flight_info;
    }

    public void setFlight_info(String flight_info) {
        this.flight_info = flight_info;
    }

    public Flight(int flight_id, int guide_id, int company_id, int price, String flight_info) {
        this.flight_id = flight_id;
        this.guide_id = guide_id;
        this.company_id = company_id;
        this.price = price;
        this.flight_info = flight_info;
    }

    @Override
    public Flight exportTableInstance(ResultSet rs) throws SQLException {
        return new Flight(
                rs.getInt("flight_id"),
                rs.getInt("guide_id"),
                rs.getInt("company_id"),
                rs.getInt("price"),
                rs.getString("flight_info")
        );
    }

    @Override
    public String getSelectQuery(int id) {
        return "SELECT * FROM flight WHERE flight_id = " + id;
    }
    public String getSelectQueryCompany(int id) {
        return "SELECT * FROM flight WHERE company_id = "+id;
    }

    @Override
    public String getSelectAllQuery() {
        return "SELECT * FROM select_flight";
    }

    @Override
    public String getDeleteQuery(int id) {
        return "DELETE FROM flight WHERE flight_id = " + id;
    }

    @Override
    public String getDeleteAllQuery() {
        return "DELETE FROM flight";
    }

    @Override
    public String getInsertQuery(Flight object) {
        return "INSERT INTO flight (flight_id, guide_id, company_id, price, flight_info) VALUES (" +
                "" + object.getFlight_id() + "," +
                "" + object.getGuide_id() + "," +
                "" + object.getCompany_id() + "," +
                "" + object.getPrice() + "," +
                "'" + object.getFlight_info() +
                "')";
    }

    @Override
    public String getUpdateQuery(Flight object, int id) {
        return "UPDATE flight SET " +
                "flight_id = " + object.getFlight_id() + ", " +
                "guide_id = " + object.getGuide_id() + ", " +
                "company_id = " + object.getCompany_id() + ", " +
                "price = " + object.getPrice() + ", " +
                "flight_info = '" + object.getFlight_info() +
                "' WHERE flight_id = " + id;
    }
}

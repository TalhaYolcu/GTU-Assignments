package models;

import interfaces.ModelInterface;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;

public class Bus implements ModelInterface<Bus> {

    private int bus_id;
    private int guide_id;
    private int company_id;
    private int price;
    private String trip_info;

    public Bus() {
    }

    public int getBus_id() {
        return bus_id;
    }

    public void setBus_id(int bus_id) {
        this.bus_id = bus_id;
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

    public String getTrip_info() {
        return trip_info;
    }

    public void setTrip_info(String trip_info) {
        this.trip_info = trip_info;
    }

    public Bus(int bus_id, int guide_id, int company_id, int price, String trip_info) {
        this.bus_id = bus_id;
        this.guide_id = guide_id;
        this.company_id = company_id;
        this.price = price;
        this.trip_info = trip_info;
    }

    @Override
    public Bus exportTableInstance(ResultSet rs) throws SQLException {
        return new Bus(
                rs.getInt("bus_id"),
                rs.getInt("guide_id"),
                rs.getInt("company_id"),
                rs.getInt("price"),
                rs.getString("trip_info")
        );
    }

    @Override
    public String getSelectQuery(int id) {
        return "SELECT * FROM bus WHERE bus_id = " + id;
    }

    @Override
    public String getSelectAllQuery() {
        return "SELECT * FROM select_bus";
    }

    @Override
    public String getDeleteQuery(int id) {
        return "DELETE FROM bus WHERE bus_id = " + id;
    }

    @Override
    public String getDeleteAllQuery() {
        return "DELETE FROM bus";
    }

    @Override
    public String getInsertQuery(Bus object) {
        return "INSERT INTO bus (bus_id, guide_id, company_id, price, trip_info) VALUES (" +
                "" + object.getBus_id() + "," +
                "" + object.getGuide_id() + "," +
                "" + object.getCompany_id() + "," +
                "" + object.getPrice() + "," +
                "'" + object.getTrip_info() +
                "')";
    }

    @Override
    public String getUpdateQuery(Bus object, int id) {
        return "UPDATE bus SET " +
                "bus_id = " + object.getBus_id() + ", " +
                "guide_id = " + object.getGuide_id() + ", " +
                "company_id = " + object.getCompany_id() + ", " +
                "price = " + object.getPrice() + ", " +
                "trip_info = '" + object.getTrip_info() +
                "' WHERE bus_id = " + id;
    }
}

package models;

import interfaces.ModelInterface;

import java.sql.ResultSet;
import java.sql.SQLException;

public class Hotel implements ModelInterface<Hotel> {

    private int hotel_id;
    private String hotel_name;
    private int company_id;

    public Hotel() {
    }

    public int getHotel_id() {
        return hotel_id;
    }

    public void setHotel_id(int hotel_id) {
        this.hotel_id = hotel_id;
    }

    public String getHotel_name() {
        return hotel_name;
    }

    public void setHotel_name(String hotel_name) {
        this.hotel_name = hotel_name;
    }

    public int getCompany_id() {
        return company_id;
    }

    public void setCompany_id(int company_id) {
        this.company_id = company_id;
    }

    public Hotel(int hotel_id, String hotel_name, int company_id) {
        this.hotel_id = hotel_id;
        this.hotel_name = hotel_name;
        this.company_id = company_id;
    }

    @Override
    public Hotel exportTableInstance(ResultSet rs) throws SQLException {
        return new Hotel(
                rs.getInt("hotel_id"),
                rs.getString("hotel_name"),
                rs.getInt("company_id")
        );
    }

    @Override
    public String getSelectQuery(int id) {
        return "SELECT * FROM hotel WHERE hotel_id = " + id;
    }

    @Override
    public String getSelectAllQuery() {
        return "SELECT * FROM hotel";
    }

    @Override
    public String getDeleteQuery(int id) {
        return "DELETE FROM hotel WHERE hotel_id = " + id;
    }

    @Override
    public String getDeleteAllQuery() {
        return "DELETE FROM hotel";
    }

    @Override
    public String getInsertQuery(Hotel object) {
        return "INSERT INTO hotel (hotel_id, hotel_name, company_id) VALUES (" +
                "" + object.getHotel_id() + "," +
                "'" + object.getHotel_name() + "'," +
                "" + object.getCompany_id() +
                ")";
    }

    @Override
    public String getUpdateQuery(Hotel object, int id) {
        return "UPDATE hotel SET " +
                "hotel_id = " + object.getHotel_id() + ", " +
                "hotel_name = '" + object.getHotel_name() + "', " +
                "company_id = " + object.getCompany_id() +
                " WHERE hotel_id = " + id;
    }
}

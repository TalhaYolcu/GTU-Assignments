package models;

import interfaces.ModelInterface;

import java.sql.ResultSet;
import java.sql.SQLException;

public class Room implements ModelInterface<Room> {

    private int room_id;
    private int hotel_id;
    private int daily_price;
    private String room_properties;

    public Room() {
    }

    public int getRoom_id() {
        return room_id;
    }

    public void setRoom_id(int room_id) {
        this.room_id = room_id;
    }

    public int getHotel_id() {
        return hotel_id;
    }

    public void setHotel_id(int hotel_id) {
        this.hotel_id = hotel_id;
    }

    public int getDaily_price() {
        return daily_price;
    }

    public void setDaily_price(int daily_price) {
        this.daily_price = daily_price;
    }

    public String getRoom_properties() {
        return room_properties;
    }

    public void setRoom_properties(String room_properties) {
        this.room_properties = room_properties;
    }

    public Room(int room_id, int hotel_id, int daily_price, String room_properties) {
        this.room_id = room_id;
        this.hotel_id = hotel_id;
        this.daily_price = daily_price;
        this.room_properties = room_properties;
    }

    @Override
    public Room exportTableInstance(ResultSet rs) throws SQLException {
        return new Room(
                rs.getInt("room_id"),
                rs.getInt("hotel_id"),
                rs.getInt("daily_price"),
                rs.getString("room_properties")
        );
    }

    @Override
    public String getSelectQuery(int id) {
        return "SELECT * FROM room WHERE room_id = " + id;
    }

    @Override
    public String getSelectAllQuery() {
        return "SELECT * FROM room";
    }

    @Override
    public String getDeleteQuery(int id) {
        return "DELETE FROM room WHERE room_id = " + id;
    }

    @Override
    public String getDeleteAllQuery() {
        return "DELETE FROM room";
    }

    @Override
    public String getInsertQuery(Room object) {
        return "INSERT INTO room (room_id, hotel_id, daily_price, room_properties) VALUES (" +
                "" + object.getRoom_id() + "," +
                "" + object.getHotel_id() + "," +
                "" + object.getDaily_price() + "," +
                "'" + object.getRoom_properties() +
                "')";
    }

    @Override
    public String getUpdateQuery(Room object, int id) {
        return "UPDATE room SET " +
                "room_id = " + object.getRoom_id() + ", " +
                "hotel_id = " + object.getHotel_id() + ", " +
                "daily_price = " + object.getDaily_price() + ", " +
                "room_properties = '" + object.getRoom_properties() +
                "' WHERE room_id = " + id;
    }
    public String getRoomsByHotelIDQuery(String hotelId) {
        return "SELECT * FROM room WHERE hotel_id = "+hotelId;
    }
}

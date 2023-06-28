package models;

import interfaces.ModelInterface;

import java.sql.Date;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;

public class Accommodation implements ModelInterface<Accommodation> {

    private int acc_id;
    private int company_id;
    private int hotel_id;
    private int room_id;
    private int person_id;
    private Date check_in_date;
    private Date check_out_date;

    public Accommodation() {
    }

    public int getAcc_id() {
        return acc_id;
    }

    public void setAcc_id(int acc_id) {
        this.acc_id = acc_id;
    }

    public int getCompany_id() {
        return company_id;
    }

    public void setCompany_id(int company_id) {
        this.company_id = company_id;
    }

    public int getHotel_id() {
        return hotel_id;
    }

    public void setHotel_id(int hotel_id) {
        this.hotel_id = hotel_id;
    }

    public int getRoom_id() {
        return room_id;
    }

    public void setRoom_id(int room_id) {
        this.room_id = room_id;
    }

    public int getPerson_id() {
        return person_id;
    }

    public void setPerson_id(int person_id) {
        this.person_id = person_id;
    }

    public Date getCheck_in_date() {
        return check_in_date;
    }

    public void setCheck_in_date(Date check_in_date) {
        this.check_in_date = check_in_date;
    }

    public Date getCheck_out_date() {
        return check_out_date;
    }

    public void setCheck_out_date(Date check_out_date) {
        this.check_out_date = check_out_date;
    }

    public Accommodation(int acc_id, int company_id, int hotel_id, int room_id, int person_id, Date check_in_date, Date check_out_date) {
        this.acc_id = acc_id;
        this.company_id = company_id;
        this.hotel_id = hotel_id;
        this.room_id = room_id;
        this.person_id = person_id;
        this.check_in_date = check_in_date;
        this.check_out_date = check_out_date;
    }

    @Override
    public Accommodation exportTableInstance(ResultSet rs) throws SQLException {
        return new Accommodation(
                rs.getInt("acc_id"),
                rs.getInt("company_id"),
                rs.getInt("hotel_id"),
                rs.getInt("room_id"),
                rs.getInt("person_id"),
                rs.getDate("check_in_date"),
                rs.getDate("check_out_date")
        );
    }

    @Override
    public String getSelectQuery(int id) {
        return "SELECT * FROM accommodation WHERE acc_id = " + id;
    }

    @Override
    public String getSelectAllQuery() {
        return "SELECT * FROM select_accommodation";
    }

    @Override
    public String getDeleteQuery(int id) {
        return "DELETE FROM accommodation WHERE acc_id = " + id;
    }

    @Override
    public String getDeleteAllQuery() {
        return "DELETE FROM accommodation";
    }

    @Override
    public String getInsertQuery(Accommodation object) {
        return "INSERT INTO accommodation (company_id, hotel_id, room_id, person_id, check_in_date, check_out_date) VALUES (" +
                "" + object.getCompany_id() + "," +
                "" + object.getHotel_id() + "," +
                "" + object.getRoom_id() + "," +
                "" + object.getPerson_id() + "," +
                "'" + object.getCheck_in_date() + "'," +
                "'" + object.getCheck_out_date() +
                "')";
    }

    @Override
    public String getUpdateQuery(Accommodation object, int id) {
        return "UPDATE accommodation SET " +
                "acc_id = " + object.getAcc_id() + ", " +
                "company_id = " + object.getCompany_id() + ", " +
                "hotel_id = " + object.getHotel_id() + ", " +
                "room_id = " + object.getRoom_id() + ", " +
                "person_id = " + object.getPerson_id() + ", " +
                "check_in_date = '" + object.getCheck_in_date() + "', " +
                "check_out_date = '" + object.getCheck_out_date() +
                "' WHERE acc_id = " + id;
    }
}

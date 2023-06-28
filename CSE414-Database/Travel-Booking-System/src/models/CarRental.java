package models;

import interfaces.ModelInterface;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Date;

public class CarRental implements ModelInterface<CarRental> {

    private int rental_id;
    private int car_id;
    private int person_id;
    private Date start_date;
    private Date end_date;
    private int company_id;

    public CarRental() {
    }

    public int getRental_id() {
        return rental_id;
    }

    public void setRental_id(int rental_id) {
        this.rental_id = rental_id;
    }

    public int getCar_id() {
        return car_id;
    }

    public void setCar_id(int car_id) {
        this.car_id = car_id;
    }

    public int getPerson_id() {
        return person_id;
    }

    public void setPerson_id(int person_id) {
        this.person_id = person_id;
    }

    public Date getStart_date() {
        return start_date;
    }

    public void setStart_date(Date start_date) {
        this.start_date = start_date;
    }

    public Date getEnd_date() {
        return end_date;
    }

    public void setEnd_date(Date end_date) {
        this.end_date = end_date;
    }

    public int getCompany_id() {
        return company_id;
    }

    public void setCompany_id(int company_id) {
        this.company_id = company_id;
    }

    public CarRental(int rental_id, int car_id, int person_id, Date start_date, Date end_date, int company_id) {
        this.rental_id = rental_id;
        this.car_id = car_id;
        this.person_id = person_id;
        this.start_date = start_date;
        this.end_date = end_date;
        this.company_id = company_id;
    }

    @Override
    public CarRental exportTableInstance(ResultSet rs) throws SQLException {
        return new CarRental(
                rs.getInt("rental_id"),
                rs.getInt("car_id"),
                rs.getInt("person_id"),
                rs.getDate("start_date"),
                rs.getDate("end_date"),
                rs.getInt("company_id")
        );
    }

    @Override
    public String getSelectQuery(int id) {
        return "SELECT * FROM car_rental WHERE rental_id = " + id;
    }

    @Override
    public String getSelectAllQuery() {
        return "SELECT * FROM select_car_rental";
    }

    @Override
    public String getDeleteQuery(int id) {
        return "DELETE FROM car_rental WHERE rental_id = " + id;
    }

    @Override
    public String getDeleteAllQuery() {
        return "DELETE FROM car_rental";
    }

    @Override
    public String getInsertQuery(CarRental object) {
        return "INSERT INTO car_rental (car_id, person_id, start_date, end_date) VALUES (" +
                "" + object.getCar_id() + "," +
                "" + object.getPerson_id() + "," +
                "'" + object.getStart_date() + "'," +
                "'" + object.getEnd_date() +
                "')";
    }

    @Override
    public String getUpdateQuery(CarRental object, int id) {
        return "UPDATE car_rental SET " +
                "rental_id = " + object.getRental_id() + ", " +
                "car_id = " + object.getCar_id() + ", " +
                "person_id = " + object.getPerson_id() + ", " +
                "start_date = '" + object.getStart_date() + "', " +
                "end_date = '" + object.getEnd_date()  +
                "' WHERE rental_id = " + id;
    }
}

package models;

import interfaces.ModelInterface;

import java.sql.ResultSet;
import java.sql.SQLException;

public class Car implements ModelInterface<Car> {

    private int car_id;
    private int company_id;
    private String car_properties;
    private int daily_price;

    public Car() {
    }

    public int getCar_id() {
        return car_id;
    }

    public void setCar_id(int car_id) {
        this.car_id = car_id;
    }

    public int getCompany_id() {
        return company_id;
    }

    public void setCompany_id(int company_id) {
        this.company_id = company_id;
    }

    public String getCar_properties() {
        return car_properties;
    }

    public void setCar_properties(String car_properties) {
        this.car_properties = car_properties;
    }

    public int getDaily_price() {
        return daily_price;
    }

    public void setDaily_price(int daily_price) {
        this.daily_price = daily_price;
    }

    public Car(int car_id, int company_id, String car_properties, int daily_price) {
        this.car_id = car_id;
        this.company_id = company_id;
        this.car_properties = car_properties;
        this.daily_price = daily_price;
    }

    @Override
    public Car exportTableInstance(ResultSet rs) throws SQLException {
        return new Car(
                rs.getInt("car_id"),
                rs.getInt("company_id"),
                rs.getString("car_properties"),
                rs.getInt("daily_price")
        );
    }

    @Override
    public String getSelectQuery(int id) {
        return "SELECT * FROM car WHERE car_id = " + id;
    }

    @Override
    public String getSelectAllQuery() {
        return "SELECT * FROM select_car";
    }

    @Override
    public String getDeleteQuery(int id) {
        return "DELETE FROM car WHERE car_id = " + id;
    }

    @Override
    public String getDeleteAllQuery() {
        return "DELETE FROM car";
    }

    @Override
    public String getInsertQuery(Car object) {
        return "INSERT INTO car (car_id, company_id, car_properties, daily_price) VALUES (" +
                "'" + object.getCar_id() + "'," +
                "'" + object.getCompany_id() + "'," +
                "'" + object.getCar_properties() + "'," +
                "'" + object.getDaily_price() +
                ")";
    }

    @Override
    public String getUpdateQuery(Car object, int id) {
        return "UPDATE car SET " +
                "car_id = " + object.getCar_id() + ", " +
                "company_id = " + object.getCompany_id() + ", " +
                "car_properties = '" + object.getCar_properties() + "', " +
                "daily_price = " + object.getDaily_price() +
                " WHERE car_id = " + id;
    }
}

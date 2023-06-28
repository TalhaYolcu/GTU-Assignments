package models;

import interfaces.ModelInterface;

import java.sql.ResultSet;
import java.sql.SQLException;

public class Tour implements ModelInterface<Tour> {

    private int tour_id;
    private int person_id;
    private int company_id;
    private int acc_id;
    private int transport_id;
    private int total_price;

    public Tour() {
    }

    public int getTour_id() {
        return tour_id;
    }

    public void setTour_id(int tour_id) {
        this.tour_id = tour_id;
    }

    public int getPerson_id() {
        return person_id;
    }

    public void setPerson_id(int person_id) {
        this.person_id = person_id;
    }

    public int getCompany_id() {
        return company_id;
    }

    public void setCompany_id(int company_id) {
        this.company_id = company_id;
    }

    public int getAcc_id() {
        return acc_id;
    }

    public void setAcc_id(int acc_id) {
        this.acc_id = acc_id;
    }

    public int getTransport_id() {
        return transport_id;
    }

    public void setTransport_id(int transport_id) {
        this.transport_id = transport_id;
    }

    public int getTotal_price() {
        return total_price;
    }

    public void setTotal_price(int total_price) {
        this.total_price = total_price;
    }

    public Tour(int tour_id, int person_id, int company_id, int acc_id, int transport_id, int total_price) {
        this.tour_id = tour_id;
        this.person_id = person_id;
        this.company_id = company_id;
        this.acc_id = acc_id;
        this.transport_id = transport_id;
        this.total_price = total_price;
    }

    @Override
    public Tour exportTableInstance(ResultSet rs) throws SQLException {
        return new Tour(
                rs.getInt("tour_id"),
                rs.getInt("person_id"),
                rs.getInt("company_id"),
                rs.getInt("acc_id"),
                rs.getInt("transport_id"),
                rs.getInt("total_price")
        );
    }

    @Override
    public String getSelectQuery(int id) {
        return "SELECT * FROM tour WHERE tour_id = " + id;
    }

    @Override
    public String getSelectAllQuery() {
        return "SELECT * FROM tour";
    }

    @Override
    public String getDeleteQuery(int id) {
        return "DELETE FROM tour WHERE tour_id = " + id;
    }

    @Override
    public String getDeleteAllQuery() {
        return "DELETE FROM tour";
    }

    @Override
    public String getInsertQuery(Tour object) {
        return "INSERT INTO tour (tour_id, person_id, company_id, acc_id, transport_id, total_price) VALUES (" +
                "'" + object.getTour_id() + "'," +
                "'" + object.getPerson_id() + "'," +
                "'" + object.getCompany_id() + "'," +
                "'" + object.getAcc_id() + "'," +
                "'" + object.getTransport_id() + "'," +
                "'" + object.getTotal_price() +
                ")";
    }

    @Override
    public String getUpdateQuery(Tour object, int id) {
        return "UPDATE tour SET " +
                "tour_id = '" + object.getTour_id() + "', " +
                "person_id = '" + object.getPerson_id() + "', " +
                "company_id = '" + object.getCompany_id() + "', " +
                "acc_id = '" + object.getAcc_id() + "', " +
                "transport_id = '" + object.getTransport_id() + "', " +
                "total_price = '" + object.getTotal_price() +
                " WHERE tour_id = " + id;
    }
}

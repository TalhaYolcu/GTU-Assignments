package models;

import interfaces.ModelInterface;

import java.sql.ResultSet;
import java.sql.SQLException;

public class Transport implements ModelInterface<Transport> {

    private int transport_id;
    private int company_id;
    private int respective_id;
    private int person_id;
    private String transport_type;

    public Transport() {
    }

    public int getTransport_id() {
        return transport_id;
    }

    public void setTransport_id(int transport_id) {
        this.transport_id = transport_id;
    }

    public int getCompany_id() {
        return company_id;
    }

    public void setCompany_id(int company_id) {
        this.company_id = company_id;
    }

    public int getRespective_id() {
        return respective_id;
    }

    public void setRespective_id(int respective_id) {
        this.respective_id = respective_id;
    }

    public int getPerson_id() {
        return person_id;
    }

    public void setPerson_id(int person_id) {
        this.person_id = person_id;
    }

    public String getTransport_type() {
        return transport_type;
    }

    public void setTransport_type(String transport_type) {
        this.transport_type = transport_type;
    }

    public Transport(int transport_id, int company_id, int respective_id, int person_id, String transport_type) {
        this.transport_id = transport_id;
        this.company_id = company_id;
        this.respective_id = respective_id;
        this.person_id = person_id;
        this.transport_type = transport_type;
    }

    @Override
    public Transport exportTableInstance(ResultSet rs) throws SQLException {
        return new Transport(
                rs.getInt("transport_id"),
                rs.getInt("company_id"),
                rs.getInt("respective_id"),
                rs.getInt("person_id"),
                rs.getString("transport_type")
        );
    }

    @Override
    public String getSelectQuery(int id) {
        return "SELECT * FROM transport WHERE transport_id = " + id;
    }

    @Override
    public String getSelectAllQuery() {
        return "SELECT * FROM transport";
    }

    @Override
    public String getDeleteQuery(int id) {
        return "DELETE FROM transport WHERE transport_id = " + id;
    }

    @Override
    public String getDeleteAllQuery() {
        return "DELETE FROM transport";
    }

    @Override
    public String getInsertQuery(Transport object) {
        return "INSERT INTO transport (company_id, respective_id, person_id, transport_type) VALUES (" +
                "" + object.getCompany_id() + "," +
                "" + object.getRespective_id() + "," +
                "" + object.getPerson_id() + "," +
                "'" + object.getTransport_type() +
                "')";
    }

    @Override
    public String getUpdateQuery(Transport object, int id) {
        return "UPDATE transport SET " +
                "transport_id = " + object.getTransport_id() + ", " +
                "company_id = " + object.getCompany_id() + ", " +
                "respective_id = " + object.getRespective_id() + ", " +
                "person_id = " + object.getPerson_id() + ", " +
                "transport_type = '" + object.getTransport_type() +
                "' WHERE transport_id = " + id;
    }
}

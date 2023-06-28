package models;

import interfaces.ModelInterface;

import java.sql.ResultSet;
import java.sql.SQLException;

public class Company implements ModelInterface<Company> {

    private int company_id;
    private String company_name;

    public Company() {
    }

    public int getCompany_id() {
        return company_id;
    }

    public void setCompany_id(int company_id) {
        this.company_id = company_id;
    }

    public String getCompany_name() {
        return company_name;
    }

    public void setCompany_name(String company_name) {
        this.company_name = company_name;
    }

    public Company(int company_id, String company_name) {
        this.company_id = company_id;
        this.company_name = company_name;
    }

    @Override
    public Company exportTableInstance(ResultSet rs) throws SQLException {
        return new Company(
                rs.getInt("company_id"),
                rs.getString("company_name")
        );
    }

    @Override
    public String getSelectQuery(int id) {
        return "SELECT * FROM company WHERE company_id = " + id;
    }

    @Override
    public String getSelectAllQuery() {
        return "SELECT * FROM company";
    }

    @Override
    public String getDeleteQuery(int id) {
        return "DELETE FROM company WHERE company_id = " + id;
    }

    @Override
    public String getDeleteAllQuery() {
        return "DELETE FROM company";
    }

    @Override
    public String getInsertQuery(Company object) {
        return "INSERT INTO company (company_id, company_name) VALUES (" +
                "'" + object.getCompany_id() + "'," +
                "'" + object.getCompany_name() +
                ")";
    }

    @Override
    public String getUpdateQuery(Company object, int id) {
        return "UPDATE company SET " +
                "company_id = '" + object.getCompany_id() + "', " +
                "company_name = '" + object.getCompany_name() +
                " WHERE company_id = " + id;
    }
}

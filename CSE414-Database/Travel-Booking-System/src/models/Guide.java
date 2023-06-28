package models;

import interfaces.ModelInterface;

import java.sql.ResultSet;
import java.sql.SQLException;

public class Guide implements ModelInterface<Guide> {

    private int guide_id;
    private int company_id;
    private int person_id;

    public Guide() {
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

    public int getPerson_id() {
        return person_id;
    }

    public void setPerson_id(int person_id) {
        this.person_id = person_id;
    }

    public Guide(int guide_id, int company_id, int person_id) {
        this.guide_id = guide_id;
        this.company_id = company_id;
        this.person_id = person_id;
    }

    @Override
    public Guide exportTableInstance(ResultSet rs) throws SQLException {
        return new Guide(
                rs.getInt("guide_id"),
                rs.getInt("company_id"),
                rs.getInt("person_id")
        );
    }

    @Override
    public String getSelectQuery(int id) {
        return "SELECT * FROM guide WHERE guide_id = " + id;
    }

    @Override
    public String getSelectAllQuery() {
        return "SELECT * FROM guide";
    }

    @Override
    public String getDeleteQuery(int id) {
        return "DELETE FROM guide WHERE guide_id = " + id;
    }

    @Override
    public String getDeleteAllQuery() {
        return "DELETE FROM guide";
    }

    @Override
    public String getInsertQuery(Guide object) {
        return "INSERT INTO guide (guide_id, company_id, person_id) VALUES (" +
                "" + object.getGuide_id() + "," +
                "" + object.getCompany_id() + "," +
                "" + object.getPerson_id() +
                ")";
    }

    @Override
    public String getUpdateQuery(Guide object, int id) {
        return "UPDATE guide SET " +
                "guide_id = " + object.getGuide_id() + ", " +
                "company_id = " + object.getCompany_id() + ", " +
                "person_id = " + object.getPerson_id() +
                " WHERE guide_id = " + id;
    }
}

package models;

import interfaces.ModelInterface;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Date;

public class Person implements ModelInterface<Person> {

    private int person_id;
    private String name;
    private Date birthdate;
    private int budget;

    public Person() {
    }

    public int getPerson_id() {
        return person_id;
    }

    public void setPerson_id(int person_id) {
        this.person_id = person_id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Date getBirthdate() {
        return birthdate;
    }

    public void setBirthdate(Date birthdate) {
        this.birthdate = birthdate;
    }

    public int getBudget() {
        return budget;
    }

    public void setBudget(int budget) {
        this.budget = budget;
    }

    public Person(int person_id, String name, Date birthdate, int budget) {
        this.person_id = person_id;
        this.name = name;
        this.birthdate = birthdate;
        this.budget = budget;
    }

    @Override
    public Person exportTableInstance(ResultSet rs) throws SQLException {
        return new Person(
                rs.getInt("person_id"),
                rs.getString("name"),
                rs.getDate("birthdate"),
                rs.getInt("budget")
        );
    }

    @Override
    public String getSelectQuery(int id) {
        return "SELECT * FROM person WHERE person_id = " + id;
    }

    @Override
    public String getSelectAllQuery() {
        return "SELECT * FROM person";
    }

    @Override
    public String getDeleteQuery(int id) {
        return "DELETE FROM person WHERE person_id = " + id;
    }

    @Override
    public String getDeleteAllQuery() {
        return "DELETE FROM person";
    }

    @Override
    public String getInsertQuery(Person object) {
        return "INSERT INTO person (person_id, name, birthdate, budget) VALUES (" +
                "" + object.getPerson_id() + "," +
                "'" + object.getName() + "'," +
                "'" + object.getBirthdate() + "'," +
                "" + object.getBudget() +
                ")";
    }

    @Override
    public String getUpdateQuery(Person object, int id) {
        return "UPDATE person SET " +
                "person_id = " + object.getPerson_id() + ", " +
                "name = '" + object.getName() + "', " +
                "birthdate = '" + object.getBirthdate() + "', " +
                "budget = " + object.getBudget() +
                " WHERE person_id = " + id;
    }
}

package yyolcu2018;

/**
 * Abstract class that represents a person
 */
public abstract class Person implements User{
    /**
     * is person login
     */
    private boolean login;
    /**
     * ID
     */
    private String ID;
    /**
     * password
     */
    private String password;
    /**
     * Name of the user
     */
    private String name;

    /**
     * Constructor that initializes the fields null/false
     */
    public Person() {
        login=false;
        ID=null;
        password=null;
        name=null;
    }

    /**
     * Constructor that takes parameters and initializes the data fields
     * @param id ID
     * @param password1 password
     * @param name name
     */
    public Person(String id,String password1,String name) {
        ID=id;
        password=password1;
        login=false;
        this.name=name;
    }

    /**
     * person wants to login
     * @param id ID
     * @param password password
     */
    @Override
    public void login(String id,String password) {
        if(login) {
            System.out.println("User already login");
        }
        else if(id.equals(getId()) && password.equals(getPassword())) {
            login=true;
            System.out.println("Login successful");
        }
        else {
            System.out.println("ID or password is incorrect");
        }
    }

    /**
     * setter for ID
     * @param id1 ID
     */
    @Override
    public void setId(String id1) {
        ID=id1;
    }

    /**
     * setter for password
     * @param password1 password
     */
    @Override
    public void setPassword(String password1) {
        password=password1;
    }

    /**
     * setter for login
     * @param log login
     */
    @Override
    public void setLogin(boolean log) {
        login=log;
    }

    /**
     * getter for ID
     * @return ID
     */
    @Override
    public String getId() {
        return ID;
    }

    /**
     * Getter for Name
     * @return Name
     */
    public String getName() {return name;}

    /**
     * getter for password
     * @return password
     */
    @Override
    public String getPassword() {
        return password;
    }

    /**
     * returns user login or not
     * @return user login or not
     */
    @Override
    public boolean isLogin() {
        return login;
    }
}

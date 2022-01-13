package yyolcu2018;

/**
 * interface for Users
 */
public interface User {
    /**
     * represents an ID
     */
    String ID=null;
    /**
     * Represents password
     */
    String password=null;
    /**
     * Represents login situation
     */
    boolean login=false;

    /**
     * Ensures to login the user
     * @param id ID
     * @param password password
     */
    void login(String id,String password);

    /**
     * setter for ID
     * @param id1 ID
     */
    void setId(String id1);

    /**
     * setter for password
     * @param password1 password
     */
    void setPassword(String password1);

    /**
     * Setter for Login
     * @param log login
     */
    void setLogin(boolean log);

    /**
     * getter for ID
     * @return ID
     */
    String getId();

    /**
     * Getter for password
     * @return password
     */
    String getPassword();

    /**
     * returns user login or not
     * @return user login or not
     */
    boolean isLogin();
}

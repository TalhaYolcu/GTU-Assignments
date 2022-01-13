/**
 * @author Yakup Talha Yolcu
 */
package yyolcu2018;

import javax.naming.OperationNotSupportedException;

/**
 * Class that represents the Person
 */
public class Person implements Person_Interface{
    /**
     * name of the person
     */
    private final String name;
    /**
     * surname of the person
     */
    private final String surname;
    /**
     * e mail of the person
     */
    private final String e_mail;
    /**
     * password of the person
     */
    private final String password;
    /**
     * Person subscribed
     */
    private boolean sub=false;

    /**
     * Simple constructor
     * @param n name of person
     * @param s surname of person
     * @param e e mail of person
     * @param p password of person
     */
    public Person(String n,String s,String e,String p) {
        name=n;
        surname=s;
        e_mail=e;
        password=p;
    }

    /**
     * Copy constructor
     * @param p1 Person that will be copied
     */
    public Person(Person p1) {
        this.name=p1.getName();
        this.surname=p1.getSurname();
        this.e_mail=p1.getE_mail();
        this.password=p1.getPassword();
        this.sub=p1.sub;
    }

    /**
     * Returns the name
     * @return name
     */
    protected String getName() {return name;}

    /**
     * Returns the surname
     * @return surname
     */
    protected String getSurname() {return  surname;}

    /**
     * Returns the e mail
     * @return e mail
     */
    protected String getE_mail() {return  e_mail;}

    /**
     * Returns the password
     * @return password
     */
    protected String getPassword() {return  password;}

    /**
     * Returns the subscription situation
     * @return subscription situation
     */
    public boolean get_sub() {
        return sub;
    }

    /**
     * Person subscribes to the system and new Customer created
     * @param be1 Branch employee which creates customer
     * @return Customer
     * @throws AlreadyExistException If this person is already Customer
     */
    public Customer subscribe(BranchEmployee be1) throws AlreadyExistException {
        if(get_sub()) {
            throw new AlreadyExistException("This person already subscribed");
        }
        try {
            Customer custom=be1.create_subscription(this);
            sub=true;
            return custom;
        }
        catch (AlreadyExistException ne) {
            throw ne;
        }
    }

    @Override
    public String toString() {
        StringBuilder str=new StringBuilder();
        str.append("Person{ name='" + name + '\'' +
                ", surname='" + surname + '\'' +
                ", e_mail='" + e_mail + '\'' +
                ", password='" + password + '\'' +
                ", sub=" + sub +
                '}');
        return str.toString();
    }
}

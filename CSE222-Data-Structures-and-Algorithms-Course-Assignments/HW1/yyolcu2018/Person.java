/**
 * @author Yakup Talha Yolcu
 */
package yyolcu2018;

/**
 * Class that represents the Person
 */
public class Person implements Person_Interface{
    /**
     * name of the person
     */
    protected String name;
    /**
     * surname of the person
     */
    protected String surname;
    /**
     * e mail of the person
     */
    protected String e_mail;
    /**
     * password of the person
     */
    protected String password;
    /**
     * whether person subscribed
     */
    protected boolean s;

    /**
     * constructor for person
     * @param n name
     * @param s surname
     * @param e email
     * @param p password
     */
    public Person(String n,String s,String e,String p) {
        name=n;
        surname=s;
        e_mail=e;
        password=p;
        this.s=false;
    }

    /**
     * person wants subsribe
     * @param b branch that will subscribed in
     * @return Customer mode of the Person
     * @throws AlreadySubscribedException if this person is already subscribed
     */
    public Customer subscribe(Branch b) throws AlreadySubscribedException{
        if(s==true) {
            throw new AlreadySubscribedException("Exception occured: This person is customer already");
        }
        else {
            s=true;
            Customer c=new Customer(b.get_name()+"_"+"CUSTOM"+String.valueOf(b.getnumofc()),this);
            b.add(c);
            return c;
        }
    }

    /**
     * return the name of the person
     * @return name of the person
     */
    public String getname() {
        return name;
    }

    /**
     * return surname of the person
     * @return surname of the person
     */
    public String getsurname() {
        return surname;
    }

    /**
     * return e mail
     * @return e mail
     */
    public String getemail() {
        return e_mail;
    }

    /**
     * return password
     * @return password
     */
    public String getpassword() {
        return password;
    }
}

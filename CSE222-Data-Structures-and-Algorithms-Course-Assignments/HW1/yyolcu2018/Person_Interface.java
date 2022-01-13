/**
 * @author Yakup Talha Yolcu
 */
package yyolcu2018;

/**
 * Interface that represents Person
 */
public interface Person_Interface {
    /**
     * name of the person
     */
    String name=null;
    /**
     * surname of the person
     */
    String surname=null;
    /**
     * e mail of the person
     */
    String e_mail=null;
    /**
     * password of the person
     */
    String password=null;

    /**
     * subscription
     * @param b branch
     * @return customer
     * @throws AlreadySubscribedException if this person is already subscribed
     */
    Customer subscribe(Branch b) throws AlreadySubscribedException;
}
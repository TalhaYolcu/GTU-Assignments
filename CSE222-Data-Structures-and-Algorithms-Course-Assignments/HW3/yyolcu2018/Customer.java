/*
  @author Yakup Talha Yolcu
 */
package yyolcu2018;

import javax.naming.OperationNotSupportedException;


/**
 * Customer class represents customers
 */
public class Customer extends Person{
    /**
     * Represents the customer number of the customer
     */
    private final String customer_number;
    /**
     * gives information about customer is log in?
     */
    private boolean log=false;
    /**
     * holds the order of the customer
     */
    private HybridList<Order> orders;

    /**
     * Simple constructor
     * @param cn customer number
     * @param p1 person
     */
    public Customer(String cn,Person p1) {
        super(p1);
        customer_number=cn;
        orders=new HybridList<Order>();
    }

    /**
     * getter for customer number
     * @return String represents the customer number
     */
    public String getCustomer_number() {
        return customer_number;
    }

    /**
     * Customer logs in to the system
     * @param cn customer number
     * @param e e-mail
     * @param p password
     * @throws AlreadyExistException If user already login
     */
    public void login(String cn,String e,String p) throws AlreadyExistException{
        /*
        If customer already loginned, throw exception
         */
        if(log) {
            throw new AlreadyExistException("User already login to the system");
        }
        if(cn.equals(customer_number) && e.equals(getE_mail()) && p.equals(getPassword())) {
            log=true;
            System.out.println("The customer with customer number " + cn +
                    " has login to the system successfully");
        }
        else {
            System.out.println("Some information is wrong,try again");
        }
    }

    /**
     * Customer lists the product of the branched
     * @param c1 company
     * @param index index of the branch
     * @throws OperationNotSupportedException If customer is not login
     */
    public void list_branch(Company c1,int index) throws OperationNotSupportedException{
        if(!log) {
            throw new OperationNotSupportedException("This customer has not login to the system yet");
        }
        else {
            System.out.println(c1.get_branch(index));
        }
    }

    /**
     * Customer lists the all of the branches
     * @param c1 company
     * @throws OperationNotSupportedException If user is not login
     */
    public void list_all(Company c1) throws OperationNotSupportedException {
        if(!log) {
            throw new OperationNotSupportedException("This customer has not login to the system yet");
        }
        else {
            for(int i=0;i<c1.get_number_of_branch();i++) {
                try {
                    list_branch(c1, i);
                }
                catch (OperationNotSupportedException ne) {
                    throw new OperationNotSupportedException();
                }
            }
        }
    }

    /**
     * Customer search for a product
     * @param c1 company
     * @param name name of the product
     * @throws OperationNotSupportedException If user is not login
     */
    public void list_product(Company c1,String name) throws OperationNotSupportedException{
        if(!log) {
            throw new OperationNotSupportedException("This customer has not login to the system yet");
        }
        else {
            TIterator<Branch> iter=c1.get_branch_iterator();
            while (iter.hasNext()) {
                Branch x=iter.next();
                System.out.println("IN BRANCH " + x.get_name());
                x.search(name);
            }
        }
    }

    /**
     * Customer buys product online
     * @param c1 company
     * @param name product name
     * @param name2 color name
     * @param stock stock number
     * @param branch_index index of the branch that will be bought from
     */
    public void buy_online(Company c1,String name,String name2,int stock,int branch_index) {
        try {
            list_all(c1);
            buy_shop(c1,c1.get_branch(branch_index),branch_index,name,stock,name2);

        }
        catch (OperationNotSupportedException ne) {
            System.out.println(ne);
        }
    }

    /**
     * Customer buys from a shop
     * @param c1 company
     * @param b1 branch
     * @param branch_index index of the branch
     * @param name name of the product
     * @param stock stock number
     * @param name2 name of the color
     */
    public void buy_shop(Company c1,Branch b1,int branch_index,String name,int stock,String name2) {
        try {
            list_branch(c1,branch_index);
            Order o=b1.get_branchemployee(0).make_sale(name,stock,name2);
            orders.add(o);
        }
        catch (OperationNotSupportedException ne) {
            System.out.println(ne);
        }
    }

    /**
     * Customer views the previous orders
     */
    public void view_previous_orders() {
        TIterator<TArrayList<Order>> iter= orders.get_iterator();
        while (iter.hasNext()) {
            System.out.println(iter.next());
        }
    }

    /**
     * Helper function for adding an order
     * @param o Order that will be added
     */
    void add_order(Order o) {
        orders.add(o);
    }
    public int get_number_of_orders() {
        return orders.size();
    }
}
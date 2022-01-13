/**
 * @author Yakup Talha Yolcu
 */
package yyolcu2018;

/**
 * Class that represents the Branch Employee
 */
public class BranchEmployee {
    /**
     * Field that holds the branch
     */
    private Branch branch;

    /**
     * Simple constructor that assigns the branch of the our branch employee
     * @param b1 Branch that will be assigned
     */
    @SuppressWarnings("unchecked")
    public BranchEmployee(Branch b1) {
        branch=b1;

    }

    /**
     * Creates subscription for person and returns customer
     * @param p1 Person that will be subscribed
     * @return Customer that will be created
     * @throws AlreadyExistException If this person is already a customer
     */
    public Customer create_subscription(Person p1) throws AlreadyExistException{
        /*
        If this user is already a customer
         */
        if(p1.get_sub()) {
            throw new AlreadyExistException("This person already subscribed");
        }
        StringBuilder str=new StringBuilder();
        str.append("CUSTOMER_");
        str.append(branch.get_name()+"_");
        str.append(branch.get_customer_size());
        Customer customer=new Customer(str.toString(),p1);
        branch.add_customer(customer);
        return customer;
    }

    /**
     * Branch Employee adds the product
     * @param p Product that will be added
     */
    public void add_product(Product p) {
        branch.add_product(p);
    }

    /**
     * Branch Employee removes the product
     * @param x Product that will be removed
     */
    public void remove_product(Product x) {
        branch.remove_product(x);
    }

    /**
     * Branch Employee changes the number of the stock of the Product
     * @param p Product that will be used
     * @param number new stock number
     */
    public void change_the_stock(Product p,int number) {
        branch.change_the_stock(p,number);
    }

    /**
     * Branch Employee queries for stock
     * @param p Product that will be queried
     */
    public void query_stock(Product p) {
        int x=branch.query_stock(p);
        System.out.println(x);
        if(x==0) {
            inform_admin(p);
        }
    }

    /**
     * Branch Employee informs admin about stocks
     * @param p Product that will be used
     */
    private void inform_admin(Product p) {
        branch.inform(p);
    }

    /**
     * Branch Employee makes a sale
     * @param name Name of the product that will be sold
     * @param stock Number of stock that customer buys
     * @param name2 Name of the color
     * @return Order is created and returnd
     */
    Order make_sale(String name,int stock,String name2) {
        Order o=branch.make_sale(name,stock,name2);
        if(o==null) {
            System.out.println("Sorry,there is not enough to buy it");
        }
        return o;
    }

    /**
     * Branch Employee views the previous orders of the customer
     * @param c1 Customer that will be used
     */
    void view_previous_orders_of_customer(Customer c1) {
        c1.view_previous_orders();
    }

    /**
     * Branch employee adds an order to the customers orders
     * @param c1 Customer that will be used
     * @param o1 Order that will be added
     */
    void add_order_to_the_customer(Customer c1,Order o1) {
        c1.add_order(o1);
    }
}
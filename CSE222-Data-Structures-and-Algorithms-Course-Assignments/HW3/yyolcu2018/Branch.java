/**
 * @author Yakup Talha Yolcu
 */
package yyolcu2018;

import javax.naming.OperationNotSupportedException;

import java.util.NoSuchElementException;

/**
 * Class that represents a Branch holds Products,Branch Employees and Customers
 */
public class Branch implements Cloneable{
    /**
     * Represents the name of the Branch
     */
    private String name;
    /**
     * ArrayList that holds the branchemployees of the branch
     */
    private TArrayList<BranchEmployee> branchemployee;
    /**
     * ArrayList that holds the customers of the branch
     */
    private TArrayList<Customer> customer;
    /**
     * HybridList that represents the officechair products
     */
    private HybridList<OfficeChair> officechair;
    /**
     * HybridList that represents the officedesk products
     */
    private HybridList<OfficeDesk> officedesk;
    /**
     * HybridList that represents the bookcase products
     */
    private HybridList<Bookcase> bookcase;
    /**
     * HybridList that represents the meetingtable products
     */
    private HybridList<MeetingTable> meetingtable;
    /**
     * HybridList that represents the officecabinet products
     */
    private HybridList<OfficeCabinet> officecabinet;
    /**
     * Helps the informing admin
     */
    private boolean admin_inform=false;
    /**
     * Represents the name of the office chair product
     */
    private static final String office_chair="OCHAIR";
    /**
     * Represents the name of the office desk product
     */
    private static final String office_desk="ODESK";
    /**
     * Represents the name of the book case product
     */
    private static final String book_case="BCASE";
    /**
     * Represents the name of the meeting table product
     */
    private static final String meeting_table="MTABLE";
    /**
     * Represents the name of the office cabinet product
     */
    private static final String office_cabinet="OCABINET";

    /**
     * Constructor that takes a String as a branch name and creates hybridlists
     * @param n Branch name
     */
    public Branch(String n) {
        /*
        We should create needed things like Hybridlists,ArrayLists
         */
        name=n;
        branchemployee=new TArrayList<>();
        customer=new TArrayList<>();
        customer.add(new Customer("NULL",new Person("NULL","NULL","NULL","NULL")));

        officechair=new HybridList<>();
        officedesk=new HybridList<>();
        bookcase=new HybridList<>();
        meetingtable=new HybridList<>();
        officecabinet=new HybridList<>();

        /*
        At the beginning we should have the products
         */

        officechair.add(new OfficeChair(office_chair+"_1","BLACK",2));
        officedesk.add(new OfficeDesk(office_desk+"_1","BLUE",5));
        bookcase.add(new Bookcase(book_case+"_1","RED",10));
        meetingtable.add(new MeetingTable(meeting_table+"_1","BLACK",4));
        officecabinet.add(new OfficeCabinet(office_cabinet+"_1","BLACK",3));

        /*
        We added some branch employees
         */
        branchemployee.add(new BranchEmployee(this));

    }

    /**
     * Copy constructor
     * @param b1 Branch that will be copied
     */
    @SuppressWarnings("unchecked")
    public Branch(Branch b1) {
        /*
         * We are copying the elements
         */
        try {
            name= b1.get_name();
            branchemployee=(TArrayList<BranchEmployee>) b1.branchemployee.clone();
            customer=(TArrayList<Customer>) b1.customer.clone();
            officechair=(HybridList<OfficeChair>) officechair.clone();
            officedesk=(HybridList<OfficeDesk>) officedesk.clone();
            bookcase=(HybridList<Bookcase>) bookcase.clone();
            meetingtable=(HybridList<MeetingTable>) meetingtable.clone();
            officecabinet=(HybridList<OfficeCabinet>) officecabinet.clone();

            admin_inform=b1.admin_inform;
        }
        catch (CloneNotSupportedException ne) {
            System.out.println(ne);
        }
    }

    /**
     * Overridden clone method
     * @return Cloned object
     * @throws CloneNotSupportedException If there is something wrong with the cloning
     */
    @SuppressWarnings("unchecked")
    protected Object clone() throws CloneNotSupportedException{

        /*
         * Clone everything
         */
        try {
            Branch c=(Branch)super.clone();
            c.name=name;
            c.customer=(TArrayList<Customer>) customer.clone();
            c.branchemployee=(TArrayList<BranchEmployee>) branchemployee.clone();
            c.officechair=(HybridList<OfficeChair>) officechair.clone();
            c.officedesk=(HybridList<OfficeDesk>) officedesk.clone();
            c.bookcase=(HybridList<Bookcase>) bookcase.clone();
            c.meetingtable=(HybridList<MeetingTable>) meetingtable.clone();
            c.officecabinet=(HybridList<OfficeCabinet>) officecabinet.clone();
            c.admin_inform=admin_inform;
            return c;
        }
        catch (CloneNotSupportedException ne) {
            throw ne;
        }

    }

    /**
     * Return the customer arraylist
     * @return customer arraylist
     */
    public TArrayList<Customer> get_customer() {
        return customer;
    }

    /**
     * Return the customer arraylist's size
     * @return customer arraylist's size
     */
    public int get_customer_size() {
        return customer.size();
    }

    /**
     * Return a branch employee in that index
     * @param index index of the branch employee
     * @return Branch Employee
     */
    public BranchEmployee get_branchemployee(int index) {
        return branchemployee.get(index);
    }

    /**
     * Return the name of the Branch
     * @return name of the Branch
     */
    public String get_name() {
        return name;
    }

    /**
     * Helper function for adding a branch employee
     */
    void add_branch_employee() {
        branchemployee.add(new BranchEmployee(this));
    }

    /**
     * Return the number of branch employee in that branch
     * @return integer that number of the branch employees
     */
    public int get_number_of_branch_employee() {
        return branchemployee.size();
    }

    /**
     * Helper function for adding a customer to the system
     * @param customer1 Customer that will be added
     */
    void add_customer(Customer customer1) {
        customer.add(customer1);
    }

    /**
     * Helper function for removing a branch employee from the system
     */
    void remove_branch_employee() {
        branchemployee.remove(branchemployee.size()-1);
    }

    /**
     * Overriden toString method
     * @return String that represents the Branch
     */
    public String toString() {
        StringBuilder str=new StringBuilder();
        str.append("THIS IS " + get_name());
        str.append("\nPRODUCT NAME\tCOLOR\tSTOCK\n");
        str.append(officechair.toString());
        str.append(officedesk.toString());
        str.append(bookcase.toString());
        str.append(meetingtable.toString());
        str.append(officecabinet.toString());

        return str.toString();
    }

    /**
     * Helper function for adding a product
     * @param p Product that will be added
     * @throws NoSuchElementException If there is no product like this, it will be thrown
     */
    void add_product(Product p) throws NoSuchElementException{
        if(p instanceof OfficeChair) {
            officechair.add((OfficeChair)p);
        }
        else if(p instanceof OfficeDesk) {
            officedesk.add((OfficeDesk) p);
        }
        else if(p instanceof Bookcase) {
            bookcase.add((Bookcase) p);
        }
        else if(p instanceof MeetingTable) {
            meetingtable.add((MeetingTable) p);
        }
        else if(p instanceof OfficeCabinet) {
            officecabinet.add((OfficeCabinet) p);
        }
        else {
            throw new NoSuchElementException("Wrong product");
        }
    }

    /**
     * Helper function for removing a product
     * @param p Product that gives us information about product which will be removed
     */
    void remove_product(Product p) {
        if(p instanceof OfficeChair) {
            officechair.remove((OfficeChair)p);
        }
        else if(p instanceof OfficeDesk) {
            officedesk.remove((OfficeDesk) p);
        }
        else if(p instanceof Bookcase) {
            bookcase.remove((Bookcase) p);
        }
        else if(p instanceof MeetingTable) {
            meetingtable.remove((MeetingTable) p);
        }
        else if(p instanceof OfficeCabinet) {
            officecabinet.remove((OfficeCabinet) p);
        }
        else {
            throw new NoSuchElementException("Wrong product");
        }
    }

    /**
     * Helper function for changing the stock of the products
     * @param p Product that will be used
     * @param number number of stock will be used
     */
    void change_the_stock(Product p,int number) {
        if(p instanceof OfficeChair) {
            officechair.change_the_stock((OfficeChair)p,number);
        }
        else if(p instanceof OfficeDesk) {
            officedesk.change_the_stock((OfficeDesk) p,number);
        }
        else if(p instanceof Bookcase) {
            bookcase.change_the_stock((Bookcase) p,number);
        }
        else if(p instanceof MeetingTable) {
            meetingtable.change_the_stock((MeetingTable) p,number);
        }
        else if(p instanceof OfficeCabinet) {
            officecabinet.change_the_stock((OfficeCabinet) p,number);
        }
        else {
            throw new NoSuchElementException("Wrong product");
        }
    }

    /**
     * Helper function for querying a stock of the product
     * @param p Product that will be queried
     * @return stock
     */
    int query_stock(Product p) {
        int x=0;
        if(p instanceof OfficeChair) {
            x=officechair.query((OfficeChair)p);
        }
        else if(p instanceof OfficeDesk) {
            x=officedesk.query((OfficeDesk) p);
        }
        else if(p instanceof Bookcase) {
            x=bookcase.query((Bookcase) p);
        }
        else if(p instanceof MeetingTable) {
            x=meetingtable.query((MeetingTable) p);
        }
        else if(p instanceof OfficeCabinet) {
            x=officecabinet.query((OfficeCabinet) p);
        }
        else {
            throw new NoSuchElementException("Wrong product");
        }
        return x;
    }

    /**
     * helper function for informing the admin
     * @param p Product that admin that will be informed about
     */
    void inform(Product p) {
        admin_inform=true;
    }

    /**
     * Helper function for informing
     * @return is admin informed?
     */
    boolean get_inform() {
        return admin_inform;
    }

    /**
     * setter for informing
     * @param x value that will be used
     */
    void set_inform(boolean x) {
        admin_inform=x;
    }

    /**
     * Helper function for searching a product with given name
     * @param name Name of the product
     * @throws NoSuchElementException when product can't be found
     */
    void search(String name) throws NoSuchElementException{
        /*
         * Depend on the name, determine the product and search for it
         */
        int count=0;
        if(name.contains(office_chair)) {
            TIterator<TArrayList<OfficeChair>> iter=officechair.get_iterator();
            while (iter.hasNext()) {
                TArrayList<OfficeChair> x=iter.next();
                TIterator<OfficeChair> iter2=x.iterator();
                while (iter2.hasNext()) {
                    OfficeChair p1=iter2.next();
                    if(name.equals(p1.get_model_name())) {
                        System.out.println(name + "\t\t" + p1.get_color_name() + "\t\t" + p1.get_stock()+"\n");
                        count+=1;
                    }
                }
            }
        }
        else if(name.contains(office_desk)) {
            TIterator<TArrayList<OfficeDesk>> iter=officedesk.get_iterator();
            while (iter.hasNext()) {
                TArrayList<OfficeDesk> x=iter.next();
                TIterator<OfficeDesk> iter2=x.iterator();
                while (iter2.hasNext()) {
                    OfficeDesk p1=iter2.next();
                    if(name.equals(p1.get_model_name())) {
                        System.out.println(name + "\t\t" + p1.get_color_name() + "\t\t" + p1.get_stock()+"\n");
                        count+=1;
                    }
                }
            }
        }
        else if(name.contains(meeting_table)) {
            TIterator<TArrayList<MeetingTable>> iter=meetingtable.get_iterator();
            while (iter.hasNext()) {
                TArrayList<MeetingTable> x=iter.next();
                TIterator<MeetingTable> iter2=x.iterator();
                while (iter2.hasNext()) {
                    MeetingTable p1=iter2.next();
                    if(name.equals(p1.get_model_name())) {
                        System.out.println(name + "\t\t" + p1.get_color_name() + "\t\t" + p1.get_stock()+"\n");
                        count+=1;
                    }
                }
            }
        }
        else if(name.contains(book_case)) {
            TIterator<TArrayList<Bookcase>> iter=bookcase.get_iterator();
            while (iter.hasNext()) {
                TArrayList<Bookcase> x=iter.next();
                TIterator<Bookcase> iter2=x.iterator();
                while (iter2.hasNext()) {
                    Bookcase p1=iter2.next();
                    if(name.equals(p1.get_model_name())) {
                        System.out.println(name + "\t\t" + p1.get_color_name() + "\t\t" + p1.get_stock()+"\n");
                        count+=1;
                    }
                }
            }
        }
        else if(name.contains(office_cabinet)) {
            TIterator<TArrayList<OfficeCabinet>> iter=officecabinet.get_iterator();
            while (iter.hasNext()) {
                TArrayList<OfficeCabinet> x=iter.next();
                TIterator<OfficeCabinet> iter2=x.iterator();
                while (iter2.hasNext()) {
                    OfficeCabinet p1=iter2.next();
                    if(name.equals(p1.get_model_name())) {
                        System.out.println(name + "\t\t" + p1.get_color_name() + "\t\t" + p1.get_stock()+"\n");
                        count+=1;
                    }
                }
            }
        }
        else {
            throw new NoSuchElementException("There is no such product with this name in this Product:" + get_name());
        }
        if(count==0) {
            System.out.println("There is no such prouct in this product with this name\n");
        }
    }

    /**
     * Helper function for make sale of the branch employee
     * @param name name of the product that will be sold
     * @param stock number of stock customer buys
     * @param name2 color name of the product
     * @return Order of the customer
     * @throws NoSuchElementException If there is no such product, it will be thrown
     */
     Order make_sale(String name,int stock,String name2) throws NoSuchElementException{
        int count=0;
         /*
          * Depend on the names, determine the product type and find it
          * Change the stock of the product
          */
        if(name.contains(office_chair)) {
            TIterator<TArrayList<OfficeChair>> iter=officechair.get_iterator();
            while (iter.hasNext()) {
                TArrayList<OfficeChair> x=iter.next();
                TIterator<OfficeChair> iter2=x.iterator();
                while (iter2.hasNext()) {
                    OfficeChair p1=iter2.next();
                    if(name.equals(p1.get_model_name())  && p1.get_stock()>=stock && p1.get_color_name().equals(name2)) {
                        p1.setStock(p1.get_stock()-stock);
                        return new Order(name,name2,stock);
                    }
                }
            }
        }
        else if(name.contains(office_desk)) {
            TIterator<TArrayList<OfficeDesk>> iter=officedesk.get_iterator();
            while (iter.hasNext()) {
                TArrayList<OfficeDesk> x=iter.next();
                TIterator<OfficeDesk> iter2=x.iterator();
                while (iter2.hasNext()) {
                    OfficeDesk p1=iter2.next();
                    if(name.equals(p1.get_model_name())  && p1.get_stock()>=stock && p1.get_color_name().equals(name2)) {
                        p1.setStock(p1.get_stock()-stock);
                        return new Order(name,name2,stock);
                    }
                }
            }
        }
        else if(name.contains(meeting_table)) {
            TIterator<TArrayList<MeetingTable>> iter=meetingtable.get_iterator();
            while (iter.hasNext()) {
                TArrayList<MeetingTable> x=iter.next();
                TIterator<MeetingTable> iter2=x.iterator();
                while (iter2.hasNext()) {
                    MeetingTable p1=iter2.next();
                    if(name.equals(p1.get_model_name())  && p1.get_stock()>=stock && p1.get_color_name().equals(name2)) {
                        p1.setStock(p1.get_stock()-stock);
                        return new Order(name,name2,stock);
                    }
                }
            }
        }
        else if(name.contains(book_case)) {
            TIterator<TArrayList<Bookcase>> iter=bookcase.get_iterator();
            while (iter.hasNext()) {
                TArrayList<Bookcase> x=iter.next();
                TIterator<Bookcase> iter2=x.iterator();
                while (iter2.hasNext()) {
                    Bookcase p1=iter2.next();
                    if(name.equals(p1.get_model_name())  && p1.get_stock()>=stock && p1.get_color_name().equals(name2)) {
                        p1.setStock(p1.get_stock()-stock);
                        return new Order(name,name2,stock);
                    }
                }
            }
        }
        else if(name.contains(office_cabinet)) {
            TIterator<TArrayList<OfficeCabinet>> iter=officecabinet.get_iterator();
            while (iter.hasNext()) {
                TArrayList<OfficeCabinet> x=iter.next();
                TIterator<OfficeCabinet> iter2=x.iterator();
                while (iter2.hasNext()) {
                    OfficeCabinet p1=iter2.next();
                    if(name.equals(p1.get_model_name())  && p1.get_stock()>=stock && p1.get_color_name().equals(name2)) {
                        p1.setStock(p1.get_stock()-stock);
                        return new Order(name,name2,stock);
                    }
                }
            }
        }
        else {
            throw new NoSuchElementException("There is no such product with this name in this Product:" + get_name());
        }
        return null;
    }
}
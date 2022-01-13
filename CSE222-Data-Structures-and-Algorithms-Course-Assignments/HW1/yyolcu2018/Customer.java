/**
 * @author Yakup Talha Yolcu
 */
package yyolcu2018;

import java.util.NoSuchElementException;

/**
 * Customer class represents customers
 */
public class Customer extends Person{
    /**
     * Did customer log in?
     */
    private boolean is_login;
    /**
     * customer number
     */
    private String customer_number;
    /**
     * did she buy something
     */
    private boolean instantbuy;
    /**
     * Orders that customer made
     */
    private Order[] orders;

    /**
     * Constructor
     * @param cn customer number
     * @param p1 person
     */
    public Customer(String cn,Person p1) {
        super(p1.name,p1.surname,p1.e_mail,p1.password);
        customer_number=cn;
        orders=new Order[1];
        orders[0]=new Order();
    }

    /**
     * list the products of the given branch
     * @param B Branch that will be listed
     * @throws NullPointerException if Branch is empty
     */
    public void list_the_branch(Branch B) throws NullPointerException{
        if(B==null) {
            throw new NullPointerException("Exception occured: This Branch does not contain any info");
        }
        System.out.println(B);
    }

    /**
     * list the whole company
     * @param c1 company that will be listed
     */
    public void list_all(Company c1) {
        for(int i=0;i<c1.getnumofb();i++) {
            try {
                System.out.println(c1.getBranch(i));
            }
            catch (NoSuchElementException ne) {
                System.out.println(ne);
            }
        }
    }

    /**
     * List the products that have the given name
     * @param c1 Company that will be listed
     * @param model_name model name that will be listed
     */
    public void list_product(Company c1,String model_name) {
        /*
        list products in the all branches
         */
        System.out.println("MODEL NAME\tSTOCK NUMBER\tBRANCH\n");
        for(int i=0;i<c1.getnumofb();i++){
            for(int k=0;k<c1.getBranch(i).getOfficeChair().getnumberofmodel();k++) {
                if(c1.getBranch(i).getOfficeChair().getModel(k).get_name().equals(model_name)) {
                    System.out.println(model_name+"\t\t\t"+c1.getBranch(i).getOfficeChair().getModel(k).getnum()+"\t"+c1.getBranch(i).get_name()+"\n");
                }
            }
            for(int k=0;k<c1.getBranch(i).getOfficeDesk().getnumberofmodel();k++) {
                if(c1.getBranch(i).getOfficeDesk().getModel(k).get_name().equals(model_name)) {
                    System.out.println(model_name+"\t\t\t"+c1.getBranch(i).getOfficeDesk().getModel(k).getnum()+"\t"+c1.getBranch(i).get_name()+"\n");
                }
            }
            for(int k=0;k<c1.getBranch(i).getMeetingTable().getnumberofmodel();k++) {
                if(c1.getBranch(i).getMeetingTable().getModel(k).get_name().equals(model_name)) {
                    System.out.println(model_name+"\t\t\t"+c1.getBranch(i).getMeetingTable().getModel(k).getnum()+"\t"+c1.getBranch(i).get_name()+"\n");
                }
            }
            for(int k=0;k<c1.getBranch(i).getBookcase().getnumberofmodel();k++) {
                if(c1.getBranch(i).getBookcase().getModel(k).get_name().equals(model_name)) {
                    System.out.println(model_name+"\t\t\t"+c1.getBranch(i).getBookcase().getModel(k).getnum()+"\t"+c1.getBranch(i).get_name()+"\n");
                }
            }
            for(int k=0;k<c1.getBranch(i).getOfficeCabinet().getnumberofmodel();k++) {
                if(c1.getBranch(i).getOfficeCabinet().getModel(k).get_name().equals(model_name)) {
                    System.out.println(model_name+"\t\t\t"+c1.getBranch(i).getOfficeCabinet().getModel(k).getnum()+"\t"+c1.getBranch(i).get_name()+"\n");
                }
            }
        }        
    }

    /**
     * buy online
     * @param c1 Company that will be buyed from
     * @param situation situation 1-5 as products
     * @param model_name model name of the product
     * @param color_name color name of the product
     * @param number stock that will be buyed
     * @throws Exception if there's something wrong such as model name,stock,situation
     */
    public void buy_online(Company c1,int situation,String model_name,String color_name,int number) throws  Exception{
        /*
        I designed buying online as buying from shop without customer knowing
         */
        if(is_login) {
            for(int i=0;i<c1.getnumofb();i++) {
                try{
                    buy_shop(c1.getBranch(i),situation,model_name,color_name,number);
                    if(getinstantbuy()) {
                        if(c1.getBranch(i).getBranchEmployee(0).getstock(c1.getBranch(i), situation, model_name, color_name)==0) {
                            c1.getBranch(i).getBranchEmployee(0).informadmin(c1);
                        }
                        break;
                    }
                }
                catch (NoSuchElementException ne) {
                    System.out.println(ne);
                }

            }
            setinstantbuy(false);
        }
        else {
            throw new Exception("CUSTOMER IS NOT LOG-INNED");
        }
    }

    /**
     * buy product from a shop
     * @param b1 branch that will be buyed from
     * @param situation 1-5 as products
     * @param model_name model name of the prodducts
     * @param color_name color name of the product
     * @param number stock that will be buyed
     * @throws NoSuchElementException if there is something is wrong
     */
    public void buy_shop(Branch b1,int situation,String model_name,String color_name,int number) throws NoSuchElementException{
        if(b1.getnumofbe()==0) {
            throw new NoSuchElementException("There is no Branch Employee");
        }
        else {
            try {
                b1.getBranchEmployee(0).make_sale(this,b1,situation,model_name,color_name,number);
            }
            catch (Exception ne) {
                System.out.println(ne);
            }
        }
    }

    /**
     * view previous orders
     */
    public void view_previous_orders() {
        System.out.println("ORDERS:\n");
        System.out.println("MOEL NAME\tCOLOR\tNUMBER\n");
        for(int i=0;i<orders.length;i++) {
            System.out.println(orders[i]);
        }
    }

    /**
     * login to the system
     * @param e_mail email
     * @param password password
     * @throws NoSuchElementException e mail or password is wrong
     */
    public void login(String e_mail,String password) throws  NoSuchElementException{
        if(this.getemail().equals(e_mail) && this.getpassword().equals(password)) {
            System.out.println("LOGIN IS SUCCESFUL");
            is_login=true;
        }
        else {
            throw new NoSuchElementException("E mail or password is not correct");
        }
    }

    /**
     * getter for customer number
     * @return customer number as a string
     */
    public String getCustomerNumber() {
        return customer_number;
    }

    /**
     * overridden string method for customer
     * @return String
     */
    public String toString() {
        String x=new String("NAME\tSURNAME\t\tE-MAIL\tPASSWORD\tCUSTOMER NUMBER\n");
        x+=String.format("%s\t%s\t%10s\t%s\t%s\n",getname(),getsurname(),getemail(),getpassword(),getCustomerNumber());
        return x;
    }

    /**
     * setter for instant buy
     * @param x did customer buy anything
     */
    public void setinstantbuy(boolean x) {
        instantbuy=x;
    }

    /**
     * getter for instant buy
     * @return did customer buy anything
     */
    public boolean getinstantbuy() {
        return instantbuy;
    }

    /**
     * return order array
     * @return order array
     */
    public Order[] getOrder() {
        return orders;
    }
}
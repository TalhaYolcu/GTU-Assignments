/**
 * @author Yakup Talha Yolcu
 */
package yyolcu2018;

/**
 * Class that represents the Branch Employee
 */
public class BranchEmployee {
    /**
     * field that represents supply need
     */
    private boolean supplyneed;
    /**
     * did I sell sth?
     */
    private boolean sold;
    /**
     * did I add sth?
     */
    private boolean added;
    /**
     * Branch
     */
    private Branch b;

    /**
     * Constuctor
     */
    public BranchEmployee() {
        supplyneed=false;
    }

    /**
     * inform admin about supply need
     * @param c1 Company
     */
    public void informadmin(Company c1) {
        c1.informadmin(c1.getAdmin(0));
    }

    /**
     * get the stock of the Product
     * @param b1 Branch that will be checked
     * @param situation represent product as 1-5
     * @param model_name model name
     * @param color_name color name
     * @return return the stock number
     */
    public int getstock(Branch b1,int situation,String model_name,String color_name) {
        return b1.get_stock(model_name,situation,color_name);
    }

    /**
     * add the product the given branch
     * @param b1 branch
     * @param o1 product
     */
    public void add_product(Branch b1,OfficeChair o1) {
        b1.add(o1);
        added=true;
    }
    /**
     * add the product the given branch
     * @param b1 branch
     * @param od1 product
     */
    public void add_product(Branch b1,OfficeDesk od1) {
        b1.add(od1);
        added=true;
    }
    /**
     * add the product the given branch
     * @param b1 branch
     * @param mt1 product
     */
    public void add_product(Branch b1,MeetingTable mt1) {
        b1.add(mt1);
        added=true;
    }
    /**
     * add the product the given branch
     * @param b1 branch
     * @param bc1 product
     */
    public void add_product(Branch b1,Bookcase bc1) {
        b1.add(bc1);
        added=true;
    }

    /**
     * Add product to given branch
     * @param b1 branch
     * @param ocab1 product
     */
    public void add_product(Branch b1,OfficeCabinet ocab1) {
        b1.add(ocab1);
        added=true;
    }

    /**
     * Add product to given branch with name and color
     * @param b1 branch
     * @param situation situations 1-5 as products
     * @param model_name model name
     * @param color_name color name
     * @param stock stock
     */
    public void add_product(Branch b1,int situation,String model_name,String color_name,int stock) {
        b1.add(situation,model_name,color_name,stock);
        added=true;
    }

    /**
     * remove the given product
     * @param b1 branch
     * @param situation situation 1-5 as product
     * @param model_name model name
     * @param color_name color name
     * @param stock stock
     */
    public void remove_product(Branch b1,int situation,String model_name,String color_name,int stock) {
        b1.remove(situation,model_name,color_name,stock);
    }

    /**
     * make sale
     * @param c1 customer that will be buy sth
     * @param b1 branch that will be used
     * @param situation situation 1-5 as products
     * @param model_name model name
     * @param color_name color name
     * @param number number of the product will be buyed
     * @throws Exception If product is can't be sold for any reason, such as wrong color name,model name and number
     */
    public void make_sale(Customer c1,Branch b1,int situation,String model_name,String color_name,int number) throws Exception{
        boolean flag=false;
       /*
       find the product in the branch by looking model and color names
       situations:
       1-officechair
       2-officedesk
       3-meeting table
       4-bookcase
       5-officecabinet
        */
        switch(situation) {
            case 1:
            for(int i=0;i<b1.getOfficeChair().getnumberofmodel();i++) {
                if(b1.getOfficeChair().getModel(i).get_name().equals(model_name)) {
                    for(int k=0;k<b1.getOfficeChair().getModel(i).getnum();k++) {
                        if(b1.getOfficeChair().getModel(i).getColor(k).getcolorname().equals(color_name) && number<=b1.getOfficeChair().getModel(i).getColor(k).getnumber()) {
                            remove_product(b1,1, model_name, color_name,number);
                            add_new_order(c1.getOrder(),model_name,color_name,number);
                            c1.setinstantbuy(true);
                            flag=true;
                        }
                        if(flag==true) {
                            break;
                        }
                    }
                }
                if(flag==true) {
                    break;
                }
            }

            break;

            case 2:
            for(int i=0;i<b1.getOfficeDesk().getnumberofmodel();i++) {
                if(b1.getOfficeDesk().getModel(i).get_name().equals(model_name)) {
                    for(int k=0;k<b1.getOfficeDesk().getModel(i).getnum();k++) {
                        if(b1.getOfficeDesk().getModel(i).getColor(k).getcolorname().equals(color_name) && number<=b1.getOfficeDesk().getModel(i).getColor(k).getnumber()) {
                            remove_product(b1,situation, model_name, color_name,number);
                            add_new_order(c1.getOrder(),model_name,color_name,number);
                            c1.setinstantbuy(true);
                            flag=true;
                        }

                        if(flag==true) {
                            break;
                        }
                    }

                }
                if(flag==true) {
                    break;
                }

            }

            break; 
            
            case 3:
            for(int i=0;i<b1.getMeetingTable().getnumberofmodel();i++) {
                if(b1.getMeetingTable().getModel(i).get_name().equals(model_name)) {
                    for(int k=0;k<b1.getMeetingTable().getModel(i).getnum();k++) {
                        if(b1.getMeetingTable().getModel(i).getColor(k).getcolorname().equals(color_name) && number<=b1.getMeetingTable().getModel(i).getColor(k).getnumber()) {
                            remove_product(b1,situation, model_name, color_name,number);
                            add_new_order(c1.getOrder(),model_name,color_name,number);
                            c1.setinstantbuy(true);
                            flag=true;
                        }
                        if(flag==true) {
                            break;
                        }
                    }
                }
                if(flag==true) {
                    break;
                }
            }
            break; 

            case 4:
            for(int i=0;i<b1.getBookcase().getnumberofmodel();i++) {
                if(b1.getBookcase().getModel(i).get_name().equals(model_name)) {
                    for(int k=0;k<b1.getBookcase().getModel(i).getnum();k++) {
                        if(b1.getBookcase().getModel(i).getColor(k).getcolorname().equals(color_name) && number<=b1.getBookcase().getModel(i).getColor(k).getnumber()) {
                            remove_product(b1,situation, model_name, color_name,number);
                            add_new_order(c1.getOrder(),model_name,color_name,number);
                            c1.setinstantbuy(true);
                            flag=true;
                        }
                        if(flag==true) {
                            break;
                        }
                    }
                }
                if(flag==true) {
                    break;
                }
            }
            break; 

            case 5:
            for(int i=0;i<b1.getOfficeCabinet().getnumberofmodel();i++) {
                if(b1.getOfficeCabinet().getModel(i).get_name().equals(model_name)) {
                    for(int k=0;k<b1.getOfficeCabinet().getModel(i).getnum();k++) {
                        if(b1.getOfficeCabinet().getModel(i).getColor(k).getcolorname().equals(color_name) && number<=b1.getOfficeCabinet().getModel(i).getColor(k).getnumber()) {
                            remove_product(b1,situation, model_name, color_name,number);
                            add_new_order(c1.getOrder(),model_name,color_name,number);
                            c1.setinstantbuy(true);
                            flag=true;
                        }
                        if(flag==true) {
                            break;
                        }
                    }
                }
                if(flag==true) {
                    break;
                }
            }
            break; 
        }
        if(flag==false) {
            throw new Exception("PRODUCT COULD NOT FOUND IN "+b1.get_name());
        }
    }

    /**
     * Add a new order to given order array
     * @param orders order array that belongs to a customer
     * @param model_name model name
     * @param color_name color name of the product
     * @param number number of stock that will be added to the order
     */
    public void add_new_order(Order[] orders,String model_name,String color_name,int number) {
        /*
        add new order to our array,resize it
         */
        Order[] temp=new Order[orders.length+1];
        for(int i=0;i<orders.length;i++) {
            temp[i]=new Order(orders[i]);
        }
        temp[orders.length]=new Order(model_name,color_name,number);
        orders=new Order[temp.length];
        for(int i=0;i<orders.length;i++) {
            orders[i]=new Order(temp[i]);
        }
    }

    /**
     * View the previos orders of the given customer
     * @param c1 Customer
     */
    public void view_previous_orders(Customer c1) {
        c1.view_previous_orders();
    }

    /**
     * Create a subscription of the Person
     * @param b1 Branch of the Person
     * @param per1 person that will be added
     */
    public void create_subscription(Branch b1,Person per1) {

        try {
            b1.create_subscription(per1);
        }
        catch (AlreadyExistException ne) {
            System.out.println(ne);
        }

    }

    /**
     * did I sold sth?
     * @return did I sold sth?
     */
    public boolean sold() {
        return sold;
    }

    /**
     * did I add sth?
     * @return did I add sth?
     */
    public boolean is_added() {
        return added;
    }
}
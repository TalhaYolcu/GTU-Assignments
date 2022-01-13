/**
 * @author Yakup Talha Yolcu
 */
package yyolcu2018;

import java.util.NoSuchElementException;

/**
 * Class that represents a Branch holds Products,Branch Employees and Customers
 */
public class Branch {

    /**
     * represent officechair
     */
    private OfficeChair ochairs;
    /**
     * represent officedesk
     */
    private OfficeDesk odesks;
    /**
     * represent meeting table
     */
    private MeetingTable mtables;
    /**
     * represent bookcase
     */
    private Bookcase bcases;
    /**
     * represent officecabinet
     */
    private OfficeCabinet ocabs;
    /**
     * is any product needed
     */
    private boolean need=false;
    /**
     * number of branch employees
     */
    private int numofbe;
    /**
     * name of the Branch
     */
    private String name;
    /**
     * Branch employees
     */
    private BranchEmployee[] BE;
    /**
     * number of customers
     */
    private int numofc;
    /**
     * customers
     */
    private Customer[] customers;

    /**
     * Constructor
     * @param name Branch name
     * @param numofbe Number of branch employees
     */
    public Branch(String name,int numofbe) {
        this.name=name;
        this.numofbe=numofbe;
        ochairs=new OfficeChair();
        odesks=new OfficeDesk();
        mtables=new MeetingTable();
        bcases=new Bookcase();
        ocabs=new OfficeCabinet();
        BE=new BranchEmployee[getnumofbe()];
        /*
        adding branch employees
         */
        for(int i=0;i<getnumofbe();i++) {
            BE[i]=new BranchEmployee();
        }
        customers=new Customer[1];
        numofc=1;

        Person p1=new Person("NAME"+String.valueOf(getnumofc()),"SURNAME"+String.valueOf(getnumofc()),"E-MAIL"+String.valueOf(getnumofc()),"PASSWORD"+String.valueOf(getnumofc()));
        customers[0]=new Customer(this.name+"_"+"CUSTOM"+String.valueOf(getnumofc()),p1);
        numofc+=1;
    }

    /**
     * Overridden toString method
     * @return String contains branch info
     */
    public String toString() {
        String x=new String("BRANCH: "+get_name()+"\n");
        x+=ochairs;
        x+=odesks;
        x+=mtables;
        x+=bcases;
        x+=ocabs;
        return x;   
    }

    /**
     * return the name of the branch
     * @return name of the branch
     */
    public String get_name() {
        return name;
    }

    /**
     * return number of branch emoployees
     * @return number of branch employees
     */
    public int getnumofbe() {
        return numofbe;
    }

    /**
     * return number of customers
     * @return return number of customers
     */
    public int getnumofc() {
        return numofc;
    }

    /**
     * return size of customer array
     * @return size of customer array
     */
    public int getsize() {
        return customers.length;
    }

    /**
     * add a Customer to the Branch, (Branch Employee calls this method)
     * @param c1 Customer that will be added
     */
    public void add(Customer c1) {
        try {
            create_subscription(c1);
        }
        catch (AlreadyExistException ne) {
            System.out.println(ne);
        }
    }

    /**
     * return Officechair
     * @return officechair
     */
    public OfficeChair getOfficeChair() {
        return ochairs;
    }
    /**
     * return Officedesk
     * @return officedesk
     */
    public OfficeDesk getOfficeDesk() {
        return odesks;
    }
    /**
     * return Meetingtable
     * @return meetingtable
     */
    public MeetingTable getMeetingTable() {
        return mtables;
    }
    /**
     * return Bookcase
     * @return Bookcase
     */
    public Bookcase getBookcase() {
        return bcases;
    }
    /**
     * return Officecabinet
     * @return Officecabinet
     */
    public OfficeCabinet getOfficeCabinet() {
        return ocabs;
    }

    /**
     * add-remove branch employee (admin calls it)
     */
    public void resize_branch_employee() {
        /*
        resize branch employees
         */
        BranchEmployee[] temp=new BranchEmployee[getnumofbe()+1];
        for(int i=0;i<getnumofbe();i++) {
            temp[i]=new BranchEmployee();
        }
        temp[getnumofbe()]=new BranchEmployee();
        numofbe+=1;
        BE=new BranchEmployee[numofbe];
        for(int i=0;i<getnumofbe();i++){
            BE[i]=temp[i];
        }
    }

    /**
     * remove branch employee
     * @throws NoSuchElementException there is no Branch employee in this index
     */
    public void remove_branch_employee() throws NoSuchElementException{
        if(getnumofbe()==0) {
            throw new NoSuchElementException("Exception occured,There is no BE to remove");
        }
        BE[getnumofbe()-1]=null;
        numofbe-=1;
    }

    /**
     * add Officechair
     * @param o1 officechair
     */
    public void add(OfficeChair o1) {
        ochairs.add(o1);
    }
    /**
     * add Officedesk
     * @param o1 officedesk
     */
    public void add(OfficeDesk o1) {
        odesks.add(o1);
    }
    /**
     * add Meetingtable
     * @param o1 Meetingtable
     */
    public void add(MeetingTable o1) {
        mtables.add(o1);
    }
    /**
     * add Bookcase
     * @param o1 bookcase
     */
    public void add(Bookcase o1) {
        bcases.add(o1);
    }
    /**
     * add Officecabinet
     * @param o1 officecabinet
     */
    public void add(OfficeCabinet o1) {
        ocabs.add(o1);
    }

    /**
     * Add a product depend on the situation
     * @param situation 1- Officechair 2- OfficeDesk 3- MeetingTable 4- Bookcase 5- OfficeCabinet
     * @param model_name model name
     * @param color_name color name
     * @param stock number of stock that will be added
     */
    public void add(int situation,String model_name,String color_name,int stock) {
        switch(situation) {
            case 1:
            ochairs.add(model_name,color_name,stock);  
            break;

            case 2:
            odesks.add(model_name,color_name,stock);  
            break;       
            
            case 3:
            mtables.add(model_name,color_name,stock);  
            break; 

            case 4:
            bcases.add(model_name,color_name,stock);  
            break;

            case 5:
            ocabs.add(model_name,color_name,stock);  
            break;   

            default:
            break;
        }       
    }

    /**
     * Add a product depend on the situation
     * @param situation 1- Officechair 2- OfficeDesk 3- MeetingTable 4- Bookcase 5- OfficeCabinet
     * @param model_name model name
     * @param color_name color name
     * @param stock number of stock will be removed
     */
    public void remove(int situation,String model_name,String color_name,int stock) {
        try {
            switch(situation) {
                case 1:
                    ochairs.remove(model_name,color_name,stock);
                    break;

                case 2:
                    odesks.remove(model_name,color_name,stock);
                    break;

                case 3:
                    mtables.remove(model_name,color_name,stock);
                    break;

                case 4:
                    bcases.remove(model_name,color_name,stock);
                    break;

                case 5:
                    ocabs.remove(model_name,color_name,stock);
                    break;

                default:
                    System.out.println("WRONG SITUATION ENTERED");
                    break;
            }
        }
        catch(NoSuchElementException ne) {
            System.out.println(ne);
        }
    }

    /**
     * Branch employee calls this method to create a subscription
     * @param p1 Person that will be subscribbed
     * @throws AlreadyExistException If this person is already customer
     */
    public void create_subscription(Person p1) throws  AlreadyExistException{
        /*
        create subscription of the person and resize the array
         */
        Customer[] temp=new Customer[customers.length+1];
        for(int i=0;i<customers.length;i++) {
            if(p1.getemail().equals(customers[i].getemail()) && p1.getpassword().equals(customers[i].getpassword())) {
                throw new AlreadyExistException("Exception occured ,This person is already Customer");
            }
            temp[i]=new Customer(customers[i].getCustomerNumber(),(Person)customers[i]);
        }
        temp[customers.length]=new Customer(this.name+"_"+"CUSTOM"+String.valueOf(getnumofc()),p1);
        customers=new Customer[temp.length];
        for(int i=0;i<temp.length;i++) {
            customers[i]=new Customer(temp[i].getCustomerNumber(),(Person)temp[i]);
        }
        numofc+=1;        
    }

    /**
     * get the stock of the given product
     * @param model_name model name
     * @param situation situations:1,2,3,4,5 for products officechair is 1 etc...
     * @param color_name color name
     * @return integer that represents the number of stock of the product
     */
    public int get_stock(String model_name,int situation,String color_name) {
        int sum=0;
        switch(situation){
            case 1:
            sum=ochairs.get_stock(model_name,color_name);
            break;

            case 2:
            sum=odesks.get_stock(model_name,color_name);
            break;

            case 3:
            sum=mtables.get_stock(model_name,color_name);
            break;

            case 4:
            sum=bcases.get_stock(model_name, color_name);
            break;

            case 5:
            sum=ocabs.get_stock(model_name, color_name);
            break;

            default:
            break;
        }
        return sum;
    }

    /**
     * returns the Branch Employee
     * @param index indicates the Branch Employee
     * @return Branch Employee in the given index
     */
    public BranchEmployee getBranchEmployee(int index) {
        return BE[index];
    }
}
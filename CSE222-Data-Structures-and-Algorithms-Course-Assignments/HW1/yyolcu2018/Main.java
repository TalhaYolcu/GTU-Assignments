/**
 * @author Yakup Talha Yolcu
 */
package yyolcu2018;

import java.util.NoSuchElementException;

/**
 * Driver class
 */
public class Main {
    /**
     * Test 1
     */
    public static void test() {
        Company c1=new Company();
        Person p=new Person("Talha","Yolcu","E-MAIL","PASSWORD");
        try {
            Customer i1=p.subscribe(c1.getBranch(50));
        }
        catch(IndexOutOfBoundsException ne) {
            System.out.println(ne);
        }
        catch(AlreadySubscribedException ne) {
            System.out.println(ne);
        }
        try {
            Customer i1=p.subscribe(c1.getBranch(0));  
            Customer i2=p.subscribe(c1.getBranch(0));      
        }
        catch(AlreadySubscribedException ne) {
            System.out.println(ne);
        }
        try { 
            Admin a1=c1.getAdmin(50);           
        }
        catch(IndexOutOfBoundsException ne) {
            System.out.println(ne);
        }
    }
    /**
     * Test 2
     */
    public static void test2() {
        Company c1=new Company();
        Person p=new Person("Talha","Yolcu","E-MAIL","PASSWORD");
        try {
            Customer i1=p.subscribe(c1.getBranch(0));  
            Admin a1=c1.getAdmin(0);
            BranchEmployee be1=new BranchEmployee();
            //i1.list_the_branch(null); there is catch block for it
            i1.list_the_branch(c1.getBranch(0));  
            i1.list_all(c1);         
            i1.list_product(c1,"MT1");
        }
        catch(IndexOutOfBoundsException ne) {
            System.out.println(ne);
        }
        catch(AlreadySubscribedException ne) {
            System.out.println(ne);
        }
        catch(NullPointerException ne) {
            System.out.println(ne);
        }
            Admin a1=c1.getAdmin(0);
            Branch b1=new Branch("BRANCH_B1",10);
            a1.add_branch(c1,b1);

        Admin a12=c1.getAdmin(0);
        Branch b12=new Branch("BRANCH_B10",10);
        a1.add_branch(c1,b12);
        a1.remove_branch(c1,10);
    }
    /**
     * Test 3
     */
    public static void test3() {
        Company c1=new Company();
        BranchEmployee b1=new BranchEmployee();
        OfficeChair o1=new OfficeChair();
        Person p=new Person("Talha","Yolcu","E-MAIL","PASSWORD");
        b1.add_product(c1.getBranch(0),o1);
        b1.remove_product(c1.getBranch(0),1,"O100","BLACK",1);
        b1.remove_product(c1.getBranch(0),1,"O1","GRAY",1);
        b1.remove_product(c1.getBranch(0),1,"O1","BLACK",50);
        b1.create_subscription(c1.getBranch(0),p);
        b1.create_subscription(c1.getBranch(0),p);
        Admin a1=c1.getAdmin(0);
        a1.remove_branch_employee(c1.getBranch(0));
        a1.remove_branch_employee(c1.getBranch(0));
        a1.remove_branch_employee(c1.getBranch(0));
        a1.remove_branch_employee(c1.getBranch(0));
        a1.remove_branch_employee(c1.getBranch(0));
        a1.remove_branch_employee(c1.getBranch(0));
    }
    /**
     * Test 4
     */
    public static void test4() {
        Company c1=new Company();
        Person p=new Person("Talha","Yolcu","E-MAIL","PASSWORD");
        Person p2=new Person("Talha","Yolcu","E-MAIL2","PASSWORD2");
        try {
            Customer i1=p.subscribe(c1.getBranch(0));
            i1.login("E-MAIL2","P");
        }
        catch(AlreadySubscribedException ne) {
            System.out.println(ne);
        }
        catch (NoSuchElementException ne) {
            System.out.println(ne);
        }
        try {
            Customer i1=p2.subscribe(c1.getBranch(0));

            i1.login("E-MAIL2","PASSWORD2");
            i1.list_the_branch(c1.getBranch(0));
            i1.buy_online(c1,1,"A","BLACK",1);
        }
        catch(AlreadySubscribedException ne) {
            System.out.println(ne);
        }
        catch (Exception ne) {
            System.out.println(ne);
        }
    }
    /**
     * Test 5 , everything work properly
     */
    public static void test5() {
        System.out.println("LAST TEST,NO EXCEPTION");
        Company c1=new Company();
        Person p=new Person("Talha","Yolcu","E-MAIL","PASSWORD");
        try {
            Customer i1=p.subscribe(c1.getBranch(0));
            System.out.println("SUBSCRIPTION IS SUCCESFUL");
            i1.login("E-MAIL","PASSWORD");
            Admin a1=c1.getAdmin(0);
            BranchEmployee b1=new BranchEmployee();
            OfficeChair o1=new OfficeChair();
            i1.list_the_branch(c1.getBranch(0));

            i1.list_all(c1);
            i1.list_product(c1,"MT1");
            System.out.println("LISTING IS SUCCESFUL");
            i1.buy_online(c1,1,"OD1","BLACK",1);
            i1.view_previous_orders();
            System.out.println("BUYMENT IS SUCCESFUL");
            i1.buy_shop(c1.getBranch(0),2,"OD3","BLUE",1);
            System.out.println("BUYMENT IS SUCCESFUL, BRANCH EMPLOYEE MADE A SALE AND ADDED A NEW ORDER");

            System.out.println("VIEWING PREVIOUS ORDERS IS SUCCESFUL");

            Branch bb=new Branch("NEW BRANCH",10);
            a1.add_branch(c1,bb);
            System.out.println("ADDING A NEW BRANCH IS SUCCESFUL");
            a1.remove_branch(c1,2);
            System.out.println("REMOVING A BRANCH IS SUCCESFUL");

            a1.add_branch_employee(bb);
            System.out.println("ADDING A NEW BRANCH EMPLOYEE IS SUCCESFUL");
            a1.remove_branch_employee(bb);
            System.out.println("REMOVING A BRANCH EMPLOYEE IS SUCCESFUL");

            b1.add_product(bb,o1);
            System.out.println("ADDING A NEW PRODUCT IS SUCCESFUL");
            b1.remove_product(bb,1,"OD3","BLACK",1);
            System.out.println("REMOVING A PRODUCT IS SUCCESFUL");

            Person p10=new Person("NAME","SURNAME","EMAIL3","PASSWORD3");
            b1.create_subscription(bb,p10);
            System.out.println("SUBSCRIPTION IS CREATED SUCCESFULLY");

        }
        catch(AlreadySubscribedException ne) {
            System.out.println(ne);
        }
        catch (NoSuchElementException ne) {
            System.out.println(ne);
        }
        catch (Exception ne) {
            System.out.println(ne);
        }
    }
    public static void main(String[] args) {
        test();
        test2();
        test3();
        test4();
        test5();
    }
    //javadoc *.java -d javadoc
}


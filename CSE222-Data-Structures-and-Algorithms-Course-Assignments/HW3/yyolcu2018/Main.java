package yyolcu2018;

import javax.naming.OperationNotSupportedException;
import java.util.InputMismatchException;
import java.util.Scanner;

public class Main {

    /*
     *LinkedList in the textbook for information about branches
     *ArrayList in the textbook for users of the automation system
     *HybridList you implemented for the furniture
     */

    public static void test1() {

        Company c1=new Company();

        System.out.println(c1.get_branch(0).get_name());

        System.out.println(c1.get_branch(1).get_name());

        Person p1=new Person("Talha","Yolcu","E_Mail","Passwd");

        Person p2=new Person("Yakup","Yolcu","EMAIL","PASSWD");



        c1.getAdmin(0).add_branch_employee(0);
        System.out.println(c1.get_branch(0).get_number_of_branch_employee());

        try {
            Customer newc=p2.subscribe(c1.get_branch(0).get_branchemployee(0));
            newc.login(newc.getCustomer_number(),newc.getE_mail(),newc.getPassword());

            Customer customer=c1.get_branch(0).get_branchemployee(0).create_subscription(p1);
            System.out.println(customer.getCustomer_number());

            customer.login(customer.getCustomer_number(), customer.getE_mail(),customer.getPassword());


            customer.list_branch(c1,0);

            c1.get_branch(0).get_branchemployee(0).add_product(new OfficeChair("OCHAIR_2","BLUE",4));

            customer.list_branch(c1,0);

            c1.get_branch(0).get_branchemployee(0).remove_product(new OfficeChair("OCHAIR_1","BLACK",2));

            customer.list_branch(c1,0);

            System.out.println("\n\n\n\n");


            customer.list_all(c1);

            c1.getAdmin(0).remove_branch_employee(0);


            System.out.println(c1.get_branch(0).get_number_of_branch_employee());

            System.out.println(c1.get_number_of_branch());

            c1.getAdmin(0).remove_branch(0);

            System.out.println(c1.get_number_of_branch());


            c1.getAdmin(0).add_branch(new Branch("BRANCH_B2"));
            customer.list_all(c1);

            customer.list_product(c1,"OCHAIR_1");


            customer.buy_online(c1,"OCABINET_1","BLACK",1,0);
            customer.view_previous_orders();
            customer.list_branch(c1,0);

        }
        catch (AlreadyExistException | OperationNotSupportedException ne) {
            System.out.println(ne);
        }
    }
    public static void customer_test(Company c1,Customer customer) {
        boolean flag=true;
        while(flag) {
            System.out.println("1)LOGIN TO THE SYSTEM, IT MUST BE DONE BEFORE THE OTHERS");
            System.out.println("2)LIST A BRANCH'S PRODUCT");
            System.out.println("3)LIST WHOLE COMPANY");
            System.out.println("4)SEARCH FOR A PRODUCT");
            System.out.println("5)BUY PRODUCT ONLINE");
            System.out.println("6)BUY PRODUCT FROM SHOP");
            System.out.println("7)VIEW PREVIOUS ORDERS");
            System.out.println("0)EXIT");

            Scanner x=new Scanner(System.in);
            try {
                int opt=x.nextInt();
                String foo=x.nextLine();
                switch (opt) {
                    case 0:
                        flag=false;
                        break;
                    case 1:
                        try {
                            customer.login(customer.getCustomer_number(),customer.getE_mail(),customer.getPassword());
                        }
                        catch (AlreadyExistException ne) {
                            System.out.println("This customer already logined");
                        }
                        break;
                    case 2:
                        System.out.println("Enter an index for branch(starts from zero), max index:" + (c1.get_number_of_branch()-1));
                        try {
                            int br=x.nextInt();
                            String foo2=x.nextLine();
                            if(br<0 || br>= c1.get_number_of_branch()) {
                                System.out.println("Wrong index,try again");
                            }
                            else {
                                try {
                                    customer.list_branch(c1,br);
                                }
                                catch (OperationNotSupportedException ne) {
                                    System.out.println(ne);
                                }
                            }
                        }
                        catch (InputMismatchException ne) {
                            System.out.println(ne);
                        }
                        break;
                    case 3:
                        System.out.println("WHOLE COMPANY WILL BE LISTED...\n");
                        try {
                            customer.list_all(c1);
                        }
                        catch (OperationNotSupportedException ne) {
                            System.out.println(ne);
                        }
                        break;
                    case 4:
                        System.out.println("Enter name of the product");
                        String s=x.nextLine();
                        //String foo3=x.nextLine();
                        try {
                            customer.list_product(c1,s);

                        }
                        catch (OperationNotSupportedException ne) {
                            System.out.println(ne);
                        }
                        break;

                    case 5:
                        System.out.println("Enter name of the model name");
                        String name1=x.nextLine();
                        String foo4=x.nextLine();
                        System.out.println("Enter name of the color name");
                        String name2=x.nextLine();
                        String foo5=x.nextLine();
                        System.out.println("How much do you want to buy (enter stock)");
                        int temp=customer.get_number_of_orders();
                        int st=x.nextInt();
                        String foo6=x.nextLine();
                        for(int i=0;i< c1.get_number_of_branch();i++) {
                            customer.buy_online(c1,name1,name2,st,i);
                            if(temp<customer.get_number_of_orders()) {
                                break;
                            }
                        }
                        System.out.println("Previous orders will be viewed");
                        customer.view_previous_orders();
                        break;

                    case 6:
                        System.out.println("Enter branch index");
                        try {
                            int btr=x.nextInt();
                            String temp3=x.nextLine();
                            if(btr<0 || btr>=c1.get_number_of_branch()) {
                                System.out.println("Wrong index, try again");
                            }
                            else {
                                System.out.println("Enter name of the model name");
                                String name11=x.nextLine();
                                System.out.println("Enter name of the color name");
                                String name22=x.nextLine();
                                System.out.println("How much do you want to buy (enter stock)");
                                int stm=x.nextInt();
                                customer.buy_online(c1,name11,name22,stm,btr);
                                System.out.println("Previous orders will be viewed");
                                customer.view_previous_orders();
                            }
                        }
                        catch (InputMismatchException ne) {
                            System.out.println(ne);
                        }
                        break;

                    case 7:
                        customer.view_previous_orders();
                        break;
                }
            }
            catch (InputMismatchException ne) {
                System.out.println(ne);
            }
        }
    }
    public static void menutest() {
        Company c1=new Company();

        Person p1=new Person("Talha","Yolcu","E_Mail","Passwd");

        Person p2=new Person("Yakup","Yolcu","EMAIL","PASSWD");

        boolean flag=true;
        while (flag) {
            System.out.println("1) PERSON MODE ");
            System.out.println("2) CUSTOMER MODE");
            System.out.println("3) ADMIN MODE");
            System.out.println("4) BRANCH EMPLOYEE MODE");
            System.out.println("0) EXIT");
            System.out.println("Enter a number: ");

            Scanner x=new Scanner(System.in);
            Person p3=new Person("JOHN","REESE","E__MAIL","PASSWDD");
            Person p4=new Person("HAROLD","FINCH","NUL","NUL");
            Customer custom=new Customer("ABCDEF",p3);
            Customer custom2=new Customer("ABCDEF2",p4);

            try {
                int opt = x.nextInt();
                String c = x.nextLine();
                switch (opt) {
                    case 0:
                        System.out.println("EXITING...");
                        flag=false;
                        break;
                    case 1:
                        System.out.println("There are 2 persons, choose one");
                        System.out.println("1) "+p1);
                        System.out.println("2) "+p2);

                        int per=x.nextInt();

                        System.out.println("SUBSCRIPTION WILL BE DONE");
                        if(per==1) {
                            try {
                                custom=p1.subscribe(c1.get_branch(0).get_branchemployee(0));
                            }
                            catch (AlreadyExistException ne) {
                                System.out.println(ne);
                            }
                        }
                        else if(per==2){
                            try {
                                custom2=p1.subscribe(c1.get_branch(0).get_branchemployee(0));
                            }
                            catch (AlreadyExistException ne) {
                                System.out.println(ne);
                            }
                        }
                        else {
                            System.out.println("Input is wrong try again");
                        }
                        break;
                    case 2:
                        System.out.println("1) USE DEFAULT CREATED CUSTOMERS");
                        System.out.println("2) CREATE NEW CUSTOMER");
                        int opt3=x.nextInt();
                        if(opt3==1) {
                            System.out.println("1) "+custom);
                            System.out.println("2) "+custom2);
                            int opt4=x.nextInt();
                            if(opt4==1) {
                                customer_test(c1,custom);
                            }
                            else if(opt4==2) {
                                customer_test(c1,custom2);
                            }
                            else {
                                System.out.println("Wrong input, try again");
                            }
                        }
                        else if(opt3==2) {
                            System.out.println("Enter name of person");
                            String temp1=x.nextLine();
                            System.out.println("Enter surname");
                            String temp2=x.nextLine();
                            System.out.println("Enter e-mail");
                            String temp4=x.nextLine();
                            System.out.println("Enter password");
                            String temp3=x.nextLine();

                            Customer customer3=null;

                            if(temp1==null || temp2==null || temp3==null || temp4==null) {
                                System.out.println("Something went wrong try again");
                            }
                            else {
                                try {
                                    customer3=c1.get_branch(0).get_branchemployee(0).create_subscription(new Person(temp1,temp2,temp4,temp3));
                                    customer_test(c1,customer3);
                                }
                                catch (AlreadyExistException ne) {
                                    System.out.println(ne);
                                }

                            }
                        }
                        break;
                    case 3:
                        boolean admin_flag=true;
                        while(admin_flag) {
                            System.out.println("1)ADD BRANCH");
                            System.out.println("2)REMOVE BRANCH");
                            System.out.println("3)ADD BRANCH EMPLOYEE");
                            System.out.println("4)REMOVE BRANCH EMPLOYEE");
                            System.out.println("5)ASK FOR ANY SUPPLY NEED");
                            System.out.println("0) EXIT");

                            try {
                                int admin_option=x.nextInt();
                                switch (admin_option) {
                                    case 0:
                                        admin_flag=false;
                                        break;
                                    case 1:
                                        c1.getAdmin(0).add_branch(new Branch("BRANCH_B"+c1.get_number_of_branch()));
                                        System.out.println("New branch is added, name is : " + c1.get_branch(c1.get_number_of_branch()-1));
                                        break;
                                    case 2:
                                        System.out.println("Enter index between 0 - " + (c1.get_number_of_branch()-1));
                                        int b_admin_option=x.nextInt();
                                        if(b_admin_option<0 || b_admin_option>=c1.get_number_of_branch()) {
                                            System.out.println("Enter proper index");
                                        }
                                        else {
                                            c1.getAdmin(0).remove_branch(b_admin_option);
                                            System.out.println("Branch is removed successfully");
                                        }
                                        break;
                                    case 3:
                                        System.out.println("Enter index to determine which branch to add branch employee"+ " (0-"+(c1.get_number_of_branch()-1));
                                        int b_admin_option2=x.nextInt();
                                        if(b_admin_option2<0 || b_admin_option2>=c1.get_number_of_branch()) {
                                            System.out.println("Enter proper index");
                                        }
                                        else {
                                            c1.getAdmin(0).add_branch_employee(b_admin_option2);
                                            System.out.println("Branch employee is added successfully");
                                        }
                                        break;

                                    case 4:
                                        System.out.println("Enter index to determine from the which branch branch employee will be removed" + " (0-"+(c1.get_number_of_branch()-1));
                                        int b_admin_option3=x.nextInt();
                                        if(b_admin_option3<0 || b_admin_option3>=c1.get_number_of_branch()) {
                                            System.out.println("Enter proper index");
                                        }
                                        else {
                                            c1.getAdmin(0).remove_branch_employee(b_admin_option3);
                                            System.out.println("Branch employee is removed successfully");
                                        }
                                        break;

                                    case 5:
                                        System.out.println("Enter branch index to query");
                                        int q=x.nextInt();
                                        if(q<0 || q>=c1.get_number_of_branch()) {
                                            System.out.println("Enter proper index");
                                        }
                                        else {
                                            if(c1.getAdmin(0).query_for_supply(q)) {
                                                System.out.println("Supply is needed");
                                            }
                                            else {
                                                System.out.println("Supply is not needed");
                                            }
                                        }
                                        break;
                                    default:
                                        System.out.println("Enter proper number");
                                        break;

                                }
                            }
                            catch (InputMismatchException ne) {
                                System.out.println(ne);
                            }
                        }
                        break;

                    case 4:
                        boolean b_flag=true;
                        System.out.println("Enter branch index to be the branch employee (0-"+(c1.get_number_of_branch()-1)+")");
                        try {
                            int index_b=x.nextInt();
                            if(index_b<0 || index_b>=c1.get_number_of_branch()-1) {
                                System.out.println("Wrong index");
                            }
                            else {
                                while (b_flag) {
                                    System.out.println("1)ADD PRODUCT");
                                    System.out.println("2)REMOVE PRODUCT");
                                    System.out.println("0)EXIT");
                                    try {
                                        int opt_b=x.nextInt();
                                        switch (opt_b) {
                                            case 0:
                                                b_flag=false;
                                                break;
                                            case 1:
                                                System.out.println("1)ADD OFFICE CHAIR");
                                                System.out.println("2)ADD OFFICE DESK");
                                                System.out.println("3)ADD MEETING TABLE");
                                                System.out.println("4)ADD BOOK CASE");
                                                System.out.println("5)ADD OFFICE CABINET");
                                                System.out.println("Enter: ");

                                                int opt_be_2=x.nextInt();
                                                System.out.println("Sample model name:");
                                                print_situation(opt_be_2);

                                                switch (opt_be_2) {
                                                    case 1:
                                                        System.out.println("There can be only 7 models");
                                                        System.out.println("Enter number 1-7)");
                                                        int model=x.nextInt();
                                                        String temp11=x.nextLine();
                                                        System.out.println("Enter color (all big letter)");
                                                        String color=x.nextLine();
                                                        if(model<1 || model>7) {
                                                            System.out.println("Wrong input");
                                                        }
                                                        else {
                                                            c1.get_branch(index_b).get_branchemployee(0).add_product(new OfficeChair(("OCHAIR_"+model),color,1));
                                                        }
                                                        break;

                                                    case 2:
                                                        System.out.println("There can be only 5 models");
                                                        System.out.println("Enter number 1-5)");
                                                        int model2=x.nextInt();
                                                        String temp12=x.nextLine();
                                                        System.out.println("Enter color (all big letter)");
                                                        String color2=x.nextLine();
                                                        if(model2<1 || model2>5) {
                                                            System.out.println("Wrong input");
                                                        }
                                                        else {
                                                            c1.get_branch(index_b).get_branchemployee(0).add_product(new OfficeDesk(("ODESK_"+model2),color2,1));
                                                        }
                                                        break;

                                                    case 3:
                                                        System.out.println("There can be only 10 models");
                                                        System.out.println("Enter number 1-10");
                                                        int model3=x.nextInt();
                                                        String temp13=x.nextLine();
                                                        System.out.println("Enter color (all big letter)");
                                                        String color3=x.nextLine();
                                                        if(model3<1 || model3>10) {
                                                            System.out.println("Wrong input");
                                                        }
                                                        else {
                                                            c1.get_branch(index_b).get_branchemployee(0).add_product(new MeetingTable(("MTABLE_"+model3),color3,1));
                                                        }
                                                        break;

                                                    case 4:
                                                        System.out.println("There can be only 12 models");
                                                        System.out.println("Enter number 1-12");
                                                        int model4=x.nextInt();
                                                        String color4="BLACK";
                                                        if(model4<1 || model4>10) {
                                                            System.out.println("Wrong input");
                                                        }
                                                        else {
                                                            c1.get_branch(index_b).get_branchemployee(0).add_product(new Bookcase(("BCASE_"+model4),color4,1));
                                                        }
                                                        break;

                                                    case 5:
                                                        System.out.println("There can be only 12 models");
                                                        System.out.println("Enter number 1-12");
                                                        int model5=x.nextInt();
                                                        String color5=x.nextLine();
                                                        if(model5<1 || model5>10) {
                                                            System.out.println("Wrong input");
                                                        }
                                                        else {
                                                            c1.get_branch(index_b).get_branchemployee(0).add_product(new OfficeCabinet(("OCABINET_"+model5),color5,1));
                                                        }
                                                        break;

                                                    default:
                                                        System.out.println("Wrong input, try again");
                                                        break;
                                                }

                                                break;

                                            case 2:
                                                System.out.println("Couldn't do adjustment for menu...");
                                                //c1.get_branch(index_b).get_branchemployee(0).remove_product();
                                                break;

                                            default:
                                                System.out.println("Wrong input, try again");
                                                break;
                                        }
                                    }
                                    catch (InputMismatchException ne) {
                                        System.out.println(ne);
                                    }
                                }
                            }
                        }
                        catch (InputMismatchException ne) {
                            System.out.println(ne);
                        }
                        break;
                    default:
                        System.out.println("Wrong input, try again");
                        break;
                }
            }
            catch (InputMismatchException ne) {
                System.out.println(ne + " Invalid input entered,try again");
            }
        }
    }
    public static void print_situation(int situation) {
        switch (situation) {
            case 1:
                System.out.println("OCHAIR_X");
                System.out.println("Colors:");
                System.out.println("BLACK-BLUE-RED-GREEN-YELLOW");
                break;
            case 2:
                System.out.println("ODESK_X");
                System.out.println("Colors:");
                System.out.println("BLACK-BLUE-RED-GREEN");
                break;
            case 3:
                System.out.println("MTABLE_X");
                System.out.println("Colors:");
                System.out.println("BLACK-BLUE-RED-GREEN-YELLOW");
                break;
            case 4:
                System.out.println("BCASE_X");
                break;
            case 5:
                System.out.println("OCABINET_X");
                break;
        }
    }
    public static void main(String[] args) {

        test1();

        menutest();

    }
}

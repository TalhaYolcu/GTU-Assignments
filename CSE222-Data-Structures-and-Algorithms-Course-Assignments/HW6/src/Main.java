import yyolcu2018.*;
import yyolcu2018.Customer;
import yyolcu2018.Trader;


import java.io.*;
import java.text.DecimalFormat;
import java.util.*;

/**
 * Main class includes trader and customer menu
 */
public class Main {

    /**
     * Unique ID length
     */
    public static final int ID_LENGTH=8;
    /**
     * password length
     */
    public static final int password_length=6;

    /**
     * menu for customers
     * @param customer current customer
     * @param test_flag flag for testing
     */
    public static void customer_menu(Customer customer,boolean test_flag) {
        boolean flag=true;
        int counter=0;
        while(flag) {
            System.out.println("1)SEARCH A PRODUCT BY ITS NAME");
            System.out.println("2)DISPLAY ALL THE PRODUCTS OF A TRADER");
            System.out.println("3)EXIT");
            System.out.println("PLEASE ENTER:");
            Scanner scanner=new Scanner(System.in);
            int option=0;
            if(test_flag) {
                if(counter==0) {
                    option=1;
                }
                else if(counter==1) {
                    option=2;
                }
                else if(counter==2) {
                    option=3;
                }
                System.out.println(option);
            }
            else {
                option=scanner.nextInt();
                scanner.nextLine();
            }
            switch (option) {
                case 1:
                    try {
                        customer.search_a_product(test_flag);
                    }
                    catch (FileNotFoundException ne) {
                        ne.printStackTrace();
                    }
                    break;
                case 2:
                    try {
                        customer.display_products_of_a_trader(test_flag);
                    }
                    catch (FileNotFoundException ne) {
                        ne.printStackTrace();
                    }
                    break;
                case 3:
                    flag=false;
                    System.out.println("EXITING...");
                    break;
                default:
                    System.out.println("WRONG INPUT,TRY AGAIN");
            }
            counter++;
        }
    }

    /**
     * menu for traders
     * @param trader current trader
     * @param test_flag flag for testing
     */
    public static void trader_menu(Trader trader,boolean test_flag) {
        boolean flag=true;
        int counter=0;
        while (flag) {
            System.out.println("1)ADD PRODUCT");
            System.out.println("2)REMOVE PRODUCT");
            System.out.println("3)EDIT PRODUCT");
            System.out.println("4)SEE THE LIST OF ORDERS AND MEET/CANCEL");
            System.out.println("5)EXIT");
            System.out.println("Enter a number:");
            Scanner scanner=new Scanner(System.in);

            try {
                int option=0;
                if(test_flag) {
                    if(counter==0) {
                        option=1;
                    }
                    else if(counter==1) {
                        option=2;
                    }
                    else if(counter==2) {
                        option=3;
                    }
                    else if(counter==3) {
                        option=4;
                    }
                    else if(counter==4) {
                        option=5;
                    }
                    System.out.println(option);
                }
                else {
                    option=scanner.nextInt();
                    scanner.nextLine();
                }
                switch (option) {
                    case 1:
                        trader.add_product(test_flag);
                        break;

                    case 2:
                        trader.remove_product(test_flag);
                        break;

                    case 3:
                        trader.edit_product(test_flag);
                        break;

                    case 4:
                        trader.see_the_list_of_orders(test_flag);

                    case 5:
                        flag=false;
                        System.out.println("EXITING...");
                        break;

                    default:
                        System.out.println("Wrong input,try again...");
                        break;
                }
            }
            catch (InputMismatchException | FileNotFoundException ne) {
                ne.printStackTrace();
            }
            counter++;
        }
    }

    /**
     * creates the users.txt
     * @param traders trader names
     * @throws IOException if there is a problem reading-writing file
     */
    public static void create_users_file(HashSet<String> traders) throws IOException {
        FileWriter write=new FileWriter("yyolcu2018/files/users.txt");
        DecimalFormat decimalFormat=new DecimalFormat("00000000");    //8 digit
        DecimalFormat decimalFormat2=new DecimalFormat("000000");    //6 digit
        Hashtable<String,String> trader_table=new Hashtable<>();
        int i=0;
        for(String s:traders) {          //traders added
            write.append(s);
            write.append("\t");

            write.append(decimalFormat.format(i+1));
            write.append("\t");

            write.append(decimalFormat2.format(i+1));
            i++;
            write.append("\n");
            trader_table.put(s,decimalFormat.format(i+1));
        }
        for(int k=0;k<10;k++) {            //10 customers added
            write.append("CUSTOMER");
            write.append(Integer.toString(k+1));
            write.append("\t");
            write.append(decimalFormat.format(i+1));
            write.append("\t");
            write.append(decimalFormat2.format(i+1));
            i++;
            write.append("\n");
        }
        write.close();
    }

    /**
     * creates the orders.txt
     * @throws IOException if there is a problem with creation of file
     */
    public static void create_orders_file() throws IOException {
        FileWriter write=new FileWriter(new File("yyolcu2018/files/orders.txt"));
        write.close();   //just create , don't write anything
    }

    /**
     * creates the products.txt
     * @throws IOException if there is a problem with creation of file
     */
    public static void create_products_file() throws IOException {
        Scanner sc = new Scanner(new File("yyolcu2018/files/e-commerce-samples.csv"));

        FileWriter write=new FileWriter("yyolcu2018/files/products.txt");

        BufferedReader csvReader = new BufferedReader(new FileReader("yyolcu2018/files/e-commerce-samples.csv"));

        HashSet<String> traders=new HashSet<>();  /*we need to hold trader names in
         hashset because there is 1 trader with the same name
        */


        while (true) {
            String str=csvReader.readLine();
            if(str==null) {
                break;
            }
            String[] buf=str.split(";");
            if(buf[1].equals("product_name")) {
                continue;
            }
            write.append(buf[1]);
            write.append(";");

            write.append(buf[5]);
            write.append(";");

            write.append(buf[6]);
            write.append(";");

            write.append(buf[0]);
            write.append(";");

            write.append(buf[2]);
            write.append(";");

            write.append(buf[3]);
            write.append(";");

            write.append(buf[4]);
            write.append(";");

            write.append("\n");

            traders.add(buf[6]);
        }
        write.close();
        sc.close();
        try {
            create_users_file(traders);   //users.txt is created with trader names
        }
        catch (IOException ne) {
            ne.printStackTrace();
        }
        csvReader.close();
        try {
            create_orders_file();      //orders.txt is created but nothing will be written
        }
        catch (IOException ne) {
            ne.printStackTrace();
        }
    }

    /**
     * driver function
     * @param test_flag flag for testing
     * @param user_type flag for customer-trader test
     * @throws FileNotFoundException if there is a problem
     */
    public static void test1(boolean test_flag,boolean user_type) throws FileNotFoundException{
        try{
            create_products_file(); //products.txt is created
        }
        catch (IOException ne) {
            ne.printStackTrace();
        }
        boolean test_over=false;
        while(true) {
            System.out.println("%%% WELCOME TO E-SHOP%%%");
            System.out.println("Enter USER ID AND PASSWORD TO LOGIN TO THE SYSTEM");
            System.out.println("TO EXIT, ENTER -1");
            System.out.println("ID:");

            Hashtable<String,String> customers=new Hashtable<>();

            Scanner scanner=new Scanner(System.in);
            String temp_id;
            /*
            ID CHECK
             */
            if(test_flag) {
                if(user_type) {
                    temp_id="00003191";
                }
                else {
                    temp_id="00000001";
                }
                System.out.println(temp_id);
            }
            else {
                if(test_over) {
                    temp_id="-1";
                    System.out.println(temp_id);
                }
                else {
                    temp_id=scanner.nextLine();
                }
            }
            if(temp_id.contains("-1")) {
                System.out.println("EXITING...");
                break;
            }
            if(temp_id.length()!=ID_LENGTH) {
                System.out.println("WRONG USER ID, TRY AGAIN\n\n");
            }
            else {
                System.out.println("\nEnter Password:\n");
                String temp_password;
                /*
                PASSWORD CHECK
                 */
                if(test_flag) {
                    if(user_type) {
                        temp_password="003191";
                        user_type=false;
                    }
                    else {
                        temp_password="000001";
                        test_over=true;

                    }
                    System.out.println(temp_password);
                }
                else {
                    temp_password=scanner.nextLine();
                }

                if(temp_password.length()!=password_length) {
                    System.out.println("WRONG PASSWORD, TRY AGAIN\n\n");
                }
                else {
                    /*
                    ID AND PASSWORD LENGTH CHECK IS CONFIRMED WE NEED TO CHECK
                    FOR MATCHING
                     */
                    boolean flag2=false;
                    Scanner users_file=new Scanner(new File("yyolcu2018/files/users.txt"));
                    users_file.useDelimiter("\n");
                    while(true) {
                        if(!users_file.hasNext()) {
                            break;
                        }
                        String line=users_file.nextLine();
                        if(line==null) {
                            break;
                        }
                        String[] buf=line.split("\t");
                        if(buf[1].equals(temp_id) && buf[2].equals(temp_password)) {
                            /*
                            ID AND PASSWORD IS CORRECT
                             */
                            System.out.println("LOGIN SUCCESSFUL, GOING TO THE MENU");
                            System.out.println("WELCOME, "+buf[0]);
                            if(buf[0].contains("CUSTOMER")) {
                                /*
                                CUSTOMER LOGIN
                                 */
                                Customer customer=new Customer(buf[1],buf[2],buf[0]);
                                customer.setLogin(true);
                                customer_menu(customer,test_flag);
                            }
                            else {
                                /*
                                TRADER LOGIN
                                 */
                                Trader trader=new Trader(buf[1],buf[2],buf[0]);
                                trader.setLogin(true);
                                trader_menu(trader,test_flag);
                            }
                            flag2=true;
                            if(test_over) {
                                test_flag=false;
                            }
                            break;
                        }
                    }
                    if(!flag2) {
                        System.out.println("WRONG ID OR PASSWORD, TRY AGAIN");
                    }
                    users_file.close();
                }
            }
        }
    }

    /**
     * main function
     * @param args arguments
     */
    public static void main(String[] args)  {

        try {
            test1(true,true);   //driver function works
            test1(false,true);  //interactive menu works
        }
        catch (FileNotFoundException ne) {
            ne.printStackTrace();
        }
        finally {
            System.gc();
        }
    }
}

package yyolcu2018;

import java.io.*;
import java.util.*;

/**
 * Class that represents a single user
 */
public class Customer extends Person{
    /**
     * Constructor takes parameters and uses abstract Person classes constructor
     * @param id ID
     * @param password password
     * @param name name
     */
    public Customer(String id,String password,String name) {
        super(id,password,name);
    }

    /**
     * No parameter constructor
     */
    public Customer() {
        super();
    }

    /**
     * insertion sort
     * @param table products
     */
    private void insertion_sort(ArrayList<Product> table) {
        for(int nextPos=1;nextPos<table.size();nextPos++) {
            insert(table,nextPos);
        }
    }

    /**
     * insertion sort method
     * @param table products
     * @param nextPos nextPosition
     */
    private void insert(ArrayList<Product> table, int nextPos) {
        Product nextVal=table.get(nextPos);
        while(nextPos>0 && table.get(nextPos-1).compareTo(nextVal)>0){
            table.set(nextPos,table.get(nextPos-1));
            nextPos--;
        }
        table.set(nextPos,nextVal);
    }

    /**
     * bubble sort method
     * @param table products
     */
    private void bubble_sort(ArrayList<Product> table) {
        int pass=1;
        boolean exchanges=false;

        do {
            exchanges=false;
            for(int i=0;i<table.size()-pass;i++) {
                if(table.get(i).compareTo(table.get(i+1))>0) {
                    Product temp=table.get(i);
                    table.set(i,table.get(i+1));
                    table.set(i+1,temp);
                    exchanges=true;
                }
            }
            pass++;
        }
        while(exchanges);
    }

    /**
     * selection sort method
     * @param arr products
     */
    private void selection_sort(ArrayList<Product> arr) {
        int n=arr.size();
        int fill;

        for(fill=0;fill<n-1;fill++) {
            int posMin=fill;
            for(int next=fill+1;next<n;next++) {
                if(arr.get(next).compareTo(arr.get(posMin))<0) {
                    posMin=next;
                }
            }
            Product temp=arr.get(fill);
            arr.set(fill,arr.get(posMin));
            arr.set(posMin,temp);
        }
    }

    /**
     * prints the reverse of the given list
     * @param table products
     */
    private void print_reverse(ArrayList<Product> table) {
        for(int i=table.size()-1;i>=0;i--) {
            System.out.println("------");
            System.out.print(table.size()-i+")");
            System.out.println(table.get(i));
        }
    }

    /**
     * Reads the products.txt and lists the products
     * @param text given search text
     * @param productArrayList products
     * @param comparator comparator for sorting
     * @throws FileNotFoundException if there is a problem reading file
     */
    private void list_products(String text, ArrayList<Product> productArrayList, Comparator<Product> comparator) throws FileNotFoundException {
        Scanner scanner=new Scanner(new File("yyolcu2018/files/products.txt"));
        scanner.useDelimiter("\n");

        while (scanner.hasNext()) {
            String[] products=scanner.next().split(";");
            if(products[0].contains(text)) {

               LinkedList<String> categories=new LinkedList<>();
                /*
                Lines with problem
                 */
                if(products[4].length()<=4) {
                    categories.add(products[4]);
                }
                else {
                    String temp=products[4].substring(4,products[4].length()-4);
                    String[] read_categories=temp.split(">>");
                    categories.addAll(Arrays.asList(read_categories));
                }
                /*
                Price and discounted price was taken as string, we need to convert them.
                 */
                int price=Integer.parseInt(products[5]);
                int discounted_price=Integer.parseInt(products[6]);

                double discount_amount=(100.0-discounted_price*100.0/price);
                /*
                We found a product within given context, we can add to the arraylist
                 */
                productArrayList.add(new Product(products[0],products[1],products[2],products[3],categories,price,discounted_price,discount_amount,comparator));
            }
        }
        scanner.close();
    }

    /**
     * Filter method
     * @param products products
     * @param test_flag flag for testing
     */
    private void filter_by_price(ArrayList<Product> products,boolean test_flag) {
        Scanner scanner=new Scanner(System.in);
        int lower=0;
        int upper=900;
        while(true) {
            try {
                System.out.println("ENTER LOWER THRESHOLD (Integer)\n" +
                        "IF YOU DON'T WANT TO DETERMINE, ENTER -1:");
                if(test_flag) {
                    lower=100;
                    System.out.println(lower);
                }
                else {
                    lower = scanner.nextInt();
                    scanner.nextLine();
                }
                System.out.println("ENTER UPPER THRESHOLD (Integer)\n" +
                        "IF YOU DON'T WANT TO DETERMINE, ENTER -1:");
                if(test_flag) {
                    upper=1150;
                    System.out.println(upper);
                }
                else {
                    upper = scanner.nextInt();
                    scanner.nextLine();
                }
                if(lower!=0 && upper>=lower) {
                    break;
                }
                else {
                    System.out.println("Enter proper numbers for upper and lower thresholds");
                }
            }
            catch (InputMismatchException ne) {
                ne.printStackTrace();
            }
        };
        int counter=0;
        /*
        user did not give any upper and lower threshold
         */
        if(upper==-1 && lower==-1) {
            for(Product p:products) {
                System.out.println("------");
                System.out.println((counter+1)+")"+p);
                counter++;
            }
            create_order(products,test_flag);
        }
        /*
        user give upper but did not give lower
         */
        if(upper == -1 && lower!=-1) {
            ArrayList<Product> lower_product=new ArrayList<>();
            for(Product p:products) {
                if(p.getPrice()>=lower) {
                    lower_product.add(p);
                }
            }
            for(Product p:lower_product) {
                System.out.println("------");
                System.out.println((counter+1)+")"+p);
                counter++;
            }
            create_order(lower_product,test_flag);
        }
        /*
        user give lower but did not give upper
         */
        if(upper!=-1 && lower==-1){
            ArrayList<Product> lower_product=new ArrayList<>();
            for(Product p:products) {
                if(p.getPrice()<=upper) {
                    lower_product.add(p);
                }
            }
            for(Product p:lower_product) {
                System.out.println("------");
                System.out.println((counter+1)+")"+p);
                counter++;
            }
            create_order(lower_product,test_flag);
        }
        /*
        gave both upper and lower
         */
        else {
            ArrayList<Product> lower_product=new ArrayList<>();
            for(Product p:products) {
                if(p.getPrice()>=lower && p.getPrice()<=upper) {
                    lower_product.add(p);
                }
            }
            for(Product p:lower_product) {
                System.out.println("------");
                System.out.println((counter+1)+")"+p);
                counter++;
            }
            create_order(lower_product,test_flag);
        }
    }

    /**
     * Method to filter products by categories
     * @param products products
     * @param test_flag flag for testing
     */
    private void filter_by_category(ArrayList<Product> products,boolean test_flag) {
        System.out.println("CATEGORIES:");
        ArrayList<String> ptr=new ArrayList<>();
        for (Product product : products) {
            String cat = product.root_category();
            if(!ptr.contains(cat)) {
                ptr.add(cat);
            }
            /*
            Higher level categories will be listed firstly
             */
        }
        int i=0;
        for(String str:ptr) {
            System.out.print(i+1);
            System.out.println(")"+str);
            i++;
        }
        System.out.println("\nEnter a number to select a category:");
        Scanner scanner=new Scanner(System.in);
        try {
            int cat=0;
            if(test_flag) {
                cat=2;
                System.out.println(cat);
            }
            else {
                cat=scanner.nextInt();
                scanner.nextLine();
            }
            cat-=1;
            if(cat<0 || cat>=ptr.size()) {
                System.out.println("WRONG INPUT,TRY AGAIN");
            }
            else {
                String printed=ptr.get(cat);
                System.out.println("1)GO TO LOWER CATEGORIES");
                System.out.println("2)PRINT JUST "+printed+"CATEGORY");
                System.out.println("3)EXIT");
                System.out.println("Enter:");
                Scanner scanner1=new Scanner(System.in);

                try {
                    int opt=0;
                    if(test_flag) {
                        opt=1;
                    }
                    else {
                        opt=scanner1.nextInt();
                    }
                    switch (opt) {
                        case 1:
                            ArrayList<Product> lower_products=new ArrayList<>();

                            for(Product my_product:products) {
                                if(my_product.root_category().equals(printed)) {
                                    Product temp=new Product(my_product);
                                    if(temp.remove_root_category()) {
                                        lower_products.add(temp);
                                    }
                                }
                            }
                            /*
                            Recursively do the same thing
                             */
                            if(lower_products.isEmpty()) {
                                System.out.println("There is no product within this context");
                                System.out.println("EXITING");
                                /*
                                base case
                                 */
                            }
                            else {
                                filter_by_category(lower_products,test_flag);
                            }
                            break;
                        case 2:
                            int counter=0;
                            ArrayList<Product> temp=new ArrayList<>();
                            for(Product my_product:products) {
                                if(my_product.root_category().equals(printed)) {
                                    temp.add(my_product);
                                }
                            }
                            /*
                            Products have this category will be listed
                             */
                            if(temp.isEmpty()) {
                                System.out.println("There is no product within this context");
                                System.out.println("EXITING");
                            }
                            else {
                                for(Product my_product:temp) {
                                    System.out.println((counter+1)+")"+my_product);
                                    counter++;
                                }
                                create_order(temp,test_flag);
                            }
                            break;
                        case 3:
                            System.out.println("EXITING...");
                            break;

                        default:
                            System.out.println("Wrong input, exiting...");
                    }
                }
                catch (InputMismatchException ne) {
                    ne.printStackTrace();
                }
            }
        }
        catch (InputMismatchException ne) {
            ne.printStackTrace();
        }
    }

    /**
     * filters the products by given input (category-threshold)
     * @param products products
     * @param test_flag flag for testing
     */
    private void filter(ArrayList<Product> products,boolean test_flag) {
        Scanner scanner=new Scanner(System.in);
        boolean flag=true;
        int counter=0;
        while (flag) {
            System.out.println("1)FILTER BY CATEGORIES");
            System.out.println("2)FILTER BY PRICE THRESHOLDS");
            System.out.println("3)EXIT");
            System.out.println("Enter:");
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
                    filter_by_category(products,test_flag);
                    break;

                case 2:
                    filter_by_price(products,test_flag);
                    break;

                case 3:
                    flag=false;
                    System.out.println("EXITING...");
                    break;

                default:
                    System.out.println("WRONG INPUT,TRY AGAIN");
                    break;
            }
            counter++;
        }
    }

    /**
     * creates and order
     * @param products products
     * @param index index
     * @param test_flag flag for testing
     * @throws NullPointerException if arraylist is empty
     * @throws IOException if there is a problem with writing to a file
     */
    private void make_an_order(ArrayList<Product> products,int index,boolean test_flag) throws NullPointerException, IOException {
        if(products==null || products.isEmpty() ) {
            throw new NullPointerException();
        }
        try {
            FileWriter fileWriter=new FileWriter("yyolcu2018/files/orders.txt",true);
            BufferedWriter bw = new BufferedWriter(fileWriter);
            bw.write(getId());
            bw.write("\t");
            bw.write(products.get(index).getID());
            bw.write("\t");
            bw.write(products.get(index).getTrader());
            bw.write("\n");
            bw.close();

        }
        catch (IOException ne) {
            ne.printStackTrace();
        }
        System.out.println("Order is created successfully");
    }

    /**
     * customer searches a product
     * @param test_flag flag for testing
     * @throws FileNotFoundException if there is a problem with file
     */
    public void search_a_product(boolean test_flag) throws FileNotFoundException{
        Scanner scanner=new Scanner(System.in);

        boolean flag=true;
        int counter=0;
        while(flag) {
            System.out.println("1)SEE PRODUCTS WITHOUT FILTERING/SORTING");
            System.out.println("2)SEE PRODUCTS WITH FILTERING/SORTING");
            System.out.println("3)EXIT");
            System.out.println("Enter:");

            Scanner scanner1=new Scanner(System.in);
            int option=-1;
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
                    ArrayList<Product> productArrayList=new ArrayList<>();
                    System.out.println("Enter search text:");

                    String text=null;
                    if(test_flag) {
                        text="Rama";
                        System.out.println(text);
                    }
                    else {
                        text=scanner1.nextLine();
                    }
                    Comparator<Product> comparator= Comparator.comparing(Product::getName);
                    list_products(text,productArrayList,comparator);
                    if(productArrayList.isEmpty()) {
                        System.out.println("Couldn't find a product with this search");
                        System.out.println("EXITING...");
                    }
                    else {
                        insertion_sort(productArrayList);
                        print_reverse(productArrayList);
                        Scanner scanner2=new Scanner(System.in);
                        System.out.println("We have found "+productArrayList.size()+" product(s) to see within this search");
                        System.out.println("Enter an index to make an order for a product," +
                                " If you do not want to buy anything, enter 0");
                        try {
                            int opt=0;
                            if(test_flag) {
                                opt=10;
                                System.out.println(opt);
                            }
                            else {
                                opt=scanner2.nextInt();
                                scanner2.nextLine();
                            }
                            if(opt==0) {
                                System.out.println("EXITING...");
                            }
                            else if(opt>productArrayList.size() || opt<0) {
                                System.out.println("Wrong input,try again");
                            }
                            else {
                                opt=productArrayList.size()-opt;
                                create_order_2(productArrayList, opt,test_flag);
                            }
                        }
                        catch (InputMismatchException ne) {
                            ne.printStackTrace();
                        }
                    }
                    break;

                case 2:
                    ArrayList<Product> productArrayList2=new ArrayList<>();
                    System.out.println("Enter search text:");
                    String text2=null;
                    if(test_flag) {
                        text2="Rama";
                        System.out.println(text2);
                    }
                    else {
                        text2=scanner1.nextLine();
                    }
                    System.out.println("1)SORT BY PRICE");
                    System.out.println("2)SORT BY PERCENTAGE OF DISCOUNT");
                    System.out.println("3)SORT BY NAME");
                    int second_option=0;
                    if(test_flag) {
                        second_option=3;
                        System.out.println(second_option);
                    }
                    else {
                        second_option=scanner1.nextInt();
                        scanner1.nextLine();
                    }
                    switch (second_option) {
                        case 1:
                            //SORT BY PRICE
                            Comparator<Product> comparator2=Comparator.comparing(Product::getPrice);
                            list_products(text2,productArrayList2,comparator2);
                            if(productArrayList2.isEmpty()) {
                                System.out.println("Couldn't find a product with this search");
                                System.out.println("EXITING...");
                            }
                            else {
                                bubble_sort(productArrayList2);
                                filter(productArrayList2,test_flag);
                            }
                            break;
                        case 2:
                            //SORT BY PERCENTAGE OF DISCOUNT
                            Comparator<Product> comparator3= Comparator.comparing(Product::getPercentage_of_discount);
                            list_products(text2,productArrayList2,comparator3);
                            if(productArrayList2.isEmpty()) {
                                System.out.println("Couldn't find a product with this search");
                                System.out.println("EXITING...");
                            }
                            else {
                                selection_sort(productArrayList2);
                                filter(productArrayList2,test_flag);
                            }
                            break;
                        case 3:
                            //3)SORT BY NAME
                            Comparator<Product> comparator4= Comparator.comparing(Product::getName);
                            list_products(text2,productArrayList2,comparator4);
                            if(productArrayList2.isEmpty()) {
                                System.out.println("Couldn't find a product with this search");
                                System.out.println("EXITING...");
                            }
                            else {
                                insertion_sort(productArrayList2);
                                filter(productArrayList2,test_flag);
                            }
                            break;
                        default:
                            System.out.println("WRONG INPUT, TRY AGAIN");
                    }
                    break;
                case 3:
                    System.out.println("EXITING...");
                    flag=false;
                    break;
                default:
                    System.out.println("WRONG INPUT,TRY AGAIN");
                    break;
            }
            counter++;
        }
    }

    /**
     * helper function to create an order
     * @param productArrayList arraylist
     * @param opt option
     * @param test_flag flag for testing
     */
    private void create_order_2(ArrayList<Product> productArrayList, int opt,boolean test_flag) {
        if(opt<-1 || opt>=productArrayList.size()) {
            System.out.println("Wrong input, try again");
        }
        else if(opt==-1) {
            System.out.println("EXITING...");
        }
        else {
            try {
                make_an_order(productArrayList,opt,test_flag);
            }
            catch (NullPointerException | IOException ne) {
                ne.printStackTrace();
            }
        }
    }

    /**
     * creates an order
     * @param productArrayList products
     * @param test_flag flag for testing
     */
    private void create_order(ArrayList<Product> productArrayList,boolean test_flag) {
        Scanner scanner2=new Scanner(System.in);
        System.out.println("Enter an index to make an order for a product," +
                " If you do not want to buy anything, enter 0");
        try {
            int opt=0;
            if(test_flag) {
                opt=5;
                System.out.println(opt);
            }
            else {
                opt=scanner2.nextInt();
                scanner2.nextLine();
            }
            create_order_2(productArrayList, opt-1,test_flag);
        }
        catch (InputMismatchException ne) {
            ne.printStackTrace();
        }
    }

    /**
     * displays the products with given trader name
     * @param input trader name
     * @throws FileNotFoundException if there is a problem with file
     */
    private void display(String input) throws FileNotFoundException {
        Scanner sc = new Scanner(new File("yyolcu2018/files/products.txt"));
        sc.useDelimiter("\n");   //sets the delimiter pattern

        while (sc.hasNext()) {
            String[] product_info=sc.next().split(";");
            if(product_info[2].equals(input)) {
                System.out.println("------");
                System.out.println("NAME: "+product_info[0]);
                System.out.println("DESCRIPTION: "+product_info[1]);
                System.out.println("TRADER: "+product_info[2]);
                System.out.println("ID: "+product_info[3]);
                System.out.println("CATEGORY TREE: "+product_info[4]);
                System.out.println("PRICE: "+product_info[5]);
                System.out.println("DISCOUNTED PRICE: "+product_info[6]);
                System.out.println("\n");
            }
        }
        System.out.println("\n\n\n");
        sc.close();
    }

    /**
     * customer wants to display products of a trader
     * @param test_flag flag for testing
     * @throws FileNotFoundException if there is a problem with file
     */
    public void display_products_of_a_trader(boolean test_flag) throws FileNotFoundException{
        Scanner sc = new Scanner(new File("yyolcu2018/files/users.txt"));
        sc.useDelimiter("\n");   //sets the delimiter pattern

        System.out.println("FIRST 10 TRADERS WILL BE LISTED, BUT YOU CAN STILL ENTER A TRADER NAME TO DISPLAY PRODUCTS OF THEM");
        System.out.println("THERE IS AN users.txt file so that you can find a trader");
        Scanner scanner=new Scanner(System.in);

        TreeSet<String> ten_trader=new TreeSet<>();
        boolean flag=false;
        try {
            for(int i=0;i<10;i++) {
                String[] trader=sc.next().split("\t");
                System.out.println(trader[0]);
                ten_trader.add(trader[0]);
            }
            System.out.println("\nEnter a trader name as a String");
            String input=null;
            if(test_flag) {
                input="Rama";
                System.out.println(input);
            }
            else {
                input=scanner.nextLine();
            }
            if(ten_trader.contains(input)) {
                try {
                    display(input);
                    flag=true;
                }
                catch (FileNotFoundException ne) {
                    ne.printStackTrace();
                }
            }
            else {
                while (sc.hasNext()) {
                    String[] trader_name=sc.next().split("\t");
                    if(trader_name[0].equals(input)) {
                        try {
                            display(input);
                            flag=true;
                            break;
                        }
                        catch (FileNotFoundException ne) {
                            ne.printStackTrace();
                        }
                    }
                }
            }
            if(!flag) {
                System.out.println("TRADER WITH THE GIVEN NAME IS NOT FOUND");
            }

        }
        catch (InputMismatchException ne) {
            ne.printStackTrace();
        }
        sc.close();
    }
}

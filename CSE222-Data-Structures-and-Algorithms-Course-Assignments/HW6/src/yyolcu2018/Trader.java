package yyolcu2018;

import java.io.*;
import java.util.*;

/**
 * Trader class that represents a single trader
 */
public class Trader extends Person{
    /**
     * number of property that product has
     */
    private static final int NUMBER_OF_PROPERTY=7;

    /**
     * constructor that takes parameters and calls the super class' constructor
     * @param id ID
     * @param password password
     * @param name name
     */
    public Trader(String id,String password,String name) {
        super(id,password,name);
    }

    /**
     * no parameter constructor
     */
    public Trader() {
        super();
    }

    /**
     * checks for uniqueness of the ID
     * @param id ID
     * @return if id is unique, return true otherwise return false
     * @throws FileNotFoundException if there is a problem with file
     */
    private boolean check_for_id(String id) throws FileNotFoundException {
        Scanner scanner=new Scanner(new File("yyolcu2018/files/products.txt"));
        scanner.useDelimiter("\n");
        /*
        IF WE HAVE A PRODUCT WITH GIVEN ID, THEN RETURN FALSE
         */
        while (scanner.hasNext()) {
            String[] properties=scanner.next().split(";");
            if(properties[3].equals(id)) {
                scanner.close();
                return false;
            }
        }
        scanner.close();
        return true;
    }

    /**
     * trader adds a product
     * @param test_flag flag for testing
     * @throws FileNotFoundException if there is a problem with file
     */
    public void add_product(boolean test_flag) throws FileNotFoundException {
        System.out.println("Enter Product information:");
        Scanner[] scanners=new Scanner[NUMBER_OF_PROPERTY];
        for(int i=0;i<NUMBER_OF_PROPERTY;i++) {
            scanners[i]=new Scanner(System.in);
        }
        String[] properties=new String[NUMBER_OF_PROPERTY];
        System.out.println("ENTER IN ORDER");
        System.out.println("PRODUCT NAME,DESCRIPTION,ID,CATEGORIES,PRICE,DISCOUNTED PRICE");

        for(int i=0;i<NUMBER_OF_PROPERTY;i++) {
            if(i==4) {
                /*
                CATEGORY SECTION
                 */
                System.out.println("\nEnter how many category you are going to have");
                Scanner cat=new Scanner(System.in);
                try {
                    int num_cat=0;
                    if(test_flag) {
                        num_cat=2;
                        System.out.println(num_cat);
                    }
                    else {
                        num_cat=cat.nextInt();
                        cat.nextLine();
                    }
                    if(num_cat<=0) {
                        System.out.println("Please enter a number greater than 0");
                        i--;
                    }
                    else {
                        ArrayList<String> cats=new ArrayList<>();
                        Scanner[] scanner=new Scanner[num_cat];
                        int k;
                        String[] test_cat_1=new String[2];
                        test_cat_1[0]="CAT1";
                        test_cat_1[1]="CAT2";
                        for(k=0;k<num_cat;k++) {
                            scanner[k]=new Scanner(System.in);
                            System.out.println(("Category:"+(k+1)));
                            if(test_flag) {
                                cats.add(test_cat_1[k]);
                                System.out.println(test_cat_1[k]);
                            }
                            else {
                                cats.add(scanner[k].nextLine());
                            }
                        }
                        int z=0;
                        StringBuilder stringBuilder=new StringBuilder();
                        for(String strings:cats) {
                            stringBuilder.append(strings);
                            if(z==(k-1)) {

                            }
                            else {
                                stringBuilder.append(" >> ");
                            }
                            z++;
                        }
                        properties[i]=stringBuilder.toString();
                    }
                }
                catch (InputMismatchException ne) {
                    ne.printStackTrace();
                }
            }
            else {
                if(i==2) {//TRADER SECTION
                    properties[i]=this.getName();
                }
                else {
                    String x=null;
                    if(i==0) {//PRODUCT NAME SECTION
                        System.out.println("Enter product name:");
                        if(test_flag) {
                            x="Product";
                            System.out.println(x);
                        }
                    }
                    else if(i==1) {//DESCRIPTION SECTION
                        System.out.println("Enter description:");
                        if(test_flag) {
                            x="Description";
                            System.out.println(x);
                        }
                    }
                    else if(i==3) {//ID SECTION
                        System.out.println("Enter ID:");
                        if(test_flag) {
                            x="HWYUX";
                            System.out.println(x);
                        }
                    }
                    else if(i==5) {//PRICE SECTION
                        System.out.println("Enter price:");
                        if(test_flag) {
                            x="500";
                            System.out.println(x);
                        }
                    }
                    else if(i==6) {//DISCOUNTED PRICE SECTION
                        System.out.println("Enter discounted price:");
                        if(test_flag) {
                            x="400";
                            System.out.println(x);
                        }
                    }
                    if(test_flag) {
                        properties[i]=x;
                    }
                    else {
                        properties[i]=scanners[i].nextLine();
                    }
                }
            }
        }
        try {
            int price=Integer.parseInt(properties[5]);
            int discounted_price=Integer.parseInt(properties[6]);  //PRICES PARSED
            if(price<discounted_price) {//PRICE IS NOT PROPER
                System.out.println("Please enter price as greater than discounted price");
                System.out.println("Product couldn't added");
            }
            else if(price<=0 || discounted_price<=0) { //DISCOUNTED PRICE AND PRICE ARE NOT PROPER
                System.out.println("Please enter price as greater than 0");
                System.out.println("Product couldn't added");
            }
            else {
                while(!check_for_id(properties[3])) {//ID IS NOT UNIQUE
                    Scanner scanner2=new Scanner(System.in);
                    System.out.println("This is not a unique id, try new ID");
                    properties[3]=null;
                    System.out.println("Enter new ID");
                    properties[3]=scanner2.nextLine();
                }
                try {//EVERYTHING IS OK, PRODUCT WILL BE ADDED
                    FileWriter fileWriter=new FileWriter("yyolcu2018/files/products.txt",true);
                    BufferedWriter bw = new BufferedWriter(fileWriter);
                    int z=0;
                    //String x="\"\"john\"\""; -> ""john""
                    //String x="\"john\"\; -> "john"
                    //"["" + ""]"
                    StringBuilder stringBuilder=new StringBuilder();
                    stringBuilder.append("\"[\"\"");      //WE NEED TO HAVE THEM BECAUSE OF THE .CSV FILE
                    stringBuilder.append(properties[4]);
                    stringBuilder.append("\"\"]\"");
                    for(String property:properties) {
                        if(z==4) {
                            bw.write(stringBuilder.toString());
                        }
                        else {
                            bw.write(property);
                        }
                        bw.write(";");
                        z++;
                    }
                    bw.write("\n");
                    bw.close();
                    System.out.println("Product is added successfully");
                }
                catch (IOException ne) {
                    ne.printStackTrace();
                }
            }
        }
        catch (NumberFormatException ne) {
            ne.printStackTrace();
        }
    }

    /**
     * prints the given arraylist
     * @param arrayList products
     */
    private void print(ArrayList<Product> arrayList) {    //PRINTING PRODUCT ARRAYLIST
        int count = 0;
        for (Product p : arrayList) {
            System.out.println((count + 1) + ")");
            System.out.println(p);
            count++;
        }
    }

    /**
     * displays the products of the current trader
     * @param arrayList products
     * @throws FileNotFoundException if there is a problem with file
     */
    private void display(ArrayList<Product> arrayList) throws FileNotFoundException {//READS THE PRODUCT AND ADDS TO THE ARRAYLIST TO SHOW PRODUCTS
        System.out.println("YOUR PRODUCTS");
        Scanner sc = new Scanner(new File("yyolcu2018/files/products.txt"));
        sc.useDelimiter("\n");   //sets the delimiter pattern
        while (sc.hasNext()) {
            String[] product_info = sc.next().split(";");
            if (product_info[2].equals(this.getName())) {

                LinkedList<String> catTree = new LinkedList<>();
                String clean;
                if (product_info[4].length() <= 4) {
                    catTree.add(product_info[4]);
                } else {
                    clean = product_info[4].substring(4, product_info[4].length() - 4);
                    String[] cats = clean.split(">>");
                    catTree.addAll(Arrays.asList(cats));
                }
                Comparator<Product> comparator = Comparator.comparing(Product::getName);
                int price = Integer.parseInt(product_info[5]);
                int discounted = Integer.parseInt(product_info[6]);
                double discount_amount = (100.0 - discounted * 100.0 / price);
                arrayList.add(new Product(product_info[0], product_info[1], product_info[2], product_info[3], catTree, price, discounted, discount_amount, comparator));
            }
        }
        sc.close();
    }

    /**
     * trader removes the product
     * @param test_flag flag for testing
     * @throws FileNotFoundException if there is a problem with file
     */
    public void remove_product(boolean test_flag) throws FileNotFoundException {
        ArrayList<Product> arrayList=new ArrayList<>();
        try {
            display(arrayList);      //TRADER SHOULD SEE THE THEIR PRODUCTS
            print(arrayList);
            System.out.println("Select a product");
            try {
                Scanner scanner = new Scanner(System.in);
                int option=0;
                if(test_flag) {
                    option=7;
                    System.out.println(option);
                }
                else {
                    option= scanner.nextInt();
                    scanner.nextLine();
                }
                if (option <= 0 || option > arrayList.size()) {
                    System.out.println("Enter proper number");
                }
                else {
                    try {
                        BufferedReader file=new BufferedReader(new FileReader("yyolcu2018/files/products.txt"));
                        StringBuffer inputBuffer = new StringBuffer();
                        String line;
                        int counter=0;
                        boolean flag=true;
                        while ((line=file.readLine())!=null) {
                            String[] properties=line.split(";");
                            if(flag && properties[2].contains(this.getName())) {
                                if(counter==(option-1)) {
                                    line="";
                                    inputBuffer.append(line);
                                    flag=false;
                                    System.out.println("Product is removed Successfully");       //READ LINE AND DELETE
                                }
                                else {
                                    inputBuffer.append(line);
                                    inputBuffer.append("\n");
                                }
                                counter++;
                            }
                            else {
                                inputBuffer.append(line);
                                inputBuffer.append("\n");
                            }
                        }
                        file.close();
                        // write the new string with the replaced line OVER the same file
                        FileOutputStream fileOut = new FileOutputStream("yyolcu2018/files/products.txt");
                        fileOut.write(inputBuffer.toString().getBytes());
                        fileOut.close();
                    }
                    catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            }
            catch(InputMismatchException ne) {
                ne.printStackTrace();
            }
        }
        catch (FileNotFoundException ne) {
            ne.printStackTrace();
        }
    }

    /**
     * helper function for update information
     * @param option1 option for property
     * @param option option for meet-cancel
     * @param str updated property
     */
    private void update(int option1,int option,String str) {
        try {
            // input the (modified) file content to the StringBuffer "input"
            BufferedReader file = new BufferedReader(new FileReader("yyolcu2018/files/products.txt"));
            StringBuffer inputBuffer = new StringBuffer();
            String line;
            int counter=0;
            while ((line = file.readLine()) != null) {
                String[] properties=line.split(";");
                if(properties[2].contains(this.getName())) {
                    if(counter==(option1-1)) {
                        properties[option]=null;
                        properties[option]=str;
                        StringBuilder stringBuilder=new StringBuilder();
                        int z=0;
                        for(String strs:properties) {
                            stringBuilder.append(strs);
                            if(z!=properties.length-1) {
                                stringBuilder.append(";");     //UPDATE THE PRODUCT
                            }
                            z++;
                        }
                        line = stringBuilder.toString();
                        inputBuffer.append(line);
                        inputBuffer.append('\n');
                    }
                    else {
                        inputBuffer.append(line);
                        inputBuffer.append('\n');
                    }
                    counter++;
                }
                else {
                    inputBuffer.append(line);
                    inputBuffer.append('\n');
                }
            }
            file.close();
            // write the new string with the replaced line OVER the same file
            FileOutputStream fileOut = new FileOutputStream("yyolcu2018/files/products.txt");
            fileOut.write(inputBuffer.toString().getBytes());
            fileOut.close();
        }
        catch (Exception e) {
            System.out.println("Problem reading file.");
        }
    }

    /**
     * trader edits the product
     * @param test_flag flag for testing
     * @throws FileNotFoundException if there is a problem with file
     */
    public void edit_product(boolean test_flag) throws FileNotFoundException {
        ArrayList<Product> arrayList=new ArrayList<>();
        try {
            display(arrayList);
            print(arrayList);   //TRADER SEES THEIR PRODUCT
        }
        catch (FileNotFoundException ne) {
            ne.printStackTrace();
        }
        System.out.println("Select a product");
        try {
            Scanner scanner=new Scanner(System.in);
            int option=0;
            if(test_flag) {
                option=7;
                System.out.println(option);
            }
            else {
                option=scanner.nextInt();
                scanner.nextLine();
            }
            if(option<=0 || option>arrayList.size()) {
                System.out.println("Enter proper number");
            }
            else {       //SELECTS A PRODUCT
                System.out.println("1)Product Name");
                System.out.println("2)Description");
                System.out.println("3)ID");
                System.out.println("4)Categories");
                System.out.println("5)Price");
                System.out.println("6)Discounted Price");
                System.out.println("Enter a number to edit product information.");
                Scanner scanner1=new Scanner(System.in);
                try {
                    int option2=0;
                    if(test_flag) {
                        option2=2;
                        System.out.println(option2);
                    }
                    else {
                        option2=scanner1.nextInt();
                        scanner1.nextLine();
                    }
                    if(option2<=0 || option2>6) {
                        System.out.println("Enter a proper number");
                    }
                    else {//SELECTS A PRODUCT PROPERTY
                       LinkedList<String> cats=new LinkedList<>();
                        if(option2==4) {//CATEGORY SECTION
                            System.out.println("Enter how many category you want to have:");
                            Scanner scanner2=new Scanner(System.in);
                            try {
                                int number=scanner2.nextInt();
                                scanner2.nextLine();
                                if(number<=0) {
                                    System.out.println("Enter proper number");
                                }
                                else {
                                    Scanner scanner3=new Scanner(System.in);

                                    for(int p=0;p<number;p++) {
                                        System.out.println("Enter category "+(p+1)+":");
                                        cats.add(scanner3.nextLine());
                                    }
                                    StringBuilder stringBuilder=new StringBuilder();
                                    stringBuilder.append("\"[\"\"");
                                    int counter2=0;
                                    for(String my_Cats:cats) {
                                        stringBuilder.append(my_Cats);
                                        if(counter2!=cats.size()-1) {
                                            stringBuilder.append(">>");
                                        }
                                        counter2++;
                                    }
                                    stringBuilder.append("\"\"]\"");
                                    update(option,option2,stringBuilder.toString());
                                    System.out.println("Categories updated successfully");
                                }
                            }
                            catch (InputMismatchException ne) {
                                ne.printStackTrace();
                            }
                        }
                        else if(option2==5) {//PRICE SECTION
                            Scanner scanner4=new Scanner(System.in);
                            try {
                                System.out.println("Enter price:");
                                int price=scanner4.nextInt();
                                scanner4.nextLine();
                                if(price<arrayList.get(option-1).getDiscounted_price()) {
                                    System.out.println("This price cannot be lower than discounted price");
                                }
                                else {
                                    update(option,option2,Integer.toString(price));
                                    //change price
                                    System.out.println("Price updated successfully");
                                }
                            }
                            catch (InputMismatchException ne) {
                                ne.printStackTrace();
                            }
                        }
                        else if(option2==6) {//DISCOUNTED PRICE SECTION
                            Scanner scanner5=new Scanner(System.in);
                            try {
                                System.out.println("Enter discounted price:");
                                int discounted_price=scanner5.nextInt();
                                scanner5.nextLine();
                                if(discounted_price>arrayList.get(option-1).getPrice()) {
                                    System.out.println("This discounted price cannot be greater than price");
                                }
                                else {
                                    update(option,option2,Integer.toString(discounted_price));
                                    //change discounted price
                                    System.out.println("Discounted price updated successfully");
                                }
                            }
                            catch (InputMismatchException ne) {
                                ne.printStackTrace();
                            }
                        }
                        else {//NAME, DESCRIPTION,ID
                            System.out.println("Enter updated information:");
                            Scanner scanner6=new Scanner(System.in);

                            try {
                                String str=null;
                                if(test_flag) {
                                    str="Description2";
                                    System.out.println(str);
                                }
                                else {
                                    str=scanner6.nextLine();
                                }

                                if(option2>=3) {   //ID SECTION
                                    option2+=1;
                                    while(!check_for_id(str)) {
                                        Scanner scanner2=new Scanner(System.in);
                                        System.out.println("This is not a unique id, try new ID");
                                        str=null;
                                        System.out.println("Enter new ID");
                                        str=scanner2.nextLine();
                                    }
                                }
                                update(option,option2-1,str);
                                System.out.println("Property updated successfully");
                            }
                            catch (InputMismatchException ne) {
                                ne.printStackTrace();
                            }
                            //change name,description,ID
                        }
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
     * helper function for update the orders
     * @param id ID
     */
    private void update_orders(String id) {     //TRADER METS/CANCELS THE ORDER
        try {
            BufferedReader file = new BufferedReader(new FileReader("yyolcu2018/files/orders.txt"));
            StringBuffer inputBuffer = new StringBuffer();
            String line;
            while ((line = file.readLine()) != null) {
                String[] properties=line.split("\t");
                if(properties[1].contains(id)) {
                    line="";       //ERASE PRODUCT FROM THE ORDERS.TXT
                    inputBuffer.append(line);
                }
                else {
                    inputBuffer.append(line);
                    inputBuffer.append("\n");
                }
            }
            FileOutputStream fileOut = new FileOutputStream("yyolcu2018/files/orders.txt");
            fileOut.write(inputBuffer.toString().getBytes());
            fileOut.close();
            file.close();
        }
        catch (Exception e) {
            System.out.println("Problem reading file.");
        }
    }

    /**
     * trader sees the orders of them
     * @param test_flag flag for testing
     */
    public void see_the_list_of_orders(boolean test_flag) {        //TRADER SEES THE ORDERS
        PriorityQueue<String> pq=new PriorityQueue<>();
        try {
            // input the (modified) file content to the StringBuffer "input"
            BufferedReader file = new BufferedReader(new FileReader("yyolcu2018/files/orders.txt"));
            String line;

            while ((line = file.readLine()) != null) {
                String[] properties=line.split("\t");
                if(properties[2].contains(this.getName())) {
                    pq.add(properties[1]);
                }
            }
            file.close();
            if(pq.isEmpty()) {
                System.out.println("YOU DON'T HAVE ANY ORDERS YET");
            }
            else {
                System.out.println("YOUR ORDERS:");
                int counter=0;
                for(String s:pq) {
                    System.out.println((counter+1)+")"+s);
                }
                System.out.println("Enter index to meet or cancel order");
                Scanner scanner=new Scanner(System.in);
                try {
                    int option=0;
                    if(test_flag) {
                        option=1;
                        System.out.println(option);
                    }
                    else {
                        option=scanner.nextInt();
                        scanner.nextLine();
                    }

                    if(option<=0 || option>pq.size()) {
                        System.out.println("Wrong index, try again");
                    }
                    else {
                        System.out.println("1)MEET ORDER");
                        System.out.println("2)CANCEL ORDER");
                        System.out.println("Enter:");
                        try {
                            Scanner scanner1=new Scanner(System.in);
                            int option2=0;
                            if(test_flag) {
                                option2=1;
                            }
                            else {
                                option2=scanner1.nextInt();
                                scanner1.nextLine();
                            }
                            if(option2<=0 || option2>2) {
                                System.out.println("Wrong option, try again");
                            }
                            else {
                                for(int i=0;i<(option-1);i++) {
                                    pq.poll();
                                }
                                String id=pq.peek();
                                update_orders(id);
                                if(option2==1) {      //MEET ORDER
                                    System.out.println("Order is met successfully");
                                    //erase from products.txt
                                    erase_met_order(id);
                                }
                                else {            //CANCEL ORDER
                                    System.out.println("Order is cancelled successfully");
                                }
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

        }
        catch (Exception e) {
            System.out.println("Problem reading file.");
        }
    }

    /**
     * helper function to erase the product that met
     * @param id ID
     * @throws FileNotFoundException if there is a problem with file
     */
    private void erase_met_order(String id) throws FileNotFoundException {  //WE NEED TO ERASE PRODUCT FROM THE products.txt
        ArrayList<Product> arrayList=new ArrayList<>();
        display(arrayList);
        int counter2=0;
        for(Product p:arrayList) {
            if(p.getID().contains(id)) {
                break;
            }
            counter2++;
        }
        try {
            BufferedReader file=new BufferedReader(new FileReader("yyolcu2018/files/products.txt"));
            StringBuffer inputBuffer = new StringBuffer();
            String line;
            int counter=0;
            boolean flag=true;
            while ((line=file.readLine())!=null) {
                String[] properties=line.split(";");
                if(flag && properties[2].contains(this.getName())) {
                    if(counter==(counter2)) {
                        line="";      //erase the product
                        inputBuffer.append(line);
                        flag=false;
                        System.out.println("Product is removed Successfully");
                    }
                    else {
                        inputBuffer.append(line);
                        inputBuffer.append("\n");
                    }
                    counter++;
                }
                else {
                    inputBuffer.append(line);
                    inputBuffer.append("\n");
                }
            }
            file.close();
            // write the new string with the replaced line OVER the same file
            FileOutputStream fileOut = new FileOutputStream("yyolcu2018/files/products.txt");
            fileOut.write(inputBuffer.toString().getBytes());
            fileOut.close();
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }
}

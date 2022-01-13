package yyolcu2018;

import java.util.Comparator;
import java.util.LinkedList;

/**
 * Class that represents a single product
 */
public class Product implements Comparable<Product>,Comparator<Product> {
    /**
     * Name of the product
     */
    private String name;
    /**
     * Product ID
     */
    private String ID;
    /**
     * trader name
     */
    private String trader;
    /**
     * Description of the product
     */
    private String description;
    /**
     * category tree of the product
     */
    private LinkedList<String> categoryTree;
    /**
     * price of the product
     */
    private int price;
    /**
     * discounted price of the product
     */
    private int discounted_price;
    /**
     * percentage of the discounted
     */
    private double percentage_of_discount;
    /**
     * current comparator
     */
    private Comparator<Product> comparator= Comparator.comparing(Product::getName);

    /**
     * Constructor that takes parameters and initializes the data fields
     * @param name name
     * @param description description
     * @param trader trader
     * @param ID ID
     * @param categoryTree category Tree
     * @param price price
     * @param discounted_price discounted price
     * @param percentage_of_discount percentage of the discounted
     * @param comparator comparator
     */
    public Product(String name,String description,String trader,String ID,LinkedList<String> categoryTree,int price,int discounted_price,double percentage_of_discount,Comparator<Product> comparator) {
        this.name=name;
        this.ID=ID;
        this.trader=trader;
        this.description=description;
        this.categoryTree=categoryTree;
        this.price=price;
        this.discounted_price=discounted_price;
        this.percentage_of_discount=percentage_of_discount;
        this.comparator=comparator;
    }

    /**
     * Copy constructor
     * @param my_product other product
     */
    public Product(Product my_product) {
        this.name= my_product.name;
        this.ID=my_product.ID;
        this.trader=my_product.trader;
        this.description=my_product.description;
        this.categoryTree=my_product.categoryTree;
        this.price=my_product.price;
        this.discounted_price=my_product.discounted_price;
        this.percentage_of_discount=my_product.percentage_of_discount;
        this.comparator=my_product.comparator;
    }

    /**
     * getter for name
     * @return name
     */
    public String getName() {
        return name;
    }

    /**
     * String representation of the whole product
     * @return String representation of the whole product
     */
    @Override
    public String toString() {
        StringBuilder str=new StringBuilder();

        str.append("\nNAME:");
        str.append(name);

        str.append("\nDESCRIPTION:");
        str.append(description);

        str.append("\nPRICE:");
        str.append(price);

        str.append("\nDISCOUNTED PRICE:");
        str.append(discounted_price);

        str.append("\nPERCENTAGE OF DISCOUNT:");
        str.append(percentage_of_discount);

        str.append("\nTRADER:");
        str.append(trader);

        str.append("\nCATEGORY TREE:");
        str.append(categoryTree);

        str.append("\nID:");
        str.append(ID);
        str.append("\n");

        return str.toString();
    }

    /**
     * getter for ID
     * @return ID
     */
    public String getID() {
        return ID;
    }

    /**
     * getter for trader name
     * @return trader name
     */
    public String getTrader() {
        return trader;
    }

    /**
     * getter for price
     * @return price
     */
    public int getPrice() {
        return price;
    }

    /**
     * getter for discounted price
     * @return discounted price
     */
    public int getDiscounted_price() {
        return discounted_price;
    }

    /**
     * getter for percentage of discount
     * @return percentage of discount
     */
    public double getPercentage_of_discount() {
        return percentage_of_discount;
    }

    /**
     * compareTo method uses comparators compare method
     * @param o other product
     * @return result
     */
    @Override
    public int compareTo(Product o) {
        return comparator.compare(this,o);
    }

    /**
     * compare method compares two products
     * @param o1 first product
     * @param o2 second product
     * @return result
     */
    @Override
    public int compare(Product o1, Product o2) {
        return o1.compareTo(o2);
    }

    /**
     * returns first element of the linkedlist
     * @return first element of the linkedlist
     */
    public String root_category() {
        return categoryTree.get(0);
    }

    /**
     * removes the root category of the linkedlist
     * @return true if removal is successful
     */
    public boolean remove_root_category() {
        if(categoryTree.removeFirst()==null) {
            return false;
        }
        return true;
    }
}

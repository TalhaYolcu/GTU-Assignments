/**
 * @author Yakup Talha Yolcu
 */
package yyolcu2018;

import java.util.NoSuchElementException;

/**
 * Abstract class that represents the product
 */

/*
office chairs (7 models and for each, 5 colors),
office desks (5 models and for each, 4 colors),
meeting tables (10 models and for each, 4 colors),
bookcases (12 models)
office cabinets (12 models).
 */

/**
 * Abstract class represent a product
  */
public abstract class Product implements Product_Interface{
    /**
     * model name of a product
     */
    private String model_name;
    /**
     * Color name of a product
     */
    private String color_name;
    /**
     * Number of stock
     */
    private int stock=0;

    /**
     * Return model name
     * @return model name
     */
    public String get_model_name() {
        return model_name;
    }
    /**
     * Return color name
     * @return color name
     */
    public String get_color_name() {
        return color_name;
    }
    /**
     * Return stock
     * @return stock
     */
    public int get_stock() {
        return stock;
    }

    /**
     * Setter for model name
     * @param s model name
     */
    protected void setModel_name(String s) {
        model_name=new String(s);
    }
    /**
     * Setter for color name
     * @param s color name
     */
    protected void setColor_name(String s){
        color_name=new String(s);
    }
    /**
     * Setter for stock
     * @param s stock
     */
    protected void setStock(int s) { stock=s; }

    /**
     * Clones the object
     * @return clone of object
     * @throws CloneNotSupportedException If something is wrong
     */
    protected Object clone() throws CloneNotSupportedException{

        Product o=(Product) super.clone();
        o.model_name=model_name;
        o.color_name=color_name;
        o.stock=stock;
        return  o;

    }

    /**
     * Returns string representation of object
     * @return string representation of object
     */
    public String toString() {
        StringBuilder str=new StringBuilder();
        str.append(model_name);
        str.append("\t\t\t");
        str.append(color_name+"\t\t");
        str.append(stock);
        return str.toString();
    }

    /**
     * Compares two objects
     * @param o Other object
     * @return Return true If they are equal
     */
    @SuppressWarnings("unchecked")
    public boolean equals(Object o) {
        Product tmp=(Product) o;
         return (model_name.equals(tmp.model_name) || color_name.equals(tmp.color_name));
    }

    /**
     * Helper function to change the stock
     * @param number new stock
     */
    void change_the_stock(int number) {
        stock=number;
    }

}
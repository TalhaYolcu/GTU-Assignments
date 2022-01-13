/**
 * @author Yakup Talha Yolcu
 */
package yyolcu2018;

/**
 * Class for Bookcase Product
 */
public class Bookcase extends Product {
    /**
     * Simple constructor
     * @param model represents model name
     * @param color represents color name
     * @param stock represents stock
     */
    public Bookcase(String model,String color,int stock) {
        setModel_name(model);
        setColor_name(color);
        setStock(stock);
    }

}
/**
 * @author Yakup Talha Yolcu
 */
package yyolcu2018;

/**
 * Product that have a property of Meeting Table
 */
public class MeetingTable extends Product {
    /**
     * Simple constructor
     * @param model represents model name
     * @param color represents color name
     * @param stock represents stock
     */
    public MeetingTable(String model,String color,int stock) {
        setModel_name(model);
        setColor_name(color);
        setStock(stock);
    }



}


/**
 * @author Yakup Talha Yolcu
 */
package yyolcu2018;
/**
 * Class that represents officechair product
 */
public class OfficeChair extends Product {
    /**
     * Simple constructor
     * @param model represents model name
     * @param color represents color name
     * @param stock represents stock
     */
    public OfficeChair(String model,String color,int stock) {
        setModel_name(model);
        setColor_name(color);
        setStock(stock);
    }

}
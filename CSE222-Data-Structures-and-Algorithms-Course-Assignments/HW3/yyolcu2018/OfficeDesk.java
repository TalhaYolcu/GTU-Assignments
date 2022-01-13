/**
 * @author Yakup Talha Yolcu
 */
package yyolcu2018;
/**
 * Class that represents Officedesk product
 */
public class OfficeDesk extends Product {
    /**
     * Simple constructor
     * @param model represents model name
     * @param color represents color name
     * @param stock represents stock
     */
    public OfficeDesk(String model,String color,int stock) {
        setModel_name(model);
        setColor_name(color);
        setStock(stock);
    }


}
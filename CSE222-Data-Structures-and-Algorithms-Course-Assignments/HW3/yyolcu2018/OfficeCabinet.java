/**
 * @author Yakup Talha Yolcu
 */
package yyolcu2018;

/**
 * Class that represents officecabinet product
 */
public class OfficeCabinet extends Product {
    /**
     * Simple constructor
     * @param model represents model name
     * @param color represents color name
     * @param stock represents stock
     */
    public OfficeCabinet(String model,String color,int stock) {
        setModel_name(model);
        setColor_name(color);
        setStock(stock);
    }



}
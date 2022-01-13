/**
 * @author Yakup Talha Yolcu
 */
package yyolcu2018;

/**
 * Interface that represents the Products
 */
public interface Product_Interface {
    /**
     * Return model name
     * @return model name
     */
    String get_model_name();
    /**
     * Return color name
     * @return color name
     */
    String get_color_name();
    /**
     * Return stock
     * @return stock
     */
    int get_stock();
}
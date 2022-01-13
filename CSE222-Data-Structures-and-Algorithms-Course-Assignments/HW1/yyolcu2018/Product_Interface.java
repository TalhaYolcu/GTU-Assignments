/**
 * @author Yakup Talha Yolcu
 */
package yyolcu2018;

/**
 * Interface that represents the Products
 */
public interface Product_Interface {
    /**
     * holds model array
     */
    Model[] models=null;
    /**
     * how many different models are there
     */
    int numberofmodel=0;

    /**
     * return a model in the index
     * @param index index
     * @return Model
     */
    Model getModel(int index);

    /**
     * return integer that holds how many different model
     * @return integer that holds how many different model
     */
    int getnumberofmodel();

    /**
     * add the product to the our stock
     * @param model_name model name
     * @param color_name color name
     * @param stock number of stock that will be added
     */
    void add(String model_name,String color_name,int stock);

    /**
     * remove the product from our stock
     * @param model_name model name
     * @param color_name color name
     * @param stock number of stock that will be removed
     */
    void remove(String model_name,String color_name,int stock);
}
/**
 * @author Yakup Talha Yolcu
 */
package yyolcu2018;

/**
 * Class that represents the orders of the customer
 */
public class Order {
    /**
     * model name of the product
     */
    private String model_name;
    /**
     * color name of the product
     */
    private String color_name;
    /**
     * how many product is in the order
     */
    private int number;

    /**
     * simple constructor
     */
    public Order() {
        model_name="OD1";
        color_name="BLACK";
        number=1;
    }

    /**
     * Other constructor that takes model color and number
     * @param model_nn model name of the product
     * @param color_nn color name of the product
     * @param nn number of product
     */
    public Order(String model_nn,String color_nn,int nn) {
        model_name=model_nn;
        color_name=color_nn;
        number=nn;
    }

    /**
     * like copy constructor
     * @param other other Order that will be copied
     */
    public Order(Order other) {
        model_name=other.getmodelname();
        color_name=other.getcolorname();
        number=other.getnumber();
    }

    /**
     * toString method returns the model name,color name and number
     * @return the model name,color name and number
     */
    public String toString() {
        String x=String.format("%s\t\t%s\t%d",model_name,color_name,number);
        return x;
    }

    /**
     * return model name
     * @return model name
     */
    public String getmodelname() {
        return model_name;
    }

    /**
     * return color name
     * @return color name
     */
    public String getcolorname() {
        return color_name;
    }

    /**
     * return number
     * @return number
     */
    public int getnumber() {
        return number;
    }   
}
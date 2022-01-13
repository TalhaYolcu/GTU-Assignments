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
    private final String name;

    /**
     * how many product is in the order
     */
    private final int number;

    /**
     * Simple constructor
     * @param name1 model name
     * @param name2 color name
     * @param stock stock number
     */
    public Order(String name1,String name2,int stock) {
        StringBuilder str=new StringBuilder();
        str.append(name1);
        str.append(" ");
        str.append(name2);
        str.append(" ");
        str.append(stock);
        name=str.toString();
        number=stock;
    }

    /**
     * like copy constructor
     * @param other other Order that will be copied
     */
    public Order(Order other) {
        name=other.get_name();
        number=other.get_number();
    }

    /**
     * toString method returns the model name,color name and number
     * @return the model name,color name and number
     */
    public String toString() {
        return name;
    }

    /**
     * return number
     * @return number
     */
    public int get_number() {
        return number;
    }

    /**
     * Getter for name of the product
     * @return name of the product
     */
    public String get_name() {
        return name;
    }
}
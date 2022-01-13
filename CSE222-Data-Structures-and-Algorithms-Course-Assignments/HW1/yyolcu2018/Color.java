/**
 * @author Yakup Talha Yolcu
 */
package yyolcu2018;

/**
 * Class that represents the Color of the Model of the Product
 */
public class Color {
    /**
     * Field that holds the colorname
     */
    private String colorname;
    /**
     * Field that holds the number of the stock of this color
     */
    private int number;

    /**
     * Constructor
     * @param name name of the color
     * @param n number of stock
     */
    public Color(String name,int n) {
        this.colorname=name;
        this.number=n;
    }

    /**
     * return the color name
     * @return color name
     */
    public String getcolorname() {
        return colorname;
    }

    /**
     * return the number of stock
     * @return number of stock
     */
    public int getnumber() {
        return this.number;
    }

    /**
     * add a product of this color
     * @param c1 Color that will be added
     */
    public void add(Color c1) {
        number+=c1.getnumber();
    }

    /**
     * add product of this stock
     * @param stock hold the stock
     */
    public void add(int stock) {
        number+=stock;
    }

    /**
     * remove the product
     * @param stock number of stock that will be removed
     * @throws Exception if requested is larger than the our stock
     */
    public void remove(int stock) throws  Exception{
        if(number<stock) {
            throw new Exception("Stock is wrong");
        }
        number-=stock;
    }

    /**
     * make sale(Branch employee comes here)
     * @param number number of product that sold
     */
    public void make_sale(int number) {
        this.number-=number;
    }
}
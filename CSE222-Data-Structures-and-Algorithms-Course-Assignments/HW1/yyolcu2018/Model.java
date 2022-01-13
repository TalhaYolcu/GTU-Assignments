/**
 * @author Yakup Talha Yolcu
 */
package yyolcu2018;

import java.util.NoSuchElementException;

/**
 * Class that holds the Models
 */
public class Model {
    /**
     * name of the model
     */
    private String name;
    /**
     * color array that holds the color
     */
    public Color[] color;
    /**
     * Model constructor
     * @param n name of the model
     */
    public Model(String n) {
        name=n;
    }

    /**
     * toString method returns the name of the Model
     * @return name of the Model
     */
    public String toString() {
        return name;
    }

    /**
     * return the model name
     * @return model name
     */
    public String get_name() {
        return name;
    }

    /**
     * return stock of this model
     * @return stock of this model
     */
    public int getnum() {
        int sum=0;
        for(int i=0;i<color.length;i++) {
            sum+=color[i].getnumber();
        }
        return sum;
    }

    /**
     * add stock to this model
     * @param m1 product that will be added
     */
    public void add(Model m1) {
        for(int i=0;i<color.length;i++) {
            color[i].add(m1.color[i]);
        }
    }

    /**
     * add stock to this model
     * @param color_name color name
     * @param stock number of stock that will be added
     */
    public void add(String color_name,int stock) {
        for(int i=0;i<color.length;i++) {
            if(color[i].getcolorname().equals(color_name)) {
                color[i].add(stock);
            }
        }      
    }

    /**
     * remove some product from our stock
     * @param color_name color name of the product
     * @param stock stock that will be removed
     * @throws NoSuchElementException if something is wrong such as stock,color name
     */
    public void remove(String color_name,int stock) throws  NoSuchElementException {
        boolean flag=false;
        for(int i=0;i<color.length;i++) {
            if(color[i].getcolorname().equals(color_name)) {
                flag=true;
                try {
                    color[i].remove(stock);
                }
                catch (Exception ne) {
                    System.out.println(ne);
                }

            }
        }
        if(flag==false) {
            throw new NoSuchElementException("Exception occured, this color does not exist");
        }
    }

    /**
     * getter for Color
     * @param index index of the color array
     * @return color
     */
    public Color getColor(int index) {
        return color[index];
    }
}
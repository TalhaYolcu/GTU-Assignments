/**
 * @author Yakup Talha Yolcu
 */
package yyolcu2018;

import java.util.NoSuchElementException;

/**
 * Abstract class that represents the person
 */
public abstract class Product implements Product_Interface{
    /**
     * model array
     */
    protected Model[] models;
    /**
     * number of models
     */
    protected int numberofmodel;

    /**
     * return model in that index
     * @param index index
     * @return Model
     */
    public Model getModel(int index) {
        return models[index];
    }

    /**
     * number of model
     * @return number of model
     */
    public int getnumberofmodel() {
        return numberofmodel;
    }

    /**
     * Stock of this product
     * @param model_name model name
     * @param color_name color name
     * @return integer that represents stock of the product
     */
    public int get_stock(String model_name,String color_name) {
        int sum=0;
        for(int i=0;i<models.length;i++) {
            if(models[i].get_name().equals(model_name)) {
                for(int k=0;k<models[i].color.length;k++) {
                    if(models[i].color[k].getcolorname().equals(color_name)) {
                        sum+=models[i].color[k].getnumber();
                    }
                }
            }
        }
        return sum;
    }

    /**
     * add product
     * @param model_name model name
     * @param color_name color name
     * @param stock number of stock that will be added
     */
    public void add(String model_name,String color_name,int stock) {
        for(int i=0;i<models.length;i++) {
            if(models[i].get_name().equals(model_name)) {
                models[i].add(color_name,stock);
            }
        }       
    }

    /**
     * remove product
     * @param model_name model name
     * @param color_name color name
     * @param stock number of stock that will be removed
     * @throws NoSuchElementException if something is wrong such as stock,color - model name
     */
    public void remove(String model_name,String color_name,int stock) throws NoSuchElementException {
        boolean flag=false;
        for(int i=0;i<models.length;i++) {
            if(models[i].get_name().equals(model_name)) {
                flag=true;
                try {
                    models[i].remove(color_name,stock);
                }
                catch (NoSuchElementException ne) {
                    System.out.println(ne);
                }

            }
        }
        if(flag==false) {
            throw new NoSuchElementException("Exception occured, this model name is wrong");
        }
    }
}
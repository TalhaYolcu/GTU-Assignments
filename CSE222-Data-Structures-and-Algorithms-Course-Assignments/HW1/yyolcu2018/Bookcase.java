/**
 * @author Yakup Talha Yolcu
 */
package yyolcu2018;

/**
 * Class for Bookcase Product
 */
public class Bookcase extends Product {

    /**
     * Constructor
     */
    public Bookcase() {
        models=new Model[12];
        /*
        adding model and color name
         */
        for(int i=0;i<12;i++) {
            String O=new String("BC");
            O+=new String(String.valueOf(i+1));
            models[i]=new Model(O);
            models[i].color=new Color[1];
            models[i].color[0]=new Color("BLACK",1);
        } 
        numberofmodel=12;
    }

    /**
     * Overriden toString method
     * @return String
     */
    public String toString() {
        String temp=new String("BOOKCASES\n");
        temp+="MODEL NAME\tSTOCK NUMBER\n";
        for(int i=0;i<12;i++) {
            temp+=String.format("%s\t\t\t",models[i]);
            temp+=String.format("%d\n",models[i].getnum());
        } 
        temp+="\n\n";
        return temp;        
    }

    /**
     * Branch employee calls this method to add bookcase
     * @param o1 product will be added
     */
    public void add(Bookcase o1) {
        for(int i=0;i<models.length;i++) {
            models[i].add(o1.models[i]);
        }
    }
}
/**
 * @author Yakup Talha Yolcu
 */
package yyolcu2018;

/**
 * Class that represents officecabinet product
 */
public class OfficeCabinet extends Product {
    /**
     * constructor
     */
    public OfficeCabinet() {
        models=new Model[12];
        for(int i=0;i<12;i++) {
            String O=new String("OCA");
            O+=new String(String.valueOf(i+1));
            models[i]=new Model(O);
            models[i].color=new Color[1];
            models[i].color[0]=new Color("BLACK",1);
        } 
        numberofmodel=12;
    }

    /**
     * toString method that returns models, colors and stock number
     * @return models, colors and stock number
     */
    public String toString() {
        String temp=new String("OFFICE CABINETS\n");
        temp+="MODEL NAME\tSTOCK NUMBER\n";
        for(int i=0;i<12;i++) {
            temp+=String.format("%s\t\t\t",models[i]);
            temp+=String.format("%d\n",models[i].getnum());
        }  
        temp+="\n\n";
        return temp;       
    }

    /**
     * add product
     * @param o1 product that will be added
     */
    public void add(OfficeCabinet o1) {
        for(int i=0;i<models.length;i++) {
            models[i].add(o1.models[i]);
        }
    }
}
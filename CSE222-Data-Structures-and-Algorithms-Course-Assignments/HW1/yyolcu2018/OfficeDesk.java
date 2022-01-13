/**
 * @author Yakup Talha Yolcu
 */
package yyolcu2018;
/**
 * Class that represents Officedesk product
 */
public class OfficeDesk extends Product {
    /**
     * constructor
     */
    public OfficeDesk() {
        models=new Model[10];
        for(int i=0;i<10;i++) {
            String O=new String("OD");
            O+=new String(String.valueOf(i+1));
            models[i]=new Model(O);
            models[i].color=new Color[4];
            models[i].color[0]=new Color("RED",1);
            models[i].color[1]=new Color("BLUE",1);
            models[i].color[2]=new Color("BLACK",1);
            models[i].color[3]=new Color("GREEN",1);
        } 
        numberofmodel=10;
    }
    /**
     * toString method that returns models, colors and stock number
     * @return models, colors and stock number
     */
    public String toString() {
        String temp=new String("OFFICE DESKS\n");
        temp+="MODEL NAME\tSTOCK NUMBER\n";
        for(int i=0;i<10;i++) {
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
    public void add(OfficeDesk o1) {
        for(int i=0;i<models.length;i++) {
            models[i].add(o1.models[i]);
        }
    }   
}
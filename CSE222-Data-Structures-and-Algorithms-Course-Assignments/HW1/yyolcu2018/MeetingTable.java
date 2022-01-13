/**
 * @author Yakup Talha Yolcu
 */
package yyolcu2018;

/**
 * Product that have a property of Meeting Table
 */
public class MeetingTable extends Product {
    /**
     * Simple constructor
     */
    public MeetingTable() {
        models=new Model[10];
        for(int i=0;i<10;i++) {
            String O=new String("MT");
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
     * simple toString that returns model name, stock number
     * @return hold information about product
     */
    public String toString() {
        String temp=new String("MEETING TABLES\n");
        temp+="MODEL NAME\tSTOCK NUMBER\n";
        for(int i=0;i<10;i++) {
            temp+=String.format("%s\t\t\t",models[i]);
            temp+=String.format("%d\n",models[i].getnum());
        }    
        temp+="\n\n"; 
        return temp;    
    }

    /**
     * if new item should be added
     * @param o1 add this item
     */
    public void add(MeetingTable o1) {
        for(int i=0;i<models.length;i++) {
            models[i].add(o1.models[i]);
        }
    } 
}


package yyolcu2018;
/**
 * Class holds the value and its occurrence
 * @param <E> Comparable Generic class
 */
public class Values<E extends Comparable<E>> {
    /**
     * value
     */
    private E value;
    /**
     * occurrence of the value
     */
    private int occurence;

    /**
     * Simple constructor
     * @param val value
     * @param occur occurrence
     */
    public Values(E val,int occur) {
        value=val;
        occurence=occur;
    }

    /**
     * increments occurrence
     */
    public void add_one() {
        occurence+=1;
    }

    /**
     * decrements occurrence
     */
    public void remove_one() {
        occurence-=1;
    }

    /**
     * Copy constructor
     * @param other other item that will be copied
     */
    public Values(Values<E> other) {
        value= other.value;
        occurence= other.occurence;
    }

    /**
     * return the value
     * @return value
     */
    public E getValue() {
        return value;
    }

    /**
     * Return the occurrence
     * @return occurrence
     */
    public int getOccurence() {
        return occurence;
    }

    /**
     * Value,occurrence
     * @return String representation of the Value class
     */
    public String toString() {
        StringBuilder str=new StringBuilder();
        str.append("(");
        str.append(value);
        str.append(",");
        str.append(occurence);
        str.append(") ");
        return str.toString();
    }
}

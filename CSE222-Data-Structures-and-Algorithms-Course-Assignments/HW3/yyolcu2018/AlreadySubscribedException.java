/**
 * @author Yakup Talha Yolcu
 */
package yyolcu2018;
/**
 * Exception class for Already subscribtion
 */
public class AlreadySubscribedException extends Throwable{
    /**
     * field that holds content
     */
    private String s;
    /**
     * Constructor
     * @param s Content
     */
    public AlreadySubscribedException(String s) {
        this.s=s;
    }
    /**
     * @return String that for toString
     */
    public String toString() {
        return s;
    }
}
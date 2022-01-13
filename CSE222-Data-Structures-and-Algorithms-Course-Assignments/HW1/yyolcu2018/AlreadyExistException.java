/**
 * @author Yakup Talha Yolcu
 */
package yyolcu2018;

/**
 * Exception class for Already existence
 */
public class AlreadyExistException extends Throwable{

    /**
     * field that holds content
     */
    private String s;

    /**
     * Constructor
     * @param s Content
     */
    public AlreadyExistException(String s) {
        this.s=s;
    }

    /**
     * @return String that for toString
     */
    public String toString() {
        return s;
    }
}

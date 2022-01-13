/**
 * @author Yakup Talha Yolcu
 */
package yyolcu2018;

/**
 * Simple exception class
 */
public class Exception extends Throwable {
    /**
     * hold content
     */
    private String message;

    /**
     * simple constructor
     * @param message hold message
     */
    public Exception(String message) {
        this.message=message;
    }

    /**
     * print the message
     * @return hold the message
     */
    public String toString() {
        return new String("Exception occured: "+this.message);
    }
}
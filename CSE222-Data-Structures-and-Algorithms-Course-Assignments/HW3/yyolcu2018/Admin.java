/**
 * @author Yakup Talha Yolcu
 */


package yyolcu2018;

import java.util.NoSuchElementException;

/**
 * Class that represents admins
 */
public class Admin {
    /**
    * Field that holds the whole company
     */
    private Company c;
    /**
     * Field that represents the whether admin is informed
     */
    private boolean informing=false;

    /**
     * Simple constructor takes parameter
     * @param c1 Company that will be referenced
     */
    public Admin(Company c1) {
        c=c1;
    }

    /**
     * Admin adds a branch
     * @param b Branch that will be added
     */
    public void add_branch(Branch b) {
        c.add_branch(b);
    }

    /**
     * Admin removes a branch
     * @param index index that represents the index of a branch
     */
    public void remove_branch(int index) {
        c.remove_branch(index);
    }

    /**
     * Admin adds a branch employee to the given branch
     * @param index which branch will be used
     */
    public void add_branch_employee(int index) {
        c.get_branch(index).add_branch_employee();
    }

    /**
     * Admin removes a branch employee from the given branch
     * @param index which branch will be used
     */
    public void remove_branch_employee(int index) {
        c.remove_branch_employee(index);
    }

    /**
     * Admin queries the for supply need
     * @param branch_index Branch that will be queried
     * @return is there any supply need?
     */
    public boolean query_for_supply(int branch_index) {
        if(c.get_branch(branch_index).get_inform()) {
            informing=true;
            c.get_branch(branch_index).set_inform(false);
        }
        return informing;
    }


}
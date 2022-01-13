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
     * field that represents the whether product is needed
     */
    private boolean needed;
    /**
     * Company that Admin belongs to
     */
    private Company c;

    /**
     * Intentionally empty Constructor
     */
    public Admin() {
    }

    /**
     * Adds branch to the given company.
     * @param c1 Company that branch will be added
     * @param b1 Branch that will be added
     */
    public void add_branch(Company c1,Branch b1) {
        try {
            c1.add_branch(b1);
        }
        catch (AlreadyExistException ne) {
            System.out.println(ne);
        }

    }

    /**
     * Removes the branch
     * @param c1 Company that branch will remove
     * @param index Index that will be removed
     */
    public void remove_branch(Company c1,int index) {
        try {
            c1.remove_branch(index);
        }
        catch(NullPointerException ne) {
            System.out.println(ne);
        }
    }

    /**
     * Adds branch employee to the given branch
     * @param b1 Branch that Branch Employee will be added
     */
    public void add_branch_employee(Branch b1) {
        b1.resize_branch_employee();
    }

    /**
     * Removes branch employee from given branch
     * @param b1 Branch that BE removed
     */
    public void remove_branch_employee(Branch b1) {
        try {
            b1.remove_branch_employee();
        }
        catch (NoSuchElementException ne) {
            System.out.println(ne);
        }
    }

    /**
     * Admin asks for product need
     * @return whether is it needed
     */
    public boolean ask_for_supply_need() {
        return get_need();
    }

    /**
     * Setter for needing
     * @param need needing
     */
    public void set_need(boolean need) {
        needed=need;
    }

    /**
     * Getter for needing
     * @return is it needed
     */
    public boolean get_need() {
        return needed;
    }

    /**
     * Is product added?
     * @param b Branch employee
     */
    public void is_added(BranchEmployee b) {
        if(b.is_added()) {
            set_need(false);
        }
    }
}
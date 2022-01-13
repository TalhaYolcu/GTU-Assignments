/**
 * @author Yakup Talha Yolcu
 */
package yyolcu2018;

/**
 * Class that represents the Company
 */
public class Company {
    /**
     * ArrayList for admins
     */
    private TArrayList<Admin> admin;
    /**
     * LinkedList for branches
     */
    private TLinkedList<Branch> branch;

    /**
     * Simple constructor
     */
    public Company() {
        /*
        admins and branches are created,admins branch employees and customers are added
         */
        admin=new TArrayList<>();
        branch=new TLinkedList<>();
        admin.add(new Admin(this));
        admin.add(new Admin(this));
        add_admin();
        branch.add(new Branch("BRANCH_B"+branch.size()));
        branch.add(new Branch("BRANCH_B"+branch.size()));
        branch.get(0).add_branch_employee();
        branch.get(1).add_branch_employee();
        branch.get(0).add_customer(new Customer("NULL1",new Person("NULL1","NULL1","NULL1","NULL1")));
        branch.get(1).add_customer(new Customer("NULL2",new Person("NULL2","NULL2","NULL2","NULL2")));
    }

    /**
     * Helper function to add an admin
     */
    void add_admin() { admin.add(new Admin(this)); }

    /**
     * Helper function to add branch
     * @param b Branch that will be added
     */
    void add_branch(Branch b) {
        branch.add(b);
        branch.get(branch.size()-1).add_branch_employee();
    }

    /**
     * Helper function to remove a branch
     * @param index Index of the Branch that will be removed
     */
    void remove_branch(int index) { branch.remove(index); }

    /**
     * returns an admin with the given index
     * @param index Index for admin
     * @return Admin
     */
    public Admin getAdmin(int index) {
        return admin.get(index);
    }

    /**
     * Getter for branch
     * @param index Index of the branch
     * @return Branch
     */
    public Branch get_branch(int index) { return this.branch.get(index); }

    /**
     * Helper function to remove a branch employee
     * @param index Index of the branch employee to remove
     */
    void remove_branch_employee(int index) { branch.get(index).remove_branch_employee(); }

    /**
     * Returns the number of branches
     * @return size of the branch linkedlist
     */
    public int get_number_of_branch() { return branch.size(); }

    /**
     * Returns an iterator for the branch linkedlist
     * @return iterator for branch linkedlist
     */
    TIterator<Branch> get_branch_iterator() {
        return branch.iterator();
    }

}
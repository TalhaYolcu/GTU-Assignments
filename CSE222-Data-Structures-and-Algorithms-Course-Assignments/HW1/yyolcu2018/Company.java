/**
 * @author Yakup Talha Yolcu
 */
package yyolcu2018;

/**
 * Class that represents the Company
 */
public class Company {
    /**
     * Field that holds the branch of the company
     */
    private Branch[] b;
    /**
     * number of branches
     */
    private int numofb=0;
    /**
     * holds the admins of the company
     */
    private Admin[] admins;

    /**
     * Constructor
     */
    public Company() {
        b=new Branch[4];
        String B1="BRANCH_B";
        for(int i=0;i<4;i++) {
            b[i]=new Branch(B1+ new String(String.valueOf(i+1)),5);
        }
        admins=new Admin[10];
        for(int i=0;i<10;i++) {
            admins[i]=new Admin();
        }
        numofb=4;
    }

    /**
     * get number of branches
     * @return integer that represents the number of branches
     */
    public int getnumofb() {
        return numofb;
    }

    /**
     * return the given index Branch
     * @param index Branch
     * @return Branch that requested
     * @throws IndexOutOfBoundsException there is no branch in this index
     */
    public Branch getBranch(int index) throws IndexOutOfBoundsException {
        if(index>=bsize()) {
            throw new IndexOutOfBoundsException("Exception Occured: There is no Branch in this index");
        }
        return b[index];
    }

    /**
     * return the admin at the given index
     * @param index index for admin array
     * @return return me an Admin
     * @throws IndexOutOfBoundsException if there is no Admin in this index
     */
    public Admin getAdmin(int index) throws IndexOutOfBoundsException{
        if(index>=admins.length) {
            throw new IndexOutOfBoundsException("Exception Occured: There is no Admin in this index");
        }
        return admins[index];
    }

    /**
     * return branch array size
     * @return integer that represents the size of the branch array
     */
    public int bsize() {
        return b.length;
    }

    /**
     *  add a branch to the company
     * @param b1 Branch that will be added
     * @throws AlreadyExistException if this branch is already exist
     */
    public void add_branch(Branch b1) throws  AlreadyExistException{
    /*
    resize branch array,add branch
     */
        for(int i=0;i<bsize();i++) {
            if(b[i].get_name().equals(b1.get_name())) {
                throw new AlreadyExistException("Exception occured, this branch is already exist");
            }
        }

        Branch[] temp=new Branch[b.length+1];
        int i=0;
        for(i=0;i<b.length;i++) {
            temp[i]=new Branch(b[i].get_name(),b[i].getnumofbe());
        }
        temp[i]=new Branch(b1.get_name(),b1.getnumofbe());
        b=new Branch[b.length+1];
        for(int k=0;k<b.length;k++) {
            b[k]=new Branch(temp[k].get_name(),temp[k].getnumofbe());
        }
        numofb+=1;
    }

    /**
     * remove the branch
     * @param index represent the branch
     * @throws NullPointerException if there is no branch in this index
     */
    public void remove_branch(int index) throws NullPointerException{
        if(index>=bsize()) {
            throw new NullPointerException("Exception occured,There is no Branch in this index");
        }
        else {
            for(int i=index;i<b.length-1;i++) {
                b[i]=new Branch(b[i+1].get_name(),b[i+1].getnumofbe());
            }
            numofb-=1;
        }

    }

    /**
     * add a branch employee to the branch
     * @param b1 Branch that will be added to
     */
    public void add_branch_employee(Branch b1) {
        b1.resize_branch_employee();
    }

    /**
     * remove a branch employee to the given branch
     * @param b1 branch that will be removed from
     */
    public void remove_branch_employee(Branch b1) {
        b1.remove_branch_employee();
    }

    /**
     * inform admin about product is needed (Branch employee comes here)
     * @param a1 admin that will be informed
     */
    public void informadmin(Admin a1) {
        a1.set_need(true);
        System.out.println("Admin is informed");
    }
}

package yyolcu2018;

/**
 * Binary Search Tree Heap Tree class
 * @param <E> Takes a paremeter as a comparable class
 */
public class BSTHeapTree<E extends Comparable<E>> {
    /**
     * the whole data
     */
    private BinarySearchTree<TMaxHeap<E>> bst;

    /**
     * Simple constructor
     * @param root takes a MaxHeap as a root
     * @throws NullPointerException if maxheap is null, it will be thrown
     */
    public BSTHeapTree(TMaxHeap<E> root) throws NullPointerException{
        bst=new BinarySearchTree<>();
        if(root==null) {
            throw new NullPointerException();
        }
        bst.add(root);
    }

    /**
     * Private method that searches for an element in the current max heap
     * @param cur_root curren max heap
     * @param val item that is searched
     * @return if maxheap contains the item,return true otherwise return false
     */
    private boolean search_for_recursive(BinaryTree.Node<TMaxHeap<E>> cur_root,E val) {
        /*
        If current root is null,return false Otherwise look for item , if current
        root does not contain it look left and right
         */
        if(cur_root==null) {
            return false;
        }
        if(cur_root.data.contains(val)) {
            return true;
        }
        return search_for_recursive(cur_root.left,val) || search_for_recursive(cur_root.right,val);
    }

    /**
     * Increments the occurrence of the value by one
     * @param cur_root current max heap
     * @param val value that whose occurrence will be incremented
     * @return if it is incremented successfully
     */
    private boolean increment_by_one(BinaryTree.Node<TMaxHeap<E>> cur_root, E val) {
        /*
        If current root is null,return false.
        If item is at the current root, add (true) and return true
        Otherwise look left and right
         */
        if(cur_root==null) {
            return false;
        }
        if(cur_root.data.contains_and_set(val,true)) {
            return true;
        }
        return increment_by_one(cur_root.left,val) || increment_by_one(cur_root.right,val);
    }

    /**
     * Adds a new value to the BSTHeapTree
     * @param val value that will be added
     * @return if it is added return true
     */
    public boolean add_new_value(E val) {
        /*
        If value is added before, increment its value
        Otherwise find proper place and add
         */
        if(search_for_recursive(bst.root,val)) {
            return increment_by_one(bst.root,val);
        }
        return add_new_value_recursive(bst.root,val);
    }

    /**
     * private add function
     * @param cur_root current heap that item will be added to
     * @param val item that will be added
     * @return if item is added successfully return true
     */
    private boolean add_new_value_recursive(BinaryTree.Node<TMaxHeap<E>> cur_root, E val) {
        /*
        If current root is null, create a heap.Add item to this heap
        If current root is full and right is null, create right heap
        If current root is full and left is null, create left heap
        Compare the value of current root and the item, decide where to put the item
        If there current root has a space, add this item to the current heap.
         */
        if(cur_root==null) {
            cur_root=new BinaryTree.Node<>(new TMaxHeap<>());
            return cur_root.data.offer(val);
        }
        else if(cur_root.data.isFull()) {
            if(cur_root.right==null) {
                cur_root.right=new BinaryTree.Node<>(new TMaxHeap<>());
            }
            if(cur_root.left==null) {
                cur_root.left=new BinaryTree.Node<>(new TMaxHeap<>());
            }
            if(cur_root.data.get_root_val().compareTo(val)<0) {
                return add_new_value_recursive(cur_root.right,val);
            }
            else if(cur_root.data.get_root_val().compareTo(val)>0) {
                return add_new_value_recursive(cur_root.left,val);
            }
            return false;
        }
        else {
            return cur_root.data.offer(val);
        }
    }

    /**
     * Simple toString method, uses binary search trees toString method
     * @return String representation of the binary search tree heap tree
     */
    public String toString() {
        return bst.toString();
    }

    /**
     * Simple add method to add something to the BSTHeapTree
     * @param item item that will be added
     * @return if it is added successfully return true
     */
    public int add(E item) {
        add_new_value(item);
        return find(item);
    }

    /**
     * Decrements the value of the item, if it is going to be , then removes it
     * @param cur_root current root that item will be queried
     * @param val item
     * @return if it is removed  successfully, return true
     */
    private boolean decrement_by_one(BinaryTree.Node<TMaxHeap<E>> cur_root, E val) {
        /*
        If current root is null, return false
        If current root's heap is null, return false
        If current root contains the item,return true
        Otherwise look left and right
         */
        if(cur_root==null) {
            return false;
        }
        else if(cur_root.data==null) {
            return false;
        }
        else if(cur_root.data.contains_and_set(val,false)) {
            return true;
        }
        return decrement_by_one(cur_root.left,val) || decrement_by_one(cur_root.right,val);
    }

    /**
     * finds the minimum value of the current root and returns it
     * @param cur_root current heap
     * @return minimum value of the heap
     */
    private Values<E> get_min_and_remove(BinaryTree.Node<TMaxHeap<E>> cur_root) {
        /*
        If current root is null,return null
        If current root's left is not null,go to the left
        If current heap is null, return null
        Otherwise find the minimum of the heap.
        If you couldn't find,return null
        Otherwise remove this item from the current place, and return this item.
         */
        if(cur_root==null) {
            return null;
        }
        if(cur_root.left!=null) {
            return get_min_and_remove(cur_root.left);
        }
        if(cur_root.data==null) {
            return null;
        }
        Values<E> ret=cur_root.data.get_min();
        if(ret==null) {
            return null;
        }
        remove_recursive(cur_root,ret.getValue());
        return ret;
    }

    /**
     * Removes the item from the given heap
     * @param cur_root heap that will be queried
     * @param item item that will be removed
     */
    private void remove_recursive(BinaryTree.Node<TMaxHeap<E>> cur_root,E item) {
        /*
        If current root is null, return null
        If current root's heap is null, return null
        If current root contains it
            If current root left and right are null
                remove the item from the current root.
                After removal, if heap is empty,remove this heap.
            If current root left is null,
                Get the right min value, remove min value from its place
                if it is null, it is exception.
                Otherwise set the value.
             Other wise take the root of the left, remove it and replace it with the our item that will be removed.
        Otherwise look to the left and right.
         */
        if(cur_root==null) {

        }
        else if(cur_root.data==null) {

        }
        //if we find the item
        else if(cur_root.data.contains(item)) {
            //if maxheap is not full
            if(cur_root.left==null && cur_root.right==null) {
                cur_root.data.remove_h(item);
                if(cur_root.data.isEmpty()) {
                    cur_root.data=null;
                    cur_root=null;
                }
            }
            //if left is empty,right has element
            else if(cur_root.left==null) {
                Values<E> temp=get_min_and_remove(cur_root.right);
                try {
                    cur_root.data.set(cur_root.data.indexOf(item),temp);
                }
                catch (NullPointerException ne) {
                    System.out.println(ne);
                }

            }
            //if left and right has element
            else {
                if(cur_root.left.data==null) {
                    Values<E> temp=get_min_and_remove(cur_root.right);
                    try {
                        cur_root.data.set(cur_root.data.indexOf(item),temp);
                    }
                    catch (NullPointerException ne) {
                        System.out.println(ne);
                    }
                }
                else {
                    Values<E> temp2=cur_root.left.data.get_root();
                    if(temp2==null) {
                        if(cur_root.right==null || cur_root.right.data==null) {

                        }
                        else {
                            Values<E> temp=get_min_and_remove(cur_root.right);
                            try {
                                cur_root.data.set(cur_root.data.indexOf(item),temp);
                            }
                            catch (NullPointerException ne) {
                                System.out.println(ne);
                            }
                        }
                    }
                    else {
                        cur_root.left.data.remove_h(temp2.getValue());
                        try {
                            cur_root.data.set(cur_root.data.indexOf(item),temp2);
                        }
                        catch (NullPointerException ne) {
                            System.out.println(ne);
                        }
                    }
                }
            }
        }
        //if we couldn't find the element
        else {
            remove_recursive(cur_root.left,item);
            remove_recursive(cur_root.right,item);
        }
    }

    /**
     * Removes the item from the BSTHeapTree
     * @param item item that will be removed
     * @return occurence of the removed item
     * @throws NullPointerException if item is null, it is thrown
     */
    public int remove(E item) throws NullPointerException{
        /*
        If item is null,throw exception
        Find occurrence of the item.
        If it is 1,remove item
        Otherwise decrement it is occurrence
         */
        if(item==null) {
            throw new NullPointerException();
        }
        int occur=find(item);
        if(occur==1) {
            remove_recursive(bst.root,item);
        }
        else if(occur>1) {
            decrement_by_one(bst.root,item);
        }
        return occur;
    }

    /**
     * Find item and return occurrence
     * @param cur_root current heap that will be queried
     * @param val item that is searched
     * @return occurrence of the item
     */
    private int find_recursive(BinaryTree.Node<TMaxHeap<E>> cur_root,E val) {
        /*
        If heap node is null,return null
        If inside of the heap is null, return null
        If cur root is empty, returnu 0, it doesn't contains it.
        Otherwise look this heap and right and left
         */
        if(cur_root==null) {
            return 0;
        }
        else if(cur_root.data==null) {
            return 0;
        }
        else if(cur_root.data.isEmpty()) {
            return 0;
        }
        return cur_root.data.give_occurence(val) + find_recursive(cur_root.left,val) + find_recursive(cur_root.right,val);
    }

    /**
     * Return the occurrence of the item
     * @param item item that will be queried
     * @return occurrence of the item
     */
    public int find(E item) {
        return find_recursive(bst.root,item);
    }

    /**
     * Compares two values' occurrences and returns the max of them.
     * @param val1 leftvalue
     * @param val2 rightvalue
     * @return max value
     */
    private Values<E> find_max(Values<E> val1,Values<E> val2) {
        if(val1==null) {
            if(val2==null) {
                return null;
            }
            return val2;
        }
        else if(val2==null) {
            return val1;
        }
        else {
            if(val1.getOccurence()>val2.getOccurence()) {
                return val1;
            }
            return val2;
        }
    }

    /**
     * finds the mode of the current heap
     * @param cur_root heap that will be queried
     * @return mode of the BSTHeap
     */
    private Values<E> find_mode_recursive(BinaryTree.Node<TMaxHeap<E>> cur_root) {
        /*
        If current root is null,return null
        If current root data is null, return null
        Find mode of the heap.
        If it is null, return null
        Otherwise look to the left and right,compare with them and return the max of them.
         */
        if(cur_root==null) {
            return null;
        }
        else if(cur_root.data==null) {
            return null;
        }
        Values<E> val=cur_root.data.give_mode();
        if(val==null) {
            return null;
        }
        else {
            if(cur_root.left==null) {
                if(cur_root.right==null) {
                    return val;
                }
                else {
                    Values<E> val3=find_mode_recursive(cur_root.right);
                    return find_max(val,val3);
                }
            }
            else {
                Values<E> val2=find_mode_recursive(cur_root.left);
                if(cur_root.right==null) {
                    return find_max(val,val2);
                }
                else {
                    Values<E> val3=find_mode_recursive(cur_root.right);
                    return find_max(val,find_max(val2,val3));
                }
            }
        }
    }

    /**
     * Finds the mode of the BSTHeap
     * @return mode of the BSTHeap
     */
    public E find_mode() {
        return find_mode_recursive(bst.root).getValue();
    }
}

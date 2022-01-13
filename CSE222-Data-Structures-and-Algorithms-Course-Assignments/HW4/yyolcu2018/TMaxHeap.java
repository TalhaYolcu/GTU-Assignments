package yyolcu2018;
import java.util.*;

/**
 * Class that represents a max heap implemented as Priority Queue, contains ArrayList to hold data
 * @param <E> Generic parameter
 */
public class TMaxHeap<E extends Comparable<E>> extends AbstractQueue<E> implements Queue<E>, Comparable<TMaxHeap<E>> {
    /**
     * ArrayList that holds values
     */
    private ArrayList<Values<E>> data;
    /**
     * represnts the maximum item that heap can contain
     */
    private static final int max_number_of_element=7;

    /**
     * Simple no parameter constructor, initializes the ArrayList
     */
    public TMaxHeap() {
        data=new ArrayList<>();
    }

    /**
     * Adds the item to the heap, checks the heap order
     * @param e Item that will be added
     * @return if it is added successfully return true
     */
    @Override
    public boolean offer(E e) {
        /*
        If this heap is full, return false
        If item is null,return false
        Otherwise add the item
        Check the heap order
         */
        if(isFull()) {
            return false;
        }
        else {
            if(e==null) {
                return false;
            }
            data.add(new Values<>(e,1));
            int child=data.size()-1;
            int parent=(child-1)/2;
        /*
        We need to protect heap order property. If something is wrong, swap values.
         */
            while(child>0 && parent>=0 && data.get(parent).getValue().compareTo(data.get(child).getValue())<0) {
                swap(parent,child);
                child=parent;
                parent=(child-1)/2;
            }

            return true;
        }
    }

    /**
     * Delegated method, I did not need this method
     * @return null
     */
    @Override
    public E poll() {
        return null;
    }
    /**
     * Compares two elements
     * @param left left value
     * @param right right value
     * @return result of the comparison
     */
    private int compare(E left,E right) {
        return (left).compareTo(right);
    }
    /**
     * To fix heap order property, we need to swap parent and child
     * @param a parent value
     * @param b child value
     */
    private void swap(int a,int b) {
        Values<E> temp=data.get(a);
        data.set(a,data.get(b));
        data.set(b,temp);
    }
    /**
     * Returns size of the heap (size of the arraylist)
     * @return size of the arraylist
     */
    public int size() {
        return data.size();
    }

    /**
     * Delegated method, I did not need to use it, it returns null
     * @return null
     */
    public Iterator<E> iterator() {return null;}

    /**
     * returns an iterator of the heap
     * @return iterator
     */
    public TMaxHeapIterator iterator_2() {
        return new TMaxHeapIterator();
    }

    /**
     * Class that iterates the MaxHeap
     */
    protected class TMaxHeapIterator {
        /**
         * represent the current index
         */
        private int cursor=0;
        /**
         * represents the last returned element's index
         */
        private int lastRet=-1;

        /**
         * Check whether current value has next element
         * @return if this element has next item
         */
        public boolean hasNext() {
            return cursor!=data.size();
        }

        /**
         * Move iterator by 1
         * @return If there is next item,return it. Otherwise return null
         */
        public Values<E> next() {
            if(hasNext()) {
                lastRet=cursor;
                return data.get(cursor++);
            }
            return null;
        }
    }

    /**
     * Returns the first element of the heap without removing it
     * @return first element of the heap
     */
    public E peek() {
        return data.get(0).getValue();
    }

    /**
     * Checks the heap has this item
     * @param item item that is searched
     * @return if it is find,return true.
     */
    public boolean contains(E item) {
        /*
        If item is null,return false
        If heap is empty, return false
        If arraylist is empty, return false
        Otherwise find it
         */
        if(item==null) {
            return false;
        }
        else if(isEmpty()) {
            return false;
        }
        else if(data==null) {
            return false;
        }
        for (Values<E> val : data) {
            if(val==null) {

            }
            else if (val.getValue().equals(item)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Check whether heap contains the item, if it contains depend
     * on the situation,add or remove item
     * @param item item that will be queried
     * @param sit situation that represents increment(true) or decrement(false)
     * @return if change is done return true
     */
    public boolean contains_and_set(E item,boolean sit) {
        TMaxHeapIterator it=iterator_2();
        /*
        If item is nul return null
        If heap is empty, return null
        If arraylist is null,return null
        Otherwise find item and increment-decrement
         */
        if(item==null) {
            return false;
        }
        else if(isEmpty()) {
            return false;
        }
        else if(data==null) {
            return false;
        }
        while(it.hasNext()) {
            Values<E> x=it.next();
            if(x==null) {

            }
            else if(x.getValue().equals(item)) {
                if(sit) {
                    x.add_one();
                }
                else {
                    x.remove_one();
                }
                return true;
            }
        }
        return false;
    }

    /**
     * Compares the two heap but I did not need to use this method
     * @param o
     * @return
     */
    @Override
    public int compareTo(TMaxHeap<E> o) {
        return 0;
    }

    /**
     * Returns the string representation of the heap's elements
     * @return string representation of the heap's elements
     */
    public String toString() {
        StringBuilder str=new StringBuilder();
        str.append("[");
        for(Values<E> val:data) {
            str.append(" ");
            str.append(val);
        }
        str.append("]");
        return str.toString();
    }

    /**
     * Gives the occurrence of the specified item
     * @param val item
     * @return occurrence of the item
     */
    public int give_occurence(E val) {
        /*
        If item is null,return 0
        If heap is empty,return null
        If arraylist is empty, return null
        Otherwise find item and return occurence
         */
        if(val==null) {
            return 0;
        }
        else if(isEmpty()) {
            return 0;
        }
        else if(data==null) {
            return 0;
        }
        int counter=0;
        for (Values<E> temp:data) {
            if (temp==null) {

            }
            else if(temp.getValue().equals(val)) {
                counter=temp.getOccurence();
                break;
            }
        }
        return counter;
    }

    /**
     * Does heap have 7 elements
     * @return
     */
    public boolean isFull() {
        return size()==max_number_of_element;
    }

    /**
     * Return the root value
     * @return root value
     */
    public E get_root_val() {
        return data.get(0).getValue();
    }

    /**
     * Returns the mode of the heap
     * @return mode of the heap
     */
    public Values<E> give_mode() {
        /*
        Find the item that have the highest occurrence
         */
        int index=0;
        int max=-1;
        int i=0;

        if(isEmpty()) {
            return null;
        }
        for(Values<E> values:data) {
            if(values.getOccurence()>max) {
                max=values.getOccurence();
                index=i;
            }
            i++;
        }
        return data.get(index);
    }

    /**
     * return the root
     * @return root
     */
    public Values<E> get_root() {
        if(isEmpty()) {
            return null;
        }
        return data.get(0);
    }

    /**
     * Set the value, check heap order
     * @param index index of the item
     * @param val item
     * @throws IndexOutOfBoundsException if index is wrong
     */
    public void set(int index,Values<E> val) throws IndexOutOfBoundsException{
        if(index<0 || index>=size()) {
            throw new IndexOutOfBoundsException();
        }
        data.set(index,val);
        check_for_heap_order(0);
    }

    /**
     * return the index of the item
     * @param item item that will be looked for
     * @return index of the item
     * @throws NullPointerException if something is null,it will be thrown
     */
    public int indexOf(E item) throws NullPointerException {
        if(item==null) {
            throw new NullPointerException();
        }
        else if(isEmpty()) {
            throw new NullPointerException();
        }
        int i=0;
        for (Values<E> val:data) {
            if(val.getValue().equals(item)) {
                break;
            }
            i++;
        }
        return i;
    }

    /**
     * Return the minimum of the heap
     * @return minimum of the heap
     */
    public Values<E> get_min() {

        if(isEmpty()) {
            return null;
        }
        Values<E> temp=new Values<E>(data.get(0).getValue(),0);
        for (Values<E> val:data) {
            if(val.getValue().compareTo(temp.getValue())<0) {
                temp=val;
            }
        }
        return temp;
    }

    /**
     * Checks the heap order
     * @param index arraylist's index
     */
    private void check_for_heap_order(int index) {
        /*
         * Check parent
         */
        if(isEmpty()) {
            return;
        }
        else if(data==null) {
            return;
        }
        if((index-1)/2>=0) {
            if(data.get((index-1)/2).getValue().compareTo(data.get(index).getValue())<0) {
                swap((index-1)/2,index);
                check_for_heap_order(index);
            }
        }
        /*
         * Check child -> leftchild -> 2*i+1 rightchild -> 2*i+2
         */
        else if(2*index+1>=size()) {
            if(2*index+2<size()) {
                if(data.get(index).getValue().compareTo(data.get(2*index+2).getValue())<0) {
                    swap(index,2*index+2);
                    check_for_heap_order(index);
                }
            }
        }
        else {
            if(2*index+2>=size()) {
                if(data.get(index).getValue().compareTo(data.get(2*index+1).getValue())<0) {
                    swap(index,2*index+1);
                    check_for_heap_order(index);
                }
            }
            else {
                if(data.get(index).getValue().compareTo(data.get(2*index+1).getValue())<0) {
                    swap(index,2*index+1);
                    check_for_heap_order(index);
                }
                if(data.get(index).getValue().compareTo(data.get(2*index+2).getValue())<0) {
                    swap(index,2*index+2);
                    check_for_heap_order(index);
                }
            }
        }
    }

    /**
     * Removes the item from the heap, checks the heap order
     * @param item item that will be removed
     */
    public void remove_h(E item) {
        if(isEmpty()) {
            return;
        }
        data.remove(indexOf(item));
        check_for_heap_order(0);
    }
}

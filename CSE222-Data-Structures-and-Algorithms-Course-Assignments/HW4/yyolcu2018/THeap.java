package yyolcu2018;
import java.lang.reflect.Array;
import java.util.*;

/**
 * Class that represents a heap implemented as Priority Queue, contains ArrayList to hold data
 * @param <E> Generic parameter
 */
public class THeap<E extends Comparable<E>> extends AbstractQueue<E> implements Queue<E>,Iterable<E> {
    /**
     * ArrayList that holds values
     */
    private ArrayList<E> data;

    /**
     * Simple no parameter constructor, initializes the ArrayList
     */
    public THeap() {
        data=new ArrayList<>();
    }

    /**
     * Simple one parameter constructor that takes capacity as integer, Sets up the arraylist
     * @param cap capacity value for arraylist
     * @throws IllegalArgumentException if capacity is less than 1
     */
    public THeap(int cap) throws IllegalArgumentException{
        if(cap<1) {
            throw new IllegalArgumentException();
        }
        data=new ArrayList<>(cap+1);
    }

    /**
     * adds an element to the heap,keeps the heap order property
     * @param item value that will be added
     * @return Is insertion  successful
     */
    public boolean offer(E item) {
        if(item==null) {
            return false;
        }
        data.add(item);
        int child=data.size()-1;
        int parent=(child-1)/2;
        /*
        We need to protect heap order property. If something is wrong, swap values.
         */
        while(child>0 && parent>=0 && data.get(parent).compareTo(data.get(child))>0) {
            swap(parent,child);
            child=parent;
            parent=(child-1)/2;
        }
        return true;
    }

    /**
     * removes the root, keeps the heap order property
     * @return removed element will be returned
     */
    public E poll() {
        if(isEmpty()) {
            return null;
        }
        E result=data.get(0);
        if(data.size()==1) {
            data.remove(0);
            return result;
        }
        /*
        After removal, heap order property should be protected.
         */
        data.set(0,data.remove(data.size()-1));
        int parent=0;
        while(true) {
            int leftchild=2*parent+1;
            if(leftchild>=data.size()) {
                break;
            }
            int rightchild=leftchild+1;
            int minchild=leftchild;
            if(rightchild<data.size() && compare(data.get(leftchild),data.get(rightchild))>0) {
                minchild=rightchild;
            }
            if(compare(data.get(parent),data.get(minchild))>0) {
                swap(parent,minchild);
                parent=minchild;
            }
            else {
                break;
            }
        }
        return result;
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
        E temp=data.get(a);
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
     * Returns the iterator of the THeap class
     * @return Iterator of THeap class
     */
    public THeapIterator iterator() {
        return new THeapIterator();
    }

    /**
     * Returns the first element of the heap without removing it
     * @return first element of the heap
     */
    public E peek() {
        return data.get(0);
    }

    /**
     * Searching for an element
     * @param item Item that will be searched
     * @return if item is found, it will be returned, otherwise null will be returned
     */
    public E find(E item) {
        for (E val : data) {
            if (val.equals(item)) {
                return val;
            }
        }
        return null;
    }

    /**
     * Merges two Heaps
     * @param other Other heap that will be merged
     */
    public void merge(THeap<E> other) {
        /*
         * Merge two heaps
         */
        for(E val:other.data) {
            offer(val);
        }
    }

    /**
     * Removes the ith_largest element of the heap,keeps heap order property
     * @param index index of the largest
     * @return If removal is successful, return true
     * @throws IndexOutOfBoundsException If index is less than 1 or more than size
     * @throws NullPointerException If heap is empty
     */
    @SuppressWarnings("unchecked")
    public boolean remove_ith(int index) throws IndexOutOfBoundsException,NullPointerException{

        /*
        If index is less than 1 or greater than size
         */
        if(index<1 || index>=size()) {
            throw new IndexOutOfBoundsException();
        }
        else if(data == null || data.size()==0) {
            throw new NullPointerException();
        }
        /*
         * find the value
         */
        E value=find_ith(index);
        /*
        If it is root
         */
        if(value.equals(data.get(0))) {
            poll();
            return true;
        }
        /*
         * Until it is find in the heap, remove all elements,then add them again without wanted value
         */
        E[] temp=(E[])Array.newInstance(data.get(0).getClass(),size());
        int i=0;
        while(!value.equals(data.get(0))) {
            temp[i]=poll();
            i++;
        }
        poll();

        if(data.size()==0) {
            data=null;
            data=new ArrayList<>();
        }
        else {
            ArrayList<E> arr = new ArrayList<>(data);
            data=null;
            data=new ArrayList<>();
            for (E e : arr) {
                offer(e);
            }
        }
        for (E e : temp) {
            offer(e);
        }
        return true;
    }

    /**
     * Finds ith_largest element of the heap
     * @param index index of the largest
     * @return ith largest element of the heap
     */
    @SuppressWarnings("unchecked")
    private E find_ith(int index) {
        /*
         * Sort the arraylist,return value
         */
        ArrayList<E> hold=(ArrayList<E>) data.clone();
        hold.sort(Comparable::compareTo);
        return hold.get(size()-index);
    }

    /**
     * Simple Iterator class for THeap class
     */
    public class THeapIterator implements Iterator<E> {
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
        @Override
        public boolean hasNext() {
            return cursor!=data.size();
        }

        /**
         * Move iterator by 1
         * @return If there is next item,return it. Otherwise return null
         */
        @Override
        public E next() {
            if(hasNext()) {
                lastRet=cursor;
                return data.get(cursor++);
            }
            return null;
        }

        /**
         * Set the last Returned item, to be able to call this function, iterator should have been moved at least 1 time
         * @param item last returned item
         * @return return the new Item
         */
        public E set(E item) throws IllegalArgumentException{
            if(cursor==0 || lastRet<0) {
                throw new IllegalArgumentException();
            }
            if(item==null) {
                return null;
            }
            data.set(lastRet,item);
            check_for_heap_order(lastRet);
            return THeap.this.data.get(cursor);
        }
    }

    /**
     * Simple toString method to print values
     * @return value of the heap
     */
    public String toString() {
        StringBuilder str=new StringBuilder();
        str.append("[");
        for(E val:data) {
            str.append(" ");
            str.append(val);
        }
        str.append("]");
        return str.toString();
    }

    /**
     * After setting, we need to keep heap order property.We check the parent and children of the current element.
     * @param index current element
     */
    private void check_for_heap_order(int index) {
        /*
         * Check parent
         */
        if((index-1)/2>=0) {
            if(data.get((index-1)/2).compareTo(data.get(index))>0) {
                swap((index-1)/2,index);
                check_for_heap_order(index);
            }
        }
        /*
         * Check child -> leftchild -> 2*i+1 rightchild -> 2*i+2
         */
        if(2*index+1>=size()) {
            if(2*index+2<size()) {
                if(data.get(index).compareTo(data.get(2*index+2))>0) {
                    swap(index,2*index+2);
                    check_for_heap_order(index);
                }
            }
        }
        else {
            if(2*index+2>=size()) {
                if(data.get(index).compareTo(data.get(2*index+1))>0) {
                    swap(index,2*index+1);
                    check_for_heap_order(index);
                }
            }
            else {
                if(data.get(index).compareTo(data.get(2*index+1))>0) {
                    swap(index,2*index+1);
                    check_for_heap_order(index);
                }
                if(data.get(index).compareTo(data.get(2*index+2))>0) {
                    swap(index,2*index+2);
                    check_for_heap_order(index);
                }
            }
        }
    }
}

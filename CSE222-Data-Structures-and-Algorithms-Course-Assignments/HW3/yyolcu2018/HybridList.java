package yyolcu2018;

import yyolcu2018.TArrayList;
import yyolcu2018.TLinkedList;

import java.util.ConcurrentModificationException;
import java.util.NoSuchElementException;


/*
The number of elements in each ArrayList should be less than MAX_NUMBER.
When the number of elements in an ArrayList exceeds MAX_NUMBER a new ArrayList should be generated in the LinkedList.
When there is no element in an ArrayList it should be removed from the LinkedList.
*/

/**
 * HybridList class that holds LinkedList
 * In LinkedList's each Node, there is an ArrayList
 * ArrayList holds data with typed E
 * @param <E> type that will be held by ArrayList
 */
public class HybridList<E> {
    /**
     * LinkedList that holds ArrayList
     */
    private TLinkedList<TArrayList<E>> storage;
    /**
     * Maximum value of the ArrayList capacity
     */
    private static final int MAXVALUE=10;

    /**
     * Simple no parameter constructor
     */
    public HybridList() {
        this(5);
    }

    /**
     * Simple constructor
     * @param init initial capacity of the ArrayLists
     */
    public HybridList(int init) {
        storage=new TLinkedList<>();
        storage.add(new TArrayList<E>(init));
        storage.add(new TArrayList<E>(init));
    }

    /**
     * adds a new data to the storage, controls the Maximum value
     * @param e element that will be added
     */
    public void add(E e) {
        int i=0;
        while(i<storage.size()) {
            if(storage.get(i).size()<MAXVALUE) {
                storage.get(i).add(e);
                return;
            }
        }
        storage.add(new TArrayList<>());
        storage.get(storage.size()-1).add(e);
    }

    /**
     * Overridden clone method
     * @return returns the clone of hybridlist
     * @throws CloneNotSupportedException if something is wrong
     */
    @SuppressWarnings("unchecked")
    protected Object clone() throws CloneNotSupportedException {
        try {
            super.clone();
            HybridList<E> tmp=new HybridList<>();
            tmp.storage=(TLinkedList<TArrayList<E>>) storage.clone();
            return (Object) tmp;
        }
        catch (CloneNotSupportedException ne) {
            throw ne;
        }
    }

    /**
     * Return a string which gives information about whole HybridList
     * @return information about storage
     */
    public String toString() {
        StringBuilder str=new StringBuilder();
        for(int i=0;i<storage.size();i++) {
            str.append(storage.get(i).toString());
        }
        return str.toString();
    }

    /**
     * Removes the given element
     * @param e element that will be removed
     */
    public void remove(E e) {
        for(int i=0;i<storage.size();i++) {
            for(int k=0;k<storage.get(i).size();k++) {
                if(storage.get(i).get(k).equals(e)) {
                    storage.get(i).remove(k);
                }
            }
        }
    }

    /**
     * change the number of stock of the element
     * @param e element
     * @param number stock
     */
    public void change_the_stock(E e,int number) {
        for(int i=0;i<storage.size();i++) {
            for(int k=0;k<storage.get(i).size();k++) {
                if(storage.get(i).get(k).equals(e)) {
                    Product p=(Product) e;
                    p.change_the_stock(number);
                }
            }
        }
    }

    /**
     * Query for an element
     * @param e element that will be queried
     * @return stock
     */
    public int query(E e) {
        int x=0;
        for(int i=0;i<storage.size();i++) {
            for(int k=0;k<storage.get(i).size();k++) {
                if(storage.get(i).get(k).equals(e)) {
                    Product p=(Product) storage.get(i).get(k);
                    x+=p.get_stock();
                }
            }
        }
        return x;
    }

    /**
     * Returns an iterator
     * @return iterator
     */
    public TIterator<TArrayList<E>> get_iterator() {
        return storage.iterator();
    }
    public int size() {
        int x=0;
        for(int i=0;i<storage.size();i++) {
            x+=storage.get(i).size();
        }
        return x;
    }
}
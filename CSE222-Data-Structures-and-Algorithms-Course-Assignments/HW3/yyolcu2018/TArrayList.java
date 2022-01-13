package yyolcu2018;
import java.util.Arrays;
import java.util.ConcurrentModificationException;
import java.util.NoSuchElementException;

public class TArrayList<E>
        implements Cloneable
{
    private static final int INITAL_CAPACITY=10;
    private E[] data;
    private int size=0;
    private int capacity=0;

    @SuppressWarnings("unchecked")
    private void reallocate() {
        //Arrays.copyOf(data,capacity);
        capacity*=2;
        Object[] temp=(E[]) new Object[capacity];
        for(int i=0;i<capacity/2;i++) {
            temp[i]=data[i];
        }
        data=(E[]) new Object[capacity];
        for (int i=0;i<capacity/2;i++) {
            data[i]=(E)temp[i];
        }
    }
    public TArrayList() {
        this(INITAL_CAPACITY);
    }
    @SuppressWarnings("unchecked")
    public TArrayList(int initialcap) {
        if(initialcap<=0) {
            throw new NullPointerException("INITIAL CAPACITY IS WRONG");
        }
        capacity=initialcap;
        data=(E[]) new Object[capacity];
    }
    @SuppressWarnings("unchecked")
    public TArrayList(TArrayList<E> other) {
        if(other==null || other.get(0)==null) {
            throw new NullPointerException("THIS ARRAYLIST IS NULL");
        }
        capacity=other.capacity;
        data=(E[]) new Object[capacity];
        for(int i=0;i<other.size();i++) {
            this.add(other.get(i));
        }
    }
    public void add(int index,E value) throws ArrayIndexOutOfBoundsException{
        if(index<0 || index>size) {
            throw new ArrayIndexOutOfBoundsException(index);
        }
        if(size>=capacity) {
            reallocate();
        }
        for(int i=size;i>index;i--) {
            data[i]=data[i-1];
        }
        data[index]=value;
        size++;
    }
    public boolean add(E e) {
        if(size>=capacity) {
            reallocate();
        }


        data[size++]=e;
        return true;
    }
    public void clear() {
        for(int i=0;i<capacity;i++) {
            data[i]=null;
        }
        size=0;
    }
    public boolean contains(Object o) {
        for(int i=0;i<size();i++) {
            if(get(i).equals(o)) {
                return true;
            }
        }
        return false;
    }

    public E get(int index) throws ArrayIndexOutOfBoundsException{
        if(index<0 || index>size) {
            throw new ArrayIndexOutOfBoundsException(index);
        }
        return data[index];
    }
    public int indexOf(Object o) {
        for(int i=0;i<size();i++) {
            if(get(i).equals(o)) {
                return i;
            }
        }
        return -1;
    }
    public boolean isEmpty() {
        return size==0;
    }
    public int lastIndexOf(Object o) {
        for(int i=size()-1;i>=0;i--) {
            if(get(i).equals(o)) {
                return i;
            }
        }
        return -1;
    }
    public TIterator<E> iterator() {
        return new TItr();
    }
    private class TItr implements TIterator<E> {
        int cursor=0;
        int lastRet=-1;
        public boolean hasNext() {
            return cursor!=size;
        }
        @SuppressWarnings("unchecked")
        public E next() {
            if(cursor>=size()) {
                throw new NoSuchElementException();
            }

            Object[] e=TArrayList.this.data;
            if(cursor>=e.length) {
                throw new ArrayIndexOutOfBoundsException();
            }
            cursor+=1;
            lastRet=cursor-1;
            return (E) e[cursor-1];
        }
        public void remove() {
            if(lastRet<0) {
                throw new IllegalStateException();
            }
            try {
                TArrayList.this.remove((int)lastRet);
                cursor=lastRet;
                lastRet=-1;
            }
            catch(IndexOutOfBoundsException ne) {
                throw new ConcurrentModificationException();
            }
        }
    }
    public E remove(int index) throws ArrayIndexOutOfBoundsException{
        if(index<0 || index>size) {
            throw new ArrayIndexOutOfBoundsException(index);
        }
        E retv=data[index];
        for(int i=index+1;i<size;i++) {
            data[i-1]=data[i];
        }
        size--;
        return retv;
    }
    /*public boolean remove(Object o) {
        boolean flag=false;
        int i;
        for(i=0;i<size();i++) {
            if(get(i).equals(o)) {
                flag=true;
                break;
            }
        }
        if(flag) {
            for(int j=i;j<size()-1;j++) {
                set(j,get(i+1));
            }
            return true;
        }
        return false;
    }*/
    public E set(int index,E newvalue) throws ArrayIndexOutOfBoundsException{
        if(index<0 || index>size) {
            throw new ArrayIndexOutOfBoundsException(index);
        }
        E oldvalue=data[index];
        data[index]=newvalue;
        return oldvalue;
    }
    public int size() {
        return size;
    }
    public Object[] toArray() {
        return Arrays.copyOf(data, size);
    }
    @Override
    protected Object clone() throws CloneNotSupportedException {
        try {
            @SuppressWarnings("unchecked")
            TArrayList<E> v = (TArrayList<E>) super.clone();
            v.data = Arrays.copyOf(data, size);
            return v;
        } catch (CloneNotSupportedException e) {
            // this shouldn't happen, since we are Cloneable
            throw new InternalError();
        }
    }
    public String toString() {
        StringBuilder str=new StringBuilder();
        TIterator itr=iterator();
        while(itr.hasNext()) {
            str.append(itr.next()+"\n");
        }
        return str.toString();
    }
}
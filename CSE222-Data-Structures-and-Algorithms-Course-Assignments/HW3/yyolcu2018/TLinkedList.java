package yyolcu2018;
import java.util.*;
public class TLinkedList<E> implements Cloneable {
    private Node<E> head=null;
    private int size=0;
    private static class Node<E> {
        private E data;
        private Node<E> next;

        private Node(E item) {
            data=item;
            next=null;
        }
        private Node(E item,Node<E> ref) {
            data=item;
            next=ref;
        }
    }
    public boolean add(E entry) {
        add(size,entry);
        return true;
    }
    public void add(int index,E entry) {
        if(index<0 || index>size) {
            throw new IndexOutOfBoundsException(Integer.toString(index));
        }
        if(index==0) {
            addFirst(entry);
        }
        else {
            Node<E> node =getNode(index-1);
            addAfter(node, entry);
        }
    }
    private void addFirst(E item) {
        head=new Node<E>(item,head);
        size++;
    }
    public void addLast(E e) {
        add(size,e);
    }
    private void addAfter(Node<E> node,E item) {
        node.next=new Node<E>(item,node.next);
        size++;
    }
    public void clear() {
        Node<E> node=getNode(0);
        for(int i=0;i<size();i++) {
            node.data=null;
            node=node.next;
        }
    }
    protected Object clone() throws CloneNotSupportedException {
        try {
            @SuppressWarnings("unchecked")
            TLinkedList<E> v = (TLinkedList<E>) super.clone();
            v.head=new Node<E>(this.head.data);
            Node<E> temp=v.head;
            Node<E> htemp=head;
            while(temp.next!=null) {
                temp.next=new Node<E>(htemp.next.data);
                temp=temp.next;
                htemp=htemp.next;
            }
            return v;
        } catch (CloneNotSupportedException e) {
            // this shouldn't happen, since we are Cloneable
            throw new InternalError();
        }
    }
    public boolean contains(Object o) {
        if(head==null) {
            throw new NullPointerException();
        }
        Node<E> node=getNode(0);
        while(node.next!=null) {
            if(node.data.equals(o)) {
                return true;
            }
        }
        return false;
    }
    private Node<E> getNode(int index) {
        Node<E> node=head;
        for(int i=0;i<index && node!=null;i++) {
            node=node.next;
        }
        return node;
    }
    public E getFirst() {
        if(head==null) {
            throw new NullPointerException();
        }
        else {
            return head.next.data;
        }
    }
    public E getLast() {
        if(head==null) {
            throw new NullPointerException();
        }
        else {
            Node<E> node=getNode(size-1);
            return node.data;
        }
    }
    public E get(int index) throws IndexOutOfBoundsException{
        if(index<0 || index>=size) {
            throw new IndexOutOfBoundsException(Integer.toString(index));
        }
        Node<E> node=getNode(index);
        return node.data;
    }
    public int indexOf(Object o) {
        int index=0;
        Node<E> node=getNode(index);
        while(true) {
            if(node.data.equals(o)) {
                break;
            }
            else if(node==null) {
                break;
            }
            else {
                node=node.next;
                index+=1;
            }
        }
        return index;
    }
    public boolean isEmpty() {
        return size!=0;
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

            Object[] e=TLinkedList.this.toArray();
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
                TLinkedList.this.remove((int)lastRet);
                cursor=lastRet;
                lastRet=-1;
            }
            catch(IndexOutOfBoundsException ne) {
                throw new ConcurrentModificationException();
            }
        }
    }
    public int lastIndexOf(Object o) {
        int index=0;
        Node<E> node=getNode(index);
        int cnt=0;
        while(true) {
            if(index==size) {
                break;
            }
            else if(cnt==size) {
                break;
            }
            else if(node.data.equals(o)) {
                index=cnt;
            }
            else {
                node=node.next;
                cnt+=1;
            }
        }
        return index;
    }
    public E remove(int index) {
        Node<E> node=getNode(0);
        E x;
        if(index<0 || index>size) {
            throw new ArrayIndexOutOfBoundsException();
        }
        else if(index==size) {
            return removeLast();
        }
        for(int i=0;i<index-1;i++) {
            node=node.next;
        }
        x=node.next.data;
        node.next=node.next.next;
        size-=1;
        return x;
    }
    public boolean remove(Object o) {
        Node<E> node=getNode(0);
        if(node.data.equals(o)) {
            removeFirst();
        }
        while(true) {
            if(node.next.data.equals(o)) {
                break;
            }
            else if(node==null) {
                return false;
            }
            else {
                node=node.next;
            }
        }
        node.next=node.next.next;
        size-=1;
        return true;
    }
    public E remove() {
        return removeFirst();
    }
    private E removeafter(Node<E> node) {
        Node<E> temp=node.next;
        if(temp!=null) {
            node.next=temp.next;
            size--;
            return temp.data;
        }
        else {
            return null;
        }
    }
    private E removeFirst() {
        Node<E> temp=head;
        if(head!=null) {
            head=head.next;
        }
        if(temp!=null) {
            size--;
            return temp.data;
        }
        else {
            return null;
        }
    }
    private E removeLast() {
        E x;
        Node<E> node=getNode(size-1);
        x=node.next.data;
        node.next=null;
        size-=1;
        return x;
    }
    public String toString() {
        Node<E> nodeRef=getNode(0);
        StringBuilder result=new StringBuilder();
        while(nodeRef!=null) {
            result.append(nodeRef.data);
            if(nodeRef.next!=null) {
                result.append("==>");
            }
            nodeRef=nodeRef.next;
        }
        return result.toString();
    }
    public E set(int index,E entry) {
        if(index<0 || index>=size) {
            throw new IndexOutOfBoundsException(Integer.toString(index));
        }
        Node<E> node=getNode(index);
        E result=node.data;
        node.data=entry;
        return result;
    }
    public int size() {
        return size;
    }
    public Object[] toArray() {
        Object[] o=new Object[size()];
        Node<E> node=getNode(0);
        for(int i=0;i<size;i++) {
            o[i]=node.data;
            node=node.next;
        }
        return o;
    }
}
package yyolcu2018;
/**
 * Class that represents BinarySearchTree
 * @param <E> Generic Comparable Class
 */
public class BinarySearchTree<E extends Comparable<E> >
    extends BinaryTree<E>
    implements SearchTree<E>{
    /**
     * result of the add operation
     */
    protected boolean addReturn;
    /**
     * result of the remove operation
     */
    protected E deleteReturn;

    /**
     * Simple constructor
     */
    public BinarySearchTree() {
        super();
    }
    //O(logn)-O(n)

    /**
     * Finds the item in the tree
     * @param target target
     * @return item
     */
    @Override
    public E find(E target) {
        return find(root,target);
    }

    /**
     * Checks the item is in the tree
     * @param target item
     * @return if it contains, return true
     */
    public boolean contains(E target) {
        return find(target)!=null;
    }

    /**
     * Recursive find method
     * @param localRoot localroot that item is queried in
     * @param target item
     * @return item
     */
    private E find(Node<E> localRoot,E target) {
        /*
        Look local root,left and right
         */
        if(localRoot==null) {
            return null;
        }
        int compResult=target.compareTo(localRoot.data);
        if(compResult==0) {
            return localRoot.data;
        }
        else if(compResult<0){
            return find(localRoot.left, target);
        }
        else {
            return find(localRoot.right, target);
        }
    }
    //O(logn)-O(n)

    /**
     * adds the item to the tree
     * @param value item
     * @return if it addedd successfully, return true
     */
    public boolean add(E value) {
        root=add(value, root);
        return addReturn;
    }

    /**
     * Recursive add method
     * @param value item
     * @param node local root
     * @return added root
     */
    private Node<E> add(E value,Node<E> node) {
        if(node==null) {
            addReturn=true;
            return new Node<E>(value);
        }
        else if(value.compareTo(node.data)==0) {
            addReturn=false;
            return node;
        }
        else if(value.compareTo(node.data)<0) {
            node.left=add(value, node.left);
            return node;
        }
        else {
            node.right=add(value,node.right);
            return node;
        }
    }
    //O(logn)-O(n)

    /**
     * Removes the item
     * @param item item
     * @return item
     */
    public E delete(E item) {
        root=delete(item,root);
        return deleteReturn;
    }

    /**
     * recursive delete method
     * @param item item
     * @param node local root
     * @return local root
     */
    private Node<E> delete(E item,Node<E> node) {
        if(node==null) {
            deleteReturn=null;
            return node;
        }
        int compResult=item.compareTo(node.data);
        if(compResult<0) {
            node.left=delete(item, node.left);
            return node;
        }
        else if(compResult>0) {
            node.right=delete(item, node.right);
            return node;
        }
        else {
            deleteReturn=node.data;
            if(node.left==null) {
                return node.right;
            }
            else if(node.right==null) {
                return node.left;
            }
            else {
                if(node.left.right==null) {
                    node.data=node.left.data;
                    node.left=node.left.left;
                    return node;
                }
                else {
                    node.data=findLargestChild(node.left);
                    return node;
                }
            }

        }
    }

    /**
     * Returns the largest child
     * @param parent parent node
     * @return largest child's value
     */
    private E findLargestChild(Node<E> parent) {
        if(parent.right.right==null) {
            E returnValue=parent.right.data;
            parent.right=parent.right.left;
            return returnValue;
        }
        else {
            return findLargestChild(parent.right);
        }
    }

    /**
     * Removes the item
     * @param target item
     * @return if it is removed, return true
     */
    public boolean remove(E target) {
        return delete(target)!=null;
    }
}
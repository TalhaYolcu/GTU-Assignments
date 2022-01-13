package yyolcu2018;
/**
 * Binary Tree class
 * @param <E> Comparable Generic Class
 */
public class BinaryTree<E extends Comparable<E>>{
    /**
     * Root node
     */
    protected Node<E> root;
        //constant time

    /**
     * Simple constructor
     */
    public BinaryTree()  {
        root=null;
    }
        //constant time

    /**
     * Constructor takes the root as a parameter
     * @param root
     */
    protected BinaryTree(Node<E> root) {
        this.root=root;
    }
        //constant time

    /**
     * Constructor takes data, left subtree and right subtree
     * @param data data
     * @param leftTree left subtree
     * @param rightTree right subtree
     */
    public BinaryTree(E data, BinaryTree<E> leftTree,BinaryTree<E> rightTree) {
        root=new Node<E>(data);
        if(leftTree!=null) {
            root.left=leftTree.root;
        }
        else {
            root.left=null;
        }
        if(rightTree!=null) {
            root.right=rightTree.root;
        }
        else {
            root.right=null;
        }
    }
            //constant time

    /**
     * Returns left subtree
     * @return left subtree
     */
    public BinaryTree<E> getLeftBinaryTree() {
        if(root!=null && root.left!=null) {
            return new BinaryTree<>(root.left);
        }
        else {
            return null;
        }
    }
            //constant time

    /**
     * Returns right subtree
     * @return right subtree
     */
    public BinaryTree<E> getRightBinaryTree() {
        if(root!=null && root.right!=null){
            return new BinaryTree<>(root.right);
        }
        else {
            return null;
        }
    }
            //constant time

    /**
     * Return root's data
     * @return root's data
     */
    public E getData() {
        return root.data;
    }
            //constant time

    /**
     * Check whether root has child
     * @return if root has child, return false
     */
    public boolean isLeaf() {
        if(root==null) {
            return false;
        }
        return (root.left==null && root.right==null);
    }

    /**
     * String representation of the tree
     * @return String representation of the tree
     */
    public String toString() {
        StringBuilder str=new StringBuilder();
        preOrderTraverse(root, 1, str);
        return str.toString();
    }
    // T(n,h) = O(n*h) logn<=h<=n 
    //O(nlogn) or O(n^2)

    /**
     * Preorder traverse of the tree root,left,righy
     * @param node current node
     * @param depth depth of the node
     * @param sb string
     */
    private void preOrderTraverse(Node<E> node,int depth,StringBuilder sb) {
        for(int i=1;i<depth;i++) {
            sb.append(" ");
        }
        if(node==null) {
            sb.append("null\n");
        }
        else {
            sb.append(node);
            sb.append("\n");
            preOrderTraverse(node.left, depth+1, sb);
            preOrderTraverse(node.right, depth+1, sb);
        }
    }

    /**
     * Inner node class
     * @param <E> Generic Comparable Class
     */
    protected static class Node<E extends Comparable <E>> {
        /**
         * Data of the node
         */
        protected E data;
        /**
         * Right child
         */
        protected Node<E> right;
        /**
         * Left child
         */
        protected Node<E> left;

        /**
         * takes a data
         * @param data data
         */
        public Node(E data) {
            this.data=data;
            left=null;
            right=null;
        }

        /**
         * String representation of the value
         * @return String representation of the value
         */
        public String toString() {
            StringBuilder str=new StringBuilder();
            str.append(data);
            return str.toString();
        }
    }

}
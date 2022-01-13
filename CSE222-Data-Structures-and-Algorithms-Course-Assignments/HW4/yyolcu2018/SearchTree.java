package yyolcu2018;
/**
 * Search Tree interface
 * @param <E> Comparable Generic Class
 */
public interface SearchTree<E extends Comparable<E>> {
    /**
     * Adds the item to the tree
     * @param item item that will be added
     * @return if it is added successfully, return true
     */
    boolean add(E item);

    /**
     * Checks the tree have the item
     * @param target item
     * @return if it contains, return true
     */
    boolean contains(E target);

    /**
     * Find the target and return it
     * @param target target
     * @return item
     */
    E find(E target);

    /**
     * Erases the item from the tree
     * @param target item
     * @return Erased item
     */
    E delete(E target);

    /**
     * If it is removed, return true
     * @param target item
     * @return if it removed, return true
     */
    boolean remove(E target);
}
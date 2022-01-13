package yyolcu2018;

/**
 * KWHashMap interface that represents the HashMap
 * @param <K> Key
 * @param <V> Value
 */
public interface KWHashMap <K,V> {
    /**
     * Returns the value associated with key,return null if key is not present
     * @param key key
     * @return value associated with key
     */
    V get(Object key);

    /**
     *  Returns true if this table contains no key value mappings
     * @return hashmap is empty or not
     */
    boolean isEmpty();

    /**
     * Associates the specified value with the specified key. Returns the previous value.
     * @param key key
     * @param value value
     * @return if key already had value, it will be returned. Otherwise null will be returned
     */
    V put(K key,V value);

    /**
     * Removes the mapping for this key from this tabke if it is present
     * @param key key
     * @return removed value will be returned, if there is no value, null will be returned
     */
    V remove(Object key);

    /**
     * Returns the size of table
     * @return size of the table
     */
    int size();
}
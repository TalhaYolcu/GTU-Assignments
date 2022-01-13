package yyolcu2018;
import java.util.*;

/** Hash table implementation using chaining.
 *   @author Koffman and Wolfgang
 * */

public class KWHashMapChain < K, V >
        implements KWHashMap < K, V > {
    /** The table */
    private LinkedList < Entry < K, V >> [] table;

    /** The number of keys */
    private int numKeys;

    /** The capacity */
    private static final int CAPACITY = 101;

    /** The maximum load factor */
    private static final double LOAD_THRESHOLD = 3.0;

    /** Contains key-value pairs for a hash table. */
    private static class Entry < K, V > {

        /** The key */
        private K key;

        /** The value */
        private V value;

        /** Creates a new key-value pair.
         @param key The key
         @param value The value
         */
        public Entry(K key, V value) {
            this.key = key;
            this.value = value;
        }

        /** Retrieves the key.
         @return The key
         */
        public K getKey() {
            return key;
        }

        /** Retrieves the value.
         @return The value
         */
        public V getValue() {
            return value;
        }

        /** Sets the value.
         @param val The new value
         @return The old value
         */
        public V setValue(V val) {
            V oldVal = value;
            value = val;
            return oldVal;
        }
        public String toString() {
            StringBuilder str=new StringBuilder();
            str.append(key);
            return str.toString();
        }
    }

    /**
     * No parameter constructor
     */
        @SuppressWarnings("unchecked")
    public KWHashMapChain() {
        table = new LinkedList[CAPACITY];
    }

    /**
     * Constructor takes an table size as a parameter
     * @param input_size table size
     */
        @SuppressWarnings("unchecked")
    public KWHashMapChain(int input_size) {
        table = new LinkedList[input_size];
    }

    /** Method get for class HashtableChain.
     @param key The key being sought
     @return The value associated with this key if found;
     otherwise, null
     */
    public V get(Object key) {
        int index = key.hashCode() % table.length;
        if (index < 0)
            index += table.length;
        if (table[index] == null)
            return null; // key is not in the table.

        // Search the list at table[index] to find the key.
        for (Entry < K, V > nextItem : table[index]) {
            if (nextItem.key.equals(key))
                return nextItem.value;
        }

        // assert: key is not in the table.
        return null;
    }

    /** Method put for class HashtableChain.
     post: This key-value pair is inserted in the
     table and numKeys is incremented. If the key is already
     in the table, its value is changed to the argument
     value and numKeys is not changed.
     @param key The key of item being inserted
     @param value The value for this key
     @return The old value associated with this key if
     found; otherwise, null
     */
    public V put(K key, V value) {
        int index = key.hashCode() % table.length;
        if (index < 0)
            index += table.length;
        if (table[index] == null) {
            // Create a new linked list at table[index].
            table[index] = new LinkedList < Entry < K, V >> ();
        }

        // Search the list at table[index] to find the key.
        for (Entry < K, V > nextItem : table[index]) {
            // If the search is successful, replace the old value.
            if (nextItem.key.equals(key)) {
                // Replace value for this key.
                V oldVal = nextItem.value;
                nextItem.setValue(value);
                return oldVal;
            }
        }

        // assert: key is not in the table, add new item.
        table[index].addFirst(new Entry < K, V > (key, value));
        numKeys++;
        if (numKeys > (LOAD_THRESHOLD * table.length))
            rehash();
        return null;
    }

    /** Returns the number of entries in the map */
    public int size() {
        return numKeys;
    }

    /** Returns true if empty */
    public boolean isEmpty() {
        return numKeys == 0;
    }

    /**
     * removes the key from the table , if key is not in the map, returns the null
     * @param key key
     * @return returns the removed element -> null or old value
     */
    public V remove(Object key) {
        int index = key.hashCode() % table.length;
        if (index < 0)
            index += table.length;
        if (table[index] == null)
            return null; // Key not in table
        Iterator < Entry < K, V >> iter = table[index].iterator();
        while (iter.hasNext()) {
            Entry < K, V > nextItem = iter.next();
            // If the search is successful, return the value.
            if (nextItem.key.equals(key)) {
                V returnValue = nextItem.value;
                iter.remove();
                return returnValue;
            }
        }
        return null; // Key not in table
    }

    /** Expands table size when loadFactor exceeds LOAD_THRESHOLD
     post: the size of table is doubled and is an
     odd integer. Each non-deleted entry from the original
     table is reinserted into the expanded table.
     The value of numKeys is reset to the number of items
     actually inserted; numDeletes is reset to 0.
     */
    @SuppressWarnings("unchecked")
    public void rehash() {
        // Save a reference to oldTable
        LinkedList < Entry < K, V >> [] oldTable = table;
        // Double capacity of this table
        table = new LinkedList[2 * oldTable.length + 1];

        // Reinsert all items in oldTable into expanded table.
        numKeys = 0;
        for (LinkedList<Entry<K, V>> entries : oldTable) {
            if (entries != null) {
                for (Entry<K, V> nextEntry : entries) {
                    // Insert entry in expanded table
                    put(nextEntry.key, nextEntry.value);
                }
            }
        }
    }

    /**
     * returns String representation of the table
     * @return String representation of the table
     */
    public String toString() {
        StringBuilder str=new StringBuilder();
        str.append("INDEX\tVALUE\n");
        int i=0;
        for(LinkedList<Entry<K, V>> entry:table) {
            str.append(i+"\t\t"+entry+"\n");
            i++;
        }
        str.append("\n");
        return str.toString();

    }
}

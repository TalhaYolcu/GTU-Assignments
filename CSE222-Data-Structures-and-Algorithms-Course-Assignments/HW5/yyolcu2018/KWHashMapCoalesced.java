package yyolcu2018;
import java.lang.annotation.Target;

/** Hash table implementation using open addressing.
 *  @author Koffman and Wolfgang
 */

public class KWHashMapCoalesced < K, V > implements KWHashMap < K, V > {
    /**
     * table
     */
    private Entry < K, V > [] table;
    /**
     * start capacity -> 101
     */
    private static final int START_CAPACITY = 101;
    /**
     * LOAD THRESHOLD -> 0.75
     */
    private double LOAD_THRESHOLD = 0.49;
    /**
     * number of keys in the table
     */
    private int numKeys;

    /**
     * No parameter constructor
     */
        @SuppressWarnings("unchecked")
    public KWHashMapCoalesced() {
        table = new Entry[START_CAPACITY];
    }

    /**
     * Constructor takes an table size as a parameter
     * @param input_size table size
     */
        @SuppressWarnings("unchecked")
    public KWHashMapCoalesced(int input_size) {table=new Entry[input_size];}

    /** Contains key-value pairs for a hash table. */
    private static class Entry < K, V > {

        /** The key */
        private K key;

        /** The value */
        private V value;
        /** The next index*/
        private int next=-1;

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

        /**
         * returns String representation of the Entry class
         * @return String representation of the Entry class
         */
        public String toString() {
            StringBuilder str=new StringBuilder();
            str.append(key+"\t\t");
            if(next<0) {
                str.append("NULL");
            }
            else {
                str.append(next);
            }
            return str.toString();
        }
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
     * Finds the empty place for key
     * @param key element that searching an empty place for
     * @param index start index
     * @return empty index
     */
    private int find_quadratic(Object key,int index) {
        int next=index;
        int i=0;
        while (table[index] != null && !table[index].equals(key)) {
            index=(key.hashCode()%table.length)+(int)Math.pow(i+1,2);
            if(index>=table.length) {
                index%=table.length;
            }
            while(index<0) {
                index+=table.length;
            }
            i+=1;
        }
        table[next].next=index;
        return index;
    }

    /**
     * Checks whether does table contains this element
     * @param key searched key
     * @return true if contains
     */
    public boolean contains(Object key) {
        for(Entry<K,V> entry:table) {
            if(entry!=null && entry.key.equals(key)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Determines the where the key should be placed
     * @param key placed key
     * @return index
     */
    private int find(Object key) {
        int index=key.hashCode()%table.length;
        if(index<0) {
            index+=table.length;
        }
        while ( (table[index] != null) && (!key.equals(table[index].key))) {
            if(table[index].next<0) {
                index=find_quadratic(key,index);
            }
            else {
                index=table[index].next;
            }
        }
        return index;
    }

    /**
     * returns the value of the key
     * @param key key
     * @return value
     */
    public V get(Object key) {
        int index=find(key);
        if(table[index]!=null) {
            return table[index].value;
        }
        return null;
    }

    /**
     * Puts the key and value proper place
     * @param key key
     * @param value value
     * @return old value, null or old value
     */
    public V put(K key, V value) {
        int index=find(key);
        if(table[index]==null) {
            table[index]=new Entry<>(key,value);
            numKeys++;
            double loadFactor=(double)(numKeys)/table.length;
            if(loadFactor>LOAD_THRESHOLD) {
                rehash();
            }
            return null;
        }
        V oldVal=table[index].value;
        table[index].value=value;
        return oldVal;
    }

    /**
     * Recreates the table
     */
        @SuppressWarnings("unchecked")
    private void rehash() {
        Entry<K,V> [] oldTable=table;
        table=new Entry[2*oldTable.length+1];
        numKeys=0;
        for(int i=0;i<oldTable.length;i++) {
            if ( (oldTable[i] != null)) {
                // Insert entry in expanded table
                put(oldTable[i].key, oldTable[i].value);
            }
        }
    }

    /**
     * Removes the key value pair from the table
     * @param key key
     * @return removed value or null
     */
    public V remove(Object key) {
        int index=find(key);
        if(table[index]==null) {
            return null;
        }
        V oldValue=table[index].value;
        if(table[index].next>=0) {
            if(table[table[index].next]==null) {

            }
            else {
                K key1=table[table[index].next].key;
                V val1=table[table[index].next].value;
                if(key1==null || val1==null) {

                }
                else {
                    Entry<K,V> entry=new Entry<>(table[table[index].next].key,table[table[index].next].value);
                    if(table[table[index].next].next<0) {
                        if(table[table[index].next].key==null) {

                        }
                        else {
                            remove(table[table[index].next].key);
                        }

                        table[index]=entry;
                        table[index].next=-1;
                    }
                    else {
                        if(table[table[index].next].key==null) {

                        }
                        else {
                            remove(table[table[index].next].key);
                        }
                        table[index].key=entry.key;
                        table[index].value=entry.value;
                    }
                }
            }


        }
        else {
            numKeys--;
        }

        for(Entry<K,V> entry:table) {
            if(entry!=null && entry.next>=0 && table[entry.next]==null) {
                entry.next=-1;
            }
        }

        return oldValue;
    }

    /**
     * returns String representation of the String
     * @return String representation of the String
     */
    public String toString() {
        StringBuilder str=new StringBuilder();
        str.append("INDEX\tVALUE\tNEXT\n");
        int i=0;
        for(Entry entry:table) {
            str.append(i+"\t\t"+entry+"\n");
            i++;
        }
        str.append("\n");
        return str.toString();

    }
}














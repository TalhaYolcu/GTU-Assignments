package yyolcu2018;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Set;

/**
 * Helper class that ensures the reach the HashMap's elements
 * @param <K> Key
 * @param <V> Value
 */
public class MyHashMap<K, V> extends HashMap<K,V> implements Iterable<K> , KWHashMap<K,V> {
    /**
     * No parameter iterator method that returns the MapIterator that starts from 0th index
     * @return MapIterator that starts from 0th index
     * @throws NullPointerException when HashMap is empty
     */
    public MapIterator<K> iterator() {
        if(isEmpty()) {
            throw new NullPointerException("This map is empty");
        }
        return new MapIterator<>();
    }

    /**
     * Key parameter iterator method that returns the MapIterator that starts from the given key
     * @param key start key
     * @return MapIterator that starts from given key
     * @throws NullPointerException when HashMap is empty
     */
    public MapIterator<K> iterator(K key) {
        if(isEmpty()) {
            throw new NullPointerException("This Map is empty");
        }
        return new MapIterator<>(key);
    }

    /**
     * Inner MapIterator class that represents iterator for HashMap
     * @param <K> Key
     */
    public class MapIterator <K> implements Iterator<K> {
        /**
         * values to iterate through
         */
        private K[] kSet;
        /**
         * cursor
         */
        private int cur=-1;
        /**
         * last key returned
         */
        private K lastItemreturned=null;
        /**
         * represents the iterated elements
         */
        private boolean[] iterated;

        /**
         * no parameter constructor that starts the iterator from 0th index
         */
        public MapIterator(){
            try {
                check_for_empty();
                iterated=new boolean[kSet.length];
            }
            catch (NullPointerException ne) {
                System.out.println("This map is empty");
            }
        }

        /**
         * key parameter constructor that starts the iterator from given key
         * @param key start key
         */
        public MapIterator(K key){
            try {
                check_for_empty();

            }
            catch (NullPointerException ne) {
                System.out.println("This map is empty");
            }
            int i=0;
            /*
            If map contains the given key, it starts from the given index
            Otherwise it stars from the 0th index
             */
            if(containsKey(key)) {
                /*
                Go to the given key
                 */
                for(K key_temp:kSet) {
                    if(key_temp.equals(key)) {
                        break;
                    }
                    i++;
                }
                /*
                Adjust iterator fields
                 */
                iterated=new boolean[kSet.length];
                cur+=i;
                lastItemreturned=kSet[cur];
            }
        }

        /**
         * It checks the map is empty or not, if it is empty it throws exception. Otherwise it initializes the array to iterate through
         * @throws NullPointerException if the map is empty or null, it will be thrown
         */
        @SuppressWarnings("unchecked")
        private void check_for_empty() throws NullPointerException{
            if(MyHashMap.super.isEmpty()) {
                throw new NullPointerException();
            }
            Set<K> temp_set= (Set<K>) keySet();
            if(temp_set.isEmpty()) {
                throw new NullPointerException();
            }
            kSet = (K[])temp_set.toArray();
        }

        /**
         * Checks whether all elements are iterated or not
         * @return if all elements are iterated, return false otherwise return true
         */
        public boolean hasNext() {
            for (boolean b : iterated) {
                if (!b) {
                    return true;
                }
            }
            return false;
        }

        /**
         * Returns the next key
         * @return there exists next key, return it, otherwise return null
         */
        public K next() {
            if(!hasNext()) {
                return kSet[0];
            }
            if(cur>=kSet.length-1) {
                cur=-1;
            }
            iterated[cur+1]=true;
            lastItemreturned=kSet[++cur];
            return lastItemreturned;
        }

        /**
         * Returns the previous key
         * @return if there exists previous key, return it otherwise return null
         */
        public K prev() {
            if(cur==-1) {
                cur=kSet.length-1;
            }
            iterated[cur]=true;
            lastItemreturned=kSet[cur--];
            return lastItemreturned;
        }
    }
}

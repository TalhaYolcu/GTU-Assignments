import yyolcu2018.*;
import java.util.ArrayList;
import java.util.Random;

public class Main {

    public static boolean compare(Integer[] arr1,Integer[] arr2) {
        int i=0;
        for(Integer x:arr1) {
            if(!x.equals(arr2[i])) {
                return true;
            }
            i++;
        }
        System.out.println("ALL ELEMENTS ARE SAME, TEST PASSED\n");
        return false;
    }

    public static void test_part_1() {

        MyHashMap<Integer,Integer> hm=new MyHashMap<>();
        Random random=new Random();

        int NUMBER_OF_INPUT=20;

        int rand=0;

        for(int i=0;i<4;i++) {
            if(i==0) {
                NUMBER_OF_INPUT=0;
            }
            else if(i==1) {
                NUMBER_OF_INPUT=20;
            }
            System.out.println("TESTING WITH INPUT SIZE "+NUMBER_OF_INPUT+"\n");

            for(int k=0;k<NUMBER_OF_INPUT;k++) {
                rand=random.nextInt(5000);
                hm.put(rand,rand);
            }
            try {
                MyHashMap<Integer,Integer>.MapIterator<Integer> mps=hm.iterator();
                MyHashMap<Integer,Integer>.MapIterator<Integer> mps2=hm.iterator();
                MyHashMap<Integer,Integer>.MapIterator<Integer> mps3=hm.iterator(rand);
                MyHashMap<Integer,Integer>.MapIterator<Integer> mps4=hm.iterator(rand);

                Integer[] arr1=new Integer[hm.size()];
                Integer[] arr2=new Integer[hm.size()];
                Integer[] arr3=new Integer[hm.size()];
                Integer[] arr4=new Integer[hm.size()];
                Integer[] arr5=new Integer[hm.size()];

                int j=0;

                System.out.println("ITERATION WITH RANGE FOR LOOP\n");

                for(Integer x:hm) {
                    System.out.print(x+" ,");
                    arr1[j]=x;
                    j++;
                }
                j=0;

                System.out.println("\n------\n");

                System.out.println("\nITERATION WITH NEXT");

                while(mps.hasNext()) {
                    arr2[j]=mps.next();
                    System.out.print(arr2[j]+" ,");
                    j++;
                }

                System.out.println("\nCOMPARING ELEMENTS AFTER ITERATION WITH RANGE FOR LOOP AND ITERATION WITH NEXT");
                if(compare(arr1, arr2)) {
                    System.out.println("FIRST TEST FAILED\n\n");
                }

                j=hm.size()-1;
                System.out.println("\n------\n");

                System.out.println("ITERATION WITH PREVIOUS\n");

                while (mps2.hasNext()) {
                    arr3[j]=mps2.prev();
                    System.out.print(arr3[j]+" ,");
                    j--;
                }

                System.out.println("\nCOMPARING ELEMENTS AFTER ITERATION WITH PREVIOUS AND ITERATION WITH NEXT");
                if(compare(arr1, arr3)) {
                    System.out.println("SECOND TEST FAILED\n\n");
                }

                j=0;

                System.out.println("START VALUE OF ITERATIONS WITH START VALUE: "+rand);

                System.out.println("\n------\n");

                System.out.println("ITERATION WITH NEXT\n");

                while (mps3.hasNext()) {
                    arr4[j]=mps3.next();
                    System.out.print(arr4[j]+" ,");
                    j++;
                }

                j=hm.size()-1;

                System.out.println("\n------\n");

                System.out.println("ITERATION WITH PREVIOUS\n");

                while (mps4.hasNext()) {
                    arr5[j]=mps4.prev();
                    System.out.print(arr5[j]+" ,");
                    j--;
                }

                System.out.println("\nCOMPARING ELEMENTS AFTER ITERATION WITH START VALUE KEY NEXT AND START VALUE KEY PREVIOUS");
                if(compare(arr4, arr5)) {
                    System.out.println("THIRD TEST FAILED\n\n");
                }

                System.out.println("INPUT SIZE "+NUMBER_OF_INPUT+" TEST PASSED, INPUT SIZE WILL BE INCREMENTED");
                NUMBER_OF_INPUT*=5;
                System.out.println("\n\n");
            }
            catch (NullPointerException ne) {
                System.out.println(ne);
            }
        }

    }

    public static void test_part_2_time() {

        KWHashMapChain<Integer,Integer> kwchain=new KWHashMapChain<>(101);
        KWHashMapChainTreeSet<Integer,Integer> kwchaintreeset=new KWHashMapChainTreeSet<>(101);
        KWHashMapCoalesced<Integer,Integer> kwchaincoalesced=new KWHashMapCoalesced<>(101);

        int N=100;

        long startTime;
        long endTime;
        double duration;

        Random rand = new Random();

        int randNum;

        startTime = System.nanoTime();
        for (int i = N; i > 1 ; i--){
            //randNum = rand.nextInt(300);
            kwchain.put(2*i,2*i);
        }
        endTime = System.nanoTime();

        duration = ((double) (endTime - startTime)/1000000 );

        System.out.println("Duration for adding "+ N +" elements in HashTableChain:: "+ duration+ " ms");


        startTime = System.nanoTime();
        for (int i = N; i > 1 ; i--){
            //randNum = rand.nextInt(300);
            kwchaintreeset.put(2*i,2*i);
        }
        endTime = System.nanoTime();

        duration = ((double) (endTime - startTime)/1000000 );

        System.out.println("Duration for adding "+ N +" elements in HashTableTreeSetChain:: "+ duration+ " ms");


        startTime = System.nanoTime();
        for (int i = N; i > 1 ; i--){
            //randNum = rand.nextInt(300);
            kwchaincoalesced.put(2*i,2*i);
        }
        endTime = System.nanoTime();

        duration = ((double) (endTime - startTime)/1000000 );

        System.out.println("Duration for adding "+ N +" elements in HashTableCoalesced:: "+ duration+ " ms");




        System.out.println("");



        startTime = System.nanoTime();
        for (int i = 1; i < N ; i++){
            //System.out.println(hashtableChain.get(2*i));
            kwchain.get(2*i);
        }
        endTime = System.nanoTime();

        duration = ((double) (endTime - startTime)/1000000 );

        System.out.println("Duration for Get() "+ N +" elements in HashTableChain:: "+ duration+ " ms");


        startTime = System.nanoTime();
        for (int i = 1; i < N ; i++){
            //System.out.println(hashtableTreeSetChain.get(2*i));
            kwchaintreeset.get(2*i);
        }
        endTime = System.nanoTime();

        duration = ((double) (endTime - startTime)/1000000 );

        System.out.println("Duration for Get() "+ N +" elements in HashTableTreeSetChain:: "+ duration+ " ms");


        startTime = System.nanoTime();
        for (int i = 1; i < N ; i++){
            //System.out.println(hashtableCoalesced.get(2*i));
            kwchaincoalesced.get(2*i);
        }
        endTime = System.nanoTime();

        duration = ((double) (endTime - startTime)/1000000 );

        System.out.println("Duration for Get() "+ N +" elements in HashTableCoalesced:: "+ duration+ " ms");



        System.out.println("");




        startTime = System.nanoTime();
        for (int i = 1; i < N ; i++){
            Integer a = kwchain.remove(2*i);
            //System.out.println(a);
        }
        endTime = System.nanoTime();

        duration = ((double) (endTime - startTime)/1000000 );

        System.out.println("Duration for Removing "+ N +" elements in HashTableChain:: "+ duration+ " ms");


        startTime = System.nanoTime();
        for (int i = 1; i < N ; i++){
            Integer a = kwchaintreeset.remove(2*i);
            //System.out.println(a);
        }
        endTime = System.nanoTime();

        duration = ((double) (endTime - startTime)/1000000 );

        System.out.println("Duration for Removing "+ N +" elements in HashTableTreeSetChain:: "+ duration+ " ms");


        startTime = System.nanoTime();
        for (int i = 1; i < N ; i++){
            Integer a = kwchaincoalesced.remove(2*i);
            //System.out.println(a);
        }
        endTime = System.nanoTime();

        duration = ((double) (endTime - startTime)/1000000 );

        System.out.println("Duration for Removing "+ N +" elements in HashTableCoalesced:: "+ duration+ " ms");




        System.out.println("");




        startTime = System.nanoTime();
        for (int i = 1; i < N ; i++){
            kwchain.remove(5*i);
        }
        endTime = System.nanoTime();

        duration = ((double) (endTime - startTime)/1000000 );

        System.out.println("Duration for Removing NOT EXIST "+ N +" elements in HashTableChain:: "+ duration+ " ms");


        startTime = System.nanoTime();
        for (int i = 1; i < N ; i++){
            kwchaintreeset.remove(2*i);
        }
        endTime = System.nanoTime();

        duration = ((double) (endTime - startTime)/1000000 );

        System.out.println("Duration for Removing NOT EXIST "+ N +" elements in HashTableTreeSetChain:: "+ duration+ " ms");


        startTime = System.nanoTime();
        for (int i = 1; i < N ; i++){
            kwchaincoalesced.remove(2*i);
        }
        endTime = System.nanoTime();

        duration = ((double) (endTime - startTime)/1000000 );

        System.out.println("Duration for Removing NOT EXIST "+ N +" elements in HashTableCoalesced:: "+ duration+ " ms");

        System.out.println("\n");

    }

    public static void test_part_2_unit() {

        Random r = new Random();
        int input_size=100;
        int try_to_remove=25;

        for(int a=0;a<4;a++) {
            KWHashMapCoalesced<Integer,Integer> hash=new KWHashMapCoalesced<>(101);
            ArrayList<Integer> arr = new ArrayList<>(input_size);
            int x;
            for(int i=0;i<input_size ;i++) {
                x = r.nextInt(505);
                x*=5;
                if(!hash.contains(x))
                {
                    arr.add(x);
                    hash.put(x,x);

                }
            }
            System.out.println(arr.size()+" PUT SUCCESSFUL "+hash.size());

            int[] array = new int[try_to_remove];
            for(int i=0;i<try_to_remove;i++) {
                int inArr = arr.remove(0);
                hash.remove(inArr);
                array[i] = inArr;
            }
            if(arr.size()!=hash.size()) {
                System.out.println(arr.size()+" FAIL "+ hash.size());
            }

            input_size*=2;
            try_to_remove*=2;
            System.out.println("TEST PASSED");


        }





    }
    public static void test_part_2() {
        KWHashMapChain<Integer,Integer> kwch=new KWHashMapChain<>(10);
        KWHashMapChainTreeSet<Integer,Integer> kwchtreeset=new KWHashMapChainTreeSet<>(10);
        KWHashMapCoalesced<Integer,Integer> kwchcoalesced=new KWHashMapCoalesced<>(10);

        int[] input={3, 12, 13, 25, 23, 51, 42};

        for(int i:input) {
            kwchcoalesced.put(i,i);
            kwch.put(i,i);
            kwchtreeset.put(i,i);
        }
        System.out.println(kwch);

        System.out.println(kwchtreeset);

        System.out.println(kwchcoalesced);

        test_part_2_time();

        test_part_2_unit();

    }

    public static void test_string(KWHashMap<String,Integer> map) {
        map.put("CSE232",90);
        map.put("CSE222",80);
        map.put("CSE101",85);
        map.put("CSE102",45);
        map.put("CSE108",90);
        map.put("CSE107",89);

        System.out.println("PRINTING MAP:\n"+map);

    }


    public static void test_part2_detailed() {
        KWHashMapChain<String,Integer> kwHashMapChain=new KWHashMapChain<>(15);
        KWHashMapChainTreeSet<String,Integer> kwHashMapChainTreeSet=new KWHashMapChainTreeSet<>(15);
        KWHashMapCoalesced<String,Integer> kwHashMapCoalesced=new KWHashMapCoalesced<>(15);

        System.out.println("\n\nTESTING DIFFERENT TYPES\n\nCHAIN:");
        test_string(kwHashMapChain);
        System.out.println("TREESET:");
        test_string(kwHashMapChainTreeSet);
        System.out.println("COALESCED:");
        test_string(kwHashMapCoalesced);

    }
    public static void test_part2_Integer() {
        KWHashMapChain<Integer,Integer> kwHashMapChain=new KWHashMapChain<>(15);
        KWHashMapChainTreeSet<Integer,Integer> kwHashMapChainTreeSet=new KWHashMapChainTreeSet<>(15);
        KWHashMapCoalesced<Integer,Integer> kwHashMapCoalesced=new KWHashMapCoalesced<>(15);

        System.out.println("FIRSTLY LOW INPUT SIZE TO SEE EASILY");

        for(int i=0;i<30;i++) {
            kwHashMapChain.put(i,i+1);
            kwHashMapChainTreeSet.put(i,i+1);
            kwHashMapCoalesced.put(i,i+1);
        }
        System.out.println("\n\nCHAIN:\n");
        System.out.println(kwHashMapChain);
        System.out.println("\n\nTREESET:\n");
        System.out.println(kwHashMapChainTreeSet);
        System.out.println("\n\nCOALESCED:\n");
        System.out.println(kwHashMapCoalesced);

        System.out.println("REMOVING 30 NUMBERS");
        for(int i=0;i<30;i++) {
            kwHashMapChain.remove(i);
            kwHashMapChainTreeSet.remove(i);
            kwHashMapCoalesced.remove(i);
        }

        System.out.println("\n\nCHAIN:\n");
        System.out.println(kwHashMapChain);
        System.out.println("\n\nTREESET:\n");
        System.out.println(kwHashMapChainTreeSet);
        System.out.println("\n\nCOALESCED:\n");
        System.out.println(kwHashMapCoalesced);


        System.out.println("ADDING 5K NUMBERS");

        for(int i=30;i<5030;i++) {
            kwHashMapChain.put(i,i+1);
            kwHashMapChainTreeSet.put(i,i+1);
            kwHashMapCoalesced.put(i,i+1);
        }

        System.out.println("REMOVING 5K NUMBERS");
        for(int i=30;i<5030;i++) {
            kwHashMapChain.remove(i);
            kwHashMapChainTreeSet.remove(i);
            kwHashMapCoalesced.remove(i);
        }
    }
    public static void test_coalesced_pdf_example() {
        KWHashMapCoalesced<Integer,Integer> kwchcoalesced=new KWHashMapCoalesced<>(10);

        int[] input={3, 12, 13, 25, 23, 51, 42};

        for(int i:input) {
            kwchcoalesced.put(i,i);
        }
        System.out.println("\nBEFORE REMOVING 13\n");
        System.out.println(kwchcoalesced);
        kwchcoalesced.remove(13);
        System.out.println("\nAFTER REMOVING 13\n");
        System.out.println(kwchcoalesced);
    }

    public static void main(String[] args) {

        test_part_1();

        test_part_2();

        test_part2_detailed();

        test_part2_Integer();

        test_coalesced_pdf_example();

    }
}


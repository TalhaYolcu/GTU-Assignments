import java.util.*;
import yyolcu2018.*;

public class Main {

    public static void test(THeap<Integer> th) {

        System.out.println("\n\nTEST MENU FOR HEAP(INTEGER):\n");
        System.out.println(th+"\n");

        boolean flag=true;
        while(flag) {
            System.out.println("1)SEARCH FOR AN ELEMENT");
            System.out.println("2)MERGE WITH ANOTHER HEAP");
            System.out.println("3)REMOVE THE ith LARGEST ELEMENT");
            System.out.println("4)SET A VALUE");
            System.out.println("0)EXIT");
            System.out.println("Enter :");
            Scanner scan=new Scanner(System.in);
            try {
                int opt=scan.nextInt();
                switch (opt) {
                    case 0:
                        System.out.println("EXITING...");
                        flag=false;
                        break;
                    case 1:
                        System.out.println("Enter element to search");
                        int val=scan.nextInt();
                        if(th.find(val)!=null) {
                            System.out.println("Heap contains this element");
                        }
                        else {
                            System.out.println("Heap does not contain this element");
                        }
                        break;
                    case 2:
                        System.out.println("Enter elements of the new Heap, to end entering enter -1");
                        THeap<Integer> ar=new THeap<>();
                        boolean flag2=true;
                        while(flag2) {
                            int val2=scan.nextInt();
                            if(val2==-1) {
                                flag2=false;
                            }
                            else {
                                ar.offer(val2);
                            }
                        }
                        System.out.println("Before merging, first heap is :\n"+th);
                        System.out.println("\nBefore merging other heap is :\n"+ar);
                        th.merge(ar);
                        System.out.println("After merging: \n"+th);
                        break;
                    case 3:
                        System.out.println("Enter an index -starts with 1- to remove ith largest element");
                        int rem=scan.nextInt();
                        System.out.println("Before removing:\n"+th);

                        try {
                            th.remove_ith(rem);
                        }
                        catch (IndexOutOfBoundsException | NullPointerException ne) {
                            System.out.println(ne);
                        }

                        System.out.println("After removing:\n"+th);
                        break;
                    case 4:
                        System.out.println("To set a value, enter an index to make iterator next");
                        int setter=scan.nextInt();
                        THeap<Integer>.THeapIterator it=th.iterator();
                        for(int i=0;i<setter+1;i++) {
                            it.next();
                        }
                        System.out.println("Enter a new value to set");
                        int newval=scan.nextInt();
                        System.out.println("Before setting:\n"+th);
                        try {
                            it.set(newval);
                        }
                        catch (IllegalArgumentException ne) {
                            System.out.println(ne);
                        }

                        System.out.println("After setting:\n"+th);
                        break;
                    default:
                        System.out.println("Wrong input,try again");
                        break;
                }
            }
            catch (InputMismatchException ne) {
                System.out.println(ne);
            }
        }
    }
    public static void test_2_1() {
        //Creation of array
        TMaxHeap<Integer> tMaxHeap=new TMaxHeap<>();
        Random rand=new Random();
        int upper_bound=5000;
        ArrayList<Integer> arr=new ArrayList<>(3000);
        BSTHeapTree<Integer> bst=new BSTHeapTree<>(tMaxHeap);
        for(int i=0;i<3000;i++) {
            int number=rand.nextInt(upper_bound);
            arr.add(number);
            bst.add(number);
        }

        //sorting array
        arr.sort(Comparable::compareTo);

        int occur;
        boolean flag = false;
        // number of occurence check:
        for(int i = 0;i<arr.size();i++) {
            occur = 0;
            int temp = i;
            for(int x = i;x<arr.size();x++) {
                if(arr.get(x).equals(arr.get(temp))) {
                    occur++;
                }
                else {
                    break;
                }
            }
            i += occur;
            i--;
            int occurencesInTree = bst.find(arr.get(temp));

            if( occurencesInTree != occur) {
                System.out.println(occurencesInTree + " ERROR " + occur+" value: " +arr.get(temp));
            }
        }
        System.out.println("\n\n"+bst+"\n\n");
        System.out.println("Successful,going to test test2_2");
        test_2_2(arr,bst);
    }
    public static int number_of_occurence_in_array(ArrayList<Integer> arr,int z) {
        int cnt=0;
        for (Integer x:arr) {
            if(x.equals(z)) {
                cnt++;
            }
        }
        return cnt;
    }
    public static void test_2_2(ArrayList<Integer> arr,BSTHeapTree<Integer> bst) {
        int i=0;
        Random rand=new Random();
        boolean flag1=true;
        boolean flag2=true;
        while(i!=100) {
            int occurence1=0;
            int occurence2=0;
            int z=rand.nextInt(5000);
            if(arr.contains(z)) {
                occurence1=number_of_occurence_in_array(arr,z);
                occurence2=bst.find(z);
                if(occurence1!=occurence2) {
                    System.out.println("FAILED");
                    flag1=false;
                }
                i++;
            }
        }
        i=0;
        while(i!=10) {
            int z= rand.nextInt(5000);
            if(!arr.contains(z)) {
                int occurence1=0;
                int occurence2= bst.find(z);
                if(occurence1!=occurence2) {
                    System.out.println("FAILED");
                    flag2=false;
                }
                i++;
            }
        }
        if(flag1 && flag2) {
            System.out.println("\n\n"+bst+"\n\n");
            System.out.println("TEST2_2 IS SUCCESSFUL GOING TO THE TEST2_3");
            test_2_3(arr,bst);
        }
        else {
            System.out.println("FAILED");
        }
    }
    public static ArrayList<Integer> mode_of_the_array(ArrayList<Integer> arr) {
        int max=-1;
        int occur=0;
        int mod=0;
        ArrayList<Integer> ar2=new ArrayList<>();
        for (Integer i:arr) {
            occur=number_of_occurence_in_array(arr,i);
            if(max<occur) {
                mod=i;
                max=occur;
                ar2.add(mod);
            }
            else if(max==occur) {
                ar2.add(i);
            }
        }
        return ar2;
    }
    public static void test_2_3(ArrayList<Integer> arr,BSTHeapTree<Integer> bst) {
        ArrayList<Integer> z=mode_of_the_array(arr);
        int c=bst.find_mode();
        if(!z.contains(c)) {
            System.out.println("FAILED");
            System.out.println(z);
            System.out.println(c);
        }
        else {
            System.out.println("\n\n"+bst+"\n\n");
            System.out.println("TEST2_3 IS SUCCESSFUL, GOING TO THE TEST2_4");
            test_2_4(arr,bst);
        }
    }
    public static void test_2_4(ArrayList<Integer> arr,BSTHeapTree<Integer> bst) {
        Random rand=new Random();
        boolean flag1=true;
        boolean flag2=true;
        int i=0;
        while (i<100) {
            int z=rand.nextInt(5000);
            if(arr.contains(z)) {
                flag1 = isFlag1(arr, bst, flag1, z);
                i++;
            }
        }
        i=0;
        while (i<10) {
            int z=50001+rand.nextInt(5000);
            try {
                flag2 = isFlag1(arr, bst, flag2, z);
            }
            catch (Exception ex) {
                System.out.println(ex);
            }
            i++;
        }
        if(flag1 && flag2) {
            System.out.println("\n\n"+bst+"\n\n");
            System.out.println("ALL TESTS ARE PASSED");
        }
        else {
            System.out.println("TEST2_4 COULDN'T PASSED");
        }
    }
    private static boolean isFlag1(ArrayList<Integer> arr, BSTHeapTree<Integer> bst, boolean flag1, int z) {
        int occurence1;
        int occurence2;
        arr.remove((Integer) z);
        bst.remove(z);
        occurence1=number_of_occurence_in_array(arr,z);
        occurence2=bst.find(z);
        if(occurence1!=occurence2) {
            System.out.println("FAILED");
            flag1=false;
        }
        return flag1;
    }
    public static void main(String[] args) {

        THeap<Integer> th=new THeap<>();

        th.offer(5);
        th.offer(6);

        THeap<Integer> tx=new THeap<>();

        tx.offer(10);

        th.merge(tx);

        System.out.println(th);

        try {
            System.out.println(th.remove_ith(1));
        }
        catch (IndexOutOfBoundsException | NullPointerException ne) {
            System.out.println(ne);
        }


        System.out.println(th);

        th.offer(10);
        System.out.println(th);
        System.out.println();

        System.out.println(th.find(5));


        th.offer(50);
        th.offer(55);
        th.offer(85);

        THeap<Integer>.THeapIterator it=  th.iterator();
        System.out.println(th);
        it.next();
        it.next();

        try {
            it.set(60);
        }
        catch (IllegalArgumentException ne) {
            System.out.println(ne);
        }
        System.out.println(th);

        test(th);

        System.out.println("After testing PART 1 , we are gonna test part 2 now.");

        TMaxHeap<Integer> tMaxHeap=new TMaxHeap<>();
        tMaxHeap.offer(37);
        tMaxHeap.offer(23);
        tMaxHeap.offer(10);
        System.out.println(tMaxHeap);


        BSTHeapTree<Integer> bst_heap=new BSTHeapTree<>(tMaxHeap);

        bst_heap.add_new_value(16);
        bst_heap.add_new_value(19);
        bst_heap.add_new_value(9);
        bst_heap.add_new_value(3);
        bst_heap.add_new_value(31);
        bst_heap.add_new_value(124);
        bst_heap.add_new_value(15);
        bst_heap.add_new_value(29);
        bst_heap.add_new_value(52);
        bst_heap.add_new_value(98);
        bst_heap.add_new_value(13);
        bst_heap.add_new_value(51);
        bst_heap.add_new_value(38);
        bst_heap.add_new_value(87);
        bst_heap.add_new_value(80);
        bst_heap.add_new_value(60);
        bst_heap.add_new_value(57);
        bst_heap.add_new_value(43);
        bst_heap.add_new_value(54);
        bst_heap.add_new_value(39);

        System.out.println(bst_heap);
        bst_heap.remove(39);
        bst_heap.remove(39);



        //System.out.println(tMaxHeap);
        System.out.println(bst_heap);
        System.out.println("\n\nPart 1 is successfull. Going to the PART2");

        test_2_1();

    }
}

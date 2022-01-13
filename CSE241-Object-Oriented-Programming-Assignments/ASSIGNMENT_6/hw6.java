/**
*This class represents the Test of the JAVA Collection Classes
*/
import java.util.Scanner;

import yyolcu2018_1801042609.Iterator;
import yyolcu2018_1801042609.Itr;
import yyolcu2018_1801042609.Collection;
import yyolcu2018_1801042609.Set;
import yyolcu2018_1801042609.Queue;
import yyolcu2018_1801042609.HashSet;
import yyolcu2018_1801042609.Duplicated;
import yyolcu2018_1801042609.List;
import yyolcu2018_1801042609.ArrayList;
import yyolcu2018_1801042609.LinkedList;
import yyolcu2018_1801042609.QueueException;
import yyolcu2018_1801042609.NoElementException;
import yyolcu2018_1801042609.OutoftherangeException;

import static java.lang.System.out;

public class hw6{
    @Deprecated
	@SuppressWarnings("unchecked")
    public static void main(String[] args) {
       out.print("\nMENU FOR TESTING\n");
       Scanner get=new Scanner(System.in);
       Integer option=new Integer(5);

      HashSet<Integer> h1=new HashSet<>();
      HashSet<String> h2=new HashSet<>();
      ArrayList<Integer> a1=new ArrayList<>();
      ArrayList<String> a2=new ArrayList<>();
      LinkedList<Integer> l1=new LinkedList<>();
      LinkedList<String> l2=new LinkedList<>();

       while(option!=0) {
       		out.println("(1) HashSet Integer");
       		out.println("(2) ArrayList Integer");
       		out.println("(3) LinkedList Integer");
       		out.println("(4) HashSet String");
       		out.println("(5) ArrayList String");
       		out.println("(6) LinkedList String");
       		out.println("(0) QUIT");
       		out.println("Waiting for command:");
       		option=get.nextInt();

       		switch(option) {
       			case 1:
       			testint(h1);
       			break;

       			case 2:
       			testint(a1);
       			break;

       			case 3:
       			testint(l1);
       			break;

       			case 4:
       			teststr(h2);
       			break;

       			case 5:
       			teststr(a2);
       			break;

       			case 6:
       			teststr(l2);
       			break;

            case 0:
            out.println("QUTTING...");
            break;

       			default:
       			out.println("WRONG OPTION TRY AGAIN...");
       			break;
       		}
       }

    }
@Deprecated
	@SuppressWarnings("unchecked")
    public static void testint(Collection<Integer> c1) {
        try {
          c1.add(4);
          c1.add(5);
          c1.add(5);
        }
        catch(Duplicated ne) {
          System.err.println("Exception occured: "+ne);
        }
        HashSet<Integer> temp=new HashSet<>();
        HashSet<Integer> temp2=new HashSet<>();
        
        try {
          temp.add(8);
          temp.add(9);

          temp2.add(1);
          temp2.add(2);
          temp2.add(3);
          temp2.add(4);          
        }
        catch(Duplicated ne) {
          System.err.println("Exception occured: "+ne);
        }
        c1.addAll(temp);
        out.println(c1);

        out.println("IS C1 EMPTY?\n"+c1.isEmpty());
        out.println("DOES C1 CONTAINS 2");
        out.println(c1.contains(2));
        
        out.println("DOES C1 CONTAINS 4");
        out.println(c1.contains(4));

        out.println("DOES C1 CONTAINS ALL OF THE 1 2 3 4");
        out.println(c1.containsAll(temp2));

        c1.remove(4);
        out.println("DOES C1 CONTAINS 4");
        out.println(c1.contains(4));   
        
        out.println("BEFORE REMOVE ALL C1 IS:");
        out.print(c1);
        c1.removeAll(temp);
        out.print("AFTER REMOVE ALL C1 IS:");
        out.print(c1);     

        try {
          c1.add(8);
          c1.add(9);
        }     
        catch(Duplicated ne) {
          System.err.println("Exception occured: "+ne);
        }
        out.println("SIZE:"+c1.size());
        out.println(temp);

        out.println("BEFORE RETAIN ALL C1 IS:");
        out.print(c1);
        c1.retainAll(temp);   
        out.print("AFTER RETAIN ALL C1 IS:");
        out.print(c1); 

        c1.clear();
        out.print(c1);
        out.println("IS C1 EMPTY?\n"+c1.isEmpty());          

      ArrayList<Integer> ai1=new ArrayList();
      try {
        Iterator<Integer> it=c1.iterator();
        it.remove();
      }
      catch(NoElementException ne) {
        System.err.println("Exception occured: "+ne);
      }
      catch(QueueException ne) {
        System.err.println("Exception occured: "+ne);
      }

      try {

        ai1.add(5);
        ai1.get(2);
      }
      catch(OutoftherangeException ne) {
        System.err.println("Exception occured: "+ne);
      }
      LinkedList<Integer> ll=new LinkedList();
      ll.addAll(ai1);
      ll.poll();
      ll.element();
      ll.offer(50);      
    }
@Deprecated
	@SuppressWarnings("unchecked")
    public static void teststr(Collection<String> c1) {
      
        try {
          c1.add("TR");
          c1.add("TRY");
          c1.add("TRY");
        }
        catch(Duplicated ne) {
          System.err.println("Exception occured: "+ne);
        }
        HashSet<String> temp=new HashSet<>();
        HashSet<String> temp2=new HashSet<>();
        
        try {
          temp.add("JAVA");
          temp.add("JAVADOC");

          temp2.add("C++");
          temp2.add("C");
          temp2.add("PYTHON");
          temp2.add("C#");          
        }
        catch(Duplicated ne) {
          System.err.println("Exception occured: "+ne);
        }
        c1.addAll(temp);
        out.println(c1);

        out.println("IS C1 EMPTY?\n"+c1.isEmpty());
        out.println("DOES C1 CONTAINS TR");
        out.println(c1.contains("TR"));
        
        out.println("DOES C1 CONTAINS PYTHON");
        out.println(c1.contains("PYTHON"));

        out.println("DOES C1 CONTAINS ALL OF THE C++ C PYTHON C#");
        out.println(c1.containsAll(temp2));

        c1.remove("TR");
        out.println("DOES C1 CONTAINS TR");
        out.println(c1.contains("TR"));   
        
        out.println("BEFORE REMOVE ALL C1 IS:");
        out.print(c1);
        c1.removeAll(temp);
        out.print("AFTER REMOVE ALL C1 IS:");
        out.print(c1);     

        try {
          c1.add("JAVA");
          c1.add("JAVADOC");
        }     
        catch(Duplicated ne) {
          System.err.println("Exception occured: "+ne);
        }
        out.println("SIZE:"+c1.size());
        out.println(temp);

        out.println("BEFORE RETAIN ALL C1 IS:");
        out.print(c1);
        c1.retainAll(temp);   
        out.print("AFTER RETAIN ALL C1 IS:");
        out.print(c1); 

        c1.clear();
        out.print(c1);
        out.println("IS C1 EMPTY?\n"+c1.isEmpty());          
      try {
        Iterator<String> it=c1.iterator();
        it.remove();
      }
      catch(NoElementException ne) {
        System.err.println("Exception occured: "+ne);
      }
      catch(QueueException ne) {
        System.err.println("Exception occured: "+ne);
      }
        ArrayList<String> ai1=new ArrayList();
      try {

        ai1.add("EXC");
        ai1.get(0);
      }
      catch(OutoftherangeException ne) {
        System.err.println("Exception occured: "+ne);
      }

      LinkedList<String> ll=new LinkedList();
      ll.addAll(ai1);

      ll.poll();
      ll.element();
      ll.offer("HE");
       
    }    
}
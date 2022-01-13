package yyolcu2018_1801042609;


import yyolcu2018_1801042609.Collection;
import yyolcu2018_1801042609.Iterator;
import yyolcu2018_1801042609.Queue;
import yyolcu2018_1801042609.QueueException;
import yyolcu2018_1801042609.NoElementException;
import yyolcu2018_1801042609.OutoftherangeException;
/**
*This interface represents the HashSet interface of the JAVA Collection Classes
*/
public class Itr<E> implements Iterator<E>{


	private E[] values;
	private int cur=-1;
	private int size=0;
	private Collection<E> hold;

	/**
	*Returns true if the iteration has more elements.
	*/
	public Itr(Collection<E> import_c,E[] import_e) {
		cur=0;
		this.size=import_c.size();
		this.values=import_e;
		this.hold=import_c;
	}
	@Override
	public boolean hasNext() {
		return cur!=size;
	}
	/**
	*Returns the next element in the iteration.
	*/
	@SuppressWarnings("unchecked")
	@Override
	public E next() throws OutoftherangeException{
		if(hasNext()) {;
			return values[cur++];
		}   
		else {
			throw new OutoftherangeException();
		}                 
	}
	/**
	*Removes from the underlying collection the last element returned by this iterator. This method does not work for Queues, it throws an exception.
	*/	
	@Override
	public void remove() throws QueueException , NoElementException{
		if(hold instanceof Queue) {
			throw new QueueException();
		}
		else if(hold.size()==0) {
			throw new NoElementException();
		}
		else {
			hold.remove(values[cur]);
		}
	}
}


package yyolcu2018_1801042609;
/**
*This interface represents the Iterator interface of the JAVA Collection Classes
*/
public interface Iterator<E> {


	/**
	*Returns true if the iteration has more elements.
	*/
	boolean hasNext();

	/**
	*Returns the next element in the iteration.
	*/
	E next() throws OutoftherangeException;

	/**
	*Removes from the underlying collection the last element returned by this iterator. This method does not work for Queues, it throws an exception.
	*/
	void remove() throws QueueException , NoElementException;
}                                          
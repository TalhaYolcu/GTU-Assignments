package yyolcu2018_1801042609;
/**
*This interface represents the Queue interface of the JAVA Collection Classes
*/
public interface Queue<E> extends Collection<E> {

	/**
	*Retrieves, but does not remove, the head of this queue.
	*/
	E element();
	/**	
	*Inserts the specified element into this queue if it is possible to do so immediately without violating capacity restrictions.
	@param e element that will be insterted	
	*/
	boolean offer(E e);
	/**
	*Retrieves and removes the head of this queue, or returns null if this queue is empty.
	*/
	E poll();
}
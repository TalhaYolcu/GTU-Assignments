
package yyolcu2018_1801042609;
/**
*This interface represents the Collection interface of the JAVA Collection Classes
*/
public interface Collection<E> {

	// Returns an iterator over the elements in this collection.
	/**
	*Return an iterator
	*/
	Iterator<E> iterator();

	//Ensures that this collection contains the specified element (optional operation).
	/**
	*Adds the given element to the collection
	@param e the element that will be added to the collection
	@exception Duplicated Element are Duplicated
	*/
	boolean add(E e) throws Duplicated;

	//Adds all of the elements in the specified collection to this collection (optional operation).
	/**
	*Adds the all of the given collection to our collection
	@param c Collection that will be added
	**/
	boolean addAll(Collection<E> c);

	//Removes all of the elements from this collection (optional operation).
	/**
	*Assigns size to zero and values to null
	*/
	void clear();

	//Returns true if this collection contains the specified element.
	/**
	*Checks the does the collection have the given element
	@param e element that will be checked
	*/
	boolean contains(E e);

	//Returns true if this collection contains all of the elements in the specified collection.
	/**
	*Checks the our collection is containing the given collection's elements
	@param c The given collection
	*/
	boolean containsAll(Collection<E> c);

	//Returns true if this collection contains no elements.
	/**
	*Is it empty?
	*/
	boolean isEmpty();

	//Removes a single instance of the specified element from this collection, if it is present (optional operation).
	/**
	*Removes the given element
	@param e the given element
	*/
	boolean remove(E e);

	//Removes all of this collection's elements that are also contained in the specified collection (optional operation).
	/**
	*Removes all of this collection's elements that are also contained in the specified collection
	@param c the given collection
	*/
	boolean removeAll(Collection<E> c);

	//Retains only the elements in this collection that are contained in the specified collection (optional operation).
	/**
	*Retains only the elements in this collection that are contained in the specified collection
	@param c the given collection  
	*/
	boolean retainAll(Collection<E> c);

	//Returns the number of elements in this collection.
	/**
	*Returns size
	*/
	int size();
}


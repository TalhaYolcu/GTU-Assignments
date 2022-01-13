package yyolcu2018_1801042609;
/**
*This interface represents the List interface of the JAVA Collection Classes
*/
public interface List<E> extends Collection<E> {

	/**
	*Returns the element at the specified position in this list.
	@param index the acces index
	*/
	E get(int index) throws OutoftherangeException;
}
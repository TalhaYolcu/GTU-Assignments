package yyolcu2018_1801042609;
/**
*This class represents the ArrayList class of the JAVA Collection Classes
*/
public class ArrayList<E> implements List<E> {


	private E[] values;
	private int size=0;

	/**
	*Constructor for ArrayList class
	*Assigns size 0
	*/
	public ArrayList() {
		size=0;
	}
	/**
	*Adds the given element to the collection
	@param e the element that will be added to the collection
	*/
	@SuppressWarnings("unchecked")
	@Override 	
	public boolean add(E e) {
		E[] temp=(E[])new Object[size+1];
		int i;
		for(i=0;i<size;i++){
			temp[i]=values[i];
		}
		temp[i]=e;
		values=(E[])new Object[size+1];
		for(i=0;i<size+1;i++) {
			values[i]=temp[i];
		}
		size+=1;
		return true;
	}
	/**
	*Return an iterator
	*/	
	@Override	
	public Iterator<E> iterator() {
		return new Itr<E>(this,values);
	}
	/**
	*Adds the all of the given collection to our collection
	@param c Collection that will be added
	**/

	@Override
	@SuppressWarnings("unchecked")	
	public boolean addAll(Collection c) {
		Iterator<E> temp_iter=c.iterator();
		while(temp_iter.hasNext()) {
			try {
				add(temp_iter.next());
			}
			catch(OutoftherangeException ne){
				System.err.println("Error occured: "+ne);
			}

		}
		return true;
	}
	/**
	*Assigns size to zero and values to null
	*/
	@Override
	public void clear() {
		size=0;
		values=null;
	}
	/**
	*Checks the does the collection have the given element
	@param e element that will be checked
	*/
	@Override
	@SuppressWarnings("unchecked")
	public boolean contains(E e) {
		int i;
		boolean flag=false;
		for(i=0;i<size;i++) {
			if(values[i]==e) {
				flag=true;
				break;
			}
		}
		return flag;
	}
	/**
	*Checks the our collection is containing the given collection's elements
	@param c The given collection
	*/
	@Override
	@SuppressWarnings("unchecked")
	public boolean containsAll(Collection c) {
		Iterator<E> temp_iter=c.iterator();
		boolean flag=true;
		while(temp_iter.hasNext()) {
			try {
				if(!contains(temp_iter.next())) {
					flag=false;
					break;
				}
			}
			catch(OutoftherangeException ne) {
				System.err.println("Error occured: "+ne);
			}

		}
		return flag;
	}
	/**
	*Is it empty?
	*/
	@Override
	public boolean isEmpty() {
		return size>0;
	}
	/**
	*Removes the given element
	@param e the given element
	*/
	@Override
	@SuppressWarnings("unchecked")	
	public boolean remove(E e) {
		boolean flag=true;
		int i;
		if(!contains(e)) {
			flag=false;
		}
		else if(size<1) {
			flag=false;
		}
		else {
			for(i=0;i<size;i++) {
				if(e==values[i]) {
					break;
				}
			}
			for(;i<size-1;i++) {
				values[i]=values[i+1];
			}
			values[size-1]=null;
			size-=1;
			flag=true;
		}
		return flag;		
	}
	/**
	*Removes all of this collection's elements that are also contained in the specified collection
	@param c the given collection
	*/
	@Override
	@SuppressWarnings("unchecked")
	public boolean removeAll(Collection c) {
		boolean flag=true;
		Iterator<E> temp_iter=c.iterator();
		if(!containsAll(c)) {
			flag=false;
		}
		else {
			while(temp_iter.hasNext()) {
				try {
					remove(temp_iter.next());
				}
				catch(OutoftherangeException ne) {
					System.err.println("Exception occured: "+ne);
				}
			}
		}
		return flag;		
	}
	/**
	*Retains only the elements in this collection that are contained in the specified collection
	@param c the given collection  
	*/
	@Override
	@SuppressWarnings("unchecked")
	public boolean retainAll(Collection c) {
		boolean flag=true;
		if(!containsAll(c)) {
			flag=false;
			//exception
		}
		else {
			int i;
			for(i=0;i<size;i++) {
				if(!c.contains(values[i])) {
					remove(values[i]);
				}
			}		
		}
		return flag;		
	}
	/**
	*Returns size
	*/
	@Override
	public int size() {
		return size;
	}
	/**
	*Returns the element at the specified position in this list.
	@param index the acces index
	*/
	public E get(int index) throws OutoftherangeException {
		if(index>=size) {
			throw new OutoftherangeException();
		}
		else {
			return values[index];			
		}

	}
	/**
	*Help to the print the fields
	*/
	@Override
	@SuppressWarnings("unchecked")	
	public String toString(){
		String buffer=new String();
		int i;
		if(size==0) {
			buffer="There is no element of this Collection\n";
		}
		else {
			buffer="HashSet's elements:\n";
			for(i=0;i<size;i++) {
				buffer+=values[i];
				buffer+=" ";
			}			
		}
		buffer+="\n";
		return buffer;
	}		
}
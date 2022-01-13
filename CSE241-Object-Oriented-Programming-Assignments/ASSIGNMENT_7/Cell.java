package yyolcu2018_1801042609;

public class Cell {
	private int y;					//holds the x , y and symbol of the cell
	private int x;
	private symbol s;
	public Cell() {}
	public void set_x(int xval) {
		x=xval;
	}				//setters and getters for cell x - y - symbol
	public int get_x() {
		return x;
	}
	public void set_y(int yval) {
		y=yval;
	}
	public int get_y() {
		return y;
	}
	public symbol get_symbol() {
		return s;
	}
	public void set_symbol(symbol sym) {
		s=sym;
	}			
}
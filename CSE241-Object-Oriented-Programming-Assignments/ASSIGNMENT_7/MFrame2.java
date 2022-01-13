package yyolcu2018_1801042609;

import javax.swing.JFrame;
import java.awt.Color;
import javax.swing.JLabel;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.*;
import yyolcu2018_1801042609.Cell;
import yyolcu2018_1801042609.HexGame;
import java.io.*;
import java.util.*;

enum symbol {
	d,
	u1,
	u2,
	w1,
	w2
}

public class MFrame2 extends JFrame implements ActionListener,HexGame{
	private JButton[][] button;
	private JButton reset;
	private JButton load;
	private JButton save;
	private int usermode;
	private int size;
	private int move;
	private int lasty;
	private int lastx;
	private JLabel label;
	private JButton undo;
	private JTextField asksize;
	private JRadioButton pvp;
	private JRadioButton pvb;
	private ButtonGroup bg;
	private JPanel panel;
	private Cell[][] hexCells;
	private Cell[] usermoves;
	private symbol[][] control;
	private int winner;
	private	int xforai;
	private	int yforai;
	private int numofmoves;

	public MFrame2() {
		int i,k;
		asksize=new JTextField("Enter size here");
		asksize.setBounds(0,750,100,50);
		this.add(asksize);
		asksize.addActionListener(this);

		size=8;
		button=new JButton[size][size];
		reset=new JButton();
		load=new JButton();
		save =new JButton();
		undo = new JButton();
		pvp=new JRadioButton("Player vs Player");
		pvb=new JRadioButton("Player vs AI");
		bg=new ButtonGroup();
		panel=new JPanel();
		panel.setBounds(0,850,300,300);

		move=1;
		winner=0;
		numofmoves=0;
		for(i=0;i<size;i++) {
			button[i]=new JButton[size];
			for(k=0;k<size;k++) {
				button[i][k]=new JButton();
			}
		}
		for(i=0;i<size;i++) {
			for(k=0;k<size;k++) {
				//button[i][k].setBounds(i*25+k*25/2,k*25,25,25);
				button[i][k].setBounds(i*50+k*50/2+25,k*50+25,50,50);
				button[i][k].addActionListener(this);
				button[i][k].setText(".");
				button[i][k].setFocusable(false);
				this.add(button[i][k]);
			}			
		}
		this.repaint();
		reset.setBounds(0,700,100,50);
		reset.addActionListener(this);
		reset.setText("RESET");

		load.setBounds(100,700,100,50);
		load.addActionListener(this);
		load.setText("LOAD");

		save.setBounds(200,700,100,50);
		save.addActionListener(this);
		save.setText("SAVE");

		undo.setBounds(300,700,100,50);
		undo.addActionListener(this);
		undo.setText("UNDO");

		pvp.setBounds(0,800,200,50);
		pvb.setBounds(0,850,100,50);

		pvp.addActionListener(this);
		pvb.addActionListener(this);

		bg.add(pvp);
		bg.add(pvb);

		panel.add(reset);
		panel.add(load);
		panel.add(save);
		panel.add(undo);
		panel.add(pvp);
		panel.add(pvb);

		label =new JLabel();
		label.setText("Turn is X");

		label.setVerticalAlignment(JLabel.TOP);
		label.setHorizontalAlignment(JLabel.CENTER);
		label.setBounds(0,0,750,25);
		label.setForeground(Color.white);
		label.setBackground(new Color(0x123456));
		label.setOpaque(true);

		this.setTitle("Yakup Talha Yolcu 1801042609 HexGame");
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setLayout(null);
		//this.setResizable(false);
		this.setSize(1200,1200);
		this.setVisible(true);
		this.add(label);
		this.add(panel);
		this.repaint();
	}
	@Override
	public void actionPerformed(ActionEvent e) {
		int i,k,z,j,win=0;
		String str=new String();
		if(e.getSource()==pvp) {
			usermode=1;
		}
		else if(e.getSource()==pvb) {
			usermode=2;
		}
		else if(e.getSource()==asksize) {
			for(i=0;i<size;i++) {
				for(k=0;k<size;k++) {
					this.remove(button[i][k]);
				}
			}
			this.repaint();
			str=String.format("%s",e.getActionCommand());
			size=Integer.parseInt(str);
			button=new JButton[size][size];
			for(i=0;i<size;i++) {
				button[i]=new JButton[size];
				for(k=0;k<size;k++) {
					button[i][k]=new JButton();
				}
			}
			for(i=0;i<size;i++) {
				for(k=0;k<size;k++) {
					//button[i][k].setBounds(i*25+k*25/2,k*25,25,25);
					button[i][k].setBounds(i*50+k*50/2+25,k*50+25,50,50);
					button[i][k].addActionListener(this);
					button[i][k].setText(".");
					button[i][k].setFocusable(true);
					button[i][k].setBackground(Color.GREEN);
					this.add(button[i][k]);
				}			
			}
			this.repaint();
			hexCells=new Cell[get_size()][get_size()];
			for(i=0;i<get_size();i++) {
				hexCells[i]=new Cell[get_size()];
				for(k=0;k<get_size();k++) {
					hexCells[i][k]=new Cell();
				}
			}
			usermoves=new Cell[get_size()*get_size()];
			for(i=0;i<get_size()*get_size();i++) {
				usermoves[i]=new Cell();
			}
			control=new symbol[get_size()][get_size()];
			for(i=0;i<get_size();i++) {
				control[i]=new symbol[get_size()];
			}
			fill_the_empty_board();
			fill_the_empty_board(control);
		}
		else if(e.getSource()==save) {
			String fname=JOptionPane.showInputDialog(null,"Enter file name","SAVE",JOptionPane.PLAIN_MESSAGE);
			try {
				FileWriter writer=new FileWriter(fname);
				String str2=new String();
				String str3=new String();
				String str4=new String();
				String str5=new String();
				String str6=new String();
				str2=String.format("%d\n%d\n%d\n",get_size(),usermode,move);
				for(i=0;i<get_size();i++) {
					for(k=0;k<get_size();k++) {
						if(hexCells[i][k].get_symbol()==symbol.u1) {
							str3+=String.format("l %d %d\n",k,i);
						} 
					}
				}
				str3+="-\n";
				for(i=0;i<get_size();i++) {
					for(k=0;k<get_size();k++) {
						if(hexCells[i][k].get_symbol()==symbol.u2) {
							str3+=String.format("l %d %d\n",k,i);
						} 
					}
				}
				str3+="-\n";
				for(i=0;i<get_size();i++) {
					for(k=0;k<get_size();k++) {
						if(hexCells[i][k].get_symbol()==symbol.d) {
							str3+=String.format("l %d %d\n",k,i);
						} 
					}
				}								
				str3+="-\n";
				str3+=String.format("%d\n",get_numof_moves());
				for(i=0;i<get_numof_moves();i++) {
					str3+=String.format("%d\n%d\n",usermoves[i].get_x(),usermoves[i].get_y());
				}
				str3+="2347";
				writer.write(str2);
				writer.write(str3);
				writer.close();
			}
			catch (IOException e1) {
				e1.printStackTrace();
			}
		}
		else if(e.getSource()==load) {
			char c;
			int xval;
			int yval;
			int tempsize;
			int tempuser;
			int tempmove;
			int mycnt=0;
			int incoming;
			int myx=0;
			int myy=0;
			String fname=JOptionPane.showInputDialog(null,"Enter file name","LOAD",JOptionPane.PLAIN_MESSAGE);
			try {
				
				//HER ŞEYİ SIFIRLA

				for(i=0;i<size;i++)  {
					for(k=0;k<size;k++) {
						this.remove(button[i][k]);
					}
				}


				Scanner x=new Scanner(new File(fname));
				String a=new String();		
				while(true) {
					a=x.next();

					set_size(Integer.parseInt(a));

					hexCells=new Cell[get_size()][get_size()];
					button=new JButton[get_size()][get_size()];
					for(i=0;i<get_size();i++) {
						hexCells[i]=new Cell[get_size()];
						button[i]=new JButton[get_size()];
						for(k=0;k<get_size();k++) {
							hexCells[i][k]=new Cell();
							//this.remove(button[k][i]);
							button[i][k]=new JButton();
							button[i][k].setBounds(i*50+k*50/2+25,k*50+25,50,50);
							button[i][k].addActionListener(this);
							button[i][k].setText(".");
							button[i][k].setFocusable(true);
							button[i][k].setBackground(Color.GREEN);
							this.add(button[i][k]);
						}
					}
					this.repaint();
					this.repaint();

					a=x.next();
					usermode=Integer.parseInt(a);
					move=Integer.parseInt(x.next());

					while(true) {
						a=x.next();
						if(a.equals("-")) {
							break;
						}
						else {
							mycnt+=1;
							a=x.next();
							xval=Integer.parseInt(a);
							a=x.next();
							yval=Integer.parseInt(a);
							hexCells[yval][xval].set_symbol(symbol.u1);
							button[xval][yval].setText("x");

							button[xval][yval].setBackground(new Color(0x123456)); 
						}
					}
					while(true) {
						a=x.next();
						if(a.equals("-")) {
							break;
						}
						else {
							mycnt+=1;
							a=x.next();
							xval=Integer.parseInt(a);
							a=x.next();
							yval=Integer.parseInt(a);
							hexCells[yval][xval].set_symbol(symbol.u2);
							button[xval][yval].setText("o");
							button[xval][yval].setBackground(Color.RED); 
						}
					}	
					while(true) {
						a=x.next();
						if(a.equals("-")) {
							break;
						}
						else {
							mycnt+=1;
							a=x.next();
							xval=Integer.parseInt(a);
							a=x.next();
							yval=Integer.parseInt(a);
							hexCells[yval][xval].set_symbol(symbol.d);
							button[xval][yval].setText(".");
							button[xval][yval].setBackground(Color.GREEN); 
						}
					}
					a=x.next();
					incoming=Integer.parseInt(a);
					set_numofmoves(incoming);
					usermoves=new Cell[get_size()*get_size()];
					for(i=0;i<get_size()*get_size();i++) {
						usermoves[i]=new Cell();
					}
					i=0;							
					while(true) {
						a=x.next();
						if(a.equals("2347")) {
							break;
						}
						else {
							myx=Integer.parseInt(a);
							a=x.next();
							myy=Integer.parseInt(a);
							usermoves[i].set_x(myx);
							usermoves[i].set_y(myy);
							i+=1;
						}
					}
					this.repaint();
					this.repaint();
					int _x=move%2;
					if(_x==1){
						label.setText("Turn is X");
					}
					else {
						label.setText("Turn is O");
					}
					break;		
				}
				x.close();
			}
			catch (IOException e1) {
				e1.printStackTrace();
			}
		}
		else if(e.getSource()==undo) {
			int x=move%2;
			switch(usermode) {
				case 1:
				hexCells[usermoves[get_numof_moves()-1].get_y()][usermoves[get_numof_moves()-1].get_x()].set_symbol(symbol.d);
				button[usermoves[get_numof_moves()-1].get_x()][usermoves[get_numof_moves()-1].get_y()].setText(".");
				button[usermoves[get_numof_moves()-1].get_x()][usermoves[get_numof_moves()-1].get_y()].setBackground(Color.GREEN);
				if(x==1) {
					move=2;
					label.setText("Turn is O");
				}
				else {
					move=1;
					label.setText("Turn is X");
				}
				break;

				case 2:
				hexCells[usermoves[get_numof_moves()-1].get_y()][usermoves[get_numof_moves()-1].get_x()].set_symbol(symbol.d);			//AI HAMLESİ
				hexCells[usermoves[get_numof_moves()-2].get_y()][usermoves[get_numof_moves()-2].get_x()].set_symbol(symbol.d);	
				button[usermoves[get_numof_moves()-1].get_x()][usermoves[get_numof_moves()-1].get_y()].setText(".");
				button[usermoves[get_numof_moves()-2].get_x()][usermoves[get_numof_moves()-2].get_y()].setText(".");
				button[usermoves[get_numof_moves()-1].get_x()][usermoves[get_numof_moves()-1].get_y()].setBackground(Color.GREEN);
				button[usermoves[get_numof_moves()-2].get_x()][usermoves[get_numof_moves()-2].get_y()].setBackground(Color.GREEN);
				break;
			}
		}
		else if(e.getSource()==reset) {
			for(i=0;i<get_size();i++) {
				for(k=0;k<get_size();k++) {
					hexCells[i][k].set_symbol(symbol.d);
					button[i][k].setBackground(Color.GREEN);
					button[i][k].setText(".");
					set_numofmoves(0);
					move=1;
					label.setText("Turn is X");
				}
			}
		}
		else {
			for(i=0;i<size;i++) {
				for(k=0;k<size;k++) {
					if(e.getSource()==button[i][k]) {
						if(check_validity(i,k)) {
							switch (move) {
								case 1:
								button[i][k].setText("x");
								numofmoves+=1;
								button[i][k].setBackground(new Color(0x123456));

								usermoves[get_numof_moves()-1].set_symbol(symbol.u1);
								usermoves[get_numof_moves()-1].set_x(i);
								usermoves[get_numof_moves()-1].set_y(k);
								label.setText("Turn is O");
								hexCells[k][i].set_symbol(symbol.u1);
								hexCells[k][i].set_x(i);
								hexCells[k][i].set_y(k);
								set_x_for_ai(i);
								set_y_for_ai(k);
								for(z=0;z<get_size();z++) {											//IF THERE IS AN ELEMENT AT THE LEFT AND RIGHT SIDE OF THE BOARD,CHECK IS A WINNER  
									if(hexCells[z][0].get_symbol()==symbol.u1) {
										for(j=0;j<get_size();j++) {
											if(hexCells[j][get_size()-1].get_symbol()==symbol.u1) {
												win=is_winner(0,z,0,control,'x');
												winner=win;																					
												fill_the_empty_board(control);			//CLEAR THE CONTROL ARRAY SO THAT WE CAN CHECK PROPERLY WHO IS WINNER AT THE NEXT MOVE									
												if(win==1) {					
													break;
												}
											}
											if(win==1) {
												break;
											}
										}
										if(win==1) {
											break;
										}						
									}
									if(win==1) {
										break;
									}
								}
								if(usermode==1) {

								}
								else {
									move=2;
									numofmoves+=1;
									play();
									for(z=0;z<get_size();z++) {										//CHECK IF THERE IS A POSSIBILITY FOR WINNING
										if(hexCells[0][z].get_symbol()==symbol.u2) {						//FROM TOP TO BOTTOM
											for(j=0;j<get_size();j++) {
												if(hexCells[get_size()-1][j].get_symbol()==symbol.u2) {
													win=is_winner(j,get_size()-1,0,control,'o'); 
													fill_the_empty_board(control);					//CLEAR THE CONTROL ARRAY
													if(win==2) {
														winner=win;
														break;
													}
												}
												if(win==2) {
													break;
												}
											}
											if(win==2) {
												break;
											}						
										}
										if(win==2) {
											break;
										}
									}				
									move=1;

								}						
								break;

								case 2:
								button[i][k].setText("o");
								button[i][k].setBackground(Color.RED);
								numofmoves+=1;
								usermoves[get_numof_moves()-1].set_x(i);
								usermoves[get_numof_moves()-1].set_y(k);
								label.setText("Turn is X");
								hexCells[k][i].set_symbol(symbol.u2);
								usermoves[get_numof_moves()-1].set_symbol(symbol.u2);
								hexCells[k][i].set_x(i);
								hexCells[k][i].set_y(k);
								for(z=0;z<get_size();z++) {										//CHECK IF THERE IS A POSSIBILITY FOR WINNING
									if(hexCells[0][z].get_symbol()==symbol.u2) {						//FROM TOP TO BOTTOM
										for(j=0;j<get_size();j++) {
											if(hexCells[get_size()-1][j].get_symbol()==symbol.u2) {
												win=is_winner(j,get_size()-1,0,control,'o'); 
												fill_the_empty_board(control);					//CLEAR THE CONTROL ARRAY
												if(win==2) {
													winner=win;
													break;
												}
											}
											if(win==2) {
												break;
											}
										}
										if(win==2) {
											break;
										}						
									}
									if(win==2) {
										break;
									}
								}				
								move=1;
								break;
							}
						}				
					}
				}
			}			
		}
		if(winner!=0) {
			label.setText("WINNER IS: PLAYER "+winner);
			for(i=0;i<get_size();i++) {
				for(k=0;k<get_size();k++) {
					button[i][k].setEnabled(false);
				}				
			}
		}
		this.repaint();
	}
	@Override
	public int get_numof_moves() {
		return numofmoves;
	}
	@Override
	public void set_numofmoves(int x) {
		numofmoves=x;
	}
	@Override
	public int get_size() {
		return size;
	}
	@Override
	public void set_size(int a) {
		size=a;
	}
	@Override
	public void fill_the_empty_board(){
		for(int i=0;i<get_size();i++) {
			for(int k=0;k<get_size();k++) {
				hexCells[i][k].set_symbol(symbol.d);
			}
		}
	}
	@Override
	public void fill_the_empty_board(symbol[][] control){
		for(int i=0;i<get_size();i++) {
			for(int k=0;k<get_size();k++) {
				control[i][k]=symbol.d;
			}
		}
	}
	@Override	
	public boolean check_validity(int xval,int yval) {
		return (hexCells[yval][xval].get_symbol()==symbol.d);	
	}
	@Override
	public int is_winner(int xval,int yval,int direction,symbol[][] control,char p) {
		int ret=-1,i;
	//IF THERE'S A POSSIBILITY OF THE WINNER CHECK IT DEPEND ON THE SITUATIONS AND DIRECTIONS
	//1 yönü x artar y azalır	//2 yönü x artar y sabit	//3 yönü x sabit y artar	//4 yönü x azalır y artar	//5 yönü x azalır y sabit	//6 yönü x sabit y azalır
		boolean arr[]=new boolean[7];
		if(p=='x' && xval==(get_size()-1)) {
			ret=1;				
		}
		else if(p=='o' && yval==0) {
			ret=2;				
		}
		else {
			if(xval==0 && yval==0) {							//1
				for(i=1;i<=6;i++) {
					if(i==2) {
						arr[i-1]=true;
					}
					else if(i==3) {
						arr[i-1]=true;					
					}
					else {
						arr[i-1]=false;					
					}
				}
			}
			else if(xval==0 && 0<yval && yval<(get_size()-1)) {			//2
				for(i=1;i<=6;i++) {
					if(i<=3) {
						arr[i-1]=true;
					}
					else if(i==6) {
						arr[i-1]=true;					
					}
					else {
						arr[i-1]=false;					
					}						
				}
			}
			else if(xval==0 && yval==(get_size()-1)) {				//3
				for(i=1;i<=6;i++) {
					if(i<=2) {
						arr[i-1]=true;
					}
					else if(i==6) {
						arr[i-1]=true;					
					}				
					else {
						arr[i-1]=false;
					}			
				}	
			}
			else if(0<xval && xval<(get_size()-1) && yval==(get_size()-1)) {		//4
				for(i=1;i<=6;i++) {
					if(i<=2) {
						arr[i-1]=true;
					}
					else if(i>=5) {
						arr[i-1]=true;
					}
					else {
						arr[i-1]=false;
					}			
				}
			}
			else if(0<xval && xval<(get_size()-1) && yval==0) {				//5
				for(i=1;i<=6;i++) {
					if(i==1) {
						arr[i-1]=false;
					}
					else if(i==6) {
						arr[i-1]=false;					
					}
					else {
						arr[i-1]=true;
					}			
				}
			}
			else if(0<xval && xval<(get_size()-1) && 0<yval && yval<(get_size()-1)) {		//6
				for(i=1;i<=6;i++) {
					arr[i-1]=true;			
				}
			}
			else if(xval==(get_size()-1) && 0<yval && yval<(get_size()-1)) {	//8		
				for(i=1;i<=6;i++) {
					if(i>=3) {
						arr[i-1]=true;
					}
					else {
						arr[i-1]=false;
					}
				}
			}
			else if(xval==(get_size()-1) && yval==(get_size()-1)) {			//9
				for(i=1;i<=6;i++) {
					if(i>=5) {
						arr[i-1]=true;
					}
					else {
						arr[i-1]=false;
					}
				}
			}
			correct(arr,direction);		
			if(p=='x') {
				ret=situation(xval,yval,direction,arr,control,'x');	
			}
			else if(p=='o') {
				ret=situation(xval,yval,direction,arr,control,'o');	
			}								
		}
		switch(ret) {
			case 1:
				hexCells[yval][xval].set_symbol(symbol.w1);		//MAKE CAPITAL LETTER
				break;
			case 2:
				hexCells[yval][xval].set_symbol(symbol.w2);
				break;			
		}
		return ret;
	}
	@Override
	public int situation(int xval,int yval,int direction,boolean arr[],symbol[][] control,char p) {
	//CHECKING DEPEND ON THE DIRECTIONS AND SITUATIONS
	//THERE IS TWO TABLE FOR EXPLAINING WHAT IS SITUATION AND DIRECTION IN helper.h
	//BOOL ARRAY HOLD THE DIRECTIONS AND P HOLD 'x' or 'o'
		int foo=direction;
		foo+=1;
		int i,ret=-1,c=-1;
		for(i=0;i<6;i++) {
			if(arr[i]==true) {
				switch(i+1) {
					case 1:
						if(p=='x') {
							if(hexCells[yval-1][xval+1].get_symbol()==symbol.u1) {
								c=check_control_array(control,xval+1,yval-1,p);
								if(c==0) {							
									control[yval][xval]=symbol.u1;	
									ret=is_winner(xval+1,yval-1,1,control,'x');		//1 yönü
								}
							}
						}
						else {
							if(hexCells[yval-1][xval+1].get_symbol()==symbol.u2) {
								c=check_control_array(control,xval+1,yval-1,p);
								if(c==0) {							
									control[yval][xval]=symbol.u2;	
									ret=is_winner(xval+1,yval-1,1,control,'o');		//1 yönü
								}
							}
						}
						break;
					case 2:																		//2 yönü
						if(p=='x') {
							if(hexCells[yval][xval+1].get_symbol()==symbol.u1) {
								c=check_control_array(control,xval+1,yval,p);
								if(c==0) {
									control[yval][xval]=symbol.u1;	
									ret=is_winner(xval+1,yval,2,control,'x');
								}
							}
						}
						else {
							if(hexCells[yval][xval+1].get_symbol()==symbol.u2) {
								c=check_control_array(control,xval+1,yval,p);
								if(c==0) {
									control[yval][xval]=symbol.u2;	
									ret=is_winner(xval+1,yval,2,control,'o');
								}
							}
						}	
						break;		
					case 3:																	//3 yönü
						if(p=='x') {
							if(hexCells[yval+1][xval].get_symbol()==symbol.u1) {
								c=check_control_array(control,xval,yval+1,p);
								if(c==0) {
									control[yval][xval]=symbol.u1;	
									ret=is_winner(xval,yval+1,3,control,'x');
								}
							}
						}
						else {
							if(hexCells[yval+1][xval].get_symbol()==symbol.u2) {
								c=check_control_array(control,xval,yval+1,p);
								if(c==0) {
									control[yval][xval]=symbol.u2;	
									ret=is_winner(xval,yval+1,3,control,'o');
								}
							}
						}
						break;
					case 4:
						if(p=='x') {
							if(hexCells[yval+1][xval-1].get_symbol()==symbol.u1) {
								c=check_control_array(control,xval-1,yval+1,p);
								if(c==0) {
									control[yval][xval]=symbol.u1;	
									ret=is_winner(xval-1,yval+1,4,control,'x');		//4 yönü
								}
							}
						}
						else {
							if(hexCells[yval+1][xval-1].get_symbol()==symbol.u2) {
								c=check_control_array(control,xval-1,yval+1,p);
								if(c==0) {
									control[yval][xval]=symbol.u2;	
									ret=is_winner(xval-1,yval+1,4,control,'o');		//4 yönü
								}
							}
						}
						break;
					case 5:
						if(p=='x') {
							if(hexCells[yval][xval-1].get_symbol()==symbol.u1) {
								c=check_control_array(control,xval-1,yval,p);
								if(c==0) {
									control[yval][xval]=symbol.u1;	
									ret=is_winner(xval-1,yval,5,control,'x');		//5 yönü
								}
							}
						}
						else {
							if(hexCells[yval][xval-1].get_symbol()==symbol.u2) {
								c=check_control_array(control,xval-1,yval,p);
								if(c==0) {
									control[yval][xval]=symbol.u2;	
									ret=is_winner(xval-1,yval,5,control,'o');		//5 yönü
								}
							}						
						}
						break;								
					case 6:
						if(p=='x') {
							if(hexCells[yval-1][xval].get_symbol()==symbol.u1) {
								c=check_control_array(control,xval,yval-1,p);
								if(c==0) {
									control[yval][xval]=symbol.u1;	
									ret=is_winner(xval,yval-1,6,control,'x');		//6 yönü
								}
							}
						}
						else {
							if(hexCells[yval-1][xval].get_symbol()==symbol.u2) {
								c=check_control_array(control,xval,yval-1,p);
								if(c==0) {
									control[yval][xval]=symbol.u2;	
									ret=is_winner(xval,yval-1,6,control,'o');		//6 yönü
								}
							}
						}
						break;	
				}
			}
			if(ret==1 || ret==2) {
				break;
			}
		}
		return ret;
	}
	@Override
	public int check_control_array(symbol[][] control,int xval,int yval,char p){
	//CHECKING IF WE'VE COME THIS PLACE WHILE WE ARE LOOKING FOR IS THERE A WINNER
		int ret=0;
		if(p=='x') {
			if(control[yval][xval]==symbol.u1) {
				ret=1;
			}
		}
		else if(p=='o') {
			if(control[yval][xval]==symbol.u2) {
				ret=1;
			}		
		}
		return ret;
	}
	@Override
	public void correct(boolean arr[],int direction){									
	//MAKE A CORRECTION FOR BOOL ARRAY THAT HOLD DIRECTONS
		//I'VE EXPLAINED ALSO WHY WE NEED TO CORRECT THE BOOL ARRAY IN helper2.h
		if(direction==0) {
		}
		else {
			if(direction>3) {
				arr[direction-4]=false;
			}
			else if(direction==3) {
				arr[5]=false;
			}
			else if(direction<3){
				arr[5-direction]=false;
			}			
		}
	}
	@Override
	public int get_y_for_ai(){
		return yforai;
	}						//ai uses the move that made my user
	@Override
	public int get_x_for_ai(){
		return xforai;
	}
	@Override
	public void set_y_for_ai(int yai){
		yforai=yai;
	}
	@Override				
	public void set_x_for_ai(int xai){
		xforai=xai;
	}
	@Override
	public void play(){
		int xval=get_x_for_ai();
		int yval=get_y_for_ai();
		int mysize=get_size();	
		if(xval==0 && yval==0) {														    //SITUATION1
			situation1();
		}
		else if(xval==0 && yval<(mysize-1) && yval>0) {										//SITUATION2
			situation2();
		}
		else if(xval==0 && yval==(mysize-1)) {										//SITUATION3
			situation3();
		}
		else if(xval<(mysize-1) && yval==(mysize-1) && yval>0) {							//SITUATION4
			situation4();
		}
		else if(xval<(mysize-1) && yval==0 && xval>0) {										//SITUATION5
			situation5();
		}
		else if(xval<(mysize-1) && yval<(mysize-1) && xval>0) {							//SITUATION6
			situation6_2();
		}
		else if(xval==(mysize-1) && yval==0) {										//SITUATION7
			situation7(xval,yval);
		}
		else if(xval==(mysize-1) && yval<(mysize-1) && yval>0) {							//SITUATION8
			situation8();
		}
		else if(xval==(mysize-1) && yval==(mysize-1)) {							//SITUATION9
			situation9();
		}				
	}
	@Override
	public void situation6(int xval,int yval) {
	// IF THERE IS NOT A MOVE THAT MACHINE FIND, MOVE THE MOST CLOSE PLACE
		//IF YOU CAN'T MOVE THE MOST CLOSE PLACE THEN START FROM BEGINNING AND MOVE THE FIRST PLACE THAT YOU FIND
		int i,k;
		double distance=999;
		double temp;
		int mx=-1,my=-1;
		int flag=0;
		for(i=1;i<(get_size()-1);i++) {
			for(k=1;k<(get_size()-1);k++) {
				temp=Math.sqrt((k-xval)*(k-xval)+(i-yval)*(i-yval));
				if(temp<distance) {
					if(check_validity_2(k,i)) {
						mx=k;
						my=i;					
					}	
				}
			}
		}
		if(mx<0) {
			for(i=0;i<get_size();i++) {
				for(k=0;k<get_size();k++) {
					if(hexCells[i][k].get_symbol()==symbol.d) {
						show(k,i);
						flag=1;
						break;
					}
				}
				if(flag==1) {
					break;
				}
			}
		}
		else {
			show(mx,my);
		}
	}
	@Override
	public void situation1() {
	// I IMPLEMENT 9 FUNCTIONS LIKE THAT FOR MACHINE DEPENDS ON THE DIRECTION AND SITUATION
		int xval=get_x_for_ai();
		int yval=get_y_for_ai();

		if(hexCells[yval][xval+1].get_symbol()==symbol.d) {
			show(xval+1,yval);	
		}
		else if(hexCells[yval+1][xval].get_symbol()==symbol.d) {
			show(xval,yval+1);
		}
		else if(hexCells[yval+2][xval].get_symbol()==symbol.d) {
			show(xval,yval+2);			
		}
		else {
			situation6(xval,yval);
		}
	}
	@Override
	public void situation2() {
		int xval=get_x_for_ai();
		int yval=get_y_for_ai();
		if(hexCells[yval][xval+1].get_symbol()==symbol.d) {
			show(xval+1,yval);
		}
		else if(hexCells[yval-1][xval+1].get_symbol()==symbol.d) {
			show(xval+1,yval-1);
		}
		else if(hexCells[yval+1][xval].get_symbol()==symbol.d) {
			show(xval,yval+1);
		}
		else if(hexCells[yval-1][xval].get_symbol()==symbol.d) {
			show(xval,yval-1);
		}
		else {
			situation6(xval,yval);
		}
	}
	@Override
	public void situation3() {
		int xval=get_x_for_ai();
		int yval=get_y_for_ai();
		if(hexCells[yval][xval+1].get_symbol()==symbol.d) {
			show(xval+1,yval);	
		}
		else if(hexCells[yval-1][xval+1].get_symbol()==symbol.d) {
			show(xval+1,yval-1);
		}
		else if(hexCells[yval][xval+1].get_symbol()==symbol.d) {
			show(xval+1,yval);
		}
		else {
			situation6(xval,yval);
		}
	}
	@Override
	public void situation4() {
		int xval=get_x_for_ai();
		int yval=get_y_for_ai();
		if(hexCells[yval][xval+1].get_symbol()==symbol.d) {
			show(xval+1,yval);
		}
		else if(hexCells[yval-1][xval+1].get_symbol()==symbol.d) {
			show(xval+1,yval-1);
		}
		else if(hexCells[yval-1][xval].get_symbol()==symbol.d) {
			show(xval,yval-1);
		}
		else if(hexCells[yval][xval-1].get_symbol()==symbol.d) {
			show(xval-1,yval);
		}
		else {
			situation6(xval,yval);
		}
	}
	@Override
	public void situation5() {
		int xval=get_x_for_ai();
		int yval=get_y_for_ai();
		if(hexCells[yval][xval-1].get_symbol()==symbol.d) {
			show(xval-1,yval);
		}
		else if(hexCells[yval+1][xval-1].get_symbol()==symbol.d) {
			show(xval-1,yval+1);
		}
		else if(hexCells[yval][xval+1].get_symbol()==symbol.d) {
			show(xval+1,yval);
		}
		else if(hexCells[yval+1][xval].get_symbol()==symbol.d) {
			show(xval,yval+1);
		}
		else {
			situation6(xval,yval);
		}
	}
	@Override
	public void situation6_2(){
		int xval=get_x_for_ai();
		int yval=get_y_for_ai();
		if(hexCells[yval][xval+1].get_symbol()==symbol.d) {
			show(xval+1,yval);
		}
		else if(hexCells[yval-1][xval+1].get_symbol()==symbol.d) {
			show(xval+1,yval-1);
		}
		else if(hexCells[yval-1][xval].get_symbol()==symbol.d) {
			show(xval,yval-1);
		}
		else if(hexCells[yval][xval-1].get_symbol()==symbol.d) {
			show(xval-1,yval);
		}
		else if(hexCells[yval+1][xval-1].get_symbol()==symbol.d) {
			show(xval-1,yval+1);
		}
		else if(hexCells[yval+1][xval].get_symbol()==symbol.d) {
			show(xval,yval+1);
		}
		else {
			situation7(get_size()-1,0);
		}
	}
	@Override
	public void situation7(int xval,int yval) {
		if(hexCells[yval][xval-1].get_symbol()==symbol.d) {
			show(xval-1,yval);
		}
		else if(hexCells[yval+1][xval].get_symbol()==symbol.d) {
			show(xval,yval+1);
		}
		else if(hexCells[yval+1][xval-1].get_symbol()==symbol.d){
			show(xval-1,yval+1);
		}
		else {
			situation6(xval,yval);
		}
	}
	@Override
	public void situation8() {
		int xval=get_y_for_ai();
		int yval=get_x_for_ai();
		if(hexCells[yval-1][xval].get_symbol()==symbol.d) {
			show(xval,yval-1);
		}
		else if(hexCells[yval][xval-1].get_symbol()==symbol.d) {
			show(xval-1,yval);
		}
		else if(hexCells[yval+1][xval-1].get_symbol()==symbol.d) {
			show(xval-1,yval+1);
		}
		else if(hexCells[yval+1][xval].get_symbol()==symbol.d) {
			show(xval,yval+1);
		}
		else {
			situation6(xval,yval);
		}
	}
	@Override
	public void situation9() {
		int xval=get_x_for_ai();
		int yval=get_y_for_ai();
		if(hexCells[yval-1][xval].get_symbol()==symbol.d) {
			show(xval,yval-1);
		}
		else if(hexCells[yval][xval-1].get_symbol()==symbol.d) {
			show(xval-1,yval);
		}
		else {
			situation6(xval,yval);
		}
	}
	@Override
	public void show(int xval,int yval){
		hexCells[yval][xval].set_symbol(symbol.u2);
		hexCells[yval][xval].set_x(xval);
		hexCells[yval][xval].set_y(yval);
		button[xval][yval].setText("o");
		button[xval][yval].setBackground(Color.RED);
		usermoves[get_numof_moves()-1].set_symbol(symbol.u2);
		usermoves[get_numof_moves()-1].set_x(xval);
		usermoves[get_numof_moves()-1].set_y(yval);
		//System.out.println(get_numof_moves());
	}
	@Override					//makes the ai's move
	public boolean check_validity_2(int xval,int yval){
		//checks the validity of the ai's move
		if(hexCells[yval][xval].get_symbol()==symbol.d) {
			return true;
		}
		else {
			return false;
		}		
	}
	@Override
	public Object clone() throws CloneNotSupportedException {
		MFrame2 temp=(MFrame2)super.clone();
		temp.size=this.size;
		temp.usermode=this.usermode;
		temp.move=move;
		temp.lasty=lasty;
		temp.lastx=lastx;
		temp.winner=winner;
		temp.xforai=xforai;
		temp.yforai=yforai;
		temp.numofmoves=numofmoves;	
		return this;
	}	
}
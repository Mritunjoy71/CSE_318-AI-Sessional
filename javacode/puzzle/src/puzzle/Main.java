package puzzle;

import java.io.*;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Scanner;
import java.util.Set;


public class Main {
	public static int size=0;
	public int level=0;

	public boolean unsolvable(int x,int [][] mat) {
		int l=mat.length;
		int count=0;
		List<Integer> arr=new ArrayList<Integer>();
		for(int i=0;i<l;i++) {
			for(int j=0;j<l;j++) {
				arr.add(mat[i][j]);
				
			}
		}
		//System.out.println(arr.size());
		
		for(int i=0;i<arr.size()-1;i++) {
			for(int j=i+1;j<arr.size();j++) {
				if(arr.get(i)!=0 && arr.get(j)!=0 && arr.get(i)>arr.get(j))
					count++;
				
			}
		}
		//System.out.println(count);
		if(arr.size()%2==1 && count%2==1)
			return true;
		if(arr.size()%2==0 && (x+count)%2==0)
			return true;
		
		
		return false;
		
	}
	
	public void printMatrix(int[][] matrix) {
		for (int i = 0; i < matrix.length; i++) {
			for (int j = 0; j < matrix.length; j++) {
				System.out.print(matrix[i][j] + " ");
			}
			System.out.println();
		}
	}
	
	
	
	public void printPath(Board root) {
		if (root == null) {
			return;
		}
		printPath(root.par);
		level++;
		printMatrix(root.mat);
		System.out.println();
	}
	public int manhattan(int[][] initial, int[][] goal)
	{
		int l=initial.length;
		int sum=0;
		for (int i=0;i<l;i++) {
			for (int j=0;j<l;j++)
			{
				int t=goal[i][j];
				if(t!=0)
				{
					for (int p=0;p<l;p++) 
					{
						for (int q=0;q<l;q++)
						{
							if(initial[p][q]==t)
							{
								sum=sum+Math.abs(i-p)+Math.abs(j-q);
								break;
							}
								
						}
							
					
					}
					
				}
				
			}
		}
		return sum;
		
	}
	
	public int Conflict(int [][] initial ) {
	    int lConflict = 0;
	    for (int i = 0; i < size; i++) {
	        int max1 = -1;
	        int max2 = -1;
	        for (int j = 0; j < size; j++) {
	        	//horizontal conflict
	            int Value1 = initial[j][i];
	            if (Value1 != 0 && Value1 % size == i + 1) {
	                if (Value1 > max1) {
	                    max1 =Value1;
	                } else {
	                    lConflict += 1;
	                }
	            }
	            //vertical conflict
	            int Value2 = initial[i][j];
	            if (Value2 != 0 && Value2 % size == i + 1) {
	                if (Value2 > max2) {
	                    max2 =Value2;
	                } else {
	                    lConflict += 1;
	                }
	            }

	        }

	    }
	    
	    //System.out.println("conflict");
	    return lConflict;
	}
	
	public int hieuristicCost(int h,int[][] initial, int[][] goal) {
		//Hamming distance
		if(h==0) {
			int count = 0;
			//int n = initial.length;
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					if (initial[i][j] != 0 && initial[i][j] != goal[i][j]) {
						count++;
					}
				}
			}
			return count;
			
		}
		//Manhattan distance:
		if(h==1)
		{
			return manhattan(initial,goal);
		}
		//linear conflict
		if(h==2)
		{
			return manhattan(initial,goal)+2*Conflict(initial);
							
		}
		return 0;
		
	}
		
		//left, top, right,bottom
	int [] r= {0,-1,0,1};
	int [] c= {-1,0,1,0};
	
	
	public boolean ValidMove(int x, int y) {
		return (x >= 0 && x < size && y >= 0 && y < size);
	}
	
	
	public void AStarSearch(int h,int [][] init,int [][] goal,int x,int y) {
		Board start = new Board(init, x, y, x, y, 0, null);
		start.hcost = hieuristicCost(h, init, goal);
		//open list
		PriorityQueue<Board> open = new PriorityQueue<Board>(1000, (a, b) -> (a.hcost + a.moves) - (b.hcost + b.moves));
		//close list
		Set<Board> close=new HashSet<Board>();
		open.add(start);
		int explored=0;
		int expanded=0;
		int optcost=0;
		while(!open.isEmpty())
		{
			Board MinB=open.poll();
			close.add(MinB);
			expanded++;
			//optcost+=MinB.moves+MinB.hcost;
			if(MinB.hcost==0)
			{
				printPath(MinB);
				//System.out.println("Optimal cost is : "+optcost);
				System.out.println("Expored nodes are : "+explored);
				System.out.println("Expanded nodes are : "+expanded+"\n");
				System.out.println("Number of levels are : "+level);
				System.out.println("\n\n");
				level=0;
				
				return;
			}
			
			for (int i = 0; i < 4; i++) 
			{	
				//explored++;
	            if (ValidMove(MinB.x + r[i], MinB.y + c[i])) {
	            	Board neighbor = new Board(MinB.mat, MinB.x, MinB.y, MinB.x + r[i], MinB.y + c[i], MinB.moves + 1, MinB);
	    
	            	open.remove(close);
	            	if(!(close.contains(neighbor)))
	            	{
	            		neighbor.hcost = hieuristicCost(h, neighbor.mat, goal);
		            	open.add(neighbor);
		            	explored++;
	            	}
	            	//System.out.println("inside");
	            }
	        }
		}
		
		
		
		
	}
	

	public static void main(String[] args) throws IOException {
		
		File file = new File("/media/mritunjoy/TermSoftwares/javacode/puzzle/src/puzzle/test.txt"); 
		  
		Scanner sc = new Scanner(file); 
	    sc.useDelimiter(" "); 
	    String in=null;
	    int x=0,y=0;
	  
	    in=sc.next();
	    int n=Integer.parseInt(in);
	    //System.out.println(n);
	    
	    size=(int) Math.sqrt(n);
	    //System.out.println(size);
	    
	    int [][] mat=new int [size][size];
	    
	    for(int i=0;i<size;i++) {
	    	for(int j=0;j<size;j++) {
	    		in=sc.next();
	    		mat[i][j]=Integer.parseInt(in);
	    		if(mat[i][j]==0) {
	    			x=i;
	    			y=j;
	    			//System.out.println(x+"  "+y);
	    		}
	    			
	    		//System.out.println(mat[i][j]);
	    	}
	    	
	    }
	    //System.out.println("len"+mat.length);
	    
	    
	   int [][] goal=new int [size][size];
	   int val=1;
	   for(int i=0;i<size;i++)
	   {
		   for(int j=0;j<size;j++)
		   {
			   goal[i][j]=val;
			   if(i==size-1 && j==size-1)
				   goal[i][j]=val;
			   val++;
		   }
	   }
		   
	  
	    	
	    
	    Main main=new Main();
	    main.AStarSearch(1,mat,goal,x,y);
	    if(!main.unsolvable(x,mat)) {
	    	for(int i=0;i<3;i++)
		    {
		    	if(i==0)
		    		System.out.println("Solution for hieuristic hamming ditance\n");
		    	if(i==1)
		    		System.out.println("Solution for hieuristic manhattan ditance\n");	
		    	if(i==2)
		    		System.out.println("Solution for hieuristic linear conflict\n");    			
		    	
		 	   	main.AStarSearch(i,mat,goal,x,y);    			    	
		    }	    	
	    }    
	    else
    		System.out.println("Unsolvable");
	    //System.out.println(main.unsolvable(x,mat));
	    //System.out.println(main.hieuristicCost(0, mat, goal));
	}
}	





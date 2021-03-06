import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.InputMismatchException;
import java.util.Scanner;
import java.util.Stack;
import java.util.StringTokenizer;

public class TSP
{
    private int numberOfNodes;
    private Stack<Integer> stack;
    public TSP()
    {
        stack = new Stack<Integer>();
    }
    public void nearestneighbourtsp(float adjacencyMatrix[][]){
        numberOfNodes = adjacencyMatrix[1].length ;
        int[] visited = new int[numberOfNodes ];
        visited[0] = 0;
        stack.push(1);
        int i,element,dst=0;
        float min = Float.MAX_VALUE;
        float cost=0;
        boolean minFlag = false;
        System.out.print(1 + "\t");
        while (!stack.isEmpty())
        {
            element = stack.peek();
            i = 0;
            min = Integer.MAX_VALUE;
            while (i < numberOfNodes)
            {
                if (adjacencyMatrix[element][i] >=1 && visited[i] == 0)
                {
                    if (min > adjacencyMatrix[element][i])
                    {
                        min = adjacencyMatrix[element][i];
                        dst = i;
                        minFlag = true;
                    }
                }
                i++;
            }
            if (minFlag)
            {
                visited[dst] = 1;
                stack.push(dst);
                System.out.print(dst + "\t");
                minFlag = false;
                cost=cost+adjacencyMatrix[element][dst];
                continue;
            }
            stack.pop();
        }
        System.out.println("\nOptimal cost is : "+cost);
        
    }
    
    public void savingsMehtod(float adjacencyMatrix[][]) {
    	numberOfNodes = adjacencyMatrix[1].length ;
    	int depot=(int)(Math.random() * (((numberOfNodes -1)-0) + 1)) + 0;
    	//System.out.println(depot);
    	float s_matrix[][] = new float[numberOfNodes][numberOfNodes];
    	
    	for (int i = 0; i < numberOfNodes; i++)
        {
            for (int j = 0; j < numberOfNodes; j++)
            {
                if(i==j || i==depot || j==depot) {
                	
                	s_matrix[i][j] = 0;                	
                }
                else {
                	s_matrix[i][j] = (adjacencyMatrix[depot][i]+ adjacencyMatrix[depot][j]-adjacencyMatrix[i][j])/2;
                	
                }
            }
        }
    	
    	
    	
    	
    	
    	
    	
    	
    	
    }
 
	public static void main(String[] args) throws IOException {
		
		File file = new File("/media/mritunjoy/TermSoftwares/javacode/TSP/src/test.txt"); 
		  
		BufferedReader br;
		try {
			br = new BufferedReader(new FileReader(file));
			String st; 
			st = br.readLine();
			int nodes=Integer.parseInt(st);
			//System.out.println(nodes );
			float X[]=new float[nodes];
			float Y[]=new float[nodes];
			
			int count=0;
			int line=0;
			while ((st = br.readLine()) != null) {
				//System.out.println(st);
				StringTokenizer st1 = new StringTokenizer(st, " "); 
			    while (st1.hasMoreTokens()) {
			    	line=Integer.parseInt(st1.nextToken()); 
			    	float co_x=Float.parseFloat(st1.nextToken()); 
			    	X[count]=co_x;
			    	//System.out.println(X[count]);
			    	float co_y=Float.parseFloat(st1.nextToken());			    	
			    	Y[count]=co_y;
			    	//System.out.println(Y[count]);
			    	count++;
			    	
			    }
			}
			
			float adjacency_matrix[][] = new float[nodes][nodes];
         
            for (int i = 0; i < nodes; i++)
            {
                for (int j = 0; j < nodes; j++)
                {
                    adjacency_matrix[i][j] = (float) Math.sqrt((X[i]-X[j])*(X[i]-X[j])-(Y[i]-Y[j])*(Y[i]-Y[j]));
                }
            }
            
            
            System.out.println("the citys are visited as follows");
            TSP tsp = new TSP();
            tsp.nearestneighbourtsp(adjacency_matrix);
            tsp.savingsMehtod(adjacency_matrix);
            
			
		} catch (FileNotFoundException e) {
			
			e.printStackTrace();
		} 
		
		  

		}
    }
    
        


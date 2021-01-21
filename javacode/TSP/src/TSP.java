import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Collections;
import java.util.InputMismatchException;
import java.util.Scanner;
import java.util.Stack;
import java.util.StringTokenizer;
import java.util.Vector;

public class TSP
{
    private int numberOfNodes;
    private Stack<Integer> stack;
    static int[] global_nnh=new int[5];
    static int[] global_nnh_2=new int[10];
    public TSP()
    {
        stack = new Stack<Integer>();
    }
    public void nearestneighbourtsp(double adjacencyMatrix[][]){
        numberOfNodes = adjacencyMatrix[1].length ;
        int[] visited = new int[numberOfNodes ];
        visited[0] = 0;
        stack.push(1);
        int i,element,dst=0;
        double min = Float.MAX_VALUE;
        double cost=0;
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
    
    public void savingsMehtod(double adjacencyMatrix[][]) {
    	
    	int num_of_nodes=adjacencyMatrix.length;
        int[][] serial = new int[5][num_of_nodes*2];
        double[][] saved = new double[num_of_nodes][num_of_nodes];
        double total_distance=0.0;

        for(int i=0;i<num_of_nodes;i++)
        {
            for(int j=0;j<num_of_nodes;j++)
            {
            	adjacencyMatrix[i][j]=adjacencyMatrix[i][j]*2;
            }
        }




        for(int k=0;k<5;k++) {

            for(int i=0;i<num_of_nodes;i++)
            {
                for(int j=0;j<num_of_nodes;j++)
                {
                    saved[i][j]=0;
                }
            }

            int permanent_index=global_nnh[k];

            for (int i = 0; i < num_of_nodes; i++) {

                for (int j = 0; j < num_of_nodes; j++) {

                    if(i==j || i==permanent_index || j==permanent_index)
                    {
                        continue;
                    }

                    saved[i][j]=(adjacencyMatrix[permanent_index][i]+adjacencyMatrix[permanent_index][j]-adjacencyMatrix[i][j])/2;

                }
            }


            int ref=1;
            Vector<Double> v = new Vector();

            for (int i = 0; i < num_of_nodes; i++) {

                for (int j = ref; j < num_of_nodes; j++) {

                    v.add(saved[i][j]);
                }
                ref++;
            }


            Collections.sort(v);
            Collections.reverse(v);

            int ss=0;

            int[] taken=new int[num_of_nodes];

            for(int i=0;i<num_of_nodes;i++)
            {
                taken[i]=0;
            }

            int cc=0,exitt=0;
            ref=1;

            for(int x=0;x<v.size();x++) {

                double nextt=v.get(ss);

                for (int i = 0; i < num_of_nodes; i++) {

                    for (int j = ref; j < num_of_nodes; j++) {

                        if(saved[i][j]==nextt && taken[i]<2 && taken[j]<2)
                        {
                            if((taken[i]==0 && taken[j]==0) || (taken[i]==0 && taken[j]==1) || (taken[i]==1 && taken[j]==0) || ((taken[i]==1 && taken[j]==1) && exitt==num_of_nodes-1))
                            {
                                //System.out.println("lll");
                                serial[k][cc]=i;
                                //System.out.println(serial[k][cc]);
                                serial[k][cc+1]=j;
                                //System.out.println(serial[k][cc+1]);
                                cc=cc+2;
                                taken[i]++;
                                taken[j]++;

                                nextt=v.get(ss);
                                exitt++;
                            }

                        }
                    }
                    ref++;
                }
                if(exitt==num_of_nodes)
                {
                    break;
                }

                ss++;
                ref=1;
            }


            for(int i=0;i<num_of_nodes;i=i+2)
            {
                total_distance=total_distance+adjacencyMatrix[serial[k][i]][serial[k][i+1]]/2;
            }



        }

        System.out.println("Saving Heuristic :");
        System.out.println();

        System.out.println("Tour Cost : "+ total_distance);
        System.out.println();
    	
    	
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
			double X[]=new double[nodes];
			double Y[]=new double[nodes];
			
			int count=0;
			int line=0;
			while ((st = br.readLine()) != null) {
				//System.out.println(st);
				StringTokenizer st1 = new StringTokenizer(st, " "); 
			    while (st1.hasMoreTokens()) {
			    	line=Integer.parseInt(st1.nextToken()); 
			    	double co_x=Float.parseFloat(st1.nextToken()); 
			    	X[count]=co_x;
			    	//System.out.println(X[count]);
			    	double co_y=Float.parseFloat(st1.nextToken());			    	
			    	Y[count]=co_y;
			    	//System.out.println(Y[count]);
			    	count++;
			    	
			    }
			}
			
			double adjacency_matrix[][] = new double[nodes][nodes];
         
            for (int i = 0; i < nodes; i++)
            {
                for (int j = 0; j < nodes; j++)
                {
                    adjacency_matrix[i][j] = (double) Math.sqrt((X[i]-X[j])*(X[i]-X[j])-(Y[i]-Y[j])*(Y[i]-Y[j]));
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
    
        

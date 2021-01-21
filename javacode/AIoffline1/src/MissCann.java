import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;


public class MissCann {
	public static int m=0,c=0;
	
	private static void pathPrint(State finalState) {
		if (null==finalState) {
			System.out.print("\nNo solution found.\n");
		} else {
			System.out.println("State(canLeft,misLeft,canRight,misRight,boatPosition): ");
			State s = finalState;
			List<State> pathway = new ArrayList<State>();
			while(null!=s) {
				pathway.add(s);
				s = s.getParState();
			}

			int level = pathway.size() - 1;
			for (int i = level; i >= 0; i--) {
				s = pathway.get(i);
				if (s.goalstate()) {
					System.out.print(s.toString());
				} else {
					System.out.print(s.toString() + " -> ");
					System.out.println();
				}
			}
			System.out.println();
			System.out.println("Level: " + level);
		}
	}
	
	
	public static void main(String[] args) {
			int mis=0,can = 0,boatcap=0,choice=-1;
			String  str=null;
			while(true) {
				try {
					BufferedReader in=new BufferedReader(new InputStreamReader(System.in));
					System.out.println("Enter number of missionaries: ");
					str=in.readLine();
					mis=Integer.parseInt(str);
					m=mis;
					
					System.out.println("Enter number of cannibals: ");
					str=in.readLine();
					can=Integer.parseInt(str);
					c=can;
					
					System.out.println("Enter boat capacity: ");
					str=in.readLine();
					boatcap=Integer.parseInt(str);
					
					//System.out.println("Enter searching choice (1 for BFS 2 for DFS): ");
				//	str=in.readLine();
					//choice=Integer.parseInt(str);
					//System.out.println("ok done");
					State StartState = new State (can,mis, 0, 0,Position.left,boatcap);
					//List<State> l=StartState.children_generators();
					
					//if(choice==1) {
						System.out.println("\n\n");
						System.out.println("Solution by Breadth First Search\n");
						Search bfs=new Search();
						long startTime=System.nanoTime();
						State finalState=bfs.BFSmethod(StartState);
						long endTime =System.nanoTime();
						long duration =(endTime-startTime);
						pathPrint(finalState);
						System.out.println("execution time is "+duration/1000+" micro seconds\n");
					
					//}
					//else {
						System.out.println("\n\n");
						System.out.println("Solution by Depth First Search\n");
						Search dfs=new Search();
					    startTime=System.nanoTime();
					     finalState=dfs.DFSmethod(StartState);
						//State finalState=dfs.exec(StartState);
						endTime =System.nanoTime();
						long duration2 =(endTime-startTime);
						pathPrint(finalState);
						System.out.println("execution time is "+duration2/1000+" micro seconds\n");
					//}
						if(duration>duration2)
							System.out.println("DFS search takes less execution time than BFS search.");
						else
							System.out.println("BFS search takes less execution time than DFS search.");
						System.out.println("\n\n");
							
					System.out.println("Input again?y/n");
					str=in.readLine();
					if(str.equalsIgnoreCase("n"))
						break;
					
				} catch (IOException e) {
					System.out.println(e);
				}						
			}		
		}
}

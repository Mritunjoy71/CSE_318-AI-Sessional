
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Stack;
public class Search {
	public State BFSmethod(State StartState) {
		List<State> h=new ArrayList<State>();  //explored list
		Queue<State> Q=new LinkedList<State>();
		if(StartState.goalstate()) {
			return StartState;
		}
		Q.add(StartState);
		h.add(StartState);
		State s;
	
		while(true) {
			if(Q.isEmpty()) {
				s= null;
				break;
			}
			else {
				State Qfirst=Q.poll();
				//h.add(Qfirst);
				if(Qfirst.goalstate()) {
					s= Qfirst;
					break;
				}
				else {
					List<State> children=new ArrayList<State>();
					children=Qfirst.children_generators();          //successors list
					for(State child : children) {
						if(!h.contains(child)) {
							if(child.goalstate()) {
								s= child;
							}
						h.add(child);
						Q.add(child);						
						}
					}
				}	
			}
		}
		int n=h.size();
		System.out.println("Explored nodes are "+n);
		System.out.println();
		return s;
		
	}
	
	
	
	public State DFSmethod(State s) {
		List<State> h=new ArrayList<>();  //explored list
		Stack<State> stack=new Stack<>();
		stack.push(s);
		int ex=0;
		
		while(true) {

			if(stack.empty()==true)
			{
				//flag=1;
				System.out.println("Explored nodes are "+ex);
				return null;
				
			}
			else
			{	
				//level--;
				s =stack.peek();
				stack.pop();
				h.add(s);
	            if(s.goalstate())
	            {
	            	System.out.println("Explored nodes are "+ex);
	            	return s;
	            }
	            else {
	            	 List<State> children ;
	 				children=s.children_generators();
	 				children.removeAll(h); //successors list
	 				for(int i = 0; i<children.size();i++) {
	 					State t = children.get(i);
	 					if(t.goalstate()) {
	 						//flag=1;
	 						System.out.println("Explored nodes are "+ex);
	 						return t;
	 					}
	 					stack.push(t); 	
	 					h.add(t);
	 					ex++;
	 					
	 				}
	            	
	            }
				
			}
			
            
		}
		//end while	
	}
}










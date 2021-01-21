import java.util.ArrayList;
import java.util.List;


enum Position{left,right}
public class State {
	private int canLeft;
	private int misLeft;
	private int canRight;
	private int misRight;
	private Position boat;
	private State parState;
	private int boatcap;
	
	public State(int canLeft, int misLeft, int canRight, int misRight,Position boat,int boatcap) {
		this.canLeft = canLeft;
		this.misLeft = misLeft;
		this.canRight = canRight;
		this.misRight = misRight;
		this.boat = boat;
		this.boatcap =boatcap;
	}
	public State() {
		
	}
	
	public int getCanLeft() {
		return canLeft;
	}



	public void setCanLeft(int canLeft) {
		this.canLeft = canLeft;
	}



	public int getMisLeft() {
		return misLeft;
	}



	public void setMisLeft(int misLeft) {
		this.misLeft = misLeft;
	}



	public int getCanRight() {
		return canRight;
	}



	public void setCanRight(int canRight) {
		this.canRight = canRight;
	}



	public int getMisRight() {
		return misRight;
	}



	public void setMisRight(int misRight) {
		this.misRight = misRight;
	}



	public Position getBoat() {
		return boat;
	}



	public void setBoat(Position boat) {
		this.boat = boat;
	}



	public State getParState() {
		return parState;
	}



	public void setParState(State parState) {
		this.parState = parState;
	}



	public boolean validstate() {
		if(misLeft <= MissCann.m && canLeft <=MissCann.c && misRight<=MissCann.m && canRight<= MissCann.c &&  misLeft>=0 && canLeft >=0 && misRight >=0 && canRight>=0 
				&&(misLeft==0 || misLeft >= canLeft) && (misRight==0 || misRight >= canRight)) {
			return true;
		}
		return false;
	}
	
	public boolean goalstate() {
		if(canLeft==0 && misLeft==0) {
			return true;
			
		}
		return false;
		
	}
	
	public List<State> children_generators(){
		List<State> children =new ArrayList<State>();
		if(boat==Position.left) {
			for(int i=0;i<=this.boatcap;i++) {
				for(int j=this.boatcap-i;j>=0;j--) {
					if(!(i==0 && j==0)) {
						//System.out.println("("+i+","+j+")");
						State state = new State(canLeft-i,misLeft-j,canRight+i,misRight+j,Position.right,boatcap);
						if(state.validstate()) {
							state.setParState(this);
							children.add(state);
						}
					}	
						
				}
					
			}
		}
		else {
			for(int i=0;i<=this.boatcap;i++) {
				for(int j=this.boatcap-i;j>=0;j--) {
					if(!(i==0 && j==0)) {
						State state = new State(canLeft+i,misLeft+j,canRight-i,misRight-j,Position.left,boatcap);
						if(state.validstate()) {
							state.setParState(this);
							children.add(state);
						}
					}	
						
				}
					
			}
		}
		
		
		return children;
		
	}

	@Override
	public String toString() {
		if(!this.goalstate())
		{
			return "{" + canLeft + ", " + misLeft + ", " + canRight + ", "
					+ misRight + ", " + boat + "}"+" Carry("+Math.abs(this.canLeft-this.canRight)+","+Math.abs(this.misLeft-this.misRight)+")";
		}
		else
		{
			return "{" + canLeft + ", " + misLeft + ", " + canRight + ", "
					+ misRight + ", " + boat + "}";
			
		}
	}

	@Override
	public boolean equals(Object obj) {
		if (!(obj instanceof State)) {
			return false;
		}
		State s = (State) obj;
        return (s.canLeft == canLeft && s.misLeft == misLeft
        		&& s.boat == boat && s.canRight == canRight
        		&& s.misRight == misRight);
	}
	

}

package puzzle;

public class Board {
	public int x,y,hcost,moves;
	public int [][] mat;
	public Board par;
	public void swap(int x,int y,int newx,int newy) {
		int temp=this.mat[x][y];
		this.mat[x][y]=this.mat[newx][newy];
		this.mat[newx][newy]=temp;
		
	}
	public Board(int[][] mat, int x, int y, int newx, int newy, int moves, Board par) {
		this.par = par;
		
		this.mat = new int[mat.length][];
		for (int i = 0; i < mat.length; i++) {
			this.mat[i] = mat[i].clone();
		}
		
		this.hcost = Integer.MAX_VALUE;
		this.moves = moves;
		swap(x,y,newx,newy);		
		this.x = newx;
		this.y = newy;
	}

}

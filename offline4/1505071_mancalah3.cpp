#include<bits/stdc++.h>
#define MIN 1
#define MAX 0
using namespace std;
void printboard(int board[]);
int askforselection(int board[]); 
bool checkboard(int board[]);
bool takeMove(int board[], int spotinarray, int human_or_comp); 
int findacross(int ending);
bool checkforone(int board[]); 
int findone(int board[]); 
typedef struct move{ 
	int binNum;
	int score;
} Move;
Move minmax(int board[], int d, int maxD, int minOrMax, int alpha, int beta); 
int computerChooseMove(int board[],int choice, int maxD);
int evalFunction(int board[], int minOrMax); 
int checkform(int board[], int choice);

int turn;
int main(){
    srand(time(0)); 
    int m;
	int selected =  rand() % 2; 
	cout<<"Toss:enter 1 for head,0 for tail\n";
	int input; 
	cin >> input;
	if(selected == input){
		turn = 0;
	}
	else{ // comp1 goes first.
		turn = 1;
	}
	int maxDepth = 2;
	cout<<"enter max depth\n";
	cin >> maxDepth;
	int choiceofmove = -5;
	int board[14] = {4,4,4,4,4,4,0,4,4,4,4,4,4,0}; 
	bool gameOver = false; 
	bool onlyone = false; 
	bool doesntmatter = false;
	int one;
	while (!gameOver){

		if (turn == MIN){// computer1 move
			onlyone = checkforone(board);
			if(onlyone){
				//cout << "Only one move possible so forced to make" << endl;
				one = findone(board);
				m = one;
			}
			else{
				m = computerChooseMove(board,MAX ,maxDepth);//otherwise use the minmax function to find the best move, given a certain depth.
			}
			cout << "Computer1 moved at "<< m << ", resulting in board below "<< endl;
			doesntmatter = takeMove(board, m, MAX);
			//printboard(board); 
			gameOver=checkboard(board); 
			if(gameOver){
				break;
			}
			else{
				turn = 0; 
			}
		}
		else{ //comp2 move.
			onlyone = checkforone(board);
			if(onlyone){
				//cout << "Only one move possible so forced to make" << endl;
				one = findone(board);//find location of move.
				m = one;
			}
			else{
				m = computerChooseMove(board,MIN, maxDepth);//otherwise use the minmax function to find the best move, given a certain depth.
			}
			cout << "Computer2 moved at "<< m%6 << ", resulting in board below "<< endl;
			doesntmatter = takeMove(board, m%6, MIN);
			//printboard(board); //print the board.
			gameOver=checkboard(board); 
			if(gameOver){
				break;
			}
			else{
				turn = 1; 
			}
		}
	}
	cout << "Game is over" << endl;
	if (board[6] > board[13]){
		cout << "Computer2 wins!" << endl;
	}
	else if (board[13] > board[6]){
		cout << "Computer1 wins!" << endl;
	}
	else {
		cout << "Game is a tie!" << endl;
	}
	//printboard(board);
}

bool takeMove(int board[], int choice, int minOrmax){
	int avoid;
	if (MAX == minOrmax){ //comp playing
		avoid = 6;
	}
	else {
		avoid = 13;
	}
	int picked = board[choice]; 
	int next = choice + 1; 
	if(next == avoid){ 
		if (avoid == 13){
			next = 0; 
		}
		else if( avoid == 6){
			next = 7;
		}
	}
	board[choice] = 0;
	bool changed = false;
	for( ; picked > 0 ; picked--){ 
		if(next == avoid){
			if (avoid == 13){
				changed = true; 
				next = 0; 
			}
			else {
				changed = true; 
				next = 7;
			}
		}
		int currentinnext = board[next]; 
		board[next] = currentinnext + 1 ; 
		int test = picked - 1;
		if (test >= 0){
			if(changed){
				next++; 
				if(next == 14){ 
					next = 0;
				}
			}
			else if (picked == 1 && currentinnext == 0){
					break; 
			}
			else{
				next++;
				if(next == 14){
					next = 0;
				}
			}
		}
	}
	int ending = next-1;
	if (ending == -1){ 
		ending = 13;
	}
	if(ending != 13 || ending != 6){ 

		if (MIN == minOrmax && board[ending] == 1 && ending > -1 && ending < 6){
				int across = findacross(ending);
				if (board[across] > 0){
					board[6] = board[6] + 1 + board[across];
					board[ending] = 0;
					board[across] = 0; 
					return true;
				}
				else{
					return false;
				}
		}
		if (MAX == minOrmax && board[ending] == 1 && ending > 6 && ending < 13){ // for comp1
				int across = findacross(ending); 
				if (board[across] > 0){
					board[13] = board[13] + 1 + board[across]; 
					board[ending] = 0; 
					board[across] = 0; 
					return true;
				}
				else{
					return false;
				}
		}
	}
	else{
		return false;
	}
	return false;
}
Move minmax(int board[], int d, int maxD, int minOrMax, int alpha, int beta) {
	Move mTemp, m;
	int board2[14];
	bool check;
	bool doesntmatter;
	check = checkboard(board);
	if (check){ 
		if (MIN == minOrMax){ // Computer is playing
			m.score = INT_MIN;
			return m;
		}
		else if (MAX == minOrMax){
			m.score = INT_MAX;
			return m;
		}
	}
	else  if (d == maxD)  {
		m.score = evalFunction(board, minOrMax);
		return m;
	}
	else {
		if (minOrMax == MIN) { // MINIMizing player
			m.score= INT_MAX;
			//m.binNum = -1;
			for (int i = 0; i <= 5; i++) {
				if (board[i] != 0) {
					for(int j = 0; j < 14 ; j++){
						board2[j] = board[j];
					}
					doesntmatter = takeMove(board, i, minOrMax);
					mTemp = minmax(board, d+1, maxD, MAX, alpha, m.score);
					if( m.score <= alpha){
						break;
					}
					if (mTemp.score < m.score) { 
						m.score = mTemp.score; 
						m.binNum = i; //bin number will be current index
						//less than because trying to minimize
					}

					for(int k = 0; k < 14 ; k++){
						board[k] = board2[k];
					}
				}
			}
			return m;
		}
		else if (minOrMax == MAX) //comp1
			{
			m.score = INT_MIN;
			//m.binNum = -1;
			for (int i = 7; i <= 12; i++) {
				if (board[i] != 0) {
					for(int j = 0; j < 14 ; j++){
						board2[j] = board[j];
					}
					doesntmatter = takeMove(board, i, minOrMax);  //change board state to next tentative move
					mTemp = minmax(board, d+1, maxD, MIN, m.score, beta); //recursive call minmax with m.score(as alpha) and beta
					if(m.score > beta){
						break;
					}
					if (mTemp.score >= m.score) {
						m.score = mTemp.score;
						m.binNum = i;
						//greater than because trying to maximize
					}
					for(int k = 0; k < 14; k++){
						board[k] = board2[k];
					}
				}
			}
			return m;
		}	
	}
}

int computerChooseMove(int board[], int choice,int maxD)
{
	Move m;
	if (choice==MAX)
	{
		int alpha = INT_MIN;
		int beta = INT_MAX; 
		m = minmax(board, 0, maxD, MAX, alpha, beta);
	}
	else{
		int alpha = INT_MIN;
		int beta = INT_MAX; 
		m = minmax(board, 0, maxD, MIN, alpha, beta);
	}
	
	return m.binNum; 
}

int evalFunction(int board[], int minOrMax){ 
	int board2[14];
	bool checkempty;
	for(int j = 0; j < 14 ; j++){
		board2[j] = board[j];
	}
	float w1,w2,w3;

	w1=145;
	w2=345;
	w3=211;


	float comp1side =board[0] + board[1] + board[2] + board[3] + board[4] + board[5]; 
	float comp1mancala = board[6]; 
	float comp2side = board[7] + board[8] + board[9] + board[10] + board[11] + board[12];
	float comp2mancala = board[13];
	int valueofboard=int(((comp1mancala-comp2mancala)*w1+(comp1side-comp2side)*w2)+0.5);
	if (turn==MAX)
	{
		for (int i = 0; i <= 5; i++) {
			checkempty = takeMove(board2, i, minOrMax);
			if(checkempty){
				int acrosslocation = findacross(i); 
				int acrosspieces = board2[acrosslocation]; 
				valueofboard = valueofboard + (acrosspieces*w3);
			}
		}
	}
	else{
		for (int i = 7; i <= 12; i++) { 
			checkempty = takeMove(board2, i, minOrMax); 
			if(checkempty){
				int acrosslocation = findacross(i);
				int acrosspieces = board2[acrosslocation];
				valueofboard = valueofboard + ((acrosspieces*w3)); 
			}
		}

	}
	
	return valueofboard; 
}


bool checkboard(int board[]){
	int bottomnumempty = 0; 
	for (int i = 0; i < 6;i++){
		if(board[i] == 0){
			bottomnumempty++;
		}
	}
	if (bottomnumempty == 6){
		board[13] = board[13] + board[12] +board[11] +board[10] +board[9] + board[8] +board[7];
		for(int i = 7; i < 13; i++){
			board[i] = 0;
		}
		return true; 
	}
	int topnumempty = 0;
	for (int i = 7; i < 13;i++){
		if(board[i] == 0){
			topnumempty++;
		}
	}
	if (topnumempty == 6){
		board[6] = board[6] + board[5] +board[4] +board[3] +board[2] + board[1] +board[0];
		for(int i = 0; i < 6; i++){
			board[i] = 0;
		}
		return true;
	}
	return false;
}

bool checkforone(int board[]){
	int check = 0;
	for (int i = 7; i <= 12; i++) {
		if(board[i] > 0){
			check++;
		}
	}
	if(check == 1){ 
		return true;
	}
	else{
		return false;
	}
}
int findone(int board[]){
	int check = 0;
	for (int i = 7; i <= 12; i++) { 
		if(board[i] > 0){
			check = i ;
			return check;
		}
	}
	return check;
}

void printboard(int board[]){
	cout << "       |  12  |  11  |  10  |   9  |   8  |   7  |" << endl;
	cout << "________________________________________________________" << endl;
	cout << "|" << "      | (" << std::setfill('0') << std::setw(2) << board[12] << ") | " ;
	cout << "(" << std::setfill('0') << std::setw(2)<< board[11] ;
	cout << ") | " << "(" << std::setfill('0') << std::setw(2)<<  board[10] << ") | ";
	cout << "(" << std::setfill('0') << std::setw(2)<<  board[9] << ") | " ;
	cout << "(" << std::setfill('0') << std::setw(2)<<  board[8] << ") | " ;
	cout <<"(" << std::setfill('0') << std::setw(2) << board[7] << ") |      |" << endl;

	cout << "|      |‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|      |" << endl;

	cout << "|  " << std::setfill('0') << std::setw(2) << board[13] << "  |";
	cout << "                                         ";
	cout << "|  " << std::setfill('0') << std::setw(2) << board[6] << "  |" << endl;
	cout << "|      |_________________________________________|      |" << endl;

	cout << "|" << "      | (" << std::setfill('0') << std::setw(2) << board[0] << ") | " ;
	cout << "(" << std::setfill('0') << std::setw(2)<< board[1] ;
	cout << ") | " << "(" << std::setfill('0') << std::setw(2)<<  board[2] << ") | ";
	cout << "(" << std::setfill('0') << std::setw(2)<<  board[3] << ") | " ;
	cout << "(" << std::setfill('0') << std::setw(2)<<  board[4] << ") | " ;
	cout <<"(" << std::setfill('0') << std::setw(2) << board[5] << ") |	|" << endl;

	cout << "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾" <<endl;
	cout << "       |   0  |   1  |   2  |   3  |   4  |   5  |" << endl;
	cout << "\n";
}

int findacross(int ending){ 
	int across = -555;

	if (ending == 0){
		across = 12;
	}
	else if (ending == 1){
		across = 11;
	}
	else if (ending == 2){
		across = 10;
	}
	else if (ending == 3){
		across = 9;
	}
	else if (ending == 4){
		across = 8;
	}
	else if (ending == 5){
		across = 7;
	}
	else if (ending == 7){
		across = 5;
	}
	else if (ending == 8){
		across = 4;
	}
	else if (ending == 9){
		across = 3;
	}
	else if (ending == 10){
		across = 2;
	}
	else if (ending == 11){
		across = 1;
	}
	else if (ending == 12){
		across = 0;
	}
	return across;
}


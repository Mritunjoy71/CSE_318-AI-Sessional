#include<bits/stdc++.h>
#define MIN 1
#define MAX 0
using namespace std;
int turn,m,selected,input,maxDepth;
int choiceofmove = -5; //for holding human move.
int board[14] = {4,4,4,4,4,4,0,4,4,4,4,4,4,0}; 
bool gameOver = false; 
int onlyone = 0; //  only one move possible.index
bool doesntmatter = false;//not important for takingthemove, but used in eval function.

typedef struct move{ //a struct for holding the score of the board and the bin location of the causing bin movement
	int binNum;
	int score;
} Move;


int checkforone(int mboard[]){
	int check = 0;
	int pos=0;
	for (int i = 7; i <= 12; i++) {
		if(mboard[i] > 0){
			check++;
			pos=i; 
		}
	}
	if(check == 1){ 
		return pos; 
	}
	else{
		return 0; 
	}
}

bool checkboard(int mboard[]){
	int bottom = 0; 
	int top= 0;
	for (int i = 0; i < 6;i++){
		if(mboard[i] == 0){
			bottom++; 
		}
	}
	if (bottom == 6){
		mboard[13] = mboard[13] + mboard[12] +mboard[11] +mboard[10] +mboard[9] + mboard[8] +mboard[7];
		for(int i = 7; i < 13; i++){
			mboard[i] = 0;
		}
		return true;
	}

	for (int i = 7; i < 13;i++){
		if(mboard[i] == 0){
			top++;
		}
	}
	if (top == 6){
		mboard[6] = mboard[6] + mboard[5] +mboard[4] +mboard[3] +mboard[2] + mboard[1] +mboard[0];
		for(int i = 0; i < 6; i++){
			mboard[i] = 0;
		}
		return true;// empty
	}
	return false;
}


int findacross(int ending){ //find across bin
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


bool takeMove(int mboard[], int choice, int minOrmax){
	int avoid;
	if (MAX == minOrmax){
		avoid = 6;
	}
	else {
		avoid = 13;
	}
	int picked = mboard[choice]; 
	int next = choice + 1; 
	if(next == avoid){ 
		if (avoid == 13){
			next = 0; 
		}
		else if( avoid == 6){
			next = 7;
		}
	}
	mboard[choice] = 0;
	bool changed = false;//if the for loop runs into 13 or 6, this make sure that it doesn't increment twice.
	for( ; picked > 0 ; picked--){ 
		if(next == avoid){
			if (avoid == 13){
				changed = true; //next is where 1 marble will be placed. changed is true because it avoids incrementing twice
				next = 0; 
			}
			else {
				changed = true; 
				next = 7;
			}
		}
		int currentinnext = mboard[next]; 
		mboard[next] = currentinnext + 1 ; 
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
	int ending = next-1;// location of ending bin
	if (ending == -1){ 
		ending = 13;
	}
	else if (ending == 7){
		ending = 6;
	}
	if (MAX == minOrmax && ending == 6){ //this is a special condition that had to be hardcoded
		ending = ending + 1;
	}
	if (MAX == minOrmax){ //Increment ending to be used later
		ending = ending + 1; //for comp
	}
	if (MIN == minOrmax){//Increment ending to be used later
		ending = ending + 1; //for human
	}
	if(ending != 13 || ending != 6){

		if (MIN == minOrmax && mboard[ending] == 1 && ending > -1 && ending < 6){ // for human
				int across = findacross(ending); 
				if (mboard[across] > 0){
					mboard[6] = board[6] + 1 + board[across]; 
					mboard[ending] = 0;
					mboard[across] = 0; 
					return true;
				}
				else{
					return false;
				}
		}
		if (MAX == minOrmax && mboard[ending] == 1 && ending > 6 && ending < 13){ // for comp
				int across = findacross(ending); 
				if (mboard[across] > 0){
					mboard[13] = mboard[13] + 1 + mboard[across]; 
					mboard[ending] = 0; 
					mboard[across] = 0; 
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


int evalFunction(int mboard[], int minOrMax){
	int board2[14];
	bool checkempty;
	for(int j = 0; j < 14 ; j++){
		board2[j] = mboard[j]; 
	}
	float humanside = (mboard[0] + mboard[1] + mboard[2] + mboard[3] + mboard[4] + mboard[5])*0.45; 
	float humanmancala = (mboard[6]) * 3.45; 
	float human = humanside + humanmancala;
	float compside = (mboard[7] + mboard[8] + mboard[9] + mboard[10] + mboard[11] + mboard[12])*0.45;
	float compmancala = (mboard[13]) * 3.45;
	float comp = compside + compmancala;
	float difference_board = comp - human; 
	int valueofboard = int(difference_board + 0.5); 
	for (int i = 0; i <= 5; i++) { //for each possible move for human
	checkempty = takeMove(board2, i, minOrMax); // landing in an empty bin
		if(checkempty){ 
			int acrosslocation = findacross(i); 
			int acrosspieces = board2[acrosslocation]; 
			valueofboard = valueofboard + ((acrosspieces*0.5)*-1);//not interested so negative
		}
	}
	for (int i = 7; i <= 12; i++) { //for each possible move for comp
	checkempty = takeMove(board2, i, minOrMax);
		if(checkempty){
			int acrosslocation = findacross(i);//find the location of that
			int acrosspieces = board2[acrosslocation];
			valueofboard = valueofboard + ((acrosspieces*0.5)); //interested ,positive
		}
	}
	return valueofboard; 
}

Move minmax(int mboard[], int d, int maxD, int minOrMax, int alpha, int beta){
	Move mTemp, m;
	int board2[14];
	bool check;//one side is empty
	bool doesntmatterL;//return bool from takemove, for eval function and doens't matter here.
	check = checkboard(mboard);

	if (check){ 
		if (MIN == minOrMax){ // Computer is playing
			m.score = INT_MIN;
			m.binNum = -1;
			return m;
		}
		else if (MAX == minOrMax){
			m.score = INT_MAX;
			m.binNum = -1;
			return m;
		}
	}
	else  if (d == maxD)  {
		m.score = evalFunction(mboard, minOrMax); //evaluate the current board state and give a score.
		m.binNum = -1;
		return m;
	}
	else{
		if (minOrMax == MIN) { // MINIMizing player
			m.score= INT_MAX;
			m.binNum = -1;
			for (int i = 0; i <= 5; i++) { //user turn 
				if (mboard[i] != 0) {
					for(int j = 0; j < 14 ; j++){
						board2[j] = mboard[j];
					}
					doesntmatterL = takeMove(mboard, i, minOrMax);  //change board state to next tentative move
					mTemp = minmax(board, d+1, maxD, MAX, alpha, m.score); 
					if( m.score <= alpha){
						break;
					}
					if (mTemp.score < m.score) {
						m.score = mTemp.score;
						m.binNum = i; //current index
						//less than because trying to minimize
					}

					for(int k = 0; k < 14 ; k++){
						mboard[k] = board2[k];
					}
				}
			}
			return m;
		}

	}

}


int computerChooseMove(int mboard[], int maxD)
{
	Move m;
	int alpha = INT_MIN; 
	int beta = INT_MAX; 
	//cout << "Initial Call for minmax just occurred" << endl;
	m = minmax(mboard, 0, maxD, MAX, alpha, beta); 
	return m.binNum; //best bin
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


int askforselection(int mboard[]){
	int selection;
	cout << "What move would you like to make? Your mancala is to the right." << endl;
	cout << "Please enter either 0,1,2,3,4 or 5." << endl;
	cin >> selection;
	while (selection > 5 || selection < 0 || mboard[selection]==0){ //make sure valid selection
		cout << "Wrong selection. Pit is either empty or out of range" << endl;
		cout << "What move would you like to make?" << endl;
		cout << "Please enter the slot number " << endl;
		cin >> selection;
	}
	return selection;
}


int main(){
	srand(time(0));
	selected =  rand() % 2; //random number generator between 0 and 1
	cout<<"Toss:enter 1 for head,0 for tail\n";
	cin>>input;
	if(selected == input){
		turn = 0;  //human first move
	}
	else{ // comp  first move
		turn = 1;
	}

	cout<<"enter max depth\n";
	cin>>maxDepth;

	while(!gameOver){
		if (turn==MIN)
		{
			onlyone = checkforone(board);
			if (onlyone!=0)
			{
				cout << "Only one move possible so forced to make\n";
				m = onlyone;//set the found location as the move			
			}
			else{
				m = computerChooseMove(board, maxDepth);
			}

			cout << "Computer1 moved at "<< m << ", resulting in board below "<< endl;
			doesntmatter = takeMove(board, m, MAX);
			printboard(board); //print the board.
			gameOver=checkboard(board); //see if the game is over
			if(gameOver){
				break;
			}
			else{
				turn = 0; //switch turn so that the human can go.
			}

		}
		else{
			onlyone = checkforone(board);
			if (onlyone!=0)
			{
				cout << "Only one move possible so forced to make\n";
				m = onlyone;//set the found location as the move			
			}
			else{
				m = computerChooseMove(board, maxDepth);
			}

			cout << "Computer2 moved at "<< m << ", resulting in board below "<< endl;
			doesntmatter = takeMove(board, m, MIN);
			printboard(board); //print the board.
			gameOver=checkboard(board); //see if the game is over
			if(gameOver){
				break;
			}
			else{
				turn = 1; //switch turn so that the human can go.
			}
		}
	}





	return 0;
}
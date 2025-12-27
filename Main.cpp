#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h> // getch() 
#include <ctime>
#include <cstdlib> // rand() 
using namespace std ;

/// Website used for Ascii art https://patorjk.com/software/taag/#p=display&f=3D+Diagonal&t=2D+WARSHIP+BATTLE&x=none&v=4&h=4&w=80&we=false	





// Functions Protoypes 
int ship_placement_choice() ; // Ask the user how he wanna place his ships random or manual
void showGameMenu() ;
void setColor(int textColor, int bgColor) ;
void clearScreen() ;
void updateScore(int &score) ;
void Instructions() ;
void clearBoard(char board[10][10]) ;
void init_fake_bool(bool arr[10][10]) ;
void ask_ship_color() ;
void displayResult(int player1Score , int player2Score) ;
void displayResult_2(int player1Score , int computerScore) ;
void initializeBoard(char board[10][10]); 
void printBoard(char board[10][10] , bool hideShips) ;
int ship_placement_choice() ;
int give_ship_size(int ship_op) ;
int give_ship_size(int ship_op) ;
void setManuallyShips_V01(char board[10][10] , int ship_size) ;
void setRandomShips_V01(char board[10][10] , int ship_size) ;
void setRandomShips(char board[10][10]); 
void  setManualships(char board[10][10]) ;
void Ship_Placement(int ship_setup_choice  , char board[10][10]) ;
void vsPlayer_Ship_Placement() ;
void vsPlayer_Board_display(char board1[10][10] , char board2[10][10]  , int current_turn) ;
int get_ships_data(char player_board[10][10] , int turn) ;
void do_fake_bool_work(char player_board[10][10] , int turn) ;
void vsPlayer(char board1[10][10]  , char board2[10][10]) ;
void vsPlayer(char board1[10][10]  , char board2[10][10]) ;
void PlayervsPlayer() ;
void do_fake_bool_work_2(char player_board[10][10] , int turn) ;
void computerAttack(char playerBoard[10][10], int &computerScore) ;
void vsComputer_Board_display(char board1[10][10] , char board2[10][10]  , int current_turn) ;
void setRandomships(char board[10][10]) ;
void placement(char grid[10][10],int row,int col,int size,bool ver) ;
bool placing(char grid[10][10],int row,int col,int size, bool ver) ; 
void PlayervsPlayer() ;
void manualplacing(char grid[10][10], string ships[], int sizes[], int numship) ;
void Mode2_ship_placement() ;
 int get_ships_data_Mode_2(char player_board[10][10] , int turn) ;
 void vsComputer_Excecute(char playerBoard[10][10], char computerBoard[10][10]) ;
 void vsComputer() ;
 void startNewGame(); 
 void showLeaderboard(const string playerNames[], const int scores[], int totalPlayers) ;
 void showGameMenu() ;

// The User Enter his position to attack 
// I keep track of the total number of attacks meaning user can end his attack anytime + position (input validation too)
// I also have to keep track if the position user entered already been hit before or not
// keep all the values in the array and after input is done then mark the postion if the boolean value at that point
// is true mark it X else O 

// Now the main point is how to mark them pink color when the ship is destroyed
// I will check throught the location  obtained to check if some ship is sinked if yes  get their cordinates
// Now when coloring them in the loop if my ship is lies in the range of the sanked then pink color it and also 
// check through the boolean array to determine which ship sank and which did'nt


int Player1_Score = 0  ;
int Player2_Score = 0 ;
int Player3_Score = 0 ;
int computer_Score = 0 ;

int ship_color1 ; 

string player1_name ; 
string player2_name ;
string player3_name ; 

// Color codes
const int BLACK = 0;
const int BLUE = 1;
const int GREEN = 10;
const int CYAN = 11;
const int RED = 4;
const int MAGENTA = 13;
const int YELLOW = 14;
const int WHITE = 15;
const int LIGHTBLUE = 9 ;
const int LIGHTCYAN = 11 ; 
const int DARKRED = 12 ;


void setColor(int textColor, int bgColor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), bgColor * 16 + textColor);
}

void clearScreen()
{
	system("CLS") ;
}


bool _attacked_ = false ;
void updateScore(int &score)
{
	if(_attacked_) score += 10 ;
	else   score -= 1 ;
}

void Instructions()
 {
 	cout<<"------------------------------------------------"<<endl;
 	cout<<"                INSTRUCTIONS                       "<<endl;
 	cout<<"------------------------------------------------"<<endl;
 	cout<<"1. Place your ships on the board."<<endl;
 	cout<<endl;
 	cout<<"2.You and computer take turns firing shots."<<endl;
 	cout<<endl;
 	cout<<"3.'O' means MISS,'X'means HIT."<<endl;
 	cout<<endl;
 	cout<<"4. Sink all enemy ships to win !"<<endl;
 	cout<<endl;
 	cout<<"5.Your score is based on accuracy and speed."<<endl;
 	
 	setColor(WHITE , RED) ;
 	cout << "Press any Button to go back to main Menu\n" ;
 	setColor(WHITE  , BLACK) ;
 	getch() ;
 	clearScreen() ;
 	showGameMenu() ;
 }



//clearboard 
void clearBoard(char board[10][10]) {
    for (int r = 0; r < 10; r++)
        for (int c = 0; c < 10; c++)
            board[r][c] = '~';
}

bool fake_bool_1[10][10] ;
bool fake_bool_2[10][10] ;
void init_fake_bool(bool arr[10][10])
{
	for(int st = 0 ;  st <= 10  -  1 ; st += 1)
	{
		for(int st2  = 0 ;  st2  <= 10 -  1 ; st2 += 1)
		{
			arr[st][st2] = false ;
		}
	}
}


char global_boat_pass[10][10] ;

char board[10][10] ;
bool ships[5] = {true , true , true , true , true} ;
int user_choice_for_ship ; // making it global so i can use it revert the not chosen ship back to normal
 
 // if i know the x and  , y cordinates + direction + size i can track that ship on board
 // and the below two array will store this stuff
char global_board_pass_for_location[5][4] ;  // this is the board which i  will use in the to store the bushra player 
// and computer code and then copy paste them to the my original code
char player1_ship_location[5][4] ; // 5 boats row , column , ship_size , direction
char player2_ship_location[5][4] ; // Same for player 2 
char player3_ship_location[5][4]; // for player from the bh code
char comp_ship_location[5][4] ; // for the comp in the bh code
int st_idx_for_ship_location ;
char player_1_board[10][10] ;
char player_2_board[10][10] ;


char track_player_turn ; // This global variable cause i have to use between multiple function
// will track  which player turn it is if is player 1 turn then i will assign it '1' so my if condition 
// inside the manually setup function will check that weather it is '1' or '2'if '1' then it means it have to
// keep the player 1 ship locations inside the player 1 ship location variable then after it is done for player 1 
// then comes player 2  i will set the st_idx_for_ship_location back to zero and make the track_plyer '2' so it will 
// now put the variables inside the  player2_ship_location


// to clear the screen i can normally use the function only also lol

void ask_ship_color()
{
	/////////////////////Determinig the color////////////////////////////
		cout << "Enter your ship color\n"	 ;
		setColor(CYAN  , BLACK) ;
		cout << "1.Cyan\n" ;
		setColor(WHITE  , BLACK) ;
		setColor(YELLOW  , BLACK) ;
		cout << "2.Yellow\n" ;
		setColor(WHITE  , BLACK) ;
		setColor(MAGENTA  , BLACK) ;
		cout << "3.Magenta\n" ;
		setColor(WHITE  , BLACK) ;
		setColor(GREEN  , BLACK) ;
		cout << "4.Green\n" ;
		setColor(WHITE  , BLACK) ;
		cout << "Choice : " ;
		int color_cho ;  
		cin >> color_cho ; 
		while(color_cho < 1 || color_cho  > 4)
		{
			cout << "Enter your correct color\n"; 
			cin >> color_cho ; 
		}
		if(color_cho == 1)
		{
			ship_color1 = CYAN ; 
		}
		else if(color_cho == 2)
		{
			ship_color1  = YELLOW ;
		}
		else if(color_cho == 3)
		{
			ship_color1  = MAGENTA ;
		}
		else 
		{
			ship_color1 = GREEN  ;
		}
}

void displayResult(int player1Score , int player2Score)
{
	clearScreen() ;
	ofstream file_output ;
	file_output.open("highscore.txt" , ios::out|ios::app) ;
	if(!file_output.is_open())
	{
		cout << "Error in File Opening , not saving the result\n\n" ;
	}
	setColor(RED , WHITE) ;
	if(player1Score > player2Score)
	{
		cout << "!!!!!!!!!!!!      PLAYER 1 WON  !!!!!!!!!!!!!!!\n" ;
		setColor(WHITE , BLACK) ;
		cout << "Player Name : " << player1_name << endl ; 
		cout << "Score : " << player1Score ;
		file_output << player1_name << " " << player1Score ;
		
	}
	else if(player1Score < player2Score)
	{
		cout << "!!!!!!!!!!!!      PLAYER 2 WON  !!!!!!!!!!!!!!!\n" ;
		setColor(WHITE , BLACK) ;
		cout << "Player Name : " << player2_name << endl ; 
		cout << "Score : " << player2Score ;
		file_output << player2_name << " " << player2Score ;
	}
	else
	{
		cout << "Draw!\n" ;
	}
	setColor(WHITE , BLACK) ;
	file_output.close() ;
}

// Set text and background color in Windows console made by sir so will use it gratefully yeahhhh


void displayResult_2(int player1Score , int computerScore)
{
	clearScreen() ;
	ofstream file_output ;
	file_output.open("highscore.txt" , ios::out|ios::app) ;
	if(!file_output.is_open())
	{
		cout << "Error in File Opening , not saving the result\n\n" ;
	}
	setColor(WHITE , RED) ;
	if(player1Score > computerScore)
	{
		cout << "!!!!!!!!!!!!      PLAYER  WON  !!!!!!!!!!!!!!!\n" ;
		setColor(WHITE , BLACK) ;
		cout << "Player Name : " << player3_name << endl ; 
		cout << "Score : " << player1Score ;
		file_output << player3_name << " " << player1Score ;
	}
	else if(player1Score < computerScore)
	{
		cout << "!!!!!!!!!!!!      AI WON  !!!!!!!!!!!!!!!\n" ;
		cout << "Score : " << computerScore ;
	}
	else
	{
		cout << "Draw!\n" ;
	}
	setColor(WHITE , BLACK) ;
	file_output.close() ;
}

void initializeBoard(char board[10][10])
{
	// Initialize 10x10 board with water '~' // This part here is done
    for (int st = 0; st <= 10 - 1 ; st++)
    {    	
        for (int st2 = 0; st2 <=  10 -  1 ;  st2++)
        {
        	board[st][st2] = '~';
		}
    }
}

void printBoard(char board[10][10] , bool hideShips)
{
	if(hideShips)
	{
		setColor(WHITE , RED) ;
		cout << "Ships are HIDDEN\n" ;
		setColor(WHITE , BLACK) ;
	}
	
    cout << "       0     1     2     3     4     5     6     7     8     9  " << endl;

    // Top border
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
    // Row 0
    cout << "  0 Š"; // weird symbol
    for (int st = 0; st < 10; st++)
    {
        char cell = board[0][st];
        if(cell == 'S' && !hideShips) // meaning filled ship placed
        {
        	setColor(0, ship_color1); cout << "  S  "; setColor(7,0); cout << "Š";
		}
        else 
		{
		setColor(7, 1); cout << "  ~  "; setColor(7,0); cout << "Š";
	    }    
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----Š" << endl;
    
    // Row 1
    cout << "  1 Š"; // weird symbol
    for (int st = 0; st < 10; st++)
    {
        char cell = board[1][st];
        if(cell == 'S' && !hideShips) // meaning filled ship placed
        {
        	setColor(0, ship_color1); cout << "  S  "; setColor(7,0); cout << "Š";
		}
        else 
		{
		setColor(7, 1); cout << "  ~  "; setColor(7,0); cout << "Š";
	    } 
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----Š" << endl;
    // Row 2
    cout << "  2 Š"; // weird symbol
    for (int st = 0; st < 10; st++)
    {
        char cell = board[2][st];
        if(cell == 'S' && !hideShips) // meaning filled ship placed
        {
        	setColor(0, ship_color1); cout << "  S  "; setColor(7,0); cout << "Š";
		}
        else 
		{
		setColor(7, 1); cout << "  ~  "; setColor(7,0); cout << "Š";
	    } 
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----Š" << endl;
    
    // Row 3
    cout << "  3 Š"; // weird symbol
    for (int st = 0; st < 10; st++)
    {
        char cell = board[3][st];
        if(cell == 'S' && !hideShips) // meaning filled ship placed
        {
        	setColor(0, ship_color1); cout << "  S  "; setColor(7,0); cout << "Š";
		}
        else 
		{
		setColor(7, 1); cout << "  ~  "; setColor(7,0); cout << "Š";
	    } 
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----Š" << endl;
    
    // Row 4
    cout << "  4 Š"; // weird symbol
    for (int st = 0; st < 10; st++)
    {
        char cell = board[4][st];
        if(cell == 'S' && !hideShips) // meaning filled ship placed
        {
        	setColor(0, ship_color1); cout << "  S  "; setColor(7,0); cout << "Š";
		}
        else 
		{
		setColor(7, 1); cout << "  ~  "; setColor(7,0); cout << "Š";
	    } 
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----Š" << endl;
    
    
    // Row 5
    cout << "  5 Š"; // weird symbol
    for (int st = 0; st < 10; st++)
    {
        char cell = board[5][st];
        if(cell == 'S' && !hideShips) // meaning filled ship placed
        {
        	setColor(0, ship_color1); cout << "  S  "; setColor(7,0); cout << "Š";
		}
        else 
		{
		setColor(7, 1); cout << "  ~  "; setColor(7,0); cout << "Š";
	    } 
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----Š" << endl;
    
    // Row 6
    cout << "  6 Š"; // weird symbol
    for (int st = 0; st < 10; st++)
    {
        char cell = board[6][st];
        if(cell == 'S' && !hideShips) // meaning filled ship placed
        {
        	setColor(0, ship_color1); cout << "  S  "; setColor(7,0); cout << "Š";
		}
        else 
		{
		setColor(7, 1); cout << "  ~  "; setColor(7,0); cout << "Š";
	    } 
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----Š" << endl;
    
    // Row 7
    cout << "  7 Š"; // weird symbol
    for (int st = 0; st < 10; st++)
    {
        char cell = board[7][st];
        if(cell == 'S' && !hideShips) // meaning filled ship placed
        {
        	setColor(0, ship_color1); cout << "  S  "; setColor(7,0); cout << "Š";
		}
        else 
		{
		setColor(7, 1); cout << "  ~  "; setColor(7,0); cout << "Š";
	    } 
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----Š" << endl;

    // Row 8
    cout << "  8 Š"; // weird symbol
    for (int st = 0; st < 10; st++)
    {
        char cell = board[8][st];
        if(cell == 'S' && !hideShips) // meaning filled ship placed
        {
        	setColor(0, ship_color1); cout << "  S  "; setColor(7,0); cout << "Š";
		}
        else 
		{
		setColor(7, 1); cout << "  ~  "; setColor(7,0); cout << "Š";
	    } 
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----Š" << endl;
    
    // Row 9
    cout << "  9 Š"; // weird symbol
    for (int st = 0; st < 10; st++)
    {
        char cell = board[9][st];
        if(cell == 'S' && !hideShips) // meaning filled ship placed
        {
        	setColor(0, ship_color1); cout << "  S  "; setColor(7,0); cout << "Š";
		}
        else 
		{
		setColor(7, 1); cout << "  ~  "; setColor(7,0); cout << "Š";
	    } 
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
}




//////////////////////////////////Main Start Point I will Use the Function Declerations to make things even more easier////////////////////////////////

int ship_placement_choice()
{
	cout << "How do wanna place the ships\n1.Manually\n2.Random\n" ;
	int ch ; 
	cout << "Choice : " ;
	cin >> ch ;
	while(ch < 1 ||  ch > 2)
	{
		cout << "Enter correct Choice :\n"; 
		cin >> ch  ;
	}
	return ch ;
}

int give_ship_size(int ship_op)
{ 
    if(user_choice_for_ship == 1)
    {
    	return  5 ;
	}
	else if(user_choice_for_ship == 2)
	{
		return 4  ;
	}
	else if(user_choice_for_ship == 3)
	{
		return 3  ;
	}
	else if(user_choice_for_ship == 4)
	{
		return 3 ; 
	}
	return  2  ;  // since the last option is only left
}

void setManuallyShips_V01(char board[10][10] , int ship_size)
{ 
        // Default Case is the horizontal case 	
	  	int flag  = true ; // don't touch this flag
	  	int row  ; 
	  	int column ;
	  	bool track_isVertical = false ;
	  	int ship_last_location = 0 ; // for vertical change row 
	  	int old_column ; 
	  	int old_row ;
	  	
	  	while(flag) // Well i don't need this while loop tho yeah like placeing one ship at a time
	  	   	{ 
	  	 	 	cout << "Enter starting row (0 - 9) : "  ;
	  	     	cin >> row ;
	  	     	while(row < 0 ||  row > 9) // input validation
			   	{
			  		cout << "\nEnter correct row : " ;
			  	 	cin >> row ;
			   	}	
			 	cout << "Enter Starting Column (0  - 9) : " ;
			 	cin >> column ;
			 	while(column < 0 || column  > 9)
			  	{ 
				 	cout << "\nEnter correct column : " ;
			  	 	cin >> column ;
			  	}
			  	 old_column = column ;
		     	 old_row = row ;
			  // Check if the ship to be placed is within the bounds of that row column like is there enough space for ship to be place
			  	if(9 - column - ship_size + 1 <   0)
			  	{
			  	 // meaning kay it is not in the bound of the row column  breaks that rule
			  	  setColor(4  , 0) ;
				  cout << "\nOUT OF BOUND KEEP IT IN RANGE\n" ;
				  setColor(7 , 0) ; //changing back to original
			  	  continue ; 
			  	} 
		    // Check if that place is clear where the ships are to be placed 
		    bool ship_placed = true; 
		     for(int st  = 0 ; st <= ship_size - 1  ;  st += 1)
		     	{ 
		   	   		if(board[row][column + st] != '~') //  check if that row or column is filled or not
		   	   		{	 
		   	     	setColor(4  , 0) ;
		   	 	 	cout << "\nWRONG PLACEMENT SHIP Already their CHOSE A NEW POSITION\n" ;
		   	 	 	setColor(7 , 0) ; // changing back to original
		   	 	 	ship_placed = false ;
		   	 	 	break ;
		       		}
		     	}
		     	if(!ship_placed)
		     	{
		     		continue ;
				}
		    	for(int st  = 0 ; st <= ship_size - 1  ;  st += 1) // ONLY HORIZONTAL PART
		     	{
		     		if(st == 0)
		     		{
		     			ship_last_location = column + st ; 
					}
		   	   		board[row][column + st] = 'S' ; // That column ++ ;
		     	}
		    	flag = false ; // Ship was placed successfully
		   	} // WHILE ENDS
	    clearScreen() ;
		printBoard(board , false) ;	
		cout << "Do you wanna place the ship vertically?\n1.Yes\n2.No\n" ; 
		int choice ; 
		cout << "Choice : " ;
		cin >> choice ;
		while(choice < 1 || choice > 2)
		{
			cout << "Enter correct choice\n" ;
			cin >> choice ;
		}
		if(choice == 1)
		{
			// Swaping row and column for the vetival case 
		       column = ship_last_location ;
			  // Check if the ship to be placed is within the bounds of that row column like is there enough space for ship to be place
			  	
				bool ship_out_of_bound = false ;  
				if(9 - row - ship_size + 1 <   0)
			  	{
			  	 // meaning kay it is not in the bound of the row column  breaks that rule
			  	  setColor(YELLOW  , RED) ;
				  cout << "\nOUT OF BOUND CANNOT PLACE SHIP HERE\nPress Any Button to continue\n" ;
				  setColor(7 , 0) ; //changing back to original 
				  getch() ;
				  ship_out_of_bound = true ;
			  	}
			  	
			  	if(!ship_out_of_bound) // out of bound nahi hai chalo phir check karo koi or ship tu nhi us jaga
			  	{
			  		ship_out_of_bound = false ;
			  		for(int st  = 0 ; st <= ship_size - 1  ;  st += 1)
		     		{	 
		     		  if(st == 0)
		     		  {
		     		  	// HERE AT THIS POINT I NEED TO MOVE 1 ROW FORWARD CAUSE IT IS GIVING ERROR why CAUSE It's checking
				 		// the last position and it the condition inside below for loop would always be true
				 		continue ;
					   }
		   	   		if(board[row + st][column] != '~') //  check if that row or column is filled or not
		   	   			{	 
		   	     		setColor(YELLOW  , RED) ;
		   	 	 		cout << "\nSORRY A SHIP IS ALREADY PLACED CANNOT ROTATE\nPress any Button to continue\n" ;
		   	 	 		setColor(7 , 0) ; // changing back to original
		   	 	 		ship_out_of_bound = true ;
		   	 	 		getch() ;
		   	 	 		break ;
		       			}
		     		}
		     		if(!ship_out_of_bound) // mtlb kay udher koi ship bi nhi hai then rotate it 
		     		{ 
		    			for(int st  = 0 ; st <= ship_size - 1  ;  st += 1) // ONLY HORIZONTAL PART
		     			{
		   	   				board[row + st][column] = 'S' ; // That column ++ ;
		     			}
		     			// reverting the old horizontal back to ~
		     			for(int st  = 0 ; st <= ship_size - 1  ;  st += 1) // ONLY HORIZONTAL PART
		     				{
		     					if(st == 0)
		     					{
		     						continue ;  // i don't wanna revert that single point  back to ~ where the turn happened
								}
		   	   				board[old_row][old_column + st] = '~' ; // That column ++ ;
		     				} // END for
		     				track_isVertical = true ; // yes the ship has rotated store it vertical cord
					}
				}
		   }
		     if(track_isVertical == true)
			 { 
		    	// Check if that place is clear where the ships are to be placed
		     	if(track_player_turn == '1') // Player one turn meaning put the boat location in player1 location array
		     	{
		     	  	player1_ship_location[st_idx_for_ship_location][0] = row + '0';  // to conveet to character
		     	  	player1_ship_location[st_idx_for_ship_location][1] = column + '0' ; 
		     	  	player1_ship_location[st_idx_for_ship_location][2] = ship_size + '0' ;
		     	  	player1_ship_location[st_idx_for_ship_location][3] = 'V' ; // It is placed horizontally
		     	  	st_idx_for_ship_location += 1 ;// move to next location for player 1  
				}
				else if(track_player_turn == '2')
				{
					player2_ship_location[st_idx_for_ship_location][0] = row + '0';  // to conveet to character
		     	  	player2_ship_location[st_idx_for_ship_location][1] = column + '0' ; 
		     	  	player2_ship_location[st_idx_for_ship_location][2] = ship_size + '0' ;
		     	  	player2_ship_location[st_idx_for_ship_location][3] = 'V' ; // It is placed horizontally
		     	  	st_idx_for_ship_location += 1 ; // move to next location for player 2
				}
		   	}
		   	else // Horizontal case
		   	{			   
		   	// remember only one will execute
		     	if(track_player_turn == '1') // Player one turn meaning put the boat location in player1 location array
		     	{
		     	  	player1_ship_location[st_idx_for_ship_location][0] = row + '0';  // to conveet to character
		     	  	player1_ship_location[st_idx_for_ship_location][1] = column + '0' ; 
		     	  	player1_ship_location[st_idx_for_ship_location][2] = ship_size + '0' ;
		     	  	player1_ship_location[st_idx_for_ship_location][3] = 'H' ; // It is placed horizontally
		     	  	st_idx_for_ship_location += 1 ;// move to next location for player 1  
				}
				else if(track_player_turn == '2')
				{
					player2_ship_location[st_idx_for_ship_location][0] = row + '0';  // to conveet to character
		     	  	player2_ship_location[st_idx_for_ship_location][1] = column + '0' ; 
		     	  	player2_ship_location[st_idx_for_ship_location][2] = ship_size + '0' ;
		     	  	player2_ship_location[st_idx_for_ship_location][3] = 'H' ; // It is placed horizontally
		     	  	st_idx_for_ship_location += 1 ; // move to next location for player 2
				}
		   }
}

//////////////////////////////////////////Below is the code for randomplacements////////////////////////////////////////////////////

// I was running into the error where it was storing  the worng column of the ship like column + st the reason for that was if the choice to place
// ships vertically is ture then it would assign the column the last ship location but what if it is plced then it
// would be false ships not rotated but column was assigned the column what is ship_last_location + st which is wrong
// so to solve this problem i will make a new column for location var which will store the location 



void setRandomShips_V01(char board[10][10] , int ship_size)
{ 
        // Default Case is the horizontal case 	
	  	int flag  = true ; // don't touch this flag
	  	int row  ; 
	  	int column ;
	  	int column_for_location = 0 ;  // I need this varaiable to store column not column + st in the loccation array 
	  	bool track_isVertical = false ;
	  	int ship_last_location = 0 ; // for vertical change row 
	  	int old_column ; 
	  	int old_row ;
	  	
	  	while(flag) // Well i don't need this while loop tho yeah like placeing one ship at a time
	  	   	{ 
	  	   	     srand(time(NULL)) ;
	  	 	 	 row = (rand() % (9 - 0 + 1)) + 0;
	  	 	 	 column = (rand() % (9 - 0 + 1)) + 0;
			  	 old_column = column ;
		     	 old_row = row ;
			  // Check if the ship to be placed is within the bounds of that row column like is there enough space for ship to be place
			  	if(9 - column - ship_size  + 1 <   0)
			  	{
			  	 // meaning kay it is not in the bound of the row column  breaks that rule
			  	  //setColor(4  , 0) ;
				 // cout << "\nOUT OF BOUND KEEP IT IN RANGE\n" ;
				  //setColor(7 , 0) ; //changing back to original
			  	  continue ; 
			  	} 
		    // Check if that place is clear where the ships are to be placed 
		    bool ship_placed = true; 
		     for(int st  = 0 ; st <= ship_size - 1  ;  st += 1)
		     	{ 
		   	   		if(board[row][column + st] != '~') //  check if that row or column is filled or not
		   	   		{	 
		   	     	//setColor(4  , 0) ;
		   	 	 	//cout << "\nWRONG PLACEMENT SHIP Already their CHOSE A NEW POSITION\n" ;
		   	 	 	//setColor(7 , 0) ; // changing back to original
		   	 	 	ship_placed = false ;
		   	 	 	break ;
		       		}
		     	}
		     	if(!ship_placed)
		     	{
		     		continue ;
				}
		    	for(int st  = 0 ; st <= ship_size - 1  ;  st += 1) // ONLY HORIZONTAL PART
		     	{
		     		if(st == 0)
		     		{
		     			ship_last_location = column + st ; 
		     			column_for_location = column ; // for horizontal case only
					}
		   	   		board[row][column + st] = 'S' ; // That column ++ ;
		     	}
		    	flag = false ; // Ship was placed successfully
		   	} // WHILE ENDS
	    //clearScreen() ;
		// display_board(board) ;	
	//	cout << "Do you wanna place the ship vertically?\n1.Yes\n2.No\n" ; 
		int choice = rand() % 2  + 1 ; 
		if(choice == 1)
		{
			// Swaping row and column for the vetival case 
		       column = ship_last_location ;
		      // cout << column ;
			  // Check if the ship to be placed is within the bounds of that row column like is there enough space for ship to be place
			  	
				bool ship_out_of_bound = false ;  
				if(9 - row - ship_size  +  1 <   0)
			  	{
			  	 // meaning kay it is not in the bound of the row column  breaks that rule
			  	  //setColor(YELLOW  , RED) ;
				  //cout << "\nOUT OF BOUND CANNOT PLACE SHIP HERE\nPress Any Button to continue\n" ;
				  //setColor(7 , 0) ; //changing back to original 
				  //getch() ;
				  ship_out_of_bound = true ;
			  	}
			  	
			  	if(!ship_out_of_bound) // out of bound nahi hai chalo phir check karo koi or ship tu nhi us jaga
			  	{
			  		ship_out_of_bound = false ;
			  		for(int st  = 0 ; st <= ship_size - 1  ;  st += 1)
		     		{	 
		     		  if(st == 0)
		     		  {
		     		  	// HERE AT THIS POINT I NEED TO MOVE 1 ROW FORWARD CAUSE IT IS GIVING ERROR why CAUSE It's checking
				 		// the last position and it the condition inside below for loop would always be true
				 		continue ;
					   }
		   	   		if(board[row + st][column] != '~') //  check if that row or column is filled or not
		   	   			{	 
		   	     		//setColor(YELLOW  , RED) ;
		   	 	 		//cout << "\nSORRY A SHIP IS ALREADY PLACED CANNOT ROTATE\nPress any Button to continue\n" ;
		   	 	 		//setColor(7 , 0) ; // changing back to original
		   	 	 		ship_out_of_bound = true ;
		   	 	 		//getch() ;
		   	 	 		break ;
		       			}
		     		}
		     		bool did_it_change_to_vertical = false ;
		     		if(!ship_out_of_bound) // mtlb kay udher koi ship bi nhi hai then rotate it 
		     		{ 
		     		    did_it_change_to_vertical = true ;
		    			for(int st  = 0 ; st <= ship_size - 1  ;  st += 1) // ONLY HORIZONTAL PART
		     			{
		   	   				board[row + st][column] = 'S' ; // That column ++ ;
		     			}
		     			// reverting the old horizontal back to ~
		     			for(int st  = 0 ; st <= ship_size - 1  ;  st += 1) // ONLY HORIZONTAL PART
		     				{
		     					if(st == 0)
		     					{
		     						continue ;  // i don't wanna revert that single point  back to ~ where the turn happened
								}
		   	   				board[old_row][old_column + st] = '~' ; // That column ++ ;
		     				} // END for
		     				if(did_it_change_to_vertical == false)  // Meaing the rand didn't change it so the column would be old
		     				{
		     				 column = column_for_location ; 	
							}
		     				track_isVertical = true ; // yes the ship has rotated store it vertical cord
					}
				}
		   }
		     if(track_isVertical == true)
			 { 
		    	// Check if that place is clear where the ships are to be placed
		     	if(track_player_turn == '1') // Player one turn meaning put the boat location in player1 location array
		     	{
		     	  	player1_ship_location[st_idx_for_ship_location][0] = row + '0';  // to conveet to character
		     	  	player1_ship_location[st_idx_for_ship_location][1] = column + '0' ; 
		     	  	player1_ship_location[st_idx_for_ship_location][2] = ship_size + '0' ;
		     	  	player1_ship_location[st_idx_for_ship_location][3] = 'V' ; // It is placed horizontally
		     	  	st_idx_for_ship_location += 1 ;// move to next location for player 1  
				}
				else if(track_player_turn == '2')
				{
					player2_ship_location[st_idx_for_ship_location][0] = row + '0';  // to conveet to character
		     	  	player2_ship_location[st_idx_for_ship_location][1] = column + '0' ; 
		     	  	player2_ship_location[st_idx_for_ship_location][2] = ship_size + '0' ;
		     	  	player2_ship_location[st_idx_for_ship_location][3] = 'V' ; // It is placed horizontally
		     	  	st_idx_for_ship_location += 1 ; // move to next location for player 2
				}
		   	}
		   	else // Horizontal case
		   	{			   
		   	// remember only one will execute
		     	if(track_player_turn == '1') // Player one turn meaning put the boat location in player1 location array
		     	{
		     	  	player1_ship_location[st_idx_for_ship_location][0] = row + '0';  // to conveet to character
		     	  	player1_ship_location[st_idx_for_ship_location][1] = column_for_location + '0' ; 
		     	  	player1_ship_location[st_idx_for_ship_location][2] = ship_size + '0' ;
		     	  	player1_ship_location[st_idx_for_ship_location][3] = 'H' ; // It is placed horizontally
		     	  	st_idx_for_ship_location += 1 ;// move to next location for player 1  
				}
				else if(track_player_turn == '2')
				{
					player2_ship_location[st_idx_for_ship_location][0] = row + '0';  // to conveet to character
		     	  	player2_ship_location[st_idx_for_ship_location][1] = column_for_location + '0' ; 
		     	  	player2_ship_location[st_idx_for_ship_location][2] = ship_size + '0' ;
		     	  	player2_ship_location[st_idx_for_ship_location][3] = 'H' ; // It is placed horizontally
		     	  	st_idx_for_ship_location += 1 ; // move to next location for player 2
				}
		   }
		   cout << "~Meow <-w-> Meow~\n" ;
}
//////////////////////////////////////////////rand placement ends//////////////////////////////////////////////////////////////////////





void setRandomShips(char board[10][10])
{
	 int ships_size[5] = {5 , 4  , 3 , 3 , 2} ;
	 for(int st = 0 ;  st <= 5 - 1  ; st += 1)
	  {
	  	cout << "." ;
	   	setRandomShips_V01(board , ships_size[st]) ;
	  }
} 


void  setManualships(char board[10][10])
{
	bool ship_not_used[5] = {true , true , true , true , true} ;
	printBoard(board , false) ;
	while(true)
	{
		cout << "Chose your Ship!\n" ; 
		cout << "1. Aircraft Carrier - 5 blocks\n" ;
		cout << "2. Battleship - 4 blocks\n" ;
		cout << "3. Destroyer - 3 blocks\n" ; 
		cout << "4. Submarine - 3 blocks\n" ;
		cout << "5. Patrol Boat - 2 blocks\n"; 	
		cout << "Choice : " ;
		cin >> user_choice_for_ship ;
		while(user_choice_for_ship < 1 || user_choice_for_ship  > 5)
		{
			cout << "Enter correct option\n"  ;
			cin  >> user_choice_for_ship ; 
 	    }
 	    // Condition to check if ship is used or not
 	    if(ship_not_used[user_choice_for_ship - 1] == false) // meaning that ship  is  used chose a new ship
 	    {
 	       clearScreen() ;
 	       printBoard(board , false);
 	       setColor(YELLOW , RED) ;
 	       cout << "Ship was Already Selected chose a new Ship\n" ;
 	       setColor(WHITE , BLACK) ;
 	       continue ;
		}
		int ship_size = give_ship_size(user_choice_for_ship) ;
		// Call the Manual ship placement function	
		setManuallyShips_V01(board , ship_size) ;	
		// Not used move forward
		ship_not_used[user_choice_for_ship - 1] = false ;  // ship selected make it false
		clearScreen() ;
		printBoard(board  , false) ;
		
		// below loop is used to break the loop if all ships are palced
		bool ship_left_any = false ; 
		for(int st = 0 ; st <= 5 - 1  ; st += 1)
		{
			if(ship_not_used[st])
			{
				ship_left_any = true ;
				break ;
			}
		}
		if(ship_left_any == false)
		{
 			break  ;
		}
  	}
    
}


void Ship_Placement(int ship_setup_choice  , char board[10][10])
{
	if(ship_setup_choice == 1) // Manual
	{
	 	setManualships(board) ;	// Function is Called Up	
	}
	else
	{
		// In case of random i will loop through the ships + size and pass them one  by one
		setColor(WHITE , RED) ;
		cout << "Wait a few seconds please...\n" ;
		setColor(WHITE , BLACK) ;
		setRandomShips(board) ;
		setColor(WHITE , RED) ;
		cout << "Placed Successfully MEOW! Press any button to continue\n" ;
		setColor(WHITE , BLACK) ;
		getch() ;
		clearScreen() ;
	}
}

/////////////////////////////////////////vs PlayerShip_Placement Starts/////////////////////////////////////

void vsPlayer_Ship_Placement()
{
	cout << "Enter Player 1  Name : " ;
	cin >> player1_name ; 
	cout << "Enter Player  2 Name : " ;
	cin >> player2_name ;
	
	setColor(WHITE , RED)  ;
	cout << "Are you ready to place your ships? \n" ;
	setColor(WHITE , BLACK) ;
	cout << player1_name ; 
	setColor(WHITE , RED)  ;
	cout << "\nPress Any Button to continue!" ;
	setColor(WHITE , BLACK) ;
	getch() ;
	clearScreen() ;
    int user_choice = ship_placement_choice() ;
    track_player_turn = '1' ;  // player 1 turn in terms of testing
    initializeBoard(player_1_board) ; // Intialize the player obe board to '~'
    clearScreen() ;
    ask_ship_color() ; 
    clearScreen() ;
    st_idx_for_ship_location = 0 ;
    Ship_Placement(user_choice , player_1_board) ;
    clearScreen() ;
    printBoard(player_1_board , false) ;
    setColor(YELLOW , RED) ;
	cout << "All Ships Placed Successfully\nPress Any Button to continue to next turn\n" ;
	setColor(WHITE , BLACK) ;
	getch() ;
	clearScreen() ;
    // Ship Place successfully for player 1
    // Player 2 turn to place the ships now
    setColor(WHITE , RED)  ;
	cout << "Are you ready to place your ships? \n" ;
	setColor(WHITE , BLACK) ;
	cout << player2_name ; 
	setColor(WHITE , RED)  ;
	cout << "\nPress Any Button to continue!" ;
	setColor(WHITE , BLACK) ;
	getch() ;
	clearScreen() ;
    user_choice = ship_placement_choice() ;
    track_player_turn = '2' ;  // player 1 turn in terms of testing
    initializeBoard(player_2_board) ; // Intialize the player obe board to '~'
    clearScreen() ;
    ask_ship_color() ; 
    clearScreen() ;
    st_idx_for_ship_location = 0 ;
    Ship_Placement(user_choice , player_2_board) ;
    clearScreen() ;
    printBoard(player_2_board , false) ;
    setColor(YELLOW , RED) ;
	cout << "All Ships Placed Successfully\nPress Any Button to continue \n" ;
	setColor(WHITE , BLACK) ;
	getch() ;
	clearScreen();
	
	setColor(YELLOW , RED) ;
	cout << "GET READY FOR THE NEXT BATTLE\nPress Any Button to continue\n" ;
	setColor(WHITE , BLACK) ;
	getch() ;
}

////////////////////////////////Vs Player Ship placement ends//////////////////////////////////////////////


//////////////////////Main vsPlayer Function Start//////////////////////////////////////////
void vsPlayer_Board_display(char board1[10][10] , char board2[10][10]  , int current_turn = 0)
{
	cout << endl << endl ;
  	cout << "    PLAYER 1 BOARD " ;
  	cout << "                              ";
  	if(current_turn % 2 == 0)
  	{
  		setColor(RED , 14) ;
  		cout << " Player 1 Turn "; 
  		setColor(WHITE , BLACK) ;
	}
	else
	{
		setColor(RED , 14) ;
		cout << " Player 2 Turn " ;
		setColor(WHITE , BLACK) ;
	}
	cout << "                             " ;
	cout << "  PLAYER 2 BOARD " << "\n" ;
	cout << "                      " ; 
	cout << "       0     1     2     3     4     5     6     7     8     9  " << endl;
	cout << "  0 1 2 3 4 5 6 7 8 9 " ; 
	cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" ;
	cout << "      0 1 2 3 4 5 6 7 8 9" ;
	cout << endl ;  
  	//  NOTE TO MYSELF : THE MID BOARD WILL CHANGE ACCORDING TO THE CURRENT TURN
  	if(current_turn % 2 == 0) // Player 1 turn
  	{
  	   for(int st = 0 ;  st <= 10 - 1  ; st += 1)
  	   {  
  	      cout << st << " " ; 
  	      for(int st2 = 0  ; st2 <= 10 - 1 ;  st2  += 1) // the Player 1 board printing part
		      { 
		    	if(board1[st][st2] == '~')
		    	{
		    		cout << "." << " " ;
				}
				else
				{
					cout << board1[st][st2] << " " ;
				}
		      }
		      
		    cout << "  " << st <<" Š"; // weird symbol
    		for (int st2 = 0; st2 <= 10 - 1; st2++)
    		{
        		char cell = board2[st][st2]; 
        		
        		if(fake_bool_2[st][st2] == true)
        		{
        		  setColor(WHITE, MAGENTA); cout << "  D  "; setColor(7,0); cout << "Š";	
				}
				else  if(cell == 'X')
        		{
        			setColor(WHITE, RED); cout << "  X  "; setColor(7,0); cout << "Š";
				}
				else if(cell == 'O')
				{
					setColor(BLACK, WHITE); cout << "  O  "; setColor(7,0); cout << "Š";
				}
				else
				{
				setColor(7, 1); cout << "  ~  "; setColor(7,0); cout << "Š";
			    }
    		}
    		
    		cout << "    "; 
    		cout << st << " " ; 
  	      	for(int st2 = 0  ; st2 <= 10 - 1 ;  st2  += 1) // the Player 2 board printing part
		   		{
		    	if(board2[st][st2] == '~')
		    	 {
		    		cout << "." << " " ;
				 } 
				   else
				 {
					cout << board2[st][st2] << " " ;
				 }
		        }
    		cout << endl ; 
    		cout << "                      " ;
            cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----Š" ;
            cout << endl;
	   } // END MAIN FOR LOOP
	}// END IF
	else // PLAYER  2 TURN
	{
		for(int st = 0 ;  st <= 10 - 1  ; st += 1)
  	   {  
  	      cout << st << " " ; 
  	      for(int st2 = 0  ; st2 <= 10 - 1 ;  st2  += 1) // the Player 1 board printing part
		      { 
		    	if(board1[st][st2] == '~')
		    	{
		    		cout << "." << " " ;
				}
				else
				{
					cout << board1[st][st2] << " " ;
				}
		      }
		   cout << "  " << st <<" Š"; // weird symbol
    		for (int st2 = 0; st2 <= 10 - 1; st2++)
    		{
        		char cell = board1[st][st2]; // Meaning PLayer 2 turn now i will display the player 1 board 
				
				if(fake_bool_1[st][st2] ==  true)
				{
					setColor(WHITE, MAGENTA); cout << "  D  "; setColor(7,0); cout << "Š";
				}
				else if(cell == 'X')
        		{
        			setColor(WHITE, RED); cout << "  X  "; setColor(7,0); cout << "Š";
				}
				else if(cell == 'O')
				{
					setColor(BLACK, WHITE); cout << "  O  "; setColor(7,0); cout << "Š";
				}
				else
				{
				setColor(7, 1); cout << "  ~  "; setColor(7,0); cout << "Š";
			    }   
    		}
    		cout << "    "; 
    		cout << st << " " ; 
  	      	for(int st2 = 0  ; st2 <= 10 - 1 ;  st2  += 1) // the Player 2 board printing part
		   		{
		    	if(board2[st][st2] == '~')
		    	 {
		    		cout << "." << " " ;
				 } 
				   else
				 {
					cout << board2[st][st2] << " " ;
				 }
		        }
    		cout << endl ; 
    		cout << "                      " ;
            cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----Š" ;
            cout << endl;
	   } // END MAIN FOR LOOP	
	} // END ELSE
	setColor(15 , RED) ;
	cout << " Player 1 Score : "  ; 
	cout << Player1_Score ; 
	setColor(WHITE , BLACK)  ;
	cout  << "                                                " ;
	cout << "                         " ;
	setColor(15 , RED) ;
	cout << "Player 2 Score : " << Player2_Score << endl ;
	setColor(WHITE , BLACK) ;  
} // end function


// will give me current player ship data how many ships left
int get_ships_data(char player_board[10][10] , int turn)
{
	int ships_count = 0 ;
	if(turn % 2 == 0) // Player 1  ships data of total ships left
	{
		for(int st = 0 ; st <= 5 - 1  ; st += 1)
		{
			if(player1_ship_location[st][3] == 'H') // meaning ship is placed horizontally
			{
				int ship_size = player1_ship_location[st][2] - '0' ; // get the row of player1 shiplocation ship size
				int count = 0 ; // i will use count to determine if the ship is still good or not if count is 0 ship that ship is dead
				int row = player1_ship_location[st][0] - '0' ;
				int column = player1_ship_location[st][1] - '0' ;
				for(int st = 0 ; st <= ship_size - 1 ;  st += 1)
				{
					if(player_board[row][column + st] == '~')
					{
						count += 1 ;
					}
				}
				if(count != 0) // meaning ship is still alive 
				{
					ships_count += 1 ;
				}
			}
			else
			{
				int ship_size = player1_ship_location[st][2] - '0' ; // get the row of player1 shiplocation ship size
				int count = 0 ; // i will use count to determine if the ship is still good or not if count is 0 ship that ship is dead
				int row = player1_ship_location[st][0] - '0' ;
				int column = player1_ship_location[st][1] - '0' ;
				for(int st = 0 ; st <= ship_size - 1 ;  st += 1)
				{
					if(player_board[row + st][column] == '~')
					{
						count += 1 ;
					}
				}
				if(count != 0) // meaning ship is still alive 
				{
					ships_count += 1 ;
				}
			} // END INNER ELSE
		}  // END For
	}// END MAIN IF
	else // Player 2  ships data
	{
		for(int st = 0 ; st <= 5 - 1  ; st += 1)
		{
			if(player2_ship_location[st][3] == 'H') // meaning ship is placed horizontally
			{
				int ship_size = player2_ship_location[st][2] - '0' ; // get the row of player1 shiplocation ship size
				int count = 0 ; // i will use count to determine if the ship is still good or not if count is 0 ship that ship is dead
				int row = player2_ship_location[st][0] - '0' ;
				int column = player2_ship_location[st][1] - '0' ;
				for(int st = 0 ; st <= ship_size - 1 ;  st += 1)
				{
					if(player_board[row][column + st] == '~')
					{
						count += 1 ;
					}
				}
				if(count != 0) // meaning ship is still alive 
				{
					ships_count += 1 ;
				}
			}
			else
			{
				int ship_size = player2_ship_location[st][2] - '0' ; // get the row of player1 shiplocation ship size
				int count = 0 ; // i will use count to determine if the ship is still good or not if count is 0 ship that ship is dead
				int row = player2_ship_location[st][0] - '0' ;
				int column = player2_ship_location[st][1] - '0' ;
				for(int st = 0 ; st <= ship_size - 1 ;  st += 1)
				{
					if(player_board[row + st][column] == '~')
					{
						count += 1 ;
					}
				}
				if(count != 0) // meaning ship is still alive 
				{
					ships_count += 1 ;
				}
			} // END INNER ELSE
		}  // END For
	} // END OUTER ELSE
	
	return ships_count  ;
}

// total attacks is basically just my ship count which i get from a function named as get ships
int total_attacks ; // making it global since i need it in two funcions vsPlayer  where i will pass the 
// player himself board then it will calulates the total ships and i will use it Playerattack where i need my  
// total number of attacks the current player , my opponent board and ofcourse current player score

void PlayerAttack(char oppponentBoard[10][10] , int &playerScore) 
{
   int idx = 0 ; 
   int shots = total_attacks + 1 ; // According to the given condition
   // the  below will store the row and column of each attack respectively
   int attack_cord[shots][2] ; // all of my player attacks will be placed in here in case if he wanna stop the attack mid way 
   cout << "\nYour Ships Destroyed : " << 5  - total_attacks  ;
   while(shots > 0) // while my current attack shots are > 0
   {
   	cout << "\nTotal Shots Left : " << shots << endl ;
   	cout << "Enter '-1' to end entering the cordinates  and attack the Ships\n" ;
   	cout << "Enter your Opponent Row to Attack : "; 
   	int row ; 
   	cin >> row ; 
   	if(row == -1)
   	{
   	 break ;	
	}
   	while(row <  -1  || row >  9)
	{
	   	cout << "Enter correct row : " ;
	   	cin >> row ;
	}
	if(row == -1)
   	{	
   	 	break ;	
	} 
	cout << "Enter your Opponent Column to Attack : "; 
   	int column ; 
   	cin >> column ; 
   	while(column <  0  || column >  9)
	{
	   	cout << "Enter correct Column : " ;
	   	cin >> column ;
	}
	if(oppponentBoard[row][column] == 'X' || oppponentBoard[row][column] == 'O')
	{
	   cout << "Already Attacked Enter your row and column Again\n ";	
	   continue ; 
	} 
	// The next condition is to prevent the user from entering the same row and column
	bool flag = true ;
	for(int st = 0  ; st <= idx - 1  ; st += 1)
	{
		if(attack_cord[st][0] == row && attack_cord[st][1] == column)
		{
			cout << "Cannot Enter same row and column\n" ;
			flag  = false ; 
			break ;
		}
	}
	if(!flag) continue ;
	
	// now commensing the attack on the following row and column
	attack_cord[idx][0] = row ;
	attack_cord[idx][1] = column ;
	idx++ ;
	shots-- ; 
   } // END WHILE

   for(int st = 0  ; st <= idx - 1  ; st +=  1) // Attacking all the cord given by the user
    {
   	if(global_boat_pass[attack_cord[st][0]][attack_cord[st][1]] == 'S') // meaning some ship is there 
   	{
   		_attacked_ = true ;
   		updateScore(playerScore) ;
   		oppponentBoard[attack_cord[st][0]][attack_cord[st][1]] = 'X' ;
	}
	else
	{
		_attacked_ = false ;
   		updateScore(playerScore) ;
		oppponentBoard[attack_cord[st][0]][attack_cord[st][1]] = 'O' ;
	}
   }
}



// Ship ki location store hai , or may ship destroyed ki board pay check karon ga the parameters of vsPlayer as
// they are the main current attack board , so if ship destroyed then mark that location on the
// fake bool array of the respective player 
void do_fake_bool_work(char player_board[10][10] , int turn)
{
	int ships_count = 0 ;
	if(turn % 2 == 0) // Player 1  ships data of total ships left
	{
		for(int st = 0 ; st <= 5 - 1  ; st += 1)
		{
			if(player1_ship_location[st][3] == 'H') // meaning ship is placed horizontally
			{
				int ship_size = player1_ship_location[st][2] - '0' ; // get the row of player1 shiplocation ship size
				int count = 0 ; // i will use count to determine if the ship is still good or not if count is 0 ship that ship is dead
				int row = player1_ship_location[st][0] - '0' ;
				int column = player1_ship_location[st][1] - '0' ;
				for(int st = 0 ; st <= ship_size - 1 ;  st += 1)
				{
					if(player_board[row][column + st] == '~')
					{
						count += 1 ;
					}
				}
				// meaning ship is meaning ship is not alive mark that ship location on fake boolean array of player 1
				// false
				if(count == 0) 
				{
				   for(int st = 0 ; st <= ship_size - 1 ;  st += 1)
					{
						fake_bool_1[row][column + st] = true ; 
					}	
				}
			}
			else
			{
				int ship_size = player1_ship_location[st][2] - '0' ; // get the row of player1 shiplocation ship size
				int count = 0 ; // i will use count to determine if the ship is still good or not if count is 0 ship that ship is dead
				int row = player1_ship_location[st][0] - '0' ;
				int column = player1_ship_location[st][1] - '0' ;
				for(int st = 0 ; st <= ship_size - 1 ;  st += 1)
				{
					if(player_board[row + st][column] == '~')
					{
						count += 1 ;
					}
				}
				if(count == 0) // meaning ship is not alive 
				{
					for(int st = 0 ; st <= ship_size - 1 ;  st += 1)
					{
						fake_bool_1[row + st][column] = true ;
					}
				}
			} // END INNER ELSE
		}  // END For
	}// END MAIN IF
	else // Player 2  ships data
	{
		for(int st = 0 ; st <= 5 - 1  ; st += 1)
		{
			if(player2_ship_location[st][3] == 'H') // meaning ship is placed horizontally
			{
				int ship_size = player2_ship_location[st][2] - '0' ; // get the row of player1 shiplocation ship size
				int count = 0 ; // i will use count to determine if the ship is still good or not if count is 0 ship that ship is dead
				int row = player2_ship_location[st][0] - '0' ;
				int column = player2_ship_location[st][1] - '0' ;
				for(int st = 0 ; st <= ship_size - 1 ;  st += 1)
				{
					if(player_board[row][column + st] == '~')
					{
						count += 1 ;
					}
				}
				if(count == 0) // meaning ship is not alive 
				{
					for(int st = 0 ; st <= ship_size - 1 ;  st += 1)
					{
						fake_bool_2[row][column + st] = true ; 
					}
				}
			}
			else
			{
				int ship_size = player2_ship_location[st][2] - '0' ; // get the row of player1 shiplocation ship size
				int count = 0 ; // i will use count to determine if the ship is still good or not if count is 0 ship that ship is dead
				int row = player2_ship_location[st][0] - '0' ;
				int column = player2_ship_location[st][1] - '0' ;
				for(int st = 0 ; st <= ship_size - 1 ;  st += 1)
				{
					if(player_board[row + st][column] == '~')
					{
						count += 1 ;
					}
				}
				if(count == 0) // meaning ship is not alive 
				{
					for(int st = 0 ; st <= ship_size - 1 ;  st += 1)
					{
						fake_bool_2[row + st][column] = true ;
					}
				}
			} // END INNER ELSE
		}  // END For
	} // END OUTER ELSE
}

void vsPlayer(char board1[10][10]  , char board2[10][10])
{
	// In versusplayershipplaement i will use the global array and for the main attack board i will just use the simple new array
	vsPlayer_Ship_Placement() ; // Both Player Ships placed Successfully 
    // Now I have to track the location of the ships in a boolean array (not necessary  boolean) and init of the 
    //original array back to  ~ then i will start the attack and  keep track of the shots hit and so on
    int turn  =  0 ;
	while(true)
    {
    	// Player 1 Turn
    	if(turn % 2 == 0)
    	{
    		clearScreen() ;
    		///////////////////////Doing the Fake bool work////////////////////////////////////////
    							do_fake_bool_work(board1  , 0); // simple checks for player1 , we'll adding turn
    							do_fake_bool_work(board2  , 1);// simply checks for player2    // was not necessary
    			///////////I'll jst call this before diplaing the main board every time
    		///////////////////////////////////////////////////////////////////////////////////////
    		
    		total_attacks = get_ships_data(board1,  turn);
    		if(total_attacks == 0) // meaning ships destroyed
    		{
    			clearScreen() ;
    			displayResult(Player1_Score , Player2_Score) ;
    			break ;
			}
    		vsPlayer_Board_display(board1 , board2 , turn); 
    		//// Now for the PLayer attack i have to pass the global boats which would check the count condition at 
    		// the end cause i can't pass more than on board as parameter due to restriction
    		// here i will initialize the global boat according to player 2 i.e my opponent
    		for(int st = 0 ;  st <= 10 - 1  ; st += 1)
    		{
    			for(int st2 = 0 ;  st2 <= 10 - 1 ;  st2 += 1)
    			{
    				global_boat_pass[st][st2] = player_2_board[st][st2] ;
				}
			}
    		PlayerAttack(board2 , Player1_Score) ;
    		clearScreen();
    		///////////////////////Doing the Fake bool work////////////////////////////////////////
    							do_fake_bool_work(board1  , 0); // simple checks for player1 , we'll adding turn
    							do_fake_bool_work(board2  , 1);// simply checks for player2    // was not necessary
    			///////////I'll jst call this before diplaing the main board every time
    		///////////////////////////////////////////////////////////////////////////////////////
    		
    		vsPlayer_Board_display(board1 , board2 , turn);
    		setColor(WHITE , RED);
	 		cout << "\nPRESS ANY BUTTON FOR NEXT PLAYER TURN\n" ;
	 		setColor(WHITE , BLACK);
	 		getch() ;
		}
		else 
		{
			clearScreen() ;
			///////////////////////Doing the Fake bool work////////////////////////////////////////
    							do_fake_bool_work(board1  , 0); // simple checks for player1 , we'll adding turn
    							do_fake_bool_work(board2  , 1);// simply checks for player2    // was not necessary
    			///////////I'll jst call this before displaing the main board every time
    		///////////////////////////////////////////////////////////////////////////////////////
			total_attacks = get_ships_data(board2 ,  turn) ;
			if(total_attacks == 0) // meaning ships destroyed
    		{
    			clearScreen() ;
    			displayResult(Player1_Score , Player2_Score) ;
    			break ;
			}
			vsPlayer_Board_display(board1 , board2 , turn);
			//// Now for the PLayer attack i have to pass the global boats which would check the count condition at 
    		// the end cause i can't pass more than on board as parameter due to restriction
    		// here i will initialize the global boat according to player 2 i.e my opponent
    		for(int st = 0 ;  st <= 10 - 1  ; st += 1)
    		{
    			for(int st2 = 0 ;  st2 <= 10 - 1 ;  st2 += 1)
    			{
    				global_boat_pass[st][st2] = player_1_board[st][st2] ;
				}
			}
			PlayerAttack(board1 , Player2_Score) ;
			clearScreen();
			///////////////////////Doing the Fake bool work////////////////////////////////////////
    							do_fake_bool_work(board1  , 0); // simple checks for player1 , we'll adding turn
    							do_fake_bool_work(board2  , 1);// simply checks for player2    // was not necessary
    			///////////I'll jst call this before diplaing the main board every time
    		///////////////////////////////////////////////////////////////////////////////////////
			
    		vsPlayer_Board_display(board1 , board2 , turn);
    		setColor(WHITE , RED);
	 		cout << "\nPRESS ANY BUTTON FOR NEXT PLAYER TURN\n" ;
	 		setColor(WHITE , BLACK);
	 		getch() ;
		}
    	turn++ ; 
	}
}

char attack_board_1[10][10] ;
char attack_board_2[10][10] ;

void PlayervsPlayer()
{	
    initializeBoard(attack_board_1) ;
	initializeBoard(attack_board_2) ;	
	init_fake_bool(fake_bool_1) ;
	init_fake_bool(fake_bool_2) ;
    vsPlayer(attack_board_1 , attack_board_2) ;	
}


////////////////////////////////////////Player vs Player ends here///////////////////////////////////////////
// player vs computer 

// for this i will make new global variables down_below	  // Well not necessary to do
char player3_board[10][10] ;
char comp_board[10][10];
char attack_board_3[10][10] ; 
char attack_board_comp[10][10] ;


void do_fake_bool_work_2(char player_board[10][10] , int turn)
{
	int ships_count = 0 ;
	if(turn % 2 == 0) // Player 1  ships data of total ships left
	{
		for(int st = 0 ; st <= 5 - 1  ; st += 1)
		{
			if(player3_ship_location[st][3] == 'H') // meaning ship is placed horizontally
			{
				int ship_size = player3_ship_location[st][2] - '0' ; // get the row of player1 shiplocation ship size
				int count = 0 ; // i will use count to determine if the ship is still good or not if count is 0 ship that ship is dead
				int row = player3_ship_location[st][0] - '0' ;
				int column = player3_ship_location[st][1] - '0' ;
				for(int st = 0 ; st <= ship_size - 1 ;  st += 1)
				{
					if(player_board[row][column + st] == '~')
					{
						count += 1 ;
					}
				}
				// meaning ship is meaning ship is not alive mark that ship location on fake boolean array of player 1
				// false
				if(count == 0) 
				{
				   for(int st = 0 ; st <= ship_size - 1 ;  st += 1)
					{
						fake_bool_1[row][column + st] = true ; 
					}	
				}
			}
			else
			{//vertical
				int ship_size = player3_ship_location[st][2] - '0' ; // get the row of player1 shiplocation ship size
				int count = 0 ; // i will use count to determine if the ship is still good or not if count is 0 ship that ship is dead
				int row = player3_ship_location[st][0] - '0' ;
				int column = player3_ship_location[st][1] - '0' ;
				for(int st = 0 ; st <= ship_size - 1 ;  st += 1)
				{
					if(player_board[row + st][column] == '~')
					{
						count += 1 ;
					}
				}
				if(count == 0) // meaning ship is not alive 
				{
					for(int st = 0 ; st <= ship_size - 1 ;  st += 1)
					{
						fake_bool_1[row + st][column] = true ;
					}
				}
			} // END INNER ELSE
		}  // END For
	}// END MAIN IF
	else // Computer  ships data
	{
		for(int st = 0 ; st <= 5 - 1  ; st += 1)
		{
			if(comp_ship_location[st][3] == 'H') // meaning ship is placed horizontally
			{
				int ship_size = comp_ship_location[st][2] - '0' ; // get the row of player1 shiplocation ship size
				int count = 0 ; // i will use count to determine if the ship is still good or not if count is 0 ship that ship is dead
				int row = comp_ship_location[st][0] - '0' ;
				int column = comp_ship_location[st][1] - '0' ;
				for(int st = 0 ; st <= ship_size - 1 ;  st += 1)
				{
					if(player_board[row][column + st] == '~')
					{
						count += 1 ;
					}
				}
				if(count == 0) // meaning ship is not alive 
				{
					for(int st = 0 ; st <= ship_size - 1 ;  st += 1)
					{
						fake_bool_2[row][column + st] = true ; 
					}
				}
			}
			else
			{
				int ship_size = comp_ship_location[st][2] - '0' ; // get the row of player1 shiplocation ship size
				int count = 0 ; // i will use count to determine if the ship is still good or not if count is 0 ship that ship is dead
				int row = comp_ship_location[st][0] - '0' ;
				int column = comp_ship_location[st][1] - '0' ;
				for(int st = 0 ; st <= ship_size - 1 ;  st += 1)
				{
					if(player_board[row + st][column] == '~')
					{
						count += 1 ;
					}
				}
				if(count == 0) // meaning ship is not alive 
				{
					for(int st = 0 ; st <= ship_size - 1 ;  st += 1)
					{
						fake_bool_2[row + st][column] = true ;
					}
				}
			} // END INNER ELSE
		}  // END For
	} // END OUTER ELSE
}



//BUSHRA


void computerAttack(char playerBoard[10][10], int &computerScore)
{
    int r, c;
    int shots = total_attacks + 1 ;
    while (shots > 0)
    {
        r = rand() % 10;
        c = rand() % 10;
        // validation for not attacking again
        if (playerBoard[r][c] == 'X' || playerBoard[r][c] == 'O')
            {
            	continue ; 
			}
     	if (global_boat_pass[r][c] == 'S')
     	{
       		playerBoard[r][c] = 'X';
       		_attacked_ = true ;
   		    updateScore(computerScore) ;
        	cout << "Computer strike your ship at " << r << "," << c <<endl;
     	}
     else
     	{
        	playerBoard[r][c] = 'O';
        	_attacked_ = false ;
   		    updateScore(computerScore) ;
        	cout << "Computer MISSED at " << r << "," << c <<endl;
     	}
     shots-- ;
   } 
}









void vsComputer_Board_display(char board1[10][10] , char board2[10][10]  , int current_turn = 0)
{
	cout << endl << endl ;
  	cout << "    PLAYER 1 BOARD " ;
  	cout << "                              ";
  	if(current_turn % 2 == 0)
  	{
  		setColor(RED , 14) ;
  		cout << " Player 1 Turn "; 
  		setColor(WHITE , BLACK) ;
	}
	else
	{
		setColor(RED , 14) ;
		cout << " Computer Turn " ;
		setColor(WHITE , BLACK) ;
	}
	cout << "                             " ;
	cout << "  COMPUTER BOARD " << "\n" ;
	cout << "                      " ; 
	cout << "       0     1     2     3     4     5     6     7     8     9  " << endl;
	cout << "  0 1 2 3 4 5 6 7 8 9 " ; 
	cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" ;
	cout << "      0 1 2 3 4 5 6 7 8 9" ;
	cout << endl ;  
  	//  NOTE TO MYSELF : THE MID BOARD WILL CHANGE ACCORDING TO THE CURRENT TURN
  	if(current_turn % 2 == 0) // Player 1 turn
  	{
  	   for(int st = 0 ;  st <= 10 - 1  ; st += 1)
  	   {  
  	      cout << st << " " ; 
  	      for(int st2 = 0  ; st2 <= 10 - 1 ;  st2  += 1) // the Player 1 board printing part
		      { 
		    	if(board1[st][st2] == '~')
		    	{
		    		cout << "." << " " ;
				}
				else
				{
					cout << board1[st][st2] << " " ;
				}
		      }
		      
		    cout << "  " << st <<" Š"; // weird symbol
    		for (int st2 = 0; st2 <= 10 - 1; st2++)
    		{
        		char cell = board2[st][st2]; 
        		
        		if(fake_bool_2[st][st2] == true)
        		{
        		  setColor(WHITE, MAGENTA); cout << "  D  "; setColor(7,0); cout << "Š";	
				}
				else  if(cell == 'X')
        		{
        			setColor(WHITE, RED); cout << "  X  "; setColor(7,0); cout << "Š";
				}
				else if(cell == 'O')
				{
					setColor(BLACK, WHITE); cout << "  O  "; setColor(7,0); cout << "Š";
				}
				else
				{
				setColor(7, 1); cout << "  ~  "; setColor(7,0); cout << "Š";
			    }
    		}
    		
    		cout << "    "; 
    		cout << st << " " ; 
  	      	for(int st2 = 0  ; st2 <= 10 - 1 ;  st2  += 1) // the Player 2 board printing part
		   		{
		    	if(board2[st][st2] == '~')
		    	 {
		    		cout << "." << " " ;
				 } 
				   else
				 {
					cout << board2[st][st2] << " " ;
				 }
		        }
    		cout << endl ; 
    		cout << "                      " ;
            cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----Š" ;
            cout << endl;
	   } // END MAIN FOR LOOP
	}// END IF
	else // COMPUTER TURN
	{
		for(int st = 0 ;  st <= 10 - 1  ; st += 1)
  	   {  
  	      cout << st << " " ; 
  	      for(int st2 = 0  ; st2 <= 10 - 1 ;  st2  += 1) // the Player 3 board printing part
		      { 
		    	if(board1[st][st2] == '~')
		    	{
		    		cout << "." << " " ;
				}
				else
				{
					cout << board1[st][st2] << " " ;
				}
		      }
		   cout << "  " << st <<" Š"; // weird symbol
    		for (int st2 = 0; st2 <= 10 - 1; st2++)
    		{
        		char cell = board1[st][st2]; // Meaning  turn nCOMPUTER i will display the player 3 board 
				
				if(fake_bool_1[st][st2] ==  true)
				{
					setColor(WHITE, MAGENTA); cout << "  D  "; setColor(7,0); cout << "Š";
				}
				else if(cell == 'X')
        		{
        			setColor(WHITE, RED); cout << "  X  "; setColor(7,0); cout << "Š";
				}
				else if(cell == 'O')
				{
					setColor(BLACK, WHITE); cout << "  O  "; setColor(7,0); cout << "Š";
				}
				else
				{
				setColor(7, 1); cout << "  ~  "; setColor(7,0); cout << "Š";
			    }   
    		}
    		cout << "    "; 
    		cout << st << " " ; 
  	      	for(int st2 = 0  ; st2 <= 10 - 1 ;  st2  += 1) // the COMPUTER board printing part
		   		{
		    	if(board2[st][st2] == '~')
		    	 {
		    		cout << "." << " " ;
				 } 
				   else
				 {
					cout << board2[st][st2] << " " ;
				 }
		        }
    		cout << endl ; 
    		cout << "                      " ;
            cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----Š" ;
            cout << endl;
	   } // END MAIN FOR LOOP	
	} // END ELSE
	setColor(15 , RED) ;
	cout << " Player 1 Score : "  ; 
	cout << Player3_Score ; 
	setColor(WHITE , BLACK)  ;
	cout  << "                                                " ;
	cout << "                         " ;
	setColor(15 , RED) ;
	cout << "Computer Score : " << computer_Score << endl ;
	setColor(WHITE , BLACK) ;  
} // end function

bool placing(char grid[10][10],int row,int col,int size, bool ver)
 {
 	if(ver)
 	{
 		if(row+size>10)
 		return false;
 		for(int i=0;i<size;i++)
 		if(grid[row+i][col]=='S')
         return false;	 
	 }
	 else
	 {if(col+size>10)
	 return false;
	 for(int i=0;i<size;i++)
	   if(grid[row][col+i]=='S')
	   return false;
	 }
	 return true;
 }
 
 void placement(char grid[10][10],int row,int col,int size,bool ver)
 {
 	for(int i=0;i<size;i++)
 	{
	 	if(ver)
 		{
 			grid[row+i][col]='S';
		}
 		else
 	 	{
 	   		grid[row][col+i] =  'S' ;	
	 	}	
	}
	/// Bushra code is above the loop // here i will add my own  code to store the cordiantes of the
	// Ships listen here this i will just do  the location storing work here  , and storing cordinates for who player
	// or computer  , i will control that through the global variable and 2D array by intializing them to the 
	// beginning i.e  the st_idx_for_storing location and and here after i get the codinated i will use some again global 
	// 2D aray to store the location and then assign it  to the original array of the main player 2D cord and then
	//  the computer location 2D array.   and i  also have to use the turn  thing too. 
	if(ver == true)
		{ 
		global_board_pass_for_location[st_idx_for_ship_location][0] = row + '0';  // to conveet to character
		global_board_pass_for_location[st_idx_for_ship_location][1] = col + '0' ; 
		global_board_pass_for_location[st_idx_for_ship_location][2] = size + '0' ;
		global_board_pass_for_location[st_idx_for_ship_location][3] = 'V' ; // It is placed horizontally
		st_idx_for_ship_location += 1 ;// move to next location for player 1  
		}
	else // Horizontal case
		{			   
		    global_board_pass_for_location[st_idx_for_ship_location][0] = row + '0';  // to conveet to character
		    global_board_pass_for_location[st_idx_for_ship_location][1] = col + '0' ; 
		    global_board_pass_for_location[st_idx_for_ship_location][2] = size + '0' ;
		    global_board_pass_for_location[st_idx_for_ship_location][3] = 'H' ; // It is placed horizontally
		    st_idx_for_ship_location += 1 ;// move to next location for player 1  
		}
}
 
 void setRandomships(char board[10][10])
 {
 	int sizes[5] = {5,4,3,3,2};
 	int numShip = 5 ;
 	for(int i=0;i<numShip;i++)
 	{bool placed=false;
 	while(!placed)
 	
 	{ int r=rand()%10;
 	  int c=rand()%10;
 	  bool ver =rand()%2;
 	  if(placing(board,r,c,sizes[i],ver))
 	  {
 	  	placement(board,r,c,sizes[i],ver);
 	  	placed=true;
	   }
	 }
	 }
 }
void manualplacing(char grid[10][10], string ships[], int sizes[], int numship)
 {
 for(int i=0;i<numship;i++)
  {
 	int row,col;
 	bool ver=false; //default horizontal
 	while(true)
 	{
 		    clearScreen() ;
	 		printBoard(grid , false);
 			setColor(15,0);
 	   		cout << "Placing " << ships[i] << " (" << sizes[i] << " cells)\n";
            cout << "Enter starting row (0-9): "<<endl;
            cin >> row;
            cout << "Enter starting column (0-9): "<<endl;
            cin >> col;
//validation 
            if (row < 0 || row > 9 || col < 0 || col > 9)
	 {
	 	setColor(12,0);
	 	cout<<"Invalid coordinate Try Again "<<endl;
	 	setColor(7,0);
	 	continue;
	 }
	int rotate;
	cout<<"Direction is default horizontal"<<endl;
	cout<<"Enter 0 to keep horizontal or 1 to change vertical"<<endl;
	cin>>rotate;

	 if(rotate==1)
	 {
	 	   ver=true;
	       if(!placing(grid,row,col,sizes[i],ver))
	       {
		   	setColor(12,0);
	       	cout<<"Vertical placement is not in coordinates! "<<endl;
	       	setColor(7,0);
	        ver=false;//keep horizontal
	       }
	}
	    if(!placing(grid,row,col,sizes[i],ver))
	    {
			setColor(12,0);
	    	cout<<"Can't place here as out of boundry & overlap"<<endl;
	    	setColor(7,0);
	    	continue;
	    }
    placement(grid,row,col,sizes[i],ver);
    break;
	 }
  }
}


 
 
void Mode2_ship_placement()
{	
 	srand(time(0));
// 	char grid[10][10]; No need at alll
  	initializeBoard(player3_board);
  	cout << "Enter your name\n" ;
  	cin >> player3_name ; 
  	clearScreen() ;
	cout << "Place your ships " << player3_name << endl ; 
	ask_ship_color() ;
 	string ships[5] = {"Aircraft Carrier", "Battleship", "Destroyer", "Submarine", "Patrol Boat"};
    int sizes[5] = {5,4,3,3,2};
    int numShips = 5;
    setColor(15,0);
    clearScreen() ;
    cout << "=== Battleship Ship Placement with Colored Board ===\n";
    cout << "1. Manual Placement"<<endl<<"2. Random Placement"<<endl<<"Choose an option: ";
    int choice;
    cin >> choice;
    while(choice < 1 || choice > 2)
    {
    	cout << "Enter correct Choice\n" ;
    	cin >> choice ;
	}
	/////////////////////////////Here i saad am intializing the st_idx for location of player3 ships////////////
	st_idx_for_ship_location = 0 ;
	if(choice==1)
     {
     	manualplacing(player3_board, ships, sizes, numShips);
     	
	 }
    else
     {
     	setRandomships(player3_board);
	 }
	 // After the above any conditions ends i will have my ships location in the global 2D array  , i just have to 
	 // paste it to the player3 board as done below.
	// Since in the bushra code i will passing a global 2D array to store the value of the locations then i will
	// copy paste them in my original player code
	for(int st = 0  ; st <= 5 - 1 ; st += 1)
	{	
	  player3_ship_location[st][0] =  global_board_pass_for_location[st][0] ;
	  player3_ship_location[st][1] =  global_board_pass_for_location[st][1] ;
	  player3_ship_location[st][2] =  global_board_pass_for_location[st][2] ;
	  player3_ship_location[st][3] =  global_board_pass_for_location[st][3] ;	
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////// 
     setColor(15,0);
     cout << "Final ship placement for Player :"<<endl;
     printBoard(player3_board , false);
     cout << "Press  any button continue\n" ; 
	 getch() ;   
	 clearScreen() ;
	 
	 /////////////////////////////Here i saad am intializing the st_idx for location of computer ships////////////
	 st_idx_for_ship_location = 0  ;
	 
	 initializeBoard(comp_board) ;
	 setRandomships(comp_board) ; // Here i am just directly calling the rand_placement for comp ships
	 cout << "Computer Board : \n" ;
	 printBoard(comp_board , true) ;
	 // After the above any conditions ends i will have my ships location in the global 2D array  , i just have to 
	 // paste it to the computer board as done below.
	// Since in the bushra code i will passing a global 2D array to store the value of the locations then i will
	// copy paste them in my original player code
	for(int st = 0  ; st <= 5 - 1 ; st += 1)
	{	
	  comp_ship_location[st][0] =  global_board_pass_for_location[st][0] ;
	  comp_ship_location[st][1] =  global_board_pass_for_location[st][1] ;
	  comp_ship_location[st][2] =  global_board_pass_for_location[st][2] ;
	  comp_ship_location[st][3] =  global_board_pass_for_location[st][3] ;	
	}
	/////////////////////s//////////////////////////////////////////////////////////////////////////////////////// 

	 
	  
	 // place the ships for the global comp_board array 
     setColor(10,0) ;
     cout << "All ships are placed successfully for Computer!\n"<<endl;
     setColor(7,0) ; 
     cout << "Get Ready for the Next Battle , Press any button to continue\n" ;
     getch();
     clearScreen() ;
}
 ////////////////////////////////After ships placement and location marking is done/////////////////////////////////////
 /////////////// below now starts the main player vs computer attack
 
 int get_ships_data_Mode_2(char player_board[10][10] , int turn)
{
	int ships_count = 0 ;
	if(turn % 2 == 0) // Player 1  ships data of total ships left
	{
		for(int st = 0 ; st <= 5 - 1  ; st += 1)
		{
			if(player3_ship_location[st][3] == 'H') // meaning ship is placed horizontally
			{
				int ship_size = player3_ship_location[st][2] - '0' ; // get the row of player1 shiplocation ship size
				int count = 0 ; // i will use count to determine if the ship is still good or not if count is 0 ship that ship is dead
				int row = player3_ship_location[st][0] - '0' ;
				int column = player3_ship_location[st][1] - '0' ;
				for(int st = 0 ; st <= ship_size - 1 ;  st += 1)
				{
					if(player_board[row][column + st] == '~')
					{
						count += 1 ;
					}
				}
				if(count != 0) // meaning ship is still alive 
				{
					ships_count += 1 ;
				}
			}
			else
			{
				int ship_size = player3_ship_location[st][2] - '0' ; // get the row of player1 shiplocation ship size
				int count = 0 ; // i will use count to determine if the ship is still good or not if count is 0 ship that ship is dead
				int row = player3_ship_location[st][0] - '0' ;
				int column = player3_ship_location[st][1] - '0' ;
				for(int st = 0 ; st <= ship_size - 1 ;  st += 1)
				{
					if(player_board[row + st][column] == '~')
					{
						count += 1 ;
					}
				}
				if(count != 0) // meaning ship is still alive 
				{
					ships_count += 1 ;
				}
			} // END INNER ELSE
		}  // END For
	}// END MAIN IF
	else // Computer  ships data
	{
		for(int st = 0 ; st <= 5 - 1  ; st += 1)
		{
			if(comp_ship_location[st][3] == 'H') // meaning ship is placed horizontally
			{
				int ship_size = comp_ship_location[st][2] - '0' ; // get the row of player1 shiplocation ship size
				int count = 0 ; // i will use count to determine if the ship is still good or not if count is 0 ship that ship is dead
				int row = comp_ship_location[st][0] - '0' ;
				int column = comp_ship_location[st][1] - '0' ;
				for(int st = 0 ; st <= ship_size - 1 ;  st += 1)
				{
					if(player_board[row][column + st] == '~')
					{
						count += 1 ;
					}
				}
				if(count != 0) // meaning ship is still alive 
				{
					ships_count += 1 ;
				}
			}
			else
			{
				int ship_size = comp_ship_location[st][2] - '0' ; // get the row of player1 shiplocation ship size
				int count = 0 ; // i will use count to determine if the ship is still good or not if count is 0 ship that ship is dead
				int row = comp_ship_location[st][0] - '0' ;
				int column = comp_ship_location[st][1] - '0' ;
				for(int st = 0 ; st <= ship_size - 1 ;  st += 1)
				{
					if(player_board[row + st][column] == '~')
					{
						count += 1 ;
					}
				}
				if(count != 0) // meaning ship is still alive 
				{
					ships_count += 1 ;
				}
			} // END INNER ELSE
		}  // END For
	} // END OUTER ELSE
	
	return ships_count  ;
}




//2nd function   

// Execute because  i have to make  a sepearte vsComputer function , cause i have to pass the board taken from
// mode 2 ship placement as well
void vsComputer_Excecute(char playerBoard[10][10], char computerBoard[10][10]) 
{
	// After this Function ends i will have my  player and computer ships placed in a global 2D array  
    // Similarly i
    int turn  = 0 ;
    while (true)
    {
        // ---------------- PLAYER TURN ----------------
        if(turn % 2 == 0) // player 3  turn
        {
        	clearScreen() ;
        	///////////////////////Doing the Fake bool work////////////////////////////////////////
    				do_fake_bool_work_2(playerBoard  , 0); // simple checks for player1 , we'll adding turn
    				do_fake_bool_work_2(computerBoard  , 1);// simply checks for player2    // was not necessary
    		///////////I'll jst call this before diplaing the main board every time
    		///////////////////////////////////////////////////////////////////////////////////////
        	
          vsComputer_Board_display(playerBoard , computerBoard , turn)	;
          total_attacks = get_ships_data_Mode_2(playerBoard,  turn);
          if(total_attacks == 0)//MEANS NO OF SHIPS
          {
          	 clearScreen() ;
          	 displayResult_2(Player3_Score , computer_Score) ;
          	 break ;
		  }
          ///////////Assigining the global boat 2D array of computer board since i am attacking computer
		  for(int st = 0 ;  st <= 10 - 1  ; st += 1)
    		{
    			for(int st2 = 0 ;  st2 <= 10 - 1 ;  st2 += 1)
    			{
    				global_boat_pass[st][st2] = comp_board[st][st2] ;
				}
			}
		  PlayerAttack(computerBoard , Player3_Score) ;
		  clearScreen() ;
		  
		  ///////////////////////Doing the Fake bool work////////////////////////////////////////
    				do_fake_bool_work_2(playerBoard  , 0); // simple checks for player1 , we'll adding turn
    				do_fake_bool_work_2(computerBoard  , 1);// simply checks for player2    // was not necessary
    		///////////I'll jst call this before diplaing the main board every time
    		///////////////////////////////////////////////////////////////////////////////////////
        	
          vsComputer_Board_display(playerBoard , computerBoard , turn)	;
          setColor(WHITE , RED) ;
          cout << "Press any Button to see the Computer Attacks\n" ;
          setColor(WHITE , BLACK); 
          getch() ;
          clearScreen() ;
		}
		else
		{
			clearScreen() ;
			total_attacks = get_ships_data_Mode_2(computerBoard,  turn);
			if(total_attacks == 0)
          	{
          	 clearScreen() ;
          	 displayResult_2(Player3_Score , computer_Score) ;
          	 break ;
		  	}
		  	///////////Assigining the global boat 2D array of computer board since i am attacking computer
		  for(int st = 0 ;  st <= 10 - 1  ; st += 1)
    		{
    			for(int st2 = 0 ;  st2 <= 10 - 1 ;  st2 += 1)
    			{
    				global_boat_pass[st][st2] = player3_board[st][st2] ;
				}
			}
			computerAttack(playerBoard , computer_Score) ;
			clearScreen() ; // to remove the computer MiSSED and Strike thing
			
			// I am doing the fake bool work here only one time since i  need to show computer board turn one time only
			
			
			///////////////////////Doing the Fake bool work////////////////////////////////////////
    		do_fake_bool_work_2(playerBoard  , 0); // simple checks for player1 , we'll adding turn
    		do_fake_bool_work_2(computerBoard  , 1);// simply checks for player2    // was not necessary
    		///////////I'll jst call this before diplaing the main board every time
    		///////////////////////////////////////////////////////////////////////////////////////
    		vsComputer_Board_display(playerBoard , computerBoard , turn)	;
    		if(get_ships_data_Mode_2(playerBoard,  turn) == 0)
          	{
          	 setColor(GREEN , BLACK) ;
          	 cout << "Game Ended , Press any button to see the Result" ;
          	 setColor(WHITE , BLACK) ;
          	 clearScreen() ;
          	 displayResult_2(Player3_Score , computer_Score) ;
          	 break ;
		  	}
			setColor(WHITE , RED) ;
          	cout << "Press any Button to continue to your turn\n" ;
          	setColor(WHITE , BLACK);
			getch() ;	
		}
		turn++ ;
	}
        
}


 
 
void vsComputer()
{
    initializeBoard(attack_board_3);
	initializeBoard(attack_board_comp) ;	
	Mode2_ship_placement() ;
	// After this function ends i will have my both player 3 and computer ships location on the global char baord
	// and i will have both my locations
	
	init_fake_bool(fake_bool_1) ;
	init_fake_bool(fake_bool_2) ;
	vsComputer_Excecute(attack_board_3  , attack_board_comp) ;
}
 
 
 
 
 
 /////////////////////////////Above Bushra Code ends/////////////////////////////////
 
 
 
void startNewGame()
{
   cout << "Enter your mode of Gameplay\n" ;
   cout << "1. Player vs Player\n" ;
   cout << "2. Player vs Computer\n" ;
   int cho ;
   cout << "Choice: "; 
   cin >> cho  ;
   while(cho < 1 || cho  > 2)
   {
   	cout << "Enter correct Choice\n" ;
   	cin >> cho   ;
   }
   clearScreen() ;  
   if(cho == 1)
   {
   	 PlayervsPlayer(); 
   }
   else
   {
   	 vsComputer() ;
   }  
}

void showLeaderboard(const string playerNames[], const int scores[], int totalPlayers) {
    string names[1000];
    int scr[1000];//score
    int total = 0;
    ifstream fin("highscore.txt");
    if (fin.is_open())  // opening of file reading
	 {while (fin >> names[total] >> scr[total]) {
            total++;
            if (total >= 1000) break;
        }
        fin.close();//closing of file reading
    }
    for (int i = 0; i < totalPlayers && total < 20; i++) {
        names[total] = playerNames[i];
        scr[total] = scores[i];
        total++;
    }

    //sorting in decending ordr
    for (int i= 0; i < total - 1; i++) {
        for (int j = 0; j < total - 1 - i; j++) {
            if (scr[j] < scr[j + 1]) {
                // sorting the scores
                int tempScore = scr[j];
                scr[j] = scr[j+ 1];
                scr[j + 1] = tempScore;

                // swap  the names
                string tempName = names[j];
                names[j] = names[j + 1];
                names[j+ 1] = tempName;}} }

    // saving only 10 top scores
    ofstream fout("highscore.txt");// opening writing file
    for (int x = 0; x < total && x < 10; x++) {
        fout << names[x] << " " << scr[x] << endl;
    }
    fout.close();//closing the file
    
    cout << "+++++ LEADERBOARD ++++"<<endl;//as only top 10 so limit is top 10
    for (int x = 0; x < total && x < 10; x++)//showing the index only 
	{
        cout << x + 1 << ". " << names[x] << " - " << scr[x] << endl;
    }
}


 

void showGameMenu()
{
	clearScreen() ;
	int choice; 
	
	
    std::cout << "\n";
    setColor(CYAN  , BLACK) ;
    std::cout << "  ____  ____      __        __    _    ____  ____  _   _ ___ ____      ____    _  _____ _____ _     _____ " << std::endl;
    std::cout << " |___ \\|  _ \\     \\ \\      / /   / \\  |  _ \\/ ___|| | | |_ _|  _ \\    | __ )  / \\|_   _|_   _| |   | ____|" << std::endl;
    setColor(DARKRED , BLACK) ;
	std::cout << "   __) | | | |     \\ \\ /\\ / /   / _ \\ | |_) \\___ \\| |_| || || |_) |   |  _ \\ / _ \\ | |   | | | |   |  _|  " << std::endl;
    std::cout << "  / __/| |_| |      \\ V  V /   / ___ \\|  _ < ___) |  _  || ||  __/    | |_) / ___ \\| |   | | | |___| |___ " << std::endl;
    setColor(GREEN , BLACK) ;
	std::cout << " |_____|____/        \\_/\\_/   /_/   \\_\\_| \\_\\____/|_| |_|___|_|       |____/_/   \\_\\_|   |_| |_____|_____|" << std::endl;
    setColor(WHITE, BLACK);
	std::cout << "\n\n\n";
	 	
  	cout << "                     _                                                             ~~~             |\n" ;
  	cout << "                    | \\                                                       ~~~~     ~~~~      -----                    |\n" ;
  	cout << "                     '.|                                                           ~~~           )___(                  -----\n" ;
  	cout << "     _-   _-    _-  _-||    _-    _-  _-   _-    _-    _-                                          |                    )___(\n" ;
  	cout << "       _-    _-   - __||___    _-       _-    _-    _-                                         ---------                  |\n" ;
  	cout << "    _-   _-    _-  |   _   |       _-   _-    _-                                              /         \\              -------\n" ;
  	cout << "      _-    _-    /_) (_) (_\\        _-    _-       _-                                       /___________\\            /       \\\n" ;
  	cout << "              _.-'           `-._      ________       _-                                           |                 /_________\\\n" ;
  	cout << "        _..--`                   `-..'       .'                                             ---------------               |\n"  ;
  	cout << "    _.-'  o/o                     o/o`-..__.'        ~  ~                                  /               \\        -------------\n" ;
  	cout << " .-'      o|o                     o|o      `.._.  // ~  ~                                 /                 \\      /             \\\n"   ;
  	cout << " `-._     o|o                     o|o        |||<|||~  ~                                 /___________________\\    /_______________\\\n" ;
  	cout << "     `-.__o\\o                     o|o       .'-'  \\ ~  ~                               ____________|______________________|__________\n" ;
  	cout << "          `-.______________________\\_...-``'.       ~  ~                                \\_                                        _/\n" ;
	cout << "                                    `._______`.                                           \\______________________________________/       \n" ;
  	setColor(BLUE , BLUE) ;
	cout << " ~~...~            ~~~.....~~                 ~~....~.             ~~.....~~       ~~..             ...~~~.           ....~~~...     ..~\n" ;
  	setColor(WHITE , BLACK) ;
  	system("PAUSE");
    system("cls");
  	
  	cout << "\n\n\n" ;
  	
  	setColor(YELLOW  , BLACK) ;
  	cout<<"=============================================================================================================================\n";
  	setColor(WHITE , RED) ;
	cout<<"                                                        BATTLESHIP GAME MENU                                                 \n";
  	setColor(WHITE , BLACK) ;
  	setColor(MAGENTA , BLACK) ;
	cout<<"=============================================================================================================================\n";
  	setColor(WHITE , BLACK) ;
  	cout<<"1. Start New Game\n";
  	cout<<"2. Instructions \n"  ;
  	cout<<"3. View Leaderboard\n";
  	cout<<"4. Exit \n";
 	cout<<"------------------------------------\n";
	cout<<" Enter choice(1-4): "  ;
	cin>>choice   ;
	clearScreen() ;
 	switch(choice)
 	{
 	case 1:
 		clearScreen() ;
 		startNewGame();
 		break;
 		
 	case 2:
 		clearScreen() ;
 		Instructions() ;
 		break;
 		
 	case 3:
 		{
 		clearScreen() ;
		string newPlayer[1];
        int newScore[1];
        cout << "================================LEADERBOARD====================================\n" ;
        showLeaderboard(newPlayer, newScore, 0);
        setColor(WHITE  , RED) ;
        cout << "Press any button to go back to main Menu\n";
        setColor(WHITE , BLACK) ;
        getch() ;
        showGameMenu() ;
 		break;
  	   }  
 	case 4:
 		cout<<"Exiting the Game  ..."<<endl;
 		break;
         
     default :
	  cout<<"Invalid choice Please select 1-4 Exiting the Game"<<endl;    
   }
} 
 

int main()
{ 
	  //  HWND hWnd = GetConsoleWindow();
	   // ShowWindow(hWnd,SW_SHOWMAXIMIZED);
    // i had to use above function in linux to max-size the terminal when game runs
    // Don't try it in Windows else your system will crash
	showGameMenu() ;
    return 0;
}

 
 
 
 








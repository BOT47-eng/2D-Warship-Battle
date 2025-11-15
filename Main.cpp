#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <stdlib.h>
using namespace std ;


// Color codes
const int BLACK = 0;
const int BLUE = 1;
const int GREEN = 2;
const int CYAN = 3;
const int RED = 4;
const int MAGENTA = 5;
const int YELLOW = 6;
const int WHITE = 7;









char board[10][10] ;
bool ships[5] = {true , true , true , true , true} ;
int user_choice_for_ship ; // making it global so i can use it revert the not chosen ship back to normal 


// to clear the screen i can normally use the function only also lol

void clearScreen()
{
	system("CLS") ;
}

void re_init_ships(){
  for(int st = 0  ;  st  <= 5  -  1   ; st += 1)
  {
  	ships[st] = true ; 
  }
}




// Set text and background color in Windows console made by sir so will use it gratefully
void setColor(int textColor, int bgColor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), bgColor * 16 + textColor);
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
bool setManuallyShips(char board[10][10] , int ship_size)
{ 
	cout << "Choose Placement Option :  1 = Manual , 2 = Random\n" ;
	cout << "Choice : " ; 
	int op ; 
	cin  >> op  ;
	while(op < 1 || op > 2)
	{
		cout << "Enter Correct Choice\n" ; 
		cin >> op ;
	}
	switch(op) // now switching between cases to
	{
	  case 1 :
	  	{
	  	  
			cout << "1. Horizontally\n2. Vertically\n" ; 
			int choice ; 
    		cin >> choice ;
			while(choice < 1 || choice > 2)
			{
	   		cout << "Enter correct Choice\n" ;
	   		cin >> choice ;	
			} 
    		switch(choice)
			{
    			case  1 :
    		{			
	  	   		int flag  = true ; // don't touch this flag
	  	   		while(flag)
	  	   		{ 
	  		 		int row  ; 
	  	 	 		cout << "Enter starting row (0 - 9) : "  ;
	  	     		cin >> row ;
	  	     		while(row < 0 ||  row > 9) // input validation
			   		{
			  	 		cout << "\nEnter correct row : " ;
			  	 		cin >> row ;
			   		}
			 	int column ;
			 	cout << "Enter Starting Column (0  - 9) : " ;
			 	cin >> column ;
			 	while(column < 0 || column  > 9)
			  	{ 
				 	cout << "\nEnter correct column : " ;
			  	 	cin >> column ;
			  	}
			  // Check if the ship to be placed is within the bounds of that row column like is there enough space for ship to be place
			  	if(9 - column - ship_size <   0)
			  	{
			  	 // meaning kay it is not in the bound of the row column  breaks that rule
			  	  setColor(4  , 0) ;
				  cout << "\nOUT OF BOUND KEEP IT IN RANGE\n" ;
				  setColor(7 , 0) ; //changing back to original
			  	  return false ; 
			  	}
		    // Check if that place is clear where the ships are to be placed 
		     for(int st  = 0 ; st <= ship_size - 1  ;  st += 1)
		     	{ 
		   	   		if(board[row][column + st] != '~') //  check if that row or column is filled or not
		   	   		{	 
		   	     	setColor(4  , 0) ;
		   	 	 	cout << "\nWRONG PLACEMENT CHOSE A NEW POSITION\n" ;
		   	 	 	setColor(7 , 0) ; // changing back to original
		   	 	 	return false ; // won't go forward when placing the ships
		       		}
		     	}
		     cout << ship_size ;
		    	for(int st  = 0 ; st <= ship_size - 1  ;  st += 1) // ONLY HORIZONTAL PART
		     	{
		   	   		board[row][column + st] = 'S' ; // That column ++ ;
		     	}
		    	flag = false ; // Ship was placed successfully
		   	}	
    		break  ;
		}// case  1 ends here
		case 2 : // for vertical
			{		
	  	   	int flag  = true ; // don't touch this flag
	  	   	while(flag)
	  	   		{	 
	  		 	int row  ; 
	  	 	 	cout << "Enter starting row (0 - 9) : "  ;
	  	     	cin >> row ;
	  	     	while(row < 0 ||  row > 9) // input validation
			   	{
			  	 cout << "\nEnter correct row : " ;
			  	 cin >> row ;
			   	}
			 	int column ;
			 	cout << "Enter Starting Column (0  - 9) : " ;
			 	cin >> column ;
			 	while(column < 0 || column  > 9)
			  	{ 
				 cout << "\nEnter correct column : " ;
			  	 cin >> column ;
			  	}
			  // Check if the ship to be placed is within the bounds of that row column like is there enough space for ship to be place
			  	if(9 - row - ship_size <   0)
			  	{
			  	 // meaning kay it is not in the bound of the row column  breaks that rule
			  	  setColor(4  , 0) ;
				  cout << "\nOUT OF BOUND KEEP IT IN RANGE\n" ;
				  setColor(7 , 0) ; //changing back to original
			  	  return false ; 
			  	}
		    	// Check if that place is clear where the ships are to be placed 
		     	for(int st  = 0 ; st <= ship_size - 1  ;  st += 1)
		     	{	 
		   	   if(board[row + st][column] != '~') //  check if that row or column is filled or not
		   	   		{	 
		   	     	setColor(4  , 0) ;
		   	 	 	cout << "\nWRONG PLACEMENT CHOSE A NEW POSITION\n" ;
		   	 	 	setColor(7 , 0) ; // changing back to original
		   	 	 	return false ; // won't go forward when placing the ships
		       		}
		     	}
		     	cout << ship_size ;
		    	for(int st  = 0 ; st <= ship_size - 1  ;  st += 1) // ONLY HORIZONTAL PART
		     	{
		   	   	board[row + st][column] = 'S' ; // That column ++ ;
		     	}
		    	flag = false ; // Ship was placed successfully
		   	}
		   break ;
			} // Case 2 ends here
		}// nested switch ends here	 
		  break ;	
		} // MAIN case  1 ends here
		case 2 : // if user choses the random option then  case 2
		{
			srand(time(0)) ; 
			while(true)
			{
			   int row = rand()  % 10 ;
			   int column = rand() % 10 ;
			   int v_or_h = rand()  % 2 ;  // 0 for vertical and 1 for horizontal
			   if(v_or_h == 1) // Places ship horizontally
			   {
			   	    bool flag = true ;
			   		while(9 - column - ship_size <=   0) // Yeah same old condition for row column check
			  		{	
			  	 	   // keep getting the column while it's out of bound
					   column = rand() % 10 ;	
			  		}
			  		while(9 - row - ship_size <=   0) // Yeah same old condition for row column check
			  		{	
			  	 	   // keep getting the row while it's out of bound
					   row = rand() % 10 ;	
			  		}
			  		for(int st  = 0 ; st <= ship_size - 1  ;  st += 1)
		             	 { 
		   	   			if(board[row][column + st] != '~') //  check if that row or column is filled it not
		   	   				{
		   	   					  flag = false ;
								  break ; // get new row and column for horizontal casew
		      			 	}
		    	 		}
		    	 	if(flag == false)
		    	 	{
		    	 		continue ;  // get the row and colume again
					}
		    	 	// Just place the ships successfully 
		    	 	for(int st  = 0 ; st <= ship_size - 1  ;  st += 1) // ONLY HORIZONTAL PART
		     			{
		   	   				board[row][column + st] = 'S' ; // That column ++ ;
		     			}
		     		// since ship is placed successfully break out of while loop
		     		break ;
			   }
			   else // Places ships vertically	
			   {
			   	bool flag = true ;
			   	while(9 - row - ship_size <=   0) // Yeah same old condition for column row check
			  		{	
			  	 	   // keep getting the  row while it's out of bound
					   row = rand() % 10 ;	
			  		} 
			  	while(9 - column - ship_size <=   0) // Yeah same old condition for row column check
			  		{	
			  	 	   // keep getting the column while it's out of bound
					   column = rand() % 10 ;	
			  		}	
			  		for(int st  = 0 ; st <= ship_size - 1  ;  st += 1) // rows and column switched here
		             	 { 
		   	   			if(board[row + st][column] != '~') //  check if that row or column is filled it not
		   	   				{
		   	   					  flag = false ; //  row is filled
								  break ; // get new row and column for vertical case since some ship is already placed there
		      			 	}
		    	 		}
		    	 		if(flag == false)
						 {
						 	continue ;  // get the rows and column again
						 }
		    	 		// just place the ships successfully now lmao since it isn't skipped 
		    	 	for(int st  = 0 ; st <= ship_size - 1  ;  st += 1) // ONLY HORIZONTAL PART
		     			{
		   	   				board[row + st][column] = 'S' ; // That column ++ ;
		     			}
		     			
		     			
		     			// if you wanna know the details in case of bug you can uncomment below lines AAAA FINALLY DID IT
//		     			cout << ship_size  << " " << row  << " " << column ;
//		                getch() ;
//		     			
		     			break ; //  ship is placed successfully
			   	 // vertcal case
			   }
		    }
		    
			break ;
		   
		}
	}
	return true; 
}



void display_board(char board[10][10])
{
    cout << "       0     1     2     3     4     5     6     7     8     9  " << endl;

    // Top border
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
    // Row 0
    cout << "  0 Š"; // weird symbol
    for (int st = 0; st < 10; st++)
    {
        char cell = board[0][st];
        if(cell == 'S') // meaning filled ship placed
        {
        	setColor(0, 6); cout << "  S  "; setColor(7,0); cout << "Š";
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
        if(cell == 'S') // meaning filled ship placed
        {
        	setColor(0, 6); cout << "  S  "; setColor(7,0); cout << "Š";
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
        if(cell == 'S') // meaning filled ship placed
        {
        	setColor(0, 6); cout << "  S  "; setColor(7,0); cout << "Š";
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
        if(cell == 'S') // meaning filled ship placed
        {
        	setColor(0, 6); cout << "  S  "; setColor(7,0); cout << "Š";
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
        if(cell == 'S') // meaning filled ship placed
        {
        	setColor(0, 6); cout << "  S  "; setColor(7,0); cout << "Š";
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
        if(cell == 'S') // meaning filled ship placed
        {
        	setColor(0, 6); cout << "  S  "; setColor(7,0); cout << "Š";
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
        if(cell == 'S') // meaning filled ship placed
        {
        	setColor(0, 6); cout << "  S  "; setColor(7,0); cout << "Š";
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
        if(cell == 'S') // meaning filled ship placed
        {
        	setColor(0, 6); cout << "  S  "; setColor(7,0); cout << "Š";
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
        if(cell == 'S') // meaning filled ship placed
        {
        	setColor(0, 6); cout << "  S  "; setColor(7,0); cout << "Š";
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
        if(cell == 'S') // meaning filled ship placed
        {
        	setColor(0, 6); cout << "  S  "; setColor(7,0); cout << "Š";
		}
        else 
		{
		setColor(7, 1); cout << "  ~  "; setColor(7,0); cout << "Š";
	    } 
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
}


int chose_ship(bool ships_left[])
{
	cout << "Chose your Ship!\n" ; 
	cout << "1. Aircraft Carrier - 5 blocks\n" ;
	cout << "2. Battleship - 4 blocks\n" ;
	cout << "3. Destroyer - 3 blocks\n" ; 
	cout << "4. Submarine - 3 blocks\n" ;
	cout << "5. Patrol Boat - 2 blocks\n"; 	
	cout << "Choice : " ;
	cin >> user_choice_for_ship ;
	while(user_choice_for_ship < 1 || user_choice_for_ship  > 9)
	{
		cout << "Enter correct option\n"  ;
		cin  >> user_choice_for_ship ; 
    }
    while(ships_left[user_choice_for_ship - 1] == false)
    {
       cout << "Ship Already Chosen ! Choose a new ship\n"; 
       cin >>  user_choice_for_ship ;
	   while(user_choice_for_ship < 1 || user_choice_for_ship  > 9) // Again input validation while user choses his new option
	     {
		  cout << "Enter correct option\n"  ;
		  cin  >> user_choice_for_ship ; 
         }     
	}
    ships_left[user_choice_for_ship - 1] = false ; 
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



void Place_ships() // Game Start
{
	// Menu 1st Option will call this function  
	
	initializeBoard(board) ;
	display_board(board);  
	
	while(true)
	{   // check if any ships is left or not to break  out of the loop
		bool flag = true ; 
		for(int st = 0  ; st <= 5 - 1  ; st += 1)
		{
			if (ships[st] == true){ // meaning still left
				flag = false ; 
				break ;
			}
		}
		if(flag == true){
			cout << "\nAll Ships Placed Successfully\n" ; 
			break ;
		}
		int ship = chose_ship(ships) ; // passing ships  to deternine the number of the ships left
	    while(setManuallyShips(board , ship) == false) // could'nt place the ship successfully
	    {
	    	ships[user_choice_for_ship - 1] = true ;  // the old ship isn't selected yet revert it back to true
	       	ship = chose_ship(ships) ; // chose a new ship
		}
		clearScreen() ;
	    display_board(board) ;
	}
}


bool Player_1[10][10] ;

void Player1_board_Init()
{
	// Intializing the player boolean array to according to the board specified by the user if the it is ship make it true else
	// false and this board will act as hidden board for the player 1
	for(int st =  0  ; st <= 10 - 1  ; st += 1)  
	{
		for(int st2  =  0 ;  st2 <= 10 -  1 ;  st2 += 1)
		{
			if(board[st][st2] == '~')
			{
				Player_1[st][st2] = false ; 
			}
			else
			{
				Player_1[st][st2] = true ;
			}
		}
	}
	
}

bool Player_2[10][10] ;

void Player2_board_Init()
{
	// Intializing the player boolean array to according to the board specified by the user if the it is ship make it true else
	// false and this board will act as hidden board for the player 1
	for(int st =  0  ; st <= 10 - 1  ; st += 1)  
	{
		for(int st2  =  0 ;  st2 <= 10 -  1 ;  st2 += 1)
		{
			if(board[st][st2] == '~')
			{
				Player_2[st][st2] = false ; 
			}
			else
			{
				Player_2[st][st2] = true ;
			}
		}
	}
	
}











void Show_Player_1(string player)
{
	setColor(RED ,  BLACK) ;
	cout << "\nFirst Turn to Place the Ships is " << player << endl ;
	setColor(WHITE ,  BLACK) ;
}

void Show_Player_2(string player)
{
	setColor(YELLOW ,  BLACK) ;
	cout << "\nFirst Turn to Place the Ships is " << player << endl ;
	setColor(WHITE ,  BLACK) ;
}





void  vsPlayer_Ships_Placement()
{
	// Determinig the First Player to Place his Boats
	setColor(MAGENTA , BLACK) ;
	cout << "1.Head\n2.Tails?\n" ;
	setColor(WHITE , BLACK) ;
	cout << "Choice : " ;
	int op ; 
	cin >> op ;
	while(op < 1 || op > 2)
	{
		cout << "Enter Correct Choice\n" ;
		cin >> op ; 
	}
	srand(time(0)) ;
	int winner_choice = (rand()  % (2 - 1 + 1)) + 1 ;
	if(op == winner_choice)
	{
		setColor(RED , BLACK) ;
		cout << "\nYou won the Toss Player 1 Turn\n" ;
		setColor(WHITE , BLACK) ;		
		Show_Player_1("Will Give this name later") ;
		re_init_ships() ; // have to initalize the avaialable ships using this function ah
		Place_ships() ;
	    Player1_board_Init() ;
	    initializeBoard(board); // Initialize it back to ~ so Player 2  can now Chose his turn
	    
	    
	     clearScreen() ;
	    
	    Show_Player_2("Give this name also") ;
	    //have to initalize the avaialable ships using this function ah 
	    // All ships are now avaialable for Player 2 aswell now since it was not calling the next functions cause no ships were available
	    re_init_ships() ;	 
	    Place_ships() ;
	    Player2_board_Init() ;
	    initializeBoard(board) ; // Change it back also too now 
	}
	else
	{
		setColor(RED , BLACK) ;
		cout << "\nYou Lost the Toss Player 2 Turn\n" ;
		setColor(WHITE , BLACK) ;
		
		Show_Player_2("Give this name also") ;
        re_init_ships() ; // have to initalize the avaialable ships using this function ah
	    Place_ships() ;
	    Player2_board_Init() ;
	    initializeBoard(board) ; // Change it back also too now 
	    
	    clearScreen() ;
	    
	    Show_Player_1("Will Give this name later") ;
		re_init_ships() ; // have to initalize the avaialable ships using this function ah
        Place_ships() ;
	    Player1_board_Init() ;
	    initializeBoard(board); // Initialize it back to ~ so Player 2  can now Chose his turn   
	}
}

void vsPlayer(char board1[10][10]  , char board2[10][10]) // This functions will execute the full player vs player attack
{
     vsPlayer_Ships_Placement() ;	
	 
	 // Now have to work on this function defination
}


signed main()
{
	char a[10][10] ;
	vsPlayer(a , a) ;
	return 0  ;
}



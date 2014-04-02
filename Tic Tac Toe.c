// CG3207 Final Demo - Tic Tac Toe Program

#include<REG51.h>

// Pads
sbit PAD_0  = P3^4; // Play button


// Internal LEDs
sbit LED_0  = P2^6; // Player 1 turn means it glows
sbit LED_1  = P2^7;	// Player 2 turn means it glows


// Board (external LEDs)
sbit X_0  = P0^0; // See board mapping below for understanding
sbit Y_0  = P1^0;

sbit X_1  = P0^1;
sbit Y_1  = P1^1;
									
sbit X_2  = P0^2;
sbit Y_2  = P1^2;
									
sbit X_3  = P0^3;
sbit Y_3  = P1^3;

sbit X_4  = P0^4;
sbit Y_4  = P1^4;

sbit X_5  = P0^5;
sbit Y_5  = P1^5;

sbit X_6  = P0^6;
sbit Y_6  = P1^6;

sbit X_7  = P0^7;
sbit Y_7  = P1^7;

sbit Z_0  = P2^0;
sbit Z_1  = P2^1;

/******
Board Layout (for LED)

x0y0   x1y1   x2y2  - If we enable x0, then player 1 choosed (0,0)
x3y3	x4y4	x5y5 
x6y6	x7y7	z0z1				  

*******/

// DIP Switch (external input)

sbit DIP_1 = P2^2;
sbit DIP_2 = P2^3;
sbit DIP_3 = P2^4;
sbit DIP_4 = P2^5;

// Traffic Lights

sbit RED_LIGHT = P3^5;	  // Glows if selected position is already full
sbit YELLOW_LIGHT = P3^6; // Glows if waiting for input
sbit GREEN_LIGHT = P3^7;  // Glows for 1 sec if input has been accepted

typedef int smallInt;

	unsigned char board[3][3]= {'0'};
	unsigned char board1[9] = {'0'}	;
void delayFunction(smallInt loopCounter)
{
		while(loopCounter--);
}

/*
void declareWinner(smallInt winner)
{
	//TODO
}
*/

void main()
{
	
	int player_turn = 1;// 1 = Player 1, -1 = Player 2 turn
	smallInt box_selected; // to store the input
	smallInt x = 0;	// to split the input into 2
	smallInt y = 0;	// to split the input into 2
	smallInt i; // for the for loop
	smallInt error = 0;
	int k=0;

	X_0 = 0;
	X_1 = 0;
	X_2 = 0;
	X_3 = 0;
	X_4 = 0;
	X_5 = 0;
	X_6 = 0;
	X_7 = 0;
	Z_0 = 0;
	
	Y_0 = 0;	
	Y_1 = 0;
	Y_2 = 0;
	Y_3 = 0;
	Y_4 = 0;
	Y_5 = 0;
	Y_6 = 0;
	Y_7 = 0;
	Z_1 = 0;

	while(1)
	{
		YELLOW_LIGHT = 1; 
		GREEN_LIGHT = 0;
		RED_LIGHT = 0;
		error = 0;
		box_selected = 0;
		x = 0;
		y = 0;				 	

		if(player_turn == 1)
		{
			LED_0 = 1;
			LED_1 = 0;
		}
		else if(player_turn == -1)
		{
			LED_0 = 0;
			LED_1 = 1;
		}
		if(PAD_0 == 1)
		{
			player_turn = player_turn * -1;

			// get DIP input
	
			YELLOW_LIGHT = 0;
		
			if(DIP_4)
			{
				box_selected += 1;  // 2^0 is 1
			}
			if(DIP_3)
			{
				box_selected += 2;  // 2^1 is 2
			}
			
			if(DIP_2)
			{
				box_selected += 4;  // 2^2 is 4
			}
			
			if(DIP_1)
			{
				box_selected += 8;  // 2^3 is 8
			}
			
		
			/****
			Mapping for box_selected
	
		    x
		y	0   1   2
			3	4	5
			6   7	8
			*****/
			k= box_selected;
			 // get coordinates from the DIP input
			if(box_selected < 3)
			{
				x = 0;
				y = box_selected;
			}
			else if(box_selected < 6)
			{
				x = 1;
				y = box_selected - 3;
			}
			else if(box_selected < 9)
			{
				x = 2;
				y = box_selected - 6;
			}
			else
			{
				// Error - glow the red LED
				RED_LIGHT = 1;
				error = 1;
			}
			
			if(error == 0)
			{					
				if(board1[k]=='0')
				{
			
					board1[k] ='1';// player_turn;
					GREEN_LIGHT = 1;
					goto qqq;
				
				}				 
				else
				{
					RED_LIGHT = 1; // already occupied - flash red and exit
				}
			
		
				 
//				if(board[x][y] == 0)
//				{
//				
//					board[x][y] = player_turn;
//						GREEN_LIGHT = 1;
//						goto qqq;
//					
//				}				 
//				else
//				{
//					RED_LIGHT = 1; // already occupied - flash red and exit
//				}
				
			}	

			qqq:
			YELLOW_LIGHT =0;
			delayFunction(10000); // for debounce
			delayFunction(10000); // for debounce		
			delayFunction(10000); // for debounce	
			delayFunction(10000); // for debounce	
		
		}
		 
	
		
		
		
	

			 
		   /*

		


		// use coordinates to set the board values
		if(board[x][y] == 0)
		{
			// selected place is free. assign it to current player
			board[x][y] = player_turn;
			
			GREEN_LIGHT = 1;
			delayFunction(60000);
			GREEN_LIGHT = 0;
	
			GREEN_LIGHT = 1;
			delayFunction(60000);
			GREEN_LIGHT = 0;

			GREEN_LIGHT = 1;
			delayFunction(60000);
			GREEN_LIGHT = 0;

			switch(x)
			{
				case 0:
					switch(y)
					{
					  case 0:	 // 0, 0
					  		if(player_turn == 1)
							{
								X_0 = 1;
							}
							else if(player_turn == -1)
							{
								Y_0 = 1;
							}
					  	break;
					  case 1: 	// 0, 1
					  		if(player_turn == 1)
							{
								X_1 = 1;
							}
							else if(player_turn == -1)
							{
								Y_1 = 1;
							}
					  	break;
					  case 2:  // 0, 2
					 		if(player_turn == 1)
							{
								X_2 = 1;
							}
							else if(player_turn == -1)
							{
								Y_2 = 1;	
							}
					  	break;
					  default: ;
					} 
					break;
				case 1:	  
					switch(y)
					{
					  case 0:   // 1, 0
					  		if(player_turn == 1)
							{
								X_3 = 1;	
							}
							else if(player_turn == -1)
							{
								Y_3 = 1;
							}
					  	break;
					  case 1:  // 1, 1
					  		if(player_turn == 1)
							{
								X_4 = 1;
							}
							else if(player_turn == -1)
							{
								Y_4 = 1;	
							}
					  	break;
					  case 2:   // 1, 2
					  		if(player_turn == 1)
							{
								X_5 = 1;
							}
							else if(player_turn == -1)
							{
								Y_5 = 1;
							}
					  	break;
					  default: ;
					}
					break;
				case 2:
					switch(y)
					{
					  case 0:   // 2, 0
					  		if(player_turn == 1)
							{
								X_6 = 1;	
							}
							else if(player_turn == -1)
							{
								Y_6 = 1;
							}
					  	break;
					  case 1:  // 2, 1
					  		if(player_turn == 1)
							{
								X_7 = 1;
							}
							else if(player_turn == -1)
							{
								Y_7 = 1;
							}
					  	break;
					  case 2:   // 2, 2
					  		if(player_turn == 1)
							{
								Z_0 = 1;	
							}
							else if(player_turn == -1)
							{
								Z_1 = 1;	
							}
					  	break;
					  default:	;
					}
					break;
				default:  ;

			}
			// Accepted Input
			GREEN_LIGHT = 1;
			delayFunction(50000);
			GREEN_LIGHT = 0;
			player_turn *= -1;
		}
		else
		{
			// selected place is already occupied.
			// Glow red light for sometime and go back
			RED_LIGHT = 1;
			delayFunction(50000);
			RED_LIGHT = 0;

			RED_LIGHT = 1;
			delayFunction(50000);
			RED_LIGHT = 0;

			RED_LIGHT = 1;
			delayFunction(50000);
			RED_LIGHT = 0;
			continue;
			
		}
		
		// To determine winner, check if three in a row
		
		for(i = 0; i < 3; i++)
		{
			// for checking row wise - i is row number
			if(board[i][0] == board[i][1] == board[i][2])
			{
				if(board[i][0] == 1)
				{
					declareWinner(1);
				}
				else
				{
					declareWinner(-1);
				}
			}
			// for checking column wise - i is now column number
		   if(board[0][i] == board[1][i] == board[2][i])
		   {
				if(board[0][i] == 1)
				{
					declareWinner(1);
				}
				else
				{
				declareWinner(-1);
				}
					   	
		   }
		   
		}

		if(board[0][0] == board[1][1] == board[2][2])
		{
			 	if(board[0][0] == 1)
				{
					declareWinner(1);
				}
				else
				{
					declareWinner(-1);
				}
		}
		else if(board[0][2] == board[1][1] == board[2][0])
		{
			 	if(board[0][2] == 1)
				{
					declareWinner(1);
				}
				else
				{
					declareWinner(-1);
				}
		}
		*/


		
	}	
}

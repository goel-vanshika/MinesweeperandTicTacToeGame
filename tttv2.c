#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"tttv2.h"

int random_no(int l,int h)
{
	return (rand()%(h-l+1) + l);
}

void choose_diff(char* d)
{
	char res;
	printf("Choose difficulty -> Easy / Hard (e/h) ");
	do
    	{
		res = getchar();
    	} while ((res != 'e') && (res != 'E') && (res != 'h') && (res != 'H'));
	*d=res;
}





int middle(char* board)
{
	if(board[4] == ' ')
		return 4;
	else
		return 0;
}

int find_corner(char* board)
{
	if (board[0] == ' ')
    		return 0;
  	if (board[2] == ' ')
    		return 2;
  	if (board[6] == ' ')
    		return 6;
  	if (board[8] == ' ')
    		return 8;
  	return 0;
}

int find_side(char* board)
{
  	if (board[1] == ' ')
    		return 1;
  	if (board[3] == ' ')
    		return 3;
  	if (board[5] == ' ')
    		return 5;
  	if (board[7] == ' ')
    		return 7;
  	return 0;
}




void first_turn(char* u,char* c)
{
	char response;
  	printf("Do you want to go first? (y/n) ");
  	do
    	{
		response = getchar();
    	} while ((response != 'y') && (response != 'Y') && (response != 'n') && (response != 'N'));
	if ((response == 'y') || (response == 'Y'))
	{
    		*u='X';
		*c='O';
	}
  	else
	{
  		*u='O';
		*c='X';
	}
}






void disp_board(char* board)
{
	printf("\n\t\t\t\tTIC-TAC-TOE\n");
	printf("\n\t\t\t\t***********\n");
	printf("\n\n");
	int k=0;
	for(int i=0;i<3;i++)
	{
		printf("\t\t\t_________________________\n");
		printf("\n\t\t\t|   %c \t|   %c \t|   %c \t|\n",board[k],board[k+1],board[k+2]);
		printf("\t\t\t_________________________\n");
		k=k+3;
	}
	printf("\n\t\t########################################\n\n");
	return;
}



void computer_move(char* board,char user,char comp,char diff)
{
	if(diff == 'e' || diff == 'E')
	{
		while(1)
		{
			int k = random_no(0,8);
			if(board[k] == ' ')
			{
				board[k]=comp;
				break;
			}
		}
		return;
	}
	else
	{	
		int sq;
		sq=find_win(board,comp);
		if(!sq)
			sq=find_win(board,user);
		if(!sq)
			sq=find_corner(board);
		if(!sq)
			sq=middle(board);
		if(!sq)
			sq=find_side(board);
		board[sq] = comp;
		return;
	}
}

int validity(char*board,int sq)
{
	if( sq>=1 && sq<=9)
	{
		if(board[sq-1] == ' ')
			return 1;
	}
	return 0;
}

void player_move(char* board,char user)
{
	int sq;
	do
	{
		printf("Enter a square:");
		scanf("%d",&sq);
	} while(!validity(board,sq));
	board[sq-1] = user;
	return;	
}



int find_win(char* board,char symbol)
{
	int sq;
	int res=0;
	for(sq=0;sq<9;sq++)
	{
		if(board[sq]== ' ')
		{
			board[sq] = symbol;
			if(check_win(board,symbol))
				res = sq;
				board[sq] = ' ';
		}
	}
	return res;
}



int check_win(char* board,char symbol)
{
	int sq;
	int k=0;
	for(sq=0;sq<3;sq++)
	{
		if((board[k] == symbol) && (board[k+1] == symbol) && (board[k+2] == symbol))
			return 1;
		k=k+3;
	}
	k=0;
	for(sq=0;sq<3;sq++)
	{
		if((board[k] == symbol) && (board[k+3] == symbol) && (board[k+6] == symbol))
			return 1;
		k++;
	}
	if ((board[0] == symbol) && (board[4] == symbol) && (board[8] == symbol))
		return 1;
	if ((board[1] == symbol) && (board[4] == symbol) && (board[7] == symbol))
    		return 1;
  	if ((board[2] == symbol) && (board[4] == symbol) && (board[6] == symbol))
    		return 1;
	if ((board[3] == symbol) && (board[4] == symbol) && (board[5] == symbol))
    		return 1;
  	return 0;
}		

		
	


void startgame(char* board,char user,char comp,char diff)
{
	srand(time(0));
	int turn;
	disp_board(board);
  	for (turn = 1; turn <= 9; turn++)
    	{
		if (turn % 2 == 1)
		{
	  		if (comp == 'X')
	    			computer_move(board,user,comp,diff);
	  		else
	    			player_move(board,user);
		}
      		else
		{
	  		if (comp == 'O')
				computer_move(board,user,comp,diff);	    			
	  		else
				player_move(board,user);	    			

		}
      		disp_board(board);			
      		if (check_win(board,comp)) 
		{
			printf("\nThe computer has won\n");
			printf("Better luck next time\n\n");
			return;
      		}
      		else if (check_win(board,user)) 
		{
			printf("\nCongratulations you have won the game!!!\n\n");
			return;
      		}
    	}
  	printf("\nThe game is a draw.\n\n");
  	return;
}




void TicTacToe()
{
	char* board = (char*)malloc(9*sizeof(char));
	char* user = (char*)malloc(sizeof(char));
	char* comp = (char*)malloc(sizeof(char));
	char* diff = (char*)malloc(sizeof(char));
	
	while(1)
	{
		for(int i=0;i<9;i++)
			board[i]=' ';
		
		first_turn(user,comp);
		choose_diff(diff);
		startgame(board,*user,*comp,*diff);
		if(!replay())
			break;
	}
	free(board);
	free(user);
	free(comp);
	free(diff);
	return;
		
}

int replay()
{
	char res;
	printf("Do you want to play again? (y/n) ");
	do
    	{
      		res = getchar();
	} while ((res != 'y') && (res != 'Y') && (res != 'n') && (res != 'N'));

  	if ((res == 'y') || (res == 'Y'))
    		return 1;
  	else
    		return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<stdarg.h>
#include"tttv2.h"
#include"MineSweeper.h"

int main()
{
	int n;
	while(1)
	{
		printf("\t\t*** WELCOME TO OUR 2 IN 1 GAMES **\n");
		printf("\t\t****WITH TIC TAC TOE AND  ****\n");
    		printf("\t\t***MINESWEEPER**\n");
    		printf("\t\t*******\n");
    		printf("\t\t*******\n");
    		printf("\t\t*******\n");
    		printf("\t\t*******\n");
    		printf("\t\t*******\n");
		printf("Enter 1 (Minesweeper) , 2 (Tic Tac Toe) , 3 (Exit application) :");
		scanf("%d",&n);
		if(n == 1)
		{
			play_game();
		}
		else if(n == 2)
		{
			TicTacToe();
		}
		else if(n == 3)
		{
			printf("Exiting application, THANKS FOR PLAYING\n");
			return 0;
		}
		else
		{
			printf("Invalid choice\n");
		}
	}
}
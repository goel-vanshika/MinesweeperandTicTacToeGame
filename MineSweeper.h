#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Cell
{
    int number_of_mines;
    char ch;
    bool uncovered;
    bool bomb;
}Cell;

typedef struct Board
{
    int height, width;
    Cell **cells; 
}Board;

void create_board(Board*); 
void display_board(Board*); 
void placing_bomb(Board*, int); 
void no_of_mines(Board*);
void uncover(Board*, int, int); 
void reveal(Board*, int, int);
void check_for_win(Board*, int);
void play_game(); 

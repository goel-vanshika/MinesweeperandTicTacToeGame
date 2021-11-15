#include<stdio.h>
#include<stdlib.h>




void TicTacToe();                
void first_turn(char*,char*);    
int random_no(int l,int h);
void startgame(char*,char,char,char);  
void disp_board(char*);         
void computer_move(char* board,char user,char comp,char diff);
void player_move(char* board,char user);        
int find_win(char*,char);          
int check_win(char*,char);           
int middle(char*);          
int find_side(char*);          
int find_corner(char*);         
int validity(char*,int);         
int replay();
void choose_diff(char*);

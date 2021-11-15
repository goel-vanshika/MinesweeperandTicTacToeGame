#include "MineSweeper.h"
#include "tttv2.h"

bool lose = false;
bool win = false;

void create_board(Board *ptr)
{
    int i, j;
    ptr->cells=(Cell**)malloc((ptr->height+2)*sizeof(Cell*));

    for(i = 0; i <= ptr->height+1; ++i)
        ptr->cells[i]=(Cell*)malloc((ptr->width+2)*sizeof(Cell)); 
    for(i = 0; i <= ptr->height+1; ++i){
        for(j = 0; j <= ptr->width+1; ++j){
            if (i==0 || i==ptr->height+1 || j==0 || j==ptr->width+1)
            {
                ptr->cells[i][j].bomb = false;
                ptr->cells[i][j].uncovered = true;
            }

            else
            {
                ptr->cells[i][j].ch = '-';
                ptr->cells[i][j].number_of_mines = 0;
                ptr->cells[i][j].bomb = false; 
                ptr->cells[i][j].uncovered = false;
            }
        }
    }

     return;
}

void display_board(Board *ptr)
{
    //system("clear"); // clearing the screen

    printf("  ");
    int i, j;
    for(i = 1; i <= ptr->width; ++i)
        printf("%d ", i); 
    printf("\n");

    for(i = 1; i <= ptr->height; ++i){
        for(j = 0; j<= ptr->width; ++j){
          if(j == 0) printf("%d ", i);   
          else printf("%c ", ptr->cells[i][j].ch);
        }
        printf("\n");
    }
   return;
}

void placing_bomb(Board *ptr, int mines)
{
    int random_row, random_col, num_of_mine = 0;
    while(num_of_mine < mines)
    {
        random_row = rand()%ptr->height+1; 
        random_col = rand()%ptr->width+1;  

        if(ptr->cells[random_row][random_col].bomb == false && (random_row != 0 && random_col != 0)) 
        {
            ptr->cells[random_row][random_col].bomb = true;
            num_of_mine++;
        }
    }
     return;
}

void no_of_mines(Board *ptr)
{

	int i, j, m, n;
	for(i = 1; i <= ptr->height; ++i){
        for(j = 1; j <= ptr->width; ++j){
            if (ptr->cells[i][j].bomb==false){
                for(m = i-1; m <= i+1; ++m)
                for(n = j-1; n <= j+1; ++n)
                    if(ptr->cells[m][n].bomb == true) 
                    ptr->cells[i][j].number_of_mines++;
            }
        }
    }
    return;
}

void uncover(Board *ptr, int a, int b)
{
    if(ptr->cells[a][b].bomb == true)
    {
        lose = true; 
        int i, j;
        
        for(i = 1; i <= ptr->height; ++i)
            for(j = 1; j <= ptr->width; ++j)
               if(ptr->cells[i][j].bomb == true)
                  ptr->cells[i][j].ch = '*'; 
               else
                  ptr->cells[i][j].ch = ptr->cells[i][j].number_of_mines + '0'; 
        display_board(ptr);
        printf("\nYou Lost\n");
        printf("Game Over\n");

         return;
    }

   ptr->cells[a][b].ch = ptr->cells[a][b].number_of_mines + '0'; 
    if(ptr->cells[a][b].number_of_mines == 0)
       reveal(ptr,a,b); 
    else
       ptr->cells[a][b].uncovered = true;

    return;
}

void reveal(Board *ptr, int a, int b)
{
    int i, j;

    if(ptr->cells[a][b].uncovered == false)
    {
        ptr->cells[a][b].uncovered = true;

        for(i = a-1; i <= a+1; ++i)
            for(j = b-1; j <= b+1; ++j)
               if(ptr->cells[i][j].uncovered == false)
                 uncover(ptr,i,j); 
    }
    return;
}

void check_for_win(Board *ptr, int mines)
{
    int i, j, counter = 0; 


    for(i = 1; i <= ptr->height; ++i)
        for(j = 1; j <= ptr->width; ++j)
           if(ptr->cells[i][j].bomb==false && ptr->cells[i][j].ch != '-' && ptr->cells[i][j].ch != '!') /*if no bomb. increment*/
             counter++; 

     
    if (counter == (ptr->height*ptr->width) - mines)
    {
        win = true;
        for(i = 1; i <= ptr->height; ++i)
            for(j = 1; j <= ptr->width; ++j)
               if(ptr->cells[i][j].bomb == true) 
                  ptr->cells[i][j].ch = '*';
               else
                  ptr->cells[i][j].ch = ptr->cells[i][j].number_of_mines + '0'; 

        display_board(ptr);
        printf("\nYou Won, Congratulations!!!\n");
          return;
    }
}


void play_game()
{

    printf("\t\t\t\t WELCOME TO MINEWSWEEPER GAME \n");
    int x, y, row, column, mines;
    char op;

    printf("Please enter the size of board:\n");
    scanf("%d%d", &x, &y);

    printf("Please enter the number of mines: ");
    scanf("%d", &mines);

    Board *ptr=(Board*)malloc(sizeof(Board));
    ptr->height = x;
    ptr->width = y;

    create_board(ptr);
    placing_bomb(ptr,mines);
    no_of_mines(ptr);
    int i = 1;
    while(i)
    {
    do
    {
        display_board(ptr);

        printf("Would you like to uncover or mark?  'u' or 'm' ");
        scanf(" %c", &op);
        fflush(stdin); 

        printf("Enter the row number: ");
        scanf("%d", &row);
        printf("Enter the column number: ");
        scanf("%d", &column);

        if(op == 'u')
            uncover(ptr,row,column);
        if(op == 'm')
            ptr->cells[row][column].ch = '!';
        if (!lose) check_for_win(ptr,mines);
    } while(!lose && !win);
    if(!replay())
    {
        i = 0;
    }
    }

     
    for(int i = 0; i <= ptr->height+1; ++i)
            free(ptr->cells[i]);
         free(ptr->cells); 
    return;
}

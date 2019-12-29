#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"

using namespace std;

/******************************************************
 * In your algorithm, you can just use the the funcitons
 * listed by TA to get the board information.(functions 
 * 1. ~ 4. are listed in next block)
 * 
 * The STL library functions is not allowed to use.
******************************************************/

/*************************************************************************
 * 1. int board.get_orbs_num(int row_index, int col_index)
 * 2. int board.get_capacity(int row_index, int col_index)
 * 3. char board.get_cell_color(int row_index, int col_index)
 * 4. void board.print_current_board(int row_index, int col_index, int round)
 * 
 * 1. The function that return the number of orbs in cell(row, col)
 * 2. The function that return the orb capacity of the cell(row, col)
 * 3. The function that return the color fo the cell(row, col)
 * 4. The function that print out the current board statement
*************************************************************************/
#define rows 5
#define cols 6

int enemy_move(Board enemy_board,int row,int col,Player *player_ptr,Player *enemy_ptr,int color,int enemy_color){
    enemy_board.place_orb(row,col,enemy_ptr);
    //enemy_board.print_current_board(row,col,100000000);
    int new_ord=0;
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(enemy_board.get_cell_color(i,j)==color){
                new_ord++;
            }
        }
    }
    return new_ord;
}
int you_move(Board moved_board,int row,int col,Player *player_ptr,Player *enemy_ptr,int init_ord,int color,int enemy_color){
    int min_score=10000;
    cout<<"***********************************************************************"<<endl;
    cout<<"                      if you move to ("<<row<<","<<col<<")"<<endl;
    moved_board.place_orb(row,col,player_ptr);
    cout<<"***********************************************************************"<<endl;
    
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(moved_board.get_cell_color(i, j) == enemy_color || moved_board.get_cell_color(i, j) == 'w'){
                int score;
                cout<<"------------------------------------------"<<endl;
                cout<<"init_ord = "<<init_ord<<endl;
                cout<<"if enemy move to ("<<i<<","<<j<<")"<<endl;
                int new_ord = enemy_move(moved_board,i,j,player_ptr,enemy_ptr,color,enemy_color);
                cout<<"new_ord = "<<new_ord<<endl;
                score = new_ord - init_ord;
                cout<<"score: "<<score<<endl;
                if(score<min_score){
                    min_score=score;
                }
            }
        }
    }
    return min_score;
}
void algorithm_A(Board board, Player player, int index[]){
    
    // cout << board.get_capacity(0, 0) << endl;
    // cout << board.get_orbs_num(0, 0) << endl;
    // cout << board.get_cell_color(0, 0) << endl;
    // board.print_current_board(0, 0, 0);

    //////////// Random Algorithm ////////////
    // Here is the random algorithm for your reference, you can delete or comment it.
    int row, col;
    int color = player.get_color();
    int enemy_color ;
    if(color == 'r')
        enemy_color='b';
    else
        enemy_color='r';
    Player enemy(enemy_color);

    //win
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(board.get_cell_color(i,j)==color && board.get_capacity(i,j)-board.get_orbs_num(i,j)==1){
                Board tmp=board;
                tmp.place_orb(i,j,&player);
                if(tmp.win_the_game(player)){
                    index[0] = i;
                    index[1] = j;
                    cout<<"win step!!!!!!!"<<endl;
                    cout<<"row :"<<index[0]<<endl;
                    cout<<"col :"<<index[1]<<endl;
                    return;
                }
            }
        }
    }
    //best
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    int max_score = -10000;
    //count ord_num
    int init_ord = 0;
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(board.get_cell_color(i,j)==color)
                init_ord++;
        }
    }

    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            int score=0;
            if(board.get_cell_color(i, j) == color || board.get_cell_color(i, j) == 'w'){
                score=you_move(board,i,j,&player,&enemy,init_ord,color,enemy_color);
                cout<<endl;
                cout<<"The score placing ord in ("<<i<<","<<j<<") is "<<score<<endl;
                if(score>max_score){
                    max_score = score;
                    index[0]=i;
                    index[1]=j;
                }
                cout<<"curren_max_score = "<<max_score<<endl;
            }
        }
    }
    cout<<endl;
    cout<<endl;
    cout<<"***********************************************************************"<<endl;
    cout<<"max_score = "<<max_score<<endl;
    cout<<"best step is ("<<index[0]<<","<<index[1]<<")"<<endl;
    cout<<"***********************************************************************"<<endl;
     cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    
}
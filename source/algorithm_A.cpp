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
bool isCorner(int row,int col){
    if((row==0&&col==0) || (row==rows-1&&col==0) || (row==rows-1&&col==cols-1) || (row==rows-1&&col==cols-1) )
        return true;
    return false;
}
bool isEdge(int row,int col){
    if((row==0||row==rows-1||col==0||col==cols-1) && !isCorner(row,col))
        return true;
    return false;
}
int enemySurrounding(Board board,int row,int col,Player *player,Player *enemy){
    int dist = board.get_capacity(row,col)-board.get_orbs_num(row,col);
    int min_enemy_dist = 4;
    if(row-1>=0&&board.get_cell_color(row-1,col)==enemy->get_color()){
        int enemy_dist = board.get_capacity(row-1,col)-board.get_orbs_num(row-1,col);
        if(enemy_dist<min_enemy_dist)
            min_enemy_dist = enemy_dist;
    }
    if(row+1<rows&&board.get_cell_color(row+1,col)==enemy->get_color()){
        int enemy_dist = board.get_capacity(row+1,col)-board.get_orbs_num(row+1,col);
        if(enemy_dist<min_enemy_dist)
            min_enemy_dist = enemy_dist;
    }
    if(col-1>=0&&board.get_cell_color(row,col-1)==enemy->get_color()){
        int enemy_dist = board.get_capacity(row,col-1)-board.get_orbs_num(row,col-1);
        if(enemy_dist<min_enemy_dist)
            min_enemy_dist = enemy_dist;
    }
    if(col+1<cols&&board.get_cell_color(row,col+1)==enemy->get_color()){
        int enemy_dist = board.get_capacity(row,col+1)-board.get_orbs_num(row,col+1);
        if(enemy_dist<min_enemy_dist)
            min_enemy_dist = enemy_dist;
    }
    if(dist==min_enemy_dist&&min_enemy_dist!=4){
        cout<<"enemy surrounding"<<endl;
        return 3;
    }
    return 0;
}
int enemy_move(Board enemy_board,int row,int col,Player* player,Player* enemy){
    enemy_board.place_orb(row,col,enemy);
    int remained_ord=0;
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(enemy_board.get_cell_color(i,j)==player->get_color()){
                remained_ord+=enemy_board.get_orbs_num(i,j);
            }
        }
    }
    return remained_ord;
}
int move(Board board,int row,int col,Player* player,Player* enemy,int init_ord){
    //before placing ord
    int bonus=0;
    if(isCorner(row,col)&&board.get_cell_color(row,col)=='w'){
        cout<<"Corner! bonus: 2"<<endl;
        bonus+=2;
        
    }
    else if(isEdge(row,col)&&board.get_cell_color(row,col)=='w'){
        cout<<"Edge! bonus: 1"<<endl;
        bonus+=1;
    }
    bonus += enemySurrounding(board,row,col,player,enemy);
    
    //after placing ord
    board.place_orb(row,col,player);
    int min=10000;
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(board.get_cell_color(i,j) == enemy->get_color()){
                int remained_ord=enemy_move(board,i,j,player,enemy);
                if(remained_ord < min){
                    min = remained_ord;
                }
            }
        }
    }
    
    return min - init_ord + bonus;
}
void algorithm_A(Board board, Player player, int index[]){

    int color = player.get_color();
    int enemy_color = (color == 'r' ? 'b':'r' );
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

    //count init_ord
    int init_ord=0;
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(board.get_cell_color(i,j)==color){
                init_ord+=board.get_orbs_num(i,j);
            }
        }
    }
    //choose best step
    int max = -10000;
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(board.get_cell_color(i, j) == color || board.get_cell_color(i, j) == 'w'){
                int score=move(board,i,j,&player,&enemy,init_ord);
                cout<<"score: "<<score<<endl<<"("<<i<<", "<<j<<")"<<endl<<endl;
                if(score > max){
                    max = score;
                    index[0]=i;
                    index[1]=j;
                }
            }
        }
    }
}
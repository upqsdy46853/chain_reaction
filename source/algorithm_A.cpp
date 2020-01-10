#include <iostream>
#include <stdlib.h>
#include "../include/algorithm.h"
using namespace std;
#define rows 5
#define cols 6
bool isCorner(int row,int col){
    if((row==0&&col==0) || (row==rows-1&&col==0) || (row==0&&col==cols-1) || (row==rows-1&&col==cols-1) )
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
    if(dist>min_enemy_dist){
        return -3;
    }
    if(dist==min_enemy_dist&&min_enemy_dist!=4){
        return 3;
    }
    return 0;
}
int enemy_move(Board enemy_board,int row,int col,Player* player,Player* enemy){
    enemy_board.place_orb(row,col,enemy);
    //lose step
    if(enemy_board.win_the_game(*enemy)){
        return -10000;
    }
    
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
float move(Board board,int row,int col,Player* player,Player* enemy,int init_ord){
    //before placing ord
    float bonus=0;
    if(board.get_cell_color(row,col)=='w'){
        if(isCorner(row,col)){
            bonus+=2;
        }
        else if(isEdge(row,col)){
            bonus+=1;
            if((row==0||row==rows-1)&&board.get_cell_color(row,col-1)=='w'&&board.get_cell_color(row,col+1)=='w')
                bonus+=0.1;
            else if((col==0||col==cols-1)&&board.get_cell_color(row-1,col)=='w'&&board.get_cell_color(row+1,col)=='w')
                bonus+=0.1;
        }
    }
    else{
        if(board.get_capacity(row,col)-board.get_orbs_num(row,col)==1)
            bonus-=0.1;
        bonus-=0.1;
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
                    if(remained_ord==-10000)
                        return -10000;
                    min = remained_ord;
                }
            }
        }
    }
    
    return (float)min - (float)init_ord + bonus;
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
    float max = -10001;
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(board.get_cell_color(i, j) == color || board.get_cell_color(i, j) == 'w'){
                float score=move(board,i,j,&player,&enemy,init_ord);
                if(score > max){
                    max = score;
                    index[0]=i;
                    index[1]=j;
                }
            }
        }
    }
}
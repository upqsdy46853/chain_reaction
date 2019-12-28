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
void my_srand(void){
    long long cpu_cycle;
    asm volatile(".byte 15;.byte 49" : "=A" (cpu_cycle));
    srand((unsigned int)cpu_cycle);
}
void algorithm_A(Board board, Player player, int index[]){

    // cout << board.get_capacity(0, 0) << endl;
    // cout << board.get_orbs_num(0, 0) << endl;
    // cout << board.get_cell_color(0, 0) << endl;
    // board.print_current_board(0, 0, 0);

    //////////// Random Algorithm ////////////
    // Here is the random algorithm for your reference, you can delete or comment it.
    my_srand();
    int row, col;
    int color = player.get_color();
    
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
    while(1){
        row = rand() % 5;
        col = rand() % 6;
        if(board.get_cell_color(row, col) == color || board.get_cell_color(row, col) == 'w') break;
    }

    index[0] = row;
    index[1] = col;
}
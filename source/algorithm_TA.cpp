#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"

using namespace std;
void my_srand(void){
    long long cpu_cycle;
    asm volatile(".byte 15;.byte 49" : "=A" (cpu_cycle));
    srand((unsigned int)cpu_cycle);
}
void algorithm_B(Board board, Player player, int index[]){
    my_srand();
    int color = player.get_color();
    int row, col;
    while(1){
        //scanf("%d %d",&row,&col);
        row = rand()%5;
        col = rand()%6;
        if(board.get_cell_color(row,col) == color ||board.get_cell_color(row,col)== 'w') break;
        //cout<<"不合法輸入!"<<endl;
    }
    
    index[0] = row;
    index[1] = col;
}
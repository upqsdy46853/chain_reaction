#include <iostream>
#include "../include/board.h"
#include "../include/player.h"
#include "../include/rules.h"
#include "../include/algorithm.h"
#include <time.h>
using namespace std;

int main(){
    int red_win=0;
    int blue_win=0;
    //srand(time(NULL));
    for(int i=0;i<10000;i++){
    Board board;
    Player red_player(RED);
    Player blue_player(BLUE);

    bool first_two_step = true;
    int round = 1;
    int index[2];

    while(1){

        //////////// Red Player operations ////////////
        algorithm_A(board, red_player, index);
        board.place_orb(index[0], index[1], &red_player);

        if(rules_violation(red_player)) return 0;

        board.print_current_board(index[0], index[1], round);
        round++;

        if(board.win_the_game(red_player) && !first_two_step){
            cout << "Red Player won the game !!!" << endl;
            red_win++;
            //return 0;
            break;
        }

        //////////// Blue Player operations ////////////
        algorithm_F(board, blue_player, index);
        board.place_orb(index[0], index[1], &blue_player);

        if(rules_violation(blue_player)) return 0;
        
        board.print_current_board(index[0], index[1], round);
        round++;

        if(board.win_the_game(blue_player) && !first_two_step){
            cout << "Blue Player won the game !!!" << endl;
            blue_win++;
            //return 0;
            break;
        }

        first_two_step = false;
    }
    }
    cout<<"red_win:"<<red_win<<endl;
    cout<<"blue_win:"<<blue_win<<endl;
    return 0;
} 
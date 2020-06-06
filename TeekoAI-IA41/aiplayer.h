#ifndef AIPLAYER_H
#define AIPLAYER_H

#include <QtWidgets>
#include <iostream>

#include "player.h"

using namespace std;

class AIPlayer : public Player
{

public :
    AIPlayer(QString name = "", int id = 0, int difficulty = 0 );
    AIPlayer& operator= (const AIPlayer& pl);
    bool operator== (AIPlayer &rhs);


    int getDifficulty();

private:
    int getIAMove(int  board [5][5]);
    int move;
    int difficulty;
    int pawn_to_move;
    int where_to_move_pawn;
    void findMove(int  board [5][5]);
    vector<int> computePossibleMoves(int index, int  board [5][5]);
    vector<int> computeSquaresAroundSquare(int index, int  board [5][5]);

    int minMax(int  board [5][5], int depth, bool is_maximizing, int alpha, int beta);
    int checkWin(vector <int>);
    int evaluateBoard(int[5][5]);
    void copyBoard(int  board [5][5], int new_board [5][5]);

    void printBoard(int b [5][5]);
};



#endif // AIPLAYER_H

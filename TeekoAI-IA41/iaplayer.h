#ifndef IAPLAYER_H
#define IAPLAYER_H

#include <QtWidgets>
#include <iostream>

#include "player.h"

class IAPlayer : public Player
{

public :
    IAPlayer(QString name = "", int id = 0 );

private:
    int getIAMove(int  board [5][5]);
    int move;
    void findMove(int  board [5][5]);
    std::vector<int> computePossibleMoves(int index, int  board [5][5]);
};



#endif // IAPLAYER_H

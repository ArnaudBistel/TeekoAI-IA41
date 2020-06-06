#ifndef GAME_H
#define GAME_H
#include <QtWidgets>
#include "player.h"
#include "aiplayer.h"
#include "board.h"

#include <iostream>
typedef int (*pointer_to_arrays)[5];

class Game : public QThread
{
    Q_OBJECT

public:
    Game(QWidget *parent = 0);


    // -------------- GAME METHODS ---------------
    void run() override;
    void restartGame();
    bool checkIfWins(int);
    void prepareBoardForNextTurn();

    // -------------- BOARD METHODS --------------
    bool checkRows(int);
    bool checkCol(int);
    bool checkSquare(int);
    bool checkDiag(int);
    void printBoard();

    // ------------- PLAYERS METHODS -------------
    void chooseFirstPlayer();
    void changeCurrentPlayer();

    // ------------- SETTERS -------------
    void setMode(int, int);
    void setPlayer1(Player pl);
    void setPlayer2(Player pl);
    void setPause(bool);

    // ------------- GETTERS -------------
    Board& getBoardObject();
    pointer_to_arrays getBoard();
    bool isPaused();

public slots:
    void playerPlayed(int);


private:

    // ------------- ATTRIBUTES -------------
//    Player player1, player2, *current_player;
    Player *player1, *player2, *current_player;
    bool win;
    int  board [5][5];
    QWidget *parent;
    bool pause;

};


#endif // GAME_H

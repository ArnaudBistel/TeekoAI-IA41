#ifndef GAME_H
#define GAME_H
#include <QtWidgets>
#include "player.h"
#include "board.h"

#include <iostream>
typedef int (*pointer_to_arrays)[5];

class Game : public QThread
{
    Q_OBJECT

public:
    Game(QWidget *parent = 0);


    // -------------- GAME METHODS ---------------
    bool checkIfWins(int);
    void run() override;
    void restartGame();

    // -------------- BOARD METHODS --------------
    bool checkRows(int);
    bool checkCol(int);
    bool checkSquare(int);
    void printBoard();
    void prepareBoardForNextTurn();
//    void endGame(QString);

    // ------------- PLAYERS METHODS -------------
    void chooseFirstPlayer();
    void changeCurrentPlayer();
    void setMode(int);

    // ------------- SETTERS -------------
    void setPlayer1(Player pl);
    void setPlayer2(Player pl);

    // ------------- GETTERS -------------
    Board& getBoardObject();
    pointer_to_arrays getBoard();

public slots:
    void playerPlayed(int);


private:

    // ------------- ATTRIBUTES -------------
    Player *player1, *player2, *current_player;
    bool win;
    int  board [5][5];
    QWidget *parent;

};


#endif // GAME_H

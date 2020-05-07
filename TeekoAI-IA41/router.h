#ifndef ROUTER_H
#define ROUTER_H

#include <QtWidgets>
#include "board.h"
#include "home.h"
#include "player.h"
#include "game.h"
#include <iostream>
using namespace std;


// Classe qui hérite de QStackedWidget et permet donc de transiter entre
// les différentes pages de l'application
class Router : public QStackedWidget
{
    Q_OBJECT

public:
    Router();
    ~Router();


    // ------------- GETTERS -------------
    Board& getBoard();

public slots:
    void changeOnglet(QString name);
    void restartGame();

private:
    // ------------- ATTRIBUTES -------------
    Home *home;
    Board *board;
    Player *player1;
    Player *player2;
    Game *game;

    friend class Board;
};


#endif // ROUTER_H

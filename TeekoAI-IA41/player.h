#ifndef PLAYER_H
#define PLAYER_H

#include <QtWidgets>
#include <iostream>


// Classe qui représente un joueur
class Player
{

public:
    Player(QString name = "", bool ia = true, int id = 0 );
    Player& operator= (const Player& pl);
    bool operator== (Player &rhs);

    // ------------- GETTERS -------------
    QString getName();
    bool isIA();
    int getID();
    bool hasPlayed();
    int pionOnBoard();
    bool chosePionToMove();
    int getPreviousIndex();

private:

    // ------------- SETTERS -------------
    void setName(QString);
    void setIA(bool);
    void setID(int);
    void setPlayed(bool);
    void setChosePionToMove(bool);
    void incrementPionOnBoard();
    void setPionOnBoard(int);
    void setPreviousIndex(int);

    // ------------- ATTRIBUTES -------------
    QString name;
    bool ia;
    int id;
    bool played;
    int pion_on_board;
    bool chose_pion_to_move;
    int previous_index;

    // ------------- FRIENDS -------------
    friend class Router;
    friend class Game;
};


#endif // PLAYER_H

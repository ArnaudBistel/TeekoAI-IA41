#ifndef BOARD_H
#define BOARD_H

#include <QtWidgets>
#include "iostream"
#include "pawn.h"
#include "playerpanel.h"

typedef int (*pointer_to_arrays)[5];

class Board : public QWidget
{
  Q_OBJECT

public:
    Board();
    Board(QWidget *parent,QString name);

    // ------------- GETTERS -------------
    pointer_to_arrays getBoard();
    void printBoard();


    // ------------- SLOTS -------------
public slots:
    void tileChosen();
    void resetGame();
    void goBack();

    // ------------- SLOTS -------------
signals:
    void changeInterface(QString name);
    void playerPlayed(int);
    void beginGame();

private:
    // ------------- METHODS -------------
    void placePion(int, int, int, bool, bool, bool);
    void displayPossibleMoves(int,int);
    void unselectPawn(int);


    void displayCurrentPlayer(int);
    void displayPlayers(QString, QString);
    void announceWinner(int, QString);
    void displayWinLabel(QString);


    void deletePossibleMoves();
    void setBoardLabelEnabled(bool);
    void prepareBoardForCurrentPlayer(int, int);
    void enableBoard();
    void initBoardVisible();
    void initBoardInvisible();
    void reinit();

    // ------------- ATTRIBUTES -------------
    int  board [5][5];
    // ---- synchronization de thread ----
    QMutex mutex;
    QWaitCondition sleepSimulator;


    // ----------------------------------
    // Fenêtre du jeu
    // ----------------------------------
    QLabel *board_label;
    Pawn* array[5][5];
    QGridLayout *but_and_image_layout;
    QLabel *win_label;


    // ----------------------------------
    // Panneau affichant les joueurs
    // ----------------------------------
    QVBoxLayout *panel_layout;
    QVBoxLayout *player1_layout;
    QGroupBox *player1_groupbox;
    QLabel *player1_name_label;
    QLabel *player1_type_label;
    QLabel *player1_color_label;
    QGroupBox *player2_groupbox;
    QVBoxLayout *player2_layout;
    QLabel *player2_name_label;
    QLabel *player2_type_label;
    QLabel *player2_color_label;


    // ----------------------------------
    // retour et recommencer
    // ----------------------------------
    QHBoxLayout *bottom_buttons_layout;
    QPushButton *back_to_home_button;
    QPushButton *reset_button;

    // -------------------------------------
    // vertical layout that contains all the widgets
    // -------------------------------------
    QVBoxLayout *v_layout;
    QHBoxLayout *h_layout;


    // ------------- FRIENDS -------------
    friend class Game;
    friend class Router;
};

#endif // BOARD_H

#ifndef BOARD_H
#define BOARD_H

#include <QtWidgets>
#include "iostream"
#include "Pawn.h"

typedef int (*pointer_to_arrays)[5];

class Board : public QWidget
{
  Q_OBJECT

public:
    Board();
    Board(QWidget *parent,QString name);

    void displayWinLabel(QString);

    // ------------- SLOTS -------------
public slots:
    void tileChosen();
    pointer_to_arrays getBoard();
//    pointer_to_arrays getBoard()
//    {
//        return this->board;
//    }

    /*
    void changeButtonPosition();
    void recordData();

    void startCountdown();
    void updateCountdown();
    void stopCountdown();
    void resetTest();
    void goToResults();
*/
        void printBoard();
    void goBack();
    void announceCurrentPlayer(QString);
    void prepareBoardForCurrentPlayer(int, int);
    void placePion(int, int, int, bool, bool);
    void initBoardVisible();
    void initBoardInvisible();
    void enableBoard();
    void afficherDeplacementPossible(int,int);
    void unselectPawn(int);

signals:
    void changeInterface(QString name);
    void playerPlayed(int);
private:

    // ------------- ATTRIBUTES -------------
    int  board [5][5];
    Pawn* array[5][5];

    // ----------------------------------
    // Instructions
    // ----------------------------------
//    QVBoxLayout *instructions_layout;
//    QLabel *instructions_label;

    // ----------------------------------
    // Fenêtre de test
    // ----------------------------------
    QLabel *board_label;

    QMutex mutex;
QWaitCondition sleepSimulator;

    QGridLayout *but_layout;
    QPushButton *test_but1, *test_but2, *test_but3, *test_but4, *test_but5;
    QPushButton *test_but11, *test_but12, *test_but13, *test_but14, *test_but15;
    QPushButton *test_but21, *test_but22, *test_but23, *test_but24, *test_but25;
    QPushButton *test_but31, *test_but32, *test_but33, *test_but34, *test_but35;
    QPushButton *test_but41, *test_but42, *test_but43, *test_but44, *test_but45;
    QGridLayout *but_and_image_layout;


    QLabel *win_label;
    QLabel *current_player_label;
    // ----------------------------------
    // Cible
    // ----------------------------------
//    QPushButton *click_me_button;
//    QTimer *countdown_timer;
//    QLabel *test_finished_label;
//    QString *beep_file;
//    QString *beeeep_file;
//    QSound *beep_sound;
//    QSound *beeeep_sound;

    // ----------------------------------
    // back, reset and results
    // ----------------------------------
    QHBoxLayout *bottom_buttons_layout;
    QPushButton *back_to_home_button;
//    QPushButton *results_button;
    QPushButton *reset_button;

    // -------------------------------------
    // vertical layout that contains all the widgets in the HomePage
    // -------------------------------------
    QVBoxLayout *v_layout;
    QHBoxLayout *h_layout;

    // ----------------------------------
    // Paramètres de test
    // ----------------------------------
//    QElapsedTimer *test_timer;
//    int click_count;
//    int target_number;
//    double a;
//    double b;
//    int target_size_mini;
//    int target_size_max;
//    FittsData *fitts_data;
//    QPoint last_recorded_pos;


    // ------------- METHODES -------------
//    void testFinished();
//    void initTarget();


    // ------------- SETTERS -------------
//    void setA(double a);
//    void setB(double b);
//    void setTargetNumber(int n);
//    void setTargetSizeMini(int m);
//    void setTargetSizeMax(int m);


    // ------------- GETTERS -------------
//    pointer_to_arrays getBoard();
//    FittsData& getFittsData();


    // ------------- FRIENDS -------------
    friend class Game;
//    friend class HomePage;
//    friend class ResultsPage;


};

#endif // BOARD_H

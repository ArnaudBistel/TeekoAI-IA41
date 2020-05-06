#ifndef HOME_H
#define HOME_H

#include <QtWidgets>
#include <iostream>
#include "player.h"
//#include

class Home : public QWidget
{
    Q_OBJECT

public:
    Home(QWidget *parent,QString name);
    ~Home();

public slots:
    void launch_game();
    void enableDifficultyChoice();
    void disableDifficultyChoice();

    bool isIAVsIA();
    bool isHumanVsIA();
    bool isHumanVsHuman();
    // ------------- SETTERS -------------
//    void setA(double a);
//    void setB(double b);
//    void setTargetNumber(int n);
//    void setTargetSizeMini(int m);
//    void setTargetSizeMax(int m);

signals:
    void changeInterface(QString name);

private:

    // -------------------------------------
    // top layout, contient le titre de l'app
    // -------------------------------------
    QLabel *title_label;
    QHBoxLayout *title_layout;

    // -------------------------------------
    // Fitts's law formula
    // -------------------------------------
/*    QGroupBox *fitts_formula_box;
    QHBoxLayout *fitts_box_layout;

    // formule de Fitts
    QVBoxLayout *fitts_formula_layout;
    QLabel *fitts_formula_label;
    QLabel *fitts_formula;

    // formulaire de choix de a et b
    QVBoxLayout *a_b_choice_layout;
    QFormLayout *a_b_form_layout;
    QLabel *a_b_choice_label;
    QDoubleSpinBox *a_spinbox;
    QDoubleSpinBox *b_spinbox;
    QFormLayout *fitts_form;
*/



    // -------------------------------------
    // mode box
    // -------------------------------------
    QGroupBox *configuration_box;
    QFormLayout *configuration_form;
    QRadioButton *button_human_vs_human;
    QRadioButton *button_human_vs_ia;
    QRadioButton *button_ia_vs_ia;

    QSpinBox *target_number_spinbox;
    QSpinBox *target_mini_size_spinbox;
    QSpinBox *target_max_size_spinbox;

    // -------------------------------------
    // difficulté box
    // -------------------------------------
    QGroupBox *difficulty_box;
    QFormLayout *difficulty_form;
    QRadioButton *button_easy;
    QRadioButton *button_medium;
    QRadioButton *button_hard;

    // -------------------------------------
    // quit / start buttons
    // -------------------------------------
    QHBoxLayout *buttons_layout;
    QPushButton *quit_button;
    QPushButton *start_button;


    // -------------------------------------
    // vertical layout that contains all the widgets in the Home
    // -------------------------------------
    QVBoxLayout *vertical_layout;
    QVBoxLayout *params_layout;
    QHBoxLayout *horizontal_layout;

};

#endif // HOME_H

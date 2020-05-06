#ifndef PAWN_H
#define PAWN_H

#include <QtWidgets>
#include "iostream"

class Pawn : public QPushButton
{
    Q_OBJECT

public:
    Pawn(const QString &text, QWidget *parent);


    // ------------- SLOTS -------------
public slots:

    int getIndex();

    bool isSelectable();

// encerclé quand sélectionné

    void isSelected(bool);
    void setSelectable(bool);
    void setColor(int);
    void setPlayer(int);
    void setIndex(int);


private:

    int index;
    int color;
    bool selected;
    int player;
    bool selectable;

};


#endif // PAWN_H

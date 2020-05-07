#include "pawn.h"
#include <iostream>

Pawn::Pawn(const QString &text, QWidget *parent): index(), color(), selected(), QPushButton(text, parent), player(), selectable()
{
    QString str = "background-color: white;";
    str+= "border-radius:50px;";
    str+="max-width:100px;";
    str+="max-height:100px;";
    str+="min-width:100px;";
    str+="min-height:100px;";
    this->setStyleSheet(str);

}


void Pawn::isSelected(bool b, bool reset)
{
    this->selected = b;
    if (b)
    {
        this->move(this->x(), this->y() - 10);

        QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
        effect->setBlurRadius(10); //Adjust accordingly
        effect->setOffset(10,10); //Adjust accordingly
        this->setGraphicsEffect(effect);

    } else {
        QString str = "background-color: white;";
        str+= "border-radius:50px;";
        str+="max-width:100px;";
        str+="max-height:100px;";
        str+="min-width:100px;";
        str+="min-height:100px;";
        this->setStyleSheet(str);

        if (!reset)
        {
            this->move(this->x(), this->y() + 10);
        }

        QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
        effect->setBlurRadius(0); //Adjust accordingly
        effect->setOffset(0,0); //Adjust accordingly
        this->setGraphicsEffect(effect);
    }

}

void Pawn::setSelectable(bool b)
{
    if (b)
    {
        this->selectable = true;
        QString str = "background-color: white;";
        str += "border-style: dotted;";
        str+= "border-width:3px;";
        str+= "border-radius:50px;";
        str += "border-color: black;";
        str+="max-width:100px;";
        str+="max-height:100px;";
        str+="min-width:100px;";
        str+="min-height:100px;";
        this->setStyleSheet(str);
    }else{
        this->selectable = false;
        QString str = "background-color: white;";
        str+= "border-radius:50px;";
        str+="max-width:100px;";
        str+="max-height:100px;";
        str+="min-width:100px;";
        str+="min-height:100px;";
        this->setStyleSheet(str);
    }
}


void Pawn::setColor(int c)
{
    if (c == 0)
    {
        QString str = "background-color: white;";
        str+= "border-radius:50px;";
        str+="max-width:100px;";
        str+="max-height:100px;";
        str+="min-width:100px;";
        str+="min-height:100px;";
        this->setStyleSheet(str);
    }
    else if (c == 1)
    {
        QString str = "background-color: blue;";
        str += "border-style: solid;";
        str+= "border-width:1px;";
        str+= "border-radius:50px;";
        str += "border-color: grey;";
        str+="max-width:100px;";
        str+="max-height:100px;";
        str+="min-width:100px;";
        str+="min-height:100px;";
        this->setStyleSheet(str);

        QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
        effect->setBlurRadius(3); //Adjust accordingly
        effect->setOffset(5,5); //Adjust accordingly
        this->setGraphicsEffect(effect);

    }
    else if (c == 2)
    {
        QString str = "background-color: red;";
        str += "border-style: solid;";
        str+= "border-width:1px;";
        str+= "border-radius:50px;";
        str += "border-color: grey;";
        str+="max-width:100px;";
        str+="max-height:100px;";
        str+="min-width:100px;";
        str+="min-height:100px;";
        this->setStyleSheet(str);

        QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
        effect->setBlurRadius(3); //Adjust accordingly
        effect->setOffset(5,5); //Adjust accordingly
        this->setGraphicsEffect(effect);

    }
}

void Pawn::setPlayer(int p)
{
    this->player = p;
    this->setColor(p);
}


void Pawn::setIndex(int i)
{
    this->index = i;
}


int Pawn::getIndex()
{
    return this->index;
}


bool Pawn::isSelectable()
{
    return this->selectable;
}

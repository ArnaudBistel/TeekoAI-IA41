#include "playerpanel.h"
//PlayerPanel::PlayerPanel(QWidget *parent, QString player_name, QString color_file) : QFrame(parent), player_name(player_name), color_file(color_file)
PlayerPanel::PlayerPanel(QString player_name, QString color_file, int size) : player_name(player_name), color_file(color_file)
{
    QVBoxLayout layout;
    this->setLayout(&layout);
    player_name_label= new QLabel(player_name);
    player_type_label = new QLabel("");
    player_color_label = new QLabel;
    QPixmap pix(color_file);
    pix.scaled(size , size ,Qt::KeepAspectRatio);
    player_color_label->setPixmap(pix);
    layout.addWidget(player_name_label);
    layout.addWidget(player_type_label);
    layout.addWidget(player_color_label);
//    this->show();
}


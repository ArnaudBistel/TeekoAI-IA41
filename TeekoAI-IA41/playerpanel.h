#ifndef PLAYERPANEL_H
#define PLAYERPANEL_H

#include <QtWidgets>

class PlayerPanel : public QWidget
{

  Q_OBJECT

public:
    PlayerPanel(QString, QString, int);
//    PlayerPanel(QWidget *parent,QString, QString);
private:
    QString player_name;
    QString color_file;

    QLabel *player_name_label;
    QLabel *player_type_label;
    QLabel *player_color_label;

};


#endif // PLAYERPANEL_H

#include "Router.h"


// Classe qui hérite de QStackedWidget et permet donc de transiter entre
// les différentes pages de l'application
Router::Router()
{
    game = new Game(this);

    home = new Home(this, "home");
    this->addWidget(static_cast<QWidget*>(home));

    board = new Board(this, "board");
    this->addWidget(static_cast<QWidget*>(board));

    this->setCurrentWidget(home);
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);


}


void Router::restartGame()
{
    game->terminate();
    qDebug() << "try to stop thread";

    while(!game->isFinished()){}

    if(!game->isRunning())
    {
        qDebug() << "thread is stopped";
        game->restartGame();
//        QThread::msleep(300);
        qDebug() << "READY TOO !!!!";
        this->setCurrentWidget(board);
        game->start();
    }

}



Router::~Router()
{}


//Controlleur : slot pour changer de page
void Router::changeOnglet(QString name)
{

    if((name == home->objectName()) && home)
    {
        this->setCurrentWidget(home);
        return;
    }
    else if((name == board->objectName()) && board)
    {
        int mode = 0;
        if (home->isIAVsIA())
        {
            mode = 1;
            board->displayPlayers("IA", "IA");
        }
        else if (home->isHumanVsIA())
        {
            mode = 2;
            board->displayPlayers("HUMAN", "IA");
        }

        else if (home->isHumanVsHuman())
        {
            mode = 3;
            board->displayPlayers("HUMAN", "HUMAN");
        }

        game->setMode(mode);
        game->start();

        this->setCurrentWidget(board);
        return;
    }

    else
    {
        QMessageBox::information(0,tr("Erreur changement onglet"),tr("Impossible de changer l'interface pour l'onglet ")+name+tr(".\nCet onglet n'existe plus ou n'a pas été créer."));
    }
}


// -----------------------------------
// ------------- GETTERS -------------
// -----------------------------------


Board& Router::getBoard()
{
    return *board;
}

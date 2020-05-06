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
//    game = new Game;

//    results_page = new ResultsPage(this, "results_page");
//    this->addWidget(static_cast<QWidget*>(results_page));

    this->setCurrentWidget(home);
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
}



// -----------------------------------
// ------------- GETTERS -------------
// -----------------------------------


Board& Router::getBoard()
{
    return *board;
}

/*
ResultsPage& Router::getResultsPage()
{
    return *results_page;
}
*/

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
        }
        else if (home->isHumanVsIA())
        {
            mode = 2;
        }

        else if (home->isHumanVsHuman())
        {
            mode = 3;
        }

        game->setMode(mode);
        game->start();

        this->setCurrentWidget(board);
//        fitts_page->startCountdown();
        return;
    }
//    else if((name == results_page->objectName()) && results_page)
//    {
//        this->setCurrentWidget(results_page);
//        return;
//    }
    else
    {
        QMessageBox::information(0,tr("Erreur changement onglet"),tr("Impossible de changer l'interface pour l'onglet ")+name+tr(".\nCet onglet n'existe plus ou n'a pas été créer."));
    }
}

#include "game.h"
#include "Router.h"

// Classe qui contient la logique du jeu.

// CONSTRUCTOR
Game::Game(QWidget *parent) : player1(), player2(), current_player(), win(), board(), parent(parent), pause()
{
}



// -------------------------------------------
// -------------- GAME METHODS ---------------
// -------------------------------------------

// boucle du jeu
void Game::run()
{
    // choisi aléatoirement qui est le premier joueur
    this->chooseFirstPlayer();

    while ( !this->win )
    {
        // attend un choix de move du joueur courant
        while (!current_player->hasPlayed())
        {
            if (current_player->isIA())
            {
                QThread::msleep(500);
//                static_cast<Router*>(this->parent)->getBoard().setBoardLabelEnabled(false);
                int move = this->current_player->getIAMove(this->board);
                emit playerPlayed(move);
            }
        }

        // joueur courant a choisi son action
        if (current_player->hasPlayed())
        {

            // imprime le board dans la console
            static_cast<Router*>(this->parent)->getBoard().printBoard();

            // on vérifie si le dernier déplacement a permis une victoire
            this->win = this->checkIfWins(current_player->getID());

            // victoire !
            if (this->win)
            {
                // affiche le vainqueur
                static_cast<Router*>(this->parent)->getBoard().announceWinner(current_player->getID(), current_player->getName());
            }

            // pas de victoire
            else {
                // nouveau joueur courant
                this->changeCurrentPlayer();
                // prepare la vue pour le nouveau joueur courant
                this->prepareBoardForNextTurn();
            }
        }

        while (this->isPaused())
        {
            QThread::msleep(1000);
        }

        QThread::msleep(500);

    }
}

// Reset le jeu pour une nouvelle partie.
// Méthode lancée en cas d'appuie sur Recommencer
void Game::restartGame()
{
    // reset le board
    static_cast<Router*>(this->parent)->getBoard().reinit();

    // reset des attributs de Game
    this->win = false;
    this->pause = false;
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            this->board[i][j]=0;
        }
    }

    // reset les attributs des joueurs
    player1->setPlayed(false);
    player1->setChosePionToMove(false);
    player1->setPionOnBoard(0);
    player1->setPreviousIndex(-1);

//    player1.setPlayed(false);
//    player1.setChosePionToMove(false);
//    player1.setPionOnBoard(0);
//    player1.setPreviousIndex(-1);

//    player2.setPlayed(false);
//    player2.setChosePionToMove(false);
//    player2.setPionOnBoard(0);
//    player2.setPreviousIndex(-1);

    player2->setPlayed(false);
    player2->setChosePionToMove(false);
    player2->setPionOnBoard(0);
    player2->setPreviousIndex(-1);

//    // réactive le board
//    if(! (player1->isIA() && player2->isIA()))
//        static_cast<Router*>(this->parent)->getBoard().setBoardLabelEnabled(true);

}



// Méthode qui regroupe les méthodes de vérification de victoire.
bool Game::checkIfWins(int id)
{
    bool win;
    win = this->checkRows(id);
    if (win)
        return win;
    win = this->checkCol(id);
    if (win)
        return win;
    win = this->checkSquare(id);
    if (win)
        return win;
    win = this->checkDiag(id);
    if (win)
        return win;

    return false;
}



// Appelée par Board lorsque le joueur courant a appuyé sur un pion ou placé un pion.
void Game::playerPlayed(int index)
{
    int line = (int) index / 5;
    int col = index % 5;

    // moins de 4 pions joués donc le joueur place son jeton
    // il va où il veut
    if (current_player->pionOnBoard() < 4)
    {
        // sauvegarde l'état du plateau
        this->board[line][col] = this->current_player->getID();

        // mise à jour de la vue
        static_cast<Router*>(this->parent)->getBoard().placePion(current_player->getID(), line, col, false, false, false);

        this->current_player->incrementPionOnBoard();
        this->current_player->setPlayed(true);


    // quand tous les joueurs ont joué leur 4 pions, ils doivent déplacer un pion par tour
    } else {

        // si le joueur n'a pas encore sélectionné de pion à déplacer
        if (!current_player->chosePionToMove())
        {
            this->current_player->setChosePionToMove(true);
            this->board[line][col] = 0;

            // sauvegarde l'ancienne position du pion
            this->current_player->setPreviousIndex(index);

            // mise à jour de la vue
            static_cast<Router*>(this->parent)->getBoard().placePion(0, line, col, true, true, false);
            static_cast<Router*>(this->parent)->getBoard().displayPossibleMoves(line, col);

        // si le joueur a déjà choisi son pion à déplacer
        } else {

            // cas où joueur déselctionne son pion pour en choisir un autre
            if (index == this->current_player->getPreviousIndex())
            {
                this->current_player->setChosePionToMove(false);
                static_cast<Router*>(this->parent)->getBoard().placePion(current_player->getID(), line, col, false, true, true);
                this->board[line][col] = current_player->getID();
                this->prepareBoardForNextTurn();

            // cas où il déplace son pion
            } else {
                this->board[line][col] = this->current_player->getID();
                static_cast<Router*>(this->parent)->getBoard().placePion(current_player->getID(), line, col, false, false, false);
                this->current_player->setPlayed(true);
                static_cast<Router*>(this->parent)->getBoard().unselectPawn(current_player->getPreviousIndex());
            }
        }
    }

//    static_cast<Router*>(this->parent)->getBoard().repaint();
}



// Demande au board de préparer la vue pour le joueur transmis en param.
void Game::prepareBoardForNextTurn()
{
    static_cast<Router*>(this->parent)->getBoard().prepareBoardForCurrentPlayer(current_player->getID(), current_player->pionOnBoard());
    QThread::msleep(200);
}






// -------------------------------------------
// -------------- BOARD METHODS --------------
// -------------------------------------------
void Game::printBoard()
{
    for(int i=0; i<5; i++)
    {
            for(int j=0; j<5; j++)
            {
                    std::cout<<" "<<board[i][j]<<" ";
            }
            std::cout<<"\n";
    }

}



bool Game::checkRows(int id)
{
    for (int j = 0 ; j < 2; j++ )
    {
        for (int i = 0 ; i < 5; i++ )
        {
            if(board[i][j]     ==  id &&
               board[i][j+1]   ==  id &&
               board[i][j+2]   ==  id &&
               board[i][j+3]   ==  id)
            {
                return true;
            }
        }
    }
    return false;
}



bool Game::checkCol(int id)
{
    for (int i = 0 ; i < 2; i++ )
    {
        for (int j = 0 ; j < 5; j++ )
        {
            if(board[i][j]       ==  id &&
               board[i+1][j]   ==  id &&
               board[i+2][j]   ==  id &&
               board[i+3][j]   ==  id)
            {
                return true;
            }
        }
    }
    return false;
}



bool Game::checkSquare(int id)
{
    for(int i=0;i<4;i++)
    {

        for(int j=0;j<4;j++)
        {
            if(board[i][j]       ==  id &&
               board[i][j+1]     ==  id &&
               board[i+1][j]     ==  id &&
               board[i+1][j+1]   ==  id)
            {
                return true;
            }
        }
    }
    return false;
}



bool Game::checkDiag(int id)
{
    for (int i = 0 ; i < 2; i++ )
    {
        for (int j = 0 ; j < 2; j++ )
        {
            if(board[i][j]       ==  id &&
               board[i+1][j+1]   ==  id &&
               board[i+2][j+2]   ==  id &&
               board[i+3][j+3]   ==  id)
            {
                return true;
            }
        }
    }

    for (int i = 0 ; i < 2; i++ )
    {
        for (int j = 3 ; j < 5; j++ )
        {
            if(board[i][j]       ==  id &&
               board[i+1][j-1]   ==  id &&
               board[i+2][j-2]   ==  id &&
               board[i+3][j-3]   ==  id)
            {
                return true;
            }
        }
    }

    return false;
}




// -------------------------------------------
// ------------- PLAYERS METHODS -------------
// -------------------------------------------

// Choix aléatoire du premier joueur à jouer.
void Game::chooseFirstPlayer()
{
    int MAX = 100, MIN = 1;

    // Génération du nombre aléatoire
    srand(time(NULL));
    int random = (rand() % (MAX - MIN + 1)) + MIN;
    if (random > 50 )
    {
//        current_player = &player1;
        current_player = player1;
        static_cast<Router*>(this->parent)->getBoard().displayCurrentPlayer(1);

    } else {
        current_player = player2;
//        current_player = &player2;
        static_cast<Router*>(this->parent)->getBoard().displayCurrentPlayer(2);
    }

    if (!current_player->isIA())
    {
        static_cast<Router*>(this->parent)->getBoard().setBoardLabelEnabled(true);
    } else {
        static_cast<Router*>(this->parent)->getBoard().setBoardLabelEnabled(false);
    }
}


// Switche le joueur courant.
void Game::changeCurrentPlayer()
{
//    if (current_player == &player1)
    if (current_player == player1)
    {
//        player1.setPlayed(false);
//        player1.setChosePionToMove(false);
//        current_player = &player2;
        player1->setPlayed(false);
        player1->setChosePionToMove(false);
        current_player = player2;
        static_cast<Router*>(this->parent)->getBoard().displayCurrentPlayer(2);
    }else
    {
//        player2.setPlayed(false);
//        player2.setChosePionToMove(false);
//        current_player = &player1;
        player2->setPlayed(false);
        player2->setChosePionToMove(false);
        current_player = player1;
        static_cast<Router*>(this->parent)->getBoard().displayCurrentPlayer(1);
    }
    if (!current_player->isIA())
    {
        static_cast<Router*>(this->parent)->getBoard().setBoardLabelEnabled(true);
    } else {
        static_cast<Router*>(this->parent)->getBoard().setBoardLabelEnabled(false);
    }
}



// -------------------------------------------
// ----------------- SETTERS -----------------
// -------------------------------------------

void Game::setPlayer1(Player pl)
{
//    this->player1 = pl;
//    this->player1.isIA();
    this->player1 = &pl;
    this->player1->isIA();
}

void Game::setPlayer2(Player pl)
{
//    this->player2 = pl;
//    this->player2.isIA();
    this->player2 = &pl;
    this->player2->isIA();
}



// Gestion de l'IA
void Game::setMode(int mode, int diff)
{
    if (mode == 1)
    {
//        AIPlayer pl1("Joueur 1", 1, diff);
//        player1 = pl1;

//        AIPlayer pl2("Joueur 2", 2, diff);
//        player2 = pl2;

        player1 = new AIPlayer("Joueur 1", 1, diff);
        player2 = new AIPlayer("Joueur 2", 2, diff);
    } else if (mode == 2) {
//        Player pl1("Joueur 1", false, 1);
//        player1 = pl1;

//        AIPlayer pl2("Joueur 2", 2, diff);
//        player2 = pl2;
        player1 = new Player("Joueur 1", false, 1);
        player2 = new AIPlayer("Joueur 2", 2, diff);
    } else if (mode == 3) {
//        Player pl1("Joueur 1", false, 1);
//        player1 = pl1;
//        Player pl2("Joueur 2", false, 2);
//        player2 = pl2;
        player1 = new Player("Joueur 1", false, 1);
        player2 = new Player("Joueur 2", false, 2);
    }



}

void Game::setPause(bool b)
{
    this->pause = b;
    if (current_player != NULL)
        static_cast<Router*>(this->parent)->getBoard().setBoardLabelEnabled(!this->current_player->isIA());
}





// -------------------------------------------
// ----------------- GETTERS -----------------
// -------------------------------------------

pointer_to_arrays Game::getBoard()
{
    return this->board;
}


bool Game::isPaused()
{
    return this->pause;
}

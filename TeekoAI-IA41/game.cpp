#include "game.h"
#include "Router.h"


Game::Game(QWidget *parent) : player1(), player2(), current_player(), win(), board(), parent(parent)
{
    player1 = new Player("Joueur 1", true, 1);
    player2 = new Player("Joueur 2", true, 2);
}



//Game::Game(Board& the_board) : player1(), player2(), current_player(), win(), board()
//{

//}



// -------------------------------------------
// -------------- GAME METHODS ---------------
// -------------------------------------------

void Game::run()
{
//    cout << "dans run" << endl;
    this->chooseFirstPlayer();
//     cout << "Joueur " << current_player->getName() << endl;


    while ( !this->win )
    {
        static_cast<Router*>(this->parent)->getBoard().announceCurrentPlayer(current_player->getName());

/*        this->current_player->play();

*/
        while (!current_player->hasPlayed())
        {
//            cout << "attente de jeu : " <<current_player->hasPlayed()<<  endl;
        }

        if (current_player->hasPlayed())
        {

            static_cast<Router*>(this->parent)->getBoard().printBoard();
//            cout << "COUCOU" << endl;

            this->win = this->checkIfWins(current_player->getID());
            if (this->win)
            {
                cout << current_player->getName().toStdString() << " a gagné !! " << endl;
//                this->endGame(current_player->getName());
            }
            else {
              this->changeCurrentPlayer();
              this->prepareBoardForNextTurn();
              QThread::sleep(1);
            }
        }

    }
}


void Game::prepareBoardForNextTurn()
{
    static_cast<Router*>(this->parent)->getBoard().prepareBoardForCurrentPlayer(current_player->getID(), current_player->pionOnBoard());
              QThread::sleep(0.5);
}


void Game::playerPlayed(int index)
{
    int line = (int) index / 5;
    int col = index % 5;

    // moins de 4 pions joués donc joueur place son jeton
    if (current_player->pionOnBoard() < 4)
    {
//        cout << "line :" << line  << endl;
//        cout << "col :" << col << endl;

    cout << "dans player played de game" << endl;
        this->board[line][col] = this->current_player->getID();
        static_cast<Router*>(this->parent)->getBoard().placePion(current_player->getID(), line, col, false, false);

        this->current_player->incrementPionOnBoard();
        this->current_player->setPlayed(true);
        // va où il veut

    } else {
        if (!current_player->chosePionToMove())
        {
            // choisir pion
            this->current_player->setChosePionToMove(true);
            this->board[line][col] = 0;
            this->current_player->setPreviousIndex(index);
            static_cast<Router*>(this->parent)->getBoard().placePion(0, line, col, true, true);
//            static_cast<Router*>(this->parent)->getBoard().placePion(0, line, col);
            static_cast<Router*>(this->parent)->getBoard().afficherDeplacementPossible(line, col);

        } else {
            this->board[line][col] = this->current_player->getID();
            static_cast<Router*>(this->parent)->getBoard().placePion(current_player->getID(), line, col, false, false);
            this->current_player->setPlayed(true);
            static_cast<Router*>(this->parent)->getBoard().unselectPawn(current_player->getPreviousIndex());

        }
        // puis le placer
    }


}

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

    return false;
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
    int counter;
    for(int i=0; i<5; i++)
    {
        counter = 0;
        for(int j=0; j<5; j++)
        {
            if (board[i][j] == id)
                counter++;
        }
        if (counter >= 4)
            return true;
    }
    return false;
}


bool Game::checkCol(int id)
{
    int counter;
    for(int i=0; i<5; i++)
    {
        counter = 0;
        for(int j=0; j<5; j++)
        {
            if (board[j][i] == id)
                counter++;
        }
        if (counter >= 4)
            return true;
    }
    return false;
}


//void Game::endGame(QString name)
//{
//    displayWinLabel(name);
//}


bool Game::checkSquare(int id)
{
    bool win;

    for(int i=0;i<4;i++)
    {

        for(int j=0;j<4;j++)
        {
            if(board[i][j]       ==  id &&\
               board[i][j+1]     ==  id &&\
               board[i+1][j]     ==  id &&\
               board[i+1][j+1]   ==  id)
            {
                win = true;
            }
        }
    }
    return win;
}



pointer_to_arrays Game::getBoard()
{
    return this->board;
}



// -------------------------------------------
// ------------- PLAYERS METHODS -------------
// -------------------------------------------

void Game::chooseFirstPlayer()
{
    int MAX = 100, MIN = 1;

    // Génération du nombre aléatoire
    srand(time(NULL));
    int random = (rand() % (MAX - MIN + 1)) + MIN;
    std::cout<<"random = "<<random<<" ";
    if (random > 50 )
        current_player = player1;
    else {
        current_player = player2;
    }
}

void Game::changeCurrentPlayer()
{
    if (current_player == player1)
    {
        player1->setPlayed(false);
        player1->setChosePionToMove(false);
        current_player = player2;
    }else
    {
        player2->setPlayed(false);
        player2->setChosePionToMove(false);
        current_player = player1;
    }
}

void Game::setMode(int mode)
{
//    cout << "dans setMode " << endl;
    if (mode == 1)
    {
        this->player1->setIA(true);
        this->player2->setIA(true);
    } else if (mode == 2) {
        this->player1->setIA(false);
        this->player2->setIA(true);
    } else if (mode == 3) {
        this->player1->setIA(false);
        this->player2->setIA(false);
    }
}



// -------------------------------------------
// ----------------- SETTERS -----------------
// -------------------------------------------

void Game::setPlayer1(Player pl)
{
    this->player1 = &pl;
    this->player1->getName();
    this->player1->isIA();
}

void Game::setPlayer2(Player pl)
{
    this->player2 = &pl;
    this->player2->isIA();
}




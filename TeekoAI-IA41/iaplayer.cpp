#include "iaplayer.h"

IAPlayer::IAPlayer(QString name, int id, int difficulty )
    : Player(name, true, id), move(), difficulty(difficulty)
{
}

int IAPlayer::getIAMove(int  board [5][5])
{
    this->findMove(board);
    return this->move;
}


int IAPlayer::getDifficulty()
{
    return this->difficulty;
}

void IAPlayer::findMove(int  board [5][5])
{
    std::vector< int > pawns;
    int move(-1);

    // récupère la liste des index des pions de l'IA
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            if (board[i][j] == this->id)
            {
                pawns.push_back(i*5 + j);
            }
        }
    }

    // Difficulté facile
//    if (this->difficulty == 1 )
//    {
        if (this->pionOnBoard() >= 4 && !this->chosePionToMove()) {
            int MAX = 3, MIN = 0;
            srand(time(NULL));
            move = (rand() % (MAX - MIN + 1)) + MIN;
            std::cout << "move : " << move << std::endl;
            move = pawns[move];

        } else if (this->pionOnBoard() >= 4 && this->chosePionToMove())
        {
            pawns = this->computePossibleMoves(this->previous_index, board);
            int MAX = pawns.size() - 1;
            int MIN = 0;
            srand(time(NULL));
            move = (rand() % (MAX - MIN + 1)) + MIN;
            std::cout << "move : " << move << std::endl;
            move = pawns[move];

        } else if (this->pionOnBoard() < 4) {
            int MAX = 24, MIN = 0;

            // Génération du nombre aléatoire
            srand(time(NULL));
            move = (rand() % (MAX - MIN + 1)) + MIN;
            std::cout << "move : " << move << std::endl;
        }
//    }


    // Difficulté Moyenne
//    else if (this->difficulty == 2 )
//    {


//    // Difficulté difficile
//    }else if (this->difficulty == 3 )
//    {
//    }
    this->move = move;
}



// affiche les déplacements possible après qu'un joueur a sélectionné un pion
std::vector<int> IAPlayer::computePossibleMoves(int index, int  board [5][5])
{
    int line = (int) index / 5;
    int col = index % 5;
    std::vector< int > pawns;

    // évaluation des choix possibles
    int i, j = 0;

    if (line - 1 >= 0 && col - 1 >= 0 )
    {
        i = line - 1;
        j = col - 1;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        }
    }

    if (line - 1 >= 0)
    {
        i = line - 1;
        j = col;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        }
    }

    if (line - 1 >= 0 && col + 1 <= 4)
    {
        i = line - 1;
        j = col + 1;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        }
    }

    if (col + 1 <= 4)
    {
        i = line;
        j = col + 1;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        }
    }

    if (line + 1 <= 4 && col + 1 <= 4 )
    {
        i = line + 1;
        j = col + 1;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        }
    }

    if (line + 1 <= 4)
    {
        i = line + 1;
        j = col;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        }
    }

    if (line + 1 <= 4 && col - 1 >= 0)
    {
        i = line + 1;
        j = col - 1;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        }
    }

    if (col - 1 >= 0)
    {
        i = line;
        j = col - 1;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        }
    }

    return pawns;
}


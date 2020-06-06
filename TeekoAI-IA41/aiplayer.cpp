#include "aiplayer.h"

// todo changer les if id == 2 par un controle qui checke l'ia courante

AIPlayer::AIPlayer(QString name, int id, int difficulty )
    : Player(name, true, id), move(), difficulty(difficulty), pawn_to_move(-1), where_to_move_pawn(-1)
{
}

AIPlayer& AIPlayer::operator=(const AIPlayer& pl)
{
    if ( this == &pl)	return *this;
    this->id = pl.id;
    this->name 	= pl.name;
    this->ia    = pl.ia;
    this->move = pl.move;
    this->difficulty = pl.difficulty;

//    std::cout << "dans = " << pl.name << std::endl;
    return *this;
}


bool AIPlayer::operator== (AIPlayer &rhs)
{
    if (rhs.isIA() == this->isIA() &&
            rhs.getID() == this->getID() &&
            rhs.getName() == this->getName() &&
            rhs.move == this->move &&
            rhs.difficulty == this->difficulty
            )
        return true;
    return false;
}



int AIPlayer::getIAMove(int  board [5][5])
{
    this->findMove(board);
    return this->move;
}


int AIPlayer::getDifficulty()
{
    return this->difficulty;
}

void AIPlayer::findMove(int  board [5][5])
{
    // AI's pawns
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
        // si l'IA a déjà placé ses 4 pions et qu'elle n'a pas encore choisi
        // quel pion elle va déplacer
        if (this->pionOnBoard() >= 4 && !this->chosePionToMove()) {
            int MAX = 3, MIN = 0;

            // choisi au hasard un pion à déplacer parmis ses 4 pions
            srand(time(NULL));
            move = (rand() % (MAX - MIN + 1)) + MIN;
//            std::cout << "move : " << move << std::endl;
            move = pawns[move];

        // si l'IA a déjà placé ses 4 pions et qu'elle a choisi
        // quel pion elle va déplacer
        } else if (this->pionOnBoard() >= 4 && this->chosePionToMove())
        {
            // cherche les déplacements possibles pour le pion qu'elle souhaite déplacer
            // qui se trouve dans previous_index
            pawns = this->computePossibleMoves(this->previous_index, board);
            int MAX = pawns.size() - 1;
            int MIN = 0;
            // choisi au hasard un déplacement parmis les déplacements possibles
            srand(time(NULL));
            move = (rand() % (MAX - MIN + 1)) + MIN;
//            std::cout << "move : " << move << std::endl;
            move = pawns[move];

        // si l'IA n'a pas encore placé ses 4 pions
        } else if (this->pionOnBoard() < 4) {
            int MAX = 24, MIN = 0;

            // Génération du nombre aléatoire
            srand(time(NULL));
            // choisi une case au hasard sur le plateau
            move = (rand() % (MAX - MIN + 1)) + MIN;

            // si la case est déjà occupée on en cherche une autre
            while (board[(int) move / 5][move % 5] != 0)
            {
                move = (rand() % (MAX - MIN + 1)) + MIN;
            }

//            std::cout << "move : " << move << std::endl;
        }
//    }

    this->move = move;
}



// retourne un vecteur contenant les index des déplacements possibles pour le
// pion dont l'index est passé en paramètre
// Donc l'ensemble des cases adjacentes qui ne sont pas déjà occupées
std::vector<int> AIPlayer::computePossibleMoves(int index, int  board [5][5])
{
//    std::cout << "AIPlayer::computePossibleMoves : " << std::endl;
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




// retourne un vecteur contenant les index des déplacements possibles pour le
// pion dont l'index est passé en paramètre
// Donc l'ensemble des cases adjacentes qui ne sont pas déjà occupées
std::vector<int> AIPlayer::computeSquaresAroundSquare(int index, int  board [5][5])
{
//    std::cout << "AIPlayer::computeSquaresAroundSquare : " << std::endl;
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
        } else {
            pawns.push_back(-1);
        }
    } else {
        pawns.push_back(-1);
    }

    if (line - 1 >= 0)
    {
        i = line - 1;
        j = col;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        } else {
            pawns.push_back(-1);
        }
    } else {
        pawns.push_back(-1);
    }

    if (line - 1 >= 0 && col + 1 <= 4)
    {
        i = line - 1;
        j = col + 1;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        } else {
            pawns.push_back(-1);
        }
    } else {
        pawns.push_back(-1);
    }

    if (col + 1 <= 4)
    {
        i = line;
        j = col + 1;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        } else {
            pawns.push_back(-1);
        }
    } else {
        pawns.push_back(-1);
    }

    if (line + 1 <= 4 && col + 1 <= 4 )
    {
        i = line + 1;
        j = col + 1;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        } else {
            pawns.push_back(-1);
        }
    } else {
        pawns.push_back(-1);
    }

    if (line + 1 <= 4)
    {
        i = line + 1;
        j = col;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        } else {
            pawns.push_back(-1);
        }
    } else {
        pawns.push_back(-1);
    }

    if (line + 1 <= 4 && col - 1 >= 0)
    {
        i = line + 1;
        j = col - 1;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        } else {
            pawns.push_back(-1);
        }
    } else {
        pawns.push_back(-1);
    }

    if (col - 1 >= 0)
    {
        i = line;
        j = col - 1;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        } else {
            pawns.push_back(-1);
        }
    } else {
        pawns.push_back(-1);
    }

    return pawns;
}




int AIPlayer::Minimax(int  board [5][5], int depth, bool is_maximizing, int alpha, int beta) {

}



void AIPlayer::copyBoard(int board [5][5], int new_board [5][5])
{
//    std::cout << "AIPlayer::copyBoard : " << std::endl;
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            new_board[i][j] = board[i][j];
        }
    }
}

void AIPlayer::printBoard(int b [5][5])
{
    for(int i=0; i<5; i++)
    {
            for(int j=0; j<5; j++)
            {
                    std::cout<<" "<<b[i][j]<<" ";
            }
            std::cout<<"\n";
    }

}

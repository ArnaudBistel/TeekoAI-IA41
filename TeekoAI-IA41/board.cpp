#include "board.h"
#include <iostream>
#include "Router.h"

// gérer cas où joueur reclique sur pion pour annuler sélection

Board::Board()
{}


Board::Board(QWidget *parent, QString name):
    QWidget(parent), board()
{

    for(int i=0; i<5; i++)
    {
            for(int j=0; j<5; j++)
            {
                    std::cout<<" "<<board[i][j]<<" ";
            }
            std::cout<<"\n";
    }


    this->setObjectName(name);
    // pour la transition entre les pages via MainWindow
    connect(this,SIGNAL(changeInterface(QString)), this->parent(),SLOT(changeOnglet(QString)));
    connect(this, SIGNAL(beginGame()), this->parent(), SLOT(restartGame()));
    connect(this,SIGNAL(playerPlayed(int)),  static_cast<Router*>(this->parent())->game,SLOT(playerPlayed(int)));



    // ----------------------------------
    // Fenêtre de jeu
    // ----------------------------------

    // ------------- Plateau ------------
    // récupère la taille de l'écran de l'utilisateur pour adapter la fenêtre de test
    board_label = new QLabel(this);
    QRect window = QGuiApplication::screens().first()->geometry();
    int screen_height = window.height();
    int screen_width = window.width();
    double board_size = screen_height * 3/4;
    board_label->setFixedSize(board_size, board_size);
    QPixmap board_image("./res/teeko_board_v.png");
//    QPixmap board_image("../res/teeko_board_v.png");
    board_label->setPixmap(board_image);
    board_label->setScaledContents( true );


    // -------------- Pions ---------------
    // mise en place des bouttons/Pions
    int index = 0;
    int y = board_label->height()/33;
    int x = board_label->height()/32.4;
    int height = board_label->height() / 8.1;

    for(int i = 0;i<5;i++){
        for(int j = 0;j<5;j++){
            Pawn *pawn = new Pawn("", board_label);
            pawn->setGeometry(x, y, height , height);

            // Next line will be used to help find the Path later
            array[i][j] = pawn;
            pawn->setIndex(index);
            index++;

            // Connects buttons to setStartEnd() function
            connect(pawn, SIGNAL(clicked()), this, SLOT(tileChosen()));
            x += board_label->height()/4.90;
        }
        x = board_label->height()/32.4;
        y += board_label->height()/4.89;

    }


    // --------- Label de victoire ---------
    win_label = new QLabel("", board_label);
    win_label->setAlignment(Qt::AlignCenter);
    win_label->setFont(QFont("Comic Sans MS", 18, QFont::Bold, false));
    win_label->setStyleSheet("QLabel {margin-left: 10px; background:white; border-radius: 25px; border: 2px solid black; color: black;}");
    win_label->setVisible(false);


    but_and_image_layout = new QGridLayout;
    but_and_image_layout->addWidget(board_label,0,0);
    but_and_image_layout->addWidget(win_label,0,0);



    // ----------------------------------
    // Panneau affichant les joueurs
    // ----------------------------------
    panel_layout = new QVBoxLayout;
    panel_layout->insertSpacing(0, screen_height * 1/7);

    player1_groupbox = new QGroupBox("", this);
    player1_groupbox->setStyleSheet("QGroupBox { border-radius: 9px;padding-right: 24px;padding-left: 24px;border: 1px solid gray;}");
    player1_layout = new QVBoxLayout;
    player1_name_label = new QLabel("Joueur 1");
    player1_name_label->setFont(QFont("Comic Sans MS", 15));
    player1_name_label->setAlignment(Qt::AlignHCenter);
    player1_type_label = new QLabel("");
    player1_type_label->setFont(QFont("Comic Sans MS", 12));
    player1_type_label->setAlignment(Qt::AlignHCenter);
    player1_color_label = new QLabel;
    QPixmap pix("./res/blue_pawn.png");
//    QPixmap pix("../res/blue_pawn.png");
    player1_color_label->setPixmap(pix.scaled((board_label->height() / 8.1) - 10 , (board_label->height() / 8.1) -10 ,Qt::KeepAspectRatio));

    player1_layout->addWidget(player1_name_label);
    player1_layout->addWidget(player1_type_label);
    player1_layout->addWidget(player1_color_label);
    player1_groupbox->setLayout(player1_layout);
    panel_layout->addWidget(player1_groupbox);


    panel_layout->insertSpacing(2, screen_height * 1/7);


    player2_groupbox = new QGroupBox("", this);
    player2_groupbox->setStyleSheet("QGroupBox { border-radius: 9px;padding-right: 24px;padding-left: 24px;border: 1px solid gray;}");
    player2_layout = new QVBoxLayout;
    player2_name_label = new QLabel("Joueur 2");
    player2_name_label->setFont(QFont("Comic Sans MS", 15));
    player2_name_label->setAlignment(Qt::AlignHCenter);
    player2_type_label = new QLabel("");
    player2_type_label->setFont(QFont("Comic Sans MS", 12));
    player2_type_label->setAlignment(Qt::AlignHCenter);
    player2_color_label = new QLabel;
    QPixmap pix2("./res/red_pawn.png");
//    QPixmap pix2("../res/red_pawn.png");
    player2_color_label->setPixmap(pix2.scaled((board_label->height() / 8.1) - 10 , (board_label->height() / 8.1) -10 ,Qt::KeepAspectRatio));

    player2_layout->addWidget(player2_name_label);
    player2_layout->addWidget(player2_type_label);
    player2_layout->addWidget(player2_color_label);

    player2_groupbox->setLayout(player2_layout);
    panel_layout->addWidget(player2_groupbox);

    panel_layout->insertSpacing(4, screen_height * 1/7);



    // ----------------------------------
    // retour et recommencer
    // ----------------------------------
    bottom_buttons_layout = new QHBoxLayout;
    back_to_home_button = new QPushButton ("Retour", this);
    connect(back_to_home_button, SIGNAL(clicked()), this, SLOT(goBack()));
    bottom_buttons_layout->addWidget(back_to_home_button);

    bottom_buttons_layout->insertSpacing(1, screen_width / 3);

    reset_button = new QPushButton("Recommencer");
    connect(reset_button, SIGNAL(clicked()), this, SLOT(resetGame()));
    bottom_buttons_layout->addWidget(reset_button);


    // -------------------------------------
    // vertical layout that contains all the widgets
    // -------------------------------------
    v_layout= new QVBoxLayout;
    v_layout->addLayout(but_and_image_layout);
    v_layout->addLayout(bottom_buttons_layout);

    h_layout = new QHBoxLayout;
    h_layout->addLayout(v_layout);
    h_layout->addLayout(panel_layout);
    this->setLayout(h_layout);
}





// ------------------------------------
// --------------- METHODS --------------
// ------------------------------------


void Board::placePion(int id, int line, int col, bool selected, bool more_than_4)
{
    this->board[line][col] = id;
    if (selected)
    {
        this->array[line][col]->isSelected(true, false);
    } else if (more_than_4)
    {
        this->array[line][col]->isSelected(false, false);
        this->array[line][col]->setPlayer(id);
    } else {
        this->array[line][col]->setPlayer(id);
    }
}



// affiche les déplacements possible après qu'un joueur a sélectionné un pion
void Board::displayPossibleMoves(int line, int col)
{
    board_label->setEnabled(true);
    this->enableBoard();

    if (line - 1 >= 0 && col - 1 >= 0 )
    {
        if (board[line - 1][col - 1] == 0 )
        {
            array[line - 1][col - 1]->setEnabled(true);
            array[line - 1][col - 1]->setSelectable(true);
        }
    }
    if (line - 1 >= 0)
    {
        if (board[line - 1][col] == 0 )
        {
            array[line - 1][col]->setEnabled(true);
            array[line - 1][col]->setSelectable(true);
        }
    }
    if (line - 1 >= 0 && col + 1 <= 4)
    {
        if (board[line - 1][col + 1] == 0 )
        {
            array[line - 1][col + 1]->setEnabled(true);
            array[line - 1][col + 1]->setSelectable(true);
        }
    }
    if (col + 1 <= 4)
    {
        if (board[line][col + 1] == 0 )
        {
            array[line][col + 1]->setEnabled(true);
            array[line][col + 1]->setSelectable(true);
        }
    }
    if (line + 1 <= 4 && col + 1 <= 4 )
    {
        if (board[line + 1][col + 1] == 0 )
        {
            array[line + 1][col + 1]->setEnabled(true);
            array[line + 1][col + 1]->setSelectable(true);
        }
    }
    if (line + 1 <= 4)
    {
        if (board[line + 1][col] == 0 )
        {
            array[line + 1][col]->setEnabled(true);
            array[line + 1][col]->setSelectable(true);
        }
    }
    if (line + 1 <= 4 && col - 1 >= 0)
    {
        if (board[line + 1][col - 1] == 0 )
        {
            array[line + 1][col - 1]->setEnabled(true);
            array[line + 1][col - 1]->setSelectable(true);
        }
    }
    if (col - 1 >= 0)
    {
        if (board[line][col - 1] == 0 )
        {
            array[line][col - 1]->setEnabled(true);
            array[line][col - 1]->setSelectable(true);
        }
    }
}



void Board::unselectPawn(int index)
{
    int line = (int) index / 5;
    int col = index % 5;
    this->array[line][col]->isSelected(false, false);
}





// entoure en gras le joueur courrant
void Board::displayCurrentPlayer(int player)
{
    if (player == 1 )
    {
        this->player1_groupbox->setStyleSheet("QGroupBox { border-radius: 9px;padding-right: 24px;padding-left: 24px;border: 5px solid black;}");
        this->player2_groupbox->setStyleSheet("QGroupBox { border-radius: 9px;padding-right: 24px;padding-left: 24px;border: 1px solid gray;}");
    } else if (player == 2)
    {
        this->player2_groupbox->setStyleSheet("QGroupBox { border-radius: 9px;padding-right: 24px;padding-left: 24px;border: 5px solid black;}");
        this->player1_groupbox->setStyleSheet("QGroupBox { border-radius: 9px;padding-right: 24px;padding-left: 24px;border: 1px solid gray;}");
    }
}



// met le type du joueur (IA ou HUMAIN)
void Board::displayPlayers(QString player1, QString player2)
{
    this->player1_type_label->setText(player1);
    this->player2_type_label->setText(player2);
}



// affiche le vainqueur
void Board::announceWinner(int id, QString name)
{
    if (id == 1)
    {
        this->player1_groupbox->setStyleSheet("QGroupBox { border-radius: 9px;padding-right: 24px;padding-left: 24px;border: 5px solid white;}");
    } else {
        this->player2_groupbox->setStyleSheet("QGroupBox { border-radius: 9px;padding-right: 24px;padding-left: 24px;border: 5px solid white;}");
    }

    win_label->setText("Bravo " + name + " vous avez gagné !");
    win_label->setVisible(true);
}


void Board::displayWinLabel(QString name)
{
    win_label->setText("Bravo " + name + "vous avez gagné !");
    win_label->setVisible(true);
}






// bloque le plateau momentanément
void Board::setBoardLabelEnabled(bool b)
{
    this->board_label->setEnabled(b);
}



// si a joué moins de 4 pions il peut placer où il veut sauf là où il a joué et là où adversaire a joué
// sinon , il choisi un de ses pions et le place ailleurs sauf là où se trouve l'adversaire et doit être
// dans case adjacente
void Board::prepareBoardForCurrentPlayer(int id, int pion_played)
{
    board_label->setEnabled(true);

    // moins de 4 pions joués donc joueur place son jeton
    // toutes les cases sur lesquelles aucun jeton n'est placé sont valides
    if (pion_played < 4)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (board[i][j] != 0)
                {
                    array[i][j]->setEnabled(false);
                } else {
                    array[i][j]->setEnabled(true);
                }
            }
        }
    } else {
        // le joueur a déjà placé ses 4 pions
        // il doit d'abord choisir son pion à déplacer
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (board[i][j] != id)
                {
                    array[i][j]->setEnabled(false);
                } else {
                    array[i][j]->setEnabled(true);
                }
                if (board[i][j] == 0)
                {
                    if (array[i][j]->isSelectable()) array[i][j]->setSelectable(false);
                }
            }
        }
    }

}




void Board::enableBoard()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            array[i][j]->setEnabled(false);
        }
    }
}


void Board::initBoardVisible()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            array[i][j]->setVisible(true);
        }
    }
}


void Board::initBoardInvisible()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            array[i][j]->setVisible(false);
        }
    }
}



// réinitialise le board
void Board::reinit()
{
    win_label->setVisible(false);
    board_label->setEnabled(false);
    int index = 0;
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            board[i][j] = 0;
            array[i][j]->setSelectable(false);
            array[i][j]->isSelected(false, true);
            array[i][j]->setColor(0);
            array[i][j]->setPlayer(0);
            array[i][j]->setIndex(index);
            index++;
        }
    }
}






// ------------------------------------
// --------------- SLOTS --------------
// ------------------------------------
// le joueur a sélectionné un pion
void Board::tileChosen()
{
    board_label->setEnabled(false);
    QMutexLocker verrou(&mutex);

    QObject* obj = sender();
    Pawn* button = qobject_cast<Pawn*>(obj);
    int index = button->getIndex();

    emit playerPlayed(index);
}


// Retourner vers l'accueil
void Board::goBack()
{
    emit changeInterface("home");
}


void Board::resetGame()
{
  int response =  QMessageBox::question(this, "Recommencer la partie ?", "Etes-vous sûr de vouloir recommencer la partie à zéro ?", QMessageBox::Reset | QMessageBox::Cancel);
  if (response == QMessageBox::Cancel)
  {
  }
  else if (response == QMessageBox::Reset)
  {
    emit beginGame();
  }
}






// ------------------------------------
// ------------- GETTERS --------------
// ------------------------------------

// retourne la matrice de int représentant le board
pointer_to_arrays Board::getBoard()
{
    return this->board;
}


void Board::printBoard()
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

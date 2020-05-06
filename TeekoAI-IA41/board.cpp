#include "board.h"
#include <iostream>
#include "Router.h"

// dealer cas où joueur reclique sur pion pour annuler sélection


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

    connect(this,SIGNAL(playerPlayed(int)),  static_cast<Router*>(this->parent())->game,SLOT(playerPlayed(int)));
    // --------------------------------------
    // ------------- ATTRIBUTES -------------
    // --------------------------------------
/*
    a=0.2;
    b=0.1;
    target_number=10;
    target_size_max = 150;
    target_size_mini = 10;
    this->fitts_data = new FittsData() ;
    this->test_timer = new QElapsedTimer;
    // le premier clic n'est pas compté
    click_count = -1;
*/

    // ----------------------------------
    // Instructions
    // ----------------------------------
//    instructions_label = new QLabel;
//    instructions_label->setText("<font color=\"black\">Cliquez sur les cibles </font> <font color=\"red\">ROUGE</font><font color=\"black\"> !</font>");
//    instructions_label->setAlignment(Qt::AlignHCenter);
//    instructions_layout = new QVBoxLayout;
//    instructions_layout->addWidget(instructions_label);


    // ----------------------------------
    // Fenêtre de test
    // ----------------------------------
    // récupère la taille de l'écran de l'utilisateur pour adapter la fenêtre de test
    board_label = new QLabel(this);
    QRect window = QGuiApplication::screens().first()->geometry();
//    int screen_width = window.width();
    int screen_height = window.height();
    double board_size = screen_height * 3/4;
    board_label->setFixedSize(board_size, board_size);
    QPixmap board_image("./res/teeko_board_v.png");
    board_label->setPixmap(board_image);

    board_label->setScaledContents( true );

    but_layout = new QGridLayout;

    int index = 0;

    int y = board_label->height()/33;
    int x = board_label->height()/32.4;
    int height = board_label->height() / 8.1;

    for(int i = 0;i<5;i++){
        for(int j = 0;j<5;j++){
            Pawn *pawn = new Pawn("", board_label);
//            Pawn *pawn = new Pawn(QString::number(i)+ QString::number(j), board_label);
            pawn->setGeometry(x, y, height , height);
//            QPushButton *pushButton = new QPushButton(QString::number(i)+ QString::number(j));

            // Next line will be used to help find the Path later
            array[i][j] = pawn;
            pawn->setIndex(index);
            index++;
            // Adds pushButton to Grid
//            w->setLayout(ButtonLayout);
//            but_layout->addWidget(pawn,i,j);
//            but_layout->addWidget(pushButton,i,j,1,1);
            // Connects buttons to setStartEnd() function
            connect(pawn, SIGNAL(clicked()), this, SLOT(tileChosen()));
            x += board_label->height()/4.90;
        }
        x = board_label->height()/32.4;
        y += board_label->height()/4.89;

    }


    win_label = new QLabel;
    win_label->setVisible(false);

    but_and_image_layout = new QGridLayout;
    but_and_image_layout->addWidget(board_label,0,0);
    but_and_image_layout->addLayout(but_layout,0,0);
    but_and_image_layout->addWidget(win_label,0,0);

//    Pawn *test_pawn= new Pawn("TEST", board_label);
//    test_pawn->setPlayer(2);
////    ->setGeometry(x_coord, y_coord, button_width, button_height);
//    y = board_label->height()/33;
//    x = board_label->height()/32.4;
//    height = board_label->height() / 8.1;
//    test_pawn->setGeometry(x, y, height , height);

//    Pawn *test_pawn2= new Pawn("TEST", board_label);
//    test_pawn2->setPlayer(2);
////    ->setGeometry(x_coord, y_coord, button_width, button_height);
//    test_pawn2->setGeometry(x, y, height , height);


//    Pawn *test_pawn3= new Pawn("TEST", board_label);
//    test_pawn3->setPlayer(2);
////    ->setGeometry(x_coord, y_coord, button_width, button_height);
//    y += board_label->height()/4.89;
//    test_pawn3->setGeometry(x, y, height , height);


//    Pawn *test_pawn4= new Pawn("TEST", board_label);
//    test_pawn4->setPlayer(2);
////    ->setGeometry(x_coord, y_coord, button_width, button_height);
//    y += board_label->height()/4.89;
//    test_pawn4->setGeometry(x, y, height , height);



//    Pawn *test_pawn5= new Pawn("TEST", board_label);
//    test_pawn5->setPlayer(2);
////    ->setGeometry(x_coord, y_coord, button_width, button_height);
//    y += board_label->height()/4.89;
//    test_pawn5->setGeometry(x, y, height , height);


//        cout << "height " << board_label->height() << endl;
//        cout << "width " << board_label->width() << endl;

//    this->addWidget(test_pawn,0,0);

//    board_label->setPixmap(board_image.scaled(board_size,board_size,Qt::KeepAspectRatio));

//    board_label->setStyleSheet("background-color: rgb(170,189,206); border: 1px solid grey;");



    current_player_label = new QLabel;


    // ----------------------------------
    // Cible
    // ----------------------------------
/*
    // bouton cible
    click_me_button = new QPushButton("5", board_label);
    this->initTarget();
    connect(click_me_button, SIGNAL(clicked()), this, SLOT(recordData()));
    connect(click_me_button, SIGNAL(clicked()), this, SLOT(changeButtonPosition()));

    // label de fin de test
    test_finished_label = new QLabel("Test fini ! Recommencez ou allez voir les résultats.", board_label);
    test_finished_label->setFont(QFont("Roboto", 12, QFont::Bold, false));
    int label_width = 375;
    int label_height = 50;
    test_finished_label->setGeometry(((board_label->width()) / 2) - (label_width/ 2), ((board_label->height() / 2) - (label_height / 2)), label_width, label_height);
    test_finished_label->resize(test_finished_label->sizeHint().width(), test_finished_label->sizeHint().height());
    test_finished_label->setVisible(false);


    // décompte avant le départ
    countdown_timer = new QTimer(this);
    connect(countdown_timer, SIGNAL(timeout()), this, SLOT(updateCountdown()));

    // son du décompte
    beep_file = new QString("./res/beep.wav");
    beeeep_file = new QString("./res/beeeep.wav");
    beep_sound = new QSound(*beep_file, this);
    beeeep_sound = new QSound(*beeeep_file, this);
*/

    // ----------------------------------
    // back, reset and results
    // ----------------------------------
    bottom_buttons_layout = new QHBoxLayout;
    back_to_home_button = new QPushButton ("Retour", this);
    connect(back_to_home_button, SIGNAL(clicked()), this, SLOT(goBack()));
    bottom_buttons_layout->addWidget(back_to_home_button);
//    bottom_buttons_layout->insertSpacing(1, screen_width / 3);



/*
    // reset button in case the user wants to retry before the test ends
    reset_button = new QPushButton("Recommencer le test");
    connect(reset_button, SIGNAL(clicked()), this, SLOT(resetTest()));
    bottom_buttons_layout->addWidget(reset_button);
*/
    // bouton vers la page Résultats
//    results_button = new QPushButton("Résultats", this);
//    results_button->setVisible(true);
//    results_button->setEnabled(false);
//    connect(results_button, SIGNAL(clicked()), this, SLOT(goToResults()));
//    bottom_buttons_layout->addWidget(results_button);


    // -------------------------------------
    // vertical layout that contains all the widgets in the HomePage
    // -------------------------------------



    v_layout= new QVBoxLayout;
//    main_layout->addLayout(instructions_layout);
    v_layout->addLayout(but_and_image_layout);
    v_layout->addLayout(bottom_buttons_layout);

    h_layout = new QHBoxLayout;
    h_layout->addLayout(v_layout);
    h_layout->addWidget(current_player_label);
    this->setLayout(h_layout);
}



pointer_to_arrays Board::getBoard()
{
    return this->board;
}


void Board::displayWinLabel(QString name)
{
    win_label->setText("Bravo " + name + "vous avez gagné !");
    win_label->setVisible(true);
}

void Board::tileChosen()
{
//    bool has_lock = mutex.try_lock();
//    while (!has_lock)
//    {
//        sleepSimulator.wait(&mutex, 1000);

//    }
    board_label->setEnabled(false);
        //    QThread::sleep(1);
        //    mutex.lock();
        QMutexLocker verrou(&mutex);

        QObject* obj = sender();
        //    QPushButton* button = qobject_cast<QPushButton*>(obj);
        Pawn* button = qobject_cast<Pawn*>(obj);
        int index = button->getIndex();
        //    int index = but_layout->indexOf(button);

        cout<< "position " << index << endl;

        emit playerPlayed(index);

}

void Board::placePion(int id, int line, int col, bool selected, bool more_than_4)
{
                    cout<< "dans place pion"  << endl;
    this->board[line][col] = id;
    if (selected)
    {
                cout<< "1"  << endl;
        this->array[line][col]->isSelected(true);
    } else if (more_than_4)
    {
                        cout<< "2"  << endl;
        this->array[line][col]->isSelected(false);
        this->array[line][col]->setPlayer(id);
    } else {
        this->array[line][col]->setPlayer(id);
    }

}


void Board::unselectPawn(int index)
{
    int line = (int) index / 5;
    int col = index % 5;
    this->array[line][col]->isSelected(false);
}



// si a joué moins de 4 pions il peut placer où il veut sauf là où il a joué et là où adversaire a joué

// sinon , il choisi un de ses pions et le place ailleurs sauf là où se trouve l'adversaire et doit être
// dans case adjacente
void Board::prepareBoardForCurrentPlayer(int id, int pion_played)
{
    cout<< "dans PrepareBoardForCurrentPlayer" << endl;
    board_label->setEnabled(true);
//    this->initBoardVisible();

    // moins de 4 pions joués donc joueur place son jeton
    // toutes les cases sur lesquelles aucun jeton n'est placé sont valides
    if (pion_played < 4)
    {
            cout<< "da,ns pion played < 4" << endl;
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

//   for (int )
}


void Board::afficherDeplacementPossible(int line, int col)
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



// ------------------------------------
// --------------- SLOTS --------------
// ------------------------------------

// Déplace la cible quand on la clique
/*void Board::changeButtonPosition()
{
    // décompte du nombre de cible cliquées
    click_count++;

    // choisi la nouvelle position de façon aléatoire en fonction du temps
    QTime now = QTime::currentTime();
    qsrand(now.msec());

    // Generate random size
    int button_width = qrand()%300 + target_size_mini;
    while (button_width > target_size_max)
    {
        button_width = qrand()%300 + target_size_mini;
    }
    int button_height = button_width;

    // Get size of screen
    int window_width = board_label->size().width();
    int window_height = board_label->size().height();

    // Generate random position
    int x_coord = 0;
    int xTemp = (qrand()%window_width) - button_width;
    if(xTemp >= target_size_mini && xTemp < window_width - target_size_mini)
        x_coord = xTemp;

    int y_coord = 0;
    int yTemp = (qrand()%window_height) - button_height;
    if( yTemp >= target_size_mini && yTemp < window_height  - target_size_mini)
        y_coord = yTemp;

    click_me_button->setGeometry(x_coord, y_coord, button_width, button_height);

    // rend la cible plus ou moins arrondie
    QString str="border-radius: ";
    str += QString::number(rand()%(button_height/2));
    str += "px; background-color: rgb(217,72,72)";
    str+=";";
    click_me_button->setStyleSheet(str);

    // affiche sur le bouton le nombre de cibles restantes
    int remaining_target_number = target_number - click_count;
    click_me_button->setText(QString::number(remaining_target_number));
    click_me_button->setFont(QFont("Roboto", click_me_button->height() * 1/2));

    // avant le début du test
    if (click_count == 0)
    {
        if (beeeep_sound != NULL )
            beeeep_sound->stop();
        // chrono du test
        this->test_timer->start();
        this->fitts_data->setA(this->a);
        this->fitts_data->setB(this->b);
    }

    // test terminé
    if (click_count >= target_number) {
        this->testFinished();
    }
}

*/

/*
// envoi à FittsData les data concernant la dernière cible cliquée
void Board::recordData()
{
        QPoint current_pos = board_label->mapFromGlobal(QCursor::pos());
        if(click_count >= 0)
        {
            double time_elapsed = test_timer->restart();
            this->fitts_data->sendData(last_recorded_pos, QPoint(click_me_button->x(), click_me_button->y()), click_me_button->width(), time_elapsed, click_count);
        }
        last_recorded_pos.setX(current_pos.x());
        last_recorded_pos.setY(current_pos.y());
}
*/


void Board::announceCurrentPlayer(QString name)
{
    this->current_player_label->setText(name + "à toi de jouer !");
}


/*
// lance le countdown sur le bouton
void Board::startCountdown()
{
    click_me_button->setText("6");
    countdown_timer->start(1000);
    beep_sound->play();
}

*/

/*
// mise à jour du décompte
void Board::updateCountdown()
{
    QString sec = click_me_button->text();
    int countdown = sec.toInt();
    countdown--;
    if(countdown > 0)
    {
        click_me_button->setText(QString::number(countdown));
        beep_sound->play();
    } else if (countdown == 0) {
        click_me_button->setEnabled(true);
        click_me_button->setText("Click me !");
        click_me_button->setFont(QFont("Roboto", click_me_button->width() * 1 / 8));
        countdown_timer->stop();
        beeeep_sound->play();
    }
}



void Board::stopCountdown()
{
    countdown_timer->stop();
}
*/



// Retourner vers l'accueil
void Board::goBack()
{
//    countdown_timer->stop();

    // TODO demander confirmation
    emit changeInterface("home");
}


/*
// relance le test
void Board::resetTest()
{
    click_count = -1;
    // reset les data de FittsData
    this->fitts_data->resetData();

    results_button->setEnabled(false);

    if( beep_sound != NULL){
        beep_sound->stop();
    }

    if (beeeep_sound != NULL ){
        beeeep_sound->stop();
    }
    beep_sound->play();

    // réinitialise la cible
    this-> initTarget();

    countdown_timer->start(1000);
    test_finished_label->setVisible(false);
}




// Aller vers la page de résultats
void Board::goToResults()
{

    if( beep_sound != NULL){
        beep_sound->stop();
    }

    if (beeeep_sound != NULL ){
        beeeep_sound->stop();
    }
    countdown_timer->stop();
    emit changeInterface("results_page");
    static_cast<MainWindow*>(this->parent())->getResultsPage().displayResults();
    static_cast<MainWindow*>(this->parent())->getResultsPage().displayData();
}
*/





// ------------------------------------
// ------------- METHODES -------------
// ------------------------------------
/*
// Lancée lorsque le test est fini
void Board::testFinished()
{
    test_finished_label->setVisible(true);
    click_me_button->setVisible(false);
    results_button->setEnabled(true);
    // calcule des résultats
    this->fitts_data->computeTestResults();
}


// réinitialise l'apparence de la cible
void Board::initTarget()
{
    int click_me_button_width = board_label->size().width() / 10 ;
    if (click_me_button_width < 144 ){
        click_me_button_width = 144 ;
    }
    int click_me_button_height = click_me_button_width;
    click_me_button->setGeometry(((board_label->width()) / 2) - (click_me_button_width/ 2), ((board_label->height() / 2) - (click_me_button_height / 2)), click_me_button_width, click_me_button_height);
    click_me_button->setVisible(true);
    click_me_button->setEnabled(false);
    click_me_button->setText("6");
    click_me_button->setFont(QFont("Roboto", click_me_button->width() * 1 / 3, QFont::Bold, false));
    click_me_button->setStyleSheet("background-color: rgb(217,72,72); color: white;");

}
*/


// ------------------------------------
// ------------- GETTERS --------------
// ------------------------------------



// ------------------------------------
// ------------- SETTERS --------------
// ------------------------------------
/*
void Board::setA(double a)
{
    this->a = a;
}

void Board::setB(double b)
{
    this->b = b;
}

void Board::setTargetNumber(int n)
{
    this->target_number = n;
}

void Board::setTargetSizeMini(int m)
{
    this->target_size_mini = m;
}

void Board::setTargetSizeMax(int m)
{
    this->target_size_max = m;
}

FittsData& Board::getFittsData()
{
    return *fitts_data;
}
*/

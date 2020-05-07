#include "home.h"
#include "Router.h"

Home::Home(QWidget *parent, QString name):
    QWidget(parent)
{
    this->setObjectName(name);

    // méthode qui permet la transition entre les différentes pages de l'app
    connect(this, SIGNAL(changeInterface(QString)), this->parent(),SLOT(changeOnglet(QString)));

    // obtenir la taille de l'écran de l'utilisateur
    QRect window = QGuiApplication::screens().first()->geometry();
    int screen_width = window.width();
    int screen_height = window.height();

    int window_width = parent->width();
    int window_height = parent->height();


    // -------------------------------------
    // top layout, contient le titre de l'app
    // -------------------------------------
    title_label = new QLabel("Teeko");
    title_label->setFont(QFont("Roboto", 20, QFont::Bold, false));
    title_label->setAlignment(Qt::AlignCenter);
    title_layout = new QHBoxLayout;
    title_layout->addWidget(title_label);


    // -------------------------------------
    // Game configuration
    // -------------------------------------
    configuration_box = new QGroupBox(tr("Mode de jeu"), this);

    configuration_form = new QFormLayout;
//    configuration_form->setVerticalSpacing(15);
    configuration_form->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);

    // nombre de cibles


    button_ia_vs_ia = new QRadioButton(this);
    connect(button_ia_vs_ia, SIGNAL(clicked()), this, SLOT(enableDifficultyChoice()));
    button_human_vs_ia = new QRadioButton(this);
    button_human_vs_ia->setChecked(true);
    connect(button_human_vs_ia, SIGNAL(clicked()), this, SLOT(enableDifficultyChoice()));
    button_human_vs_human = new QRadioButton(this);
    connect(button_human_vs_human, SIGNAL(clicked()), this, SLOT(disableDifficultyChoice()));

    configuration_form->addRow("IA vs IA\t\t", button_ia_vs_ia);
    configuration_form->addRow("Humain vs IA\t\t", button_human_vs_ia);
    configuration_form->addRow("Humain vs Humain\t\t", button_human_vs_human);

    configuration_box->setLayout(configuration_form);
    configuration_box->setMaximumSize(QSize((int) window_width , (int) window_height * 0.33));


    // -------------------------------------
    // difficulty box
    // -------------------------------------
    difficulty_box = new QGroupBox(tr("Force de l'IA"), this);

    // formulaire de configuration du test
    difficulty_form = new QFormLayout;
//    configuration_form->setVerticalSpacing(15);
    difficulty_form->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);

    // nombre de cibles


    button_easy = new QRadioButton(this);
    button_medium = new QRadioButton(this);
    button_medium ->setChecked(true);
    button_hard = new QRadioButton(this);

    difficulty_form->addRow("Facile\t\t", button_easy);
    difficulty_form->addRow("Moyen\t\t", button_medium);
    difficulty_form->addRow("Difficile\t\t", button_hard);
//    connect(target_number_spinbox, SIGNAL(valueChanged(int)), this, SLOT(setTargetNumber(int)));

    difficulty_box->setLayout(difficulty_form);
    difficulty_box->setMaximumSize(QSize((int) window_width , (int) window_height * 0.33));


    // -------------------------------------
    // layout qui contient les deux box
    // -------------------------------------
    params_layout = new QVBoxLayout;
    params_layout->addWidget(configuration_box);
    params_layout->insertSpacing(1, screen_height * 1/7);
    params_layout->addWidget(difficulty_box);
    params_layout->setAlignment(Qt::AlignHCenter);

    // -------------------------------------
    // quit / start buttons
    // -------------------------------------
    buttons_layout = new QHBoxLayout;

    quit_button= new QPushButton("Quitter");
    connect(quit_button, SIGNAL(clicked()), qApp, SLOT(quit()));
    buttons_layout->addWidget(quit_button);

    buttons_layout->insertSpacing(1, screen_width / 4);

    restart_button= new QPushButton("Recommencer");
    restart_button->setVisible(false);
    connect(restart_button, SIGNAL(clicked()), this->parent(), SLOT(restartGame()));
    buttons_layout->addWidget(restart_button);

    start_button= new QPushButton("Démarrer le jeu");
    connect(start_button, SIGNAL(clicked()), this, SLOT(launch_game()));
    buttons_layout->addWidget(start_button);

    // -------------------------------------
    // vertical layout that contains all the widgets in the Home
    // -------------------------------------
    vertical_layout = new QVBoxLayout();
    vertical_layout->addLayout(title_layout);
//    vertical_layout->insertSpacing(1, screen_height * 1/7);
    vertical_layout->addLayout(params_layout);
    vertical_layout->insertSpacing(3, screen_height * 1/7);
    vertical_layout->addLayout(buttons_layout);

    this->setLayout(vertical_layout);
}



// envoie l'utilisateur sur la page de test
// en passant à FittsTestWindow les param du test
void Home::launch_game()
{
    emit changeInterface("board");
    this->start_button->setText("Continuer");
    this->restart_button->setVisible(true);
}


void Home::enableDifficultyChoice()
{
//    std::cout << "test : " << b <<std::endl;
    this->button_easy->setEnabled(true);
    this->button_medium->setEnabled(true);
    this->button_hard->setEnabled(true);
}

void Home::disableDifficultyChoice()
{
//    std::cout << "test : " << b <<std::endl;
    this->button_easy->setEnabled(false);
    this->button_medium->setEnabled(false);
    this->button_hard->setEnabled(false);
}


bool Home::isIAVsIA()
{
    return this->button_ia_vs_ia->isChecked();
}


bool Home::isHumanVsIA()
{
    return this->button_human_vs_ia->isChecked();
}


bool Home::isHumanVsHuman()
{
    return this->button_human_vs_human->isChecked();
}


Home::~Home()
{
}


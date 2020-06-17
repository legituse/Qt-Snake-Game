#include "menu.h"




Menu::Menu(QMainWindow* parent)
    : QMainWindow(parent) {

    
    MenuFrame = new QFrame();

    startButton = new QPushButton("Start", MenuFrame);
    exitButton = new QPushButton("Exit", MenuFrame);
    scoreButton = new QPushButton("Show Score", MenuFrame);

    mainvbox = new QVBoxLayout(MenuFrame);

    mainhbox = new QHBoxLayout(MenuFrame);

    mainhbox->addWidget(scoreButton);
    mainhbox->addWidget(exitButton);

    mainvbox->addItem(mainhbox);
    mainvbox->addWidget(startButton);
    // creating the main menu frame with its respective buttons and layouts


    game = new Game(this);

    // creating the game object


    ScoreFrame = new QFrame();

    menuButton = new QPushButton("Show Menu", ScoreFrame);

    
    CurrentScore = new QLabel(CurrentScoreText.arg(scoreholder), ScoreFrame);
    CurrentScore->setFont(QFont("Sans", 25));
    CurrentScore->setAlignment(Qt::AlignVCenter);

    
    HighScore = new QLabel(HighScoreText.arg(scoreholder), ScoreFrame);
    HighScore->setFont(QFont("Sans", 25));
    HighScore->setAlignment(Qt::AlignVCenter);

    scores = new QVBoxLayout(ScoreFrame);
    scores->addWidget(CurrentScore);
    scores->addWidget(HighScore);
    scores->addWidget(menuButton);
    // creating the score frame which contains current and high scores and it's buttons and layouts



    stack = new QStackedWidget(this);


    stack->addWidget(MenuFrame);
    stack->addWidget(game);
    stack->addWidget(ScoreFrame);

    stack->setCurrentIndex(0);
    setCentralWidget(stack);
    // creating a stacked widget to place all frames into


    connect(startButton, &QPushButton::clicked, this , &Menu::changeWindow);
    //connecting start button to change window to the game widget
    connect(exitButton, &QPushButton::clicked, qApp, QApplication::exit);
    //connect exit button to exit the application
    connect(scoreButton, &QPushButton::clicked, this, &Menu::ViewScore);
    //connecting the score button in the menu to show the scores 
    connect(menuButton, &QPushButton::clicked, this, &Menu::changeWindow);
    //connecting the menu button in the scores frame to go back to the menu
    connect(game, SIGNAL(WindowChangeSignal()), this, SLOT(WindowChangeSlot()));
    // creating a signal and a slot from the game object to windowchangeslot which allows for changing of frames when game is over or ended
}


void Menu::changeWindow() {
    if (stack->currentIndex()==0) {// if menu is shown currently then show game on function call
        stack->setCurrentIndex(1);
    }
    else if (stack->currentIndex()==1) { // if game is shown currently then show score on function call
        stack->setCurrentIndex(2);
    }
    else if (stack->currentIndex() == 2) {// if score is shown currently then show menu on function call
        stack->setCurrentIndex(0);
    }
}

void Menu::ViewScore() { // show score from menu
    stack->setCurrentIndex(2);
}




void Menu::WindowChangeSlot() { // slot function triggered when the game has ended or is closed by the user
    if (game->GetScore() > scoreholder) { // calculating high scores and current scores
        CurrentScore->setText(CurrentScoreText.arg(game->GetScore()));
        HighScore->setText(HighScoreText.arg(game->GetScore()));
    }
    else {
        CurrentScore->setText(CurrentScoreText.arg(game->GetScore()));
    }
    scoreholder = game->GetScore(); // updating the current score variable
    changeWindow(); // changing the window from game to scores
    
}
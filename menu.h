#pragma once
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QLabel>
#include "game.h"



class Menu : public QMainWindow{

    Q_OBJECT

public:
    Menu(QMainWindow * parent = 0);
    

private:
    QPushButton* startButton;
    QPushButton* exitButton;
    QPushButton* scoreButton;
    QPushButton* menuButton;
    //push buttons for starting, exiting, going to the score frame and menu frame
    QLabel* CurrentScore; // label to display current score
    QLabel* HighScore; // label to display high score
    void changeWindow(); // function to change the window with button presses
    void ViewScore(); // function to view the score frame from the menu
    Game* game; // object game which holds the QWidget for the snakes game
    QFrame* MenuFrame; // a frame to hold the menu
    QFrame* ScoreFrame; // a frame to hold the scores and display the values
    QStackedWidget* stack; // a stacked wiget used to cycle between menu, game and the score frames/widgets
    QVBoxLayout* mainvbox; // a VBoxlayout used in the menu frame
    QHBoxLayout* mainhbox; // a HBoxlayout used in the menu frame
    QVBoxLayout* scores;  // a HBoxlayout used in the scores frame
    QString CurrentScoreText = "Current Score: %1"; // Qstring to hold the message for the current score
    QString HighScoreText = "High Score: %1"; // Qstring to hold the message for the high score
    int scoreholder = 0;

    public slots:
        void WindowChangeSlot();  // slot used and called when game ends or is exited

};
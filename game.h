#pragma once
#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <deque>
#include "coordinates.h"


class Game : public QWidget{

    Q_OBJECT

public:
    Game(QWidget* parent = 0);
    int GetScore(); // function to return score 

private:
    QTimer* timer; // timer for repainting the graphics
    int currX; // stores current x position of snake head
    int currY; // stores current y position of snake head
    int snakesize; // stores size of snake in pixels
    int speed; // stores speed of snake in pixels
    int accelx; // stores acceleration/direction the snake moves in the 2d grid in the X direction
    int accely; // stores acceleration/direction the snake moves in the 2d grid in the Y direction
    std::deque<coordinates> coords; // deque to hold coordinates of the snake's body, its size used to represent the snake length
    int fruitx; // stores current x position of the fruit 
    int fruity; // stores current y position of the fruit 
    bool checkcollision(); // used to check if snake collides with its body
    void EndGame(); // used when game is exited or game over has occured
    void delay(int); // a delay called when the game ends
    QMap<int, bool> keys; // holds which key is being pressed
    void checkKeyPress(); // changes the accelx/y values when keys are pressed to indicate movement
    int SCORE; // int to hold the score. aka the size of the snake
    



signals:
    void WindowChangeSignal(); // signal to trigger when game ends to change frames to score frame

protected:
    void paintEvent(QPaintEvent* e);//paint event called on every repaint and update. 
    void drawWidget(QPainter& qp);

    void keyPressEvent(QKeyEvent* e) // key event to record when keys are pressed, and sets the key pressed to true in the QMap
    {
        keys[e->key()] = true; QWidget::keyPressEvent(e);
    }

    void keyReleaseEvent(QKeyEvent* e) // key event to see when keys are released thus they are set to false in the QMap
    {
        keys[e->key()] = false; QWidget::keyReleaseEvent(e);
    }

};
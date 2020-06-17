#include "game.h"
#include <QApplication>
#include <cstdlib>
#include <QTime>





Game::Game(QWidget* parent)
	: QWidget(parent) {
	currX = 500;
	currY = 400;
	// setting base starting position derived from default app size in main

	timer = new QTimer(this); 
	// a new timer to repaint the graphics

	fruitx = 200;
	fruity = 300;
	// sets a starting default fruit position of the snake

	coords.push_back(coordinates(500, 400));
	coords.push_back(coordinates(480, 400));
	coords.push_back(coordinates(460, 400));
	//setting default length of snake body and position of 3

	snakesize = 20;
	//setting snake size of 20 pixels

	speed = 20;
	//setting speed of snake to 20 pixels

	accelx = speed;
	accely = 0;
	//setting default acceleration of the snake moving in the positive x direction


	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	//connecting the timer to rerender and repaint the game

	timer->start(75);
	//timer starts and triggeres updates every 75ms
}



void Game::paintEvent(QPaintEvent* e) { // called when timer runs out every 75ms



	checkKeyPress();// checks to see which keys are pressed for snake movements

	QPainter Background(this);
	QColor black(0, 0, 0);
	Background.setPen(black);
	Background.setBrush(black);
	Background.drawRect(0, 0, width(), height());
	// creating a black background


	


	QPainter qp(this);// creats a qpainter 

	
	currX += accelx;
	currY += accely;
	coords.push_front(coordinates(currX, currY));
	//updates current position of the snake and stores it in the Deque of all positions of the snake body

	if (currX > width() - snakesize) {
		currX = snakesize;
	}
	if (currX < 0) {
		currX = width() - snakesize;
	}
	if (currY > height() - snakesize) {
		currY = snakesize;
	}
	if (currY < 0) {
		currY = height() - snakesize;
	}
	//checks if snake goes out of the screen and makes it reappear on the other side of screen

	if (currX == fruitx && currY == fruity) {
		coords.push_back(coordinates(currX, currY));
		srand(time(0));
		fruitx = (rand() % ((width() - 20) / 20)) * 20;
		fruity = (rand() % ((height() - 20) / 20)) * 20;
		// sets the fruit coords to a new random position on the screen using rand() and the current time as a seed
	}
	// checks if snake goes over a fruit square and increases its body length by one by adding another set of coordinates to the coords deque
	
	
	drawWidget(qp);
	// calling the draw widget event, draws the snake and fruit


	QWidget::paintEvent(e);

}

void Game::drawWidget(QPainter& qp) { // paints the fruit and the snake body
	QColor red(255, 0, 0);
	qp.setPen(red);
	qp.setBrush(red);
	qp.drawRect(fruitx, fruity, snakesize, snakesize);
	//draws the fruit in red color

	QColor green(0, 255, 127);
	qp.setPen(green);
	qp.setBrush(green);
	// sets painter to green color for snake body

	coords.pop_back();
	//removes the last snake body coords, 
	//this essentially creates movement as a new snake body coords are created and destroy every timer occurance

	for (coordinates coord : coords) { // draws the whole snake
		qp.drawRect(coord.x, coord.y, snakesize, snakesize);
	}

	if (checkcollision()) { // checks collision to see if snake runs into himself
		EndGame(); // calls endgame function when snake head collides with one of its body coords
	}
	

}





	

void Game::checkKeyPress() { // converts wasd and arrow key presses to snake movements. and Escape key to exit the game
	if ((keys[Qt::Key_W] || keys[Qt::Key_Up]) && (accely != speed)) { // Keys W and Up arrow makes the snake move up
		accelx = 0;
		accely = -speed;
	}
	else if ((keys[Qt::Key_A] || keys[Qt::Key_Left]) && (accelx != speed)) { // Keys A and Left arrow makes the snake move left
		accelx = -speed;
		accely = 0;
	}
	else if ((keys[Qt::Key_S] || keys[Qt::Key_Down]) && (accely != -speed)) { // Keys S and Down arrow makes the snake move down
		accelx = 0;
		accely = speed;
	}
	else if ((keys[Qt::Key_D] || keys[Qt::Key_Right]) && (accelx != -speed)) { // Keys D and Right arrow makes the snake move right
		accelx = speed;
		accely = 0;
	}
	else if (keys[Qt::Key_Escape]) { // Keys Escape, ends the game
		keys[Qt::Key_Escape] = false;
		EndGame(); // calls the endgame function which endsthe game
	}


}

bool Game::checkcollision() { // compares current position of the snake with it's body position 
	for (int c = 2; c < coords.size(); c++) {
		if (currX == coords[c].x && currY == coords[c].y) {
			return true;
		}
	}
	return false;
	// returns true when collision occurs, false otherwise
}

void Game::delay(int millisecondsToWait) // delay function to induce a delay when game ends
{
	QTime dieTime = QTime::currentTime().addMSecs(millisecondsToWait);
	while (QTime::currentTime() < dieTime)
	{
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
	}
}


void Game::EndGame() { // the End function which is called everytime the snake collides or the user exits
	SCORE = coords.size() - 3; // sets the score to the size of the coords array minus 3, because 3 is the default size of the snake
	coords.clear(); // clear the coords of the snake body
	coords.push_back(coordinates(480, 400));
	coords.push_back(coordinates(460, 400));
	coords.push_back(coordinates(440, 400));
	currX = 500;
	currY = 400;
	accelx = speed;
	accely = 0;
	// resets the snake defaults to the same one as the constructor function

	delay(2000);
	// delays the program for 2 seconds to indicate that the game is over

	emit WindowChangeSignal();
	// emits windowchangesignal which changes the screen to the Scores frame


}

int Game::GetScore() { // returns the score of the game
	return SCORE;
}



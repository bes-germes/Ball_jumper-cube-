#include <QPainter>
#include <QTime>
#include <QTextStream>
#include "ball.h"

Ball::Ball(QWidget *parent) : QWidget(parent) {

    setStyleSheet("background-color:white;");
    inGame = true;

    resize(B_WIDTH, B_HEIGHT);
    loadImages();
    initGame();
}

void Ball::loadImages() {

    head.load("C:\\Users\\Oleg\\Pictures\\Saved Pictures\\head.png");
    field.load("C:\\Users\\Oleg\\Pictures\\Saved Pictures\\field.png");
    bad_pixel.load("C:\\Users\\Oleg\\Pictures\\Saved Pictures\\dot.png");
}


void Ball::initGame() {

    x = 800;
    y = 500;
    groundPixel = 500;
    maxRight = 1400;
    timerId = startTimer(DELAY);
}

void Ball::locateBadPixel(){

}

void Ball::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);

    doDrawing();
}

void Ball::doDrawing() {

    QPainter qp(this);

    if (inGame) {

        qp.drawImage(0, 0, field);
        qp.drawImage(x, y, head);


    } else {


    }
}

void Ball::keyPressEvent(QKeyEvent *e) {

    int key = e->key();

    if (key == Qt::Key_Right) {

        rightDirection = true;
        leftDirection = false;

    }

    if (key == Qt::Key_Left) {

        rightDirection = false;
        leftDirection = true;

    }

    if (key == Qt::Key_Up && booljump != true && boolDontReapeatJump != true) {

        booljump = true;
        boolDontReapeatJump = true;
    }

    QWidget::keyPressEvent(e);
}

void Ball::keyReleaseEvent(QKeyEvent *e) {

        switch (e->key()) {
            case Qt::Key_Left:
                leftDirection = false;
                break;

            case Qt::Key_Right:
                rightDirection = false;
                break;
        }

}

void Ball::jump(){

    if (booljump && y > groundPixel - 40){

        y -= 10;

    }else{
        booljump = false;
        down();
    }

}

void Ball::down(){

    if(!booljump && y < groundPixel){
        y += 10;
    }else{
        boolDontReapeatJump = false;
    }
}

void Ball::move(){

    if (rightDirection && x <= maxRight){
        x += DOT_SIZE;
    }

    if (leftDirection){
        x -= DOT_SIZE;
    }
}

void Ball::moveObject(){


}

void Ball::checkCollision(){
    if(x <= 1400){
        groundPixel = 500;
    }
    if(x > 1400 && x <= 1430){
        groundPixel = 480;
    }
    if(x > 1430 && x <= 1455){
        groundPixel = 460;
    }
    if(x > 1455 && x <= 1490){
        groundPixel = 440;
    }
    if(x > 1490 && x <= 1705){
        groundPixel = 420;
    }
    if(x > 1705 && x <= 1880){
        groundPixel = 400;
    }
    if (groundPixel == 500 && (y > 480 && y <= 505)){
         maxRight = 1400;
    }
    if (groundPixel == 480 && (y > 460 && y <= 480)){
        maxRight = 1430;
    }
    if (groundPixel == 460 && (y > 440 && y <= 460)){
        maxRight = 1455;
    }
    if (groundPixel == 440 && (y > 420 && y <= 440)){
        maxRight = 1490;
    }
    if (groundPixel == 420 && (y > 400 && y <= 420)){
        maxRight = 1705;
    }
    if (groundPixel == 400 && (y > 380 && y <= 400)){
        maxRight = 1880;
    }
}

void Ball::terminalOut() {

  QTextStream out(stdout);
  out << "Ground pixel = " << groundPixel << endl;
  out << "x = " << x << endl;
  out << "y = " << y << endl;
}

void Ball::timerEvent(QTimerEvent *e) {

    Q_UNUSED(e);

    if (inGame) {
       checkCollision();
       move();
       jump();
       terminalOut();

    }
    repaint();
}

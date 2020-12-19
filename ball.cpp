#include <QPainter>
#include <QTime>
#include <QTextStream>
#include <typeinfo>
#include <string>

#include "ball.h"

Ball::Ball(QWidget *parent) : QWidget(parent) {

    setStyleSheet("background-color:white;");
    inGame = true;

    resize(B_WIDTH, B_HEIGHT);
    loadImages();
    initGame();
}

void Ball::loadImages() {
    spike.load(":/pictures/spike.png");
    head.load(":/pictures/head.png");
    field.load(":/pictures/field.png");
    bad_pixel.load(":/pictures/block1.png");
    block.load(":/pictures/apple.png");
    white_screen.load(":/pictures/white_screen.png");
    field_1.load(":/pictures/field_1.png");
    field_2.load(":/pictures/field_2.png");
}


void Ball::initGame() {
    gameOverBool = 0;
    NumberOfLevel = 0;


    x = 20;
    y = 500;



    groundPixel = 500;
    //levelOfHight[0] = 500;
    prev_groundPixel= 300;
    maxRight = 1920;
    maxLeft = 0;
    booljump = false;
    boolDown = false;
    boolDontReapeatJump = false;
    rightDirection = false;
    leftDirection = false;

    timerId = startTimer(DELAY);
}


void Ball::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);

    doDrawing();
}


void Ball::doDrawing() {

    QPainter qp(this);

    switch (NumberOfLevel){
        case 0:
            qp.drawImage(0, 0, field);


        break;

        case 1:
            qp.drawImage(0, 0, field_1);

        break;
        case 2:
            qp.drawImage(0, 0, field_2);

        break;
    }

    if (inGame) {

        qp.drawImage(x, y, head);
        if (NumberOfLevel == 3){
            qp.drawImage(0, 0, white_screen);
            finishGame(&qp, "You have won","(press escape to restart)");
        }
    } else {
        if (NumberOfLevel == 3){
            qp.drawImage(0, 0, white_screen);
            finishGame(&qp, "You have won","Thank you for playing in beta test");
        }else{
            qp.drawImage(0, 0, white_screen);
            finishGame(&qp, "Game lost","(press escape to restart)");
        }
    }

}

void Ball::finishGame(QPainter *painter, QString message,QString message2) {

  QFont font("Courier", 15, QFont::DemiBold);
  QFontMetrics fm(font);
  int textWidth = fm.horizontalAdvance(message);
  int textWidth2 = fm.horizontalAdvance(message2);

  painter->setFont(font);
  int h = height();
  int w = width();

  painter->translate(QPoint(w/2, h/2));
  painter->drawText(-textWidth/2, -10, message);
  painter->drawText(-textWidth2/2, 10, message2);
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

    if ((key == Qt::Key_Up || key == Qt::Key_Space) && booljump != true &&  boolDontReapeatJump != true )  {

        groundPixel = y + 10;
        booljump = true;
        //boolDontReapeatJump = true;
    }

    if (key == Qt::Key_Escape){
        x = 0;
        y = 500;
        NumberOfLevel = 0;
        inGame = true;
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

    if (groundPixel - 60 < y && booljump){
        y -= 10;
    }
    if(groundPixel - 60 >= y && booljump){
        boolDown = true;
        booljump = false;
    }

}

void Ball::down(){
    switch (NumberOfLevel) {
        case 0:
            block_down_blue = field.pixel( x, y + 10);
        break;
        case 1:
            block_down_blue = field_1.pixel( x, y + 10);
        break;
    }
    QColor clrCurrent_Down_blue(block_down_blue);
        if (clrCurrent_Down_blue.name() == "#99d9ea"){
            y += 5;
            boolDontReapeatJump = true;
        }else{
           boolDontReapeatJump = false;
        }
}

void Ball::moveObject(){
    for(int i = 425; i < 1340; ++i){
        badBlock_x = i;
    }
    for(int i = 1340; i > 425; --i){
        badBlock_x = i;
    }

}

void Ball::move(){

    if (rightDirection && x <= maxRight){
        x += 5;
    }

    if (leftDirection && x >= maxLeft){
        x -= 5;
    }
}

void Ball::updateLevel(){
    switch (NumberOfLevel) {
        case 0:
            if (x >= 1905){
                NumberOfLevel = 1;
                x = 20;
                y = 400;
            }
        break;
        case 1:
        if (x >= 1905){
            NumberOfLevel = 2;
            x = 20;
            y = 700;
            badBlock_y = 570;
        }
        break;
        case 2:
        if (x >= 1905){
            NumberOfLevel = 3;
            x = 20;
            y = 600;
            inGame = false;
        }
        break;
        }
}

void Ball::checkCollision(){
    switch (NumberOfLevel) {
        case 0:
            block_down_blue = field.pixel( x, y + 10);
            block_down_green = field.pixel( x, y + 9);
            block_right = field.pixel( x + 10, y);
            block_left = field.pixel( x, y);
            spike_down = field.pixel( x, y + 10);
            spike_left = field.pixel( x - 1, y);
            spike_right = field.pixel( x + 3, y);
        break;
        case 1:
            block_down_blue = field_1.pixel( x, y + 10);
            block_down_green = field_1.pixel( x, y + 9);
            block_right = field_1.pixel( x + 10, y);
            block_left = field_1.pixel( x, y);
            spike_down = field_1.pixel( x, y + 10);
            spike_left = field_1.pixel( x - 1, y);
            spike_right = field_1.pixel( x + 3, y);
        break;
        case 2:
            block_down_blue = field_2.pixel( x, y + 10);
            block_down_green = field_2.pixel( x, y + 9);
            block_right = field_2.pixel( x + 10, y);
            block_left = field_2.pixel( x, y);
            spike_down = field_2.pixel( x, y + 10);
            spike_left = field_2.pixel( x - 1, y);
            spike_right = field_2.pixel( x + 3, y);
        break;
    }

    QColor clrCurrent_Down_green(block_down_green);
    QColor clrCurrent_Right(block_right);
    QColor clrCurrent_Left(block_left);
    QColor clrCurrent_Down_blue( block_down_blue);
    QColor clrCurrent_spike_down(spike_down);
    QColor clrCurrent_spike_left(spike_left);
    QColor clrCurrent_spike_right(spike_right);

    if (clrCurrent_Down_green.name() == "#22b14c" && !booljump){
        y -= 10;
//        prev_groundPixel = y + 10;
//        groundPixel = y + 10;
    }

    if (!booljump && boolDown){

    }
    if (clrCurrent_Right.name() == "#22b14c"){
        x -= 5;
    }
    if (clrCurrent_Left.name() == "#22b14c"){
        x += 5;
    }
    if (clrCurrent_spike_down.name() == "#f46200" || clrCurrent_spike_left.name() == "#f46200" || clrCurrent_spike_right.name() == "#f46200"){
        inGame = false;
    }


}

void Ball::terminalOut() {
//    QColor clrCurrent_Down( field_1.pixel( x, y + 10));
//    QColor clrCurrent_Right( field_1.pixel( x + 10, y));
//    QColor clrCurrent_Left( field_1.pixel( x - 10, y));
//    QColor clrCurrent_spike( field_1.pixel( x, y + 10));


  QTextStream out(stdout);
  out << "x = " << x << endl;
  out << "y = " << y << endl;
  out << "numberOfLevel = " << NumberOfLevel << endl;
  out << "Down = " << inGame << endl;
  out << "Down = " << boolDontReapeatJump << endl;
  out << "MaxRight = " << prev_groundPixel << endl;

}





void Ball::timerEvent(QTimerEvent *e) {
    //QPainter hi(this);
    Q_UNUSED(e);

    if (inGame) {
       jump();
       down();
       updateLevel();
//       moveObject();
       checkCollision();
       move();
       terminalOut();

    }else{

    }
    repaint();
}



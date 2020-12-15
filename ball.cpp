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
    spike.load("C:\\Users\\Oleg\\Pictures\\Saved Pictures\\spike.png");
    head.load("C:\\Users\\Oleg\\Pictures\\Saved Pictures\\head.png");
    field.load("C:\\Users\\Oleg\\Pictures\\Saved Pictures\\field.png");
    bad_pixel.load("C:\\Users\\Oleg\\Pictures\\Saved Pictures\\dot.png");
    block.load("C:\\Users\\Oleg\\Pictures\\Saved Pictures\\apple.png");
    white_screen.load("C:\\Users\\Oleg\\Pictures\\Saved Pictures\\white_screen.png");
    field_1.load("C:\\Users\\Oleg\\Pictures\\Saved Pictures\\field_1.png");
}


void Ball::initGame() {
    gameOverBool = 0;
    NumberOfLevel = 0;

    dots = 2;
    x = 1920;
    y = 500;


    groundPixel = 500;
    //levelOfHight[0] = 500;
    prev_groundPixel= 500;
    maxRight = 1920;
    maxLeft = 0;
    booljump = false;
    boolDontReapeatJump = false;

    timerId = startTimer(DELAY);
}

bool Ball::checkBoolArray(){
    for (int i = 0; i < 114; ++i){
        if (test[i] != true){
            return false;
        }else{

        }
    }
    return true;
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

            for (int i = 0; i < 71; ++i) {
                block_x[i] = 0 + i * 20;
                block_y[i] = 510;
                //levelOfHight[1] = 490;
                qp.drawImage(block_x[i], block_y[i], block);
            }
            for (int i = 71; i < 74; ++i){
                block_x[i] = 1400 + (i - 71) * 20;
                block_y[i] = 490;
                //levelOfHight[1] = 490;
                qp.drawImage(block_x[i], block_y[i], block);
            }

            for (int i = 74; i < 77; ++i){
                block_x[i] = 1440 + (i - 74) * 20;
                block_y[i] = 470;
                //levelOfHight[2] = 470;
                qp.drawImage(block_x[i], block_y[i], block);
            }
            for (int i = 77; i < 80; ++i){
                block_x[i] = 1460 + (i - 77) * 20;
                block_y[i] = 450;
                //levelOfHight[2] = 470;
                qp.drawImage(block_x[i], block_y[i], block);
            }
            for (int i = 80; i < 92; ++i){
                block_x[i] = 1500 + (i - 80) * 20;
                block_y[i] = 430;
                //levelOfHight[2] = 470;
                qp.drawImage(block_x[i], block_y[i], block);
            }
            for (int i = 92; i < 103; ++i){
                block_x[i] = 1700 + (i - 92) * 20;
                block_y[i] = 410;
                //levelOfHight[2] = 470;
                qp.drawImage(block_x[i], block_y[i], block);
            }
            for (int i = 103; i < 104; ++i){
                block_x[i] = 1900 + (i - 103) * 20;
                block_y[i] = 390;
                //levelOfHight[2] = 470;
                qp.drawImage(block_x[i], block_y[i], block);
            }
            for (int i = 104; i < 107; ++i){
                block_x[i] = 120 + (i - 104) * 20;
                block_y[i] = 490;
                //levelOfHight[2] = 470;
                qp.drawImage(block_x[i], block_y[i], block);
            }
            for (int i = 107; i < 109; ++i){
                block_x[i] = 140 + (i - 107) * 20;
                block_y[i] = 470;
                //levelOfHight[2] = 470;
                qp.drawImage(block_x[i], block_y[i], block);
            }
            for (int i = 109; i < 112; ++i){
                block_x[i] = 220 + (i - 109) * 20;
                block_y[i] = 490;
                //levelOfHight[2] = 470;
                qp.drawImage(block_x[i], block_y[i], block);
            }
            for (int i = 112; i < 114; ++i){
                block_x[i] = 220 + (i - 112) * 20;
                block_y[i] = 470;
                //levelOfHight[2] = 470;
                qp.drawImage(block_x[i], block_y[i], block);
            }
            for (int i = 0; i < 2; ++i){
                spike_x[i] = 180 + i * 20;
                spike_y[i] = 500;
                qp.drawImage(spike_x[i], spike_y[i], spike);
            }

        break;

        case 1:
            qp.drawImage(0, 0, field_1);


            for (int i = 0; i < 114; ++i) {
                block_x[i] = 0 + i * 20;
                block_y[i] = 390;
                //levelOfHight[1] = 490;
                qp.drawImage(block_x[i], block_y[i], block);
            }

        break;
    }

    if (inGame) {

        qp.drawImage(x, y, head);

    } else {
        qp.drawImage(0, 0, white_screen);
        if (NumberOfLevel == 1){
            finishGame(&qp, "You have won","(press escape to restart)");
        }else{
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

    if ((key == Qt::Key_Up || key == Qt::Key_Space) && booljump != true && boolDontReapeatJump != true) {

        booljump = true;
        boolDontReapeatJump = true;
    }

    if (key == Qt::Key_Escape){
        x = 0;
        y = 500;
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

    if (booljump && y > groundPixel - 50){

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
        x += 5;
    }

    if (leftDirection && x >= maxLeft){
        x -= 5;
    }
}

void Ball::updateLevel(){
    NumberOfLevel = 1;
    x = 0;
    y = 350;
}

void Ball::checkCollision(){

    for (int i = 0; i < 114; ++i) {


            if(x >= block_x[i] - 15 && x <= block_x[i] + 25){

                if(x <= block_x[i] ){

                maxRight = block_x[i] - 15;

                if (block_y[i] - 10 >= y ){

                    groundPixel = block_y[i] - 10;
                    prev_groundPixel = groundPixel - 30;
                    maxRight = block_x[i];
                    }
                }

                if(x >= block_x[i]){

                maxLeft = block_x[i] + 25;

                if (block_y[i] - 10 >= y){
                    groundPixel = block_y[i] - 10;
                    prev_groundPixel = groundPixel - 30;
                    maxLeft = block_x[i];
                    }
                }
            }

            if (x < block_x[i] - 15 || x > block_x[i] + 25){
                test[i] = true;
            }else{
                test[i] = false;
            }


        if (checkBoolArray()){
            groundPixel = prev_groundPixel;
        }
        if (maxLeft == block_x[0]){
            maxLeft = 0;
        }
        if (maxRight == block_x[104]){
            maxRight = 1905;
        }
        if (x >= block_x[102]){
            updateLevel();
        }

    }
    for (int i = 0; i < 2; ++i){
        if (x >= spike_x[i]  && x <= spike_x[i] + 15 && y >= spike_y[i]){
            groundPixel = spike_y[i] - 10;
            prev_groundPixel = groundPixel - 30;
            inGame = false;
        }
    }

}

void Ball::terminalOut() {

  QTextStream out(stdout);
  out << "x = " << x << endl;
  out << "y = " << y << endl;
  out << "numberOfLevel = " << NumberOfLevel << endl;
  out << "gameOver = " << gameOverBool << endl;
  out << "Right = " << maxRight << endl;
  out << "prev_Ground pixel = " << prev_groundPixel << endl;

}





void Ball::timerEvent(QTimerEvent *e) {
    //QPainter qp(this);
    Q_UNUSED(e);

    if (inGame) {

       checkCollision();
       move();
       jump();
       terminalOut();

    }else{

    }
    repaint();
}


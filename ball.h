#pragma once

#include <QPushButton>
#include <QWidget>
#include <QKeyEvent>
#include <QPixmap>
#include <QColor>
#include <QThread>
#include <QEventLoop>


class Ball : public QWidget {

    public:
        Ball(QWidget *parent = 0);

        static void msleep(int ms)
                {
                    QThread::msleep(ms);
                }

    protected:
        void paintEvent(QPaintEvent *);
        void timerEvent(QTimerEvent *);
        void keyPressEvent(QKeyEvent *);
        void keyReleaseEvent(QKeyEvent *);
    private:
        QImage head;
        QImage field;
        QImage bad_pixel;
        QImage block;
        QImage spike;
        QImage white_screen;
        QImage field_1;
        QImage field_2;
        QImage block1;


        QEventLoop loop;

        QColor clrCurrent_Down;
        QColor clrCurrent_Up;
        QColor clrCurrent_Right;
        QColor clrCurrent_Left;
        QRgb qRgb;

        static const int B_WIDTH = 1920;
        static const int B_HEIGHT = 1080;
        static const int DOT_SIZE = 5;
        static const int DELAY = 20;

        int timerId;

        bool test[256];
        bool test1[256];

        int x;
        int y;
        int block_down_green;
        int block_down_blue;
        int block_left;
        int block_right;
        int spike_down;
        int spike_left;
        int spike_right;


        int badBlock_x;
        int badBlock_y;
        int groundPixel;
        int prev_groundPixel;
        int next_groundPixel;
        int cur_groundPixel;
        int maxRight;
        int maxLeft;
        int NumberOfLevel;
        int initNumber;

        bool gameOverBool;
        bool boolDown;
        bool boolDontReapeatJump;
        bool inGame;
        bool booljump;
        bool drawField;
        bool rightDirection;
        bool leftDirection;
        bool testspike;

        void loadImages();
        void initGame();
        void locateBadPixel();
        void moveObject();
        void checkCollision();
        void jump();
        void updateLevel();
        void down();
        void move();
        void terminalOut();
        void doDrawing();
        bool checkBoolArray();
        void finishGame(QPainter *, QString,QString);
        void gameOver(QPainter &);
};





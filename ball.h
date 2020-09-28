#pragma once

#include <QWidget>
#include <QKeyEvent>

class Ball : public QWidget {

    public:
        Ball(QWidget *parent = 0);

    protected:
        void paintEvent(QPaintEvent *);
        void timerEvent(QTimerEvent *);
        void keyPressEvent(QKeyEvent *);
        void keyReleaseEvent(QKeyEvent *);
    private:
        QImage head;
        QImage field;
        QImage bad_pixel;

        static const int B_WIDTH = 1920;
        static const int B_HEIGHT = 1080;
        static const int DOT_SIZE = 5;
        static const int DELAY = 45;

        int timerId;

        int x;
        int y;

        int groundPixel;
        int maxRight;

        bool boolDontReapeatJump;
        bool inGame;
        bool booljump;
        bool drawField;
        bool rightDirection;
        bool leftDirection;

        void loadImages();
        void initGame();
        void locateBadPixel();
        void checkApple();
        void moveObject();
        void checkCollision();
        void jump();
        void down();
        void move();
        void terminalOut();
        void doDrawing();
        void gameOver(QPainter &);
};

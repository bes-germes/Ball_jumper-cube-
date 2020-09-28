#include <QApplication>
#include "ball.h"

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);

  Ball window;

  window.setWindowTitle("Ball_jumper");
  window.show();

  return app.exec();
}

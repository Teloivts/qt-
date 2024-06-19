#include "mainwindow.h"
#include "first.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    //QApplication::setOverrideCursor(Qt::BlankCurror);
    first f;
    f.show();
    //MainWindow w;
    //w.setMouseTracking(true);//开启鼠标追踪
    //w.show();
    return a.exec();
}

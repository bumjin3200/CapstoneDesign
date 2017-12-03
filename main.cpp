#include "window.h"
#include "getdata.h"
#include "getSocket.h"
#include <QApplication>
#include <QThread>
#include <QTimer>

using namespace::std;
//Additional header files

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Window *window;
    getdata *gd;
    getsocket *gs;
    gd = new getdata();
    gs = new getsocket();
    window = new Window();
   
    window->show();
    window->resize(800,480);
    gd->start();
    QObject::connect(gd,SIGNAL(make(int,int,int)),window, SLOT(make(int,int,int)));
    gs->start();
    QObject::connect(gs,SIGNAL(gesture(QString)),window, SLOT(gesture(QString)));
    return app.exec();
}


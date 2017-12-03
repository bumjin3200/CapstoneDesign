#include "circlewidget.h"
#include "window.h"
#include <QtWidgets>
#include <QImage>
#include <QTimer>
#include <string>
#include <QDebug>
using namespace::std;

Window::Window()
{
    setWindowTitle(tr("DADM"));
    // Making title message
    stateAndroid = "none";
    // Initializing state of Android
//    gd->start();
}
void Window::displayAndroid(QString state, QString number, QString content)
{
    stateAndroid = state;
    // Changing state of Android
    displayBackGroundAndroid(state);
    // Setting background of right sight
    displayStateAndroid(state,number,content);
    // Setting Message of right sight
}
void Window::displayStateAndroid(QString state,QString number,QString content)
{
    // Setting String
    QString *words;
    QFont font;
    if(state == "call")
    {
        words = new QString("Call from \n\n" + number);
        font.setPointSize(32);
    }
    else if(state == "msg")
    {
	for(int i = 16 ; i<content.length() ; i = i+17)
		content.insert(i,"\n");
        words = new QString("from " + number+"\n" + content);
	font.setPointSize(20);
    }
    // Setting Text Color
    QPalette palette;
    QBrush brush(QColor(255, 255, 255, 255));
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
    palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);

    // Making widget
    QLabel *displayMsg = new QLabel(this);
    displayMsg->setFont(font);
    displayMsg->setText(*words);
    displayMsg->setPalette(palette);
    displayMsg->setAlignment(Qt::AlignCenter);

    // Display widget
    displayMsg->move(455,200);         //QLabel위치 조정
    displayMsg->show();

    // Connect function for closing this.
    connect(this, SIGNAL(androidFinish()),displayMsg, SLOT(close()));

}

void Window::displayBackGroundAndroid(QString state)
{
    // Setting imege
    QImage *img;
    QLabel *imgview;
    img = new QImage();
    QPixmap *buffer = new QPixmap();
    if(state == "call")
          img->load(":/call.png");
    else if(state == "msg")
          img->load(":/msg.png");
    else if(state == "success")
          img->load(":/success.png");
    else if(state == "emergency")
	  img->load(":/emergency.png");
    *buffer = QPixmap::fromImage(*img);

    // Making widget
    imgview = new QLabel(this);
    imgview->setPixmap(*buffer);
    imgview->resize(buffer->width(),buffer->height());

    // Display widget
    if(state != "emergency")
	    imgview->move(440,47);
    
    imgview->show();

    // Connect function for closing this.
    if(state != "success")
	    connect(this, SIGNAL(androidFinish()),imgview, SLOT(close()));
    else
	    connect(this, SIGNAL(successFinish()),imgview, SLOT(close()));
}
void Window::makeCircle(int x, int y, int r)
{
    // For connect function
    QTimer *timer = new QTimer(this);

    // Setting and making CircleWidget
    CircleWidget *circleWidgets;
    QGridLayout *layout = new QGridLayout();
    circleWidgets = new CircleWidget();
    circleWidgets->resize(400,480);

    // Points that made circle
    circleWidgets->setPointAndRadius(x,y,r);

    // Setting timer for circle display
    timer->start(12);
    connect(timer, SIGNAL(timeout()),circleWidgets, SLOT(nextAnimationFrame()));
    layout->addWidget(circleWidgets,1,1);
    setLayout(layout);
    delete layout; 
}

void Window::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/normal.png").scaled(size()));
    QWidget::paintEvent(e);
}

void Window::timerEvent(QTimerEvent *event)
{
        emit successFinish();
        stateAndroid = "none";
}

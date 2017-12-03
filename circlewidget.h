#ifndef CIRCLEWIDGET_H
#define CIRCLEWIDGET_H

#include <QWidget>
#include <iostream>
#include <QThread>
#include <thread>
using namespace::std;
//! [0]
class CircleWidget : public QWidget
{
    Q_OBJECT
public:

    CircleWidget(QWidget *parent = 0);
    void setFloatBased(bool floatBased);
    void setAntialiased(bool antialiased);
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    // Setting points
    void setPointAndRadius(int _x, int _y, int _r);

    // Points that circle made
    int x;
    int y;
    int r;
public slots:
    // Function for animation
    void nextAnimationFrame();
signals:
    void finished();
protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    bool floatBased;
    bool antialiased;
    int frameNo;
};
//! [0]

#endif // CIRCLEWIDGET_H

#include "canvas.h"
#include <iostream>

Canvas::Canvas(QWidget *parent) :
    QWidget(parent),
    pen{QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)},
    brush{QBrush(Qt::darkGreen)}
{

}

QSize Canvas::sizeHint() const{
    return QSize(200, 200);
}

void Canvas::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect rect(10, 10, 180, 180);
    painter.drawEllipse(rect);
}

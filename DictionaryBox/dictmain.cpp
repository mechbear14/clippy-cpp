#include "dictmain.h"
#include <QDebug>

DictMain::DictMain(QWidget *parent)
    : QWidget(parent)
    , startPage{ new DictStartPage(parent) }
    , frontEnd{ new DictFrontend() }
{
    startPage->setFrontend(frontEnd);
}

void DictMain::start()
{
    QPoint boxSize { QPoint(startPage->width(), startPage->height()) };
    startPage->move(topLeft - QPoint(boxSize.x() / 2 - 100, boxSize.y() + 10));
    startPage->show();
    qDebug() << boxSize;
    qDebug() << size();
}

void DictMain::setTopLeft(QPoint topLeft){
    this->topLeft = topLeft;
}

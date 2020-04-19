#include "dictmain.h"
#include <QDebug>

DictMain::DictMain(QWidget *parent)
    : startPage{ new DictStartPage(parent) }
    , searchingPage{ new DictSearchingPage(parent) }
    , resultPage{ new DictResultPage(parent) }
    , frontEnd{ new DictFrontend }
    , httpAPI{ new DictHTTP }
    , parent{ parent }
{
    startPage->setFSM(frontEnd);
    searchingPage->setFSM(frontEnd);
    resultPage->setFSM(frontEnd);
    httpAPI->setFSM(frontEnd);
}

void DictMain::start()
{
    startPage->show();
}

void DictMain::setTopLeft(QPoint topLeft){
    frontEnd->setTopLeft(topLeft);
}

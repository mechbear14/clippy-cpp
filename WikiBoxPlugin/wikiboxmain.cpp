#include "wikiboxmain.h"

WikiBoxMain::WikiBoxMain(QObject *parent)
    : QObject(parent)
    , states{ new WikiBoxState }
    , startPage{ new StartPage(qobject_cast<QWidget *> (parent)) }
    , searchingPage{ new SearchingPage(qobject_cast<QWidget *> (parent)) }
    , resultPage{ new ResultPage(qobject_cast<QWidget *> (parent)) }
{

}

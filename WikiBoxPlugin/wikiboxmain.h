#ifndef WIKIBOXMAIN_H
#define WIKIBOXMAIN_H

#include "wikiboxbackend.h"
#include "wikiboxstate.h"
#include "wikiboxui.h"

#include <QObject>

class WikiBoxMain : public QObject
{
    Q_OBJECT
public:
    explicit WikiBoxMain(QObject *parent = nullptr);

signals:

public slots:
private:
    WikiBoxBackend *backend;
    WikiBoxState *states;
    StartPage *startPage;
    SearchingPage *searchingPage;
    ResultPage *resultPage;
};

#endif // WIKIBOXMAIN_H

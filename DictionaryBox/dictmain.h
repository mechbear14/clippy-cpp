#ifndef DICTMAIN_H
#define DICTMAIN_H

#include <QWidget>
#include "dictfrontend.h"
#include "dicthttp.h"
#include "dictresultpage.h"
#include "dictsearchingpage.h"
#include "dictstartpage.h"

class DictMain
{
public:
    explicit DictMain(QWidget *parent = nullptr);
    void start();
    void setTopLeft(QPoint topLeft);

private:
    DictStartPage *startPage;
    DictSearchingPage *searchingPage;
    DictResultPage *resultPage;
    DictFrontend *frontEnd;
    DictHTTP *httpAPI;

    QWidget *parent;
    QPoint topLeft;
};

#endif // DICTMAIN_H

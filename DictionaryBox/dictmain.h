#ifndef DICTMAIN_H
#define DICTMAIN_H

#include "dictfrontend.h"
#include "dictstartpage.h"

#include <QMouseEvent>
#include <QWidget>

class DictMain : public QWidget
{
    Q_OBJECT
public:
    explicit DictMain(QWidget *parent = nullptr);
    void start();
    void setTopLeft(QPoint topLeft);

signals:

public slots:

private:
    DictStartPage *startPage;
    DictFrontend *frontEnd;

    QPoint topLeft;
};

#endif // DICTMAIN_H

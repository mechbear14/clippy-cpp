#ifndef CLIPPYMAIN_H
#define CLIPPYMAIN_H

#include "abstractclippystate.h"
#include "clippywidget.h"

#include <QObject>

class ClippyMain : public QObject
{
    Q_OBJECT
public:
    explicit ClippyMain(QObject *parent = nullptr);
    void start(QPoint *topleft);

signals:

private:
    ClippyWidget * clippy;
    AbstractClippyState * state;
};

#endif // CLIPPYMAIN_H

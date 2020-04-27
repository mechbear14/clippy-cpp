#ifndef ABSTRACTCLIPPYSTATE_H
#define ABSTRACTCLIPPYSTATE_H

#include <QObject>
#include <QMovie>

class AbstractClippyState : public QObject
{
    Q_OBJECT
public:
    explicit AbstractClippyState(QObject *parent = nullptr);
    void start(QPoint *topleft);

signals:
    void setAnimation(QMovie * animation);
    void startWidget(QPoint *topleft);

public slots:
    virtual void onClick();
    virtual void onAnimationEnd();
};

#endif // ABSTRACTCLIPPYSTATE_H

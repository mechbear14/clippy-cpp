#ifndef CLIPPYSTATE_H
#define CLIPPYSTATE_H

#include "abstractclippystate.h"

#include <vector>
#include <queue>
#include <QObject>
#include <QRandomGenerator>

class ClippyState : public AbstractClippyState
{
    Q_OBJECT
public:
    ClippyState(QObject *parent = nullptr);

    // TODO: Change these to enum
    static const char IDLE = 0;
    static const char BLINK = 1;
    static const char LEFT = 2;
    static const char RIGHT = 3;
    static const char MOVE_CLOSE = 4;

    void start(QPoint *topleft);

signals:
    // TODO: Should this be in abstract class?
    void animationEnded();

public slots:
    void onClick() override;
    void onAnimationEnd() override;

private slots:
    // TODO: Should this be in abstract class?
    void onUpdate(int frameNumber);
    void setNextAnimation();

private:
    char animationState;
    std::vector<QString> filenames;
    std::vector<QMovie *> animations;
    std::vector<int> frameNumbers;
    std::queue<char> toPlay;
    QRandomGenerator *nextGenerator;
};

#endif // CLIPPYSTATE_H

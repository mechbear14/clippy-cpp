#include <algorithm>
#include <QDebug>
#include <QTimer>
#include "clippystate.h"

const char ClippyState::IDLE;
const char ClippyState::BLINK;
const char ClippyState::LEFT;
const char ClippyState::RIGHT;
const char ClippyState::MOVE_CLOSE;

ClippyState::ClippyState(QObject *parent)
    : AbstractClippyState(parent)
    , animationState{ ClippyState::IDLE }
    ,  filenames{
          ":/normal/idle.gif",
          ":/normal/twinkle.gif",
          ":/normal/left.gif",
          ":/normal/right.gif",
          ":/normal/approach.gif"
          }
    , nextGenerator{ new QRandomGenerator }
{
    animations.resize(filenames.size());
    std::transform(filenames.begin(), filenames.end(), animations.begin(), [](QString filename){
        return new QMovie(filename);
    });
    frameNumbers.resize(animations.size());
    std::transform(animations.begin(), animations.end(), frameNumbers.begin(), [](QMovie * movie){
        return movie->frameCount();
    });
    for(QMovie * movie: animations){
        connect(movie, &QMovie::frameChanged, this, &ClippyState::onUpdate);
    }
    connect(this, &ClippyState::animationEnded, this, &ClippyState::onAnimationEnd);
}

void ClippyState::onUpdate(int frameNumber){
    if(frameNumber >= frameNumbers[animationState] - 1){
        animations[animationState]->stop();
        emit animationEnded();
    }
}

void ClippyState::onClick(){
//    Temporary change
//    toPlay.push(ClippyState::MOVE_CLOSE);
    animationState = ClippyState::MOVE_CLOSE;
    emit setAnimation(animations[ClippyState::MOVE_CLOSE]);
}

void ClippyState::onAnimationEnd(){
//    if(toPlay.empty()){
//        emit setAnimation(animations[ClippyState::IDLE]);
//    } else {
//        emit setAnimation(animations[toPlay.front()]);
//        toPlay.pop();
//    }
//    int nextTime = nextGenerator->bounded(60, 120) * 1000;
//    QTimer *timer{ new QTimer(this) };
//    timer->setSingleShot(true);
//    connect(timer, &QTimer::timeout, this, &ClippyState::setNextAnimation);
//    timer->start(nextTime);
    setNextAnimation();
}

void ClippyState::setNextAnimation(){
    char selector = nextGenerator->bounded(0, 4);
    char choice = 0;
    if(selector > 2){
        choice = ClippyState::RIGHT;
    } else if (selector > 1){
        choice = ClippyState::LEFT;
    } else {
        choice = ClippyState::BLINK;
    }
    animationState = choice;
    emit setAnimation(animations[choice]);
}

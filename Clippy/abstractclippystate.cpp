#include "abstractclippystate.h"

AbstractClippyState::AbstractClippyState(QObject * parent)
    : QObject(parent)
{

}


void AbstractClippyState::start(QPoint *topleft){
    emit startWidget(topleft);
}

void AbstractClippyState::onClick(){

}

void AbstractClippyState::onAnimationEnd(){

}

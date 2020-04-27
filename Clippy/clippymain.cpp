#include "clippymain.h"
#include "clippystate.h"

ClippyMain::ClippyMain(QObject *parent)
    : QObject(parent)
    , clippy{ new ClippyWidget }
    , state{ new ClippyState(this) }
{
    clippy->setStateMachine(state);
}

void ClippyMain::start(QPoint *topleft){
    state->start(topleft);
}

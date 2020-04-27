#include "clippygif.h"

ClippyGIF::ClippyGIF(QString filename)
    : movie { new QMovie(filename) }
    , length { movie->frameCount() }
{
    connect(movie, &QMovie::frameChanged, this, &ClippyGIF::checkFinishOnUpdate);
}

void ClippyGIF::checkFinishOnUpdate(int frameNumber){
    if(frameNumber > length - 1){
        movie->stop();
        emit movieFinished();
    }
}

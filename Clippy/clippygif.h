#ifndef CLIPPYGIF_H
#define CLIPPYGIF_H

#include <QMovie>

class ClippyGIF : public QObject
{
    Q_OBJECT

public:
    ClippyGIF(QString filename);
    QMovie * getMovie();

signals:
    void movieFinished();

private slots:
    void checkFinishOnUpdate(int frameNumber);

private:
    QMovie * movie;
    int length;
};

#endif // CLIPPYGIF_H

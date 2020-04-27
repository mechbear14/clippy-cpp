#include "Clippy/clippywidget.h"
#include <QApplication>
#include <Clippy/clippymain.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    ClippyWidget w;
//    w.show();
    ClippyMain w;
    w.start(new QPoint(600, 600)); // TODO: Save and load start position
    return a.exec();
}

#include "clippywidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClippyWidget w;
    w.show();
    return a.exec();
}

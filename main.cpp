#include "clippywidget.h"
//#include "messagebox.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClippyWidget w;
//    MessageBox w;
    w.show();
    return a.exec();
}

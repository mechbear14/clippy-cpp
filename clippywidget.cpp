#include <QVBoxLayout>
#include <QMouseEvent>
#include <QAction>
#include <QCoreApplication>
#include "clippywidget.h"
#include "canvas.h"

ClippyWidget::ClippyWidget(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint)
//    , messageBox{ new MessageBox }
{
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TranslucentBackground);

    Canvas *canvas{ new Canvas };
    QVBoxLayout *layout{ new QVBoxLayout };
    layout->addWidget(canvas);
    layout->setMargin(0);

    setLayout(layout);
    setWindowTitle("Canvas");
    setContextMenuPolicy(Qt::ActionsContextMenu);

    QAction *quitAction{ new QAction(tr("&Quit")) };
    quitAction->setShortcut(tr("Ctrl+Q"));
    connect(quitAction, &QAction::triggered, this, &QCoreApplication::quit);
    addAction(quitAction);
}

QSize ClippyWidget::sizeHint() const{
    return QSize(200, 200);
}

void ClippyWidget::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        QPoint topLeft = frameGeometry().topLeft();
        dragPosition = event->globalPos() - topLeft;
//        messageBox->move(topLeft - messageBox->frameGeometry().topLeft());
//        messageBox->show();
        event->accept();
    }
}

void ClippyWidget::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() & Qt::LeftButton){
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}

void ClippyWidget::resizeEvent(QResizeEvent *event){
    int side = qMin(width(), height());
    QRegion maskedRegion(width() / 2 - side / 2, height() / 2 - side / 2, side,
                         side, QRegion::Ellipse);
    setMask(maskedRegion);
}

#include "clippywidget.h"

#include <QMouseEvent>
#include <QDebug>
#include <QAction>

ClippyWidget::ClippyWidget(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint )
    , clippy{ new QLabel }
    , mainLayout { new QVBoxLayout }
    , mousedown { false }
    , mousemove { false }
{
    QMovie * movie = new QMovie(":/normal/idle.gif");
    clippy->setMovie(movie);
    movie->start();
    mainLayout->addWidget(clippy);
    setLayout(mainLayout);

    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TranslucentBackground);
    QAction *quitAction = new QAction(tr("E&xit"), this);
    quitAction->setShortcut(tr("Ctrl+Q"));
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    addAction(quitAction);
    setContextMenuPolicy(Qt::ActionsContextMenu);
}

void ClippyWidget::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        mousedown = true;
        event->accept();
    }
}

void ClippyWidget::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() & Qt::LeftButton){
        move(event->globalPos() - dragPosition);
        mousemove = true;
        event->accept();
    }
}

void ClippyWidget::mouseReleaseEvent(QMouseEvent *event){
    if(mousedown && !mousemove){
        emit clicked();
//        qDebug() << "Clicked";
        event->accept();
    }
    mousedown = false;
    mousemove = false;
}

QSize ClippyWidget::sizeHint() const{
    return QSize(150, 150);
}

void ClippyWidget::setStateMachine(AbstractClippyState *state){
    if(this->state != state && this->state != nullptr){
        disconnect(this, &ClippyWidget::clicked, this->state, &AbstractClippyState::onClick);
        disconnect(this->state, &AbstractClippyState::startWidget, this, &ClippyWidget::onCreate);
        disconnect(this->state, &AbstractClippyState::setAnimation, this, &ClippyWidget::onSwitchMovie);
    }
    this->state = state;
    connect(this, &ClippyWidget::clicked, state, &AbstractClippyState::onClick);
    connect(state, &AbstractClippyState::startWidget, this, &ClippyWidget::onCreate);
    connect(state, &AbstractClippyState::setAnimation, this, &ClippyWidget::onSwitchMovie);
}

void ClippyWidget::onCreate(QPoint * position){
    move(*position);
    show();
}

void ClippyWidget::onSwitchMovie(QMovie * movie){
    clippy->setMovie(movie);
    movie->start();
}

#ifndef CLIPPYWIDGET_H
#define CLIPPYWIDGET_H

#include "abstractclippystate.h"
#include "clippygif.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

class ClippyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ClippyWidget(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    QSize sizeHint() const override;

    void setStateMachine(AbstractClippyState* state);

signals:
    void clicked();

public slots:
    void onCreate(QPoint * position);
    void onSwitchMovie(QMovie * movie);

private:
    QLabel * clippy;
    QVBoxLayout *mainLayout;
    std::vector<ClippyGIF> movies;
    bool mousedown;
    bool mousemove;
    QPoint dragPosition;
    AbstractClippyState * state;
};

#endif // CLIPPYWIDGET_H

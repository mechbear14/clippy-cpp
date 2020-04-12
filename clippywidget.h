#ifndef CLIPPYWIDGET_H
#define CLIPPYWIDGET_H

#include "messagebox.h"

#include <QWidget>

class ClippyWidget : public QWidget
{
    Q_OBJECT

public:
    ClippyWidget(QWidget *parent = nullptr);
    QSize sizeHint() const override;

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    QPoint dragPosition;
    MessageBox *messageBox;
    bool clicked;
    bool dragging;
};

#endif // CLIPPYWIDGET_H

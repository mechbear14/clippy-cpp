#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QWidget>

class MessageBox : public QWidget
{
    Q_OBJECT
public:
    explicit MessageBox(QWidget *parent = nullptr);
    QSize sizeHint() const override;

signals:

public slots:

};

#endif // MESSAGEBOX_H

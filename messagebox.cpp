#include "messagebox.h"

#include <QLabel>
#include <QPushButton>
#include <QSizePolicy>
#include <QVBoxLayout>

MessageBox::MessageBox(QWidget *parent) :
    QWidget(parent, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint)
{
    QLabel *message{ new QLabel(tr("Hello bear")) };
    QPushButton *okButton{ new QPushButton(tr("OK")) };
    QVBoxLayout *layout{ new QVBoxLayout(parent) };
    layout->addWidget(message);
    layout->addWidget(okButton);
    layout->setStretchFactor(message, 1);
    setLayout(layout);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum));
    setStyleSheet("MessageBox {background: #ffff80}");

    connect(okButton, &QAbstractButton::clicked, this, &MessageBox::close);
}

QSize MessageBox::sizeHint() const{
    return QSize(200, 150);
}

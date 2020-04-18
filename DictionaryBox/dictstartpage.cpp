#include "dictstartpage.h"

DictStartPage::DictStartPage(QWidget *parent)
    : QWidget(parent, Qt::Popup | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint)
    , title{ new QLabel(tr("What's that word? What's that word? What's that word? What's that word?")) }
    , input{ new QLineEdit(this) }
    , message{ new QLabel(this) }
    , backButton{ new QPushButton(tr("Back")) }
    , searchButton{ new QPushButton(tr("Search")) }
    , buttonLayout{ new QHBoxLayout }
    , mainLayout{ new QVBoxLayout }
{
    title->setStyleSheet("QLabel {font: bold}");
    message->setStyleSheet("QLabel {color: red}");
    message->hide();
    this->setStyleSheet("QPushButton, QLineEdit, DictStartPage {background: #ffffc8}, QPushButton:hover {background: #ffff80}");

    mainLayout->addWidget(title);
    mainLayout->addWidget(input);
    mainLayout->addWidget(message);
    buttonLayout->addWidget(backButton);
    buttonLayout->addWidget(searchButton);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum));
}

QSize DictStartPage::sizeHint() const{
    return QSize(200, 100);
}

void DictStartPage::setFrontend(QObject *frontend)
{
    this->frontend = frontend;
}

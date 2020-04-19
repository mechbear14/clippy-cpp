#include "dictsearchingpage.h"

DictSearchingPage::DictSearchingPage(QWidget *parent)
    : QWidget(parent, Qt::Popup | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint)
    , pageNumber{ DictFrontend::SEARCHINGPAGE }
    , text{ new QLabel(tr("Searching...")) }
    , cancelButton{ new QPushButton(tr("Cancel")) }
    , mainLayout{ new QVBoxLayout }
{
    this->setStyleSheet("QPushButton, DictSearchingPage {background: #ffffc8}, QPushButton:hover {background: #ffff80}");
    text->setWordWrap(true);

    mainLayout->addWidget(text);
    mainLayout->addWidget(cancelButton);
    mainLayout->setStretchFactor(text, 1);
    setLayout(mainLayout);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum));
}

QSize DictSearchingPage::sizeHint() const{
    return QSize(200, 100);
}

void DictSearchingPage::setFSM(DictFrontend *fsm){
    this->fsm = fsm;
    connect(this->cancelButton, &QPushButton::clicked, this, &DictSearchingPage::onCancel);
    connect(this, &DictSearchingPage::cancelSearch, this->fsm, &DictFrontend::onCancelSearch);
    connect(this->fsm, &DictFrontend::turnToPage, this, &DictSearchingPage::onTurnPage);
}

void DictSearchingPage::onTurnPage(const char & pageNumber){
    if(pageNumber == this->pageNumber){
        this->show();
    } else {
        this->hide();
    }
}

void DictSearchingPage::onCancel(){
    emit cancelSearch();
}



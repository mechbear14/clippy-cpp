#include "dictresultpage.h"

#include <QDesktopServices>

DictResultPage::DictResultPage(QWidget *parent)
    : QWidget(parent, Qt::Popup | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint)
    , pageNumber{ DictFrontend::RESULTPAGE }
    , nextURL{ QUrl("https://www.google.co.uk/") }
    , title{ new QLabel(tr("No item found")) }
    , content{ new QLabel(tr("You might want to search Google instead")) }
    , backButton{ new QPushButton(tr("Back")) }
    , detailButton{ new QPushButton(tr("Detail")) }
    , buttonLayout{ new QHBoxLayout }
    , mainLayout{ new QVBoxLayout }
{
    title->setStyleSheet("QLabel {font: bold}");
    title->setWordWrap(true);
    content->setWordWrap(true);
    this->setStyleSheet("QPushButton, QLineEdit, DictResultPage {background: #ffffc8}, QPushButton:hover {background: #ffff80}");

    mainLayout->addWidget(title);
    mainLayout->addWidget(content);
    buttonLayout->addWidget(backButton);
    buttonLayout->addWidget(detailButton);
    mainLayout->addLayout(buttonLayout);
    mainLayout->setStretchFactor(content, 1);
    setLayout(mainLayout);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum));
}

QSize DictResultPage::sizeHint() const{
    return QSize(200, 100);
}

void DictResultPage::setFSM(DictFrontend *fsm){
    this->fsm = fsm;

    connect(this, &DictResultPage::endSearch, this->fsm, &DictFrontend::onQuit);
    connect(this->backButton, &QPushButton::clicked, this->fsm, &DictFrontend::onNewSearch);
    connect(this->detailButton, &QPushButton::clicked, this, &DictResultPage::onExplore);

    connect(this->fsm, &DictFrontend::turnToPage, this, &DictResultPage::onTurnPage);
    connect(this->fsm, &DictFrontend::returnResultToScreen, this, &DictResultPage::onResult);
}

void DictResultPage::onTurnPage(const char & pageNumber){
    if(pageNumber == this->pageNumber){
        this->show();
    } else {
        this->hide();
    }
}

void DictResultPage::onResult(const QJsonObject & result,
                              const bool & isExpected,
                              const QUrl & nextURL)
{
    if(isExpected){
        title->show();
        title->setText(result["title"].toString());
        content->setText(result["snippet"].toString());
        detailButton->setText("Explore");
    } else {
        title->hide();
        content->setText("No Wikipedia entry found. You may search on Google instead.");
        detailButton->setText("Go to Google");
    }
    this->nextURL = nextURL;
    adjustSize();
}

void DictResultPage::onExplore(){
    QDesktopServices::openUrl(nextURL);
    emit endSearch();
}

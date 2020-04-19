#include "dictstartpage.h"

DictStartPage::DictStartPage(QWidget *parent)
    : QWidget(parent, Qt::Popup | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint)
    , pageNumber{ DictFrontend::STARTPAGE }
    , title{ new QLabel(tr("What's that word?")) }
    , input{ new QLineEdit }
    , message{ new QLabel(tr("Error: Not implemented")) }
    , backButton{ new QPushButton(tr("Back")) }
    , searchButton{ new QPushButton(tr("Search")) }
    , buttonLayout{ new QHBoxLayout }
    , mainLayout{ new QVBoxLayout }
{
    title->setStyleSheet("QLabel {font: bold}");
    title->setWordWrap(true);
    message->setStyleSheet("QLabel {color: red}");
    message->setWordWrap(true);
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

void DictStartPage::setFSM(DictFrontend *fsm){
    this->fsm = fsm;
    connect(this->input, &QLineEdit::textEdited, this, &DictStartPage::onInput);
    connect(this->backButton, &QPushButton::clicked, this, &DictStartPage::onBack);
    connect(this->searchButton, &QPushButton::clicked, this, &DictStartPage::onSubmit);
    connect(this, &DictStartPage::quit, this->fsm, &DictFrontend::onQuit);
    connect(this, &DictStartPage::startSearch, this->fsm, &DictFrontend::onStartSearch);
    connect(this, &DictStartPage::validationError, this, &DictStartPage::onError);

    connect(this->fsm, &DictFrontend::reportErrorToScreen, this, &DictStartPage::onError);
    connect(this->fsm, &DictFrontend::newSearch, this, &DictStartPage::onNewSearch);
    connect(this->fsm, &DictFrontend::turnToPage, this, &DictStartPage::onTurnPage);
}

void DictStartPage::onError(const QString & error){
    message->setText("Error: " + error);
    message->show();
    searchButton->setDisabled(false);
}

void DictStartPage::onNewSearch(){
    message->hide();
    searchButton->setDisabled(false);
}

void DictStartPage::onTurnPage(const char & pageNumber){
    if(pageNumber == this->pageNumber){
        this->show();
    } else {
        this->hide();
    }
}

void DictStartPage::onInput(const QString & text){
    if(message->isVisible()){
        message->hide();
    }
}

void DictStartPage::onBack(){
    emit quit();
}

void DictStartPage::onSubmit(){
    searchButton->setDisabled(true);
    if(input->text().isEmpty()){
        emit validationError("Query text cannot be empty");
        message->show();
        searchButton->setDisabled(false);
    } else {
        emit startSearch(input->text());
    }
}

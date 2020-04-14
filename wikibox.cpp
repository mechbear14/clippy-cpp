#include "wikibox.h"

WikiBox::WikiBox(QWidget *parent)
    : QWidget(parent, Qt::Popup | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint)
    , mainLayout { new QVBoxLayout }
    , startPage { new WikiStartPage(this) }
    , searchingPage { new WikiSearchingPage(this) }
    , resultPage { new WikiResultPage(this) }
    , currentPage { resultPage }
{
    mainLayout->addWidget(currentPage);
    toPage(startPage);
    setLayout(mainLayout);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum));
    setStyleSheet("WikiBox {background: #ffff80}");
}

QSize WikiBox::sizeHint() const{
    return QSize(200, 150);
}

void WikiBox::tryCallParent(){
    this->close();
}

void WikiBox::onSearchStart(){
    toPage(searchingPage);
}

void WikiBox::onSearchCancel(){
    toPage(startPage);
}

void WikiBox::onSearchComplete(){
    toPage(resultPage);
}

void WikiBox::onRestart(){
    toPage(startPage);
}

void WikiBox::toPage(QWidget *page){
    if(currentPage != page){
        startPage->hide();
        searchingPage->hide();
        resultPage->hide();
        page->show();
        mainLayout->replaceWidget(currentPage, page);
        currentPage = page;
    }
}

WikiStartPage::WikiStartPage(QWidget * parent)
    : QWidget(parent)
    , title { new QLabel(tr("What would you like to know?")) }
    , query { new QLineEdit }
    , searchButton { new QPushButton(tr("Search")) }
    , backButton { new QPushButton(tr("Back")) }
    , mainLayout { new QVBoxLayout }
    , buttonLayout { new QHBoxLayout }
{
    title->setStyleSheet("QLabel {font: bold}");
    title->setWordWrap(true);
    connect(backButton, &QPushButton::clicked, qobject_cast<WikiBox *>(parent), &WikiBox::tryCallParent);
    connect(searchButton, &QPushButton::clicked, qobject_cast<WikiBox *>(parent), &WikiBox::onSearchStart);
    buttonLayout->addWidget(backButton);
    buttonLayout->addWidget(searchButton);
    mainLayout->addWidget(title);
    mainLayout->addWidget(query);
    mainLayout->addLayout(buttonLayout);
    mainLayout->setMargin(0);
    setLayout(mainLayout);
}

WikiSearchingPage::WikiSearchingPage(QWidget * parent)
    : QWidget(parent)
    , title { new QLabel(tr("Searching...")) }
    , cancelButton { new QPushButton(tr("Cancel")) }
    , mainLayout { new QVBoxLayout }
{
    title->setWordWrap(true);
    connect(cancelButton, &QPushButton::clicked, qobject_cast<WikiBox *>(parent), &WikiBox::onSearchCancel);
    mainLayout->addWidget(title);
    mainLayout->addWidget(cancelButton);
    mainLayout->setMargin(0);
    setLayout(mainLayout);
}

WikiResultPage::WikiResultPage(QWidget * parent)
    : QWidget(parent)
    , contentBox { new QLabel(tr("No WikiPedia result found. I'm opening the browser for you though")) }
    , exploreButton { new QPushButton(tr("Explore")) }
    , backButton { new QPushButton(tr("Back")) }
    , buttonLayout { new QHBoxLayout }
    , mainLayout { new QVBoxLayout }
{
    contentBox->setWordWrap(true);
    connect(backButton, &QPushButton::clicked, qobject_cast<WikiBox *>(parent), &WikiBox::onRestart);
    buttonLayout->addWidget(backButton);
    if(!content.isEmpty()){
        buttonLayout->addWidget(exploreButton);
        connect(exploreButton, &QPushButton::clicked, qobject_cast<WikiBox *>(parent), &WikiBox::tryCallParent);
    }
    mainLayout->addWidget(contentBox);
    mainLayout->addLayout(buttonLayout);
    mainLayout->setMargin(0);
    setLayout(mainLayout);
}

void WikiResultPage::setContent(QString resultContent){
    content = resultContent;
}

#include <iostream>
#include "wikibox.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QJsonArray>
#include <QStringBuilder>
#include <QDesktopServices>

WikiBox::WikiBox(QWidget *parent)
    : QWidget(parent, Qt::Popup | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint)
    , mainLayout { new QVBoxLayout }
    , startPage { new WikiStartPage(this) }
    , searchingPage { new WikiSearchingPage(this) }
    , resultPage { new WikiResultPage(this) }
    , currentPage { resultPage }
    , http {new QNetworkAccessManager(this) }
{
    mainLayout->addWidget(currentPage);
    toPage(startPage);
    setLayout(mainLayout);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum));
    setStyleSheet("WikiBox {background: #ffff80}");
    connect(http, &QNetworkAccessManager::finished, this, &WikiBox::onSearchComplete);
}

QSize WikiBox::sizeHint() const{
    return QSize(200, 150);
}

void WikiBox::tryCallParent(){
    this->close();
}

void WikiBox::onSearchStart(){
    QString endpointBase {QString ("https://en.wikipedia.org/w/api.php?action=query&list=search&format=json&srsearch=")};
    queryText = startPage->getQueryText();
    if(queryText.isEmpty()){
        startPage->setMessage("Query text cannot be empty");
    } else {
        QUrl url{ endpointBase + queryText };
        url = url.toEncoded();
        response = http->get(QNetworkRequest(url));
        toPage(searchingPage);
    }
}

void WikiBox::onSearchCancel(){
    response->abort();
    toPage(startPage);
}

void WikiBox::onSearchComplete(){
    if(response->error()){
        startPage->setMessage(QString("Error: " + response->errorString()));
        toPage(startPage);
    } else {
        QJsonParseError *error{};
        QJsonObject jsonResponse { QJsonDocument::fromJson(response->readAll(), error).object() };
        QJsonObject result{ jsonResponse["query"].toObject()["search"].toArray()[0].toObject() };
        QString resultTitle{ result["title"].toString() };
        QString resultText{ result["snippet"].toString() };
        if(queryText.toLower() == resultTitle.toLower()){
            urlToOpen = QUrl(QString("https://en.wikipedia.org/wiki/" + queryText));
            urlToOpen = urlToOpen.toEncoded();
            resultPage->setContent(resultTitle, resultText);
        } else {
            urlToOpen = QUrl(QString("https://www.google.co.uk/search?q=" + queryText));
            urlToOpen = urlToOpen.toEncoded();
            resultPage->setContent("", "");
        }
        toPage(resultPage);
    }
    response->deleteLater();
}

void WikiBox::onRestart(){
    toPage(startPage);
}

void WikiBox::onExplore(){
    QDesktopServices::openUrl(urlToOpen);
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
    , message { new QLabel }
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
    mainLayout->addWidget(message);
    mainLayout->addWidget(query);
    mainLayout->addLayout(buttonLayout);
    mainLayout->setMargin(0);
    setLayout(mainLayout);
    message->hide();
}

QString WikiStartPage::getQueryText(){
    return query->text();
}

void WikiStartPage::setMessage(QString message){
    this->message->setText(message);
    this->message->show();
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
    , titleBox { new QLabel(tr("")) }
    , contentBox { new QLabel(tr("No WikiPedia result found. I'm opening the browser for you though")) }
    , exploreButton { new QPushButton(tr("Explore")) }
    , backButton { new QPushButton(tr("Back")) }
    , buttonLayout { new QHBoxLayout }
    , mainLayout { new QVBoxLayout }
{
    contentBox->setWordWrap(true);
    connect(backButton, &QPushButton::clicked, qobject_cast<WikiBox *>(parent), &WikiBox::onRestart);
    connect(exploreButton, &QPushButton::clicked, qobject_cast<WikiBox *>(parent), &WikiBox::onExplore);
    buttonLayout->addWidget(backButton);
    buttonLayout->addWidget(exploreButton);
    mainLayout->addWidget(titleBox);
    mainLayout->addWidget(contentBox);
    mainLayout->addLayout(buttonLayout);
    mainLayout->setMargin(0);
    setLayout(mainLayout);
}

void WikiResultPage::setContent(QString title, QString content){
    this->title = title;
    this->content = content;
    if(title.isEmpty()){
        titleBox->hide();
        contentBox->setText(tr("No WikiPedia result found. I'm opening the browser for you though"));
    } else {
        titleBox->show();
        titleBox->setText(title);
        contentBox->setText(content);
    }
}

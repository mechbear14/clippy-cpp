#include <QDebug>
#include <QStringBuilder>
#include "dictfrontend.h"

DictFrontend::DictFrontend(QObject *parent)
    : QObject(parent)
    , topLeft{ QPoint(0, 0) }
    , wikiPediaURLBase{ QString("https://en.wikipedia.org/wiki/") }
    , googleURLBase{ QString("https://www.google.co.uk/search?q=") }
{

}

QPoint DictFrontend::getTopLeft(){
    return topLeft;
}

void DictFrontend::setTopLeft(QPoint topLeft){
    this->topLeft = topLeft;
}

void DictFrontend::onError(const QString & error){
    emit reportErrorToScreen(error);
    emit turnToPage(DictFrontend::STARTPAGE);
}

void DictFrontend::onResult(const QJsonObject & result){
    if(result["title"].toString().toLower() == query.toLower()){
        QUrl nextURL = QUrl(wikiPediaURLBase + query);
        nextURL = nextURL.toEncoded();
        emit returnResultToScreen(result, true, nextURL);
    } else {
        QUrl nextURL = QUrl(googleURLBase + query);
        nextURL = nextURL.toEncoded();
        emit returnResultToScreen(result, false, nextURL);
    }
    emit turnToPage(DictFrontend::RESULTPAGE);
}

void DictFrontend::onQuit(){
    emit turnToPage(DictFrontend::CLOSED);
}

void DictFrontend::onStartSearch(const QString & query){
    this->query = query;
    emit turnToPage(DictFrontend::SEARCHINGPAGE);
    emit getQueryResult(this->query);
}

void DictFrontend::onCancelSearch(){
    emit cancelSearch();
}

void DictFrontend::onNewSearch(){
    emit turnToPage(DictFrontend::STARTPAGE);
}

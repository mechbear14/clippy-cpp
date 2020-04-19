#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QStringBuilder>
#include "dicthttp.h"

DictHTTP::DictHTTP(QObject *parent)
    : QObject(parent)
    , http{ new QNetworkAccessManager }
    , baseURL{ QString("https://en.wikipedia.org/w/api.php?action=query&list=search&format=json&srsearch=") }
{
    connect(http, &QNetworkAccessManager::finished, this, &DictHTTP::onRequestFinish);
}

void DictHTTP::onQuery(const QString & query){
    QUrl url{ baseURL + query };
    url = url.toEncoded();
    response = http->get(QNetworkRequest(url));
}

void DictHTTP::onRequestFinish(){
    if(response->error()){
        emit reportError(response->errorString());
    } else {
        QJsonParseError *error{ new QJsonParseError() };
        QJsonObject jsonResponse { QJsonDocument::fromJson(response->readAll(), error).object() };
        if(error->error != QJsonParseError::NoError){
            emit reportError(error->errorString());
        } else {
            QJsonObject result{ jsonResponse["query"].toObject()["search"].toArray()[0].toObject() };
            emit returnResult(result);
        }
    }
    response->deleteLater();
}

void DictHTTP::onCancel(){
    response->abort();
}

void DictHTTP::setFSM(DictFrontend *fsm){
    this->fsm = fsm;

    connect(this, &DictHTTP::reportError, this->fsm, &DictFrontend::onError);
    connect(this, &DictHTTP::returnResult, this->fsm, &DictFrontend::onResult);

    connect(this->fsm, &DictFrontend::getQueryResult, this, &DictHTTP::onQuery);
    connect(this->fsm, &DictFrontend::cancelSearch, this, &DictHTTP::onCancel);
}

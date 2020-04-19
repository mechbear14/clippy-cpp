#ifndef DICTHTTP_H
#define DICTHTTP_H

#include "dictfrontend.h"

#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>

class DictHTTP : public QObject
{
    Q_OBJECT
public:
    explicit DictHTTP(QObject *parent = nullptr);
    void setFSM(DictFrontend *fsm); // TODO: Change name!

signals:
    void returnResult(QJsonObject result);
    void reportError(QString error);

public slots:
    void onQuery(const QString & query);
    void onCancel();

private slots:
    void onRequestFinish();

private:
    QNetworkAccessManager *http;
    QNetworkReply *response;
    QString baseURL;
    DictFrontend *fsm;
};

#endif // DICTHTTP_H

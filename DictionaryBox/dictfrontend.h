#ifndef DICTFRONTEND_H
#define DICTFRONTEND_H

#include <QJsonObject>
#include <QUrl>
#include <vector>
#include <QObject>
#include <QPoint>

class DictFrontend : public QObject
{
    Q_OBJECT

public:
    explicit DictFrontend(QObject *parent = nullptr);
    void setTopLeft(QPoint topLeft);
    QPoint getTopLeft();
    // Think of another architecture. This is very awkward.
//    void addPage(QWidget* page);
//    void init();

    // After refactor
    const static char CLOSED = 3;
    const static char STARTPAGE = 0;
    const static char SEARCHINGPAGE = 1;
    const static char RESULTPAGE = 2;

signals:
    // After refactor
    void getQueryResult(QString query);
    void reportErrorToScreen(QString error);
    void returnResultToScreen(QJsonObject result, bool isExpected, QUrl nextURL);
    void turnToPage(char pageNumber);
    void cancelSearch();
    void newSearch();

public slots:
    // After refactor
    void onResult(const QJsonObject & result);
    void onError(const QString & error);
    void onQuit();
    void onStartSearch(const QString & query);
    void onCancelSearch();
    void onNewSearch();

private:    
    QPoint topLeft;

    // After refactor
    QString query;

    const QString wikiPediaURLBase;
    const QString googleURLBase;
};

#endif // DICTFRONTEND_H

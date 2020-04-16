#ifndef WIKIBOXFRONTEND_H
#define WIKIBOXFRONTEND_H

#include <QObject>

class WikiBoxFrontend : public QObject
{
    Q_OBJECT
public:
    explicit WikiBoxFrontend(QObject *parent = nullptr);

signals:

public slots:
    void quitProgram();
    void startSearch();
    void cancelSearch();
    void newSearch();
    void explore();
};

#endif // WIKIBOXFRONTEND_H

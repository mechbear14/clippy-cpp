#ifndef WIKIBOXSTATE_H
#define WIKIBOXSTATE_H

#include "wikiboxbackend.h"
#include "wikiboxfrontend.h"

#include <QObject>

class WikiBoxState : public QObject
{
    Q_OBJECT

public:
    explicit WikiBoxState(QObject *parent = nullptr,
                          WikiBoxFrontend *frontend = nullptr,
                          WikiBoxBackend *backend = nullptr);
    static const char QUIT = 0;
    static const char START = 1;
    static const char SEARCH = 2;
    static const char RESULT = 3;

signals:

public slots:

private:
    WikiBoxFrontend *frontend;
    WikiBoxBackend *backend;
};

#endif // WIKIBOXSTATE_H
